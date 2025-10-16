/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0008,1 */

/** \cond DONTDOCUMENT */

#ifndef CRY_LN_H
#define CRY_LN_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Cry_Common.h>
#include <Cry_CommonConfig.h>

/*==[Macros]==================================================================*/

#if (CPU_TYPE == CPU_TYPE_32)

#if (defined CRY_LN_WORD_LEN_BYTES)
#error CRY_LN_WORD_LEN_BYTES is already defined
#endif
/** \brief  The length of a word of the long number representation in bytes.
 **
 **/
#define CRY_LN_WORD_LEN_BYTES 4U

#if (defined CRY_LN_WORD_LEN_LEN_BITS)
#error CRY_LN_WORD_LEN_LEN_BITS is already defined
#endif
/** \brief  The length of the length of a word in the long number representation in
 **  bits.
 **
 **/
#define CRY_LN_WORD_LEN_LEN_BITS 5U

#if (defined CRY_LN_HALFWORD_MAX)
#error CRY_LN_HALFWORD_MAX is already defined
#endif
/** \brief  The maximal value which can fit into one half of a word.
 **
 **/
#define CRY_LN_HALFWORD_MAX 0xFFFFU

#if (defined CRY_LN_WORD_HIGH_BIT)
#error CRY_LN_WORD_HIGH_BIT is already defined
#endif
/** \brief  A word where only the most significant bit is set.
 **
 **/
#define CRY_LN_WORD_HIGH_BIT (Cry_LNWordType)0x80000000UL

#elif (CPU_TYPE == CPU_TYPE_16)

#if (defined CRY_LN_WORD_LEN_BYTES)
#error CRY_LN_WORD_LEN_BYTES is already defined
#endif
/** \brief  The length of a word of the long number representation in bytes.
 **
 **/
#define CRY_LN_WORD_LEN_BYTES 2U

#if (defined CRY_LN_WORD_LEN_LEN_BITS)
#error CRY_LN_WORD_LEN_LEN_BITS is already defined
#endif
/** \brief  The length of the length of a word in the long number representation in
 ** bits.
 **
 **/
#define CRY_LN_WORD_LEN_LEN_BITS 4U

#if (defined CRY_LN_HALFWORD_MAX)
#error CRY_LN_HALFWORD_MAX is already defined
#endif
/** \brief  The maximal value which can fit into one half of a word.
 **
 **/
#define CRY_LN_HALFWORD_MAX 0xFFU

#if (defined CRY_LN_WORD_HIGH_BIT)
#error CRY_LN_WORD_HIGH_BIT is already defined
#endif
/** \brief  A word where only the most significant bit is set.
 **
 **/
#define CRY_LN_WORD_HIGH_BIT (Cry_LNWordType)0x8000U

#else

#error Unknown CPU_TPYE
#endif

#if (defined CRY_LN_WORD_LEN_BITS)
#error CRY_LN_WORD_LEN_BITS is already defined
#endif
/** \brief  The length of a word of the long number representation in bits.
 **
 **/
#define CRY_LN_WORD_LEN_BITS (CRY_LN_WORD_LEN_BYTES * 8U)

#if (defined CRY_LN_HALFWORD_LEN_BITS)
#error CRY_LN_HALFWORD_LEN_BITS is already defined
#endif
/** \brief  The length of a half word of the long number representation in bits.
 **
 **/
#define CRY_LN_HALFWORD_LEN_BITS        (CRY_LN_WORD_LEN_BITS / 2U)

#if (defined Cry_LNLowHalfWord)
#error Cry_LNLowHalfWord is already defined
#endif
/** \brief  Extracts the low half word of a given word.
 **
 **/
#define Cry_LNLowHalfWord(a) ((Cry_LNWordType)((a) & (Cry_LNWordType)CRY_LN_HALFWORD_MAX))

#if (defined Cry_LNHighHalfWord)
#error Cry_LNHighHalfWord is already defined
#endif
/** \brief  Extracts the high half word of a given word.
 **
 **/
#define Cry_LNHighHalfWord(a) ((Cry_LNWordType)((a) >> (CRY_LN_WORD_LEN_BITS >> 1U)))

#if (defined Cry_LNDivByWordLen)
#error Cry_LNDivByWordLen is already defined
#endif
/** \brief  Divide a value by the word length in bits.
 **
 **/
#define Cry_LNDivByWordLen(x) ((Cry_LNWordType)((x) >> CRY_LN_WORD_LEN_LEN_BITS))

#if (defined Cry_LNModWordLen)
#error Cry_LNModWordLen is already defined
#endif
/** \brief  Compute "x mod CRY_WORD_LEN_BITS". This only works because
 **  ::CRY_WORD_LEN_BITS is a power of 2.
 **
 **/
#define Cry_LNModWordLen(x) ((uint8)((x) & (Cry_LNWordType)(CRY_LN_WORD_LEN_BITS - 1U)))

#if (defined Cry_LNNumberLen)
#error Cry_LNNumberLen is already defined
#endif
/** \brief  Compute the amount of words that the long number representation of a
 **    number will need from the length of the number in bytes. This is the value
 **    "(float)x / (float)CSM_LN_WORD_LEN_BYTES" rounded up. We compute this with
 **    the following formula: ((x - 1) / CRY_LN_WORD_LEN_BYTES) + 1. .
 **
 **/
#define Cry_LNNumberLen(x)                          \
(                                                   \
   (Cry_LNWordType)                                 \
   (                                                \
      (uint32)                                      \
      (                                             \
         (uint32)                                   \
         (                                          \
            (uint32)(x) - (uint32)1                 \
         ) /                                        \
         (uint32)CRY_LN_WORD_LEN_BYTES              \
      ) +                                           \
     (uint32)1                                      \
   )                                                \
)

#if (defined Cry_LNGetBit)
#error Cry_LNGetBit is already defined
#endif
/** \brief  Returns a given bit of a given long number.
 **
 **/
#define Cry_LNGetBit(number,bit)                                         \
(                                                                        \
   (Cry_LNWordType)                                                      \
   (                                                                     \
      (Cry_LNWordType)                                                   \
      (                                                                  \
         (number)[Cry_LNDivByWordLen(bit) + (Cry_LNWordType)1] >>        \
                                                   Cry_LNModWordLen(bit) \
      ) &                                                                \
      (Cry_LNWordType)1                                                  \
   )                                                                     \
)

#if (defined CRY_MINIMUM)
#error CRY_MINIMUM is already defined
/** \brief Returns the minimum of two values */
#endif
#define CRY_MINIMUM(x, y) ((x) < (y)) ? (x) : (y)

/*==[Types]===================================================================*/

#if (CPU_TYPE == CPU_TYPE_32)

/** \brief  The word type
 **
 ** This is the integer type which has the fastest memory access on the
 ** current architecture. The long number representation is based on arrays
 ** of this type
 **/

typedef uint32 Cry_LNWordType;

#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON)

/** \brief  The double word type */

typedef uint64 Cry_LNDoubleWordType;
#endif

#elif (CPU_TYPE == CPU_TYPE_16)

/** \brief  The word type. This is the integer type which has the fastest memory access on the
 ** current architecture. The long number representation is based on arrays
 ** of this type.
 **
 **/

typedef uint16 Cry_LNWordType;

#if (CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT == STD_ON)

/** \brief  The double word type */

typedef uint32 Cry_LNDoubleWordType;
#endif

#else
  #error Unsupported CPU_TYPE
#endif

/** \brief Internal states of the inversion. */
typedef enum
{
  /** \brief The start of the inversion. */
  CRY_LN_S_INVERSION_START,
  /** \brief Intermediate of the inversion. */
  CRY_LN_S_INVERSION_LOOP_OUTER,
  /** \brief Intermediate of the inversion. */
  CRY_LN_S_INVERSION_LOOP_INNER_1,
  /** \brief Intermediate of the inversion. */
  CRY_LN_S_INVERSION_LOOP_INNER_2,
  /** \brief Intermediate of the inversion. */
  CRY_LN_S_INVERSION_SUBTRACT,
  /** \brief Intermediate of the inversion. */
  CRY_LN_S_INVERSION_MODULO
}
Cry_LNInversionStateType;


/**
 *
 * \enum Cry_LNMultiplyStateType
 * \brief Internal states of the multiplication
 *
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_BEGIN
 * \brief State of the CRY_LN_S_MULTIPLY_BEGIN
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_COMPUTE_OSUM
 * \brief State of the CRY_LN_S_MULTIPLY_COMPUTE_OSUM
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_COMPUTE_ISUM1
 * \brief State of the CRY_LN_S_MULTIPLY_COMPUTE_ISUM1
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_COMPUTE_ISUM2
 * \brief State of the CRY_LN_S_MULTIPLY_COMPUTE_ISUM2
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_CARRY
 * \brief State of the CRY_LN_S_MULTIPLY_CARRY
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_EXPORT
 * \brief State of the CRY_LN_S_MULTIPLY_EXPORT
 *//**
 * \var Cry_LNMultiplyStateType::CRY_LN_S_MULTIPLY_FINISH
 * \brief Operation finished
 */
