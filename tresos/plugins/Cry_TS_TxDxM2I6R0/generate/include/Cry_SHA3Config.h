/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

[!INCLUDE "Cry_common.m"!][!//
[!//

#ifndef CRY_SHA3CONFIG_H
#define CRY_SHA3CONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_SHA_CommonConfig.h>

/*==[Macros]==================================================================*/

/* !LINKSTO EB_CRY_0018,1 */
#if (defined CRY_SHA3_ENABLED)
#error CRY_SHA3_ENABLED is already defined
#endif
#define CRY_SHA3_ENABLED [!"$CRY_SHA3_ENABLED"!]
[!IF "$CRY_SHA3_ENABLED = 'STD_ON'"!][!//

#if (defined CRY_SHA3_224_HASH_LEN_BYTES)
#error CRY_SHA3_224_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA3-224 algorithm in  bytes.
 **
 **/
#define CRY_SHA3_224_HASH_LEN_BYTES 28U

#if (defined CRY_SHA3_256_HASH_LEN_BYTES)
#error CRY_SHA3_256_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA3-256 algorithm in  bytes.
**
**/
#define CRY_SHA3_256_HASH_LEN_BYTES 32U

#if (defined CRY_SHA3_384_HASH_LEN_BYTES)
#error CRY_SHA3_384_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA3-384 algorithm in  bytes.
**
**/
#define CRY_SHA3_384_HASH_LEN_BYTES 48U

#if (defined CRY_SHA3_512_HASH_LEN_BYTES)
#error CRY_SHA3_512_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA3-512 algorithm in  bytes.
**
**/
#define CRY_SHA3_512_HASH_LEN_BYTES 64U

#if (defined CRY_SHA3_224_ALGORITHM_ID)
#error CRY_SHA3_224_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA3-224 hash algorithm
 **
 **/
#define CRY_SHA3_224_ALGORITHM_ID \
          0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, \
          0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x07, 0x05, \
          0x00, 0x04, 0x40

#if (defined CRY_SHA3_256_ALGORITHM_ID)
#error CRY_SHA3_256_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA3-256 hash algorithm
 **
 **/
#define CRY_SHA3_256_ALGORITHM_ID \
          0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, \
          0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x08, 0x05, \
          0x00, 0x04, 0x40

#if (defined CRY_SHA3_384_ALGORITHM_ID)
#error CRY_SHA3_384_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA3-384 hash algorithm
 **
 **/
#define CRY_SHA3_384_ALGORITHM_ID \
          0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, \
          0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x09, 0x05, \
          0x00, 0x04, 0x40

#if (defined CRY_SHA3_512_ALGORITHM_ID)
#error CRY_SHA3_512_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA3-512 hash algorithm
 **
 **/
#define CRY_SHA3_512_ALGORITHM_ID \
          0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, \
          0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x0a, 0x05, \
          0x00, 0x04, 0x40

#if (defined CRY_SHA3_IMMEDIATE_RESTART_ENABLED)
#error CRY_SHA3_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmHash/CsmHashImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CrySHA3/CrySHA3ImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SHA3_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SHA3_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SHA3_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

[!ENDIF!][!//
[!//

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

[!IF "$CRY_SHA3_ENABLED = 'STD_ON'"!][!//
#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CrySHA3/CrySHA3Config/*"!][!//
extern CONST(Cry_SHAConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif
