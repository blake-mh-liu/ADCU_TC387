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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.c/0001,1 */

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

#include <Crypto_xVIx_xAIx_Int.h>         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_Ecc.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.c/0004,1 */

/*==================[macros]======================================================================*/

/* --- ECC -------------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA is already defined
#endif
/** \brief  Macro representing if fast reduction compA is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB is already defined
#endif
/** \brief  Macro representing if fast reduction compB is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB STD_OFF
#endif

/* --- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE is already defined
#endif
/** \brief Macro representing if point addition calculate CDE is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 is already defined
#endif
/** \brief  Macro representing if point addition calculate A2 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 is already defined
#endif
/** \brief  Macro representing if point addition calculate Z3 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF is already defined
#endif
/** \brief  Macro representing if point addition calculate AF is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 is already defined
#endif
/** \brief  Macro representing if point addition calculate Tmp5 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 is already defined
#endif
/** \brief  Macro representing if point addition calculate final X3 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 STD_OFF
#endif

/* --- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE is already defined
#endif
/** \brief  Macro representing if point doubling procedure is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF is already defined
#endif
/** \brief  Macro representing if point doubling calculate EF is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB is already defined
#endif
/** \brief  Macro representing if point doubling calculate B is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH is already defined
#endif
/** \brief  Macro representing if point doubling calculate H is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 is already defined
#endif
/** \brief  Macro representing if point doubling calculate Z3 is enabled
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 STD_ON
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 STD_OFF
#endif

#if (defined CRYPTO_XVIX_XAIX_MAX_TEMP_LEN_WORDS)
  #error CRYPTO_XVIX_XAIX_MAX_TEMP_LEN_WORDS is already defined
#endif
/** \brief Calculates the maximum needed length of a temporary buffer, which is needed for the long
 *         number representation of the longest possible temporary number.
 */
#define CRYPTO_XVIX_XAIX_MAX_TEMP_LEN_WORDS(BYTES)                                \
(                                                                                 \
  (Crypto_xVIx_xAIx_LNWordType)                                                   \
  (                                                                               \
    (CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(BYTES) * (Crypto_xVIx_xAIx_LNWordType)2UL) +  \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                            \
  )                                                                               \
)

#if(defined CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES is already defined
#endif
/** \brief The private key length of the secp256r1 curve in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES 32U

#if(defined CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PUBKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PUBKEY_LEN_BYTES is already defined
#endif
/** \brief The public key length of the secp256r1 curve in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PUBKEY_LEN_BYTES 64U

#if(defined CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES is already defined
#endif
/** \brief The private key length of the secp384r1 curve in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES 48U

#if(defined CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PUBKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PUBKEY_LEN_BYTES is already defined
#endif
/** \brief The public key length of the secp384r1 curve in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PUBKEY_LEN_BYTES 96U

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/* ---ED25519 / Ed25519PH / X25519 -------------------------------------------------------------- */

/** \brief  Reduce point A.
 **
 ** \param[in,out]  tmp    Pointer to a buffer which will be used as temporary storage
 **                        during the reduction.
 ** \param[in,out]  value  Value to be reduced.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAFastReductionCompA
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA == STD_ON) */

/** \brief  Reduce point b.
 **
 ** \param[out]     tmp    Pointer to a buffer which will be used as temporary storage
 **                        during the reduction.
 ** \param[in,out]  value  Value to be reduced.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAFastReductionCompB
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB == STD_ON) */

/* ============================================================================================== */
/*                      These functions are used just for ED25519/ED25519PH                       */
/* ============================================================================================== */

/** \brief  This function doubles a points on an elliptic curve which are given in
 **         projective coordinates and returns the result again in projective coordinates.
 **
 ** \param[out]    result  Pointer to an Edwards curve point where the result of the
 **                        doubling will be stored in projective coordinates.
 ** \param[in]     value   Pointer to an Edwards curve point given in projective coordinates
 **                        which should be doubled.
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage
 ** \param[in]     edCtx   Pointer the the context.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingProcedure
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE == STD_ON) */

/* ---Sub Functions ----------------------------------------------------------------------------- */

/* ---Point additoin ---------------------------------------------------------------------------- */

/** \brief  Calculate C, D and E
 **
 ** \param[in]     addent1 Pointer to an Edwards Curve point given in projective coordinates
 **                        which should be added.
 ** \param[in]     addent2 Pointer to an Edwards Curve point given in projective coordinates
 **                        which should be added.
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateCDE
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE == STD_ON) */

/** \brief  Calculate A^2
 **
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateA2
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 == STD_ON) */

/** \brief  Calculate Z^3
 **
 ** \param[out]    result  Pointer to an Edwards Curve point where the result of the
 **                        addition will be stored in projective coordinates.
 ** \param[in]     addent1 Pointer to an Edwards Curve point given in projective coordinates
 **                        which should be added. This parameter may point to the same memory location
 **                        as the result point "result".
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateZ3
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 == STD_ON) */

/** \brief  Calculate temporary point
 **
 ** \param[out]    result  Pointer to an Edwards Curve point where the result of the
 **                        addition will be stored in projective coordinates.
 ** \param[in]     addent2 Pointer to an Edwards Curve point given in projective coordinates
 **                        which should be added. This parameter may point to the same memory location
 **                        as the result point "result".
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateAF
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF == STD_ON) */

/** \brief  Calculate temporary point
 **
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx  Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateInterimTmp5
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 == STD_ON) */

/** \brief  Calculate X3
 **
 ** \param[out]    result Pointer to an Edwards Curve point where the result of the
 **                       addition will be stored in projective coordinates.
 ** \param[in,out] tmp    Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx  Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateFinalX3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 == STD_ON) */

/* ---Point doubling ---------------------------------------------------------------------------- */

/** \brief  Calculate E and F
 **
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateEF
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF == STD_ON) */

/** \brief  Calculate B
 **
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateB
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB == STD_ON) */

/** \brief  Calculate B
 **
 ** \param[out]    value   Pointer to an Edwards Curve point where the result of the
 **                        doubling will be stored in projective coordinates.
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateH
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH == STD_ON) */

/** \brief  Calculate Z3
 **
 ** \param[out]    value   Pointer to an Edwards Curve point where the result of the
 **                        doubling will be stored in projective coordinates.
 ** \param[in,out] tmp     Pointer to a buffer which will be used as temporary storage.
 ** \param[in,out] edCtx   Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateZ3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON)

/*----- ECC P-256 Fast Reduction -----------------------------------------------------------------*/

/** \brief Calculate s1, s2 and s3 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out] temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReductionCalcValue1
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate s4, s5 and s6 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out] temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReductionCalcValue2
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate s4, s5 and s6 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out]  temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out]  buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReductionCalcValue3
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/*----- ECC NIST 384 -----------------------------------------------------------------------------*/

/** \brief Calculate s1, s2 and s3 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out] temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue1
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate s4, s5 and s6 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out] temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue2
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate s7 and s8 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out] temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue3
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate s9 and s10 integers.
 *
 * \param[in,out] value  Value to be reduced.
 * \param[in,out] temp   Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out]  buffer Pointer to a buffer which will be used as temporary
 *                       storage during the reduction.
 * \param[in,out] ctxPtr Pointer to the elliptic curve context.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue4
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/*----- ECC NIST Point Addition ------------------------------------------------------------------*/

/** \brief Check if either of the input points are at infinity.
 *
 * \param[in,out] result   Pointer to an Elliptic Curve Point where the result of the
 *                         addition will be stored in projective coordinates.
 * \param[in]     addend1  Pointer to an Elliptic Curve Point given in projective coordinates
 *                         which should be added. This parameter may Point to the
 *                         same memory location as the result Point "result".
 * \param[in]     addend2  Pointer to an Elliptic Curve Point given in projective coordinates
 *                         which should be added. This parameter may Point to
 *                         the same memory location as the result Point "result".
 * \param[in,out] finished Pointer to a flag that indicates if the operation is Finished.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCheckInfinity
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(boolean,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) finished
);

/** \brief Calculate A and B
 *
 *         This function calculates temporary results for the point addition.
 *
 * \param[in,out] result  Pointer to an Elliptic Curve Point where the result of the
 *                        addition will be stored in projective coordinates.
 * \param[in]     addend1 Pointer to an Elliptic Curve Point given in projective coordinates
 *                        which should be added. This parameter may Point to the same memory location
 *                        as the result Point "result".
 * \param[in]     addend2 Pointer to an Elliptic Curve Point given in projective coordinates
 *                        which should be added. This parameter may Point to the same memory location
 *                        as the result Point "result".
 * \param[in,out] tmp1    An array which holds a temporary number during addition.
 * \param[in,out] tmp2    An array which holds a temporary number during addition.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcAB
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate C
 *
 *         This function calculates temporary results for the point addition.
 *
 * \param[in,out] result  Pointer to an Elliptic Curve Point where the result of the
 *                        addition will be stored in projective coordinates.
 * \param[in,out] tmp2    An array which holds a temporary number during addition.
 * \param[in,out] tmp3    An array which holds a temporary number during addition.
 * \param[in,out] tmp4    An array which holds a temporary number during addition.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcC
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate final result of Z3
 *
 *         This function calculates the final result of Z3.
 *
 * \param[in,out] result  Pointer to an Elliptic Curve Point where the result of the
 *                        addition will be stored in projective coordinates.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcFinalZ3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate temporary Point for the point addition
 *
 * \param[in,out] result  Pointer to an Elliptic Curve Point where the result of the
 *                        addition will be stored in projective coordinates.
 * \param[in,out] tmp2    An array which holds a temporary number.
 * \param[in,out] tmp3    An array which holds a temporary number.
 * \param[in,out] tmp4    An array which holds a temporary number.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcInterimTmp4
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate final results of X3 and Y3
 *
 *         This function calculates the final results of X3 and Y3.
 *
 * \param[in,out] result  Pointer to an Elliptic Curve Point where the result of the
 *                        addition will be stored in projective coordinates.
 * \param[in,out] tmp1    An array which holds a temporary number.
 * \param[in,out] tmp3    An array which holds a temporary number.
 * \param[in,out] tmp4    An array which holds a temporary number.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcFinalX3Y3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/*----- ECC NIST Point Doubling ------------------------------------------------------------------*/

/** \brief Point doubling for elliptic curves with a = -3
 *
 *         This function doubles a point on an elliptic curve which is given in
 *         projective coordinates and returns the result in projective coordinates.
 *         The doubling is performed in slices and the current slice is stored in the
 *         given context.
 *
 *         This function only works for elliptic curves y^2 = x^3 + ax + b where the value
 *         of a is set to -3. In other words it only works for elliptic curves
 *         y^2 = x^3 - 3x + b. All NIST curves and many other curves fulfill this requirement.
 *
 * \param[in,out] result  Pointer to an elliptic curve point where the result of the
 *                        doubling will be stored in projective coordinates.
 * \param[in]     value   Pointer to an elliptic curve point given in projective
 *                        coordinates which should be doubled.
 * \param[in,out] tmp1    An array which holds a temporary number.
 * \param[in,out] tmp2    An array which holds a temporary number.
 * \param[in,out] tmp3    An array which holds a temporary number.
 * \param[in,out] tmp4    An array which holds a temporary number.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the doubling.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoubling
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate A and B
 *
 *         This function calculates temporary results for the point doubling.
 *
 * \param[in]     value  Pointer to an Elliptic Curve Point given in projective
 *                       coordinates which should be doubled.
 * \param[in,out] tmp1   An array which holds a temporary number.
 * \param[in,out] tmp2   An array which holds a temporary number.
 * \param[in,out] tmp4   An array which holds a temporary number.
 * \param[in,out] ctxPtr Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcAB
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate intern results
 *
 *         This function calculates temporary results for the point doubling.
 *
 * \param[in,out] result Pointer to an Elliptic Curve Point where the result of the
 *                       doubling will be stored in projective coordinates.
 * \param[in]     value  Pointer to an Elliptic Curve Point given in projective
 *                       coordinates which should be doubled.
 * \param[in,out] tmp1   An array which holds a temporary number.
 * \param[in,out] tmp2   An array which holds a temporary number.
 * \param[in,out] tmp3   An array which holds a temporary number.
 * \param[in,out] ctxPtr Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcInternTmp
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate final result of Y3
 *
 *         This function calculates final result of Y3.
 *
 * \param[in,out] result Pointer to an Elliptic Curve Point where the result of the
 *                       doubling will be stored in projective coordinates.
 * \param[in,out] tmp1   An array which holds a temporary number.
 * \param[in,out] tmp2   An array which holds a temporary number.
 * \param[in,out] tmp4   An array which holds a temporary number.
 * \param[in,out] ctxPtr Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcFinalY3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Calculate final result of X3 and Z3
 *
 *         This function calculates final result of X3 and Z3.
 *
 * \param[in,out] result Pointer to an Elliptic Curve Point where the result of the
 *                       doubling will be stored in projective coordinates.
 * \param[in,out] tmp2   An array which holds a temporary number.
 * \param[in,out] tmp3   An array which holds a temporary number.
 * \param[in,out] ctxPtr Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcFinalX3Z3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON) */
#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief The elliptic curve informations.
 *         When a new curve is added, the default values have to be adapted.
 *         In this Version only Ed25519/Ed25519ph Signature Gen/Verify is supported.
 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO == STD_ON)
CONST(Crypto_xVIx_xAIx_EllipticCurveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_EllipticCurveInfo[CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM] =
{
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
  /* Ed25519/Ed25519ph Informations */
  {

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0008,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0008,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0008,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0008,1 */
    /* Base Point */
    {
      /* X */
      {
        0x00000008UL,
        0x8F25D51AUL, 0xC9562D60UL, 0x9525A7B2UL, 0x692CC760UL,
        0xFDD6DC5CUL, 0xC0A4E231UL, 0xCD6E53FEUL, 0x216936D3UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Y */
      {
        0x00000008UL,
        0x66666658UL, 0x66666666UL, 0x66666666UL, 0x66666666UL,
        0x66666666UL, 0x66666666UL, 0x66666666UL, 0x66666666UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Z */
      {
        0x00000001UL,
        0x00000001UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      }
    },

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0002,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0002,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0002,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0002,1 */
    /* Prime number of Edwards Curve Ed25519. */
    {
      0x00000008UL,
      0xFFFFFFEDUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0x7FFFFFFFUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0006,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0006,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0006,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0006,1 */
    /* Modulus - LValue: The order of G(p). */
    {
      0x00000008UL,
      0x5CF5D3EDUL, 0x5812631AUL, 0xA2F79CD6UL, 0x14DEF9DEUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x10000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0007,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0007,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0007,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0007,1 */
    /* Coeff1 - DValue: A non-square element d of G(p). */
    {
      0x00000008UL,
      0x135978A3UL, 0x75EB4DCAUL, 0x4141D8ABUL, 0x00700A4DUL,
      0x7779E898UL, 0x8CC74079UL, 0x2B6FFE73UL, 0x52036CEEUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0004,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0004,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0004,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0004,1 */
    /* Coeff2 - nValue: An integer with c <= n <= b. */
    {
      0x00000001UL,
      0x000000FEUL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0009,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0009,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0009,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0009,1 */
    /* DER-Encoding of the Curve */
    {
      3U,
      {
        0x2BU, 0x65U, 0x70U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
      }
    },
#if (CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED == STD_ON)

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0016,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0016,1 */
    CRYPTO_ALGOFAM_ED25519,
#elif (CRYPTO_XVIX_XAIX_ALGOFAM_ED25519PH_ENABLED == STD_ON) /* (CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED == STD_ON)*/

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519PH_NOTSET/GENERAL/0017,1 */

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519PH_NOTSET/GENERAL/0017,1 */
    CRYPTO_ALGOFAM_ED25519PH,
#else /* (CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED == STD_ON) */
    CRYPTO_ALGOFAM_NOT_SET,
#endif /* (CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED == STD_ON) */
    /* Length of private key */
    CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PRIVKEY_LEN_BYTES,
    /* Length of public key */
    CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PUBKEY_LEN_BYTES,
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
    Crypto_xVIx_xAIx_EdDSAFastReduction
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
    NULL_PTR
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
  },
  /* X25519 Informations, This curve is birationally equivalent to a twisted Edwards Curve  */
  {
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0007,1 */
    /* Base Point */
    {
      /* X */
      {
        0x00000008UL,
        0x8F25D51AUL, 0xC9562D60UL, 0x9525A7B2UL, 0x692CC760UL,
        0xFDD6DC5CUL, 0xC0A4E231UL, 0xCD6E53FEUL, 0x216936D3UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Y */
      {
        0x00000008UL,
        0x66666658UL, 0x66666666UL, 0x66666666UL, 0x66666666UL,
        0x66666666UL, 0x66666666UL, 0x66666666UL, 0x66666666UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Z */
      {
        0x00000001UL,
        0x00000001UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      }
    },
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0004,1 */
    /* Prime number of the Curve. */
    {
      0x00000008UL,
      0xFFFFFFEDUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0x7FFFFFFFUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
    },
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0008,1 */
    /* Modulus */
    {
      0x00000008UL,
      0x5CF5D3EDUL, 0x5812631AUL, 0xA2F79CD6UL, 0x14DEF9DEUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x10000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
    },
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0003,1 */
    /* Coeff1 - UCoordinate: The u-coordinate of the base Point.*/
    {
      0x00000001UL,
      0x00000009UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0005,1 */
    /* Coeff2 - A24: An element in the finite field GF(p), not equal to -2 or 2. */
    {
      0x00000001UL,
      0x0001DB41UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0006,1 */
    /* DER-Encoding of the Curve */
    {
      3U,
      {
        0x2BU, 0x65U, 0x6EU, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
      }
    },
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0018,1 */
    CRYPTO_ALGOFAM_X25519,
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0019,1 */
    /* Length of private key */
    CRYPTO_XVIX_XAIX_CURVE_X25519_PRIVKEY_LEN_BYTES,
    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0020,1 */
    /* Length of public and secret shared key */
    CRYPTO_XVIX_XAIX_CURVE_X25519_PUBKEY_LEN_BYTES,
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
    Crypto_xVIx_xAIx_EdDSAFastReduction
#else /* (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
    NULL_PTR
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
  },
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON)

  /* Elliptic Curve SecP256r1 / NIST P-256 / Prime256v1 Informations */
  {
    /* !LINKSTO Crypto.Req.CPr/Ecc/P256_Base_Point/0001,1 */
    /* Base Point */
    {
      /* X */
      {
        0x00000008UL,
        0xD898C296UL, 0xF4A13945UL, 0x2DEB33A0UL, 0x77037D81UL,
        0x63A440F2UL, 0xF8BCE6E5UL, 0xE12C4247UL, 0x6B17D1F2UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Y */
      {
        0x00000008UL,
        0x37BF51F5UL, 0xCBB64068UL, 0x6B315ECEUL, 0x2BCE3357UL,
        0x7C0F9E16UL, 0x8EE7EB4AUL, 0xFE1A7F9BUL, 0x4FE342E2UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Z */
      {
        0x00000001UL,
        0x00000001UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      }
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P256_Prime/0001,1 */
    /* Prime number of Elliptic Curve P-256. */
    {
      0x00000008UL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000001UL, 0xFFFFFFFFUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P256_Order/0001,1 */
    /* Modulus */
    {
      0x00000008UL,
      0xFC632551UL, 0xF3B9CAC2UL, 0xA7179E84UL, 0xBCE6FAADUL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P256_Coefficient_A/0001,1 */
    /* Coeff1 - A: coefficient of y^2 = x^3 + Ax + B */
    {
      0x00000008UL,
      0xFFFFFFFCUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0x00000000UL,
      0x00000000UL, 0x00000000UL, 0x00000001UL, 0xFFFFFFFFUL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P256_Coefficient_B/0001,1 */
    /* Coeff2 - B: coefficient of y^2 = x^3 + Ax + B */
    {
      0x00000008UL,
      0x27D2604BUL, 0x3BCE3C3EUL, 0xCC53B0F6UL, 0x651D06B0UL,
      0x769886BCUL, 0xB3EBBD55UL, 0xAA3A93E7UL, 0x5AC635D8UL,
      0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P256_OID/0001,1 */
    /* DER-Encoding of the Curve */
    {
      8U,
      {
        0x2AU, 0x86U, 0x48U, 0xCEU, 0x3DU, 0x03U, 0x01U, 0x07U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
      }
    },
    CRYPTO_ALGOFAM_ECDSA,
    /* Length of private key */
    CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES,
    /* Length of public key */
    CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PUBKEY_LEN_BYTES,
    Crypto_xVIx_xAIx_ECP256FastReduction
  },
  /* Elliptic Curve SecP384r1 / NIST P-384 Informations */
  {
    /* !LINKSTO Crypto.Req.CPr/Ecc/P384_Base_Point/0001,1 */
    /* Base Point */
    {
      /* X */
      {
        0x0000000CUL,
        0x72760AB7UL, 0x3A545E38UL, 0xBF55296CUL, 0x5502F25DUL,
        0x82542A38UL, 0x59F741E0UL, 0x8BA79B98UL, 0x6E1D3B62UL,
        0xF320AD74UL, 0x8EB1C71EUL, 0xBE8B0537UL, 0xAA87CA22UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Y */
      {
        0x0000000CUL,
        0x90EA0E5FUL, 0x7A431D7CUL, 0x1D7E819DUL, 0x0A60B1CEUL,
        0xB5F0B8C0UL, 0xE9DA3113UL, 0x289A147CUL, 0xF8F41DBDUL,
        0x9292DC29UL, 0x5D9E98BFUL, 0x96262C6FUL, 0x3617DE4AUL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      },
      /* Z */
      {
        0x00000001UL,
        0x00000001UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL,
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
      }
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P384_Prime/0001,1 */
    /* Prime number of Elliptic Curve P-384. */
    {
      0x0000000CUL,
      0xFFFFFFFFUL, 0x00000000UL, 0x00000000UL, 0xFFFFFFFFUL,
      0xFFFFFFFEUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P384_Order/0001,1 */
    /* Modulus */
    {
      0x0000000CUL,
      0xCCC52973UL, 0xECEC196AUL, 0x48B0A77AUL, 0x581A0DB2UL,
      0xF4372DDFUL, 0xC7634D81UL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P384_Coefficient_A/0001,1 */
    /* Coeff1 - A: coefficient of y^2 = x^3 + Ax + B */
    {
      0x0000000CUL,
      0xFFFFFFFCUL, 0x00000000UL, 0x00000000UL, 0xFFFFFFFFUL,
      0xFFFFFFFEUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
      0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P384_Coefficient_B/0001,1 */
    /* Coeff2 - B: coefficient of y^2 = x^3 + Ax + B */
    {
      0x0000000CUL,
      0xD3EC2AEFUL, 0x2A85C8EDUL, 0x8A2ED19DUL, 0xC656398DUL,
      0x5013875AUL, 0x0314088FUL, 0xFE814112UL, 0x181D9C6EUL,
      0xE3F82D19UL, 0x988E056BUL, 0xE23EE7E4UL, 0xB3312FA7UL
    },
    /* !LINKSTO Crypto.Req.CPr/Ecc/P384_OID/0001,1 */
    /* DER-Encoding of the Curve */
    {
      5U,
      {
        0x2BU, 0x81U, 0x04U, 0x00U, 0x22U, 0x00U, 0x00U, 0x00U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
      }
    },
    CRYPTO_ALGOFAM_ECDSA,
    /* Length of private key */
    CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES,
    /* Length of public key */
    CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PUBKEY_LEN_BYTES,
    Crypto_xVIx_xAIx_ECP384FastReduction
  },
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON) */
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Elliptic Curves ----------------------------------------------------------------------------*/

/*---Crypto_xVIx_xAIx_GetECIndex------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_GetECIndex/0001,1 */
/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_GetECIndex/0002,1 */
/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_GetECIndex/0003,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetECIndex
(
          uint8                                         serviceInfo,
          uint8                                         algorithmFamily,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) curveDER,
          uint8                                         curveDERLength,
    P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) curveIndex
)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8 i;

  if(NULL_PTR == curveDER)
  {
    /* Signature generation / Signature verification */
    if(   (CRYPTO_SIGNATUREGENERATE == serviceInfo)
       || (CRYPTO_SIGNATUREVERIFY   == serviceInfo)
      )
    {
      /* Use Ed25519/Ed25519ph as default for Signature generation or verification */
      if (   (CRYPTO_ALGOFAM_ED25519   == algorithmFamily)
          || (CRYPTO_ALGOFAM_ED25519PH == algorithmFamily)
         )
      {
        *curveIndex = CRYPTO_XVIX_XAIX_SIGNATURE_ED25519YY_DEFAULT_CURVE;
        retVal = E_OK;
      }
      /* SecP256r1 / NIST P-256 / Prime256v1 are not supported in this version */
      /* Already we do not support any Brainpool Curves */
      else
      {
        retVal = E_NOT_OK;
      }
    }
    /* KeyExchange is not supported in this version */
    else
    {
      /* Unsupported Algorithm */
      retVal = E_NOT_OK;
    }
  }
  else  /* NULL_PTR != curveDER */
  {
    /* The first element of the DER-Encoding contains 0x06.
     * The second element contains the actual length of the DER-Encoding.
     */
    if(0x06U != curveDER[0U])
    {
      retVal = E_NOT_OK;
    }
    else
    if((curveDER[1U] + 2U) > curveDERLength)
    {
      retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else
    {
      for(i = 0U; i < CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM; i++)
      {
        /* Check the length of DER-Encoding and the family type */
        if(
            (Crypto_xVIx_xAIx_EllipticCurveInfo[i].ecDER.length == curveDER[1U]     ) &&
            (Crypto_xVIx_xAIx_EllipticCurveInfo[i].algoFam      == algorithmFamily  )
          )
          {
            /* Check the value of the DER-Encoding from key Element */
            if(E_OK == Crypto_xVIx_xAIx_MemCmp(
                                                Crypto_xVIx_xAIx_EllipticCurveInfo[i].ecDER.value,
                                                &(curveDER[2U]),
                                                Crypto_xVIx_xAIx_EllipticCurveInfo[i].ecDER.length
                                              )
              )
              {
                *curveIndex = i;
                retVal = E_OK;
              }
          }
      }
    }
  }
  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX == STD_ON) */

/*--- Ed25519/X25519 -----------------------------------------------------------------------------*/

/*---Crypto_xVIx_xAIx_EdDSAFastReduction----------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_EdDSAFastReduction/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAFastReduction
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  Crypto_xVIx_xAIx_LNWordType tmp[CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS];

  Crypto_xVIx_xAIx_LNWordType temp1;

  /* set the higher positions of the value to zero if necessary */
  for (temp1 = (value[0U] + 1U); temp1 < CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS; temp1++)
  {
    value[temp1] = 0U;
  }

  Crypto_xVIx_xAIx_EdDSAFastReductionCompA(tmp, value);

  /* value = A1 + A2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, tmp, value, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* value = value + A1 = 2*A1 + A2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* value = value + A1 = 3*A1 + A2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  Crypto_xVIx_xAIx_EdDSAFastReductionCompB(&temp1, tmp);

  /* value = value + B2 = 3.A1 + A2 + B2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* tmp = B1 */
  tmp[1U] = temp1;
  tmp[0U] = 1U;

  Crypto_xVIx_xAIx_LNNormalizeNumber(tmp);

  /* value = 3*A1 + A2 + B2 + 3*B1 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* tmp = B1*(2^4) */
  tmp[1U] = (Crypto_xVIx_xAIx_LNWordType) (tmp[1U] << 4U);
  tmp[0U] = 1U;

  Crypto_xVIx_xAIx_LNNormalizeNumber(tmp);

  /* value = value + tmp = 3*A1 + A2 + B2 + 3*B1 + B1*(2^4) */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, tmp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */
/* ============================================================================================== */
/*                      These functions are used just for ED25519/ED25519PH                       */
/* ============================================================================================== */

/*---Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  point,
  P2CONST(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  multiplicand,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  edCtx
)
{
  /* first the result shall be set to the Point of infinity. */
  result->xValue[0U] = 0U;
  result->xValue[1U] = 0U;
  result->yValue[0U] = 1U;
  result->yValue[1U] = 1U;
  result->zValue[0U] = 1U;
  result->zValue[1U] = 1U;

  edCtx->currentBit = Crypto_xVIx_xAIx_LNBitLengthOfNumber(multiplicand);
  while(0U < edCtx->currentBit)
  {
    edCtx->currentBit--;
    Crypto_xVIx_xAIx_EdDSAPointDoublingProcedure(
                                                   result,
                                                   result,
                                                   tmp,
                                                   edCtx
                                                 );

    if (1U == (CRYPTO_XVIX_XAIX_LN_GET_BIT(multiplicand, edCtx->currentBit)))
    {
      Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition(
                                                     result,
                                                     result,
                                                     point,
                                                     tmp,
                                                     edCtx
                                                   );
    }
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */

/*---Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* In projective coordinates the Point of infinity corresponds to the Point (X : Y : Z) = (0 : 1 : 1) */
  if (   ( 0U == addend1->xValue[0U] )
      && ((1U == addend1->yValue[0U])  && (1U == addend1->yValue[1U]))
      && ((1U == addend1->zValue[0U])  && (1U == addend1->zValue[1U]))
     )
  {
    TS_MemCpy(result->xValue, addend2->xValue, (addend2->xValue[0U] + 1U) << 2U);
    TS_MemCpy(result->yValue, addend2->yValue, (addend2->yValue[0U] + 1U) << 2U);
    TS_MemCpy(result->zValue, addend2->zValue, (addend2->zValue[0U] + 1U) << 2U);
  }
  else
  {
    /* calculate C, D and E */
    Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateCDE(
                                                     addend1,
                                                     addend2,
                                                     tmp,
                                                     edCtx
                                                   );

    /* A: tmp4 = Z1 * Z2 */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        &tmp[3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS],
                                        addend1->zValue,
                                        addend2->zValue,
                                        &(edCtx->lnCtx)
                                      );

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS], edCtx);

    Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateA2(tmp, edCtx);

    /* Z3 = tmp6 * tmp3 : Final result */
    Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateZ3(
                                                    result,
                                                    addend1,
                                                    tmp,
                                                    edCtx
                                                  );

    /* X3 = A * F: tmp4 * tmp6 */
    Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateAF(
                                                    result,
                                                    addend2,
                                                    tmp,
                                                    edCtx
                                                  );

    /* tmp5 = tmp5 * tmp6 */
    Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateInterimTmp5(tmp, edCtx);

    /* X3 = X3 * tmp5 - Final result */
    Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateFinalX3(
                                                         result,
                                                         tmp,
                                                         edCtx
                                                       );

    /* tmp4 = A * G: tmp4 * tmp3 */
    /*Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateAG(edCtx, tmp);*/
    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        &tmp[tmp4],
                                        &tmp[tmp4],
                                        &tmp[tmp3],
                                        &(edCtx->lnCtx)
                                      );
    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp4], edCtx);

    /* Y3 = tmp4 * tmp5 - Final result */

    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        result->yValue,
                                        &tmp[tmp4],
                                        &tmp[tmp5],
                                        &(edCtx->lnCtx)
                                      );

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->yValue, edCtx);
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */

/*---Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff-----------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* CHECK: NOPARSE
   * The z-coordinate is set in Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication before this
   * function call so the condition is always false. But check is kept here for defensive
   * programming.
   */
  /* z-coordinate = 0 then the conversion is the infinity */
  if (0U == point->zValue[0U])
  {
    point->xValue[0U] = 0U;
    point->xValue[1U] = 0U;
    point->yValue[0U] = 1U;
    point->yValue[1U] = 1U;

  }
  else
  {
    /* Z = Z^(-1) */
    Crypto_xVIx_xAIx_LNInversion(point->zValue,
                                 point->zValue,
                                 &(tmp[tmp1]),
                                 &(tmp[tmp2]),
                                 &(tmp[tmp3]),
                                 Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime,
                                 &(edCtx->lnCtx)
                                );

    /* X = X * Z */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(point->xValue,
                                       point->xValue,
                                       point->zValue,
                                       &(edCtx->lnCtx)
                                      );
    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(point->xValue, edCtx);

    /* Y = Y * Z */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(point->yValue,
                                       point->yValue,
                                       point->zValue,
                                       &(edCtx->lnCtx)
                                      );
    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(point->yValue, edCtx);
  }
  /* CHECK: PARSE */

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF == STD_ON) */

/*----- ECC NIST --------------------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON)

/*----- Fast Reduction SecP256r1 / NIST P-256 ----------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_ECP256FastReduction/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReduction
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  Crypto_xVIx_xAIx_LNWordType temp[CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES) + 1U];

#if (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_64)

  Crypto_xVIx_xAIx_LNWordType buffer[CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES)];

  /* Set the higher positions of the value to zero if necessary */
  for (buffer[0U] = (value[0U] + 1U); buffer[0U] < CRYPTO_XVIX_XAIX_MAX_TEMP_LEN_WORDS(CRYPTO_XVIX_XAIX_CURVE_SECP256R1_PRIVKEY_LEN_BYTES); buffer[0U]++)
  {
    value[buffer[0U]] = 0U;
  }

  /* Calculate s1, s2 and s3 */
  Crypto_xVIx_xAIx_ECP256FastReductionCalcValue1(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + s3 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* value = s1 + 2*s2 + 2*s3 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* Calculate s4, s5 and s6 */
  Crypto_xVIx_xAIx_ECP256FastReductionCalcValue2(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + 2*s3 + s4 + s5 - s6 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* Calculate s7, s8 and s9 */
  Crypto_xVIx_xAIx_ECP256FastReductionCalcValue3(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + 2*s3 + s4 + s5 - s6 - s7  - s8 - s9 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);
#else /* #if (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_64) */

#error Unsupported CPU_TYPE

#endif /* #if (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_64) #else */
}

/*----- Fast Reduction SecP384r1 / NIST P-384 ----------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_ECP384FastReduction/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReduction
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  Crypto_xVIx_xAIx_LNWordType temp[CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES) + 1U];

#if (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_64)

  Crypto_xVIx_xAIx_LNWordType buffer[CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES)];

  /* Set the higher positions of the value to zero if necessary */
  for (buffer[0U] = (value[0U] + 1U); buffer[0U] < CRYPTO_XVIX_XAIX_MAX_TEMP_LEN_WORDS(CRYPTO_XVIX_XAIX_CURVE_SECP384R1_PRIVKEY_LEN_BYTES); buffer[0U]++)
  {
    value[buffer[0U]] = 0U;
  }

  /* Calculate s1, s2 and s3 */
  Crypto_xVIx_xAIx_ECP384FastReductionCalcValue1(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + s3 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* Calculate s4, s5 and s6 */
  Crypto_xVIx_xAIx_ECP384FastReductionCalcValue2(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + s3 + s4 + s5 + s6 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* Calculate s7 and s8 */
  Crypto_xVIx_xAIx_ECP384FastReductionCalcValue3(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + s3 + s4 + s5 + s6 + s7 - s8 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* Calculate s9 and s10 */
  Crypto_xVIx_xAIx_ECP384FastReductionCalcValue4(value, temp, buffer, ctxPtr);

  /* value = s1 + 2*s2 + s3 + s4 + s5 + s6 + s7 - s8 - s9 - s10 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);
#else /* #if (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_64) */

#error Unsupported CPU_TYPE

#endif /* #if (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_64) #else */
}

/*----- ECC NIST Point Multiplication ------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_ECPointMultiplication/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointMultiplication
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2CONST(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicand,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* first the result shall be set to the point of infinity. */
  result->xValue[0U] = 0U;
  result->xValue[1U] = 0U;
  result->yValue[0U] = 1U;
  result->yValue[1U] = 1U;
  result->zValue[0U] = 0U;
  result->zValue[1U] = 0U;

  ctxPtr->currentBit = Crypto_xVIx_xAIx_LNBitLengthOfNumber(multiplicand);
  while(0U < ctxPtr->currentBit)
  {
    ctxPtr->currentBit--;
    Crypto_xVIx_xAIx_ECSimplePointDoubling(
                                         result,
                                         result,
                                         tmp1,
                                         tmp2,
                                         tmp3,
                                         tmp4,
                                         ctxPtr
                                       );

    if (1U == CRYPTO_XVIX_XAIX_LN_GET_BIT(multiplicand, ctxPtr->currentBit))
    {
      Crypto_xVIx_xAIx_ECPointAddition(
                                           result,
                                           result,
                                           point,
                                           tmp1,
                                           tmp2,
                                           tmp3,
                                           tmp4,
                                           ctxPtr
                                         );
    }
  }
}

/*----- ECC NIST Point Addition ------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_ECPointAddition/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAddition
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  boolean Finished = FALSE;

  Crypto_xVIx_xAIx_ECPointAdditionCheckInfinity(
                                                 result,
                                                 addend1,
                                                 addend2,
                                                 &Finished
                                                );
  if(FALSE == Finished)
  {
    /* Calculate A and B */
    Crypto_xVIx_xAIx_ECPointAdditionCalcAB(result, addend1, addend2, tmp1, tmp2, ctxPtr);

    /* Z3 = Z1 * Z2 */
    Crypto_xVIx_xAIx_LNMultiplyNumbers
    (
      result->zValue,
      addend1->zValue,
      addend2->zValue,
      &ctxPtr->lnCtx
    );
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->zValue, ctxPtr);

    /* Calculate C */
    Crypto_xVIx_xAIx_ECPointAdditionCalcC(result, tmp2, tmp3, tmp4, ctxPtr);

    /* Z3: Calculate Final result */
    Crypto_xVIx_xAIx_ECPointAdditionCalcFinalZ3(result, ctxPtr);

    /* Calculate intern results for the point addition */
    Crypto_xVIx_xAIx_ECPointAdditionCalcInterimTmp4(result, tmp2, tmp3, tmp4, ctxPtr);

    /* X3 and Y3: Calculate final results */
    Crypto_xVIx_xAIx_ECPointAdditionCalcFinalX3Y3(result, tmp1, tmp3, tmp4, ctxPtr);
  }
}

/*----- ECC NIST Point of Infinity ---------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/Ecc/Crypto_xVIx_xAIx_ECProjectivePointOfInfinity/0001,1 */

FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECProjectivePointOfInfinity
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point
)
{
  boolean result;

  /* In projective coordinates the point of infintity corresponds to
   * the point (X : Y : Z) = (0 : 1 : 0).
   */
  if
  (
    (0U == point->xValue[0U])                                &&
   ((1U == point->yValue[0U])  && (1U == point->yValue[1U])) &&
    (0U == point->zValue[0U])
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/* ---ED25519 / ED25519PH / X25519 -------------------------------------------------------------- */

/*---Crypto_xVIx_xAIx_EdDSAFastReductionCompA ----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAFastReductionCompA
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value
)
{
  /* A1, the last 8 items of value */
  tmp[8U] =   (Crypto_xVIx_xAIx_LNWordType) (value[16U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[15U] >> 31U);
  tmp[7U] =   (Crypto_xVIx_xAIx_LNWordType) (value[15U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[14U] >> 31U);
  tmp[6U] =   (Crypto_xVIx_xAIx_LNWordType) (value[14U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[13U] >> 31U);
  tmp[5U] =   (Crypto_xVIx_xAIx_LNWordType) (value[13U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[12U] >> 31U);
  tmp[4U] =   (Crypto_xVIx_xAIx_LNWordType) (value[12U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[11U] >> 31U);
  tmp[3U] =   (Crypto_xVIx_xAIx_LNWordType) (value[11U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[10U] >> 31U);
  tmp[2U] =   (Crypto_xVIx_xAIx_LNWordType) (value[10U] << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[9U]  >> 31U);
  tmp[1U] =   (Crypto_xVIx_xAIx_LNWordType) (value[9U]  << 1U)
            | (Crypto_xVIx_xAIx_LNWordType) (value[8U]  >> 31U);
  tmp[0U] =   (Crypto_xVIx_xAIx_LNWordType) 8U; /* the size of the number */

  /* normalize tmp */
  Crypto_xVIx_xAIx_LNNormalizeNumber(tmp);

  /* value = A2 */
  value[0U]  = 8U;
  value[8U] &= (Crypto_xVIx_xAIx_LNWordType) 0x7FFFFFFFUL;

  /* normalize value */
  Crypto_xVIx_xAIx_LNNormalizeNumber(value);
}
#endif /*#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPA == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAFastReductionCompB ----------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAFastReductionCompB
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value
)
{
  /* Store for B1 : 4-bits */
  *tmp = value[8U] >> 27U;

  /* value = B2 */
  value[8U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[8U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[7U] >> 28U);
  value[7U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[7U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[6U] >> 28U);
  value[6U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[6U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[5U] >> 28U);
  value[5U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[5U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[4U] >> 28U);
  value[4U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[4U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[3U] >> 28U);
  value[3U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[3U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[2U] >> 28U);
  value[2U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[2U] << 4U)
               | (Crypto_xVIx_xAIx_LNWordType) (value[1U] >> 28U);
  value[1U]  =   (Crypto_xVIx_xAIx_LNWordType) (value[1U] << 4U);
  value[0U]  = 8U;

  value[8U] &= (Crypto_xVIx_xAIx_LNWordType) 0x7FFFFFFFUL;

  Crypto_xVIx_xAIx_LNNormalizeNumber(value);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTIONCOMPB == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointDoubling ---------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingProcedure
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  /* tmp1    Offset where G is stored. */
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp2    Offset where G is stored. */
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp3    Offset where G is stored. */
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp4    Offset where A is stored. */
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp5    Offset where B is stored. */
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* if the Point is infinity, no calculation is necessary */
  if (   ( 0U == value->xValue[0U] )
      && ((1U == value->yValue[0U])  && (1U == value->yValue[1U]))
      && ((1U == value->zValue[0U])  && (1U == value->zValue[1U]))
     )
  {
    result->xValue[0U] = 0U;
    result->xValue[1U] = 0U;
    result->yValue[0U] = 1U;
    result->yValue[1U] = 1U;
    result->zValue[0U] = 1U;
    result->zValue[1U] = 1U;
  }
  else
  {
    /* tmp1 = X1 + Y1 */
    Crypto_xVIx_xAIx_LNAdditionModular(
                              &tmp[tmp1],
                              value->xValue,
                              value->yValue,
                              Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                            );

    /* tmp2 = X1 * X1 */
    Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp2], value->xValue, &(edCtx->lnCtx));

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp2], edCtx);

    /* tmp3 = Y1 * Y1 */
    Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp3], value->yValue, &(edCtx->lnCtx));

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);

    /* a = -1: tmp4 = Prime - 1*/
    (&tmp[tmp5])[0U] = 1U;
    (&tmp[tmp5])[1U] = 1U;

    Crypto_xVIx_xAIx_LNSubtractionModular(
                                 &tmp[tmp4],
                                 Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime,
                                 &tmp[tmp5],
                                 Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                               );

    /* E : tmp4 = tmp4 * tmp2 */
    /* F = E + D: tmp4 + tmp3 */
    Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateEF(tmp, edCtx);

    /* B : tmp1 ^ 2 = (X1 + Y1)^2 */
    Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateB(tmp, edCtx);

    /* Y3 = F * (E - D): tmp5 * tmp4 */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        result->yValue,
                                        &tmp[tmp5],
                                        &tmp[tmp4],
                                        &(edCtx->lnCtx)
                                      );

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->yValue, edCtx);

    /* H: tmp4 = Z1 * Z1 */
    Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateH(
                                                    value,
                                                    tmp,
                                                    edCtx
                                                  );

    /* Z3 = F * J: tmp5 * tmp4 - Final result */
    Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateZ3(
                                                    result,
                                                    tmp,
                                                    edCtx
                                                  );

    /* X3 = tmp1 * J - Final result */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        result->xValue,
                                        &tmp[tmp1],
                                        &tmp[tmp4],
                                        &(edCtx->lnCtx)
                                      );
    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->xValue, edCtx);
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGPROCEDURE == STD_ON) */

/* ---Sub Functions ----------------------------------------------------------------------------- */

/* ---Point additoin ---------------------------------------------------------------------------- */

/*---Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateCDE----------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateCDE
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  /* tmp1    Offset where C is stored. */
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp2    Offset where D is stored. */
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp3    Offset where E is stored. */
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* C: tmp1 = X1 * X2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp1],
                                      addent1->xValue,
                                      addent2->xValue,
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp1], edCtx);

  /* D: tmp2 = Y1 * Y2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp2],
                                      addent1->yValue,
                                      addent2->yValue,
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp2], edCtx);

  /* E: tmp3 = DValue * tmp1 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp3],
                                      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].coeff1,
                                      &tmp[tmp1],
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);

  /* E: tmp3 = tmp3 * tmp2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp3],
                                      &tmp[tmp3],
                                      &tmp[tmp2],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATECDE == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateA2 ----------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateA2
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  /* tmp3    Offset where G is stored. */
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp4    Offset where A is stored. */
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp5    Offset where B is stored. */
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  /* tmp6    Offset where F is stored. */
  const uint32 tmp6 = (5U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* B = A^2: tmp5 = tmp4 * tmp4 */
  Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp5], &tmp[tmp4], &(edCtx->lnCtx));

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp5], edCtx);

  /* F: tmp6 = tmp5 - tmp3 */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                         &tmp[tmp6],
                                         &tmp[tmp5],
                                         &tmp[tmp3],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                       );

  /* G: tmp3 = tmp5 + tmp3 */
  Crypto_xVIx_xAIx_LNAdditionModular(
                                      &tmp[tmp3],
                                      &tmp[tmp5],
                                      &tmp[tmp3],
                                      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                    );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEA2 == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateZ3-----------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateZ3
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* Z3 = tmp6 * tmp3 : Final result */

  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      result->zValue,
                                      &tmp[tmp6],
                                      &tmp[tmp3],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->zValue, edCtx);

  /* tmp5 = X1 + Y1 */
  Crypto_xVIx_xAIx_LNAdditionModular(
                                      &tmp[tmp5],
                                      addent1->xValue,
                                      addent1->yValue,
                                      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                    );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEZ3 == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateAF-----------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateAF
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addent2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx

)
{
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      result->xValue,
                                      &tmp[tmp4],
                                      &tmp[tmp6],
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->xValue, edCtx);

  /* tmp6 = X2 + Y2 */
  Crypto_xVIx_xAIx_LNAdditionModular(
                                      &tmp[tmp6],
                                      addent2->xValue,
                                      addent2->yValue,
                                      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                    );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEAF == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateInterimTmp5--------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateInterimTmp5
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* tmp5 = tmp5 * tmp6 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp5],
                                      &tmp[tmp5],
                                      &tmp[tmp6],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp5], edCtx);

  /* tmp5 = tmp5 - C */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                         &tmp[tmp5],
                                         &tmp[tmp5],
                                         &tmp[tmp1],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                       );

  /* tmp5 = tmp5 - tmp2 */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                         &tmp[tmp5],
                                         &tmp[tmp5],
                                         &tmp[tmp2],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                       );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEINTERIMTMP5 == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateFinalX3------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointAdditionCalculateFinalX3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  edCtx
)
{
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      result->xValue,
                                      result->xValue,
                                      &tmp[tmp5],
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->xValue, edCtx);

  /* tmp5 = D + C: tmp2 + tmp1 */
  Crypto_xVIx_xAIx_LNAdditionModular(
                                      &tmp[tmp5],
                                      &tmp[tmp2],
                                      &tmp[tmp1],
                                      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                    );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITIONCALCULATEFINALX3 == STD_ON) */

