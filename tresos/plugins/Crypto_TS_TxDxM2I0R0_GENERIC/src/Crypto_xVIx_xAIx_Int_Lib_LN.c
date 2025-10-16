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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_LN.c/0001,1 */

/*==================[deviations]==================================================================*/

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_LN.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_LN.c/0003,1 */

/*==================[macros]======================================================================*/

/* --- LN --------------------------------------------------------------------------------------- */
#if (defined CRYPTO_XVIX_XAIX_LN_MIN)
#error CRYPTO_XVIX_XAIX_LN_MIN is already defined
#endif
/** \brief  Returns the minimum of two values. **/
#define CRYPTO_XVIX_XAIX_LN_MIN(x, y) ((x) < (y)) ? (x) : (y)

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO is already defined
#endif
/** \brief   Macro representing if division by two is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO is already defined
#endif
/** \brief  Macro representing if multiply by two is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION is already defined
#endif
/** \brief  Macro representing if montgomery normalization is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION is already defined
#endif
/** \brief  Macro representing if montgomery reduction is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP is already defined
#endif
/** \brief  Macro representing if montgomery setup is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP STD_OFF
#endif

/* --- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY is already defined
#endif
/** \brief  Macro representing if modulo carry is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT is already defined
#endif
/** \brief  Macro representing if modulo shift is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 is already defined
#endif
/** \brief  Macro representing if modulo shift2 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT is already defined
#endif
/** \brief  Macro representing if modulo subtract is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 is already defined
#endif
/** \brief  Macro representing if modulo subtract2 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETT)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETT is already defined
#endif
/** \brief  Macro representing if modulo barrett is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETT STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETT STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETTSUBTRACTNUMBERS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETTSUBTRACTNUMBERS is already defined
#endif
/** \brief  Macro representing if modulo barrett subtract numbers is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETTSUBTRACTNUMBERS STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULOBARRETTSUBTRACTNUMBERS STD_OFF
#endif

/* --- DER -------------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING is already defined
#endif
/** \brief  Macro representing if DER length encoding is enabled
 **/
#if (   CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE    == STD_ON \
     || CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING == STD_ON \
    )
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH is already defined
#endif
/** \brief  Macro representing if DER get length is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER is already defined
#endif
/** \brief  Macro representing if DER get integer is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA is already defined
#endif
/** \brief  Macro representing if EncodeKey_Data  is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_OFF) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN is already defined
#endif
/** \brief  Macro representing if LNNumberToBEByteArray_DerDataLen is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_OFF) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA is already defined
#endif
/** \brief  Macro representing if LNNumberToBEByteArray_DerData is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_OFF) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH is already defined
#endif
/** \brief  Macro representing if EncodeKey_Length is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_OFF) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_RSA_KENUM_MAX)
#error CRYPTO_XVIX_XAIX_RSA_KENUM_MAX is already defined
#endif
/** \brief  Macro representing maximum number of fields RSA key material can have in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_KENUM_MAX 10U

#if (defined CRYPTO_XVIX_XAIX_RSA_VER_LEN)
#error CRYPTO_XVIX_XAIX_RSA_VER_LEN is already defined
#endif
/** \brief  Macro representing the version number length of RSA private key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_VER_LEN 3U

#if (defined CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE)
#error CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE is already defined
#endif
/** \brief  Macro representing version number length of RSA private key in LN format
 **/
#define CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE 2U

#if (defined CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE_INDEX)
#error CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE_INDEX is already defined
#endif
/** \brief  Macro representing version number index of RSA private key in LN format
 **/
#define CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE_INDEX 0U

#if (defined CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX)
#error CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX is already defined
#endif
/** \brief  Macro representing the sequence index of RSA key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX 0U

#if (defined CRYPTO_XVIX_XAIX_RSA_VER_INDEX)
#error CRYPTO_XVIX_XAIX_RSA_VER_INDEX is already defined
#endif
/** \brief  Macro representing version number sequence index of RSA private key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_VER_INDEX 1U

#if (defined CRYPTO_XVIX_XAIX_RSA_P1_INDEX)
#error CRYPTO_XVIX_XAIX_RSA_P1_INDEX is already defined
#endif
/** \brief  Macro representing sequence index of number prime1 of RSA private key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_P1_INDEX 5U

#if (defined CRYPTO_XVIX_XAIX_RSA_KEYDERLEN_INVALID)
#error CRYPTO_XVIX_XAIX_RSA_KEYDERLEN_INVALID is already defined
#endif
/** \brief  Macro representing invalid key length in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_KEYDERLEN_INVALID 0xFFFFFFFFU

#if (defined CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX)
#error CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX is already defined
#endif
/** \brief  Macro representing modulus sequence index of RSA key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX 2U

#if (defined CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE4)
#error CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE4 is already defined
#endif
/** \brief  Macro representing number of necessary elements in RSA private key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE4 4U

#if (defined CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE9)
#error CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE9 is already defined
#endif
/** \brief  Macro representing number of total elements in RSA private key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE9 9U

#if (defined CRYPTO_XVIX_XAIX_RSA_PUBLIC_NUMBER_KE2)
#error CRYPTO_XVIX_XAIX_RSA_PUBLIC_NUMBER_KE2 is already defined
#endif
/** \brief  Macro representing number of total elements in RSA public key in DER format
 **/
#define CRYPTO_XVIX_XAIX_RSA_PUBLIC_NUMBER_KE2 2U

#if (defined CRYPTO_XVIX_XAIX_ENCODE_ERROR)
#error CRYPTO_XVIX_XAIX_ENCODE_ERROR is already defined
#endif
/** \brief  Macro representing the error return code for EncodeKey API. **/
#define CRYPTO_XVIX_XAIX_ENCODE_ERROR CRYPTO_E_SMALL_BUFFER

/* --- LN --------------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_LN_LENGTH_POS)
#error CRYPTO_XVIX_XAIX_LN_LENGTH_POS is already defined
#endif
/** \brief  The position of the length in a number. **/
#define CRYPTO_XVIX_XAIX_LN_LENGTH_POS 0U

#if (defined CRYPTO_XVIX_XAIX_LN_LSW_POS)
#error CRYPTO_XVIX_XAIX_LN_LSW_POS is already defined
#endif
/** \brief  The position of the least significant word in a number. **/
#define CRYPTO_XVIX_XAIX_LN_LSW_POS 1U

#if (defined CRYPTO_XVIX_XAIX_LN_WORD_MAX)
#error CRYPTO_XVIX_XAIX_LN_WORD_MAX already defined
#endif
/** \brief  The maximal value which can be stored in an unsigned word. **/
#define CRYPTO_XVIX_XAIX_LN_WORD_MAX 0xFFFFFFFFU

#if (defined CRYPTO_XVIX_XAIX_MONT_CALCMU)
#error CRYPTO_XVIX_XAIX_MONT_CALCMU is already defined
#endif
/** \brief  Calculate number * rho. **/
#define CRYPTO_XVIX_XAIX_MONT_CALCMU(x, rho) (ctxPtr->montgomeryReductionC[(x)] * (rho))

#if (defined CRYPTO_XVIX_XAIX_LN_MONT_INNERMUL)
#error CRYPTO_XVIX_XAIX_LN_MONT_INNERMUL is already defined
#endif
/** \brief  Calculate the product and handle the carry. **/
#define CRYPTO_XVIX_XAIX_LN_MONT_INNERMUL(cPtr, carry, mu, ModPtr, Y)                     \
do                                                                                        \
{                                                                                         \
  Crypto_xVIx_xAIx_LNDoubleWordType Temp;                                                 \
  Temp       =   (  (Crypto_xVIx_xAIx_LNDoubleWordType) (cPtr)[0U]                        \
                  + (Crypto_xVIx_xAIx_LNDoubleWordType) (carry)                           \
                 )                                                                        \
               + (  ((Crypto_xVIx_xAIx_LNDoubleWordType) (mu))                            \
                  * (Crypto_xVIx_xAIx_LNDoubleWordType) (ModPtr)[(Y)]                     \
                 );                                                                       \
  (cPtr)[0U] = (Crypto_xVIx_xAIx_LNWordType) (Temp & CRYPTO_XVIX_XAIX_LN_WORD_MAX);       \
  (carry)    = (Crypto_xVIx_xAIx_LNWordType) (Temp >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS); \
}                                                                                         \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_LN_MONT_PROPCARRY)
#error CRYPTO_XVIX_XAIX_LN_MONT_PROPCARRY is already defined
#endif
/** \brief  Propagate the carry. **/
#define CRYPTO_XVIX_XAIX_LN_MONT_PROPCARRY(cPtr, carry)           \
do                                                                \
{                                                                 \
  Crypto_xVIx_xAIx_LNWordType Temp;                               \
  (cPtr)[0U]  = (Crypto_xVIx_xAIx_LNWordType)                     \
                (   (Crypto_xVIx_xAIx_LNWordType) (cPtr)[0U]      \
                  + (Crypto_xVIx_xAIx_LNWordType) (carry)         \
                );                                                \
  Temp        = (cPtr)[0U];                                       \
  (carry)     = (Crypto_xVIx_xAIx_LNWordType)                     \
                (                                                 \
                    ((Crypto_xVIx_xAIx_LNWordType) Temp)          \
                  < ((Crypto_xVIx_xAIx_LNWordType) (carry))       \
                );                                                \
}                                                                 \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_LN_MONT_POWOF2)
#error CRYPTO_XVIX_XAIX_LN_MONT_POWOF2 is already defined
#endif
/** \brief  Compute 2 ** exponent. **/
#define CRYPTO_XVIX_XAIX_LN_MONT_POWOF2(number, exponent)                                          \
do                                                                                                 \
{                                                                                                  \
  uint8                       carry      = (((exponent) % CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS) > 0U);\
  Crypto_xVIx_xAIx_LNWordType WordOffset = (Crypto_xVIx_xAIx_LNWordType)                           \
                                           (  (exponent)                                           \
                                            / ((uint32) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS)         \
                                           );                                                      \
  (number)[WordOffset + carry]           =    (Crypto_xVIx_xAIx_LNWordType) 1U                     \
                                           << ((exponent) % CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS);    \
  (number)[0U]                           = WordOffset + carry;                                     \
}                                                                                                  \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_LN_COMBA_FORWARD)
#error CRYPTO_XVIX_XAIX_LN_COMBA_FORWARD is already defined
#endif
/** \brief  Forward shift the carry word. **/
#define CRYPTO_XVIX_XAIX_LN_COMBA_FORWARD(c0, c1, c2) \
do                                                 \
{                                                  \
    (c0) = (c1);                                   \
    (c1) = (c2);                                   \
    (c2) = 0U;                                     \
}                                                  \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_LN_COMBA_MULADD)
#error CRYPTO_XVIX_XAIX_LN_COMBA_MULADD is already defined
#endif
/** \brief  Compute the column product. **/
#define CRYPTO_XVIX_XAIX_LN_COMBA_MULADD(I, J, c0, c1, c2)                                        \
do                                                                                                \
{                                                                                                 \
  Crypto_xVIx_xAIx_LNDoubleWordType Temp;                                                         \
  Temp = (Crypto_xVIx_xAIx_LNDoubleWordType) (c0) + (  (Crypto_xVIx_xAIx_LNDoubleWordType) (I)    \
                                                     * (Crypto_xVIx_xAIx_LNDoubleWordType) (J)    \
                                                    );                                            \
  (c0)  = (Crypto_xVIx_xAIx_LNWordType) (Temp & CRYPTO_XVIX_XAIX_LN_WORD_MAX);                    \
  Temp  = (Crypto_xVIx_xAIx_LNDoubleWordType) (c1) + (Temp >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS); \
  (c1)  = (Crypto_xVIx_xAIx_LNWordType) (Temp & CRYPTO_XVIX_XAIX_LN_WORD_MAX);                    \
  (c2) += (Crypto_xVIx_xAIx_LNWordType) (Temp >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS);              \
}                                                                                                 \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_LN_COMBA_SQRADD2)
#error CRYPTO_XVIX_XAIX_LN_COMBA_SQRADD2 is already defined
#endif
/** \brief  For squaring some of the terms are doubled. **/
#define CRYPTO_XVIX_XAIX_LN_COMBA_SQRADD2(I, J, c0, c1, c2)                                        \
do                                                                                                 \
{                                                                                                  \
  Crypto_xVIx_xAIx_LNDoubleWordType Temp, Temp2;                                                   \
  Temp  = ((Crypto_xVIx_xAIx_LNDoubleWordType) (I) * (Crypto_xVIx_xAIx_LNDoubleWordType) (J));     \
  Temp2 = (Crypto_xVIx_xAIx_LNDoubleWordType) (c0) + Temp;                                         \
  (c0)  = (Crypto_xVIx_xAIx_LNWordType) (Temp2 & CRYPTO_XVIX_XAIX_LN_WORD_MAX);                    \
  Temp2 = (Crypto_xVIx_xAIx_LNDoubleWordType) (c1) + (Temp2 >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS); \
  (c1)  = (Crypto_xVIx_xAIx_LNWordType) (Temp2 & CRYPTO_XVIX_XAIX_LN_WORD_MAX);                    \
  (c2) += (Crypto_xVIx_xAIx_LNWordType) (Temp2 >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS);              \
  Temp2 = (Crypto_xVIx_xAIx_LNDoubleWordType) (c0) + Temp;                                         \
  (c0)  = (Crypto_xVIx_xAIx_LNWordType) (Temp2 & CRYPTO_XVIX_XAIX_LN_WORD_MAX);                    \
  Temp2 = (Crypto_xVIx_xAIx_LNDoubleWordType) (c1) + (Temp2 >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS); \
  (c1)  = (Crypto_xVIx_xAIx_LNWordType) (Temp2 & CRYPTO_XVIX_XAIX_LN_WORD_MAX);                    \
  (c2) += (Crypto_xVIx_xAIx_LNWordType) (Temp2 >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS);              \
}                                                                                                  \
while (0U)

/* --- DER -------------------------------------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH == STD_ON)

#if (defined CRYPTO_XVIX_XAIX_DER_SEQUENCE_TAG)
#error CRYPTO_XVIX_XAIX_DER_SEQUENCE_TAG is already defined
#endif
/** \brief  The DER tag of a Sequence. **/
#define CRYPTO_XVIX_XAIX_DER_SEQUENCE_TAG 0x30U

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER == STD_ON)

#if (defined CRYPTO_XVIX_XAIX_DER_INTEGER_TAG)
#error CRYPTO_XVIX_XAIX_DER_INTEGER_TAG is already defined
#endif
/** \brief  The DER tag of an Integer. **/
#define CRYPTO_XVIX_XAIX_DER_INTEGER_TAG 0x02U

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER == STD_ON) */

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Helper function to reduce the complexity of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** This is used to reduce the related SW metric values.
 ** For more details see the documentation of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** \param[in,out]  number   A pointer to the long number representation of the number on which
 **                          the modulo operation should be performed and also the place where
 **                          the result should be stored.
 ** \param[in]      modulus  A pointer to the long number representation of the modulus.
 ** \param[in,out]  ctxPtr   A pointer to a context which holds the current state of the modulo
 **                          operation.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloShift
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT == STD_ON) */

/** \brief  Helper function to reduce the complexity of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** This is used to reduce the related SW metric values.
 ** For more details see the documentation of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** \param[in,out]  number   A pointer to the long number representation of the number on which
 **                          the modulo operation should be performed and also the place where the
 **                          result should be stored.
 ** \param[in]      modulus  A pointer to the long number representation of the modulus.
 ** \param[in,out]  ctxPtr   A pointer to a context which holds the current state of the modulo
 **                          operation.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloShift2
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 == STD_ON) */

/** \brief  Helper function to reduce the complexity of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** This is used to reduce the related SW metric values.
 ** For more details see the documentation of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** \param[in,out]  number   A pointer to the long number representation of the number on which the
 **                          modulo operation should be performed and also the place where the
 **                          result should be stored.
 ** \param[in]      modulus  A pointer to the long number representation of the modulus.
 ** \param[in,out]  ctxPtr   A pointer to a context which holds the current state of the modulo
 **                          operation.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloSubtract
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT == STD_ON) */

/** \brief  Helper function to reduce the complexity of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** This is used to reduce the related SW metric values.
 ** For more details see the documentation of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** \param[in,out]  number   A pointer to the long number representation of the number on which the
 **                          modulo operation should be performed and also the place where the result
 **                          should be stored.
 ** \param[in]      modulus  A pointer to the long number representation of the modulus.
 ** \param[in,out]  ctxPtr   A pointer to a context which holds the current state of the modulo
 **                          operation.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloSubtract2
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 == STD_ON) */

/** \brief  Helper function to reduce the complexity of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** This is used to reduce the related SW metric values.
 ** For more details see the documentation of the Crypto_xVIx_xAIx_LNModulo function.
 **
 ** \param[in,out]  number  A pointer to the long number representation of the number on which the
 **                         modulo operation should be performed and also the place where the result
 **                         should be stored.
 ** \param[in,out]  ctxPtr  A pointer to a context which holds the current state of the modulo
 **                         operation.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloCarry
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY == STD_ON) */

/** \brief  Multiply a number in long number representation by two.
 **
 ** \param[out]  result  The multiplied number.
 ** \param[in]   number  A number to multiplied.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMultByTwo
(
 P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
 P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO == STD_ON) */

/** \brief  This function calculates the rho value (equal to (-1 / modulo[0]) mod (word base)).
 **
 ** The implementation of the function assumes that the modulo is odd.
 **
 ** \param[in]   modulo  A pointer to the modulo used for the reduction.
 ** \param[out]  rho     A pointer to a memory location which will hold
 **                      the value of the calculated rho.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMontgomerySetup
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulo,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) rho
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP == STD_ON) */

/** \brief  This function computes R mod m, in order to convert the input number
 **         into Montgomery domain.
 **
 ** \param[in, out]  result  A pointer to number to be converted; This memory location will
 **                          also hold the conversion result.
 ** \param[in]       modulo  A pointer to the modulo used for the reduction.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMontgomeryNormalization
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulo
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION == STD_ON) */

/** \brief  This function computes the modular reduction of the number, in the Montgomery domain.
 **         into Montgomery domain.
 **
 ** \param[out]     remainderptr  A pointer to a memory location which will hold
 **                            the value of the remainder.
 ** \param[in]      number     A pointer to the number to be reduced.
 ** \param[in]      modulo     A pointer to the modulo used for the reduction.
 ** \param[in,out]  ctxPtr     A pointer to a context which holds temporary buffers needed
 **                            for reentrancy.
 ** \param[in]      rho        The rho value used to calculate the reduction.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMontgomeryReduction
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) remainderptr,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulo,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr,
          Crypto_xVIx_xAIx_LNWordType                               rho
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION == STD_ON) */

/** \brief  Divides a given value by two.
 **
 ** \param[in,out]  value     The byte array which holds the number to be divided.
 ** \param[in]      overflow  0 or 1 depending on what shall be added in the highest position.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNDivByTwo
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
        Crypto_xVIx_xAIx_LNWordType                               overflow
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO == STD_ON) */

/** \brief  Creates the part of a DER header which encodes the payload length.
 **
 ** The DER header of an ASN.1 element consists of several parts, one being
 ** the encoding of the length of the payload of the element. This function
 ** creates the length encoding given the payload length.
 **
 ** \param[out]  lengthEncodingBuffer  Holds a pointer to the start of a buffer where the
 **                                    length encoding should be stored.
 ** \param[in]   payloadLength         length of the payload of the ASN.1 element.
 **
 ** \returns  length of the length encoding in bytes.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DerLengthEncoding
(
   P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) lengthEncodingBuffer,
         uint32                                        payloadLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING == STD_ON) */

/** \brief  This function converts a DER encoded length into a length in uint32.
 **
 ** \param[in]   lengthOctets       A pointer to the beginning of the DER encoded length.
 ** \param[out]  result             A pointer to store the length in Byte.
 ** \param[in]   maxEncodingLength  The maximal size of the DER encoded length.
 **
 ** \return  The read Bytes, 0 represents an error.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DerGetLength
(
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) lengthOctets,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
          uint32                                    maxEncodingLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH == STD_ON) */

/** \brief  This function converts a DER encoded Integer to an array of type LNWordType.
 **
 ** \param[in]   data           A pointer to the beginning of the DER encoded data.
 ** \param[out]  integerArray   A pointer to the location where the result shall be stored.
 ** \param[in]   maxDataLength  The maximal size of the DER encoded data.
 **
 ** \return  The read Bytes, 0 represents an error.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DerGetInteger
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) data,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) integerArray,
          uint32                                                    maxDataLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER == STD_ON) */

/** \brief  Calculate length of RSA key in DER format
 **
 ** \param[in]     isRSAPrivateKey         Is the input an encoding of an RSA private key?
 ** \param[in,out] rsaKeyElementsPtr       Pointer to a buffer which holds the RSA key in DER format.
 ** \param[in,out] encodedRSAKeyPtr        Pointer to the buffer which holds the RSA key in LN format.
 ** \param[in]     lengthOfEncodedRSAKey   Length of RSA key in DER format.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EncodeKey_Length
(
    boolean                                                                   isRSAPrivateKey,
    Crypto_xVIx_xAIx_RsaKeyElementInfo_Type*                                  rsaKeyElementsPtr,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) encodedRSAKeyPtr,
    uint32                                                                    lengthOfEncodedRSAKey
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH == STD_ON) */

/** \brief  Calculate the DER encoding of RSA key in LN format
 **
 ** \param[in,out] number       Pointer to the buffer which holds the RSA key in LN format.
 ** \param[in,out] array        Pointer to a buffer which holds the integer value of RSA key in DER format.
 ** \param[in]     dataLength   Variable which holds the length of sequence of RSA key in DER format.
 ** \param[in]     signLength   Variable which holds the sign value of sequence of RSA key in DER format.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerData
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
          uint32                                                              dataLength,
          uint8                                                               signLength
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA == STD_ON) */

/** \brief  Calculate length of value of sequence in a RSA key
 **
 ** \param[in,out] number          Pointer to the buffer which holds the RSA key in LN format.
 ** \param[in,out] dataLengthPtr   Pointer to a buffer which holds the length of sequence of RSA key in DER format.
 ** \param[in,out] signLengthPtr   Pointer to the buffer which holds the sign value of sequence of RSA key in DER format.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerDataLen
(
    P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint16,                        AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) dataLengthPtr,
    P2VAR(uint8,                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) signLengthPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN == STD_ON) */

/** \brief  Encode the value of RSA key components in DER format
 **
 ** \param[in,out] key                     Pointer to the buffer which holds the RSA key in DER format.
 ** \param[in]     isRSAPrivateKey         Is the input an encoding of an RSA private key?
 ** \param[in,out] encodedRSAKeyPtr        Pointer to the buffer which holds the RSA key in LN format.
 ** \param[in]     lengthOfEncodedRSAKey   Length of RSA key in DER format.
 ** \param[in,out] rsaKeyElementsPtr       Pointer to a buffer which holds the RSA key in DER format.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EncodeKey_Data
(
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key,
          boolean                                                             isRSAPrivateKey,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) encodedRSAKeyPtr,
          uint32                                                              lengthOfEncodedRSAKey,
          Crypto_xVIx_xAIx_RsaKeyElementInfo_Type*                            rsaKeyElementsPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA == STD_ON) */
