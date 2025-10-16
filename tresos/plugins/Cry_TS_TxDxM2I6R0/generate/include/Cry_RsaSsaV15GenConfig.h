/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_RSASSAV15_G_CFG_H
#define CRY_RSASSAV15_G_CFG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_LN.h>

/*==[Macros]==================================================================*/

#if (defined CRY_RSASSAV15_GEN_ENABLED)
#error CRY_RSASSAV15_GEN_ENABLED is already defined
#endif
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryRsaSsaV15Generate/CryRsaSsaV15GenerateConfig/*))"!][!//
#define CRY_RSASSAV15_GEN_ENABLED TRUE
[!ELSE!][!//
#define CRY_RSASSAV15_GEN_ENABLED FALSE
[!ENDIF!][!//

#if (CRY_RSASSAV15_GEN_ENABLED == TRUE)

/*==[Types]===================================================================*/
/*
 * CHECK: NOPARSE

<api API="TYPES_EXTERN">
  <name>Cry_RsaSsaV15GenConfigType</name>
  <synopsis>The configuration of the RSASSA-PKCS1-v1_5 signature generation</synopsis>
  <syntax>
typedef struct
{
   Csm_ConfigIdType HashCfg;
}
Cry_RsaSsaV15GenConfigType;
  </syntax>
  <values>
    HashCfg=The configuration of the underlying hash algorithm.
  </values>
  <values>
    RandomCfg=The configuration of the underlying Random.
  </values>
  <values>
    CurveInfo=The configured elliptic curve.
  </values>
</api>

 * CHECK: PARSE
*/
typedef struct
{
   Csm_ConfigIdType HashCfg;
}
Cry_RsaSsaV15GenConfigType;


/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryRsaSsaV15Generate/CryRsaSsaV15GenerateConfig/*"!][!//
extern CONST(Cry_RsaSsaV15GenConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* #if (CRY_RSASSAV15_GEN_ENABLED == TRUE) */

#endif /* CRY_RSASSAV15_G_CFG_H */