typedef enum
{
  CRY_LN_S_MULTIPLY_BEGIN,
  CRY_LN_S_MULTIPLY_COMPUTE_OSUM,
  CRY_LN_S_MULTIPLY_COMPUTE_ISUM1,
  CRY_LN_S_MULTIPLY_COMPUTE_ISUM2,
  CRY_LN_S_MULTIPLY_CARRY,
  CRY_LN_S_MULTIPLY_EXPORT,
  CRY_LN_S_MULTIPLY_FINISH
}
Cry_LNMultiplyStateType;


/**
 * \enum Cry_LNModuloStateType
 * \brief Internal states of the modulo computation
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_BEGIN
 * \brief computation is started
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_SHIFT1
 * \brief first shift state
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_SHIFT2
 * \brief second shift state
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_SUBTRACT1
 * \brief first subtraction
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_SUBTRACT2
 * \brief second subtraction
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_CARRY
 * \brief carry state
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_EXPORT
 * \brief export of the result
 *//**
 * \var Cry_LNModuloStateType::CRY_LN_S_MODULO_FINISH
 * \brief Operation finished
 */
typedef enum
{
  CRY_LN_S_MODULO_BEGIN,
  CRY_LN_S_MODULO_SHIFT1,
  CRY_LN_S_MODULO_SHIFT2,
  CRY_LN_S_MODULO_SUBTRACT1,
  CRY_LN_S_MODULO_SUBTRACT2,
  CRY_LN_S_MODULO_CARRY,
  CRY_LN_S_MODULO_EXPORT,
  CRY_LN_S_MODULO_FINISH
}
Cry_LNModuloStateType;


/**
 * \enum Cry_LNModExpStateType
 * \brief Internal states of the modulo exponentiation
 *//**
 * \var Cry_LNModExpStateType::CRY_LN_S_MODEXP_START
 * \brief computation is started
 *//**
 * \var Cry_LNModExpStateType::CRY_LN_S_MODEXP_INPUT
 * \brief processing of input
 *//**
 * \var Cry_LNModExpStateType::CRY_LN_S_MODEXP_INPUT_MULTIPLY1
 * \brief first multiplication
 *//**
 * \var Cry_LNModExpStateType::CRY_LN_S_MODEXP_INPUT_MODULO1
 * \brief first modulo computation
 *//**
 * \var Cry_LNModExpStateType::CRY_LN_S_MODEXP_INPUT_MULTIPLY2
 * \brief second multiplication
 *//**
 * \var Cry_LNModExpStateType::CRY_LN_S_MODEXP_INPUT_MODULO2
 * \brief second modulo computation
 */
typedef enum
{
  CRY_LN_S_MODEXP_START,
  CRY_LN_S_MODEXP_INPUT,
  CRY_LN_S_MODEXP_INPUT_MULTIPLY1,
  CRY_LN_S_MODEXP_INPUT_MODULO1,
  CRY_LN_S_MODEXP_INPUT_MULTIPLY2,
  CRY_LN_S_MODEXP_INPUT_MODULO2
}
Cry_LNModExpStateType;


/**
 * \enum Cry_LNModuloBarrettStateType
 * \brief Internal states of the Barrett modulo computation
 *//**
 * \var Cry_LNModuloBarrettStateType::CRY_LN_S_MODULO_B_BEGIN
 * \brief computation is started
 *//**
 * \var Cry_LNModuloBarrettStateType::CRY_LN_S_MODULO_B_MULTIPLY
 * \brief multiplication state
 *//**
 * \var Cry_LNModuloBarrettStateType::CRY_LN_S_MODULO_B_SHIFT
 * \brief shift state
 *//**
 * \var Cry_LNModuloBarrettStateType::CRY_LN_S_MODULO_B_FINISH
 * \brief Operation finished
 */
typedef enum
{
   CRY_LN_S_MODULO_B_BEGIN,
   CRY_LN_S_MODULO_B_MULTIPLY,
   CRY_LN_S_MODULO_B_SHIFT,
   CRY_LN_S_MODULO_B_FINISH
}
Cry_LNModuloBarrettStateType;


