/* --------{ EB Automotive C Source File }-------- */
/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 13.5 (required)
 *   "The right hand operand of a logical && or || operator shall not contain persistent side effects."
 *
 *   Reason:
 *   The MISRA rule is not violated. This is a constraint of the MISRA checker: When a function
 *   is called on the right hand side of a logical operator, the checker always raises this error
 *   because it does not know whether the function has side effects or not. In our case, none of
 *   the functions have side effects.
 *
 *  MISRAC2012-2) Deviated Rule: 8.5 (required)
 *   " An external object or function shall be declared once in one and only one file."
 *
 *   Reason:
 *   This function will be used in some test case. In this case it is necessary this declaration.
 *
 */

/* !LINKSTO EB_CRY_0009,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Cry_LN.h>     /* !LINKSTO EB_CRY_0010,1 */
#include <TSAutosar.h>

/*==[Macros]==================================================================*/

#ifndef CRY_PRIV_DECL
#define CRY_PRIV_DECL static
#endif

#ifndef CRY_PRIV_DEFN
#define CRY_PRIV_DEFN static
#endif

#if (defined CRY_LN_LENGTH_POS)
#error CRY_LN_LENGTH_POS is already defined
#endif
/**
 * \brief The position of the length in a number.
 *
 */
#define CRY_LN_LENGTH_POS 0U

#if (defined CRY_LN_LSW_POS)
#error CRY_LN_LSW_POS is already defined
#endif
/**
 * \brief The position of the least significant word in a number.
 *
 */
#define CRY_LN_LSW_POS    1U

#if (CPU_TYPE == CPU_TYPE_32)

#if (defined CRY_LN_WORD_MAX)
#error CRY_LN_WORD_MAX is already defined
#endif
/**
 * \brief The maximal value which can be stored in an unsigned word.
 */
#define CRY_LN_WORD_MAX           0xFFFFFFFFU

#elif (CPU_TYPE == CPU_TYPE_16)

#if (defined CRY_LN_WORD_MAX)
#error CRY_LN_WORD_MAX is already defined
#endif
/**
 * \brief The maximal value which can be stored in an unsigned word.
 *
 */
#define CRY_LN_WORD_MAX           0xFFFFU

#endif

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)

#if (defined CRY_MONT_CALCMU)
#error CRY_MONT_CALCMU is already defined
#endif
/**
 * \brief Calculate mu = Number * Rho.
 */
#define CRY_MONT_CALCMU  mu = c[x] * Rho

#if (defined CRY_MONT_INNERMUL)
#error CRY_MONT_INNERMUL is already defined
#endif
/**
 * \brief Calculate the product and handle the carry.
 */
#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON)
#define CRY_MONT_INNERMUL                                               \
  do                                                                    \
  {                                                                     \
    Cry_LNDoubleWordType t;                                             \
    t = ((Cry_LNDoubleWordType)cPtr[0] + (Cry_LNDoubleWordType)carry) +   \
        (((Cry_LNDoubleWordType)mu) * (Cry_LNDoubleWordType)modPtr[y]); \
    cPtr[0] = (Cry_LNWordType)(t & CRY_LN_WORD_MAX);                      \
    carry = (Cry_LNWordType)(t >> CRY_LN_WORD_LEN_BITS);                \
  } while (0U)
#else
#define CRY_MONT_INNERMUL                                           \
  do                                                                \
  {                                                                 \
    Cry_LNWordType locRes[2];                                       \
    CRY_U32_MUL(modPtr[y], mu, locRes[0], locRes[1]);               \
    CRY_U32_ADD(locRes[0], locRes[1], carry, locRes[0], locRes[1]); \
    CRY_U32_ADD(locRes[0], locRes[1], cPtr[0], cPtr[0], carry);         \
  } while (0U)
#endif

#if (defined CRY_MONT_PROPCARRY)
#error CRY_MONT_PROPCARRY is already defined
#endif
/**
 * \brief Propagate the carry.
 */
#define CRY_MONT_PROPCARRY                                         \
  do                                                               \
  {                                                                \
    Cry_LNWordType t;                                              \
    cPtr[0] += carry;                                                \
    t     = cPtr[0];                                                 \
    carry = (t < carry) ? (Cry_LNWordType)1U : (Cry_LNWordType)0U; \
  } while (0U)

#if (defined CRY_MONT_POWOF2)
#error CRY_MONT_POWOF2 is already defined
#endif
/**
 * \brief Compute 2 ** Exponent
 */
#define CRY_MONT_POWOF2(Number, Exponent)                                                         \
  do                                                                                              \
  {                                                                                               \
    uint8          carry         = (((Exponent) % CRY_LN_WORD_LEN_BITS) > 0U) ? 1U : 0U;          \
    Cry_LNWordType WordOffset    = (Cry_LNWordType)((Exponent) / ((uint32)CRY_LN_WORD_LEN_BITS)); \
    (Number)[WordOffset + carry] = (Cry_LNWordType)1U << ((Exponent) % CRY_LN_WORD_LEN_BITS);     \
    (Number)[0]                  = WordOffset + carry;                                            \
  } while (0U)

#if (defined CRY_COMBA_FORWARD)
#error CRY_COMBA_FORWARD is already defined
#endif
/** \brief Forward shift the carry word */
#define CRY_COMBA_FORWARD                                                      \
  do {                                                                         \
    c0 = c1;                                                                   \
    c1 = c2;                                                                   \
    c2 = 0U;                                                                   \
  } while (0U);

#if (defined CRY_COMBA_MULADD)
#error CRY_COMBA_MULADD is already defined
#endif
/** \brief Compute the column product */
#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON)
#define CRY_COMBA_MULADD(i, j)                                                               \
  do                                                                                         \
  {                                                                                          \
    Cry_LNDoubleWordType t;                                                                  \
    t  = (Cry_LNDoubleWordType)c0 + ((Cry_LNDoubleWordType)(i) * (Cry_LNDoubleWordType)(j)); \
    c0 = (Cry_LNWordType)(t & CRY_LN_WORD_MAX);                                              \
    t  = (Cry_LNDoubleWordType)c1 + (t >> CRY_LN_WORD_LEN_BITS);                             \
    c1 = (Cry_LNWordType)(t & CRY_LN_WORD_MAX);                                              \
    c2 += (Cry_LNWordType)(t >> CRY_LN_WORD_LEN_BITS);                                       \
  } while (0U)
#else
#define CRY_COMBA_MULADD(i, j)                                                 \
  do {                                                                         \
    Cry_LNWordType locRes[2], t[2];                                            \
    CRY_U32_MUL((i), (j), locRes[0], locRes[1]);                               \
    CRY_U32_ADD(locRes[0], locRes[1], c0, t[0], t[1]);                         \
    c0 = t[0];                                                                 \
    CRY_U32_ADD(t[1], 0U, c1, t[0], t[1]);                                     \
    c1 = t[0];                                                                 \
    CRY_U32_ADD(t[1], 0U, c2, locRes[0], locRes[1]);                           \
    c2 = locRes[0];                                                            \
  } while (0U)
#endif

#if (defined CRY_COMBA_SQRADD2)
#error CRY_COMBA_SQRADD2 is already defined
#endif
/** \brief For squaring some of the terms are doubled */
#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON)
#define CRY_COMBA_SQRADD2(i, j)                                   \
  do                                                              \
  {                                                               \
    Cry_LNDoubleWordType t, tt;                                   \
    t  = ((Cry_LNDoubleWordType)(i) * (Cry_LNDoubleWordType)(j)); \
    tt = (Cry_LNDoubleWordType)c0 + t;                            \
    c0 = (Cry_LNWordType)(tt & CRY_LN_WORD_MAX);                  \
    tt = (Cry_LNDoubleWordType)c1 + (tt >> CRY_LN_WORD_LEN_BITS); \
    c1 = (Cry_LNWordType)(tt & CRY_LN_WORD_MAX);                  \
    c2 += (Cry_LNWordType)(tt >> CRY_LN_WORD_LEN_BITS);           \
    tt = (Cry_LNDoubleWordType)c0 + t;                            \
    c0 = (Cry_LNWordType)(tt & CRY_LN_WORD_MAX);                  \
    tt = (Cry_LNDoubleWordType)c1 + (tt >> CRY_LN_WORD_LEN_BITS); \
    c1 = (Cry_LNWordType)(tt & CRY_LN_WORD_MAX);                  \
    c2 += (Cry_LNWordType)(tt >> CRY_LN_WORD_LEN_BITS);           \
  } while (0U)
#else
#define CRY_COMBA_SQRADD2(i, j)                                                \
  do {                                                                         \
    Cry_LNWordType locRes[2], t[2], tt[2];                                     \
    CRY_U32_MUL((i), (j), t[0], t[1]);                                         \
    CRY_U32_ADD(t[0], t[1], c0, tt[0], tt[1]);                                 \
    c0 = tt[0];                                                                \
    CRY_U32_ADD(tt[1], 0U, c1, tt[0], tt[1]);                                  \
    c1 = tt[0];                                                                \
    CRY_U32_ADD(tt[1], 0U, c2, locRes[0], locRes[1]);                          \
    c2 = locRes[0];                                                            \
    CRY_U32_ADD(t[0], t[1], c0, tt[0], tt[1]);                                 \
    c0 = tt[0];                                                                \
    CRY_U32_ADD(tt[1], 0U, c1, tt[0], tt[1]);                                  \
    c1 = tt[0];                                                                \
    CRY_U32_ADD(tt[1], 0U, c2, locRes[0], locRes[1]);                          \
    c2 = locRes[0];                                                            \
  } while (0U)
#endif

#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_OFF)
#if (defined CRY_U32_MUL)
#error CRY_U32_MUL is already defined
#endif
/** \brief Calculate p * q and put the 'MSW' in resH and the 'LSW' in resL */
#define CRY_U32_MUL(p, q, resL, resH)                                                             \
  do                                                                                              \
  {                                                                                               \
    Cry_LNWordType s0, s1, s2, s3, partProd;                                                      \
    partProd = Cry_LNLowHalfWord((q)) * Cry_LNLowHalfWord((p));                                   \
    s0       = Cry_LNLowHalfWord(partProd);                                                       \
    partProd = (Cry_LNHighHalfWord((q)) * Cry_LNLowHalfWord((p))) + Cry_LNHighHalfWord(partProd); \
    s1       = Cry_LNLowHalfWord(partProd);                                                       \
    s2       = Cry_LNHighHalfWord(partProd);                                                      \
    partProd = s1 + (Cry_LNLowHalfWord((q)) * Cry_LNHighHalfWord((p)));                           \
    s1       = Cry_LNLowHalfWord(partProd);                                                       \
    partProd =                                                                                    \
      (s2 + Cry_LNHighHalfWord(partProd)) + (Cry_LNHighHalfWord((q)) * Cry_LNHighHalfWord((p)));  \
    s2     = Cry_LNLowHalfWord(partProd);                                                         \
    s3     = Cry_LNHighHalfWord(partProd);                                                        \
    (resL) = (Cry_LNWordType)((Cry_LNWordType)s1 << CRY_LN_HALFWORD_LEN_BITS) | s0;               \
    (resH) = (Cry_LNWordType)((Cry_LNWordType)s3 << CRY_LN_HALFWORD_LEN_BITS) | s2;               \
  } while (0U)

#if (defined CRY_U32_ADD)
#error CRY_U32_ADD is already defined
#endif
/** \brief Calculate [qH:qL] + p and put the 'MSW' in resH and the 'LSW' in resL */
#define CRY_U32_ADD(qL, qH, p, resL, resH)                                        \
  do                                                                              \
  {                                                                               \
    Cry_LNWordType cLH, xLH, xUH;                                                 \
    xLH    = Cry_LNLowHalfWord((qL)) + Cry_LNLowHalfWord((p));                    \
    cLH    = Cry_LNHighHalfWord(xLH);                                             \
    xUH    = (Cry_LNHighHalfWord((qL)) + Cry_LNHighHalfWord((p))) + cLH;          \
    (resL) = ((xLH)&CRY_LN_HALFWORD_MAX) |                                        \
             (Cry_LNWordType)((Cry_LNWordType)(xUH) << CRY_LN_HALFWORD_LEN_BITS); \
    (resH) = (qH) + ((xUH) >> CRY_LN_HALFWORD_LEN_BITS);                          \
  } while (0U)
#endif

#endif

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_BEGIN
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation is be performed and the location
 ** where the result is stored
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \param[out] Finished A pointer to a boolean which indicates whether the modulo
 ** operation is completed
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloBegin
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  P2VAR(boolean,          AUTOMATIC, CRY_APPL_DATA) Finished
);

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_SHIFT1
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus.
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloShift1
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_SHIFT2.
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation is be performed and the location
 ** where the result is stored.
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus.
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloShift2
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_SUBTRACT1.
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \param[out] Finished A pointer to a boolean which indicates whether the modulo
 ** operation is completed.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloSubtract1
(
  P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_SUBTRACT2.
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation is be performed and the location
 ** where the result is stored.
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus.
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloSubtract2
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_CARRY
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation is be performed and the location
 ** where the result is stored.
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloCarry
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2VAR(Cry_LNCtxType,  AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_EXPORT.
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloExport
(
  P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a multiplication
 **
 ** This function perform the computations in the state CRY_LN_S_MULTIPLY_BEGIN.
 **
 ** \param[out] Result=a pointer to the memory area which should contain the
 ** long number representation of the result of the multiplication
 **
 ** \param[in] Multiplicand A pointer to the long number representation of
 **  the multiplicand
 **
 ** \param[in] Multiplicator A pointer to the long number representation of
 **  the multiplicator
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **  multiplication.
 **
 ** \param[out] Finished A pointer which points to a variable which indicates
 ** whether the functionality is finished
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNStateMultiplyBegin
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  P2VAR(boolean,          AUTOMATIC, CRY_APPL_DATA) Finished
);

/** \brief Helper function for a multiplication
 **
 ** This function perform the computations in the state CRY_LN_S_MULTIPLY_COMPUTE_OSUM.
 **
 ** \param[in] Multiplicand A pointer to the long number representation of
 **  the multiplicand
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **  multiplication.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNStateMultiplyComputeOsum
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a multiplication
 **
 ** This function perform the computations in the state CRY_LN_S_MULTIPLY_COMPUTE_ISUM1.
 **
 ** \param[in] Multiplicand A pointer to the long number representation of
 **  the multiplicand
 **
 ** \param[in] Multiplicator A pointer to the long number representation of
 **  the multiplicator
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **  multiplication.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNStateMultiplyComputeIsum1
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a multiplication
 **
 ** This function perform the computations in the state CRY_LN_S_MULTIPLY_COMPUTE_ISUM2.
 **
 ** \param[in] Multiplicand A pointer to the long number representation of
 **  the multiplicand
 **
 ** \param[in] Multiplicator A pointer to the long number representation of
 **  the multiplicator
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **  multiplication.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNStateMultiplyComputeIsum2
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a multiplication
 **
 ** This function perform the computations in the state CRY_LN_S_MULTIPLY_CARRY.
 **
 ** \param[out] Result=a pointer to the memory area which should contain the
 ** long number representation of the result of the multiplication
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **  multiplication.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNStateMultiplyCarry
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Result,
  P2VAR(Cry_LNCtxType,  AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a multiplication
 **
 ** This function perform the computations in the state CRY_LN_S_MULTIPLY_EXPORT.
 **
 ** \param[out] Result=a pointer to the memory area which should contain the
 ** long number representation of the result of the multiplication
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **  multiplication.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNStateMultiplyExport
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Result,
  P2VAR(Cry_LNCtxType,  AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

#if (CRY_LN_USE_BARRETT == STD_ON)

/** \brief Helper function for a modulo operation when Barrett reduction is used
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_B_BEGIN
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation is be performed and the location
 ** where the result is stored.
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloBarrettBegin
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation when Barrett reduction is used
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_B_MULTIPLY
 **
 ** \param[in] Barrett A pointer to the long number representation of the Barrett value
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloBarrettMultiply
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Barrett,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation when Barrett reduction is used
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_B_SHIFT
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloBarrettShift
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Helper function for a modulo operation when Barrett reduction is used
 **
 ** This function perform the computations in the state CRY_LN_S_MODULO_B_FINISH
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation is be performed and the location
 ** where the result is stored.
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNModuloBarrettFinish
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

#endif /* #if (CRY_LN_USE_BARRETT == STD_ON) */
#endif /* #if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON) */

#if (CRY_LN_USE_BARRETT == STD_ON)
/**  \brief This function subtracts two numbers
 **
 ** This function subtracts two numbers from each other.
 **
 ** \param[out] Result      A pointer to a memory location which will hold the
 **                         result of the subtraction.
 ** \param[in]  Minuend     A pointer to the minuend of the subtraction.
 ** \param[in]  Subtrahend  A pointer to the subtrahend of the subtraction.
 ** \param[in]  CutOff      Maximal length of the subtrahend.
 **
 **/

 /* Deviation MISRAC2012-2 */
CRY_PRIV_DECL FUNC(void, CRY_CODE) Cry_LNBarretSubtractNumbers
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Minuend,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Subtrahend,
  Cry_LNWordType                                    CutOff
);
#endif

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)
/**  \brief This function squares a number
 **
 ** \param[out] Result      The squared Number.
 ** \param[in]  Number      A number to be squared.
 **
 **/
