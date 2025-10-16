/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_HMAC_H
#define CRY_HMAC_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_HMACConfig.h>

/*==[Macros]==================================================================*/

#if (defined CRY_HMAC_HASH_BLOCK_LEN_BYTES)
#error CRY_HMAC_HASH_BLOCK_LEN_BYTES is already defined
#endif
/** \brief the length of one encryption block for the HMAC
 */
#define CRY_HMAC_HASH_BLOCK_LEN_BYTES 64U

#if (defined CRY_HMAC_HASH_MAX_LEN)
#error CRY_HMAC_HASH_MAX_LEN is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes.
 */
#define CRY_HMAC_HASH_MAX_LEN 32U

/* !LINKSTO CS_SECURE_CRY_0195,1 */
#if (defined CRY_HMAC_IPAD)
#error CRY_HMAC_IPAD is already defined
#endif
/** \brief Macro for the inner Padding according to RFC 2104.
 */
#define CRY_HMAC_IPAD 0x36

/* !LINKSTO CS_SECURE_CRY_0196,1 */
#if (defined CRY_HMAC_OPAD)
#error CRY_HMAC_OPAD is already defined
#endif
/** \brief Macro for the outer Padding according to RFC 2104
 */
#define CRY_HMAC_OPAD 0x5c

/*==[Types]===================================================================*/

/** \brief The key used for creating a signature */
typedef struct
{
  /** \brief Length of the key */
  uint32   KeyLength;
  /** \brief Array containting the key */
  uint8    Key[CRY_HMAC_NUM_LEN_BYTES];
}
Cry_HMACKeyType;

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* CRY_HMAC_H */