/** \struct Cry_LNCtxType
 **  \brief The context of the long number arithmetic functions
 **
 ** \var Cry_LNCtxType::LNMultiplyNumbersState
 **  \brief Internal state of the function Cry_LNMultiplyNumbers().
 **
 ** \var Cry_LNCtxType::LNModExpState
 **  \brief Internal state of the function Cry_LNModExp()
 **
 ** \var Cry_LNCtxType::i
 **  \brief Loop counter of the arithmetic routines
 **
 ** \var Cry_LNCtxType::j
 **  \brief Loop counter of the arithmetic routines
 **
 ** \var Cry_LNCtxType::temp
 **  \brief Temporary value in one of the arithmetic routines
 **
 ** \var Cry_LNCtxType::rl
 **  \brief The low word of a multiplication result of the arithmetic routines
 **
 ** \var Cry_LNCtxType::carry
 **  \brief  A carry used in an addition
 **
 ** \var Cry_LNCtxType::tempResult
 **  \brief Temporary value in one of the arithmetic routines
 **
 ** \var Cry_LNCtxType::LNModuloState
 **  \brief Internal state of the function Cry_LNModulo()
 **
 ** \var Cry_LNCtxType::LengthDifference
 **  \brief Difference in length of two numbers in the modulo
 **
 ** \var Cry_LNCtxType::wordOfShiftedMod
 **  \brief One word of the shifted modulus in the modulo
 **
 ** \var Cry_LNCtxType::cmpNumMod
 **  \brief Stores whether number is larger than the shifted modulus in the modulo computation
 **
 ** \var Cry_LNCtxType::shiftBits
 **  \brief the amount of bits by which each word of modulus is to be shifted in the modulo
 **         computation
 **
 ** \var Cry_LNCtxType::shiftWords
 **  \brief The amount of full words by which modulus is to be shifted in the modulo computation
 **
 ** \var Cry_LNCtxType::posInNum
 **  \brief The current position in number in the modulo computation
 **
 ** \var Cry_LNCtxType::posInMod
 **  \brief  The current position in modulus in the modulo computation
 **
 ** \var Cry_LNCtxType::Bits
 **  \brief the current position in the exponent during the fast exponentiation computation
 **
 ** \var Cry_LNCtxType::LNModuloBarrettState
 **  \brief Internal state of the function Cry_LNModuloBarrett()
 **
 ** \var Cry_LNCtxType::tempNumber
 **  \brief Used for temporary storage of intermediate results
 **
 **/

typedef struct
{
  Cry_LNMultiplyStateType  LNMultiplyNumbersState;
  Cry_LNInversionStateType LNInversionState;
  Cry_LNModExpStateType    LNModExpState;
  Cry_LNWordType           i;
  Cry_LNWordType           j;
  Cry_LNWordType           temp;
  Cry_LNWordType           rl;
  Cry_LNWordType           carry;
  Cry_LNWordType           tempResult;

  Cry_LNModuloStateType    LNModuloState;
  Cry_LNWordType           LengthDifference;
  Cry_LNWordType           wordOfShiftedMod;
  Cry_ReturnType           cmpNumMod;
  uint8                    shiftBits;
  Cry_LNWordType           shiftWords;
  Cry_LNWordType           posInNum;
  Cry_LNWordType           posInMod;
  uint32                   Bits;
#if (CRY_LN_USE_BARRETT == STD_ON)
  Cry_LNModuloBarrettStateType                  LNModuloBarrettState;
  P2VAR(Cry_LNWordType, TYPEDEF, CRY_APPL_DATA) tempNumber;
#endif
}
Cry_LNCtxType;

/**
 * \struct Cry_RsaPublicKeyType
 * \brief The public RSA key used for verifying a signature.
 *//**
 * \var Cry_RsaPublicKeyType::length
 * \brief Dummy element to make the type compatible with the Csm key type.
 *//**
 * \var Cry_RsaPublicKeyType::PublicExponent
 * \brief The public exponent of the RSA key.
 *//**
 * \var Cry_RsaPublicKeyType::Modulus
 * \brief The modulus of the RSA key.
 *//**
 * \var Cry_RsaPublicKeyType::Barrett
 * \brief The Barrett value (only used if Barrett reduction is enabled).
 */
typedef struct
{
  uint32           length;
  Cry_LNWordType   PublicExponent[CRY_RSAPUBKEY_NUM_LEN_WORDS];
  Cry_LNWordType   Modulus[CRY_RSAPUBKEY_NUM_LEN_WORDS];
#if (CRY_LN_USE_BARRETT == STD_ON)
  Cry_LNWordType   Barrett[CRY_RSAPUBKEY_NUM_LEN_WORDS + 1U];
#endif
}
Cry_RsaPublicKeyType;

/**
 * \struct Cry_RsaPrivateKeyType
 * \brief The private RSA key used for verifying a signature.
 *//**
 * \var Cry_RsaPrivateKeyType::length
 * \brief Dummy element to make the type compatible with the Csm key type.
 *//**
 * \var Cry_RsaPrivateKeyType::SecretExponent
 * \brief The private exponent of the RSA key.
 *//**
 * \var Cry_RsaPrivateKeyType::Modulus
 * \brief The modulus of the RSA key.
 */
typedef struct
{
  uint32 length;
  Cry_LNWordType   SecretExponent[CRY_RSAPRIVKEY_NUM_LEN_WORDS];
  Cry_LNWordType   Modulus[CRY_RSAPRIVKEY_NUM_LEN_WORDS];
}
Cry_RsaPrivateKeyType;

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Bit length of a number in long number representation
 **
 ** This function computes the length of the binary representation of a number
 ** given in long number represenation. Since this function only uses the
 ** length information stored in <code>Number[0]</code> and the
 ** information stored in <code>Number[Number[0]]</code>, the number must
 ** have been normalized beforehand, for example by a call to
 ** Cry_LNNormalizeNumer(), to obtain a correct result
 **
 ** \param[in] Number A pointer to the number in long number representation,
 ** whose bit-length shall be computed. It must be a normalized number
 **
 ** \returns Length of the binary representation of the number
 **
 **/
extern FUNC(uint32, CRY_CODE) Cry_LNBitLengthOfNumber
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number
);
/** \brief  Remove leading zeros in long number representation
 **
 ** The most significant words of the long number representation of a number
 ** can contain zeros. This function removes those leading zeros.
 **
 ** \param[in,out] Number A pointer to the number in long number representation,
 ** whose leading zeros shall be removed
 **
 **/
extern FUNC(void, CRY_CODE) Cry_LNNormalizeNumber
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number
);

/** \brief  Start the multiplication
 **
 ** This function modifies the given context such that when the function
 ** Cry_LNMultiplyNumbers() is called with that context, it will perform
 ** a point multiplication
 **
 ** \param[in,out] CtxPtr A pointer to a context which will be initialized such that
 ** the function Cry_LNMultiplyNumbers() can be called with it
 **
 **/
extern FUNC(void, CRY_CODE) Cry_LNMultiplyStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA)    CtxPtr
);

/** \brief  Multiplies two numbers given in long number representation
 **
 ** This function multiplies two numbers given in long number representation.
 ** The function is implemented in such a way that multiplicand, multiplicator
 ** and result can all point to the same memory location.
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
 **  multiplication. Before the first call of this function, the context has to
 **  be initialized by a call to Cry_LNMultiplyNumbersStart()
 **
 ** \returns Error value
 **
 ** \retval FALSE The multiplication has not yet finished. It has to be called again
 **  with the same parameters
 ** \retval TRUE The multiplication has finished. Now, "Result" contains the result
 ** of the multiplication
 **
 **/
extern FUNC(boolean, CRY_CODE) Cry_LNMultiplyNumbers
(
   P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicand,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Multiplicator,
   P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief  Compares two numbers given in long number representation
 **
 ** This function compares two numbers given in long number representation
 **
 ** \param[in] Number1 A pointer to the long number representation of the
 ** first number to be compared
 **
 ** \param[in] Number2 A pointer to the long number representation of the
 ** second number to be compared
 **
 ** \returns Result of the comparison
 **
 ** \retval CRY_E_SMALLER If the first number is smaller than the second number
 **
 ** \retval CRY_E_EQUAL If both numbers are equal
 **
 ** \retval CRY_E_LARGER=If the first number is larger than the second number
 **
 **/
extern FUNC(Cry_ReturnType, CRY_CODE) Cry_LNCompareNumbers
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number1,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number2
);

/** \brief Start the multiplication
 **
 ** This function modifies the given context such that when the function
 ** Cry_LNModulo() is called with that context, it will perform
 ** a modulo computation.
 **
 ** \param[in,out] CtxPtr A pointer to a context which will be initialized such that
 ** the function Cry_LNModulo() can be called with it
 **
 **/
extern FUNC(void, CRY_CODE) Cry_LNModuloStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Computes the modulo operation
 **
 ** This function computes a modulo operation
 **
 ** \param[in,out] Number A pointer to the long number representation of the
 ** number on which the modulo operation should be performed and also the place
 ** where the result should be stored
 **
 ** \param[in] Modulus A pointer to the long number representation of the modulus
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modulo operation. Before the first call of this function, the context has to
 ** be initialized by a call to Cry_LNModuloStart().
 **
 ** \retruns Status of the modulo operation
 **
 ** \retval FALSE The modulo operation has not yet finished. It has to be called again
 ** with the same parameters
 **
 ** \retval TRUE The modulo operation has finished. Now, "Number" contains the result
 ** of the operation
 **/