#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*---Crypto_xVIx_xAIx_LNNormalizeNumber-----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNormalizeNumber
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number
)
{
  Crypto_xVIx_xAIx_LNWordType i = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];

  while (((Crypto_xVIx_xAIx_LNWordType) 0U == number[i]) && ((Crypto_xVIx_xAIx_LNWordType) 0U < i))
  {
    i--;
  }
  number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = i;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSquareComba---------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNSquareComba/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA  == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSquareComba
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  Crypto_xVIx_xAIx_LNWordType i, j, tx, ty, numMultiplications;
  Crypto_xVIx_xAIx_LNWordType multiplicandLength = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
  Crypto_xVIx_xAIx_LNWordType prodLen            = multiplicandLength + multiplicandLength;
  Crypto_xVIx_xAIx_LNWordType c0                 = 0U;
  Crypto_xVIx_xAIx_LNWordType c1                 = 0U;
  Crypto_xVIx_xAIx_LNWordType c2                 = 0U;

  /* reset ctx variable */
  TS_MemBZero(ctxPtr->localResultSquareComba,
              CRYPTO_XVIX_XAIX_RESULT_SQUARE_COMBA_LENGTH
             );

  for (i = 0U; i < prodLen; i++)
  {
    ty = CRYPTO_XVIX_XAIX_LN_MIN((multiplicandLength - 1U), i);
    tx = (i - ty);

    numMultiplications
    = CRYPTO_XVIX_XAIX_LN_MIN((Crypto_xVIx_xAIx_LNWordType)(multiplicandLength - tx),
                               (Crypto_xVIx_xAIx_LNWordType)(ty + 1U)
                              );
    numMultiplications = CRYPTO_XVIX_XAIX_LN_MIN(numMultiplications, (((ty - tx) + 1U) >> 1U));

    /* Forward shift the carry word */
    CRYPTO_XVIX_XAIX_LN_COMBA_FORWARD(c0, c1, c2);

    for (j = 0U; j < numMultiplications; j++)
    {
      /* Double the terms */
      CRYPTO_XVIX_XAIX_LN_COMBA_SQRADD2((number[(tx + j) + 1U]),
                                     (number[(ty - j) + 1U]),
                                     c0,
                                     c1,
                                     c2
                                    );
    }

    if ((i & 1U) == 0U)
    {
      Crypto_xVIx_xAIx_LNWordType Offset = (i >> 1U) + (Crypto_xVIx_xAIx_LNWordType) 1U;
      Crypto_xVIx_xAIx_LNWordType ADp    = number[Offset];
      CRYPTO_XVIX_XAIX_LN_COMBA_MULADD((ADp), (number[Offset]), c0, c1, c2);
    }

    /* Propagate carry */
    ctxPtr->localResultSquareComba[i + 1U] = c0;
  }

  ctxPtr->localResultSquareComba[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
  = multiplicandLength + multiplicandLength;

  Crypto_xVIx_xAIx_LNNormalizeNumber(ctxPtr->localResultSquareComba);

  TS_MemCpy(result,
            ctxPtr->localResultSquareComba,
            ((  (uint32) ctxPtr->localResultSquareComba[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
              + (uint32) 1U
             ) * (uint32) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES
            )
           );
}
#endif /* CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA  == STD_ON */

/*---Crypto_xVIx_xAIx_LNIsValid-------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNIsValid/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID == STD_ON)
FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNIsValid
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) longNumber,
          uint32                                                    permittedMaxLength
)
{
  boolean status = FALSE;
  if (   (longNumber[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] < permittedMaxLength)
      && (   (0U != longNumber[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
          && (0U != longNumber[longNumber[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]])
         )
     )
  {
    status = TRUE;
  }
  return status;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID == STD_ON) */

/*---Crypto_xVIx_xAIx_LNBitLengthOfNumber---------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNBitLengthOfNumber/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER == STD_ON)
FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNBitLengthOfNumber
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number
)
{
  Crypto_xVIx_xAIx_LNWordType tempWord; /* the most significant word of "number" */
  Crypto_xVIx_xAIx_LNWordType length; /* the length of the number */

  if (0U == number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
  {
    length = 0U;
  }
  else
  {
    /* All words of the number except for the most significant word contribute
       CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS bits to the length of the number. */
    length = (Crypto_xVIx_xAIx_LNWordType)
             (  number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
              - (Crypto_xVIx_xAIx_LNWordType) 1U
             ) * (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS;

    /* We compute the amount of bits which the most significant word of
       "number" contributes to its length. In each round of this for-loop,
       the most significant word is shifted one bit to the right and we test
       it still is non-zero. */
    for (tempWord = number[number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]];
         ((Crypto_xVIx_xAIx_LNWordType)0U < tempWord);
         tempWord >>= 1U
        )
    {
      length++;
    }
  }
  return length;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER == STD_ON) */

/*---Crypto_xVIx_xAIx_LNMultiplyNumbers-----------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNMultiplyNumbers/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMultiplyNumbers
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicand,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicator,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* check if size is ok*/
  Crypto_xVIx_xAIx_LNWordType i, j, numMultiplications, tx, ty;
  Crypto_xVIx_xAIx_LNWordType multiplicandLength  = multiplicand[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
  Crypto_xVIx_xAIx_LNWordType multiplicatorLength = multiplicator[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
  Crypto_xVIx_xAIx_LNWordType prodLen             = multiplicandLength + multiplicatorLength;

  Crypto_xVIx_xAIx_LNWordType c0 = 0U;
  Crypto_xVIx_xAIx_LNWordType c1 = 0U;
  Crypto_xVIx_xAIx_LNWordType c2 = 0U;

  /* reset ctx variable */
  TS_MemBZero(ctxPtr->localResultMultiply, CRYPTO_XVIX_XAIX_RESULT_MULTI_LENGTH);
  for (i = 0U; i < prodLen; i++)
  {
    /* Word offset of the multiplicator */
    ty = CRYPTO_XVIX_XAIX_LN_MIN((multiplicatorLength - 1U), i);
    /* Word offset of the multiplicand */
    tx = i - ty;

    numMultiplications = CRYPTO_XVIX_XAIX_LN_MIN((Crypto_xVIx_xAIx_LNWordType)
                                                  (multiplicandLength - tx),
                                                  (ty + 1U)
                                                 );

    /* Forward shift the carry word */
    CRYPTO_XVIX_XAIX_LN_COMBA_FORWARD(c0, c1, c2);

    for (j = 0U; j < numMultiplications; j++)
    {
      /* Compute the column product */
      CRYPTO_XVIX_XAIX_LN_COMBA_MULADD((multiplicand[(tx + j) + 1U]),
                                    (multiplicator[(ty - j) + 1U]),
                                    c0,
                                    c1,
                                    c2
                                   );
    }

    /* Propagate carry */
    ctxPtr->localResultMultiply[i + 1U] = c0;
  }

  ctxPtr->localResultMultiply[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] =   multiplicandLength
                                                                + multiplicatorLength;

  Crypto_xVIx_xAIx_LNNormalizeNumber(ctxPtr->localResultMultiply);

  TS_MemCpy(result,
            ctxPtr->localResultMultiply,
            (  (  (uint32) ctxPtr->localResultMultiply[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
                + (uint32) 1U
               )
             * (uint32) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES
            )
           );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSubtraction---------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSubtraction
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) minuend,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) subtrahend
)
{
  Crypto_xVIx_xAIx_LNDoubleWordType tempDifference;
  Crypto_xVIx_xAIx_LNWordType       loopCount;
  Crypto_xVIx_xAIx_LNWordType       borrow = 0U;

  /* Calculate the differences up to the maximum available number of common digits
   * (subtrahend is either smaller or equal to minuend)
   */
  for (loopCount = CRYPTO_XVIX_XAIX_LN_LSW_POS;
       loopCount <= subtrahend[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
       loopCount++
      )
  {
    /* Calculate the difference */
    tempDifference =   (  (Crypto_xVIx_xAIx_LNDoubleWordType) minuend[loopCount]
                        - (Crypto_xVIx_xAIx_LNDoubleWordType) subtrahend[loopCount]
                       )
                     - (Crypto_xVIx_xAIx_LNDoubleWordType) borrow;

    /* Extract the borrow bit */
    borrow = (  (Crypto_xVIx_xAIx_LNWordType) (  tempDifference
                                             >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS)
              & 1U
             );

    /* The result of the column is equal to the lower part of the difference */
    result[loopCount] = (Crypto_xVIx_xAIx_LNWordType) tempDifference;
  }

  /* Copy the remaining digits */
  for (; loopCount <= minuend[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; loopCount++)
  {
    /* Calculate the difference */
    tempDifference =   (Crypto_xVIx_xAIx_LNDoubleWordType) minuend[loopCount]
                     - (Crypto_xVIx_xAIx_LNDoubleWordType) borrow;

    /* Extract the borrow bit */
    borrow = (  (Crypto_xVIx_xAIx_LNWordType) (   tempDifference
                                             >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS)
              & 1U
             );

    /* The result of the column is equal to the lower part of the difference */
    result[loopCount] = (Crypto_xVIx_xAIx_LNWordType) tempDifference;
  }

  /* Set the length of the result */
  result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = loopCount - (Crypto_xVIx_xAIx_LNWordType) 1U;

  Crypto_xVIx_xAIx_LNNormalizeNumber(result);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION == STD_ON) */

/*---Crypto_xVIx_xAIx_LNCompareNumbers------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNCompareNumbers/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS == STD_ON)
FUNC(Crypto_xVIx_xAIx_LNCompareReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNCompareNumbers
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number1,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number2
)
{
  Crypto_xVIx_xAIx_LNWordType numberPos; /* the current position in the numbers */
  Crypto_xVIx_xAIx_LNCompareReturnType compare; /* the result of the comparison */

  /* First, the lengths of the two numbers are compared. If we find a
     difference here, the comparison is over. */
  if (number1[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] > number2[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
  {
    compare = CRYPTO_XVIX_XAIX_LN_E_LARGER;
  }
  else
  if (number1[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] < number2[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
  {
    compare = CRYPTO_XVIX_XAIX_LN_E_SMALLER;
  }
  else
  {
    /* Both numbers have an identical length. Now, we compare the words of
       those numbers from most to least significant word. */

    compare = CRYPTO_XVIX_XAIX_LN_E_EQUAL;

    for (numberPos = number1[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
         (numberPos > (Crypto_xVIx_xAIx_LNWordType) 0U) && (CRYPTO_XVIX_XAIX_LN_E_EQUAL == compare);
         numberPos--
        )
    {
      if (number1[numberPos] > number2[numberPos])
      {
        compare = CRYPTO_XVIX_XAIX_LN_E_LARGER;
      }
      else
      if (number1[numberPos] < number2[numberPos])
      {
        compare = CRYPTO_XVIX_XAIX_LN_E_SMALLER;
      }
      else
      {
        /* Do nothing. The numbers are identical up to here and this is
           reflected by the fact that "compare" is EQUAL at the moment. */
      }
    }
  }
  return compare;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS == STD_ON) */

/*---Crypto_xVIx_xAIx_LNModulo--------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNModulo/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNModulo
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  uint32 lengthOfNum; /* the length of number in bits */
  uint32 lengthOfMod; /* the length of modulus in bits */

  /* We compute the length of number in bits. */
  lengthOfNum = Crypto_xVIx_xAIx_LNBitLengthOfNumber(number);

  /* We compute the length of modulus in bits. */
  lengthOfMod = Crypto_xVIx_xAIx_LNBitLengthOfNumber(modulus);

  /* We only do something if number is at least as long as modulus.
     Otherwise, result = number mod modulus = number.
     If the modulus is 0 -> the result is 0. */
  if (0U == lengthOfMod)
  {
    number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = lengthOfMod;
  }
  else
  if (lengthOfMod <= lengthOfNum)
  {
    /* We compute the length difference of number and modulus in bits.
       We add 1 because we will subtract 1 at the beginning of the
       do-while-loop. */
    ctxPtr->lengthDifference = (Crypto_xVIx_xAIx_LNWordType) (lengthOfNum - lengthOfMod + 1U);

    /* Binary division: We shift modulus an amount of
       ctxPtr->lengthDifference bits to the left. Then we check whether
       number is at least as large as the shifted modulus. If this is
       the case we subtract the shifted modulus from number. We decrease
       ctxPtr->lengthDifference by one and repeat this game until
       ctxPtr->lengthDifference is 0.
       The modulus is not really shifted but the individual words of the
       shifted modulus are computed when they are needed and stored in
       ctxPtr->wordOfShiftedMod. */
    do
    {
      Crypto_xVIx_xAIx_LNSModuloShift(number, modulus, ctxPtr);
    }
    while ((Crypto_xVIx_xAIx_LNWordType) 0U < (ctxPtr->lengthDifference));
    Crypto_xVIx_xAIx_LNNormalizeNumber(number);
  }
  else
  {
    Crypto_xVIx_xAIx_LNNormalizeNumber(number);
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO == STD_ON) */

/*---Crypto_xVIx_xAIx_LNBEByteArrayToNumber-------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNBEByteArrayToNumber/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNBEByteArrayToNumber
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
          uint32                                                    arrayLength,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
          Crypto_xVIx_xAIx_LNWordType                               numberLength
)
{
   Crypto_xVIx_xAIx_LNWordType numberPos; /* the position in "number" */
   Crypto_xVIx_xAIx_LNWordType wordPos;  /* the byte position in the current word of "number" */
   uint32                      arrayPos; /* the position in the byte array */
   Std_ReturnType              retVal = E_NOT_OK;

  if (0U != arrayLength)
  {
    if (numberLength < (CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(arrayLength) + 1U))
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* We cycle through all of the words of the resulting number */
      for (numberPos = 1U;
           numberPos <= CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(arrayLength);
           numberPos++
          )
      {
        /* The current word of number is initialized to "0". */
        number[numberPos] = 0U;

        /* "CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES" bytes of the array are combined to make up
           the current word of the number. */
        for (wordPos = 0U;
             wordPos < (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
             wordPos++
            )
        {
          /* We compute the current position in "array". */
          arrayPos  = CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
          arrayPos *= ((uint32) numberPos - 1U);
          arrayPos += (uint32) wordPos;
          arrayPos  = (arrayLength - arrayPos) - 1U;

          if (arrayPos < arrayLength)
          {
            /* If we are not over the edge of "array", we incorporate the
               current byte of "array" into the current word of the number. */
            number[numberPos] |= (Crypto_xVIx_xAIx_LNWordType)
                                 (   (Crypto_xVIx_xAIx_LNWordType) array[arrayPos]
                                  << (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType) wordPos << 3U)
                                 );
          }
        }
      }

      number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(arrayLength);

      Crypto_xVIx_xAIx_LNNormalizeNumber(number);
      retVal = E_OK;
    }
  }
  else
  {
    if (numberLength == 0U)
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* The length of "array" is "0", so the resulting number is also "0". */
      number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = 0U;
      retVal = E_OK;
    }
  }
  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER == STD_ON) */

/*---Crypto_xVIx_xAIx_LNNumberToBEByteArray-------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNNumberToBEByteArray/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToBEByteArray
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) arrayLengthPtr
)
{
  Crypto_xVIx_xAIx_LNWordType numberPos; /* the position in "number" */
  Crypto_xVIx_xAIx_LNWordType wordPos; /* the byte position in the current word of "number" */
  Crypto_xVIx_xAIx_LNWordType arrayPos; /* the position in the byte array */
  Std_ReturnType              retVal = E_OK;

  if (  ((*arrayLengthPtr) / CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES)
      < number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
     )
  {
    retVal = E_NOT_OK;
  }
  else
  {
    /* We cycle through all the words of "number". */
    for (numberPos = (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_LSW_POS;
         numberPos <= number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
         numberPos++
        )
    {
      /* Begin computing the index of the byte which will be updated. */
      arrayPos  = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
      arrayPos -= numberPos;
      arrayPos += (Crypto_xVIx_xAIx_LNWordType) 1U;
      arrayPos *= (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;

      /* Each word of "number" is split into "CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES" bytes of
         "array". */
      for (wordPos = (Crypto_xVIx_xAIx_LNWordType) 0U;
           (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES > wordPos;
           wordPos++
          )
      {
        /* Finish computing the index of the byte which will be updated. */
        arrayPos -= (Crypto_xVIx_xAIx_LNWordType) 1U;

        /* The current byte of "array" is computed from the current word of
           "number". */
        array[arrayPos] = (uint8) (number[numberPos] >> (uint8) ((uint8) wordPos << 3U));
      }
    }

    /* Return the correct length of the byte array. */
    *arrayLengthPtr = (uint16) (  number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
                                * (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES
                               );
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY == STD_ON) */

/*---Crypto_xVIx_xAIx_LNLEByteArrayToNumber-------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNLEByteArrayToNumber/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNLEByteArrayToNumber
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
          uint32                                                              arrayLength,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
          Crypto_xVIx_xAIx_LNWordType                                         numberLength
)
{
  Crypto_xVIx_xAIx_LNWordType numberPos; /* the position in "number" */
  Crypto_xVIx_xAIx_LNWordType wordPos; /* byte position in the current word of "number" */
  uint16                      arrayPos; /* the position in the byte array */
  Std_ReturnType              retVal = E_NOT_OK;

  if (0U != arrayLength)
  {
    /* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNLEByteArrayToNumber/0004,1 */
    if (numberLength < (CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(arrayLength) + 1U))
    {
      retVal = E_NOT_OK;
    }
    else
    {
      retVal = E_OK;
      /* We cycle through all of the words of the resulting number. */
      for (numberPos = (Crypto_xVIx_xAIx_LNWordType) 1U;
           numberPos <= CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(arrayLength);
           numberPos++
          )
      {
        /* The current word of number is initialized to "0". */
        number[numberPos] = (Crypto_xVIx_xAIx_LNWordType) 0U;

        /* "CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES" bytes of the array are combined to make
           up the current word of the number. */
        for (wordPos = (Crypto_xVIx_xAIx_LNWordType) 0U;
             wordPos < (Crypto_xVIx_xAIx_LNWordType)CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
             wordPos++
            )
        {
          arrayPos  = (uint16) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
          arrayPos *= (uint16) (numberPos - (Crypto_xVIx_xAIx_LNWordType) 1U);
          arrayPos += (uint16) wordPos;
          /* We have already checked that the number is large enough to store the whole byte array
             so we can add the current byte to the position in the number. */
          number[numberPos] |= (Crypto_xVIx_xAIx_LNWordType)
                               (   (Crypto_xVIx_xAIx_LNWordType) array[arrayPos]
                                << (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType)
                                                                  wordPos << 3U
                                                                 )
                               );
        }
      }

      number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(arrayLength);

      Crypto_xVIx_xAIx_LNNormalizeNumber(number);
    }
  }
  else
  {
    retVal = E_OK;
    if (numberLength == 0U)
    {
      /* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNLEByteArrayToNumber/0002,1 */
      retVal = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNLEByteArrayToNumber/0003,1 */
      /* The length of "array" is "0U", so the resulting number is also "0U". */
      number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = (Crypto_xVIx_xAIx_LNWordType) 0U;
    }
  }
  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER == STD_ON) */

/*---Crypto_xVIx_xAIx_LNNumberToLEByteArray-------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNNumberToLEByteArray/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToLEByteArray
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) arrayLengthPtr
)
{
  Crypto_xVIx_xAIx_LNWordType numberPos; /* the position in "number" */
  Crypto_xVIx_xAIx_LNWordType wordPos; /* byte position in the current word of "number" */
  Crypto_xVIx_xAIx_LNWordType arrayPos; /* the position in the byte array */
  Std_ReturnType              retVal = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNNumberToLEByteArray/0002,1 */
  if (  ((*arrayLengthPtr) / CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES)
      < number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
     )
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
    /* we cycle through all the words of "number". */
    for (numberPos = (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_LSW_POS;
         numberPos <= number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
         numberPos++
        )
    {
      /* Begin computing the index of the byte which will be updated. */
      arrayPos  = numberPos;
      arrayPos -= (Crypto_xVIx_xAIx_LNWordType) 1U;
      arrayPos *= (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;

      /* Each word of "number" is split into "CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES" bytes
         of "array". */
      for (wordPos = (Crypto_xVIx_xAIx_LNWordType) 0U;
           wordPos < (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
           wordPos++
          )
      {
        /* The current byte of "array" is computed from the current word of
           "number". */
        array[arrayPos] = (uint8) (   number[numberPos]
                                   >> (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType)
                                                                     wordPos << 3U
                                                                    )
                                  );

        /* Finish computing the index of the byte which will be updated. */
        arrayPos += (Crypto_xVIx_xAIx_LNWordType) 1U;
      }
    }

    /* Return the correct length of the byte array. */
    *arrayLengthPtr = (uint16) (  number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]
                                * (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES
                               );
  }
  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY == STD_ON) */

/*---Crypto_xVIx_xAIx_LNAddition------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNAddition/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION == STD_ON)
FUNC(uint8, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNAddition
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sum,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2
)
{
  const Crypto_xVIx_xAIx_LNWordType* largestOperand;

  Crypto_xVIx_xAIx_LNDoubleWordType tempSum;
  Crypto_xVIx_xAIx_LNWordType loopCount, minLength, maxLength, carry = 0U;

  /* Find the larger of the two operands */
  if (addend1[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] > addend2[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
  {
    minLength                       = addend2[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    maxLength                       = addend1[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    largestOperand = addend1;
  }
  else
  {
    minLength                       = addend1[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    maxLength                       = addend2[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    largestOperand = addend2;
  }

  /* Calculate the sums up to the maximum available number of common digits */
  for (loopCount = CRYPTO_XVIX_XAIX_LN_LSW_POS; loopCount <= minLength; loopCount++)
  {
    /* Calculate the sum */
    tempSum =   (Crypto_xVIx_xAIx_LNDoubleWordType) addend1[loopCount]
              + (Crypto_xVIx_xAIx_LNDoubleWordType) addend2[loopCount]
              + (Crypto_xVIx_xAIx_LNDoubleWordType) carry;

    /* The result of the column is equal to the lower part of the difference */
    sum[loopCount] = (Crypto_xVIx_xAIx_LNWordType) tempSum;

    /* Extract the carry bit */
    carry = (Crypto_xVIx_xAIx_LNWordType) (tempSum >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS);
  }

  /* Copy the remaining digits */
  for (; loopCount <= maxLength; loopCount++)
  {
    /* Calculate the sum */
    tempSum =   (Crypto_xVIx_xAIx_LNDoubleWordType) largestOperand[loopCount]
              + (Crypto_xVIx_xAIx_LNDoubleWordType) carry;

    /* The result of the column is equal to the lower part of the difference */
    sum[loopCount] = (Crypto_xVIx_xAIx_LNWordType) tempSum;

    /* Extract the carry bit */
    carry = (Crypto_xVIx_xAIx_LNWordType) (tempSum >> CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS);

  }

  sum[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = maxLength;

  return (uint8) carry;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION == STD_ON) */

/*---Crypto_xVIx_xAIx_LNAdditionModular-----------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNAdditionModular/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNAdditionModular
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sum,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus
)
{
  Crypto_xVIx_xAIx_LNWordType i;
  uint8                       carry = 0U;

  carry = Crypto_xVIx_xAIx_LNAddition(sum, addend1, addend2);

  for (i = (sum[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] + 1U);
       i <= modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
       i++
      )
  {
    sum[i] = 0U;
  }

  /* check if there is a carry after the last addition */

  /* if the carry is 1 and the sum is smaller then the modulus, the carry can
     be added in the highest position. */
  if (   (sum[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] < modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
      && (1U == carry)
     )
  {
    sum[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]++;
    sum[sum[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]] = 1U;
  }
  /* else the carry is set to one. Then the sum length equals the modulus
     length and it is necessary to subtract. Also, if the length of the sum
     equals the modulus and the most significant position is larger than the
     modulus a subtraction is needed. */
  else
  if (   (CRYPTO_XVIX_XAIX_LN_E_SMALLER != Crypto_xVIx_xAIx_LNCompareNumbers(sum, modulus))
      || (1U == carry)
     )
  {
    do
    {
      Crypto_xVIx_xAIx_LNSubtraction(sum, sum, modulus);
    }
    while (CRYPTO_XVIX_XAIX_LN_E_SMALLER != Crypto_xVIx_xAIx_LNCompareNumbers(sum, modulus));
  }
  else
  {
    /* Caution: this "else" is required by MISRA-C:2012 */
  }
  Crypto_xVIx_xAIx_LNNormalizeNumber(sum);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSubtractionModular--------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSubtractionModular
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) difference,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) minuend,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) subtrahend,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus
)
{
  Crypto_xVIx_xAIx_LNWordType i;
  uint8                       carry = 0U;
  uint8                       borrow = 0U;
  Crypto_xVIx_xAIx_LNWordType tmp;
  Crypto_xVIx_xAIx_LNWordType tmp2;

  for (i = CRYPTO_XVIX_XAIX_LN_LSW_POS; i <= modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i++)
  {
    if (i > minuend[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
    {
      tmp = 0U;
    }
    else
    {
      tmp = minuend[i];
    }
    if (i > subtrahend[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
    {
      tmp2 = 0U;
    }
    else
    {
      tmp2 = subtrahend[i];
    }
    difference[i] = (tmp - tmp2) - borrow;

    if (difference[i] >= tmp)
    {
      if ((0U != tmp2) || ( 0U != borrow))
      {
        borrow = 1U;
      }
    }
    else
    {
      borrow = 0U;
    }
  }

  difference[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];

  /* if the number is "negative", which equals a remaining borrow, the modulus
     must be added. */
  if (1U == borrow)
  {
    for (i = 1U; i <= modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i++)
    {
      tmp           = difference[i];
      difference[i] = (tmp + carry) + modulus[i];

      if ((difference[i] <= tmp) && (difference[i] <= modulus[i]))
      {
        carry = 1U;
      }
      else
      {
        carry = 0U;
      }
    }
  }

  Crypto_xVIx_xAIx_LNNormalizeNumber(difference);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR == STD_ON) */

/*---Crypto_xVIx_xAIx_LNInversion-----------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNInversion/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNInversion
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) invValue,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1Value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2Value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3Value,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  Crypto_xVIx_xAIx_LNWordType addResult, i;
  Crypto_xVIx_xAIx_LNCompareReturnType compNumRes;

  /* Copy the input */
  /* u = a */
  for (i = 0U; i <= value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i++)
  {
    tmp1Value[i] = value[i];
  }
  /* v = p */
  for (i = 0U; i <= modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i++)
  {
    tmp2Value[i] = modulus[i];
  }

  /* x1 = 1 */
  tmp3Value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = 1U;
  tmp3Value[CRYPTO_XVIX_XAIX_LN_LSW_POS]    = 1U;

  /* x2 = 0 */
  invValue[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = 0U;
  invValue[CRYPTO_XVIX_XAIX_LN_LSW_POS]    = 0U;

  /* while (u != 1 and v != 1) */
  while (   (   !(   (1U == tmp1Value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
                  && (1U == tmp1Value[CRYPTO_XVIX_XAIX_LN_LSW_POS]   )
                 )
             && !(   (1U == tmp2Value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
                  && (1U == tmp2Value[CRYPTO_XVIX_XAIX_LN_LSW_POS]   )
                 )
            )
         && (0U != tmp1Value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
        )
  {
    /* while u is even */
    while (0U == (tmp1Value[CRYPTO_XVIX_XAIX_LN_LSW_POS] & 1U))
    {
      /* u = u/2 */
      Crypto_xVIx_xAIx_LNDivByTwo(tmp1Value, 0U);

      /* if x1 is even */
      if (0U == (tmp3Value[CRYPTO_XVIX_XAIX_LN_LSW_POS] & 1U))
      {
        /* x1 = x1 / 2 */
        Crypto_xVIx_xAIx_LNDivByTwo(tmp3Value, 0U);
      }
      else
      {
        /* x1 = (x1 + p) / 2 */
        addResult = Crypto_xVIx_xAIx_LNAddition(tmp3Value, tmp3Value, modulus);
        Crypto_xVIx_xAIx_LNDivByTwo(tmp3Value, addResult);
      }
    }

    /* while v is even */
    while (0U == (tmp2Value[CRYPTO_XVIX_XAIX_LN_LSW_POS] & 1U))
    {
      /* v = v / 2 */
      Crypto_xVIx_xAIx_LNDivByTwo(tmp2Value, 0U);

      /* if x2 is even */
      if (0U == (invValue[CRYPTO_XVIX_XAIX_LN_LSW_POS] & 1U))
      {
        /* x2 = x2 / 2 */
        Crypto_xVIx_xAIx_LNDivByTwo(invValue, 0U);
      }
      else
      {
        /* x2 = (x2 + p) / 2 */
        addResult = Crypto_xVIx_xAIx_LNAddition(invValue, invValue, modulus);
        Crypto_xVIx_xAIx_LNDivByTwo(invValue, addResult);
      }
    }

    /* if (u >= v) */
    compNumRes = Crypto_xVIx_xAIx_LNCompareNumbers(tmp1Value, tmp2Value);
    if ((CRYPTO_XVIX_XAIX_LN_E_LARGER == compNumRes) || (CRYPTO_XVIX_XAIX_LN_E_EQUAL == compNumRes))
    {
      /* u = u - v */
      Crypto_xVIx_xAIx_LNSubtractionModular(tmp1Value, tmp1Value, tmp2Value, modulus);
      /* x1 = x1 - x2 */
      Crypto_xVIx_xAIx_LNSubtractionModular(tmp3Value, tmp3Value, invValue, modulus);
    }
    else
    {
      /* v = v - u */
      Crypto_xVIx_xAIx_LNSubtractionModular(tmp2Value, tmp2Value, tmp1Value, modulus);
      /* x2 = x2 - x1 */
      Crypto_xVIx_xAIx_LNSubtractionModular(invValue, invValue, tmp3Value, modulus);
    }
  }

  /* if (u == 1) */
  if (   (1U == tmp1Value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
      && (1U == tmp1Value[CRYPTO_XVIX_XAIX_LN_LSW_POS]   )
     )
  {
    /* return (x1 mod p) */
    for (i = 0U; i <= tmp3Value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i++)
    {
      invValue[i] = tmp3Value[i];
    }
  }

  Crypto_xVIx_xAIx_LNModulo(invValue, modulus, ctxPtr);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION == STD_ON) */

/*---Crypto_xVIx_xAIx_LNModExp--------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNModExp
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) base,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) exponent,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  uint32                      bits = Crypto_xVIx_xAIx_LNBitLengthOfNumber(exponent);
  Crypto_xVIx_xAIx_LNWordType rho;
  Crypto_xVIx_xAIx_LNWordType i;

  /* reset ctx variable */
  TS_MemBZero(ctxPtr->modExpLocalBase,CRYPTO_XVIX_XAIX_LN_MOD_EXP_LENGTH);
  for (i = 0U; i <= base[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i++)
  {
    ctxPtr->modExpLocalBase[i] = base[i];
  }

  /* Calculate rho */
  Crypto_xVIx_xAIx_LNMontgomerySetup(modulus, &rho);

  /* Calculate R mod m */
  Crypto_xVIx_xAIx_LNMontgomeryNormalization(result, modulus);

  /* G > P so we reduce it first */
  if (   Crypto_xVIx_xAIx_LNCompareNumbers(modulus, ctxPtr->modExpLocalBase)
      != CRYPTO_XVIX_XAIX_LN_E_LARGER
     )
  {
    Crypto_xVIx_xAIx_LNModulo(ctxPtr->modExpLocalBase, modulus, ctxPtr);
  }

  /* x * (R mod P) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(ctxPtr->modExpLocalBase,
                                     result,
                                     ctxPtr->modExpLocalBase,
                                     ctxPtr
                                    );
  Crypto_xVIx_xAIx_LNModulo(ctxPtr->modExpLocalBase, modulus, ctxPtr);

  while ((bits) > 0U)
  {
    --(bits);

    /* result = result**2 mod modulus  */
    Crypto_xVIx_xAIx_LNSquareComba(result, result, ctxPtr);
    Crypto_xVIx_xAIx_LNMontgomeryReduction(result, result, modulus, ctxPtr, rho);

    if ((Crypto_xVIx_xAIx_LNWordType) 1U == CRYPTO_XVIX_XAIX_LN_GET_BIT(exponent, bits))
    {
      Crypto_xVIx_xAIx_LNMultiplyNumbers(result,
                                         result,
                                         ctxPtr->modExpLocalBase,
                                         ctxPtr
                                        );
      Crypto_xVIx_xAIx_LNMontgomeryReduction(result, result, modulus, ctxPtr, rho);
    }
  }

  /* Apply Trans**(-1) to return from Montgomery system */
  Crypto_xVIx_xAIx_LNMontgomeryReduction(result, result, modulus, ctxPtr, rho);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP == STD_ON) */

/* --- Crypto_xVIx_xAIx_DecodeKey -------------------------------------------------------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_DecodeKey/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DecodeKey
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key,
          uint32                                                              keyLength,
          boolean                                                             isRSAPrivateKey,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) decodedRSAKeyPtr,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyLenPtr,
          uint32                                                              keyLenMaxBufferSize
)
{
  Std_ReturnType              retVal                  = E_NOT_OK;
  uint32                      currentPosition         = 0U;
  uint32                      remainingSequenceLength = 0U;
  uint32                      readBytes               = 0U;
  uint32                      index                   = 0U;
  uint8                       currentSequence         = 0U;
  uint32                      currentKeyByteLength    = 0U;
  uint8                       numberOfDERSequences    = 0U;
  uint32                      lengthOfDecodedRSAKey   = keyLenMaxBufferSize / CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;

  if (TRUE == isRSAPrivateKey)
  {
    numberOfDERSequences = 9U;
  }
  else
  {
    numberOfDERSequences = 2U;
  }

  /* The input must have at least one byte so that we can check its tag. */
  if ((1U <= keyLength) && (CRYPTO_XVIX_XAIX_DER_SEQUENCE_TAG == key[currentPosition]))
  {
    /* Jump over the tag byte of the input. */
    currentPosition++;

    /* Check that the encoding of the length of the sequence is valid, that the encoded length of the sequence is
       not zero and that the encoded length of the sequence is identical to the actual remaining
       bytes in the input array.
     */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0017,1 */
    readBytes = Crypto_xVIx_xAIx_DerGetLength(&key[currentPosition], &remainingSequenceLength, keyLength - currentPosition);
    if ((readBytes > 0U) && (remainingSequenceLength > 0U) && ((remainingSequenceLength + readBytes + currentPosition) == keyLength))
    {
      /* Loop over all DER-encoded integers of the sequence. */
      do
      {
        /* Skip as much bytes as needed to arrive at the current DER-encoded integer to transform.
           On the first execution of the loop, that means skipping over the encoding of the sequence.
           On all other executions of the loop, that means skipping over the last DER-encoded integer.
         */
        currentPosition += readBytes;

        /* Are we allowed to transform another DER-encoded integer? */
        if (numberOfDERSequences > currentSequence)
        {
          /* Get the length of the next DER-encoded integer and check that the length encoding is
             valid and that we have enough space in our output array to store the transformed
             integer.

             Please note that we will not read over the end of "key", because we are sure that there
             is at least one byte left in "key" when this happens. Because if not, "remainingSequenceLength"
             would have been 0 and we would have never entered the loop or already left it.
           */
          readBytes = Crypto_xVIx_xAIx_DerGetLength(&key[currentPosition + 1U], &currentKeyByteLength, keyLength - (currentPosition + 1U));
          if(readBytes > 0U)
          {
            /* Check that there is enough space in the output buffer to write the decoded number and that there
             * is enough space in the input buffer to read the number without going outside the array bounds.
             */
            if
            (
              (lengthOfDecodedRSAKey >= (CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(currentKeyByteLength) + index + 1U)) &&
              (keyLength             >= readBytes + currentPosition + 1U + currentKeyByteLength)
            )
            {
              /* Set the maximal allowed size of the output array. */
              decodedRSAKeyPtr[index] = lengthOfDecodedRSAKey - index;
              /* Extract the key element */
              readBytes = Crypto_xVIx_xAIx_DerGetInteger(&key[currentPosition],
                                                         &decodedRSAKeyPtr[index],
                                                         keyLength - currentPosition
                                                         );

              /* The version number of a private key must be zero. All other integers must not be zero. */
              if
              (
                (
                  (TRUE == isRSAPrivateKey) &&
                  (0U == currentSequence) &&
                  (0U != readBytes) &&
                  (0U == decodedRSAKeyPtr[index])
                ) ||
                (
                  (
                    (FALSE == isRSAPrivateKey) ||
                    (0U != currentSequence)
                  ) &&
                  (0U != readBytes) &&
                  (0U != decodedRSAKeyPtr[index])
                )
              )
              {
                index = index + decodedRSAKeyPtr[index] + 1U;
                if
                (
                  (TRUE == isRSAPrivateKey) &&
                  (0U == currentSequence)
                )
                {
                  /* The version number is stored using only one word, because its value is 0. But other
                   * code expects the version to be two words long, so we skip an additional word.
                   */
                  index++;
                }
                remainingSequenceLength = remainingSequenceLength - readBytes;
                currentSequence++;
                retVal = E_OK;
              }
              else
              {
                /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0018,1 */
                retVal = E_NOT_OK;
                remainingSequenceLength = 0U;
              }
            }
            else
            {
              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0014,1 */
              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0016,1 */
              retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
              remainingSequenceLength = 0U;
            }
          }
          else
          {
            retVal = E_NOT_OK;
            remainingSequenceLength = 0U;
          }
        }
        else
        {
          retVal = E_NOT_OK;
          remainingSequenceLength = 0U;
        }
      }
      while(0U != remainingSequenceLength);

      if
      (
        (E_OK == retVal) &&
        (
          ((TRUE == isRSAPrivateKey) && (9U != currentSequence) && (4U != currentSequence)) ||
          ((FALSE == isRSAPrivateKey) && (2U != currentSequence))
        )
      )
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0020,1 */
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0021,1 */
        retVal = E_NOT_OK;
        remainingSequenceLength = 0U;
      }
      if (E_OK == retVal)
      {
        *keyLenPtr = index * 4U;
      }
    }
  }
  return retVal;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON) */

/*---Crypto_xVIx_xAIx_CommonDerHeaderSequence-----------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_CommonDerHeaderSequence/0001, 1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE == STD_ON)
FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CommonDerHeaderSequence
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) headerBuffer,
        uint32                                        payloadLength
)
{
  uint32 headerLength;

  headerBuffer[0U] = CRYPTO_XVIX_XAIX_DER_SEQUENCE_TAG;
  headerLength     = Crypto_xVIx_xAIx_DerLengthEncoding(&headerBuffer[1U], payloadLength);
  return headerLength + 1U;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE == STD_ON) */

/*---Crypto_xVIx_xAIx_EncodeKey-----------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_EncodeKey/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EncodeKey
(
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key,
    P2VAR(uint32,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyLengthPtr,
    boolean                                                                   isRSAPrivateKey,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) encodedRSAKeyPtr,
    uint32                                                                    lengthOfEncodedRSAKey
)
{
                       Std_ReturnType retVal                  = E_NOT_OK;
                               uint32 keyLenInDerFormat       = 0U;
  Crypto_xVIx_xAIx_RsaKeyElementInfo_Type rsaKeyElements[CRYPTO_XVIX_XAIX_RSA_KENUM_MAX] =
                                      {
                                        {{CRYPTO_XVIX_XAIX_DER_SEQUENCE_TAG, 0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* sequence */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  1U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* version */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* modulus - n */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* publicExponent - e */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* privateExponen - d */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* prime1 - p */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* prime2 - q */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* exponent1 - d mod (p-1) */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* exponent2 - d mod (q-1) */
                                        {{CRYPTO_XVIX_XAIX_DER_INTEGER_TAG,  0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U}, /* (inverse of q) mod p */
                                      };

  keyLenInDerFormat = Crypto_xVIx_xAIx_EncodeKey_Length(
                                                    isRSAPrivateKey,
                                                    rsaKeyElements,
                                                    encodedRSAKeyPtr,
                                                    lengthOfEncodedRSAKey
                                                  );

  if (CRYPTO_XVIX_XAIX_RSA_KEYDERLEN_INVALID == keyLenInDerFormat)
  {
    retVal = E_NOT_OK;
  }
  else
  if (keyLenInDerFormat > *keyLengthPtr)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0008,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0010,1 */
    retVal = CRYPTO_XVIX_XAIX_ENCODE_ERROR;
  }
  else
  {
    *keyLengthPtr = keyLenInDerFormat;
    retVal = Crypto_xVIx_xAIx_EncodeKey_Data(
                                key,
                                isRSAPrivateKey,
                                encodedRSAKeyPtr,
                                lengthOfEncodedRSAKey,
                                rsaKeyElements
                              );
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON) */

/*---Crypto_xVIx_xAIx_EncodeKey_Length-----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EncodeKey_Length
(
    boolean                                                                   isRSAPrivateKey,
    Crypto_xVIx_xAIx_RsaKeyElementInfo_Type*                                  rsaKeyElementsPtr,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) encodedRSAKeyPtr,
    uint32                                                                    lengthOfEncodedRSAKey
)
{
  uint16 i                     = 0U;
  uint16 allKeyElements_length = 0U;
  uint16 currentNumber_Index   = 0U;
  uint16 previousNumber_Index  = 0U;
  uint16 keyElementStart_Index = 0U;
  uint32 keyDer_length         = 0U;
  uint32 version_length        = 0U;
  uint8  numberOfKeyElements   = 0U;

  if (isRSAPrivateKey)
  {
    version_length = encodedRSAKeyPtr[CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE_INDEX];
    /* CHECK: NOPARSE
     * The version number is set to 0 for PKCS1v15.
     */
    /*Check if version len in LN number is 0*/
    if (0U == version_length)
    {
      rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_VER_INDEX].der_length = CRYPTO_XVIX_XAIX_RSA_VER_LEN;

      allKeyElements_length += CRYPTO_XVIX_XAIX_RSA_VER_LEN;
      currentNumber_Index   += CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE;
      keyElementStart_Index  = CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX; /*Modulus Index*/
      numberOfKeyElements   += 1U;
    }
    else
    {
      keyElementStart_Index  = CRYPTO_XVIX_XAIX_RSA_VER_INDEX; /*Version Index*/
    }
    /* CHECK: PARSE */
  }
  else
  {
    keyElementStart_Index  = CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX; /*Modulus Index*/
  }

  for (i = keyElementStart_Index; i < CRYPTO_XVIX_XAIX_RSA_KENUM_MAX; i++)
  {
    currentNumber_Index += previousNumber_Index;

    if (currentNumber_Index < lengthOfEncodedRSAKey)
    {
      Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerDataLen(
                                                    &encodedRSAKeyPtr[currentNumber_Index],
                                                    &rsaKeyElementsPtr[i].data_length,
                                                    &rsaKeyElementsPtr[i].sign_length
                                                  );

      if (0U != rsaKeyElementsPtr[i].data_length)
      {
        rsaKeyElementsPtr[i].header_length = (uint8) (1U + Crypto_xVIx_xAIx_DerLengthEncoding(
                                                                                 &rsaKeyElementsPtr[i].header[1U],
                                                                                 rsaKeyElementsPtr[i].data_length
                                                                               ));
        rsaKeyElementsPtr[i].der_length    = rsaKeyElementsPtr[i].header_length + rsaKeyElementsPtr[i].data_length;
        allKeyElements_length             += rsaKeyElementsPtr[i].der_length;
        numberOfKeyElements               += 1U;
      }
      else
      /* Deviation TASKING-1 */
      if ((0U == rsaKeyElementsPtr[i].data_length) && (CRYPTO_XVIX_XAIX_RSA_P1_INDEX == i))
      {
        /* Prime1 size is 0, stop process length information*/
        break;
      }
      else
      {
        /* Do nothing */
      }
      previousNumber_Index = (uint16) (1U + encodedRSAKeyPtr[currentNumber_Index]);
    }
    else
    {
      /* Do nothing*/
    }
  }

  if (((CRYPTO_XVIX_XAIX_RSA_PUBLIC_NUMBER_KE2  == numberOfKeyElements) && (FALSE == isRSAPrivateKey)) ||
      ((CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE9 == numberOfKeyElements) && (TRUE  == isRSAPrivateKey)) ||
      ((CRYPTO_XVIX_XAIX_RSA_PRIVATE_NUMBER_KE4 == numberOfKeyElements) && (TRUE  == isRSAPrivateKey)))
  {
    rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].header_length = (uint8) (1U + Crypto_xVIx_xAIx_DerLengthEncoding(
                                                                                                     &rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].header[1U],
                                                                                                     allKeyElements_length
                                                                                                    ));
    rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].der_length = rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].header_length;

    keyDer_length = (uint32) rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].der_length + (uint32) allKeyElements_length;
  }
  else
  {
    keyDer_length = CRYPTO_XVIX_XAIX_RSA_KEYDERLEN_INVALID;
  }

  return keyDer_length;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_LENGTH == STD_ON) */

/*---Crypto_xVIx_xAIx_EncodeKey_Data-----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EncodeKey_Data
(
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key,
          boolean                                                             isRSAPrivateKey,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) encodedRSAKeyPtr,
          uint32                                                              lengthOfEncodedRSAKey,
          Crypto_xVIx_xAIx_RsaKeyElementInfo_Type*                            rsaKeyElementsPtr
)
{
  uint16 i                     = 0U;
  uint16 currentNumber_Index   = 0U;
  uint16 previousNumber_Index  = 0U;
  uint16 currKeyByte_Index     = 0U;
  uint16 keyElementStart_Index = 1U;
  uint32 version_length        = 0U;

  /* Update Sequence */
  TS_MemCpy(
             &key[currKeyByte_Index],
             &rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].header,
             rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].der_length
           );
  currKeyByte_Index += rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_SEQ_INDEX].der_length;

  if (isRSAPrivateKey)
  {
    version_length = encodedRSAKeyPtr[CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE_INDEX];
    /* CHECK: NOPARSE
     * The version number is set to 0 for PKCS1v15.
     */
    if (0U == version_length)
    {
      /* Update Version */
      TS_MemCpy(
                 &key[currKeyByte_Index],
                 &rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_VER_INDEX].header[0u],
                 rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_VER_INDEX].der_length
                );
      currKeyByte_Index    += rsaKeyElementsPtr[CRYPTO_XVIX_XAIX_RSA_VER_INDEX].der_length;
      currentNumber_Index  += CRYPTO_XVIX_XAIX_RSA_VER_LNSIZE;
      keyElementStart_Index = CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX;
    }
    else
    {
      keyElementStart_Index = CRYPTO_XVIX_XAIX_RSA_VER_INDEX;
    }
    /* CHECK: PARSE */
  }
  else
  {
    keyElementStart_Index = CRYPTO_XVIX_XAIX_RSA_MODULUS_INDEX;
  }

  /* Update KeyElements Data*/
  for (i = keyElementStart_Index; i < CRYPTO_XVIX_XAIX_RSA_KENUM_MAX; i++)
  {
    currentNumber_Index += previousNumber_Index;

    if (currentNumber_Index < lengthOfEncodedRSAKey)
    {
      /* CHECK: NOPARSE
       * Key elements length can not be equal to zero but this check kept here for defensive programming.
       */
      if (0U != rsaKeyElementsPtr[i].der_length)
      {
        /*Header Copy Process*/
        TS_MemCpy(&key[currKeyByte_Index], &rsaKeyElementsPtr[i].header, rsaKeyElementsPtr[i].header_length);
        currKeyByte_Index += rsaKeyElementsPtr[i].header_length;

        /*Data Copy Process*/
        (void)Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerData(
                                                   &encodedRSAKeyPtr[currentNumber_Index],
                                                   &key[currKeyByte_Index],
                                                   rsaKeyElementsPtr[i].data_length,
                                                   rsaKeyElementsPtr[i].sign_length
                                                 );
        currKeyByte_Index += rsaKeyElementsPtr[i].data_length;

        previousNumber_Index = (uint16) (1U + encodedRSAKeyPtr[currentNumber_Index]);
      }
      /* CHECK: PARSE */
    }
    else
    {
      /* Do nothing*/
    }
  }
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_ENCODEKEY_DATA == STD_ON) */

/*---Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerDataLen-----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerDataLen
(
    P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint16,                        AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) dataLengthPtr,
    P2VAR(uint8,                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) signLengthPtr
)
{
  uint16 numberWord_len;
  uint16 numberMsb_pos;
  uint8  numberByte_len;
  uint8  numberSign_len;

  numberWord_len  = (uint16)number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];

  if (numberWord_len > 0U)
  {
    numberMsb_pos = numberWord_len;
    if (number[numberMsb_pos] < 0x100U)
    {
      numberByte_len = 3U;
      numberSign_len = (uint8)(((uint8)(number[numberMsb_pos]) & 0x80u) > 0U);
    }
    else
    if (number[numberMsb_pos] < 0x10000U)
    {
      numberByte_len = 2U;
      numberSign_len = (uint8)(((uint8)(number[numberMsb_pos] >> 8U) & 0x80u) > 0U);
    }
    else
    if (number[numberMsb_pos] < 0x1000000U)
    {
      numberByte_len = 1U;
      numberSign_len = (uint8)(((uint8)(number[numberMsb_pos] >> 16U) & 0x80u) > 0U);
    }
    else
    {
      numberByte_len = 0U;
      numberSign_len = (uint8)(((uint8)(number[numberMsb_pos] >> 24U) & 0x80u) > 0U);
    }
    *dataLengthPtr  = (numberWord_len * 4U) - numberByte_len + numberSign_len;
    *signLengthPtr  = numberSign_len;
  }
  else
  {
    *dataLengthPtr = 0U;
    *signLengthPtr = 0U;
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATALEN == STD_ON) */

