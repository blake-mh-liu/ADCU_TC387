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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_LN.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_LIB_LN_H
#define CRYPTO_XVIX_XAIX_INT_LIB_LN_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_Lib_LN_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_LN.h/0002,1 */

/*==================[macros]======================================================================*/

/* --- Error codes (Crypto_xVIx_xAIx_LNCompareReturnType) --------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_LN_E_EQUAL)
#error CRYPTO_XVIX_XAIX_LN_E_EQUAL already defined
#endif
/** \brief  Memory blocks are equal. **/
#define CRYPTO_XVIX_XAIX_LN_E_EQUAL 2U

#if (defined CRYPTO_XVIX_XAIX_LN_E_NOT_EQUAL)
#error CRYPTO_XVIX_XAIX_LN_E_NOT_EQUAL already defined
#endif
/** \brief  Memory blocks are not equal. **/
#define CRYPTO_XVIX_XAIX_LN_E_NOT_EQUAL 3U

#if (defined CRYPTO_XVIX_XAIX_LN_E_SMALLER)
#error CRYPTO_XVIX_XAIX_LN_E_SMALLER already defined
#endif
/** \brief  If number1 smaller than number2. **/
#define CRYPTO_XVIX_XAIX_LN_E_SMALLER 4U

#if (defined CRYPTO_XVIX_XAIX_LN_E_LARGER)
#error CRYPTO_XVIX_XAIX_LN_E_LARGER already defined
#endif
/** \brief  If number1 is greater than number2. **/
#define CRYPTO_XVIX_XAIX_LN_E_LARGER 5U

/* --- General ---------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES)
#error CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES already defined
#endif
/** \brief  The length of a word in the long number representation in bytes. **/
#define CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES 4U

#if (defined CRYPTO_XVIX_XAIX_LN_WORD_LEN_LEN_BITS)
#error CRYPTO_XVIX_XAIX_LN_WORD_LEN_LEN_BITS already defined
#endif
/** \brief  The length of a word in the long number representation in bits. **/
#define CRYPTO_XVIX_XAIX_LN_WORD_LEN_LEN_BITS 5U

#if (defined CRYPTO_XVIX_XAIX_LN_HALFWORD_MAX)
#error CRYPTO_XVIX_XAIX_LN_HALFWORD_MAX already defined
#endif
/** \brief  The maximal value which can fit into one half of a word. **/
#define CRYPTO_XVIX_XAIX_LN_HALFWORD_MAX 0xFFFFU

#if (defined CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT)
#error CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT already defined
#endif
/** \brief  A word where only the most significant bit is set. **/
#define CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT (Crypto_xVIx_xAIx_LNWordType) 0x80000000UL