/* ---Point doubling ---------------------------------------------------------------------------- */

/*---Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateEF ----------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateEF
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  /* E : tmp4 = tmp4 * tmp2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(&tmp[tmp4], &tmp[tmp4], &tmp[tmp2], &(edCtx->lnCtx));
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp4], edCtx);

  /* F = E + D: tmp4 + tmp3 */
  Crypto_xVIx_xAIx_LNAdditionModular(
                            &tmp[tmp5],
                            &tmp[tmp4],
                            &tmp[tmp3],
                            Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                          );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEEF == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateB------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateB
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp1], &tmp[tmp1], &(edCtx->lnCtx));

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp1], edCtx);

  /* tmp4 = E - D: tmp4 - tmp3 */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                          &tmp[tmp4],
                                          &tmp[tmp4],
                                          &tmp[tmp3],
                                          Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                        );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEB == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateH------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateH
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp4], value->zValue, &(edCtx->lnCtx));

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp4], edCtx);

  /* tmp4 = 2 * H */
  Crypto_xVIx_xAIx_LNAdditionModular(
                            &tmp[tmp4],
                            &tmp[tmp4],
                            &tmp[tmp4],
                            Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                          );

  /* J: tmp4 = tmp5 - tmp4 */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                               &tmp[tmp4],
                               &tmp[tmp5],
                               &tmp[tmp4],
                               Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                             );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEH == STD_ON) */

