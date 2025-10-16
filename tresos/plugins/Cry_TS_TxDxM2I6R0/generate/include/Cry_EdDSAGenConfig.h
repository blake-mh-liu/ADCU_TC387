/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EDDSA_G_CGF_H
#define CRY_EDDSA_G_CGF_H

/*==[Includes]================================================================*/
#include <Std_Types.h>

#include <Csm.h>
#include <Csm_Hash.h>
#include <Csm_Types.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>

/*==[Macros]==================================================================*/

#if (defined CRY_EDDSA_GEN_ENABLED)
#error CRY_EDDSA_GEN_ENABLED is already defined
#endif
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryEdDSAGen/CryEdDSAGenConfig/*))"!][!//
#define CRY_EDDSA_GEN_ENABLED STD_ON
[!ELSE!][!//
#define CRY_EDDSA_GEN_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_EDDSA_GEN_ENABLED == STD_ON)

#if (defined CRY_EDDSAGEN_IMMEDIATE_RESTART_ENABLED)
#error CRY_EDDSAGEN_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmSignatureGenerate/CsmSignatureGenerateImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CryEdDSAGen/CryEdDSAGenImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_EDDSAGEN_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_EDDSAGEN_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_EDDSAGEN_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==[Types]===================================================================*/
/**
 * \struct Cry_EdDSAGenConfigType
 * \brief The configuration of the Ed25519ph signature generation.
 *//**
 * \var Cry_EdDSAGenConfigType::HashCfg
 * \brief The configuration of the underlying hash algorithm.
 *//**
 * \var Cry_EdDSAGenConfigType::SupportRestart
 * \brief Indicates whether restarting of the signature generation feature is
 *        enabled or not.
 *//**
 * \var Cry_EdDSAGenConfigType::NumberOfTimeSlices
 * \brief The configured number of time slices for long number or point operations
 *        during one main function call.
 */
typedef struct
{
  Csm_ConfigIdType   HashCfg;
  boolean            SupportRestart;
  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlices,1 */
  uint16             NumberOfTimeSlices;
}
Cry_EdDSAGenConfigType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryEdDSAGen/CryEdDSAGenConfig/*"!][!//
/** \brief EdDSA generation configuration
 *
 * One of the configurations of the EdDSA generation.
 *
 */
extern CONST(Cry_EdDSAGenConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*================================================================================*/

#endif /* (CRY_EDDSA_GEN_ENABLED == STD_ON) */

#endif /* CRY_EDDSA_G_CGF_H */
