/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_HMAC_CFG_H
#define CRY_HMAC_CFG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

/*==[Macros]==================================================================*/

[!VAR "CryHMACNumberLength" = "1"!][!//
[!LOOP "as:modconf('Cry')/CryHMACGen/CryHMACGenConfig/*"!][!//
   [!IF "($CryHMACNumberLength < num:i(node:value(./CryHMACKeyLength)))"!][!//
      [!VAR "CryHMACNumberLength" = "num:i(node:value(./CryHMACKeyLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "as:modconf('Cry')/CryHMACVrfy/CryHMACVrfyConfig/*"!][!//
   [!IF "($CryHMACNumberLength < num:i(node:value(./CryHMACKeyLength)))"!][!//
      [!VAR "CryHMACNumberLength" = "num:i(node:value(./CryHMACKeyLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

#if (defined CRY_HMAC_NUM_LEN_BYTES)
#error CRY_HMAC_NUM_LEN_BYTES is already defined
#endif
#define CRY_HMAC_NUM_LEN_BYTES [!"num:i($CryHMACNumberLength)"!]U

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* CRY_HMAC_CFG_H */
