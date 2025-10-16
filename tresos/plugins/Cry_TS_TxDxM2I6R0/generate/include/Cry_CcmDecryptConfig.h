/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */
#ifndef CRY_CCMDECRYPTCONFIG_H
#define CRY_CCMDECRYPTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm.h>
#include <Cry_CCM_CommonConfig.h>

/*==================[macros]======================================================================*/

#if (defined CRY_CCM_DEC_ENABLED)
#error CRY_CCM_DEC_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCcmDecrypt/CryCcmDecryptConfig/*))"!][!//
#define CRY_CCM_DEC_ENABLED STD_ON

#if (defined CRY_MAX_PAYLOAD_SIZE)
#error CRY_MAX_PAYLOAD_SIZE is already defined
#endif
/** \brief Maximum size of the payload */
#define CRY_MAX_PAYLOAD_SIZE [!"num:i(num:max(as:modconf('Cry')/CryCcmDecrypt/CryCcmDecryptConfig/*/CryCCMMaxPayloadSize))"!]U

[!ELSE!][!//
#define CRY_CCM_DEC_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_CCM_DEC_ENABLED == STD_ON)

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryCcmDecrypt/CryCcmDecryptConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */
[!LOOP "as:modconf('Cry')/CryCcmDecrypt/CryCcmDecryptConfig/*"!][!//
extern CONST(Cry_CcmCryptConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CCM_DEC_ENABLED == STD_ON) */

#endif /* #ifndef CRY_CCMDECRYPTCONFIG_H */
