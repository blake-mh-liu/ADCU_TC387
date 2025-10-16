/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_CVCPUBLICKEYEXTRACTCONFIG_H
#define CRY_CVCPUBLICKEYEXTRACTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

#if (defined CRY_CVCPUBLICKEYEXTRACT_ENABLED)
#error CRY_CVCPUBLICKEYEXTRACT_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
/** \brief Indicates whether a CVCPublicKeyExtract configuration exists.
 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*))"!][!//
#define CRY_CVCPUBLICKEYEXTRACT_ENABLED STD_ON

#if (defined CRY_CVCPUBLICKEYEXTRACT_INVALID_CFG)
#error CRY_CVCPUBLICKEYEXTRACT_INVALID_CFG is already defined
#endif
#define CRY_CVCPUBLICKEYEXTRACT_INVALID_CFG                 0xFFFFU

#if (defined CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI)
#error CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI is already defined
#endif
[!IF "as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*/CryCVCPublicKeyExtractEnableCertChain = 'true'"!][!//
#define CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI           STD_ON
[!ELSE!][!//
#define CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI           STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_CVCPUBLICKEYEXTRACT_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON)
[!//
[!VAR "maxSizeRootCert" = "0"!][!//
[!VAR "maxSizeSigCert" = "0"!][!//
[!LOOP "as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*"!][!//
  [!IF "(node:value(./CryCVCPublicKeyExtractEnableCertChain )) = 'true'"!][!//
   [!VAR "curSizeRootCert" = "num:i(./CryExtractCVCRootCertificateLength)"!][!//
     [!IF "$curSizeRootCert > $maxSizeRootCert"!][!//
     [!VAR "maxSizeRootCert" = "$curSizeRootCert"!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//
  [!VAR "curSizeSigCert" = "num:i(./CryExtractCVCSigCertificateLength)"!][!//
  [!IF "$curSizeSigCert > $maxSizeSigCert"!][!//
    [!VAR "maxSizeSigCert" = "$curSizeSigCert"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

#if (defined CRY_CVCPUBKEY_ROOTCERT_LEN_BYTES)
#error CRY_CVCPUBKEY_ROOTCERT_LEN_BYTES is already defined
#endif
#define CRY_CVCPUBKEY_ROOTCERT_LEN_BYTES   [!"num:i($maxSizeRootCert)"!]U

#if (defined CRY_CVCPUBKEY_SIGCERT_LEN_BYTES)
#error CRY_CVCPUBKEY_SIGCERT_LEN_BYTES is already defined
#endif
#define CRY_CVCPUBKEY_SIGCERT_LEN_BYTES    [!"num:i($maxSizeSigCert)"!]U

/*==================[type definitions]============================================================*/

/*---[struct]-------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CRY_0017,1 */
/** \brief  Configuration type for a configured CVC Public key extraction configuration.
 **/
typedef struct
{
  Csm_ConfigIdType VerifySignatureCfg;
  boolean          EnableCertChain;
}
Cry_CVCPublicKeyExtractConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*"!][!//

/** \brief A CVCPublicKeyExtract primitive configuration.
 */
extern CONST(Cry_CVCPublicKeyExtractConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON) */

#endif /* #ifndef CRY_CVCPUBLICKEYEXTRACTCONFIG_H */