extern FUNC(boolean, CRY_CODE) Cry_LNModulo
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA)    CtxPtr
);

#if (CRY_LN_USE_BARRETT == STD_ON)
/**  \brief Start the modulus operation
 **
 ** This function modifies the given context such that when the function
 ** Cry_LNModuloBarrett() is called with that context, it will perform
 ** a modulo computation.
 **
 ** \param[in,out]   CtxPtr  A pointer to a context which will be initialized
 **                          such that the function Cry_LNModuloBarrett() can be
 **                          called with it.
 **/
extern FUNC(void, CRY_CODE) Cry_LNModuloBarrettStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/**  \brief This function computes a modulo operation
 **
 ** This function computes the modulus operation for configurations with activated
 ** Barrett reduction
 **
 ** \param[in,out] Number A pointer to the long number representation of the number
 **                       on which the modulo operation should be performed and also
 **                       the place where the result should be stored. Cry_LNModuloBarrett()
 **                       executes computations on Number, which makes it neccessary,
 **                       that the provided space in memory for Number is at least twice
 **                       the length of the Modulus.
 ** \param[in]    Modulus A pointer to the long number representation of the Modulus.
 **                       The Modulus must never be 0.
 ** \param[in]    Barrett A pointer to the long number representation of the Barrett value.
 **                       The Barrett value must never be 0.
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 **                       modulo operation. Before the first call of this function, the context
 **                       has to be initialized by a call to Cry_LNModuloBarrettStart().
 **
 ** \returns    State of the computation
 **
 ** \retval     TRUE      The modulo operation has finished. Now, "Number" contains the
 **                       result of the operation.
 ** \retval     FALSE     The modulo operation has not yet finished. It has to be called
 **                       again with the same parameters.
 **
 **/
extern FUNC(boolean, CRY_CODE) Cry_LNModuloBarrett
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Number,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Barrett,
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA)    CtxPtr
);
#endif

/** \brief Converts byte array to long number representation
 **
 ** This function converts a byte array which contains a number in big endian
 ** notation to long number representation.
 **
 ** \param[in] Array A pointer to the memory area which holds the number as
 ** a byte array in big endian notation. This means that the most significant
 ** byte is at <code>array[0]</code>
 **
 ** \param[in] ArrayLength The length of the array in bytes
 **
 ** \param[out] Number A pointer to the memory area which will hold the long
 ** number representation of the converted number after the function has
 ** finished.
 **
 ** \param[in]  NumberLength The length of the memory area where the number can be stored
 ** (including the first word containing the length of long number
 ** representation).
 **
 ** \retruns Status of the convert operation
 **
 ** \retval E_OK The conversion succeeded
 **
 ** \retval E_NOT_OK There was not enough space to store the number
 **
 **/
extern FUNC(Std_ReturnType, CRY_CODE) Cry_LNBEByteArrayToNumber
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)        Array,
  uint32                                          ArrayLength,
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  Cry_LNWordType                                  NumberLength
);

/** \brief Converts a long number representation to a byte array
 **
 ** This function converts the long number representation of a number to a
 ** byte array in big endian notation
 **
 ** \param[in] Number A pointer to the long number representation which
 ** should be converted.
 **
 ** \param[out] Array A pointer to the memory area which will hold the number
 ** as a byte array in big endian notation. This means that the most significant
 ** byte is at <code>array[0]</code>
 **
 ** \param[in,out] ArrayLengthPtr A pointer to a variable which has to contain the length of
 ** the memory area where the number will be stored. When the function returns
 ** it, the variable contains the length of the stored number.
 **
 ** \retruns Status of the convert operation
 **
 ** \retval E_OK The conversion succeeded
 **
 ** \retval E_NOT_OK There was not enough space to store the number
 **
 **/
extern FUNC(Std_ReturnType, CRY_CODE) Cry_LNNumberToBEByteArray
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)            Array,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA)           ArrayLengthPtr
);

/** \brief Converts a long number representation to a byte array.
 **
 **    This function converts the long number representation of a number to a
 **    byte array in little endian notation.
 **
 ** \param[in]    A pointer to the long number representation which should be converted.
 **
 **
 ** \param[in,out] A pointer to the memory area which will hold the number
 **                as a byte array in little endian notation.
 **
 **
 ** \param[in,out] A pointer to a variable which has to contain the length of
 **                the memory area where the number will be stored. When the function returns
 **                it, the variable contains the length of the stored number.
 **
 ** \retruns
 **
 ** \retval E_OK The conversion succeeded
 **
 ** \retval E_NOT_OK There was not enough space to store the number
 **
 **/
FUNC(Std_ReturnType, CRY_CODE) Cry_LNNumberToLEByteArray
(
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)            Array,
   P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA)           ArrayLengthPtr
);

/** \brief Division by two
 **
 ** \param[in]   The byte array which holds the number to be divided.
 **
 ** \param[in,out] 0 or 1 depending on what shall be added in the highest
 **/
FUNC(void, CRY_CODE) Cry_LNDivByTwo
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Value,
   Cry_LNWordType                                  Overflow
);

/** \brief Converts byte array to long number representation.
 **
 ** This function converts a byte array which contains a number in little endian
 ** notation to long number representation.
 **
 ** \param[in]     A pointer to the memory area which holds the number as
 **                a byte array in little endian notation.
 **
 ** \param[in]     The length of the array in bytes.
 **
 ** \param[in,out] A pointer to the memory area which will hold the long
 **                number representation of the converted number after the function has finished.
 **
 ** \param[in]     The length of the memory area where the number can be stored
 **                (including the first word containing the length of long number representation).
 **
 ** \retruns
 **
 ** \retval E_OK The conversion succeeded
 **
 ** \retval E_NOT_OK There was not enough space to store the number
 **
 **/
FUNC(Std_ReturnType, CRY_CODE) Cry_LNLEByteArrayToNumber
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)        Array,
  uint32                                          ArrayLength,
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Number,
  Cry_LNWordType                                  NumberLength
);

/** \brief Performs the addition of two values in long number representation
 **
 ** The function is implemented in such a way that addend1, addend2 and result
 ** can all point to the same memory location.
 **
 ** Both Addend1 and Addend2 *must* be smaller than Modulus
 **
 **
 ** \param[in, out] The value the operation will store the result of the addition too.
 **
 ** \param[in]      The array to the addend1
 **
 ** \param[in]      The array to the addend2
 **
 ** \param[in]      The array to the modulus of the addition.
 **/
FUNC(void, CRY_CODE) Cry_LNAdditionModular
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Sum,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend1,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend2,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus
);


/** \brief Performs the addition of two values in long number representation
 **
 ** The function is implemented in such a way that addend1, addend2 and result
 ** can all point to the same memory location.
 **
 ** \param[out] The value the operation will store the result of the addition to.
 **
 ** \param[in]  The array to the addend1
 **
 ** \param[in]  The array to the addend1
 **
 ** \retruns    The result of addition.
 **
 **/
FUNC(Cry_LNWordType, CRY_CODE) Cry_LNAddition
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Sum,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend1,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Addend2
);

/** \brief Performs the subtraction of two values in long number representation
 **
 **  The function is implemented in such a way that minuend, subtrahend and
 **  result can all point to the same memory location. Performs the subtraction
 **  of two values in long number representation.
 **
 ** \param[out] The value the operation will store the result of the subtraction to.
 **
 ** \param[in]  The array to the minuend.
 **
 ** \param[in]  The array to the subtracted.
 **
 ** \param[in]  The array to the modulus of the subtraction.
 **
 **/
FUNC(void, CRY_CODE) Cry_LNSubtractionModular
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Difference,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Minuend,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Subtrahend,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus
);

/** \brief Start the inversion.
 **
 ** This function modifies the given context such that when the function
 ** Cry_LNInversion() is called with that context, it will perform an inversion.
 **
 ** \param[in,out] A pointer to a context which will be initialized such that
 **                the function Cry_LNInversion() can be called with it.
 **/
FUNC(void, CRY_CODE) Cry_LNInversionStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);


/** \brief Start the inversion.
 **
 ** Computes a^-1 mod p of a given value a and modulus p
 **
 ** \param[in,out] The value the operation will store the result of the invertion to.
 **
 ** \param[in]     The array to the value to be inverted.
 **
 ** \param[in,out] The array to the first temporary Value neede within the computation
 **
 ** \param[in,out] The array to the second temporary Value neede within the computation
 **
 ** \param[in,out] The array to the third temporary Value neede within the computation
 **
 ** \param[in]     The array to the modulus of the subtraction.
 **
 ** \param[in,out] A pointer to a context which holds the current state of the
 **                inversion. Before the first call of this function, the context has to
 **                be initialized by a call to Cry_LNInversionStart().
 **
 ** \retruns boolean
 **
 ** \retval FALSE The inversion has not yet finished. It has to be called again
 **               with the same parameters.
 **
 ** \retval TRUE  The inversion has finished. Now, "InvValue" contains the result of the operation.
 **
 **/