/*---Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateZ3-----------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAPointDoublingCalculateZ3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS);

  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      result->zValue,
                                      &tmp[tmp5],
                                      &tmp[tmp4],
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(result->zValue, edCtx);

  /* tmp1 = B - C */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                         &tmp[tmp1],
                                         &tmp[tmp1],
                                         &tmp[tmp2],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                       );

  /* tmp1 = tmp1 - D */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                         &tmp[tmp1],
                                         &tmp[tmp1],
                                         &tmp[tmp3],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                       );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTDOUBLINGCALCULATEZ3 == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON)

/*----- ECC P-256 Fast Reduction -----------------------------------------------------------------*/

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReductionCalcValue1
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Save some elements of value */
  buffer[7U] = value[16U];
  buffer[6U] = value[15U];
  buffer[5U] = value[14U];
  buffer[4U] = value[13U];
  buffer[3U] = value[12U];
  buffer[2U] = value[11U];
  buffer[1U] = value[10U];
  buffer[0U] = value[9U];

  /* temp = s2 */
  temp[8U] = value[16U];
  temp[7U] = value[15U];
  temp[6U] = value[14U];
  temp[5U] = value[13U];
  temp[4U] = value[12U];
  temp[3U] = 0x00U;
  temp[2U] = 0x00U;
  temp[1U] = 0x00U;
  temp[0U] = 0x08U;

  /* value = s1 */
  value[0U] = 8U;

  /* value = s1 + s2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* value = s1 + 2*s2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s3 */
  temp[8U] = 0x00U;
  temp[7U] = buffer[7U];
  temp[6U] = buffer[6U];
  temp[5U] = buffer[5U];
  temp[4U] = buffer[4U];
  temp[3U] = 0x00U;
  temp[2U] = 0x00U;
  temp[1U] = 0x00U;
  temp[0U] = 0x07U;
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReductionCalcValue2
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* s4 */
  temp[8U] = buffer[7U];
  temp[7U] = buffer[6U];
  temp[6U] = 0x00U;
  temp[5U] = 0x00U;
  temp[4U] = 0x00U;
  temp[3U] = buffer[2U];
  temp[2U] = buffer[1U];
  temp[1U] = buffer[0U];
  temp[0U] = 0x08U;

  /* value = s1 + 2*s2 + 2*s3 + s4 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s5 */
  temp[8U] = buffer[0U];
  temp[7U] = buffer[5U];
  temp[6U] = buffer[7U];
  temp[5U] = buffer[6U];
  temp[4U] = buffer[5U];
  temp[3U] = buffer[3U];
  temp[2U] = buffer[2U];
  temp[1U] = buffer[1U];
  temp[0U] = 0x08U;

  /* value = s1 + 2*s2 + 2*s3 + s4 + s5 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s6 */
  temp[8U] = buffer[2U];
  temp[7U] = buffer[0U];
  temp[6U] = 0x00U;
  temp[5U] = 0x00U;
  temp[4U] = 0x00U;
  temp[3U] = buffer[5U];
  temp[2U] = buffer[4U];
  temp[1U] = buffer[3U];
  temp[0U] = 0x08U;
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReductionCalcValue3
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* s7 */
  temp[8U] = buffer[3U];
  temp[7U] = buffer[1U];
  temp[6U] = 0x00U;
  temp[5U] = 0x00U;
  temp[4U] = buffer[7U];
  temp[3U] = buffer[6U];
  temp[2U] = buffer[5U];
  temp[1U] = buffer[4U];
  temp[0U] = 0x08U;

  /* value = s1 + 2*s2 + 2*s3 + s4 + s5 - s6 - s7 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s8 */
  temp[8U] = buffer[4U];
  temp[7U] = 0x00U;
  temp[6U] = buffer[2U];
  temp[5U] = buffer[1U];
  temp[4U] = buffer[0U];
  temp[3U] = buffer[7U];
  temp[2U] = buffer[6U];
  temp[1U] = buffer[5U];
  temp[0U] = 0x08U;

  /* value = s1 + 2*s2 + 2*s3 + s4 + s5 - s6 - s7  - s8 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s9 */
  temp[8U] = buffer[5U];
  temp[7U] = 0x00U;
  temp[6U] = buffer[3U];
  temp[5U] = buffer[2U];
  temp[4U] = buffer[1U];
  temp[3U] = 0x00U;
  temp[2U] = buffer[7U];
  temp[1U] = buffer[6U];
  temp[0U] = 0x08U;
}

/*----- SecP384r1 / NIST P-384 -------------------------------------------------------------------*/

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue1
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Save some elements of value */
  buffer[11U] = value[24U];
  buffer[10U] = value[23U];
  buffer[9U ] = value[22U];
  buffer[8U ] = value[21U];
  buffer[7U ] = value[20U];
  buffer[6U ] = value[19U];
  buffer[5U ] = value[18U];
  buffer[4U ] = value[17U];
  buffer[3U ] = value[16U];
  buffer[2U ] = value[15U];
  buffer[1U ] = value[14U];
  buffer[0U ] = value[13U];

  /* temp = s2 */
  temp[12U] = 0x00U;
  temp[11U] = 0x00U;
  temp[10U] = 0x00U;
  temp[9U ] = 0x00U;
  temp[8U ] = 0x00U;
  temp[7U ] = value[24U];
  temp[6U ] = value[23U];
  temp[5U ] = value[22U];
  temp[4U ] = 0x00U;
  temp[3U ] = 0x00U;
  temp[2U ] = 0x00U;
  temp[1U ] = 0x00U;
  temp[0U ] = 7U;

  /* value = s1 */
  value[0U] = 12U;

  /* value = s1 + s2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* value = s1 + 2*s2 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s3 */
  temp[12U] = buffer[11U];
  temp[11U] = buffer[10U];
  temp[10U] = buffer[9U];
  temp[9U ] = buffer[8U];
  temp[8U ] = buffer[7U];
  temp[7U ] = buffer[6U];
  temp[6U ] = buffer[5U];
  temp[5U ] = buffer[4U];
  temp[4U ] = buffer[3U];
  temp[3U ] = buffer[2U];
  temp[2U ] = buffer[1U];
  temp[1U ] = buffer[0U];
  temp[0U ] = 12U;
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue2
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* s4 */
  temp[12U] = buffer[8U];
  temp[11U] = buffer[7U];
  temp[10U] = buffer[6U];
  temp[9U ] = buffer[5U];
  temp[8U ] = buffer[4U];
  temp[7U ] = buffer[3U];
  temp[6U ] = buffer[2U];
  temp[5U ] = buffer[1U];
  temp[4U ] = buffer[0U];
  temp[3U ] = buffer[11U];
  temp[2U ] = buffer[10U];
  temp[1U ] = buffer[9U];
  temp[0U ] = 12U;

  /* value = s1 + 2*s2 + s3 + s4 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s5 */
  temp[12U] = buffer[7U];
  temp[11U] = buffer[6U];
  temp[10U] = buffer[5U];
  temp[9U ] = buffer[4U];
  temp[8U ] = buffer[3U];
  temp[7U ] = buffer[2U];
  temp[6U ] = buffer[1U];
  temp[5U ] = buffer[0U];
  temp[4U ] = buffer[8U];
  temp[3U ] = 0x00U;
  temp[2U ] = buffer[11U];
  temp[1U ] = 0x00U;
  temp[0U ] = 12U;

  /* value = s1 + 2*s2 + s3 + s4 + s5 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s6 */
  temp[12U] = 0x00U;
  temp[11U] = 0x00U;
  temp[10U] = 0x00U;
  temp[9U ] = 0x00U;
  temp[8U ] = buffer[11U];
  temp[7U ] = buffer[10U];
  temp[6U ] = buffer[9U ];
  temp[5U ] = buffer[8U ];
  temp[4U ] = 0x00U;
  temp[3U ] = 0x00U;
  temp[2U ] = 0x00U;
  temp[1U ] = 0x00U;
  temp[0U ] = 8U;
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue3
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* s7 */
  temp[12U] = 0x00U;
  temp[11U] = 0x00U;
  temp[10U] = 0x00U;
  temp[9U ] = 0x00U;
  temp[8U ] = 0x00U;
  temp[7U ] = 0x00U;
  temp[6U ] = buffer[11U];
  temp[5U ] = buffer[10U];
  temp[4U ] = buffer[9U ];
  temp[3U ] = 0x00U;
  temp[2U ] = 0x00U;
  temp[1U ] = buffer[8U ];
  temp[0U ] = 6U;

  /* value = s1 + 2*s2 + s3 + s4 + s5 + s6 + s7 */
  Crypto_xVIx_xAIx_LNAdditionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s8 */
  temp[12U] = buffer[10U];
  temp[11U] = buffer[9U ];
  temp[10U] = buffer[8U ];
  temp[9U ] = buffer[7U ];
  temp[8U ] = buffer[6U ];
  temp[7U ] = buffer[5U ];
  temp[6U ] = buffer[4U ];
  temp[5U ] = buffer[3U ];
  temp[4U ] = buffer[2U ];
  temp[3U ] = buffer[1U ];
  temp[2U ] = buffer[0U ];
  temp[1U ] = buffer[11U];
  temp[0U ] = 12U;
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReductionCalcValue4
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) temp,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* s9 */
  temp[12U] = 0x00U;
  temp[11U] = 0x00U;
  temp[10U] = 0x00U;
  temp[9U ] = 0x00U;
  temp[8U ] = 0x00U;
  temp[7U ] = 0x00U;
  temp[6U ] = 0x00U;
  temp[5U ] = buffer[11U];
  temp[4U ] = buffer[10U];
  temp[3U ] = buffer[9U ];
  temp[2U ] = buffer[8U ];
  temp[1U ] = 0x00U;
  temp[0U ] = 5U;

  /* value = s1 + 2*s2 + s3 + s4 + s5 + s6 + s7 - s8 - s9 */
  Crypto_xVIx_xAIx_LNSubtractionModular(value, value, temp, Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime);

  /* s10 */
  temp[12U] = 0x00U;
  temp[11U] = 0x00U;
  temp[10U] = 0x00U;
  temp[9U ] = 0x00U;
  temp[8U ] = 0x00U;
  temp[7U ] = 0x00U;
  temp[6U ] = 0x00U;
  temp[5U ] = buffer[11U];
  temp[4U ] = buffer[11U];
  temp[3U ] = 0x00U;
  temp[2U ] = 0x00U;
  temp[1U ] = 0x00U;
  temp[0U ] = 5U;
}

/*----- ECC NIST Point Addition ------------------------------------------------------------------*/

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCheckInfinity
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(boolean,                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) finished
)
{
  /* if the addend1 is the Point of infinity, the result is the addend2 */
  if (TRUE == Crypto_xVIx_xAIx_ECProjectivePointOfInfinity(addend1))
  {

    TS_MemCpy(result->xValue, addend2->xValue, (addend2->xValue[0U] + 1U) << 2U);
    TS_MemCpy(result->yValue, addend2->yValue, (addend2->yValue[0U] + 1U) << 2U);
    TS_MemCpy(result->zValue, addend2->zValue, (addend2->zValue[0U] + 1U) << 2U);

    *finished = TRUE;
  }
  /* if the addend2 is the Point of infinity, the result is the addend1 */
  else
  if (TRUE == Crypto_xVIx_xAIx_ECProjectivePointOfInfinity(addend2))
  {
    TS_MemCpy(result->xValue, addend1->xValue, (addend1->xValue[0U] + 1U) << 2U);
    TS_MemCpy(result->yValue, addend1->yValue, (addend1->yValue[0U] + 1U) << 2U);
    TS_MemCpy(result->zValue, addend1->zValue, (addend1->zValue[0U] + 1U) << 2U);

    *finished = TRUE;
  }
  else
  {
    /* Nothing to do. */
  }
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcAB
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Tmp1 = Y1 * Z2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp1,
    addend1->yValue,
    addend2->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp1, ctxPtr);

  /* Tmp2 = X1 * Z2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp2,
    addend1->xValue,
    addend2->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp2, ctxPtr);

  /* We are using the result array as temporary storage. But we have to
   * be careful because the input and output points can be the same
   * storage. So, e.g., after setting result->xValue we can no longer use
   * addend1->xValue nor addend2->xValue.
   */

  /* Y3 = Y2 * Z1 - Tmp1 = A */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->yValue,
    addend2->yValue,
    addend1->zValue,
    &ctxPtr->lnCtx
  );

  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->yValue, ctxPtr);

  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    result->yValue,
    result->yValue,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* X3 = X2 * Z1 - Tmp2 = B */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->xValue,
    addend2->xValue,
    addend1->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->xValue, ctxPtr);

  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    result->xValue,
    result->xValue,
    tmp2,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcC
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Tmp4 = Y3^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp4,
    result->yValue,
    result->yValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp4, ctxPtr);

  /* Tmp4 = Tmp4 * Z3 = (Y3^2) * Z3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp4,
    tmp4,
    result->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp4, ctxPtr);

  /* Tmp3 = X3 + 2 * Tmp2 */
  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp3,
    tmp2,
    tmp2,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp3,
    result->xValue,
    tmp3,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp3 = X3 * Tmp3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp3,
    tmp3,
    result->xValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp3, ctxPtr);

  /* Tmp3 = X3 * Tmp3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp3,
    tmp3,
    result->xValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp3, ctxPtr);

  /* Tmp3 = Tmp4 - Tmp3 = C */
  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    tmp3,
    tmp4,
    tmp3,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcFinalZ3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Z3 = X3 * Z3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->zValue,
    result->xValue,
    result->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->zValue, ctxPtr);

  /* Z3 = X3 * Z3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->zValue,
    result->xValue,
    result->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->zValue, ctxPtr);

  /* Z3 = X3 * Z3 (final result) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->zValue,
    result->xValue,
    result->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->zValue, ctxPtr);
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcInterimTmp4
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Tmp4 = X3^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp4,
    result->xValue,
    result->xValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp4, ctxPtr);

  /* Tmp4 = Tmp4 * Tmp2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp4,
    tmp4,
    tmp2,
    &ctxPtr->lnCtx
    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp4, ctxPtr);

  /* Tmp4 = Tmp4 - Tmp3 */
  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    tmp4,
    tmp4,
    tmp3,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp4 = Y3 * Tmp4 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp4,
    result->yValue,
    tmp4,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp4, ctxPtr);
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAdditionCalcFinalX3Y3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Y3 = X3^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->yValue,
    result->xValue,
    result->xValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->yValue, ctxPtr);

  /* Y3 = Y3 * X3 = X3^3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->yValue,
    result->yValue,
    result->xValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->yValue, ctxPtr);

  /* Y3 = Y3 * Tmp1 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->yValue,
    result->yValue,
    tmp1,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->yValue, ctxPtr);

  /* Y3 = Tmp4 - Y3 (final result) */
  Crypto_xVIx_xAIx_LNSubtractionModular
  (
     result->yValue,
     tmp4,
     result->yValue,
     Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* X3 = X3*Tmp3 (final result) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->xValue,
    result->xValue,
    tmp3,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->xValue, ctxPtr);
}

