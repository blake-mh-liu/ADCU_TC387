/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EDDSACONFIG_H_
#define CRY_EDDSACONFIG_H_

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>

#include <Cry_LN.h>
#include <Cry_Common.h>

/*==[Macros]==================================================================*/

#if (defined CRY_EdDSA_ENABLED)
#error CRY_EdDSA_ENABLED is already defined
#endif
[!IF "(count(as:modconf('Cry')/CryEdDSAVrfy/CryEdDSAVrfyConfig/*) > 0) or
      (count(as:modconf('Cry')/CryEdDSAGen/CryEdDSAGenConfig/*) > 0)"!][!//
#if (defined CRY_EdDSA_NUMBER_LEN)
#error CRY_EdDSA_NUMBER_LEN is already defined
#endif
#define CRY_EdDSA_NUMBER_LEN 32U

#define CRY_EdDSA_ENABLED    STD_ON
[!ELSE!][!//
#define CRY_EdDSA_ENABLED    STD_OFF
[!ENDIF!][!//

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* CRY_EDDSACONFIG_H_ */