static FUNC(void, CRY_CODE) Cry_LNSquareComba
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number
);

/** \brief This function calculates the Rho value (equal to (-1 / Modulo[0]) mod (word base))
 **
 ** The implementation of the function assumes that the modulo is odd.
 **
 ** \param[in]   Modulo  A pointer to the modulo used for the reduction.
 ** \param[out]  Rho     A pointer to a memory location which will hold
 **                      the value of the calculated Rho.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNMontgomerySetup
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulo,
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Rho
);

/** \brief This function computes R mod m, in order to convert the input number
 **        into Montgomery domain.
 **
 ** \param[inout]  Result  A pointer to number to be converted; This memory location will
 **                        also hold the conversion result.
 ** \param[in]     Modulo  A pointer to the modulo used for the reduction.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNMontgomeryNormalization
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulo
);

/** \brief This function computes the modular reduction of the number, in the Montgomery domain.
 **        into Montgomery domain.
 **
 ** \param[out]  Remainder  A pointer to a memory location which will hold
 **                         the value of the remainder.
 ** \param[in]   Number     A pointer to the number to be reduced.
 ** \param[in]   Modulo     A pointer to the modulo used for the reduction.
 ** \param[in]   Rho        The Rho value used to calculate the reduction.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNMontgomeryReduction
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Remainder,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulo,
          Cry_LNWordType                            Rho
);
#endif

/** \brief This function subtracts two numbers
 **
 ** This function subtracts two numbers from each other.
 ** The implementation of the function assumes that |Minuend| >= |Subtrahend|.
 **
 ** \param[out] Result      A pointer to a memory location which will hold the
 **                         result of the subtraction.
 ** \param[in]  Minuend     A pointer to the minuend of the subtraction.
 ** \param[in]  Subtrahend  A pointer to the subtrahend of the subtraction.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_LNSubtraction
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Minuend,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Subtrahend
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with internal linkage]===========================*/

#if (CRY_LN_USE_BARRETT == STD_ON)

#define CRY_START_SEC_CODE
#include <MemMap.h>

CRY_PRIV_DEFN FUNC(void, CRY_CODE) Cry_LNBarretSubtractNumbers
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Minuend,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Subtrahend,
  Cry_LNWordType                                    CutOff
)
{
  Cry_LNWordType loopCount;
  Cry_LNWordType borrow = 0U;

  /* We subtract subtrahend from minuend (least significant word to most     */
  /* significant word) until either the subtrahend has been exhausted or     */
  /* "cutOff" words have been done, whichever comes first.
   */
  for (
       loopCount = CRY_LN_LSW_POS;
       (loopCount <= Subtrahend[CRY_LN_LENGTH_POS]) && (loopCount <= CutOff);
       loopCount++
      )
  {
    Cry_LNWordType lowerDifference;
    Cry_LNWordType upperDifference;

    /* Lower half words */
    /* Calculate the difference */
    lowerDifference = ((Cry_LNWordType)Cry_LNLowHalfWord(Minuend[loopCount]) -
                       (Cry_LNWordType)Cry_LNLowHalfWord(Subtrahend[loopCount])) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (lowerDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The lower difference is equal to the lower part of the difference */
    lowerDifference &= CRY_LN_HALFWORD_MAX;

    /* Upper half words */
    /* Calculate the difference */
    upperDifference = ((Cry_LNWordType)Cry_LNHighHalfWord(Minuend[loopCount]) -
                       (Cry_LNWordType)Cry_LNHighHalfWord(Subtrahend[loopCount])) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (upperDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The upper difference is equal to the lower part of the difference */
    upperDifference &= CRY_LN_HALFWORD_MAX;

    /* Concatenate the partial differences */
    Result[loopCount] =
      (Cry_LNWordType)(upperDifference << CRY_LN_HALFWORD_LEN_BITS) | lowerDifference;
  }

  /* Copy the remaining digits */
  for (; loopCount <= Minuend[CRY_LN_LENGTH_POS]; loopCount++)
  {
    Cry_LNWordType lowerDifference;
    Cry_LNWordType upperDifference;


    /* Calculate the difference */
    lowerDifference = (Cry_LNWordType)Cry_LNLowHalfWord(Minuend[loopCount]) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (lowerDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The lower difference is equal to the lower part of the difference */
    lowerDifference &= CRY_LN_HALFWORD_MAX;

    /* Upper half words */
    /* Calculate the difference */
    upperDifference = (Cry_LNWordType)Cry_LNHighHalfWord(Minuend[loopCount]) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (upperDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The upper difference is equal to the lower part of the difference */
    upperDifference &= CRY_LN_HALFWORD_MAX;

    /* Concatenate the partial differences */
    Result[loopCount] =
      (Cry_LNWordType)(upperDifference << CRY_LN_HALFWORD_LEN_BITS) | lowerDifference;
  }

  Result[CRY_LN_LENGTH_POS] = loopCount - (Cry_LNWordType)1U;

  Cry_LNNormalizeNumber(Result);
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_LN_USE_BARRETT == STD_ON) */


/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(uint32, CRY_CODE) Cry_LNBitLengthOfNumber
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number
)
{
   Cry_LNWordType tempWord; /* the most significant word of "Number" */
   Cry_LNWordType length;   /* the length of the number */

   if ( 0U == Number[CRY_LN_LENGTH_POS] )
   {
      length = 0U;
   }
   else
   {
      /* All words of the number except for the most significant word contribute
       * CRY_LN_WORD_LEN_BITS bits to the length of the number.
       */
      length = (Cry_LNWordType)(Number[CRY_LN_LENGTH_POS]-(Cry_LNWordType)1U) *
               (Cry_LNWordType)CRY_LN_WORD_LEN_BITS;

      /* We compute the amount of bits which the most significant word of
       * "Number" contributes to  its length. In each round of this for-loop,
       * the most significant word is shifted one bit to the right and we test
       * it still is non-zero.
       */
      for
      (
          tempWord = Number[Number[CRY_LN_LENGTH_POS]];
          tempWord > (Cry_LNWordType)0U;
          tempWord >>= 1U
      )
      {
         length++;
      }
   }

   return length;
}

FUNC(void, CRY_CODE) Cry_LNNormalizeNumber
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number
)
{
  Cry_LNWordType i; /* loop counter */

  i = Number[CRY_LN_LENGTH_POS];

  while((Number[i] == (Cry_LNWordType)0U) && (i > (Cry_LNWordType)0U))
  {
    i--;
  }

  Number[CRY_LN_LENGTH_POS] = i;
}

FUNC(void, CRY_CODE) Cry_LNMultiplyStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
   CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_BEGIN;
}

FUNC(boolean, CRY_CODE) Cry_LNMultiplyNumbers
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
   boolean Finished = FALSE;

   switch(CtxPtr->LNMultiplyNumbersState)
   {
      case CRY_LN_S_MULTIPLY_BEGIN:
        Cry_LNStateMultiplyBegin
          (
            Result,
            Multiplicand,
            Multiplicator,
            CtxPtr,
            &Finished
          );
         break;

      case CRY_LN_S_MULTIPLY_COMPUTE_OSUM:
         Cry_LNStateMultiplyComputeOsum
           (
             Multiplicand,
             CtxPtr
           );
         break;

      case CRY_LN_S_MULTIPLY_COMPUTE_ISUM1:
         Cry_LNStateMultiplyComputeIsum1
           (
              Multiplicand,
              Multiplicator,
              CtxPtr
           );
         break;

     case CRY_LN_S_MULTIPLY_COMPUTE_ISUM2:
         Cry_LNStateMultiplyComputeIsum2
           (
             Multiplicand,
             Multiplicator,
             CtxPtr
           );
         break;

      case CRY_LN_S_MULTIPLY_CARRY:
         Cry_LNStateMultiplyCarry
           (
             Result,
             CtxPtr
           );
         break;

      case CRY_LN_S_MULTIPLY_EXPORT:
         Cry_LNStateMultiplyExport
           (
             Result,
             CtxPtr
           );
         break;

      case CRY_LN_S_MULTIPLY_FINISH:
         /* We give the result the maximal possible length. */
         Result[CRY_LN_LENGTH_POS] = Multiplicand[CRY_LN_LENGTH_POS] +
                                     Multiplicator[CRY_LN_LENGTH_POS];

         /* We remove leading zeroes from the result. */
         Cry_LNNormalizeNumber(Result);

         Finished = TRUE;
         break;

      /* CHECK: NOPARSE */
      /* Caution: This 'default' is not reachable by processing the function without an externally
                  manipulated context.
                  So it is for defensive programming and MISRA-C:2004.
      */
      default:
         {
           Finished = TRUE;
           break;
         }
      /* CHECK: PARSE */
   }

   return Finished;
#else

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_MEMORY_OPTIMIZED)
  Cry_LNWordType i              = 0U;
  Cry_LNWordType j              = 0U;
  Cry_LNWordType tempResult     = 0U;
  Cry_LNWordType temp           = 0U;
  Cry_LNWordType rl             = 0U;
  Cry_LNWordType carry          = 0U;
  Cry_LNWordType Multiplicand0  = Multiplicand[CRY_LN_LENGTH_POS];
  Cry_LNWordType Multiplicator0 = Multiplicator[CRY_LN_LENGTH_POS];

  TS_PARAM_UNUSED(CtxPtr);

  if (((Cry_LNWordType)0U == Multiplicand0) || ((Cry_LNWordType)0U == Multiplicator0))
  {
    /* One of the inputs was 0, so the result is also 0. */
    Result[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }
  else
  {
    /* The highest word of the result is initialized to 0. This word is
     * not set directly during the following multiplication, but can
     * be reached through overflows during the computation of the lower
     * words.
     */
    Result[Multiplicand0 + Multiplicator0] = (Cry_LNWordType)0U;

    for (i = (Cry_LNWordType)(Multiplicand0 + Multiplicator0) - (Cry_LNWordType)1U;
         i > (Cry_LNWordType)0U;
         i--
        )
    {
      /* We compute the outer sum "\sum_{i=1}^{n+m-1}" from top to bottom. */

      if (i >= Multiplicand0)
      {
        j = (Cry_LNWordType)(i - Multiplicand0) + (Cry_LNWordType)1U;
      }
      else
      {
        j = (Cry_LNWordType)1U;
      }

      tempResult = (Cry_LNWordType)0U;

      /* We compute the inner sum "\sum_{j=\max\{1,i-n+1\}}^{\min\{i,m\}}".*/
      for (; (j <= i) && (j <= Multiplicator0); j++)
      {
        Cry_LNWordType LocalMultiplicand  = Multiplicand[(i - j) + (Cry_LNWordType)1];
        Cry_LNWordType LowMultiplicand    = Cry_LNLowHalfWord(LocalMultiplicand);
        Cry_LNWordType HighMultiplicand   = Cry_LNHighHalfWord(LocalMultiplicand);
        Cry_LNWordType LocalMultiplicator = Multiplicator[j];
        Cry_LNWordType LowMultiplicator   = Cry_LNLowHalfWord(LocalMultiplicator);
        Cry_LNWordType HighMultiplicator  = Cry_LNHighHalfWord(LocalMultiplicator);

        /* Multiply 'Multiplicand[i-j+1]' with 'Multiplicator[j]' and store
         * the lower word of the result in 'rl' and the higher word in
         * 'carry'. 'temp' is a temporary variable.
         */
        rl = HighMultiplicand * LowMultiplicator;

        temp = (LowMultiplicand * HighMultiplicator) + rl;

        if (temp < rl)
        {
          carry = Cry_LNHighHalfWord(temp) |
                  (Cry_LNWordType)((Cry_LNWordType)CRY_LN_HALFWORD_MAX + (Cry_LNWordType)1U);
        }
        else
        {
          carry = Cry_LNHighHalfWord(temp);
        }

        rl = Cry_LNLowHalfWord(temp) << (CRY_LN_WORD_LEN_BITS >> 1U);

        temp = LowMultiplicand * LowMultiplicator;

        /* The low word of the multiplication result is computed. */
        rl += temp;

        if (rl < temp)
        {
          carry++;
        }

        /* The high word of the multiplication result is stored in
         * 'carry'. */
        carry += HighMultiplicand * HighMultiplicator;

        /* The low word of the multiplication result is added to 'tempResult'. */
        tempResult += rl;

        if (tempResult < rl)
        {
          /* There was an overflow. So, we increase the carry by one.
           * This increment cannot overflow since the carry, being the
           * high word of the multiplication of two words, is at least
           * one smaller than the maximal possible value.
           */
          carry++;
        }

        /* We carry the carry upward until it has trickled away. */
        temp = (Cry_LNWordType)1U;

        while (carry != (Cry_LNWordType)0U)
        {
          Result[i + temp] += carry;

          if (Result[i + temp] < carry)
          {
            /* We had another overflow. */
            carry = (Cry_LNWordType)1U;
          }
          else
          {
            /* No overflow, the carry has trickled away. */
            carry = (Cry_LNWordType)0U;
          }

          temp++;
        }
      }

      Result[i] = tempResult;
    }

    /* We give the result the maximal possible length. */
    Result[CRY_LN_LENGTH_POS] = Multiplicand0 + Multiplicator0;

    /* We remove leading zeroes from the result. */
    Cry_LNNormalizeNumber(Result);
  }

  return TRUE;
#else /* COMBA */
#if (CRY_LN_USE_BARRETT == STD_ON)
  Cry_LNWordType localResult[(CRY_MAX_KEY_NUM_LEN_WORDS * 3U) - 1U] = {0U};
#else
  Cry_LNWordType localResult[(CRY_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U] = {0U};
#endif
  Cry_LNWordType i, j, numMultiplications, tx, ty;
  Cry_LNWordType c0 = 0U;
  Cry_LNWordType c1 = 0U;
  Cry_LNWordType c2 = 0U;
  const Cry_LNWordType multiplicandLength  = Multiplicand[CRY_LN_LENGTH_POS];
  const Cry_LNWordType multiplicatorLength = Multiplicator[CRY_LN_LENGTH_POS];
  const Cry_LNWordType prodLen = multiplicandLength + multiplicatorLength;

  TS_PARAM_UNUSED(CtxPtr);

  for (i = 0U; i < prodLen; i++)
  {
    /* Word offset of the Multiplicator */
    ty = CRY_MINIMUM((multiplicatorLength - 1U), i);
    /* Word offset of the Multiplicand */
    tx = i - ty;

    numMultiplications = CRY_MINIMUM((Cry_LNWordType)(multiplicandLength - tx), (ty + 1U));

    /* Forward shift the carry word */
    CRY_COMBA_FORWARD;

    for (j = 0U; j < numMultiplications; j++)
    {
      /* Compute the column product */
      CRY_COMBA_MULADD((Multiplicand[(tx + j) + 1U]), (Multiplicator[(ty - j) + 1U]));
    }

    /* Propagate carry */
    localResult[i + 1U] = c0;
  }

  localResult[CRY_LN_LENGTH_POS] = multiplicandLength + multiplicatorLength;

  Cry_LNNormalizeNumber(localResult);

  Cry_CommonCopy(Result,
                 localResult,
                 (((uint32)localResult[CRY_LN_LENGTH_POS] + (uint32)1U) * (uint32)CRY_LN_WORD_LEN_BYTES)
                );

  return TRUE;

#endif /* #if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_MEMORY_OPTIMIZED) */

#endif /* #if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON) */
}

FUNC(void, CRY_CODE) Cry_LNMultByTwo
(
 P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) A,
 P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) B
)
{
  Cry_LNWordType x, oldused, carry, nextCarry, *src, *dest;

  oldused              = A[CRY_LN_LENGTH_POS];
  A[CRY_LN_LENGTH_POS] = B[CRY_LN_LENGTH_POS];

  /* Aliases for source and destination */
  src  = &B[CRY_LN_LSW_POS];
  dest = &A[CRY_LN_LSW_POS];

  carry = 0U;
  for (x = 0; x < B[CRY_LN_LENGTH_POS]; x++)
  {
    /* Get what will be the *next* carry bit from the
     * MSB of the current digit */
    nextCarry = src[x] >> ((Cry_LNWordType)((CRY_LN_WORD_LEN_BITS) - 1U));

    /* Now shift up this digit, add in the carry [from the previous] */
    dest[x] = ((Cry_LNWordType)((Cry_LNWordType)src[x] << ((Cry_LNWordType)1U)) | carry);

    /* Copy the carry that would be from the source
     * digit into the next iteration */
    carry = nextCarry;
  }

  /* New leading digit? */
  if (carry != 0)
  {
    /* Add B MSB which is always 1 at this point */
    dest[x] = 1U;
    ++(A[CRY_LN_LENGTH_POS]);
  }

  /* Now zero any excess digits on the destination
   * that we didn't write to */
  dest = &(A[A[CRY_LN_LENGTH_POS] + 1U]);

  for (x = A[CRY_LN_LENGTH_POS]; x < oldused; x++)
  {
    dest[x] = 0U;
  }
}

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)

