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

#ifndef CAL_HASH_H
#define CAL_HASH_H

/*==[Includes]================================================================*/

#include <Cal_Types.h>
#include <Cal_Hash_Cfg.h>


#if (CAL_HASH_ENABLED == TRUE)
/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief Defines the context buffer for the hash services
 */
typedef Cal_AlignType Cal_HashCtxBufType[CAL_HASH_CONTEXT_BUFFER_SIZE];


/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_HashConfigType
 * \brief Structure which contains the configuration for a hash service.
 *//**
 * \var Cal_HashConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_HashConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_HashConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_HashConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_HashConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
   Cal_ConfigIdType ConfigId;

   P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
   (
      P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
      Cal_HashCtxBufType                      contextBuffer
   );

   P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
   (
      P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
      Cal_HashCtxBufType                       contextBuffer,
      P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
      uint32                                   dataLength
   );

   P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
   (
      P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
      Cal_HashCtxBufType                      contextBuffer,
      P2VAR(uint8, AUTOMATIC, CAL_APPL_DATA)  resultPtr,
      P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) resultLengthPtr,
      boolean                                 truncationAllowed
   );

   P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_HashConfigType;


/*==[Constants with external linkage]=========================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containg all Hash service configurations.
 */
extern CONST(Cal_HashConfigType, CAL_CONST) Cal_HashConfigurations[CAL_HASH_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/


#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0089, 1
 */
/**
 *
 * \brief Start hash computation.
 *
 * This function requests the start of the hash computation for the
 * given configuration. The start function of the configured primitive is
 * called and its return value is returned.
 *
 * \param[in]  cfgId         An identification of the configuration for which the
 *                           start of the hash
 *                           computation should be requested.
 * \param[out] contextBuffer A Pointer to a buffer where the contect of the current configuration
 *                           will be stored.
 *
 * \returns error value
 *
 * \retval CAL_E_OK If the start was successfully requested.
 *
 * \retval CAL_E_NOT_OK If the service request failed.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_HashStart
(
  Cal_ConfigIdType   cfgId,
  Cal_HashCtxBufType contextBuffer
);

/* !LINKSTO CAL0094, 1
 */
/**
 *
 * \brief Update hash computation.
 *
 * This function requests the update of the hash computation for the
 * given data. The update function of the configured primitive is
 * called and its return value is returned.
 *
 * \param[in]      cfgId         an identification of the configuration for which the
 *                               hash computation should be requested.
 * \param[in,out]  contextBuffer A Pointer to a buffer which holds the context of the current hash
 *                               computation.
 * \param[in]      dataPtr       a pointer to the start of an array which contains a
 *                               part of the data for which the hash digest should be
 *                               created.
 * \param[in]      dataLength    the amount of bytes of data.
 *
 * \returns error value
 *
 * \retval CAL_E_OK If the update was successfully requested.
 *
 * \retval CAL_E_NOT_OK If no hash computation has been started via Cal_HashStart(),
 *         yet.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_HashUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_HashCtxBufType                       contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
);


/* !LINKSTO CAL0101, 1
 */
/**
 *
 * \brief Finish hash computation.
 *
 * This function requests the finishing of the hash computation and
 * the storing of the hash digest in the given result buffer. The finish
 * function of the configured primitive is called and its return value is
 * returned.
 *
 * \param[in]      cfgId             an identification of the configuration for which the
 *                                   hash computation should be requested.
 * \param[in,out]  contextBuffer     A Pointer to a buffer which holds the context of the current
 *                                   hash computation.
 * \param[out]     resultPtr         a pointer to the start of a buffer where the hash digest
 *                                   should be stored.
 * \param[in,out]  resultLengthPtr   a pointer to a variable which contains the maximal allowed
 *                                   length for the hash and where the actual length of the hash
 *                                   should be stored.
 * \param[in]      truncationAllowed If this flag is ::TRUE and the hash digest is longer than
 *                                   the given result buffer, the hash is truncated to the buffer
 *                                   length. If
 *                                   this flag is ::FALSE and the hash digest is longer than the
 *                                   given result
 *                                   buffer, an error code of CAL_E_SMALL_BUFFER is returned.
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the finish was successfully requested.
 *
 * \retval CAL_E_NOT_OK If no hash computation has been started via Cal_HashStart(),
 *                      yet.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_HashFinish
(
  Cal_ConfigIdType                         cfgId,
  Cal_HashCtxBufType                       contextBuffer,
  P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA)  resultLengthPtr,
  boolean                                  truncationAllowed
);


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CAL_HASH_ENABLED == TRUE) */

#endif /* #ifndef CAL_HASH_H */

