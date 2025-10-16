/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_CBCPKCS7DECRYPTCONFIG_H
#define CRY_CBCPKCS7DECRYPTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm.h>

/*==================[macros]======================================================================*/

#if (defined CRY_CBC_PKCS7_DEC_ENABLED)
#error CRY_CBC_PKCS7_DEC_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCbcPkcs7Decrypt/CryCbcPkcs7DecryptConfig/*))"!][!//
#define CRY_CBC_PKCS7_DEC_ENABLED STD_ON
[!ELSE!][!//
#define CRY_CBC_PKCS7_DEC_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON)

/*==================[type definitions]============================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/** \brief  Configuration type for representing a configured AES algorithm.
 **/
typedef struct
{
  Csm_ConfigIdType symBlockDecryptCfgId;
}
Cry_CbcPkcs7DecryptConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryCbcPkcs7Decrypt/CryCbcPkcs7DecryptConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryCbcPkcs7Decrypt/CryCbcPkcs7DecryptConfig/*"!][!//
extern CONST(Cry_CbcPkcs7DecryptConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON) */

#endif /* #ifndef CRY_CBC_PKCS7_DECCONFIG_H */