static FUNC(void, CRY_CODE) Cry_LNSquareComba
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number
)
{
  Cry_LNWordType localResult[(CRY_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U] = {0U};
  Cry_LNWordType i, j, tx, ty, numMultiplications;
  Cry_LNWordType c0 = 0U;
  Cry_LNWordType c1 = 0U;
  Cry_LNWordType c2 = 0U;
  const Cry_LNWordType multiplicandLength = Number[CRY_LN_LENGTH_POS];
  const Cry_LNWordType prodLen            = multiplicandLength + multiplicandLength;

  for (i = 0U; i < prodLen; i++)
  {
    ty = CRY_MINIMUM((multiplicandLength - 1U), i);
    tx = (i - ty);

    numMultiplications = CRY_MINIMUM((Cry_LNWordType)(multiplicandLength - tx), (Cry_LNWordType)(ty + 1U));
    numMultiplications = CRY_MINIMUM(numMultiplications, (((ty - tx) + 1U) >> 1U));

    /* Forward shift the carry word */
    CRY_COMBA_FORWARD;

    for (j = 0U; j < numMultiplications; j++)
    {
      /* Double the terms */
      CRY_COMBA_SQRADD2((Number[(tx + j) + 1U]), (Number[(ty - j) + 1U]));
    }

    if ((i & 1U) == 0U)
    {
      Cry_LNWordType offset = (i >> 1U) + (Cry_LNWordType)1U;
      Cry_LNWordType aDp = Number[offset];
      CRY_COMBA_MULADD((aDp), (Number[offset]));
    }

    /* Propagate carry */
    localResult[i + 1U] = c0;
  }

  localResult[CRY_LN_LENGTH_POS] = multiplicandLength + multiplicandLength;

  Cry_LNNormalizeNumber(localResult);

  Cry_CommonCopy(Result,
                 localResult,
                 (((uint32)localResult[CRY_LN_LENGTH_POS] + (uint32)1U) * (uint32)CRY_LN_WORD_LEN_BYTES)
                );
}

static FUNC(void, CRY_CODE) Cry_LNMontgomerySetup
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulo,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Rho
)
{
  Cry_LNWordType x, b;

  /* Fast inversion mod 2**k
   *
   * Based on the fact that
   *
   * XA = 1 (mod 2**n)  =>  (X(2-XA)) A = 1 (mod 2**2n)
   *                    =>  2*X*A - X*X*A*A = 1
   *                    =>  2*(1) - (1)     = 1
   */
  b = Modulo[CRY_LN_LSW_POS];

  x = (Cry_LNWordType)((Cry_LNWordType)((b + 2U) & 4U) << 1U) + b; /* here x*a==1 mod 2**4 */
  x *= (Cry_LNWordType)((Cry_LNWordType)2U - (b * x));             /* here x*a==1 mod 2**8 */
  x *= (Cry_LNWordType)((Cry_LNWordType)2U - (b * x));             /* here x*a==1 mod 2**16 */
  x *= (Cry_LNWordType)((Cry_LNWordType)2U - (b * x));             /* here x*a==1 mod 2**32 */

  /* rho = -1/m mod b */
  *Rho = (Cry_LNWordType)((Cry_LNWordType)(~x) + 1U);
}

static FUNC(void, CRY_CODE) Cry_LNMontgomeryNormalization
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulo
)
{
  uint32 bits;
  Cry_LNWordType x;

  bits = Cry_LNBitLengthOfNumber(Modulo) % CRY_LN_WORD_LEN_BITS;
  if (bits == 0U)
  {
    bits = CRY_LN_WORD_LEN_BITS;
  }

  /* compute A = B^(n-1) * 2^(bits-1) */
  /* The else branch cannot be reached in a real world situation */
  /* CHECK: NOPARSE */
  if (Modulo[CRY_LN_LENGTH_POS] > 1U)
  /* CHECK: PARSE */
  {
    const uint32 Exponent = (uint32)((uint32)((uint32)((uint32)((uint32)Modulo[CRY_LN_LENGTH_POS] - (uint32)1U)) * (uint32)CRY_LN_WORD_LEN_BITS) + (uint32)bits) - (uint32)1U;

    for (x = CRY_LN_LSW_POS; x <= Result[CRY_LN_LENGTH_POS]; x++)
    {
      Result[x] = 0U;
    }

    CRY_MONT_POWOF2(Result, Exponent);
  }
  else
  {
    Result[CRY_LN_LENGTH_POS] = 1U;
    Result[CRY_LN_LSW_POS]    = 1U;
    bits                      = 1U;
  }

  /* Now compute C = A * B mod b */
  for (x = (Cry_LNWordType)(bits - 1U); x < (Cry_LNWordType)CRY_LN_WORD_LEN_BITS; x++)
  {
    /* Find R */
    Cry_LNMultByTwo(Result, Result);

    /* If the result is larger than Modulo reduce it as we only need the quantity */
    /* that, when addded to the input makes it divisible by R without remainder. */
    if (Cry_LNCompareNumbers(Result, Modulo) != CRY_E_SMALLER)
    {
      Cry_LNSubtraction(Result, Result, Modulo);
    }
  }
}

static FUNC(void, CRY_CODE) Cry_LNMontgomeryReduction
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Remainder,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulo,
          Cry_LNWordType                            Rho
)
{
  Cry_LNWordType c[(CRY_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U] = {0U};
  Cry_LNWordType mu, x, y, oldused, carry, *cPtr, *destPtr;
  Cry_LNWordType pa = Modulo[CRY_LN_LENGTH_POS];
  const Cry_LNWordType * modPtr;

  /* Copy the input */
  oldused = Number[CRY_LN_LENGTH_POS];
  for (x = CRY_LN_LSW_POS; x <= oldused; x++)
  {
    c[x - 1U] = Number[x];
  }

  for (x = 0U; x < pa; x++)
  {
    carry = 0U;

    /* Get Mu for this round */
    CRY_MONT_CALCMU;

    cPtr     = &(c[x]);
    modPtr = &(Modulo[1U]);
    y      = 0U;

    for (y = 0U; y < pa; y++)
    {
      CRY_MONT_INNERMUL;
      cPtr = &(cPtr[1U]);
    }

    while (carry != 0U)
    {
      CRY_MONT_PROPCARRY;
      cPtr = &(cPtr[1U]);
    }
  }

  /* Now copy out the result */
  cPtr      = &(c[pa]);
  destPtr = &(Remainder[CRY_LN_LSW_POS]);
  for (x = 0U; x < (pa + 1U); x++)
  {
    destPtr[x] = cPtr[x];
  }

  /* Zero out the remaining words */
  for (; x < oldused; x++)
  {
    destPtr[x] = 0U;
  }

  Remainder[CRY_LN_LENGTH_POS] = pa + 1U;

  Cry_LNNormalizeNumber(Remainder);

  /* if A >= m then A = A - m */
  if (Cry_LNCompareNumbers(Remainder, Modulo) != CRY_E_SMALLER)
  {
    Cry_LNSubtraction(Remainder, Remainder, Modulo);
  }
}
#endif

static FUNC(void, CRY_CODE) Cry_LNSubtraction
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Minuend,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Subtrahend
)
{
#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON)
  Cry_LNDoubleWordType tempDifference;
  Cry_LNWordType loopCount;
  Cry_LNWordType borrow = 0U;

  /* Calculate the differences up to the maximum available number of common digits
   * (Subtrahend is either smaller or equal to Minuend)
   */
  for (loopCount = CRY_LN_LSW_POS; loopCount <= Subtrahend[CRY_LN_LENGTH_POS]; loopCount++)
  {
    /* Calculate the difference */
    tempDifference = ((Cry_LNDoubleWordType)Minuend[loopCount] -
                      (Cry_LNDoubleWordType)Subtrahend[loopCount]) -
                     (Cry_LNDoubleWordType)borrow;

    /* Extract the borrow bit */
    borrow = ((Cry_LNWordType)(tempDifference >> CRY_LN_WORD_LEN_BITS) & 1U);

    /* The result of the column is equal to the lower part of the difference */
    Result[loopCount] = (Cry_LNWordType)tempDifference;
  }

  /* Copy the remaining digits */
  for (; loopCount <= Minuend[CRY_LN_LENGTH_POS]; loopCount++)
  {
    /* Calculate the difference */
    tempDifference = (Cry_LNDoubleWordType)Minuend[loopCount] - (Cry_LNDoubleWordType)borrow;

    /* Extract the borrow bit */
    borrow = ((Cry_LNWordType)(tempDifference >> CRY_LN_WORD_LEN_BITS) & 1U);

    /* The result of the column is equal to the lower part of the difference */
    Result[loopCount] = (Cry_LNWordType)tempDifference;
  }
#else
  Cry_LNWordType loopCount;
  Cry_LNWordType borrow = 0U;

  /* Calculate the differences up to the maximum available number of common digits
   * (Subtrahend is either smaller or equal to Minuend)
   */
  for (loopCount = CRY_LN_LSW_POS; loopCount <= Subtrahend[CRY_LN_LENGTH_POS]; loopCount++)
  {
    Cry_LNWordType lowerDifference;
    Cry_LNWordType upperDifference;

    /* Lower half words */
    /* Calculate the difference */
    lowerDifference = ((Cry_LNWordType)Cry_LNLowHalfWord(Minuend[loopCount]) -
                       (Cry_LNWordType)Cry_LNLowHalfWord(Subtrahend[loopCount])) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (lowerDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The lower difference is equal to the lower part of the difference */
    lowerDifference &= CRY_LN_HALFWORD_MAX;

    /* Upper half words */
    /* Calculate the difference */
    upperDifference = ((Cry_LNWordType)Cry_LNHighHalfWord(Minuend[loopCount]) -
                       (Cry_LNWordType)Cry_LNHighHalfWord(Subtrahend[loopCount])) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (upperDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The upper difference is equal to the lower part of the difference */
    upperDifference &= CRY_LN_HALFWORD_MAX;

    /* Concatenate the partial differences */
    Result[loopCount] =
      (Cry_LNWordType)(upperDifference << CRY_LN_HALFWORD_LEN_BITS) | lowerDifference;
  }

  /* Copy the remaining digits */
  for (; loopCount <= Minuend[CRY_LN_LENGTH_POS]; loopCount++)
  {
    Cry_LNWordType lowerDifference;
    Cry_LNWordType upperDifference;


    /* Calculate the difference */
    lowerDifference = (Cry_LNWordType)Cry_LNLowHalfWord(Minuend[loopCount]) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (lowerDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The lower difference is equal to the lower part of the difference */
    lowerDifference &= CRY_LN_HALFWORD_MAX;

    /* Upper half words */
    /* Calculate the difference */
    upperDifference = (Cry_LNWordType)Cry_LNHighHalfWord(Minuend[loopCount]) -
                      (Cry_LNWordType)borrow;

    /* Extract the borrow bit */
    borrow = (upperDifference >> CRY_LN_HALFWORD_LEN_BITS) & 1U;

    /* The upper difference is equal to the lower part of the difference */
    upperDifference &= CRY_LN_HALFWORD_MAX;

    /* Concatenate the partial differences */
    Result[loopCount] =
      (Cry_LNWordType)((Cry_LNWordType)upperDifference << CRY_LN_HALFWORD_LEN_BITS) |
      lowerDifference;
  }
#endif

  /* Set the length of the result */
  Result[CRY_LN_LENGTH_POS] = loopCount - (Cry_LNWordType)1U;

  Cry_LNNormalizeNumber(Result);
}

FUNC(Cry_ReturnType, CRY_CODE) Cry_LNCompareNumbers
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number1,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number2
)
{
  Cry_LNWordType numberPos; /* the current position in the numbers */
  Cry_ReturnType compare;   /* the result of the comparison */

  /* First, the lengths of the two numbers are compared. If we find a
   * difference here, the comparison is over.
   */
  if (Number1[CRY_LN_LENGTH_POS] > Number2[CRY_LN_LENGTH_POS])
  {
    compare = CRY_E_LARGER;
  }
  else if (Number1[CRY_LN_LENGTH_POS] < Number2[CRY_LN_LENGTH_POS])
  {
    compare = CRY_E_SMALLER;
  }
  else
  {
    /* Both numbers have an identical length. Now, we compare the words of
     * those numbers from most to least significant word.
     */
    compare = CRY_E_EQUAL;

    for
    (
       numberPos = Number1[CRY_LN_LENGTH_POS];
       (numberPos > (Cry_LNWordType)0U) && (CRY_E_EQUAL == compare);
       numberPos--
    )
    {
      if (Number1[numberPos] > Number2[numberPos])
      {
        compare = CRY_E_LARGER;
      }
      else if (Number1[numberPos] < Number2[numberPos])
      {
        compare = CRY_E_SMALLER;
      }
      else
      {
        /* Do nothing. The numbers are identical up to here and this is   */
        /* reflected by the fact that 'compare' is EQUAL at the moment.   */
      }
    }
  }

  return compare;
}

FUNC(void, CRY_CODE) Cry_LNModuloStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
   CtxPtr->LNModuloState = CRY_LN_S_MODULO_BEGIN;
}

FUNC(boolean, CRY_CODE) Cry_LNModulo
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA)    CtxPtr
)
{
#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
  boolean Finished = FALSE;

  switch(CtxPtr->LNModuloState)
  {
     case CRY_LN_S_MODULO_BEGIN:
        Cry_LNModuloBegin(Number,Modulus,CtxPtr,&Finished);
        break;

     case CRY_LN_S_MODULO_SHIFT1:
        Cry_LNModuloShift1(Modulus,CtxPtr);
        break;

     case CRY_LN_S_MODULO_SHIFT2:
        Cry_LNModuloShift2(Number,Modulus,CtxPtr);
        break;

     case CRY_LN_S_MODULO_SUBTRACT1:
        Cry_LNModuloSubtract1(CtxPtr);
        break;

     case CRY_LN_S_MODULO_SUBTRACT2:
        Cry_LNModuloSubtract2(Number,Modulus,CtxPtr);
        break;

     case CRY_LN_S_MODULO_CARRY:
        Cry_LNModuloCarry(Number,CtxPtr);
        break;

     case CRY_LN_S_MODULO_EXPORT:
        Cry_LNModuloExport(CtxPtr);
        break;

     case CRY_LN_S_MODULO_FINISH:
        Cry_LNNormalizeNumber(Number);
        Finished = TRUE;
        break;

     /* CHECK: NOPARSE */
     /* Caution: This 'default' is not reachable by processing the function without an externally
                 manipulated context.
                 So it is for defensive programming and MISRA-C:2004.
     */
     default:
        {
          Finished = TRUE;
          break;
        }
     /* CHECK: PARSE */
  }

  return Finished;
#else
  uint32         lengthOfMod;  /* the length of modulus in bits */
  uint32         lengthOfNum;  /* the length of number in bits */
  Cry_LNWordType wordOfNumber; /* one word of number */

  Cry_LNWordType LengthDifference = 0U;
  Cry_LNWordType wordOfShiftedMod = 0U;
  Cry_LNWordType carry            = 0U;
  Cry_LNWordType posInNum         = 0U;
  Cry_LNWordType posInMod         = 0U;
  Cry_LNWordType shiftWords       = 0U;
  Cry_ReturnType cmpNumMod        = CRY_E_EQUAL;
  Cry_LNWordType Modulus0         = Modulus[CRY_LN_LENGTH_POS];
  uint8_least    shiftBits        = 0U;
  uint8          tempCarry;    /* Used to store whether the carry has to be  */
                               /* set for the next word.                     */

  TS_PARAM_UNUSED(CtxPtr);

  /* We compute the length of number in bits. */
  lengthOfNum   = Cry_LNBitLengthOfNumber(Number);

  /* We compute the length of modulus in bits. */
  lengthOfMod   = Cry_LNBitLengthOfNumber(Modulus);

  /* We only do something if number is at least as long as modulus.
   * Otherwise, result = number mod modulus = number.
   * If the Modulus is 0 -> the result is 0.
   */
  if (lengthOfMod == 0U)
  {
    Number[CRY_LN_LENGTH_POS] = (Cry_LNWordType)lengthOfMod;
  }
  else if (lengthOfMod <= lengthOfNum)
  {
    /* We compute the length difference of number and modulus in bits.
     * We add 1 because we will subtract 1 at the beginning of the
     * do-while-loop.
     */
    LengthDifference =
      (Cry_LNWordType)(lengthOfNum - lengthOfMod) +
      (Cry_LNWordType)1U;

    /* Binary division: We shift modulus an amount of
     * LengthDifference bits to the left. Then we check whether
     * number is at least as large as the shifted modulus. If this is
     * the case we subtract the shifted modulus from number. We decrease
     * LengthDifference by one and repeat this game until
     * LengthDifference is 0.
     * The modulus is not really shifted but the individual words of the
     * shifted modulus are computed when they are needed and stored in
     * wordOfShiftedMod.
     */
    do
    {
      /* At the beginning of each round, we decrease LengthDifference by one */
      (LengthDifference)--;

      /* We extract from LengthDifference how many complete
       * words to shift modulus and how many bits to shift modulus.
       */
      shiftWords = Cry_LNDivByWordLen(LengthDifference);
      shiftBits  = Cry_LNModWordLen(LengthDifference);

      /* The first position of modulus from which to create the shifted
       * modulus is computed. Note that this is one larger than the
       * most significant word of modulus.
       */
      posInMod = Modulus0 + (Cry_LNWordType)1U;

      /* The first position of number which to compare to the shifted
       * modulus is computed.
       */
      posInNum = posInMod + shiftWords;

      /* For each word of modulus, the shifted modulus is computed and
       * compared to the corresponding word of number.
       */
      do
      {
        /* We assemble the current word of the shifted modulus from the
         * words modulus[posInMod] and modulus[posInMod - 1].
         */

        /* We test whether the current position in modulus is an allowed
         * position.
         */
        if(posInMod <= Modulus0)
        {
          /* The current position in modulus is allowed. We take some
           * bits from the word of modulus at that position.
           */
          wordOfShiftedMod = Modulus[posInMod] << shiftBits;
        }
        else
        {
          /* The current position in modulus is too high. We are at a
           * "leading zero". So, all the bits which go into
           * wordOfShiftedMod are zero.
           */
          wordOfShiftedMod = (Cry_LNWordType)0U;
        }

        /* The needed bits from modulus[posInMod - 1] are incorporated
         * into wordOfShiftedMod. If we shift the modulus by complete
         * words (which means "shiftBits == 0") or if posInMod
         * is the lowest possible position (which means posInMod == 1)
         * no bits from modulus[posInMod - 1] are needed.
         */
        if ( (shiftBits != (uint8)0U) && (posInMod > (Cry_LNWordType)1U) )
        {
          wordOfShiftedMod |=
            (Cry_LNWordType)
            (
              Modulus[posInMod - (Cry_LNWordType)1] >>
                (uint8)((uint8)CRY_LN_WORD_LEN_BITS - shiftBits)
            );
        }

        /* We compute the word of number which to compare to the word
         * of the shifted modulus. This is normally simply
         * number[posInNum], but the position can be too high which
         * means that we are at a "leading zero" of number.
         */
        if(posInNum > Number[CRY_LN_LENGTH_POS])
        {
          wordOfNumber = (Cry_LNWordType)0U;
        }
        else
        {
          wordOfNumber = Number[posInNum];
        }

        /* Now, we compare the word of the shifted modulus to the current
         * word of number.
         */
        if(wordOfShiftedMod == wordOfNumber)
        {
          cmpNumMod = CRY_E_EQUAL;
        }
        else if (wordOfShiftedMod > wordOfNumber)
        {
          cmpNumMod = CRY_E_SMALLER;
        }
        else
        {
          cmpNumMod = CRY_E_LARGER;
        }

        /* The positions are decreased by 1. */
        posInMod--;
        posInNum--;
      }
      while((CRY_E_EQUAL == cmpNumMod) && (posInMod > (Cry_LNWordType)0U));


      /* If number is at least as large as the shifted modulus, we
       * subtract modulus from number.
       */
      if(cmpNumMod != CRY_E_SMALLER)
      {
        wordOfShiftedMod = (Cry_LNWordType)0U;

        carry = (Cry_LNWordType)0U;

        /* When subtracting the shifted modulus from number we can
         * skip the least significant words of number because the
         * shifted modulus is 0, there. We compute the least
         * significant word of number which is affected by the
         * subtraction.
         */
        posInNum = (Cry_LNWordType)1U + shiftWords;

        /* We go through every word of the shifted modulus.    */
        for
        (
          posInMod = (Cry_LNWordType)1U;
          posInMod <= Modulus0;
          posInMod++
        )
        {
          Cry_LNWordType tempNumber = Number[posInNum];
          Cry_LNWordType tempModulus = Modulus[posInMod];
          tempCarry = (uint8)0U;

          wordOfShiftedMod |=
            (Cry_LNWordType)(tempModulus << shiftBits);

          /* We test whether a carry forms at this position. This
           * happens when "wordOfShiftedMod + carry >
           * number[posInNum]".  Since we cannot test this condition
           * directly because of possible overflows we use a more complicated
           * looking test which actually does exactly what we want.
           */
          if(
              (wordOfShiftedMod > tempNumber)    ||
              (
                (wordOfShiftedMod >= tempNumber) &&
                (carry > (Cry_LNWordType)0)
              )
            )
          {
            tempCarry = (uint8)1U;
          }

          /* We subtract "wordOfShiftedMod" and "carry" from
           * the number.
           */
          Number[posInNum] = tempNumber - (wordOfShiftedMod + carry);

          carry = (Cry_LNWordType)tempCarry;

          if(shiftBits == (uint8)0U)
          {
            wordOfShiftedMod = (Cry_LNWordType)0U;
          }
          else
          {
            wordOfShiftedMod = tempModulus >>
                     (uint8)((uint8)CRY_LN_WORD_LEN_BITS - shiftBits);
          }

          posInNum++;
        }

        /* Now we have to deal with leftover carries and a possible last
         * word of the shifted modulus. Since the carry is at most one
         * and wordOfShiftedMod is at least one bit shorter than the
         * largest possible word (making it at most half as large), we
         * can add both numbers in "carry" without overflow.
         */
        carry += wordOfShiftedMod;

        /* Now we deal with the leftover carries. */
        while(carry != (Cry_LNWordType)0U)
        {
           /* CHECK: NOPARSE */
           /* Defensive Programming - "else" branch is unreachable code. */
           if(Number[posInNum] >= carry)
            /* CHECK: PARSE */
           {
              /* The carry has trickled away. */
              Number[posInNum] -= carry;
              carry             = (Cry_LNWordType)0U;
           }
           else
           {
              /* We have to take the carry one word upwards. */
              Number[posInNum] -= carry;
              carry             = (Cry_LNWordType)1U;
           }
           posInNum++;
        }
      }

    } while ((LengthDifference) > (Cry_LNWordType)0U);
  }
  else
  {
    /* for MISRA-C */
  }

  Cry_LNNormalizeNumber(Number);

  return TRUE;
#endif
}

#if (CRY_LN_USE_BARRETT == STD_ON)

FUNC(void, CRY_CODE) Cry_LNModuloBarrettStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
   CtxPtr->LNModuloBarrettState = CRY_LN_S_MODULO_BEGIN;
}

FUNC(boolean, CRY_CODE) Cry_LNModuloBarrett
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Barrett,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
  boolean Finished = FALSE;

  switch(CtxPtr->LNModuloBarrettState)
  {
      case CRY_LN_S_MODULO_B_BEGIN:
        Cry_LNModuloBarrettBegin(Number,Modulus,CtxPtr);
        break;

      case CRY_LN_S_MODULO_B_MULTIPLY:
        Cry_LNModuloBarrettMultiply(Barrett,CtxPtr);
        break;

      case CRY_LN_S_MODULO_B_SHIFT:
         Cry_LNModuloBarrettShift(Modulus,CtxPtr);
        break;

      case CRY_LN_S_MODULO_B_FINISH:
         Cry_LNModuloBarrettFinish(Number,Modulus,CtxPtr);
         Finished = TRUE;
        break;

      /* CHECK: NOPARSE */
      /* Caution: This 'default' is not reachable by processing the function without an externally
                  manipulated context.
                  So it is for defensive programming and MISRA-C:2004.
      */
      default:
        {
          Finished = TRUE;
          break;
        }
      /* CHECK: PARSE */

    }

  return Finished;
