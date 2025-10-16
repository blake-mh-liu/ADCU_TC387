/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO CAL0004, 1
 */
#ifndef CAL_TYPES_H
#define CAL_TYPES_H


/*==[Includes]================================================================*/

/* !LINKSTO CAL0008, 1
 */
/* !LINKSTO CAL0739, 1
 */
#include <Std_Types.h>

#include <Cal_Types_Cfg.h>


/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/




/* !LINKSTO CAL0069, 1
 */
/**
 *
 * \enum Cal_ReturnType
 * \brief Enumeration of the return values of the CAL.
 *
 *//**
 * \var Cal_ReturnType::CAL_E_OK
 * \brief Operation successful.
 *//**
 * \var Cal_ReturnType::CAL_E_NOT_OK
 * \brief Operation failed.
 *//**
 * \var Cal_ReturnType::CAL_E_SMALL_BUFFER
 * \brief Result buffer is too small to hold the complete result.
 *//**
 * \var Cal_ReturnType::CAL_E_ENTROPY_EXHAUSTION
 * \brief The pseudo random number generator cannot generate
 *        bytes at the moment.
 *//**
 * \var Cal_ReturnType::CAL_E_BUSY
 * \brief API function isn't finished but yields execution focus.
 */
typedef enum
{
  CAL_E_OK,
  CAL_E_NOT_OK,
  CAL_E_SMALL_BUFFER,
  CAL_E_ENTROPY_EXHAUSTION,
  CAL_E_BUSY
}
Cal_ReturnType;

/* !LINKSTO CAL0075, 1
 */
/**
 *
 * \enum Cal_VerifyResultType
 * \brief Enumeration of the return values a signature verification.
 *
 *//**
 * \var Cal_VerifyResultType::CAL_E_VER_OK
 * \brief Signature fits the given data.
 *//**
 * \var Cal_VerifyResultType::CAL_E_VER_NOT_OK
 * \brief Signature does not fit the given data.
 */
typedef enum
{
  CAL_E_VER_OK,
  CAL_E_VER_NOT_OK
}
Cal_VerifyResultType;


/* !LINKSTO CAL0073, 1
 */
/**
 *
 * \brief The type of configuration IDs
 *
 * Every configuration of a CAL service has a number which uniquely identifies
 * it among that service's configurations. The identifier is of this type.
 *
 */
typedef uint16 Cal_ConfigIdType;

/* !LINKSTO CAL0082, 1
 */
/**
 * \struct Cal_SymKeyType
 * \brief Type of symmetrical keys
 *//**
 * \var Cal_SymKeyType::length
 * \brief Length information of the key data.
 *//**
 * \var Cal_SymKeyType::data
 * \brief key data.
 */
typedef struct
{
  uint32 length;
  Cal_AlignType data[CAL_SYM_KEY_MAX_SIZE];
} Cal_SymKeyType;

/* !LINKSTO CAL0079, 1
 */
/**
 * \struct Cal_AsymPublicKeyType
 * \brief Type of asymmetrical public keys
 *//**
 * \var Cal_AsymPublicKeyType::length
 * \brief Length information of the key data.
 *//**
 * \var Cal_AsymPublicKeyType::data
 * \brief key data.
 */
typedef struct
{
  uint32 length;
  Cal_AlignType data[CAL_ASYM_PUB_KEY_MAX_SIZE];
} Cal_AsymPublicKeyType;


/* !LINKSTO CAL0086, 1
 */
/**
 * \struct Cal_KeyExchangeBaseType
 * \brief Structure with base type information of the key exchange protocol.
 *//**
 * \var Cal_KeyExchangeBaseType::length
 * \brief Length information of key exchange base.
 *//**
 * \var Cal_KeyExchangeBaseType::data
 * \brief key exchange base data.
 */
typedef struct
{
  uint32 length;
  Cal_AlignType data[CAL_KEY_EX_BASE_MAX_SIZE];
} Cal_KeyExchangeBaseType;

/* !LINKSTO CAL0087, 1
 */
/**
 * \struct Cal_KeyExchangePrivateType
 * \brief Structure with private type information of the key exchange protocol.
 *//**
 * \var Cal_KeyExchangePrivateType::length
 * \brief Length information of key exchange private value.
 *//**
 * \var Cal_KeyExchangePrivateType::data
 * \brief key exchange private value data.
 */
typedef struct
{
  uint32 length;
  Cal_AlignType data[CAL_KEY_EX_PRIV_MAX_SIZE];
} Cal_KeyExchangePrivateType;

/*==[Constants with external linkage]=========================================*/



/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/

#endif /* #ifndef CAL_TYPES_H */

