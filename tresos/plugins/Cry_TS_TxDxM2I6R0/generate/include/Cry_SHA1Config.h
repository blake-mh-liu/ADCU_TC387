/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

[!INCLUDE "Cry_common.m"!][!//
[!//
#ifndef CRY_SHA1CONFIG_H
#define CRY_SHA1CONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_SHA_CommonConfig.h>

/*==[Macros]==================================================================*/

/* !LINKSTO EB_CRY_0018,1 */
#if (defined CRY_SHA1_ENABLED)
#error CRY_SHA1_ENABLED is already defined
#endif
#define CRY_SHA1_ENABLED [!"$CRY_SHA1_ENABLED"!]
[!IF "$CRY_SHA1_ENABLED = 'STD_ON'"!][!//

#if (defined CRY_SHA1_HASH_LEN_BYTES)
#error CRY_SHA1_HASH_LEN_BYTES is already defined
#endif
/** \brief  The length of a message digest computed with the SHA-1 algorithm in  bytes.
 **/
#define CRY_SHA1_HASH_LEN_BYTES 20U

#if (defined CRY_SHA1_BLOCK_LEN_BYTES)
#error CRY_SHA1_BLOCK_LEN_BYTES is already defined
#endif
/** \brief  A message which should be hashed is divided into blocks which are processed
 ** individually. This macro gives the length of a block in bytes.
 **/
#define CRY_SHA1_BLOCK_LEN_BYTES CRY_SHA_BLOCK_LEN_BYTES

#if (defined CRY_SHA_1_ALGORITHM_ID)
#error CRY_SHA_1_ALGORITHM_ID is already defined
#endif
/** \brief   The X.509 algorithm identifier of the SHA-1 hash algorithm
 **/
#define CRY_SHA_1_ALGORITHM_ID 0x30,0x09,0x06,0x05,0x2b,0x0e,0x03,0x02,0x1a,0x05,0x00

#if (defined CRY_SHA1_IMMEDIATE_RESTART_ENABLED)
#error CRY_SHA1_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmHash/CsmHashImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CrySHA1/CrySHA1ImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SHA1_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SHA1_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SHA1_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

[!ENDIF!][!//

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

[!IF "$CRY_SHA1_ENABLED = 'STD_ON'"!][!//
#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CrySHA1/CrySHA1Config/*"!][!//
extern CONST(Cry_SHAConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif
