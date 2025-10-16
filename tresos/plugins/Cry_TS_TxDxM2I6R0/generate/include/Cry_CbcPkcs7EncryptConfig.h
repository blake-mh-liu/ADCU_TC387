/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_CBCPKCS7ENCRYPTCONFIG_H
#define CRY_CBCPKCS7ENCRYPTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm.h>

/*==================[macros]======================================================================*/

#if (defined CRY_CBC_PKCS7_ENC_ENABLED)
#error CRY_CBC_PKCS7_ENC_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCbcPkcs7Encrypt/CryCbcPkcs7EncryptConfig/*))"!][!//
#define CRY_CBC_PKCS7_ENC_ENABLED STD_ON
[!ELSE!][!//
#define CRY_CBC_PKCS7_ENC_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_CBC_PKCS7_ENC_ENABLED == STD_ON)

/*==================[type definitions]============================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/** \brief  Configuration type for representing a configured AES algorithm.
 **/
typedef struct
{
  Csm_ConfigIdType symBlockEncryptCfgId;
}
Cry_CbcPkcs7EncryptConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryCbcPkcs7Encrypt/CryCbcPkcs7EncryptConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryCbcPkcs7Encrypt/CryCbcPkcs7EncryptConfig/*"!][!//
extern CONST(Cry_CbcPkcs7EncryptConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CBC_PKCS7_ENC_ENABLED == STD_ON) */

#endif /* #ifndef CRY_CBC_PKCS7_ENCCONFIG_H */