/*---Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerData-----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNNumberToBEByteArray_DerData
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
          uint32                                                              dataLength,
          uint8                                                               signLength
)
{
  Crypto_xVIx_xAIx_LNWordType numberPos; /* the position in "number" */
  Crypto_xVIx_xAIx_LNWordType wordPos; /* the byte position in the current word of "number" */
  Crypto_xVIx_xAIx_LNWordType arrayPos; /* the position in the byte array */
  Crypto_xVIx_xAIx_LNWordType numberToProcess;
  Crypto_xVIx_xAIx_LNWordType numberByteLen;

  uint8 additionalSignByte = 0U;
  uint8 notRequiredProcessByte = 0U;

  Std_ReturnType         retVal = E_OK;

  numberByteLen = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] * 4U;

  if (dataLength > numberByteLen)
  {
    numberToProcess    = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    additionalSignByte = 1U;
    array[0U]          = 0U;
  }
  else
  if (dataLength == numberByteLen)
  {
    numberToProcess    = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    additionalSignByte = 0U;
  }
  else
  {
    numberToProcess        = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] - 1U;
    notRequiredProcessByte = (uint8) (numberByteLen - dataLength);
    if (signLength > 0U)
    {
      array[0U] = 0U;
    }
  }

  /* We cycle through all the words of "number". */
  for (numberPos = (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_LSW_POS;
       numberPos <= numberToProcess;
       numberPos++
      )
  {
    /* Begin computing the index of the byte which will be updated. */
    arrayPos  = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
    arrayPos -= numberPos;
    arrayPos += (Crypto_xVIx_xAIx_LNWordType) 1U;
    arrayPos *= (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
    arrayPos += (Crypto_xVIx_xAIx_LNWordType) additionalSignByte - (Crypto_xVIx_xAIx_LNWordType) notRequiredProcessByte;

    /* Each word of "number" is split into "CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES" bytes of
       "array". */
    for (wordPos = (Crypto_xVIx_xAIx_LNWordType) 0U;
         (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES > wordPos;
         wordPos++
        )
    {
      /* Finish computing the index of the byte which will be updated. */
      arrayPos -= (Crypto_xVIx_xAIx_LNWordType) 1U;

      /* The current byte of "array" is computed from the current word of
         "number". */
      array[arrayPos] = (uint8) (number[numberPos] >> (uint8) ((uint8) wordPos << 3U));
    }
  }

  if (notRequiredProcessByte > 0U)
  {
    arrayPos = (Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES - notRequiredProcessByte;

    for (wordPos = (Crypto_xVIx_xAIx_LNWordType) 0U;
             ((Crypto_xVIx_xAIx_LNWordType) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES - notRequiredProcessByte) > wordPos;
             wordPos++
            )
    {
      /* Finish computing the index of the byte which will be updated. */
      arrayPos -= (Crypto_xVIx_xAIx_LNWordType) 1U;

      /* The current byte of "array" is computed from the current word of "number". */
      array[arrayPos] = (uint8) (number[numberPos] >> (uint8) ((uint8) wordPos << 3U));
    }
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LNNUMBERTOBEBYTEARRAY_DERDATA == STD_ON) */

/*---Crypto_xVIx_xAIx_CommonDerHeaderOctetString--------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_CommonDerHeaderOctetString/0001, 1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING == STD_ON)
FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CommonDerHeaderOctetString
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) headerBuffer,
        uint32                                        payloadLength
)
{
  uint32 headerLength;

  headerBuffer[0U] = 0x04U;
  headerLength     = Crypto_xVIx_xAIx_DerLengthEncoding(&headerBuffer[1U], payloadLength);
  return headerLength + 1U;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*---Crypto_xVIx_xAIx_LNMultByTwo-----------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/LN/Crypto_xVIx_xAIx_LNMultByTwo/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMultByTwo
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number
)
{
  Crypto_xVIx_xAIx_LNWordType x, oldUsed, carry, nextCarry, *srcPtr, *destPtr;

  oldUsed                                = result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
  result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];

  /* Aliases for source and destination */
  srcPtr  = &number[CRYPTO_XVIX_XAIX_LN_LSW_POS];
  destPtr = &result[CRYPTO_XVIX_XAIX_LN_LSW_POS];

  carry = 0U;
  for (x = 0U; x < number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; x++)
  {
    /* Get what will be the *next* carry bit from the
       MSB of the current digit */
    nextCarry =    srcPtr[x]
                >> ((Crypto_xVIx_xAIx_LNWordType) ((CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS) - 1U));

    /* Now shift up this digit, add in the carry [from the previous] */
    destPtr[x] = ((Crypto_xVIx_xAIx_LNWordType) (   (Crypto_xVIx_xAIx_LNWordType) srcPtr[x]
                                                 << ((Crypto_xVIx_xAIx_LNWordType) 1U)
                                                ) | carry
                 );

    /* Copy the carry that would be from the source
     * digit into the next iteration */
    carry = nextCarry;
  }

  /* New leading digit? */
  if (carry != 0U)
  {
    /* Add b MSB which is always 1 at this point */
    destPtr[x] = 1U;
    ++(result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]);
  }

  /* Now zero any excess digits on the destination
   * that we didn`'t write to */
  destPtr = &(result[result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] + 1U]);

  for (x = result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; x < oldUsed; x++)
  {
    destPtr[x] = 0U;
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTBYTWO == STD_ON) */

/*---Crypto_xVIx_xAIx_LNMontgomerySetup-----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMontgomerySetup
(
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulo,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) rho
)
{
  Crypto_xVIx_xAIx_LNWordType x, b;

  /* Fast inversion mod 2**k
   *
   * Based on the fact that
   *
   * XA = 1 (mod 2**n)  =>  (x(2-XA)) A = 1 (mod 2**2n)
   *                    =>  2*x*A - x*x*A*A = 1
   *                    =>  2*(1) - (1)     = 1
   */
  b = modulo[CRYPTO_XVIX_XAIX_LN_LSW_POS];

  /* here x*a==1 mod 2**4 */
  x  = (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType) ((b + 2U) & 4U) << 1U) + b;
  /* here x*a==1 mod 2**8 */
  x *= (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType) 2U - (b * x));
  /* here x*a==1 mod 2**16 */
  x *= (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType) 2U - (b * x));
  /* here x*a==1 mod 2**32 */
  x *= (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType) 2U - (b * x));

  /* rho = -1/m mod b */
  *rho = (Crypto_xVIx_xAIx_LNWordType) ((Crypto_xVIx_xAIx_LNWordType) (~x) + 1U);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYSETUP == STD_ON) */