/*----- ECC NIST Point Doubling ------------------------------------------------------------------*/

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoubling
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* If the point is the point in infinity, there is no calculation
   * necessary.
   */
  if (TRUE == Crypto_xVIx_xAIx_ECProjectivePointOfInfinity(value))
  {
    result->xValue[0U] = 0U;
    result->xValue[1U] = 0U;
    result->yValue[0U] = 1U;
    result->yValue[1U] = 1U;
    result->zValue[0U] = 0U;
    result->zValue[1U] = 0U;
  }
  else
  {
    /* Calculate A */
    Crypto_xVIx_xAIx_ECSimplePointDoublingCalcAB(value, tmp1, tmp2, tmp4, ctxPtr);

    /* Calculate intern results for the point doubling */
    Crypto_xVIx_xAIx_ECSimplePointDoublingCalcInternTmp(result, value, tmp1, tmp2, tmp3, ctxPtr);

    /* Calculate D and Y3 (final result) */
    Crypto_xVIx_xAIx_ECSimplePointDoublingCalcFinalY3(result, tmp1, tmp2, tmp4, ctxPtr);

    /* X3 and Z3: Calculate final results */
    Crypto_xVIx_xAIx_ECSimplePointDoublingCalcFinalX3Z3(result, tmp2, tmp3, ctxPtr);
  }
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcAB
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Tmp1 = X1 - Z1 */
  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    tmp1,
    value->xValue,
    value->zValue,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp2 = X1 + Z1 */
  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp2,
    value->xValue,
    value->zValue,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp1 = Tmp1*Tmp2 = X1^2 - Z1^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      tmp1,
                                      tmp1,
                                      tmp2,
                                      &ctxPtr->lnCtx
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp1, ctxPtr);

  /* Tmp4 = 3*Tmp1 = 3(X1^2 - Z1^2) = A. Please note that the actual formula for A is
   * A = 3*X1^2 + a*Z1^2. So, we have assumed that a = -3.
   */
  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp4,
    tmp1,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp4,
    tmp4,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp1 = Y1*Z1 = B */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp1,
    value->yValue,
    value->zValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp1, ctxPtr);

}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcInternTmp
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Tmp3 = 2*Tmp1 = 2B */
  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp3,
    tmp1,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp1 = Y1*Tmp3 = 2B*Y1 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp1,
    value->yValue,
    tmp3,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp1, ctxPtr);

  /* Tmp2 = Tmp1^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp2,
    tmp1,
    tmp1,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp2, ctxPtr);

  /* Y3 = 2*Tmp2 */
  Crypto_xVIx_xAIx_LNAdditionModular
  (
    result->yValue,
    tmp2,
    tmp2,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp1 = 2*X1*Tmp1 = 4C */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    tmp1,
    tmp1,
    value->xValue,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp1, ctxPtr);

  Crypto_xVIx_xAIx_LNAdditionModular
  (
    tmp1,
    tmp1,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcFinalY3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Tmp2 = Tmp4^2 - 2*Tmp1 = D */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      tmp2,
                                      tmp4,
                                      tmp4,
                                      &ctxPtr->lnCtx
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp2, ctxPtr);

  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    tmp2,
    tmp2,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    tmp2,
    tmp2,
    tmp1,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp1 = Tmp1 - Tmp2 */
  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    tmp1,
    tmp1,
    tmp2,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );

  /* Tmp1 = Tmp4 * Tmp1 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      tmp1,
                                      tmp1,
                                      tmp4,
                                      &ctxPtr->lnCtx
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(tmp1, ctxPtr);

  /* Y3 = Tmp1 - Y3 (final result) */
  Crypto_xVIx_xAIx_LNSubtractionModular
  (
    result->yValue,
    tmp1,
    result->yValue,
    Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].prime
  );
}

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECSimplePointDoublingCalcFinalX3Z3
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
)
{
  /* Z3 = Tmp3^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->zValue,
    tmp3,
    tmp3,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->zValue, ctxPtr);

  /* Z3 = Z3 * Tmp3 (final result) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->zValue,
    result->zValue,
    tmp3,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->zValue, ctxPtr);

  /* X3 = Tmp2 * Tmp3 (final result) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    result->xValue,
    tmp2,
    tmp3,
    &ctxPtr->lnCtx
  );
  Crypto_xVIx_xAIx_EllipticCurveInfo[ctxPtr->curveIndex].fastReductionFun(result->xValue, ctxPtr);
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON) */
#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

