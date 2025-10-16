/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*================================================================================================*/

/* !LINKSTO CSM0004, 1
 */

#ifndef CSM_TYPES_H
#define CSM_TYPES_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Cfg.h>
#include <Csm_Version.h>

/* !LINKSTO EB_CSM0677_01, 1
 */
#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm_Type.h>
#endif

/*==================[macros]======================================================================*/

#if !(defined CSM_E_OK)
/** \brief  Operation successful. */
#define CSM_E_OK                     0U
#endif

#if !(defined CSM_E_NOT_OK)
/** \brief  Operation failed. */
#define CSM_E_NOT_OK                 1U
#endif

#if !(defined CSM_E_BUSY)
/** \brief  Service is busy at the moment. */
#define CSM_E_BUSY                   2U
#endif

#if !(defined CSM_E_SMALL_BUFFER)
/** \brief  Result buffer is too small to hold the complete result. */
#define CSM_E_SMALL_BUFFER           3U
#endif

#if !(defined CSM_E_ENTROPY_EXHAUSTION)
/** \brief  Random number generator cannot generate bytes at the moment. */
#define CSM_E_ENTROPY_EXHAUSTION     4U
#endif

#if !(defined CSM_E_VER_OK)
/** \brief  Signature fits the given data. */
#define CSM_E_VER_OK                 0U
#endif

#if !(defined CSM_E_VER_NOT_OK)
/** \brief  Signature does not fit the given data. */
#define CSM_E_VER_NOT_OK             1U
#endif

/*==================[type definitions]============================================================*/

/* !LINKSTO CSM0728, 1
 */
/** \brief  An integer type with maximal alignment restrictions.
 **
 ** This is an integer type which has the maximal alignment restrictions. That means that a pointer
 ** to a variable to this type can be cast to a pointer to any other integer type without risking
 ** alignment problems.
 **/
#ifndef RTE_TYPE_Csm_AlignType
#define RTE_TYPE_Csm_AlignType
typedef CSM_ALIGN_BASE_TYPE Csm_AlignType;
#endif /* #ifndef RTE_TYPE_Csm_AlignType */

/* !LINKSTO EB_CSM0079_01, 1
 */
/** \brief  The type of a public asymmetrical key.
 **
 ** This type is used for the public asymmetrical key of asymmetrical cryptographic schemes like
 ** signature verification or asymmetrical encryption.
 **/
#ifndef RTE_TYPE_Csm_AsymPublicKeyType
#define RTE_TYPE_Csm_AsymPublicKeyType
typedef struct
{
  uint32        length;
  Csm_AlignType data[CSM_ASYM_PUB_KEY_MAX_SIZE];
}
Csm_AsymPublicKeyType;
#endif /* #ifndef RTE_TYPE_Csm_AsymPublicKeyType */

/* !LINKSTO EB_CSM0080_01, 1
 */
/** \brief  The type of a private asymmetrical key.
 **
 ** This type is used for the private asymmetrical key of asymmetrical cryptographic schemes like
 ** signature generation or asymmetrical decryption.
 **/
#ifndef RTE_TYPE_Csm_AsymPrivateKeyType
#define RTE_TYPE_Csm_AsymPrivateKeyType
typedef struct
{
  uint32        length;
  Csm_AlignType data[CSM_ASYM_PRIV_KEY_MAX_SIZE];
}
Csm_AsymPrivateKeyType;
#endif /* #ifndef RTE_TYPE_Csm_AsymPrivateKeyType */

/* !LINKSTO EB_CSM0082_01, 1
 */
/** \brief  The type of a symmetrical key.
 **
 ** This type is used for the symmetrical key of symmetrical cryptographic schemes like HMAC
 ** generation.
 **/
#ifndef RTE_TYPE_Csm_SymKeyType
#define RTE_TYPE_Csm_SymKeyType
typedef struct
{
  uint32        length;
  Csm_AlignType data[CSM_SYM_KEY_MAX_SIZE];
}
Csm_SymKeyType;
#endif /* #ifndef RTE_TYPE_Csm_SymKeyType */

/* !LINKSTO EB_CSM0069_01, 1
 */
/** \brief  Type of the return values of the CSM.
 **/
#ifndef RTE_TYPE_Csm_ReturnType
#define RTE_TYPE_Csm_ReturnType
typedef uint8 Csm_ReturnType;
#endif /* #ifndef RTE_TYPE_Csm_ReturnType */

/* !LINKSTO EB_CSM0075_01, 1
 */
/** \brief  Type of the return values of a signature verification.
 **/
#ifndef RTE_TYPE_Csm_VerifyResultType
#define RTE_TYPE_Csm_VerifyResultType
typedef uint8 Csm_VerifyResultType;
#endif /* #ifndef RTE_TYPE_Csm_VerifyResultType */

/* !LINKSTO CSM0691, 1
 */
/** \brief  The type of configuration IDs
 **
 ** Every configuration of a CSM service has a number which uniquely identifies it among that
 ** service's configurations. The identifier is of this type.
 **/
#ifndef RTE_TYPE_Csm_ConfigIdType
#define RTE_TYPE_Csm_ConfigIdType
typedef uint16 Csm_ConfigIdType;
#endif /* #ifndef RTE_TYPE_Csm_ConfigIdType */

/* !LINKSTO CSM0073, 1
 */
/** \brief  Callback functions
 **
 ** For each configured service, the user has to provide a callback function which will be called
 ** by the service when it has finished. All callback function have to be of this type.
 **/
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, Csm_CallbackType)(Csm_ReturnType Result);

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_TYPES_H */

/*==================[end of file]=================================================================*/