/*---Crypto_xVIx_xAIx_LNMontgomeryNormalization---------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMontgomeryNormalization
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulo
)
{
  uint32                      bits;
  Crypto_xVIx_xAIx_LNWordType x;

  bits = Crypto_xVIx_xAIx_LNBitLengthOfNumber(modulo) % CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS;
  if (bits == 0U)
  {
    bits = CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS;
  }

  /* compute A = b^(n-1) * 2^(bits-1) */
  /* The else branch cannot be reached in a real world situation */

  if (modulo[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] > 1U)

  {
    uint32 exponent =   (  (  ((uint32) modulo[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] - 1U)
                            * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS
                           )
                         + bits
                        )
                      - 1U;

    for (x = CRYPTO_XVIX_XAIX_LN_LSW_POS; x <= result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; x++)
    {
      result[x] = 0U;
    }

    CRYPTO_XVIX_XAIX_LN_MONT_POWOF2(result, exponent);
  }
  else
  {
    result[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = 1U;
    result[CRYPTO_XVIX_XAIX_LN_LSW_POS]    = 1U;
    bits                                   = 1U;
  }

  /* Now compute C = A * b mod b */
  for (x = (Crypto_xVIx_xAIx_LNWordType)(bits - 1U);
       x < (Crypto_xVIx_xAIx_LNWordType)CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS;
       x++
      )
  {
    /* Find R */
    Crypto_xVIx_xAIx_LNMultByTwo(result, result);

    /* If the result is larger than modulo reduce it as we only need the quantity */
    /* that, when addded to the input makes it divisible by R without remainder. */
    if (Crypto_xVIx_xAIx_LNCompareNumbers(result, modulo) != CRYPTO_XVIX_XAIX_LN_E_SMALLER)
    {
      Crypto_xVIx_xAIx_LNSubtraction(result, result, modulo);
    }
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYNORMALIZATION == STD_ON) */

/*---Crypto_xVIx_xAIx_LNMontgomeryReduction-------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNMontgomeryReduction
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) remainderptr,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulo,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr,
          Crypto_xVIx_xAIx_LNWordType                               rho
)
{
  Crypto_xVIx_xAIx_LNWordType mu, x, y, oldUsed, carry, *cPtr, *destPtr;
  Crypto_xVIx_xAIx_LNWordType pa = modulo[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];

  /* reset ctx variable */
  TS_MemBZero(ctxPtr->montgomeryReductionC, sizeof(ctxPtr->montgomeryReductionC));
  /* Copy the input */
  oldUsed = number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS];
  for (x = CRYPTO_XVIX_XAIX_LN_LSW_POS; x <= oldUsed; x++)
  {
    ctxPtr->montgomeryReductionC[x - 1U] = number[x];
  }

  for (x = 0U; x < pa; x++)
  {
    carry = 0U;

    /* Get mu for this round */
    mu   = CRYPTO_XVIX_XAIX_MONT_CALCMU(x, rho);
    cPtr = &(ctxPtr->montgomeryReductionC[x]);

    for (y = 0U; y < pa; y++)
    {
      CRYPTO_XVIX_XAIX_LN_MONT_INNERMUL(cPtr, carry, mu, &(modulo[1U]), y);
      cPtr = &(cPtr[1U]);
    }

    while (carry != 0U)
    {
      CRYPTO_XVIX_XAIX_LN_MONT_PROPCARRY(cPtr, carry);
      cPtr = &(cPtr[1U]);
    }
  }

  /* Now copy out the result */
  cPtr    = &(ctxPtr->montgomeryReductionC[pa]);
  destPtr = &(remainderptr[CRYPTO_XVIX_XAIX_LN_LSW_POS]);
  for (x = 0U; x < (pa + 1U); x++)
  {
    destPtr[x] = cPtr[x];
  }

  /* Zero out the remaining words */
  for (; x < oldUsed; x++)
  {
    destPtr[x] = 0U;
  }

  remainderptr[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] = pa + 1U;

  Crypto_xVIx_xAIx_LNNormalizeNumber(remainderptr);

  /* if A >= m then A = A - m */
  if (Crypto_xVIx_xAIx_LNCompareNumbers(remainderptr, modulo) != CRYPTO_XVIX_XAIX_LN_E_SMALLER)
  {
    Crypto_xVIx_xAIx_LNSubtraction(remainderptr, remainderptr, modulo);
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MONTGOMERYREDUCTION == STD_ON) */