#else
  Cry_LNWordType loopCount;
  Cry_LNWordType * tempNumber;

  TS_PARAM_UNUSED(CtxPtr);

  /* The input 'Number' is needed twice during the computation, but once it
   * is shifted 'Modulus[CRY_LN_LENGTH_POS]-1' words to the right and once it is cropped to
   * the last 'Modulus[CRY_LN_LENGTH_POS]+1' words. This means that on the first occasion
   * all the words of 'Number' except for the last 'Modulus[CRY_LN_LENGTH_POS]-1' are needed
   * and on the second occasion only the last 'Modulus[CRY_LN_LENGTH_POS]+1' words of
   * 'Number' are needed. So, with the exception of a two word overlap, two
   * distinct parts of 'Number' are needed during the computation. So, we
   * begin by splitting 'Number' into the two distinct parts with a little
   * shifting. Then we have both parts at our disposal.
   */

  /* The more significant part of 'Number' is shifted 3 blocks to the left.  */
  for (loopCount = Number[CRY_LN_LENGTH_POS]; loopCount >= Modulus[CRY_LN_LENGTH_POS]; loopCount--)
  {
    Number[loopCount + (Cry_LNWordType)3U] = Number[loopCount];
  }

  /* The length of the two parts is computed. The left part starts at
   * Number[Modulus[CRY_LN_LENGTH_POS]+2].
   */
  if (Modulus[CRY_LN_LENGTH_POS] > Number[CRY_LN_LENGTH_POS])
  {
    /* The Number is so small that the right shifted part is zero and the
     * cropped part is the Number itself.
     */
    Number[Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U] = (Cry_LNWordType)0U;
  }
  else
  {
    /* The length of the right shifted part. */
    Number[Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U] =
     (Cry_LNWordType)(Number[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U) - Modulus[CRY_LN_LENGTH_POS];

    /* The length of the cropped part. */
    Number[CRY_LN_LENGTH_POS] = Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U;
  }

  /* tempNumber is set to the start of the newly created Number. */
  tempNumber = &Number[Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U];

  /* "tempNumber" now contains the value of "Number" shifted "Modulus[CRY_LN_LENGTH_POS]-1"
   * words to the right, while "Number" itself now contains the old value of
   * Number cropped to the last "Modulus[CRY_LN_LENGTH_POS]+1" words. So, in the notation of
   * Menezes et al., 'tempNumber' contains q1, while 'Number' contains r1.
   */

   /* q2 = q1 * mu. q2 is stored in "tempNumber". */
  (void)Cry_LNMultiplyNumbers(tempNumber, tempNumber, Barrett, CtxPtr);

  /* q3 = q2 / b**(k+1). This is a right shift by 'Modulus[CRY_LN_LENGTH_POS]+1' words. q3
   * is stored in "tempNumber".
   */
  if (Modulus[CRY_LN_LENGTH_POS] >= tempNumber[CRY_LN_LENGTH_POS])
  {
    /* 'tempNumber' is so small that the right shift makes it 0. */
    tempNumber[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }
  else
  {
    for (
          loopCount = (Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U);
          loopCount <= tempNumber[CRY_LN_LENGTH_POS];
          loopCount++
        )
    {
      tempNumber[loopCount - (Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U)] =
                                                                              tempNumber[loopCount];
    }

    tempNumber[CRY_LN_LENGTH_POS] -=
                                  (Cry_LNWordType)(Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U);
  }


  /* r3 = q3 * m. This step is not in the book. There, it is combined with
   * the next step and we go directly to r2 = (q3 * m) mod b**(k+1). r3 is
   * stored in tempNumber.
   */
  (void)Cry_LNMultiplyNumbers(tempNumber, tempNumber, Modulus, CtxPtr);

  /* r2 = r3 mod b**(k+1). r2 is stored in tempNumber. */
  if((Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U) < tempNumber[CRY_LN_LENGTH_POS])
  {
    tempNumber[CRY_LN_LENGTH_POS] = Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U;
  }

  /* We now compute the following two steps of the algorithm in one go:
   *   3. r = r1 - r2.
   *   4. if r < 0 then r = r + b**(k+1).
   * r is stored in "Number".
   */
  Cry_LNBarretSubtractNumbers
  (
     Number,
     Number,
     tempNumber,
     Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U
  );

  /* We know that the following while loop can never be repeated more than
   * twice with the correct Barrett value. So, we count the repetitions.
   */
  loopCount = (Cry_LNWordType)0U;

  /* while r > m do r = r - m. r is stored in Number. After this while-loop
   * has finished, the modulo computation is finished and the result is in
   * "Number".
   */
  while
  (
     (CRY_E_SMALLER != Cry_LNCompareNumbers(Number,Modulus)) &&
     (loopCount      < (Cry_LNWordType)4U                  )
  )
  {
    Cry_LNBarretSubtractNumbers
    (
       Number,
       Number,
       Modulus,
       CRY_LN_WORD_MAX
    );

     loopCount++;
  }

  /* Did we do too many loop repetitions? */
  if ((Cry_LNWordType)4U == loopCount)
  {
    /* Something went wrong. Probably an incorrect Barrett value. We set
     * the result to 0.
     */
    Number[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }

  return TRUE;
#endif
}

#endif /* (CRY_LN_USE_BARRETT == STD_ON) */

FUNC(Std_ReturnType, CRY_CODE) Cry_LNBEByteArrayToNumber
(
  P2CONST(uint8,        AUTOMATIC, CRY_APPL_DATA) Array,
  uint32                                          ArrayLength,
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  Cry_LNWordType                                  NumberLength
)
{
  Cry_LNWordType numberPos; /* the position in 'number' */
  Cry_LNWordType wordPos;   /* the byte position in the current word of 'number'*/
  uint32         arrayPos;  /* the position in the byte array */
  Std_ReturnType RetVal = E_OK;

  if ((uint32)0U != ArrayLength)
  {
    if (NumberLength < (Cry_LNNumberLen(ArrayLength) + 1U))
    {
      RetVal = E_NOT_OK;
    }
    else
    {
      /* We cycle through all of the words of the resulting number */
      for (numberPos = (Cry_LNWordType)1U; numberPos <= Cry_LNNumberLen(ArrayLength); numberPos++)
      {
        /* The current word of number is initialized to '0'. */
        Number[numberPos] = (Cry_LNWordType)0U;

        /* "CRY_LN_WORD_LEN_BYTES" bytes of the array are combined to make up
         * the current word of the number.
         */
        for (wordPos = (Cry_LNWordType)0U;
             wordPos < (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES;
             wordPos++
            )
        {
          /* We compute the current position in 'array'. */
          arrayPos = (uint32)CRY_LN_WORD_LEN_BYTES;
          arrayPos *= (uint32)((uint32)numberPos - (Cry_LNWordType)1U);
          arrayPos += (uint32)wordPos;
          arrayPos = (uint32)((uint32)(ArrayLength - arrayPos) - (uint32)1U);

          if (arrayPos < ArrayLength)
          {
            /* If we are not over the edge of 'array', we incorporate the
             * current byte of 'array' into the current word of the number.
             */
            Number[numberPos] |= (Cry_LNWordType)((Cry_LNWordType)Array[arrayPos]                 <<
                                                  (Cry_LNWordType)((Cry_LNWordType)wordPos << 3U)
                                                 );
          }
        }
      }

      Number[CRY_LN_LENGTH_POS] = Cry_LNNumberLen(ArrayLength);

      Cry_LNNormalizeNumber(Number);
    }
  }
  else
  {
    /* The length of 'array' is '0', so the resulting number is also '0'. */
    Number[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }

  return RetVal;
}


FUNC(Std_ReturnType, CRY_CODE) Cry_LNNumberToBEByteArray
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2VAR(uint8,            AUTOMATIC, CRY_APPL_DATA) Array,
  P2VAR(uint32,           AUTOMATIC, CRY_APPL_DATA) ArrayLengthPtr
)
{
  Cry_LNWordType numberPos; /* the position in 'number' */
  Cry_LNWordType wordPos;   /* the byte position in the current word of 'number'*/
  Cry_LNWordType arrayPos;  /* the position in the byte array */
  Std_ReturnType RetVal = E_OK;

  if (((*ArrayLengthPtr) / CRY_LN_WORD_LEN_BYTES) < Number[CRY_LN_LENGTH_POS])
  {
    RetVal = E_NOT_OK;
  }
  else
  {
    /* We cycle through all the words of 'number'. */
    for (numberPos = (Cry_LNWordType)CRY_LN_LSW_POS;
         numberPos <= Number[CRY_LN_LENGTH_POS];
         numberPos++
        )
    {
      /* Begin computing the index of the byte which will be updated. */
      arrayPos  = Number[CRY_LN_LENGTH_POS];
      arrayPos -= numberPos;
      arrayPos += (Cry_LNWordType)1U;
      arrayPos *= (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES;

      /* Each word of 'number' is split into 'CRY_LN_WORD_LEN_BYTES' bytes of 'array'. */
      for (wordPos = (Cry_LNWordType)0U; wordPos < (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES; wordPos++)
      {
        /* Finish computing the index of the byte which will be updated. */
        arrayPos -= (Cry_LNWordType)1U;

        /* The current byte of 'array' is computed from the current word of 'number'. */
        Array[arrayPos] = (uint8)(Number[numberPos] >> (uint8)((uint8)wordPos << 3U));
      }
    }

    /* Return the correct length of the byte array. */
    *ArrayLengthPtr = (uint16)(Number[CRY_LN_LENGTH_POS] * (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES);
  }

  return RetVal;
}

FUNC(Std_ReturnType, CRY_CODE) Cry_LNNumberToLEByteArray
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2VAR(uint8,            AUTOMATIC, CRY_APPL_DATA) Array,
  P2VAR(uint32,           AUTOMATIC, CRY_APPL_DATA) ArrayLengthPtr
)
{
  Cry_LNWordType NumberPos; /* the position in 'Number' */
  Cry_LNWordType wordPos;   /* byte position in the current word of 'Number'*/
  Cry_LNWordType ArrayPos;  /* the position in the byte Array */
  Std_ReturnType RetVal = E_OK;

  if (((*ArrayLengthPtr) / CRY_LN_WORD_LEN_BYTES) < Number[CRY_LN_LENGTH_POS])
  {
    RetVal = E_NOT_OK;
  }
  else
  {
    /* we cycle through all the words of 'Number'. */
    for (NumberPos = (Cry_LNWordType)CRY_LN_LSW_POS;
         NumberPos <= Number[CRY_LN_LENGTH_POS];
         NumberPos++
        )
    {
      /* Begin computing the index of the byte which will be updated. */
      ArrayPos = NumberPos;
      ArrayPos -= (Cry_LNWordType)1U;
      ArrayPos *= (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES;

      /* Each word of 'Number' is split into 'CRY_LN_WORD_LEN_BYTES' bytes of 'Array'. */
      for (wordPos = (Cry_LNWordType)0U; wordPos < (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES; wordPos++)
      {
        /* The current byte of 'Array' is computed from the current word of 'Number'.  */
        Array[ArrayPos] =
          (uint8)(Number[NumberPos] >> (Cry_LNWordType)((Cry_LNWordType)wordPos << 3U));

        /* Finish computing the index of the byte which will be updated. */
        ArrayPos += (Cry_LNWordType)1;
      }
    }

    /* Return the correct length of the byte array. */
    *ArrayLengthPtr = (uint16)(Number[CRY_LN_LENGTH_POS] * (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES);
  }

  return RetVal;
}

FUNC(void, CRY_CODE) Cry_LNAdditionModular
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Sum,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend1,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend2,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus
)
{
  Cry_LNWordType i, carry;
  Cry_ReturnType result;

  carry = Cry_LNAddition(Sum, Addend1, Addend2);

  for (i = (Sum[CRY_LN_LENGTH_POS] + 1U); i <= Modulus[CRY_LN_LENGTH_POS]; i++)
  {
    Sum[i] = 0U;
  }

  result = Cry_LNCompareNumbers(Sum, Modulus);

  /* if the carry is 1 and the sum is smaller then the modulus, the carry can
   * be added in the highest position
   */
  if ((Sum[CRY_LN_LENGTH_POS] < Modulus[CRY_LN_LENGTH_POS]) && (1U == carry))
  {
    Sum[CRY_LN_LENGTH_POS]++;
    Sum[Sum[CRY_LN_LENGTH_POS]] = 1U;
  }
  /* else the carry is set to one. Then the sum length equals the modulus
   * length and it is necessary to subtract. Also, if the length of the sum
   * equals the modulus and the most significant position is larger than the
   * modulus a subtraction is needed
   */
  else if ((1U == carry) || (result != CRY_E_SMALLER))
  {
    Cry_LNSubtraction(Sum, Sum, Modulus);
  }
  else
  {
    /* Nothing to do (MISRA) */
  }

  Cry_LNNormalizeNumber(Sum);
}

FUNC(void, CRY_CODE) Cry_LNSubtractionModular
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Difference,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Minuend,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Subtrahend,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus
)
{
  Cry_LNWordType i, tmp, tmp2;
  uint8          carry, borrow;

  borrow = 0U;

  for (i = CRY_LN_LSW_POS; i <= Modulus[CRY_LN_LENGTH_POS]; i++)
  {
    tmp           = (i > Minuend[CRY_LN_LENGTH_POS]) ? (Cry_LNWordType)0 : Minuend[i];
    tmp2          = (i > Subtrahend[CRY_LN_LENGTH_POS]) ? (Cry_LNWordType)0 : Subtrahend[i];
    Difference[i] = (tmp - tmp2) - borrow;

    if (Difference[i] >= tmp)
    {
      if ((0U != tmp2) || (0U != borrow))
      {
        borrow = 1U;
      }
    }
    else
    {
      borrow = 0U;
    }
  }

  Difference[CRY_LN_LENGTH_POS] = Modulus[CRY_LN_LENGTH_POS];

  /* if the number is 'negative', which equals a remaining borrow, the modulus must be added */
  if (1U == borrow)
  {
    carry = 0U;

    for (i = 1U; i <= Modulus[CRY_LN_LENGTH_POS]; i++)
    {
      tmp           = Difference[i];
      Difference[i] = (tmp + carry) + Modulus[i];

      if ((Difference[i] <= tmp) && (Difference[i] <= Modulus[i]))
      {
        /* In theory the false branch cannot be reached as tmp != 0 and the modulus be 0.
         * Nevertheless, I prefer to leave it as is for completeness. */
        /* CHECK: NOPARSE */
        if ((0U != tmp) || (0U != Modulus[i]))
        {
          carry = 1U;
        }
        /* CHECK: PARSE */
      }
      else
      {
        carry = 0U;
      }
    }
  }

  Cry_LNNormalizeNumber(Difference);
}

FUNC(void, CRY_CODE) Cry_LNDivByTwo
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Value,
   Cry_LNWordType                                  Overflow
)
{
  Cry_LNWordType i, diffTmpVal1, diffTmpVal2;

  diffTmpVal2 = Overflow;

  for (i = Value[CRY_LN_LENGTH_POS]; i > 0U; i--)
  {
    diffTmpVal1 = Value[i] & 1U;
    Value[i]    = Value[i] >> 1U;
    Value[i] =
      Value[i] | (Cry_LNWordType)((Cry_LNWordType)diffTmpVal2 << (CRY_LN_WORD_LEN_BITS - 1U));
    diffTmpVal2 = diffTmpVal1;
   }

   Cry_LNNormalizeNumber(Value);
}

FUNC(Cry_LNWordType, CRY_CODE) Cry_LNAddition
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Sum,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend1,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend2
)
{
#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_MEMORY_OPTIMIZED)
  Cry_LNWordType i;
  Cry_LNWordType length;
  Cry_LNWordType tmp;
  Cry_LNWordType tmp2;
  uint8          carry;

  /* Get the length of the largest operand */
  length = (Addend1[CRY_LN_LENGTH_POS] > Addend2[CRY_LN_LENGTH_POS]) ? Addend1[CRY_LN_LENGTH_POS] :
                                                                       Addend2[CRY_LN_LENGTH_POS];
  carry = 0U;

  /* Loop over all the digits */
  for (i = CRY_LN_LSW_POS; i <= length; i++)
  {
    /* Check if the operands have more digits, otherwise return 0 */
    tmp    = (i > Addend1[CRY_LN_LENGTH_POS]) ? (Cry_LNWordType)0U : Addend1[i];
    tmp2   = (i > Addend2[CRY_LN_LENGTH_POS]) ? (Cry_LNWordType)0U : Addend2[i];
    Sum[i] = tmp + tmp2 + carry;

    if ((Sum[i] <= tmp) && (Sum[i] <= tmp2))
    {
      if ((0U != tmp) || (0U != tmp2))
      {
        carry = 1U;
      }
    }
    else
    {
      carry = 0U;
    }
  }

  Sum[CRY_LN_LENGTH_POS] = length;
#else /* (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED) */

#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_OFF)
  Cry_LNWordType        loopCount;
  Cry_LNWordType        minLength;
  Cry_LNWordType        maxLength;
  Cry_LNWordType        carry = 0U;
  const Cry_LNWordType *largestOperand;

  /* Find the larger of the two operands */
  if (Addend1[CRY_LN_LENGTH_POS] > Addend2[CRY_LN_LENGTH_POS])
  {
    minLength      = Addend2[CRY_LN_LENGTH_POS];
    maxLength      = Addend1[CRY_LN_LENGTH_POS];
    largestOperand = Addend1;
  }
  else
  {
    minLength      = Addend1[CRY_LN_LENGTH_POS];
    maxLength      = Addend2[CRY_LN_LENGTH_POS];
    largestOperand = Addend2;
  }

  /* Calculate the sums up to the maximum available number of common digits */
  for (loopCount = CRY_LN_LSW_POS; loopCount <= minLength; loopCount++)
  {
    Cry_LNWordType lowerSum;
    Cry_LNWordType upperSum;

    /* Calculate the lower sum */
    lowerSum = ((Cry_LNWordType)Cry_LNLowHalfWord(Addend1[loopCount]) +
                (Cry_LNWordType)Cry_LNLowHalfWord(Addend2[loopCount])) +
               (Cry_LNWordType)carry;

    /* Extract the carry bit */
    carry = (Cry_LNWordType)(lowerSum >> CRY_LN_HALFWORD_LEN_BITS);

    /* The lower sum is equal to the lower half of the difference */
    lowerSum &= CRY_LN_HALFWORD_MAX;

    /* Calculate the upper sum */
    upperSum = ((Cry_LNWordType)Cry_LNHighHalfWord(Addend1[loopCount]) +
                (Cry_LNWordType)Cry_LNHighHalfWord(Addend2[loopCount])) +
               (Cry_LNWordType)carry;

    /* Extract the carry bit */
    carry = (Cry_LNWordType)(upperSum >> CRY_LN_HALFWORD_LEN_BITS);

    /* The upper sum is equal to the lower half of the difference */
    upperSum &= CRY_LN_HALFWORD_MAX;

    /* Concatenate the partial sums */
    Sum[loopCount] =
      ((Cry_LNWordType)((Cry_LNWordType)upperSum << CRY_LN_HALFWORD_LEN_BITS) | lowerSum);
  }

  /* Copy the remaining digits */
  for (; loopCount <= maxLength; loopCount++)
  {
    Cry_LNWordType lowerSum;
    Cry_LNWordType upperSum;

    /* Calculate the lower sum */
    lowerSum = (Cry_LNWordType)Cry_LNLowHalfWord(largestOperand[loopCount]) + (Cry_LNWordType)carry;

    /* Extract the carry bit */
    carry = lowerSum >> CRY_LN_HALFWORD_LEN_BITS;

    /* The lower sum is equal to the lower half of the difference */
    lowerSum &= CRY_LN_HALFWORD_MAX;

    /* Calculate the upper sum */
    upperSum =
      (Cry_LNWordType)Cry_LNHighHalfWord(largestOperand[loopCount]) + (Cry_LNWordType)carry;

    /* Extract the carry bit */
    carry = upperSum >> CRY_LN_HALFWORD_LEN_BITS;

    /* The upper sum is equal to the lower half of the difference */
    upperSum &= CRY_LN_HALFWORD_MAX;

    /* Concatenate the partial sums */
    Sum[loopCount] =
      ((Cry_LNWordType)((Cry_LNWordType)upperSum << CRY_LN_HALFWORD_LEN_BITS) | lowerSum);
  }

  Sum[CRY_LN_LENGTH_POS] = maxLength;
#else /* (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON) */

  Cry_LNDoubleWordType  tempSum;
  Cry_LNWordType        loopCount, minLength, maxLength, carry = 0U;
  const Cry_LNWordType *largestOperand;

  /* Find the larger of the two operands */
  if (Addend1[CRY_LN_LENGTH_POS] > Addend2[CRY_LN_LENGTH_POS])
  {
    minLength      = Addend2[CRY_LN_LENGTH_POS];
    maxLength      = Addend1[CRY_LN_LENGTH_POS];
    largestOperand = Addend1;
  }
  else
  {
    minLength      = Addend1[CRY_LN_LENGTH_POS];
    maxLength      = Addend2[CRY_LN_LENGTH_POS];
    largestOperand = Addend2;
  }

  /* Calculate the sums up to the maximum available number of common digits */
  for (loopCount = CRY_LN_LSW_POS; loopCount <= minLength; loopCount++)
  {
    /* Calculate the sum */
    tempSum =
      ((Cry_LNDoubleWordType)Addend1[loopCount] + (Cry_LNDoubleWordType)Addend2[loopCount]) +
      (Cry_LNDoubleWordType)carry;

    /* The result of the column is equal to the lower part of the difference */
    Sum[loopCount] = (Cry_LNWordType)tempSum;

    /* Extract the carry bit */
    carry = (Cry_LNWordType)((Cry_LNDoubleWordType)tempSum >> CRY_LN_WORD_LEN_BITS);
  }

  /* Copy the remaining digits */
  for (; loopCount <= maxLength; loopCount++)
  {
    /* Calculate the sum */
    tempSum = (Cry_LNDoubleWordType)largestOperand[loopCount] + (Cry_LNDoubleWordType)carry;

    /* The result of the column is equal to the lower part of the difference */
    Sum[loopCount] = (Cry_LNWordType)tempSum;

    /* Extract the carry bit */
    carry = (Cry_LNWordType)((Cry_LNDoubleWordType)tempSum >> CRY_LN_WORD_LEN_BITS);
  }

  Sum[CRY_LN_LENGTH_POS]     = maxLength;

#endif /* (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON) */
#endif /* (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED) */

  return carry;
}


FUNC(void, CRY_CODE) Cry_LNInversionStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
   CtxPtr->LNInversionState = CRY_LN_S_INVERSION_START;
}

FUNC(boolean, CRY_CODE) Cry_LNInversion
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) InvValue,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Value,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) tmp1Value,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) tmp2Value,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) tmp3Value,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
  boolean        Finished = FALSE;
  Cry_LNWordType addResult, i;

  switch (CtxPtr->LNInversionState)
  {
    case CRY_LN_S_INVERSION_START:
      /* u = a */
      for (i = 0U; i <= Value[CRY_LN_LENGTH_POS]; i++)
      {
        tmp1Value[i] = Value[i];
      }
      /* v = p */
      for (i = 0U; i <= Modulus[CRY_LN_LENGTH_POS]; i++)
      {
        tmp2Value[i] = Modulus[i];
      }

      /* x1 = 1 */
      tmp3Value[CRY_LN_LENGTH_POS] = 1U;
      tmp3Value[CRY_LN_LSW_POS]    = 1U;

      /* x2 = 0 */
      InvValue[CRY_LN_LENGTH_POS] = 0U;
      InvValue[CRY_LN_LSW_POS]    = 0U;

      CtxPtr->LNInversionState = CRY_LN_S_INVERSION_LOOP_OUTER;
      break;

    case CRY_LN_S_INVERSION_LOOP_OUTER:
      /* while (u != 1 and v != 1) */
      if ((!((1U == tmp1Value[CRY_LN_LENGTH_POS]) && (1U == tmp1Value[CRY_LN_LSW_POS])) &&
           !((1U == tmp2Value[CRY_LN_LENGTH_POS]) && (1U == tmp2Value[CRY_LN_LSW_POS]))) &&
          (0U != tmp1Value[CRY_LN_LENGTH_POS])
         )
      {
        CtxPtr->LNInversionState = CRY_LN_S_INVERSION_LOOP_INNER_1;
      }
      else
      {
        /* if (u == 1) */
        if ((1U == tmp1Value[CRY_LN_LENGTH_POS]) && (1U == tmp1Value[CRY_LN_LSW_POS]))
        {
          /* return (x1 mod p) */
          for (i = 0U; i <= tmp3Value[CRY_LN_LENGTH_POS]; i++)
          {
            InvValue[i] = tmp3Value[i];
          }
        }

        Cry_LNModuloStart(CtxPtr);
        CtxPtr->LNInversionState = CRY_LN_S_INVERSION_MODULO;
      }
      break;

    case CRY_LN_S_INVERSION_LOOP_INNER_1:
      /*  while u is even */
      if (0U == (tmp1Value[CRY_LN_LSW_POS] & 1U))
      {
        /* u = u/2 */
        Cry_LNDivByTwo(tmp1Value, 0U);

        /* if x1 is even */
        if (0U == (tmp3Value[CRY_LN_LSW_POS] & 1U))
        {
          /* x1 = x1 / 2 */
          Cry_LNDivByTwo(tmp3Value, 0U);
        }
        else
        {
          /* x1 = (x1 + p) / 2 */
          addResult = Cry_LNAddition(tmp3Value, tmp3Value, Modulus);
          Cry_LNDivByTwo(tmp3Value, addResult);
        }
      }
      else
      {
        CtxPtr->LNInversionState = CRY_LN_S_INVERSION_LOOP_INNER_2;
      }
      break;

    case CRY_LN_S_INVERSION_LOOP_INNER_2:
      /* while v is even */
      if (0U == (tmp2Value[CRY_LN_LSW_POS] & 1U))
      {
        /* v = v / 2 */
        Cry_LNDivByTwo(tmp2Value, 0U);

        /* if x2 is even */
        if (0U == (InvValue[CRY_LN_LSW_POS] & 1U))
        {
          /* x2 = x2 / 2 */
          Cry_LNDivByTwo(InvValue, 0U);
        }
        else
        {
          /* x2 = (x2 + p) / 2 */
          addResult = Cry_LNAddition(InvValue, InvValue, Modulus);
          Cry_LNDivByTwo(InvValue, addResult);
        }
      }
      else
      {
        CtxPtr->LNInversionState = CRY_LN_S_INVERSION_SUBTRACT;
      }
      break;

    case CRY_LN_S_INVERSION_SUBTRACT:
      /* if (u >= v) */
      /* Deviation MISRAC2012-1 */
      if ((CRY_E_LARGER == Cry_LNCompareNumbers(tmp1Value, tmp2Value)) ||
          (CRY_E_EQUAL  == Cry_LNCompareNumbers(tmp1Value, tmp2Value))
         )
      {
        /* u = u - v */
        Cry_LNSubtractionModular(tmp1Value, tmp1Value, tmp2Value, Modulus);
        /* x1 = x1 - x2 */
        Cry_LNSubtractionModular(tmp3Value, tmp3Value, InvValue, Modulus);
      }
      else
      {
        /* v = v - u */
        Cry_LNSubtractionModular(tmp2Value, tmp2Value, tmp1Value, Modulus);
        /* x2 = x2 - x1 */
        Cry_LNSubtractionModular(InvValue, InvValue, tmp3Value, Modulus);
      }

      CtxPtr->LNInversionState = CRY_LN_S_INVERSION_LOOP_OUTER;
      break;

    case CRY_LN_S_INVERSION_MODULO:
      if (Cry_LNModulo(InvValue, Modulus, CtxPtr) == TRUE)
      {
        Finished = TRUE;
      }
      break;

    /* CHECK: NOPARSE */
    /* Caution: This 'default' is not reachable by processing the function without an externally
                manipulated context.
                So it is for defensive programming and MISRA-C:2004.
    */
    default:
      {
        Finished = TRUE;
        break;
      }
      /* CHECK: PARSE */
  }

  return Finished;