#if (defined CRYPTO_XVIX_XAIX_LNLOWHALFWORD)
#error CRYPTO_XVIX_XAIX_LNLOWHALFWORD is already defined
#endif
/** \brief  Extracts the low half word of a given word. **/
#define CRYPTO_XVIX_XAIX_LNLOWHALFWORD(A)                                                         \
(                                                                                                 \
  (Crypto_xVIx_xAIx_LNWordType) (  (A)                                                            \
                                 & (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_HALFWORD_MAX \
                                )                                                                 \
)

#if (defined CRYPTO_XVIX_XAIX_LNHIGHHALFWORD)
#error CRYPTO_XVIX_XAIX_LNHIGHHALFWORD is already defined
#endif
/** \brief  Extracts the high half word of a given word. **/
#define CRYPTO_XVIX_XAIX_LNHIGHHALFWORD(A) \
((Crypto_xVIx_xAIx_LNWordType) ((A) >> (CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS >> 1U)))

#if (defined CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS)
#error CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS already defined
#endif
/** \brief  The length of a word of the long number representation in bits. **/
#define CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS (CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES << 3U)

#if (defined CRYPTO_XVIX_XAIX_LN_HALFWORD_LEN_BITS)
#error CRYPTO_XVIX_XAIX_LN_HALFWORD_LEN_BITS is already defined
#endif
/** \brief  The length of a half word of the long number representation in bits. **/
#define CRYPTO_XVIX_XAIX_LN_HALFWORD_LEN_BITS (CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS >> 1U)

#if (defined CRYPTO_XVIX_XAIX_LN_LOW_HALF_WORD)
#error CRYPTO_XVIX_XAIX_LN_LOW_HALF_WORD already defined
#endif
/** \brief  Extracts the low half word of a given word. **/
#define CRYPTO_XVIX_XAIX_LN_LOW_HALF_WORD(A)                                                      \
(                                                                                                 \
  (Crypto_xVIx_xAIx_LNWordType) (  (A)                                                            \
                                 & (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_HALFWORD_MAX \
                                )                                                                 \
)

#if (defined CRYPTO_XVIX_XAIX_LN_HIGH_HALF_WORD)
#error CRYPTO_XVIX_XAIX_LN_HIGH_HALF_WORD already defined
#endif
/** \brief  Extracts the high half word of a given word. **/
#define CRYPTO_XVIX_XAIX_LN_HIGH_HALF_WORD(A) \
((Crypto_xVIx_xAIx_LNWordType) ((A) >> (CRYPTO_XVIX_XAIX_LN_HALFWORD_LEN_BITS)))

#if (defined CRYPTO_XVIX_XAIX_LN_DIV_BY_WORD_LEN)
#error CRYPTO_XVIX_XAIX_LN_DIV_BY_WORD_LEN already defined
#endif
/** \brief  Divide a value by the word length in bits. **/
#define CRYPTO_XVIX_XAIX_LN_DIV_BY_WORD_LEN(X) \
((Crypto_xVIx_xAIx_LNWordType) ((X) >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_LEN_BITS))

#if (defined CRYPTO_XVIX_XAIX_LN_MOD_WORD_LEN)
#error CRYPTO_XVIX_XAIX_LN_MOD_WORD_LEN already defined
#endif
/** \brief  Compute "x mod CRYPTO_WORD_LEN_BITS".
 **
 ** This only works because CRYPTO_WORD_LEN_BITS is a power of 2.
 **/
#define CRYPTO_XVIX_XAIX_LN_MOD_WORD_LEN(X) \
((uint8) ((X) & (Crypto_xVIx_xAIx_LNWordType) (CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS - 1U)))

#if (defined CRYPTO_XVIX_XAIX_LN_NUMBER_LEN)
#error CRYPTO_XVIX_XAIX_LN_NUMBER_LEN already defined
#endif
/** \brief  Compute the amount of words that the long number representation of a number will need
 **         from the length of the number in bytes.
 **
 ** This is the value "(float)x / (float)CSM_LN_WORD_LEN_BYTES" rounded up.
 ** We compute this with the following formula:
 ** ((x - 1U) / CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES) + 1U.
 **/
#define CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(X) \
((Crypto_xVIx_xAIx_LNWordType) (((((uint32) (X) + CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES) - 1U) / CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES)))

#if (defined CRYPTO_XVIX_XAIX_LN_GET_BIT)
#error CRYPTO_XVIX_XAIX_LN_GET_BIT already defined
#endif
/** \brief  Returns a given bit of a given long number. **/
#define CRYPTO_XVIX_XAIX_LN_GET_BIT(Number, Bit)                                              \
(                                                                                             \
  (Crypto_xVIx_xAIx_LNWordType)                                                               \
  (                                                                                           \
    (Crypto_xVIx_xAIx_LNWordType)                                                             \
    (                                                                                         \
      (Number)[CRYPTO_XVIX_XAIX_LN_DIV_BY_WORD_LEN((Bit)) + (Crypto_xVIx_xAIx_LNWordType) 1U] \
      >> CRYPTO_XVIX_XAIX_LN_MOD_WORD_LEN((Bit))                                              \
    ) & (Crypto_xVIx_xAIx_LNWordType) 1U                                                      \
  )                                                                                           \
)

#if (defined CRYPTO_XVIX_XAIX_RESULT_SQUARE_COMBA_LENGTH)
#error CRYPTO_XVIX_XAIX_RESULT_SQUARE_COMBA_LENGTH already defined
#endif
/** \brief  Macro representing the length of the buffer needed for the Square comba operation **/
#define CRYPTO_XVIX_XAIX_RESULT_SQUARE_COMBA_LENGTH \
((CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U)

#if (defined CRYPTO_XVIX_XAIX_MONTGOM_REDUC_C_LENGTH)
#error CRYPTO_XVIX_XAIX_MONTGOM_REDUC_C_LENGTH already defined
#endif
/** \brief  Macro representing the length of the buffer needed for Montgomery Reduction operation.
 **/
#define CRYPTO_XVIX_XAIX_MONTGOM_REDUC_C_LENGTH \
((CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U)

#if (defined CRYPTO_XVIX_XAIX_LN_MOD_EXP_LENGTH)
#error CRYPTO_XVIX_XAIX_LN_MOD_EXP_LENGTH already defined
#endif
/** \brief  Macro representing the length of the buffer which contains the context for
 **         modular exponentiation operation.
 **/
#define CRYPTO_XVIX_XAIX_LN_MOD_EXP_LENGTH \
((CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS * 2U) - 1U)

#if (defined CRYPTO_XVIX_XAIX_RESULT_MULTI_LENGTH)
#error CRYPTO_XVIX_XAIX_RESULT_MULTI_LENGTH already defined
#endif
/** \brief  Macro representing the length of the buffer which hold the current state of
 **         the multiplication.
 **/
#define CRYPTO_XVIX_XAIX_RESULT_MULTI_LENGTH \
((CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS * 3U) - 1U)

#if (defined CRYPTO_XVIX_XAIX_INT_LIB_EDDSA_PRIME_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_LIB_EDDSA_PRIME_LENGTH already defined.
#endif
/** \brief  The length of the EdDSA prime array. **/
#define CRYPTO_XVIX_XAIX_INT_LIB_EDDSA_PRIME_LENGTH 9U

#if (defined CRYPTO_XVIX_XAIX_TEMP_BUFFER_LEN)
#error CRYPTO_XVIX_XAIX_TEMP_BUFFER_LEN already defined
#endif
/** \brief  TBD! what is the origon of this value!**/
#define CRYPTO_XVIX_XAIX_TEMP_BUFFER_LEN 11U

/*==================[type definitions]============================================================*/

/** \brief  The crypto return type for compare functions. **/
typedef uint8 Crypto_xVIx_xAIx_LNCompareReturnType;

/** \brief  The word type. **/
typedef uint32 Crypto_xVIx_xAIx_LNWordType;

/** \brief  The double word type. **/
typedef uint64 Crypto_xVIx_xAIx_LNDoubleWordType;

/** \brief  The context of the long number arithmetic functions.
 **
 ** \var  rl
 ** \brief  The low word of a multiplication result of the arithmetic routines.
 **
 ** \var  carry
 ** \brief  A carry used in an addition.
 **
 ** \var  tempResult
 ** \brief  Temporary value in one of the arithmetic routines.
 **
 ** \var  lengthDifference
 ** \brief  Difference in length of two numbers in the modulo computation.
 **
 ** \var  wordOfShiftedMod
 ** \brief  one word of the shifted modulus in the modulo computation.
 **
 ** \var  shiftWords
 ** \brief  The amount of full words by which modulus is to be shifted in the modulo computation.
 **
 ** \var  posInNum
 ** \brief  The current position in number in the modulo computation.
 **
 ** \var  posInMod
 ** \brief  The current position in modulus in the modulo computation.
 **
 ** \var  tempBuffer
 ** \brief  Temporary calculation array needed for LN calculations. This is needed for reenterency.
 **
 ** \var  localResultSquareComba
 ** \brief  To store the local temporary result of the square comba. This is needed for reenterency.
 **
 ** \var  localResultMultiply
 ** \brief  To store the local temporary result Multiply. This is needed for reenterency.
 **
 ** \var  montgomeryReductionC
 ** \brief  To store the local temporary result during montgomery reduction.This is needed for
 **         reentrancy.
 **
 ** \var  modExpLocalBase
 ** \brief  To store the local temporary result during modulus expansion local base.This is needed for
 **         reentrancy.
 **
 ** \var  cmpNumMod
 ** \brief  Stores whether number is larger than the shifted modulus in the modulo computation.
 **
 ** \var  shiftBits
 ** \brief  The amount of bits by which each word of modulus is to be shifted in the modulo
 **         computation.
 **/
typedef struct
{
  Crypto_xVIx_xAIx_LNWordType rl;
  Crypto_xVIx_xAIx_LNWordType carry;
  Crypto_xVIx_xAIx_LNWordType tempResult;
  Crypto_xVIx_xAIx_LNWordType lengthDifference;
  Crypto_xVIx_xAIx_LNWordType wordOfShiftedMod;
  Crypto_xVIx_xAIx_LNWordType shiftWords;
  Crypto_xVIx_xAIx_LNWordType posInNum;
  Crypto_xVIx_xAIx_LNWordType posInMod;

  Crypto_xVIx_xAIx_LNWordType tempBuffer[CRYPTO_XVIX_XAIX_TEMP_BUFFER_LEN];
  Crypto_xVIx_xAIx_LNWordType localResultSquareComba[CRYPTO_XVIX_XAIX_RESULT_SQUARE_COMBA_LENGTH];
  Crypto_xVIx_xAIx_LNWordType localResultMultiply[CRYPTO_XVIX_XAIX_RESULT_MULTI_LENGTH];
  Crypto_xVIx_xAIx_LNWordType montgomeryReductionC[CRYPTO_XVIX_XAIX_MONTGOM_REDUC_C_LENGTH];
  Crypto_xVIx_xAIx_LNWordType modExpLocalBase[CRYPTO_XVIX_XAIX_LN_MOD_EXP_LENGTH];

  Crypto_xVIx_xAIx_LNCompareReturnType cmpNumMod;
  uint8                       shiftBits;
}
Crypto_xVIx_xAIx_LNCtxType;

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The most significant words of the long number representation of a number can contain
 **         zeros.This function removes those leading zeros.
 **
 ** \param[in,out]  number  A pointer to the number in long number representation, whose leading
 **                         zeros shall be removed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNormalizeNumber
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number
);
#endif /* CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER */

/** \brief  The function is implemented in such a way that addend1, addend2 and result can all point
 **         to the same memory location.
 **
 ** \param[in,out]  sum      The location where the result of the addition will be stored to.
 ** \param[in]      addend1  The array to the addend1.
 ** \param[in]      addend2  The array to the addend2.
 ** \param[in]      modulus  The array to the modulus of the addition.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNAdditionModular
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sum,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR == STD_ON) */

/** \brief  Performs a modular exponentiation using the square-and-multiply algorithm.
 **
 ** \param[out]  result    A pointer to the buffer where the result will be stored and also where
 **                        intermediate results will be stored. Because of this its length has to be
 **                        twice the length of Base.
 ** \param[in]   base      The base which should be exponentiated.
 ** \param[in]   modulus   The modulus which should be used in the modular exponentiation.
 ** \param[in]   exponent  The exponent with which the base should be exponentiated.
 ** \paran[in]   ctxPtr    A pointer to a context which holds the current state of the inversion.
 **                        Before the first call of this function, the context has to be initialized
 **                        by a call to Crypto_xVIx_xAIx_LNModExpStart().
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNModExp
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) base,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) exponent,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON) */

/** \brief  Performs the inversion of values in long number representation and calculates modulo a
 **         given value.
 **
 ** \param[in,out]   invValue   The value the operation will store the result of the invertion to.
 ** \param[in]       value      The array to the value to be inverted.
 ** \param[in]       tmp1Value  The array to the first temporary Value needed within the computation.
 ** \param[in]       tmp2Value  The array to the second temporary Value needed within the computation
 ** \param[in]       tmp3Value  The array to the third temporary Value needed within the computation.
 ** \param[in]       modulus    The array to the modulus of the subtraction.
 ** \param[in]       ctxPtr     A pointer to a context which holds the current state of the inversion.
 **                             Before the first call of this function, the context has to be
 **                             initialized by a call to Crypto_xVIx_xAIx_LNInversionStart().
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNInversion
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) invValue,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1Value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2Value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3Value,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION == STD_ON) */

/** \brief  The function is implemented in such a way that minuend, subtrahend and result can all
 **         point to the same memory location. Performs the subtraction of two values in long number
 **         representation.
 **
 ** \param[in,out]  difference  The location where the result of the subtraction will be stored to.
 ** \param[in]      minuend     The array to the minuend.
 ** \param[in]      subtrahend  The array to the subtrahend.
 ** \param[in]      modulus     The array to the modulus of the subtraction.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSubtractionModular
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) difference,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) minuend,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) subtrahend,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR == STD_ON) */

/** \brief  The function is implemented in such a way that addend1, addend2 and result can all
 **         point to the same memory location.
 **
 ** \param[in,out]  sum      The location where the result of the addition will be stored to.
 ** \param[in]      addend1  The array to the addend1
 ** \param[in]      addend2  The array to the addend2.
 **
 ** \returns  The carry value.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION == STD_ON)
extern FUNC(uint8, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNAddition
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sum,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION == STD_ON) */

/** \brief  This function converts the long number representation of a number to a byte array in
 **         little endian notation.
 **
 ** \param[in]      number          A pointer to the long number representation which should be
 **                                 converted.
 ** \param[out]     array           A pointer to the memory area which will hold the number as a byte
 **                                 array in little endian notation.
 ** \param[in,out]  arrayLengthPtr  A pointer to a variable which has to contain the length of the
 **                                 memory area where the number will be stored. When the function
 **                                 returns it, the variable contains the length of the stored number.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      The conversion succeeded.
 ** \retval  E_NOT_OK  There was not enough space to store the number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToLEByteArray
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) arrayLengthPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY == STD_ON) */

/** \brief  This function converts a byte array which contains a number in little endian
 **         notation to long number representation.
 **
 ** \param[in]      array         A pointer to the memory area which holds the number as a byte
 **                               array in little endian notation.
 ** \param[in]      arrayLength   The length of the array in bytes.
 ** \param[out]     number        A pointer to the memory area which will hold the long number
 **                               representation of the converted number after the function has
 **                               finished.
 ** \param[in,out]  numberLength  The length of the memory area where the number can be stored in
 **                               double words. (including the first word containing the length of
 **                               long number representation. e.g. 32Byte = 9Word).
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      The conversion succeeded.
 ** \retval  E_NOT_OK  There was not enough space to store the number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNLEByteArrayToNumber
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
          uint32                                                    arrayLength,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
          Crypto_xVIx_xAIx_LNWordType                               numberLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER == STD_ON) */

/** \brief  This function converts the long number representation of a number to a byte array in
 **         big endian notation.
 **
 ** \param[in]      number          A pointer to the long number representation which should be
 **                                 converted.
 ** \param[out]     array           A pointer to the memory area which will hold the number as a byte
 **                                 array in big endian notation. This means that the most significant
 **                                 byte is at array[0].
 ** \param[in,out]  arrayLengthPtr  A pointer to a variable which has to contain the length of the
 **                                 memory area where the number will be stored. When the function
 **                                 returns it, the variable contains the length of the stored number.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      The conversion succeeded.
 ** \retval  E_NOT_OK  There was not enough space to store the number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToBEByteArray
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) arrayLengthPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY == STD_ON) */

/** \brief  This function converts a byte array which contains a number in big endian
 **         notation to long number representation.
 **
 ** \param[in]      array         A pointer to the memory area which holds the number as a byte
 **                               array in big endian notation.
 ** \param[in]      arrayLength   The length of the array in bytes.
 ** \param[out]     number        A pointer to the memory area which will hold the long number
 **                               representation of the converted number after the function has
 **                               finished.
 ** \param[in,out]  numberLength  The length of the memory area where the number can be stored in
 **                               double words. (including the first word containing the length of
 **                               long number representation. e.g. 32Byte = 9Word).
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      The conversion succeeded.
 ** \retval  E_NOT_OK  There was not enough space to store the number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNBEByteArrayToNumber
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
          uint32                                                    arrayLength,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
          Crypto_xVIx_xAIx_LNWordType                               numberLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER == STD_ON) */

/** \brief  This function computes a modulo operation.
 **
 ** \param[in,out]  number   A pointer to the long number representation of the number on which the
 **                          modulo operation should be performed and also the place where the
 **                          result should be stored.
 ** \param[in]      modulus  A pointer to the long number representation of the modulus.
 ** \param[in,out]  ctxPtr   A pointer to a context which holds the current state of the modulo
 **                          operation. Before the first call of this function, the context has to
 **                          be initialized by a call to Crypto_xVIx_xAIx_LNModuloStart().
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNModulo
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */

/** \brief  This function compares two numbers given in long number representation.
 **
 ** \param[in]  number1  A pointer to the long number representation of the first number to be
 **                      compared.
 ** \param[in]  number2  A pointer to the long number representation of the second number to be
 **                      compared.
 **
 ** \returns  Result of the comparison.
 **
 ** \retval  CRYPTO_XVIX_XAIX_LN_E_SMALLER  If the first number is smaller than the second number.
 ** \retval  CRYPTO_XVIX_XAIX_LN_E_EQUAL    If both numbers are equal.
 ** \retval  CRYPTO_XVIX_XAIX_LN_E_LARGER   If the first number is larger than the second number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS == STD_ON)
extern FUNC(Crypto_xVIx_xAIx_LNCompareReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNCompareNumbers
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number1,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number2
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS == STD_ON) */

/** \brief  This function subtracts two numbers.
 **
 ** This function subtracts two numbers from each other.
 ** The implementation of the function assumes that |Minuend| >= |Subtrahend|.
 **
 ** \param[out]  result     A pointer to a memory location which will hold the
 **                         result of the subtraction.
 ** \param[in]  minuend     A pointer to the minuend of the subtraction.
 ** \param[in]  subtrahend  A pointer to the subtrahend of the subtraction.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSubtraction
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) minuend,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) subtrahend
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION == STD_ON) */

/** \brief  This function squares a number.
 **
 ** \param[out]  result  The squared Number.
 ** \param[in]   number  A number to be squared.
 ** \param[in]   ctxPtr  A pointer to a context which holds the buffers needed for the Sqare comba
 **                      operation.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSquareComba
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA == STD_ON */

/** \brief  Checks whether a LongNumber representation is valid.
 **
 ** Performs a length information check for the given LongNumber representation.
 **
 ** \param[in]  longNumber          The LongNumber to check.
 ** \param[in]  permittedMaxLength  The max length the LongNumber shall have in
 **                                 [Crypto_xVIx_xAIx_LNWordType].
 **
 ** \returns  Statement regarding the validity of the LongNumber.
 **
 ** \retval  FALSE  The LongNumber is not valid.
 ** \retval  TRUE   The LongNumber is valid.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID == STD_ON)
extern FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNIsValid
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) longNumber,
          uint32                                                    permittedMaxLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID == STD_ON) */

/** \brief  This function computes the binary representation of a number in LN representation.
 **
 ** This function computes the length of the binary representation of a number given in long number
 ** Representation. Since this function only uses the length information stored in
 ** Number[0] and the information stored in Number[Number[0]], the number must have been normalized
 ** beforehand, for example by a call to Crypto_xVIx_xAIx_LNNormalizeNumer(), to obtain a correct
 ** result.
 **
 ** \param[in]  number  A pointer to the number in long number representation,whose bit-length
 **                     shall be computed. It must be a normalized number.
 **
 ** \returns  The length of the binary representation of the number.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER == STD_ON)
extern FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNBitLengthOfNumber
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER == STD_ON) */

/** \brief  This function multiplies two numbers given in long number representation. The function
 **         is implemented in such a way that multiplicand, multiplicator and result can all point
 **         to the same memory location.
 **
 ** \param[out]  result         A pointer to the memory area which should cotain the long
 **                             number representation of the result of the multiplication.
 ** \param[in]   multiplicand   A pointer to the long number representation of the multiplicand.
 ** \param[in]   multiplicator  A pointer to the long number representation of the multiplicator.
 ** \param[in]   ctxPtr         A pointer to a context which holds the current state of the
 **                             multiplication.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMultiplyNumbers
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicand,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicator,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS == STD_ON) */

/** \brief  This function converts LNWordType RSAKeyMaterial to a DER formatted RsaKey.
 **
 ** \param[in]   key                    A pointer to the input key.
 ** \param[in]   keyLengthPtr           Pointer to the buffer which holds the length of the input key.
 ** \param[in]   isRSAPrivateKey        Is the input an encoding of an RSA private key?
 ** \param[out]  encodedRSAKeyPtr       Pointer to the buffer which holds the RSA key in LN format.
 ** \param[in]   lengthOfEncodedRSAKey  Length of the Key.
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EncodeKey
(
  P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key,
  P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyLengthPtr,
        boolean                                                             isRSAPrivateKey,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) encodedRSAKeyPtr,
        uint32                                                              lengthOfEncodedRSAKey
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON) */

/** \brief  This function converts a DER RsaPubKey to Modulus and Exponent of LNWordType.
 **
 ** The RSAPublicKey has to present in the correct Form as specified.
 ** RSAPublicKey ::= SEQUENCE {
 **                             modulus        INTEGER, -- n
 **                             publicExponent INTEGER  -- e
 **                           }
 ** The RSAPrivateKey has to present in the correct Form as specified.
 ** RSAPrivateKey ::= SEQUENCE {
 **                             version         INTEGER, -- Version
 **                             modulus         INTEGER, -- n
 **                             publicExponent  INTEGER, -- e
 **                             privateExponent INTEGER  -- d
 **                             prime1 INTEGER OPTIONAL, -- p
 **                             prime2 INTEGER OPTIONAL, -- q
 **                             exponent1 INTEGER OPTIONAL, -- d mod (p-1)
 **                             exponent2 INTEGER OPTIONAL, -- d mod (q-1)
 **                             coefficient INTEGER OPTIONAL -- (inverse of q) mod p}
 **
 ** \param[in]   key                    A pointer to the input key.
 ** \param[in]   keyLength              The length of the input key.
 ** \param[in]   isRSAPrivateKey        Is the input an encoding of an RSA private key?
 ** \param[out]  decodedRSAKeyPtr       A pointer to where the decoded key shall be stored.
 ** \param[out]  keyLenPtr              A pointer to Length of the Key.
 ** \param[in]   keyLenMaxBufferSize    The length of the configured key.
 **
 ** \return  Error value.
 **
 ** \retval  E_OK                        The conversion succeeded.
 ** \retval  E_NOT_OK                    Format is wrong.
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Format is wrong or output buffers are to small.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DecodeKey
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key,
          uint32                                                              keyLength,
          boolean                                                             isRSAPrivateKey,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) decodedRSAKeyPtr,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyLenPtr,
          uint32                                                              keyLenMaxBufferSize
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON) */

/** \brief  Creates a DER header for a sequence.
 **
 ** This function creates a DER header for an ASN.1 sequence. The header
 ** contains a byte which identifies the sequence followed by several bytes
 ** which encode the length of the payload of the sequence.
 **
 ** \param[out]  headerBuffer   Holds a pointer to the start of a buffer where the header
 **                             should be stored.
 ** \param[in]   payloadLength  Length of the payload of the sequence.
 **
 ** \returns  Length of the header in bytes.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE == STD_ON)
extern FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CommonDerHeaderSequence
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) headerBuffer,
        uint32                                        payloadLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE == STD_ON) */

/** \brief  Creates a DER header for an octet string.
 **
 ** This function creates a DER header for an ASN.1 octet string. The header
 ** contains a byte which identifies the octet string followed by several bytes
 ** which encode the length of the payload of the octet string.
 **
 ** \param[out]  headerBuffer   Holds a pointer to the start of a buffer where the header
 **                             should be stored.
 ** \param[in]   payloadLength  Length of the payload of the octet string.
 **
 ** \returns  Length of the header in bytes.
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING == STD_ON)
extern FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CommonDerHeaderOctetString
(
   P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) headerBuffer,
         uint32                                        payloadLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_LIB_LN_H */

/*==================[end of file]=================================================================*/