/*---Crypto_xVIx_xAIx_LNDivByTwo------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNDivByTwo
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
        Crypto_xVIx_xAIx_LNWordType                               overflow
)
{
  Crypto_xVIx_xAIx_LNWordType i;
  Crypto_xVIx_xAIx_LNWordType diffTmpVal1;
  Crypto_xVIx_xAIx_LNWordType diffTmpVal2;

  diffTmpVal2 = overflow;

  for (i = value[CRYPTO_XVIX_XAIX_LN_LENGTH_POS]; i > 0U; i--)
  {
    diffTmpVal1 = value[i] & 1U;
    value[i]    = value[i] >> 1U;
    value[i]   |= (diffTmpVal2 << (CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS - 1U));
    diffTmpVal2 = diffTmpVal1;
  }
  Crypto_xVIx_xAIx_LNNormalizeNumber(value);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_DIVBYTWO == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSModuloShift--------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloShift
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* At the beginning of each round, we decrease
     ctxPtr->lengthDifference by one. */
  (ctxPtr->lengthDifference)--;

  /* We extract from ctxPtr->lengthDifference how many complete
     words to shift modulus and how many bits to shift modulus. */
  ctxPtr->shiftWords = CRYPTO_XVIX_XAIX_LN_DIV_BY_WORD_LEN(ctxPtr->lengthDifference);
  ctxPtr->shiftBits  = CRYPTO_XVIX_XAIX_LN_MOD_WORD_LEN(ctxPtr->lengthDifference);

  /* The first position of modulus from which to create the shifted
     modulus is computed. Note that this is one larger than the
     most significant word of modulus. */
  ctxPtr->posInMod = modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS] + (Crypto_xVIx_xAIx_LNWordType) 1U;

  /* The first position of number which to compare to the shifted
     modulus is computed. */
  ctxPtr->posInNum = ctxPtr->posInMod + ctxPtr->shiftWords;

  /* For each word of modulus, the shifted modulus is computed and
     compared to the corresponding word of number. */
  Crypto_xVIx_xAIx_LNSModuloShift2(number, modulus, ctxPtr);
  Crypto_xVIx_xAIx_LNSModuloSubtract(number, modulus, ctxPtr);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSModuloShift2-------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloShift2
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  do
  {
    Crypto_xVIx_xAIx_LNWordType wordOfNumber; /* one word of number */
    /* We assemble the current word of the shifted modulus from the
       words modulus[ctxPtr->posInMod] and modulus[ctxPtr->posInMod - 1]. */

    /* We test whether the current position in modulus is an allowed position. */
    if(ctxPtr->posInMod <= modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
    {
      /* The current position in modulus is allowed. We take some
         bits from the word of modulus at that position. */
      ctxPtr->wordOfShiftedMod = modulus[ctxPtr->posInMod] << ctxPtr->shiftBits;
    }
    else
    {
      /* The current position in modulus is too high. We are at a
         "leading zero". So, all the bits which go into
         ctxPtr->wordOfShiftedMod are zero. */
      ctxPtr->wordOfShiftedMod = (Crypto_xVIx_xAIx_LNWordType) 0U;
    }

    /* The needed bits from modulus[ctxPtr->posInMod - 1] are incorporated
       into ctxPtr->wordOfShiftedMod. If we shift the modulus by complete
       words (which means "ctxPtr->shiftBits == 0U") or if ctxPtr->posInMod
       is the lowest possible position (which means ctxPtr->posInMod == 1U)
       no bits from modulus[ctxPtr->posInMod - 1U] are needed. */
    if (((uint8) 0U != ctxPtr->shiftBits) && ((Crypto_xVIx_xAIx_LNWordType) 1U < ctxPtr->posInMod))
    {
      ctxPtr->wordOfShiftedMod |= (Crypto_xVIx_xAIx_LNWordType)
                                  (   modulus[ctxPtr->posInMod - (Crypto_xVIx_xAIx_LNWordType) 1U]
                                   >> (uint8) (  (uint8) CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS
                                               - ctxPtr->shiftBits
                                              )
                                  );
    }

    /* We compute the word of number which to compare to the word
       of the shifted modulus. This is normally simply
       number[ctxPtr->posInNum], but the position can be too high which
       means that we are at a "leading zero" of number. */
    if(ctxPtr->posInNum > number[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
    {
      wordOfNumber = (Crypto_xVIx_xAIx_LNWordType) 0U;
    }
    else
    {
      wordOfNumber = number[ctxPtr->posInNum];
    }

    /* Now, we compare the word of the shifted modulus to the current
       word of number. */
    if(ctxPtr->wordOfShiftedMod == wordOfNumber)
    {
      ctxPtr->cmpNumMod = CRYPTO_XVIX_XAIX_LN_E_EQUAL;
    }
    else
    if (ctxPtr->wordOfShiftedMod > wordOfNumber)
    {
      ctxPtr->cmpNumMod = CRYPTO_XVIX_XAIX_LN_E_SMALLER;
    }
    else
    {
      ctxPtr->cmpNumMod = CRYPTO_XVIX_XAIX_LN_E_LARGER;
    }

    /* The positions are decreased by 1. */
    ctxPtr->posInMod--;
    ctxPtr->posInNum--;
  }
  while (   (CRYPTO_XVIX_XAIX_LN_E_EQUAL == ctxPtr->cmpNumMod      )
         && ((Crypto_xVIx_xAIx_LNWordType) 0U < ctxPtr->posInMod)
        );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSHIFT2 == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSModuloSubtract-----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloSubtract
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* If number is at least as large as the shifted modulus, we
     subtract modulus from number. */
  if(CRYPTO_XVIX_XAIX_LN_E_SMALLER != ctxPtr->cmpNumMod)
  {
    ctxPtr->wordOfShiftedMod = (Crypto_xVIx_xAIx_LNWordType) 0U;

    ctxPtr->carry = (Crypto_xVIx_xAIx_LNWordType) 0U;

    /* When subtracting the shifted modulus from number we can
       skip the least significant words of number because the
       shifted modulus is 0, there. We compute the least
       significant word of number which is affected by the
       subtraction. */
    ctxPtr->posInNum = (Crypto_xVIx_xAIx_LNWordType) 1U + ctxPtr->shiftWords;

    /* We go through every word of the shifted modulus. */
    ctxPtr->posInMod = (Crypto_xVIx_xAIx_LNWordType) 1U;

    Crypto_xVIx_xAIx_LNSModuloSubtract2(number, modulus, ctxPtr);
    Crypto_xVIx_xAIx_LNSModuloCarry(number, ctxPtr);
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSModuloSubtract2----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloSubtract2
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  uint8 tempCarry; /* Used to store whether the carry has to be  */
  /* set for the next word.                     */
  while (ctxPtr->posInMod <= modulus[CRYPTO_XVIX_XAIX_LN_LENGTH_POS])
  {
    tempCarry = (uint8) 0U;

    ctxPtr->wordOfShiftedMod |= (Crypto_xVIx_xAIx_LNWordType)
                                (modulus[ctxPtr->posInMod] << ctxPtr->shiftBits);

    /* We test whether a ctxPtr->carry forms at this position. This
       happens when "ctxPtr->wordOfShiftedMod + ctxPtr->carry >
       number[ctxPtr->posInNum]".  Since we cannot test this condition
       directly because of possible overflows. We use a more complicated
       test which actually does what we want. */
    if (   (ctxPtr->wordOfShiftedMod >= number[ctxPtr->posInNum])
        && (   (ctxPtr->wordOfShiftedMod > number[ctxPtr->posInNum])
            || (ctxPtr->carry > (Crypto_xVIx_xAIx_LNWordType) 0U   )
           )
       )
    {
      tempCarry = (uint8) 1U;
    }

    /* We subtract "ctxPtr->wordOfShiftedMod" and "ctxPtr->carry" from
       the number. */
    number[ctxPtr->posInNum] -= ctxPtr->wordOfShiftedMod;
    number[ctxPtr->posInNum] -= (Crypto_xVIx_xAIx_LNWordType) ctxPtr->carry;

    ctxPtr->carry = (Crypto_xVIx_xAIx_LNWordType) tempCarry;

    if ((uint8) 0U == ctxPtr->shiftBits)
    {
      ctxPtr->wordOfShiftedMod = (Crypto_xVIx_xAIx_LNWordType) 0U;
    }
    else
    {
      ctxPtr->wordOfShiftedMod =    modulus[ctxPtr->posInMod]
                                 >> (uint8) (CRYPTO_XVIX_XAIX_LN_WORD_LEN_BITS - ctxPtr->shiftBits);
    }

    ctxPtr->posInNum++;
    ctxPtr->posInMod++;
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOSUBTRACT2 == STD_ON) */

/*---Crypto_xVIx_xAIx_LNSModuloCarry--------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_LNSModuloCarry
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) number,
  P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Now we have to deal with leftover carries and a possible last
     word of the shifted modulus. Since the ctxPtr->carry is at most one
     and ctxPtr->wordOfShiftedMod is at least one bit shorter than the
     largest possible word (making it at most half as large), we
     can add both numbers in "ctxPtr->carry" without overflow. */
  ctxPtr->carry += ctxPtr->wordOfShiftedMod;

  /* Now we deal with the leftover carries. */
  /* The ctxPtr->carry has trickled away. */
  number[ctxPtr->posInNum] -= ctxPtr->carry;
  ctxPtr->carry             = (Crypto_xVIx_xAIx_LNWordType) 0U;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SMODULOCARRY == STD_ON) */

/*---Crypto_xVIx_xAIx_DerLengthEncoding-----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DerLengthEncoding
(
   P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) lengthEncodingBuffer,
         uint32                              payloadLength
)
{
   uint32 lengthEncodingLength;

   if (payloadLength <= 0x7FU)
   {
      lengthEncodingBuffer[0U] = (uint8) payloadLength;
      lengthEncodingLength     = 1U;
   }
   else
   {
     /* Values greater than 0x7f need a control byte */
     uint32 numberOfBytes    = 0U;
     uint32 locPayloadLength = payloadLength;
     uint32 curPos           = 0U;
     while (locPayloadLength != 0U)
     {
       locPayloadLength >>= 8U;
       numberOfBytes++;
     }
     lengthEncodingBuffer[0U] = (uint8) 0x80U | (uint8) numberOfBytes;
     /* Encode the length with big endian byte order */
     for (curPos = 1U; curPos <= numberOfBytes; curPos++)
     {
       lengthEncodingBuffer[curPos] = (uint8) (payloadLength >> (8U * (numberOfBytes - curPos)));
     }
     lengthEncodingLength = 1U + numberOfBytes;
   }

   return lengthEncodingLength;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_LENGTHENCODING == STD_ON) */

/*---Crypto_xVIx_xAIx_DerGetLength----------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DerGetLength
(
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) lengthOctets,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
          uint32                                    maxEncodingLength
)
{
  uint32 readBytes = 0U;
  uint8  LengthOfLength = 0U;
  uint8  i = 0U;

  /* The length encoding must be at least 1 byte long. */
  if(maxEncodingLength > 0U)
  {
    if (0U == (0x80U & lengthOctets[0U]))
    {
      /* short form of length */
      *result   = lengthOctets[0U];
      readBytes = 1U;
    }
    else
    {
      /* long form of length*/

      /* Check that the encoding of the length fits in the result and that we do not read over
         the end of the input buffer during decoding.
       */
      LengthOfLength = 0x7FU & lengthOctets[0U];
      if
      (
        (LengthOfLength <= sizeof(uint32)) &&
        (LengthOfLength <= (maxEncodingLength - 1U))
      )
      {
        *result = 0U;
        for(i = 0U; i < LengthOfLength; i++)
        {
          /* The length is stored with most significant byte first. */
          *result = (*result << 8) + (uint32)lengthOctets[i + 1U];
        }

        readBytes = (uint32)LengthOfLength + 1UL;
      }
    }
  }
  return readBytes;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETLENGTH == STD_ON) */

/*---Crypto_xVIx_xAIx_DerGetInteger------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DerGetInteger
(
  P2CONST(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) data,
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) integerArray,
          uint32                                                    maxDataLength
)
{
  uint32 readBytes = 0U;
  uint32 length    = 0U;

  if((maxDataLength > 0U) && (CRYPTO_XVIX_XAIX_DER_INTEGER_TAG == data[0U]))
  {
    /* CHECK: NOPARSE
     * Following two if condition will never fail due to checks made in Crypto_xVIx_xAIx_DecodeKey function.
     */
    readBytes = Crypto_xVIx_xAIx_DerGetLength(&data[1U], &length, maxDataLength - 1U);
    if (0U != readBytes)
    {
      if(E_OK == Crypto_xVIx_xAIx_LNBEByteArrayToNumber(&data[1U + readBytes],
                                                        length,
                                                        &integerArray[0U],
                                                        integerArray[0U]
                                                        )
        )
      {
        readBytes += 1U + length;
      }
      else
      {
        readBytes = 0U;
      }
    }
    /* CHECK: PARSE */
  }
  return readBytes;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_GETINTEGER == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