FUNC(boolean, CRY_CODE) Cry_LNInversion
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   InvValue,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Value,
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   tmp1Value,
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   tmp2Value,
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   tmp3Value,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA)    CtxPtr
);


/** \brief Start the modular exponentiation
 **
 ** This function modifies the given context such that when the function
 ** Cry_LNModExp() is called with that context, it will perform
 ** a modular exponentiation
 **
 ** \param[in,out] CtxPtr A pointer to a context which will be initialized such that
 ** the function Cry_LNModExp() can be called with it
 **/
extern FUNC(void, CRY_CODE) Cry_LNModExpStart
(
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

/** \brief Computes a^b mod c of a given value a, exponent b, and modulus c
 **
 ** Performs a modular exponentiation using the square-and-multiply algorithm
 **
 ** \param[out] Result=a pointer to the buffer where the result will be stored and also
 ** where intermediate results will be stored. Because of this its length
 ** has to be twice the length of Base
 **
 ** \param[in] Base The base which should be exponentiated
 **
 ** \param[in] Modulus The modulus which should be used in the modular exponentiation
 **
 ** \param[in] Exponent The exponent with which the base should be exponentiated
 **
 ** \param[in,out] CtxPtr A pointer to a context which holds the current state of the
 ** modular exponentiation. Before the first call of this function, the context has to
 ** be initialized by a call to Cry_LNModExpStart()
 **
 ** \returns Status of the operation
 **
 ** \retval FALSE The exponentiation has not yet finished. It has to be called again
 ** with the same parameters
 **
 ** \retval TRUE The exponentiation has finished. Now, "Result" contains the result
 ** of the operation.
 **/
extern FUNC(boolean, CRY_CODE) Cry_LNModExp
(
   P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA)   Result,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Base,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
   P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Exponent,
   P2VAR(Cry_LNCtxType, AUTOMATIC, CRY_APPL_DATA)    CtxPtr
);

/** \brief Checks whether a LongNumber representation is valid
 **
 ** Performs a length information check for the given LongNumber representation
 **
 ** \param[in] LongNumber         The LongNumber to check
 **
 ** \param[in] PermittedMaxLength The max length the LongNumber shall have in [Cry_LNWordType]
 **
 ** \returns Statement regarding the validity of the LongNumber
 **
 ** \retval FALSE The LongNumber is not valid
 ** \retval TRUE  The LongNumber is valid
 **/
extern FUNC(boolean, CRY_CODE) Cry_LNIsValid
(
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) LongNumber,
          uint32                                    PermittedMaxLength
);

/**  \brief Multiply a number in long number representation by two
 **
 ** \param[out] A      The multiplied number.
 ** \param[in]  B      A number to multiplied.
 **
 **/
extern FUNC(void, CRY_CODE) Cry_LNMultByTwo
(
 P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) A,
 P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) B
);

#if (CRY_LN_USE_BARRETT == STD_ON)

/**  \brief Computes a^b mod c of a given value a, exponent b, and modulus c
 **
 ** Performs a modular exponentiation using the square-and-multiply algorithm.
 ** The modulo operation uses Barrett reduction.
 **
 ** \param[out] Result     A pointer to the buffer where the result is stored
 **                        and also where intermediate results are stored. Because
 **                        of this its length has to be twice the length of Base.
 ** \param[in]  Base       The base which is exponentiated.
 ** \param[in]  Modulus    The modulus which is used in the modular exponentiation.
 ** \param[in]  Exponent   The exponent with which the base is exponentiated.
 ** \param[in]  Barrett    The Barrett value for the modulo operation
 ** \param[in,out] CtxPtr  A pointer to a context which holds the current state of the
 **                        inversion. Before the first call of this function, the context
 **                        has to be initialized by a call to Cry_LNModExpStart().
 **
 ** \returns    State of the computation
 **
 ** \retval     TRUE      The exponentiation has finished. Now, "Result" contains the result
 **                       of the operation.
 ** \retval     FALSE     The exponentiation has not yet finished. It has to be called again
 **                       with the same parameters.
 **
 **/
extern FUNC(boolean, CRY_CODE) Cry_LNModExpBarrett
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) Result,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Base,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Modulus,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Exponent,
  P2CONST(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) Barrett,
  P2VAR(Cry_LNCtxType,    AUTOMATIC, CRY_APPL_DATA) CtxPtr
);
#endif

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/** \endcond  */

#endif /* #ifndef CRY_LN_H */