#else
  Cry_LNWordType addResult, i;

  TS_PARAM_UNUSED(CtxPtr);

  /* Copy the input */
  /* u = a */
  for (i = 0U; i <= Value[CRY_LN_LENGTH_POS]; i++)
  {
    tmp1Value[i] = Value[i];
  }
  /* v = p */
  for (i = 0U; i <= Modulus[CRY_LN_LENGTH_POS]; i++)
  {
    tmp2Value[i] = Modulus[i];
  }

  /* x1 = 1 */
  tmp3Value[CRY_LN_LENGTH_POS] = 1U;
  tmp3Value[CRY_LN_LSW_POS]    = 1U;

  /* x2 = 0 */
  InvValue[CRY_LN_LENGTH_POS] = 0U;
  InvValue[CRY_LN_LSW_POS]    = 0U;

  /* while (u != 1 and v != 1) */
  while ((!((1U == tmp1Value[CRY_LN_LENGTH_POS]) && (1U == tmp1Value[CRY_LN_LSW_POS])) &&
          !((1U == tmp2Value[CRY_LN_LENGTH_POS]) && (1U == tmp2Value[CRY_LN_LSW_POS]))) &&
         (0U != tmp1Value[CRY_LN_LENGTH_POS])
        )
  {
    /* while u is even */
    while (0U == (tmp1Value[CRY_LN_LSW_POS] & 1U))
    {
      /* u = u/2 */
      Cry_LNDivByTwo(tmp1Value, 0U);

      /* if x1 is even */
      if (0U == (tmp3Value[CRY_LN_LSW_POS] & 1U))
      {
        /* x1 = x1 / 2 */
        Cry_LNDivByTwo(tmp3Value, 0U);
      }
      else
      {
        /* x1 = (x1 + p) / 2 */
        addResult = Cry_LNAddition(tmp3Value, tmp3Value, Modulus);
        Cry_LNDivByTwo(tmp3Value, addResult);
      }
    }

    /* while v is even */
    while (0U == (tmp2Value[CRY_LN_LSW_POS] & 1U))
    {
      /* v = v / 2 */
      Cry_LNDivByTwo(tmp2Value, 0U);

      /* if x2 is even */
      if (0U == (InvValue[CRY_LN_LSW_POS] & 1U))
      {
        /* x2 = x2 / 2 */
        Cry_LNDivByTwo(InvValue, 0U);
      }
      else
      {
        /* x2 = (x2 + p) / 2 */
        addResult = Cry_LNAddition(InvValue, InvValue, Modulus);
        Cry_LNDivByTwo(InvValue, addResult);
      }
    }

    /* if (u >= v) */
    /* Deviation MISRAC2012-1 */
    if ((CRY_E_LARGER == Cry_LNCompareNumbers(tmp1Value, tmp2Value)) ||
        (CRY_E_EQUAL  == Cry_LNCompareNumbers(tmp1Value, tmp2Value))
       )
    {
      /* u = u - v */
      Cry_LNSubtractionModular(tmp1Value, tmp1Value, tmp2Value, Modulus);
      /* x1 = x1 - x2 */
      Cry_LNSubtractionModular(tmp3Value, tmp3Value, InvValue, Modulus);
    }
    else
    {
      /* v = v - u */
      Cry_LNSubtractionModular(tmp2Value, tmp2Value, tmp1Value, Modulus);
      /* x2 = x2 - x1 */
      Cry_LNSubtractionModular(InvValue, InvValue, tmp3Value, Modulus);
    }
  }

  /* if (u == 1) */
  if ((1U == tmp1Value[CRY_LN_LENGTH_POS]) && (1U == tmp1Value[CRY_LN_LSW_POS]))
  {
    /* return (x1 mod p) */
    for (i = 0U; i <= tmp3Value[CRY_LN_LENGTH_POS]; i++)
    {
      InvValue[i] = tmp3Value[i];
    }
  }

  (void)Cry_LNModulo(InvValue, Modulus, CtxPtr);

  return TRUE;
#endif
}

FUNC(Std_ReturnType, CRY_CODE) Cry_LNLEByteArrayToNumber
(
  P2CONST(uint8,        AUTOMATIC, CRY_APPL_DATA) Array,
  uint32                                          ArrayLength,
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  Cry_LNWordType                                  NumberLength
)
{
  Cry_LNWordType NumberPos; /* the position in 'Number' */
  Cry_LNWordType wordPos;   /* byte position in the current word of 'Number'*/
  uint16         ArrayPos;  /* the position in the byte Array */
  Std_ReturnType RetVal = E_OK;

  if ((uint32)0 != ArrayLength)
  {
    if (NumberLength < (Cry_LNNumberLen(ArrayLength) + 1U))
    {
      RetVal = E_NOT_OK;
    }
    else
    {
      /* We cycle through all of the words of the resulting Number */
      for (NumberPos = (Cry_LNWordType)1; NumberPos <= Cry_LNNumberLen(ArrayLength); NumberPos++)
      {
        /* The current word of Number is initialized to '0'. */
        Number[NumberPos] = (Cry_LNWordType)0;

        /* "CRY_LN_WORD_LEN_BYTES" bytes of the Array are combined to make
         * up the current word of the Number.
         */
        for (wordPos = (Cry_LNWordType)0U;
             wordPos < (Cry_LNWordType)CRY_LN_WORD_LEN_BYTES;
             wordPos++
            )
        {
          ArrayPos  = (uint16)CRY_LN_WORD_LEN_BYTES;
          ArrayPos *= (uint16)(NumberPos - (Cry_LNWordType)1U);
          ArrayPos += (uint16)wordPos;

          if (ArrayPos < ArrayLength)
          {
            /* If we are not over the edge of 'Array', we incorporate the
             * current byte of 'Array' into the current word of the Number.
             */
            Number[NumberPos] |= (Cry_LNWordType)((Cry_LNWordType)Array[ArrayPos] <<
                                                  (Cry_LNWordType)((Cry_LNWordType)wordPos << 3U)
                                                 );
          }
        }
      }

      Number[CRY_LN_LENGTH_POS] = Cry_LNNumberLen(ArrayLength);

      Cry_LNNormalizeNumber(Number);
    }
  }
  else
  {
    /* The length of 'Array' is '0', so the resulting Number is also '0'. */
    Number[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }

  return RetVal;
}

FUNC(void, CRY_CODE) Cry_LNModExpStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  CtxPtr->LNModExpState = CRY_LN_S_MODEXP_START;
}

FUNC(boolean, CRY_CODE) Cry_LNModExp
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Base,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Exponent,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
  boolean Finished = FALSE;

  switch (CtxPtr->LNModExpState)
  {
    case CRY_LN_S_MODEXP_START:
      CtxPtr->Bits              = Cry_LNBitLengthOfNumber(Exponent);
      Result[CRY_LN_LENGTH_POS] = 1U;
      Result[CRY_LN_LSW_POS]    = 1U;
      CtxPtr->LNModExpState     = CRY_LN_S_MODEXP_INPUT;
      break;

    case CRY_LN_S_MODEXP_INPUT:
      if ((CtxPtr->Bits) > (Cry_LNWordType)0U)
      {
        --(CtxPtr->Bits);

        Cry_LNMultiplyStart(CtxPtr);
        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MULTIPLY1;
      }
      else
      {
        Finished = TRUE;
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MULTIPLY1:
      /* Result = Result**2 mod Modulus  */
      if (Cry_LNMultiplyNumbers(Result, Result, Result, CtxPtr) == TRUE)
      {
        Cry_LNModuloStart(CtxPtr);

        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MODULO1;
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MODULO1:
      if (Cry_LNModulo(Result, Modulus, CtxPtr) == TRUE)
      {
        if ((Cry_LNWordType)1U == Cry_LNGetBit(Exponent, CtxPtr->Bits))
        {
          Cry_LNMultiplyStart(CtxPtr);
          CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MULTIPLY2;
        }
        else
        {
          CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT;
        }
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MULTIPLY2:
      /* Result = (Base * Result) mod Modulus */
      if (Cry_LNMultiplyNumbers(Result, Result, Base, CtxPtr) == TRUE)
      {
        Cry_LNModuloStart(CtxPtr);

        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MODULO2;
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MODULO2:
      if (Cry_LNModulo(Result, Modulus, CtxPtr) == TRUE)
      {
        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT;
      }
      break;

    /* CHECK: NOPARSE */
    /* Caution: This 'default' is not reachable by processing the function without an externally
                manipulated context.
                So it is for defensive programming and MISRA-C:2004.
    */
    default:
      {
        Finished = TRUE;
        break;
      }
      /* CHECK: PARSE */
  }

  return Finished;
#else
  uint32 Bits = Cry_LNBitLengthOfNumber(Exponent);
#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)
  Cry_LNWordType localBase[(CRY_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U] = {0U};
  Cry_LNWordType Rho;
  Cry_LNWordType i;

  for (i = 0U; i <= Base[CRY_LN_LENGTH_POS]; i++)
  {
    localBase[i] = Base[i];
  }
#else
  Result[CRY_LN_LENGTH_POS]  = 1U;
  Result[CRY_LN_LSW_POS]     = 1U;
#endif

  TS_PARAM_UNUSED(CtxPtr);

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)
  /* Calculate Rho */
  Cry_LNMontgomerySetup(Modulus, &Rho);

  /* Calculate R mod m */
  Cry_LNMontgomeryNormalization(Result, Modulus);

  /* G > P so we reduce it first */
  if (Cry_LNCompareNumbers(Modulus, localBase) != CRY_E_LARGER)
  {
    (void)Cry_LNModulo(localBase, Modulus, CtxPtr);
  }

  /* x * (R mod P) */
  (void)Cry_LNMultiplyNumbers(localBase, Result, localBase, CtxPtr);
  (void)Cry_LNModulo(localBase, Modulus, CtxPtr);
#endif

  while ((Bits) > 0U)
  {
    --(Bits);

    /* Result = Result**2 mod Modulus  */
#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_MEMORY_OPTIMIZED)
    (void)Cry_LNMultiplyNumbers(Result, Result, Result, CtxPtr);
#else
    Cry_LNSquareComba(Result, Result);
#endif

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)
    Cry_LNMontgomeryReduction(Result, Result, Modulus, Rho);
#else
    (void)Cry_LNModulo(Result, Modulus, CtxPtr);
#endif

    if ((Cry_LNWordType)1U == Cry_LNGetBit(Exponent, Bits))
    {
#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)
      (void)Cry_LNMultiplyNumbers(Result, Result, localBase, CtxPtr);

      Cry_LNMontgomeryReduction(Result, Result, Modulus, Rho);
#else
      (void)Cry_LNMultiplyNumbers(Result, Result, Base, CtxPtr);

      (void)Cry_LNModulo(Result, Modulus, CtxPtr);
#endif
    }
  }

#if (CRY_LN_ALGORITHM_VARIANT == CRY_LN_SPEED_OPTIMIZED)
  /* Apply Trans**(-1) to return from Montgomery system */
  Cry_LNMontgomeryReduction(Result, Result, Modulus, Rho);
#endif

  return TRUE;
#endif
}

FUNC(boolean, CRY_CODE) Cry_LNIsValid
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) LongNumber,
          uint32                                    PermittedMaxLength
)
{
  boolean status = FALSE;
  if ((LongNumber[CRY_LN_LENGTH_POS] < PermittedMaxLength) &&
      ((0U != LongNumber[CRY_LN_LENGTH_POS]) && (0U != LongNumber[LongNumber[CRY_LN_LENGTH_POS]]))
     )
  {
    status = TRUE;
  }
  return status;
}

#if (CRY_LN_USE_BARRETT == STD_ON)

FUNC(boolean, CRY_CODE) Cry_LNModExpBarrett
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Base,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Exponent,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Barrett,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
  boolean Finished = FALSE;

  switch (CtxPtr->LNModExpState)
  {
    case CRY_LN_S_MODEXP_START:
      CtxPtr->Bits              = Cry_LNBitLengthOfNumber(Exponent);
      Result[CRY_LN_LENGTH_POS] = 1U;
      Result[CRY_LN_LSW_POS]    = 1U;
      CtxPtr->LNModExpState     = CRY_LN_S_MODEXP_INPUT;
      break;

    case CRY_LN_S_MODEXP_INPUT:
      if ((CtxPtr->Bits) > 0U)
      {
        --(CtxPtr->Bits);

        Cry_LNMultiplyStart(CtxPtr);
        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MULTIPLY1;
      }
      else
      {
        Finished = TRUE;
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MULTIPLY1:
      /* Result = Result**2 mod Modulus  */
      if (Cry_LNMultiplyNumbers(Result, Result, Result, CtxPtr) == TRUE)
      {
        Cry_LNModuloBarrettStart(CtxPtr);
        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MODULO1;
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MODULO1:
      if (Cry_LNModuloBarrett(Result, Modulus, Barrett, CtxPtr) == TRUE)
      {
        if ((Cry_LNWordType)1U == Cry_LNGetBit(Exponent, CtxPtr->Bits))
        {
          Cry_LNMultiplyStart(CtxPtr);
          CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MULTIPLY2;
        }
        else
        {
          CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT;
        }
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MULTIPLY2:
      /* Result = (Base * Result) mod Modulus */
      if (Cry_LNMultiplyNumbers(Result, Result, Base, CtxPtr) == TRUE)
      {
        Cry_LNModuloBarrettStart(CtxPtr);

        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT_MODULO2;
      }
      break;

    case CRY_LN_S_MODEXP_INPUT_MODULO2:
      if (Cry_LNModuloBarrett(Result, Modulus, Barrett, CtxPtr) == TRUE)
      {
        CtxPtr->LNModExpState = CRY_LN_S_MODEXP_INPUT;
      }
      break;

    /* CHECK: NOPARSE */
    /* Caution: This 'default' is not reachable by processing the function without an externally
                manipulated context.
                So it is for defensive programming and MISRA-C:2004.
    */
    default:
      {
        Finished = TRUE;
        break;
      }
      /* CHECK: PARSE */
  }

  return Finished;
#else

  uint32 Bits = Cry_LNBitLengthOfNumber(Exponent);

  TS_PARAM_UNUSED(CtxPtr);

  Result[CRY_LN_LENGTH_POS] = 1U;
  Result[CRY_LN_LSW_POS]    = 1U;
  while ((Bits) > 0U)
  {
    --(Bits);

    /* Result = Result**2 mod Modulus  */
    (void)Cry_LNMultiplyNumbers(Result, Result, Result, CtxPtr);

    (void)Cry_LNModuloBarrett(Result, Modulus, Barrett, CtxPtr);

    if ((Cry_LNWordType)1U == Cry_LNGetBit(Exponent, Bits))
    {
      (void)Cry_LNMultiplyNumbers(Result, Result, Base, CtxPtr);

      (void)Cry_LNModuloBarrett(Result, Modulus, Barrett, CtxPtr);
    }
  }

  return TRUE;
#endif
}

#endif /* #if (CRY_LN_USE_BARRETT == STD_ON) */

/*==[Declaration of functions with internal linkage]==========================*/

#if (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON)
static FUNC(void, CRY_CODE) Cry_LNModuloBegin
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr,
   P2VAR(boolean,          AUTOMATIC, CRY_APPL_DATA) Finished
)
{
  uint32 lengthOfNum;
  uint32 lengthOfMod;

  /* We compute the length of number in bits. */
  lengthOfNum = Cry_LNBitLengthOfNumber(Number);

  /* We compute the length of modulus in bits. */
  lengthOfMod = Cry_LNBitLengthOfNumber(Modulus);

  /* We only do something if number is at least as long as modulus.
   * Otherwise, result = number mod modulus = number.
   * If the Modulus is 0 -> the result is 0.
   */
  if (lengthOfMod == (Cry_LNWordType)0U)
  {
    Number[CRY_LN_LENGTH_POS] = (Cry_LNWordType)lengthOfMod;
    *Finished                 = TRUE;
  }
  else if (lengthOfMod <= lengthOfNum)
  {
    /* We compute the length difference of number and modulus in bits.
     * We add 1 because we will subtract 1 at the beginning of the
     * do-while-loop.
     */
    CtxPtr->LengthDifference = (Cry_LNWordType)(lengthOfNum - lengthOfMod) + (Cry_LNWordType)1;

    /* Binary division: We shift modulus an amount of
     * CtxPtr->LengthDifference bits to the left. Then we check whether
     * number is at least as large as the shifted modulus. If this is
     * the case we subtract the shifted modulus from number. We decrease
     * CtxPtr->LengthDifference by one and repeat this game until
     * CtxPtr->LengthDifference is 0.
     * The modulus is not really shifted but the individual words of the
     * shifted modulus are computed when they are needed and stored in
     * CtxPtr->wordOfShiftedMod.
     */
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_SHIFT1;
  }
  else
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_FINISH;
  }
}

static FUNC(void, CRY_CODE) Cry_LNModuloShift1
(
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  /* At the beginning of each round, we decrease
   * CtxPtr->LengthDifference by one
   */
  (CtxPtr->LengthDifference)--;

  /* We extract from CtxPtr->LengthDifference how many complete
   * words to shift modulus and how many bits to shift modulus.
   */
  CtxPtr->shiftWords = Cry_LNDivByWordLen(CtxPtr->LengthDifference);
  CtxPtr->shiftBits  = Cry_LNModWordLen(CtxPtr->LengthDifference);

  /* The first position of modulus from which to create the shifted
   * modulus is computed. Note that this is one larger than the
   * most significant word of modulus.
   */
  CtxPtr->posInMod = Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U;

  /* The first position of number which to compare to the shifted
   * modulus is computed.
   */
  CtxPtr->posInNum = CtxPtr->posInMod + CtxPtr->shiftWords;

  /* For each word of modulus, the shifted modulus is computed and
   * compared to the corresponding word of number.
   */
  CtxPtr->LNModuloState = CRY_LN_S_MODULO_SHIFT2;
}

static FUNC(void, CRY_CODE) Cry_LNModuloShift2
(
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  Cry_LNWordType wordOfNumber; /* one word of number */

  /* We assemble the current word of the shifted modulus from the
   * words modulus[CtxPtr->posInMod] and modulus[CtxPtr->posInMod - 1].
   */

  /* We test whether the current position in modulus is an allowed
   * position.
   */
  if (CtxPtr->posInMod <= Modulus[CRY_LN_LENGTH_POS])
  {
    /* The current position in modulus is allowed. We take some
     * bits from the word of modulus at that position.
     */
    CtxPtr->wordOfShiftedMod = Modulus[CtxPtr->posInMod] << CtxPtr->shiftBits;
  }
  else
  {
    /* The current position in modulus is too high. We are at a
     * "leading zero". So, all the bits which go into
     * CtxPtr->wordOfShiftedMod are zero.
     */
    CtxPtr->wordOfShiftedMod = (Cry_LNWordType)0U;
  }

  /* The needed bits from modulus[CtxPtr->posInMod - 1] are incorporated
   * into CtxPtr->wordOfShiftedMod. If we shift the modulus by complete
   * words (which means "CtxPtr->shiftBits == 0") or if CtxPtr->posInMod
   * is the lowest possible position (which means CtxPtr->posInMod == 1)
   * no bits from modulus[CtxPtr->posInMod - 1] are needed.
   */
  if ((CtxPtr->shiftBits != (uint8)0U) && (CtxPtr->posInMod > (Cry_LNWordType)1U))
  {
    CtxPtr->wordOfShiftedMod |= (Cry_LNWordType)(Modulus[CtxPtr->posInMod - (Cry_LNWordType)1U] >>
                                (uint8)((uint8)CRY_LN_WORD_LEN_BITS - CtxPtr->shiftBits));
  }

  /* We compute the word of number which to compare to the word
   * of the shifted modulus. This is normally simply
   * number[CtxPtr->posInNum], but the position can be too high which
   * means that we are at a "leading zero" of number.
   */
  if (CtxPtr->posInNum > Number[CRY_LN_LENGTH_POS])
  {
    wordOfNumber = (Cry_LNWordType)0U;
  }
  else
  {
    wordOfNumber = Number[CtxPtr->posInNum];
  }

  /* Now, we compare the word of the shifted modulus to the current
   * word of number.
   */
  if (CtxPtr->wordOfShiftedMod == wordOfNumber)
  {
    CtxPtr->cmpNumMod = CRY_E_EQUAL;
  }
  else if (CtxPtr->wordOfShiftedMod > wordOfNumber)
  {
    CtxPtr->cmpNumMod = CRY_E_SMALLER;
  }
  else
  {
    CtxPtr->cmpNumMod = CRY_E_LARGER;
  }

  /* The positions are decreased by 1. */
  CtxPtr->posInMod--;
  CtxPtr->posInNum--;

  if ((CRY_E_EQUAL == CtxPtr->cmpNumMod) && (CtxPtr->posInMod > (Cry_LNWordType)0U))
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_SHIFT2;
  }
  else
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_SUBTRACT1;
  }
}

static FUNC(void, CRY_CODE) Cry_LNModuloSubtract1
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  /* If number is at least as large as the shifted modulus, we
   * subtract modulus from number.
   */
  if (CtxPtr->cmpNumMod != CRY_E_SMALLER)
  {
    CtxPtr->wordOfShiftedMod = (Cry_LNWordType)0U;

    CtxPtr->carry = (Cry_LNWordType)0U;

    /* When subtracting the shifted modulus from number we can
     * skip the least significant words of number because the
     * shifted modulus is 0, there. We compute the least
     * significant word of number which is affected by the
     * subtraction.
     */
    CtxPtr->posInNum = (Cry_LNWordType)1U + CtxPtr->shiftWords;

    /* We go through every word of the shifted modulus.    */
    CtxPtr->posInMod = (Cry_LNWordType)1U;

    CtxPtr->LNModuloState = CRY_LN_S_MODULO_SUBTRACT2;
  }
  else
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_EXPORT;
  }
}

static FUNC(void, CRY_CODE) Cry_LNModuloSubtract2
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  uint8 tempCarry;

  if (CtxPtr->posInMod <= Modulus[CRY_LN_LENGTH_POS])
  {
    tempCarry = 0U;

    CtxPtr->wordOfShiftedMod |= (Cry_LNWordType)(Modulus[CtxPtr->posInMod] << CtxPtr->shiftBits);

    /* We test whether a CtxPtr->carry forms at this position. This
     * happens when "CtxPtr->wordOfShiftedMod + CtxPtr->carry >
     * number[CtxPtr->posInNum]".  Since we cannot test this condition
     * directly because of possible overflows we use a more complicated
     * looking test which actually does exactly what we want.
     */
    if ((CtxPtr->wordOfShiftedMod > Number[CtxPtr->posInNum]) ||
        ((CtxPtr->wordOfShiftedMod >= Number[CtxPtr->posInNum]) &&
         (CtxPtr->carry > (Cry_LNWordType)0U)))
    {
      tempCarry = (uint8)1U;
    }

    /* We subtract "CtxPtr->wordOfShiftedMod" and "CtxPtr->carry" from
     * the number.
     */
    Number[CtxPtr->posInNum] -= CtxPtr->wordOfShiftedMod;
    Number[CtxPtr->posInNum] -= (Cry_LNWordType)CtxPtr->carry;

    CtxPtr->carry = (Cry_LNWordType)tempCarry;

    if (CtxPtr->shiftBits == (uint8)0U)
    {
      CtxPtr->wordOfShiftedMod = (Cry_LNWordType)0U;
    }
    else
    {
      CtxPtr->wordOfShiftedMod =
        Modulus[CtxPtr->posInMod] >> (uint8)((uint8)CRY_LN_WORD_LEN_BITS - CtxPtr->shiftBits);
    }

    CtxPtr->posInNum++;
    CtxPtr->posInMod++;
  }
  else
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_CARRY;
  }
}

static FUNC(void, CRY_CODE) Cry_LNModuloCarry
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2VAR(Cry_LNCtxType,  AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  /* Now we have to deal with leftover carries and a possible last
   * word of the shifted modulus. Since the CtxPtr->carry is at most one
   * and CtxPtr->wordOfShiftedMod is at least one bit shorter than the
   * largest possible word (making it at most half as large), we
   * can add both numbers in "CtxPtr->carry" without overflow.
   */
  CtxPtr->carry += CtxPtr->wordOfShiftedMod;

  /* Now we deal with the leftover carries. */
  while (CtxPtr->carry != (Cry_LNWordType)0U)
  {
    /* CHECK: NOPARSE */
    /* Defensive Programming - "else" branch is unreachable code. */
    if (Number[CtxPtr->posInNum] >= CtxPtr->carry)
    /* CHECK: PARSE */
    {
      /* The CtxPtr->carry has trickled away. */
      Number[CtxPtr->posInNum] -= CtxPtr->carry;
      CtxPtr->carry = (Cry_LNWordType)0U;
    }
    else
    {
      /* We have to take the CtxPtr->carry one word upwards. */
      Number[CtxPtr->posInNum] -= CtxPtr->carry;
      CtxPtr->carry = (Cry_LNWordType)1U;
    }
    CtxPtr->posInNum++;
  }
  CtxPtr->LNModuloState = CRY_LN_S_MODULO_EXPORT;
}

static FUNC(void, CRY_CODE) Cry_LNModuloExport
(
  P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  if ((CtxPtr->LengthDifference) > (Cry_LNWordType)0U)
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_SHIFT1;
  }
  else
  {
    CtxPtr->LNModuloState = CRY_LN_S_MODULO_FINISH;
  }
}

static FUNC(void, CRY_CODE) Cry_LNStateMultiplyBegin
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  P2VAR(boolean,          AUTOMATIC, CRY_APPL_DATA) Finished
)
{
  if (((Cry_LNWordType)0U == Multiplicand[CRY_LN_LENGTH_POS]) ||
      ((Cry_LNWordType)0U == Multiplicator[CRY_LN_LENGTH_POS])
     )
  {
    /* One of the inputs was 0, so the result is also 0. */
    Result[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
    *Finished                 = TRUE;
  }
  else
  {
    /* The highest word of the result is initialized to 0. This word is
     * not set directly during the following multiplication, but can
     * be reached through overflows during the computation of the lower
     * words.
     */
    Result[Multiplicand[CRY_LN_LENGTH_POS] + Multiplicator[CRY_LN_LENGTH_POS]] = (Cry_LNWordType)0U;

    CtxPtr->i =
      (Cry_LNWordType)(Multiplicand[CRY_LN_LENGTH_POS] + Multiplicator[CRY_LN_LENGTH_POS]) -
      (Cry_LNWordType)1U;

    CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_COMPUTE_OSUM;
  }
}

static FUNC(void, CRY_CODE) Cry_LNStateMultiplyComputeOsum
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  /* We compute the outer sum "\sum_{i=1}^{n+m-1}" from top to bottom. */

  if (CtxPtr->i > (Cry_LNWordType)0U)
  {
    if (CtxPtr->i >= Multiplicand[CRY_LN_LENGTH_POS])
    {
      CtxPtr->j =
        (Cry_LNWordType)(CtxPtr->i - Multiplicand[CRY_LN_LENGTH_POS]) + (Cry_LNWordType)1U;
    }
    else
    {
      CtxPtr->j = (Cry_LNWordType)1U;
    }

    CtxPtr->tempResult = (Cry_LNWordType)0U;

    CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_COMPUTE_ISUM1;
  }
  else
  {
    CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_FINISH;
  }
}

static FUNC(void, CRY_CODE) Cry_LNStateMultiplyComputeIsum1
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  /* We compute the inner sum "\sum_{j=\max\{1,i-n+1\}}^{\min\{i,m\}}".*/

  /* Multiply 'Multiplicand[i-j+1]' with 'Multiplicator[j]' and store
   * the lower word of the result in 'rl' and the higher word  in
   * 'carry'. 'temp' is a temporary variable.
   */

  if ((CtxPtr->j <= CtxPtr->i) && (CtxPtr->j <= Multiplicator[CRY_LN_LENGTH_POS]))
  {
    CtxPtr->temp = Cry_LNLowHalfWord(Multiplicand[(CtxPtr->i - CtxPtr->j) + (Cry_LNWordType)1U]) *
                   Cry_LNHighHalfWord(Multiplicator[CtxPtr->j]);

    CtxPtr->rl = Cry_LNHighHalfWord(Multiplicand[(CtxPtr->i - CtxPtr->j) + (Cry_LNWordType)1U]) *
                 Cry_LNLowHalfWord(Multiplicator[CtxPtr->j]);

    CtxPtr->temp += CtxPtr->rl;

    if (CtxPtr->temp < CtxPtr->rl)
    {
      CtxPtr->carry = Cry_LNHighHalfWord(CtxPtr->temp) |
                      (Cry_LNWordType)((Cry_LNWordType)CRY_LN_HALFWORD_MAX + (Cry_LNWordType)1U);
    }
    else
    {
      CtxPtr->carry = Cry_LNHighHalfWord(CtxPtr->temp);
    }

    CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_COMPUTE_ISUM2;
  }
  else
  {
    CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_EXPORT;
  }
}

static FUNC(void, CRY_CODE) Cry_LNStateMultiplyComputeIsum2
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  CtxPtr->rl = (Cry_LNWordType)(Cry_LNLowHalfWord(CtxPtr->temp) << (CRY_LN_WORD_LEN_BITS >> 1U));

  CtxPtr->temp = Cry_LNLowHalfWord(Multiplicand[(CtxPtr->i - CtxPtr->j) + (Cry_LNWordType)1U]) *
                 Cry_LNLowHalfWord(Multiplicator[CtxPtr->j]);

  /* The low word of the multiplication result is computed. */
  CtxPtr->rl += CtxPtr->temp;

  if (CtxPtr->rl < CtxPtr->temp)
  {
    CtxPtr->carry++;
  }

  /* The high word of the multiplication result is stored in 'carry'.  */
  CtxPtr->carry +=
    (Cry_LNWordType)(Cry_LNHighHalfWord(Multiplicand[(CtxPtr->i - CtxPtr->j) + (Cry_LNWordType)1U])
    * Cry_LNHighHalfWord(Multiplicator[CtxPtr->j]));

  /* The low word of the multiplication result is added to
   * 'tempResult'.
   */
  CtxPtr->tempResult += CtxPtr->rl;

  if (CtxPtr->tempResult < CtxPtr->rl)
  {
    /* There was an overflow. So, we increase the carry by one.
     * This increment cannot overflow since the carry, being the
     * high word of the multiplication of two words, is at least
     * one smaller than the maximal possible value.
     */
    CtxPtr->carry++;
  }

  /* We carry the carry upward until it has trickled away. */
  CtxPtr->temp = (Cry_LNWordType)1U;

  CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_CARRY;
}

static FUNC(void, CRY_CODE) Cry_LNStateMultiplyCarry
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Result,
  P2VAR(Cry_LNCtxType,  AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  while (CtxPtr->carry != (Cry_LNWordType)0U)
  {
    Result[CtxPtr->i + CtxPtr->temp] += CtxPtr->carry;

    if (Result[CtxPtr->i + CtxPtr->temp] < CtxPtr->carry)
    {
      /* We had another overflow. */
      CtxPtr->carry = (Cry_LNWordType)1U;
    }
    else
    {
      /* No overflow, the carry has trickled away. */
      CtxPtr->carry = (Cry_LNWordType)0U;
    }

    CtxPtr->temp++;
  }

  CtxPtr->j++;
  CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_COMPUTE_ISUM1;
}

static FUNC(void, CRY_CODE) Cry_LNStateMultiplyExport
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Result,
  P2VAR(Cry_LNCtxType,  AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  /* Now we are sure that we do not need values of the input arrays up
   * to position i anymore, so we can write the result array.
   */
  Result[CtxPtr->i] = CtxPtr->tempResult;

  CtxPtr->LNMultiplyNumbersState = CRY_LN_S_MULTIPLY_COMPUTE_OSUM;
  CtxPtr->i--;
}

#if (CRY_LN_USE_BARRETT == STD_ON)

static FUNC(void, CRY_CODE) Cry_LNModuloBarrettBegin
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  uint32 loopCount;

  /* The input 'Number' is needed twice during the computation, but once it
   * is shifted 'Modulus[CRY_LN_LENGTH_POS]-1' words to the right and once it is cropped to
   * the last 'Modulus[CRY_LN_LENGTH_POS]+1' words. This means that on the first occasion
   * all the words of 'Number' except for the last 'Modulus[CRY_LN_LENGTH_POS]-1' are needed
   * and on the second occasion only the last 'Modulus[CRY_LN_LENGTH_POS]+1' words of
   * 'Number' are needed. So, with the exception of a two word overlap, two
   * distinct parts of 'Number' are needed during the computation. So, we
   * begin by splitting 'Number' into the two distinct parts with a little
   * shifting. Then we have both parts at our disposal.
   */

  /* The more significant part of 'Number' is shifted 3 blocks to the left.  */
  for (loopCount = Number[CRY_LN_LENGTH_POS]; loopCount >= Modulus[CRY_LN_LENGTH_POS]; loopCount--)
  {
    Number[loopCount + (Cry_LNWordType)3U] = Number[loopCount];
  }

  /* The length of the two parts is computed. The left part starts at
   * Number[Modulus[CRY_LN_LENGTH_POS]+2].
   */
  if (Modulus[CRY_LN_LENGTH_POS] > Number[CRY_LN_LENGTH_POS])
  {
    /* The Number is so small that the right shifted part is zero and the
     * cropped part is the Number itself.
     */
    Number[Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U] = (Cry_LNWordType)0U;
  }
  else
  {
    /* The length of the right shifted part. */
    Number[Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U] =
      (Cry_LNWordType)(Number[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U) - Modulus[CRY_LN_LENGTH_POS];

    /* The length of the cropped part. */
    Number[CRY_LN_LENGTH_POS] = Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U;
  }

  /* CtxPtr->tempNumber is set to the start of the newly created Number. */
  CtxPtr->tempNumber = &Number[Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U];

  /* "CtxPtr->tempNumber" now contains the value of "Number" shifted "Modulus[CRY_LN_LENGTH_POS]-1"
   * words to the right, while "Number" itself now contains the old value of
   * Number cropped to the last "Modulus[CRY_LN_LENGTH_POS]+1" words. So, in the notation of
   * Menezes et al., 'CtxPtr->tempNumber' contains q1, while 'Number' contains r1.
   */

  CtxPtr->LNModuloBarrettState = CRY_LN_S_MODULO_B_MULTIPLY;
}

static FUNC(void, CRY_CODE) Cry_LNModuloBarrettMultiply
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Barrett,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  boolean OpResult;

  /* q2 = q1 * mu. q2 is stored in "CtxPtr->tempNumber". */
  Cry_LNMultiplyStart(CtxPtr);
  do
  {
    OpResult = Cry_LNMultiplyNumbers(CtxPtr->tempNumber, CtxPtr->tempNumber, Barrett, CtxPtr);
  } while (FALSE == OpResult);

  CtxPtr->LNModuloBarrettState = CRY_LN_S_MODULO_B_SHIFT;
}


static FUNC(void, CRY_CODE) Cry_LNModuloBarrettShift
(
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  uint32 loopCount;

  /* q3 = q2 / b**(k+1). This is a right shift by 'Modulus[CRY_LN_LENGTH_POS]+1' words. q3
   * is stored in "CtxPtr->tempNumber".
   */
  if (Modulus[CRY_LN_LENGTH_POS] >= CtxPtr->tempNumber[CRY_LN_LENGTH_POS])
  {
    /* 'CtxPtr->tempNumber' is so small that the right shift makes it 0. */
    CtxPtr->tempNumber[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }
  else
  {
    for (loopCount = (Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)2U);
         loopCount <= CtxPtr->tempNumber[CRY_LN_LENGTH_POS];
         loopCount++
        )
    {
      CtxPtr->tempNumber[loopCount - (Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U)] =
        CtxPtr->tempNumber[loopCount];
    }

    CtxPtr->tempNumber[CRY_LN_LENGTH_POS] -=
      (Cry_LNWordType)(Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U);
  }

  CtxPtr->LNModuloBarrettState = CRY_LN_S_MODULO_B_FINISH;
}

static FUNC(void, CRY_CODE) Cry_LNModuloBarrettFinish
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  uint32  loopCount;
  boolean OpResult;

  /* r3 = q3 * m. This step is not in the book. There, it is combined with
   * the next step and we go directly to r2 = (q3 * m) mod b**(k+1). r3 is
   * stored in CtxPtr->tempNumber.
   */
  Cry_LNMultiplyStart(CtxPtr);
  do
  {
    OpResult = Cry_LNMultiplyNumbers(CtxPtr->tempNumber, CtxPtr->tempNumber, Modulus, CtxPtr);
  } while (FALSE == OpResult);

  /* r2 = r3 mod b**(k+1). r2 is stored in CtxPtr->tempNumber. */
  if ((Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U) < CtxPtr->tempNumber[CRY_LN_LENGTH_POS])
  {
    CtxPtr->tempNumber[CRY_LN_LENGTH_POS] = Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U;
  }

  /* We now compute the following two steps of the algorithm in one go:
   *   3. r = r1 - r2.
   *   4. if r < 0 then r = r + b**(k+1).
   * r is stored in "Number".
   */
  Cry_LNBarretSubtractNumbers(Number,
                              Number,
                              CtxPtr->tempNumber,
                              Modulus[CRY_LN_LENGTH_POS] + (Cry_LNWordType)1U
                             );

  /* We know that the following while loop can never be repeated more than
   * twice with the correct Barrett value. So, we count the repetitions.
   */
  loopCount = (Cry_LNWordType)0U;

  /* while r > m do r = r - m. r is stored in Number. After this while-loop
   * has finished, the modulo computation is finished and the result is in
   * "Number".
   */
  while ((CRY_E_SMALLER != Cry_LNCompareNumbers(Number, Modulus)) &&
         (loopCount < (Cry_LNWordType)4U)
        )
  {
    Cry_LNBarretSubtractNumbers(Number, Number, Modulus, CRY_LN_WORD_MAX);
    loopCount++;
  }

  /* Did we do too many loop repetitions? */
  if ((Cry_LNWordType)4U == loopCount)
  {
    /* Something went wrong. Probably an incorrect Barrett value. We set
     * the result to 0.
     */
    Number[CRY_LN_LENGTH_POS] = (Cry_LNWordType)0U;
  }
}

#endif /* #if (CRY_LN_USE_BARRETT == STD_ON) */

#endif /* (CRY_LN_INTERRUPTABLE_ENABLED == STD_ON) */

#define CRY_STOP_SEC_CODE
#include <MemMap.h>
