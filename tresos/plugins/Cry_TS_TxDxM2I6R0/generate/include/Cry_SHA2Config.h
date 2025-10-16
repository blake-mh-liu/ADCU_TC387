/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

[!INCLUDE "Cry_common.m"!][!//
[!//
#ifndef CRY_SHA2CONFIG_H
#define CRY_SHA2CONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_SHA_CommonConfig.h>

/*==[Macros]==================================================================*/

/* !LINKSTO EB_CRY_0018,1 */
#if (defined CRY_SHA2_ENABLED)
#error CRY_SHA2_ENABLED is already defined
#endif
#define CRY_SHA2_ENABLED [!"$CRY_SHA2_ENABLED"!]
[!IF "$CRY_SHA2_ENABLED = 'STD_ON'"!][!//

#if (defined CRY_SHA224_HASH_LEN_BYTES)
#error CRY_SHA224_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA-224 algorithm in bytes.
 **/
#define CRY_SHA224_HASH_LEN_BYTES 28U

#if (defined CRY_SHA256_HASH_LEN_BYTES)
#error CRY_SHA256_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA-256 algorithm in bytes.
 **/
#define CRY_SHA256_HASH_LEN_BYTES 32U

#if (defined CRY_SHA384_HASH_LEN_BYTES)
#error CRY_SHA384_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA-384 algorithm in bytes.
 **/
#define CRY_SHA384_HASH_LEN_BYTES 48U

#if (defined CRY_SHA512_HASH_LEN_BYTES)
#error CRY_SHA512_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA-512 algorithm in bytes.
 **/
#define CRY_SHA512_HASH_LEN_BYTES 64U

#if (defined CRY_SHA2_BLOCK_LEN_BYTES)
#error CRY_SHA2_BLOCK_LEN_BYTES is already defined
#endif
/** \brief  A message which should be hashed is divided into blocks which are processed
 **         individually. This macro gives the length of a block in bytes.
 **/
#define CRY_SHA2_BLOCK_LEN_BYTES CRY_SHA_BLOCK_LEN_BYTES

#if (defined CRY_SHA_224_ALGORITHM_ID)
#error CRY_SHA_224_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA-224 hash algorithm
 **/
#define CRY_SHA_224_ALGORITHM_ID 0x30,0x0d,0x06,0x09,0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x04,0x05,0x00

#if (defined CRY_SHA_256_ALGORITHM_ID)
#error CRY_SHA_256_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA-256 hash algorithm
 **/
#define CRY_SHA_256_ALGORITHM_ID 0x30,0x0d,0x06,0x09,0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x01,0x05,0x00

#if (defined CRY_SHA_384_ALGORITHM_ID)
#error CRY_SHA_384_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA-384 hash algorithm
 **/
#define CRY_SHA_384_ALGORITHM_ID 0x30,0x0d,0x06,0x09,0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x02,0x05,0x00

#if (defined CRY_SHA_512_ALGORITHM_ID)
#error CRY_SHA_512_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA-512 hash algorithm
 **/
#define CRY_SHA_512_ALGORITHM_ID 0x30,0x0d,0x06,0x09,0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x03,0x05,0x00

[!ENDIF!][!//
[!//

#if (defined CRY_SHA2_WORD_SIZE)
#error CRY_SHA2_WORD_SIZE is already defined
#endif
/** \brief   Word size, in bits, used by the SHA algorithm
 **/
[!IF "((count(as:modconf('Cry')/CrySHA2/CrySHA2Config/*[CrySHA2Type = 'CRY_SHA_384']) > 0) or (count(as:modconf('Cry')/CrySHA2/CrySHA2Config/*[CrySHA2Type = 'CRY_SHA_512']) > 0))"!][!//
#define CRY_SHA2_WORD_SIZE 64U
[!ELSE!][!//
#define CRY_SHA2_WORD_SIZE 32U
[!ENDIF!][!//

#if (defined CRY_SHA2_IMMEDIATE_RESTART_ENABLED)
#error CRY_SHA2_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmHash/CsmHashImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CrySHA2/CrySHA2ImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SHA2_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SHA2_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SHA2_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

[!IF "($CRY_SHA1_ENABLED = 'STD_ON') or ($CRY_SHA2_ENABLED = 'STD_ON')"!][!//

#if (CRY_SHA2_WORD_SIZE == 32U)

#if (defined CRY_SHA_BLOCK_LEN_BYTES)
#error CRY_SHA_BLOCK_LEN_BYTES is already defined
#endif
/** \brief   Block size in uint32 words.
 **/
#define CRY_SHA_BLOCK_LEN_BYTES     64U

#endif

#if (CRY_SHA2_WORD_SIZE == 64U)

#if (defined CRY_SHA_BLOCK_LEN_BYTES)
#error CRY_SHA_BLOCK_LEN_BYTES is already defined
#endif
/** \brief   Block size in uint64 words.
 **          We use 2 uint32 for an uint64 and the block is 64 words long: 64 * (2 * uint32) = 128.
 **/
#define CRY_SHA_BLOCK_LEN_BYTES        128U

#endif

[!ENDIF!][!//

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

[!IF "$CRY_SHA2_ENABLED = 'STD_ON'"!][!//
#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CrySHA2/CrySHA2Config/*"!][!//
extern CONST(Cry_SHAConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif
