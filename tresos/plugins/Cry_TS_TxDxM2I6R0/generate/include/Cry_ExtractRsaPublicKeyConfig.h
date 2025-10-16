/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EXTRACTRSAPUBLICKEYCONFIG_H
#define CRY_EXTRACTRSAPUBLICKEYCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

#if (defined CRY_EXTRACTRSAPUBLICKEY_ENABLED)
#error CRY_EXTRACTRSAPUBLICKEY_ENABLED is already defined
#endif
/** \brief Indicates whether a ExtractRsaPublicKey configuration exists.
 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryExtractRsaPublicKey/CryExtractRsaPublicKeyConfig/*))"!][!//
#define CRY_EXTRACTRSAPUBLICKEY_ENABLED TRUE
[!ELSE!][!//
#define CRY_EXTRACTRSAPUBLICKEY_ENABLED FALSE
[!ENDIF!][!//

#if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE)

/*==================[type definitions]============================================================*/

/*---[struct]-------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0017, 1
 */
/** \brief  Configuration type for representing a configured RSA Public key extraction.
 **/
typedef struct
{
  uint32 KeyLength;
}
Cry_ExtractRsaPubKeyConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryExtractRsaPublicKey/CryExtractRsaPublicKeyConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryExtractRsaPublicKey/CryExtractRsaPublicKeyConfig/*"!][!//

/** \brief One Configuration of ExtractRsaPublicKey primitive.
 */
extern CONST(Cry_ExtractRsaPubKeyConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE) */

#endif /* #ifndef CRY_EXTRACTRSAPUBLICKEYCONFIG_H */
