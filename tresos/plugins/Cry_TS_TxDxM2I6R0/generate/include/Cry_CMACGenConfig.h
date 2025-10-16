/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_CMACGENCONFIG_H
#define CRY_CMACGENCONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>

/*==[Macros]==================================================================*/

#if (defined CRY_CMAC_GEN_ENABLED)
#error CRY_CMAC_GEN_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCMACGen/CryCMACGenConfig/*))"!][!//
#define CRY_CMAC_GEN_ENABLED STD_ON
[!ELSE!][!//
#define CRY_CMAC_GEN_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_CMAC_GEN_ENABLED == STD_ON)

/*==[Types]===================================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/**
 *
 * \struct Cry_CMACGenConfigType
 * \brief The configuration of the CMAC generation
 *
 * \var Cry_CMACGenConfigType::SymBlockEncryptCfg
 * \brief The configuration of the underlying hash algorithm.
 *
 * \var uint8::MacType
 * \brief The configuration flag to select between OMAC1/CMAC or OMAC2.
 */
typedef struct
{
  Csm_ConfigIdType SymBlockEncryptCfg;
  uint8            MacType;
}
Cry_CMACGenConfigType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryCMACGen/CryCMACGenConfig/*"!][!//
extern CONST(Cry_CMACGenConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* #if (CRY_CMAC_GEN_ENABLED == STD_ON) */

#endif /* CRY_CMACGENCONFIG_H */
