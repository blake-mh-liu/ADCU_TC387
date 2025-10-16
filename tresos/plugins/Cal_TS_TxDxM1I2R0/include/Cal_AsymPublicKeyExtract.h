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

#ifndef CAL_ASYMPUBLICKEYEXTRACT_H
#define CAL_ASYMPUBLICKEYEXTRACT_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_AsymPublicKeyExtract_Cfg.h>

#if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE)


/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type representing the required context buffer for asymmetrical public key extraction.
 */
typedef Cal_AlignType Cal_AsymPublicKeyExtractCtxBufType[CAL_ASYMPUBKEYEXTRACT_CTX_BUF_SIZE];

/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_AsymPublicKeyExtractConfigType
 * \brief Structure representing the configuration of the asymmetrical public key extraction
 *         algorithm.
 *//**
 * \var Cal_AsymPublicKeyExtractConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_AsymPublicKeyExtractConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_AsymPublicKeyExtractConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_AsymPublicKeyExtractConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_AsymPublicKeyExtractConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_AsymPublicKeyExtractCtxBufType      contextBuffer
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_AsymPublicKeyExtractCtxBufType       contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
    uint32                                   dataLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)                cfgPtr,
    Cal_AsymPublicKeyExtractCtxBufType                     contextBuffer,
    P2VAR(Cal_AsymPublicKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_AsymPublicKeyExtractConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0436, 1
 */
/** \brief  Start asymmetrical public key extraction.
 **
 ** This function performs the start of the extraction of an asymmetrical public key for the
 ** given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the start of the asymmetric public key extraction shall be
 **                                requested.
 ** \param[out]     contextBuffer  A Pointer to a buffer where the context of the current
 **                                configuration of the AsymPublicKeyExtract service will be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_AsymPublicKeyExtractStart
(
  Cal_ConfigIdType                   cfgId,
  Cal_AsymPublicKeyExtractCtxBufType contextBuffer
);

/* !LINKSTO CAL0443, 1
 */
/** \brief  Update asymmetric public key extraction.
 **
 ** This function performs the update of the extraction of an asymmetrical public key for the
 ** given data. The update function of the configured primitive is called and
 ** its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the update of the asymmetric public key extraction shall be
 **                                requested.
 ** \param[in,out]  contextBuffer  A Pointer to a buffer which holds the context of the current
 **                                configuration of the AsymPublicKeyExtract service.
 ** \param[in]      dataPtr        A pointer to the start of an array which contains
 **                                a part of the key which should be extracted.
 ** \param[in]      dataLength     The amount of bytes of data.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK     If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK Otherwise.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_AsymPublicKeyExtractUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_AsymPublicKeyExtractCtxBufType       contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
);

/* !LINKSTO CAL0450, 1
 */
/** \brief  Finish asymmetric public key extraction.
 **
 ** This function performs the finishing of the extraction of an asymmetrical public key and
 ** the storing of the key in the given buffer. The finish function of the
 ** configured primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the finishing of the asymmetric public key extraction shall be
 **                                requested.
 ** \param[in,out]  contextBuffer  A Pointer to a buffer which holds the context of the current
 **                                configuration of the AsymPublicKeyExtract service.
 ** \param[out]     keyPtr         A pointer to the buffer where the extracted key
 **                                should be stored
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_AsymPublicKeyExtractFinish
(
  Cal_ConfigIdType                                       cfgId,
  Cal_AsymPublicKeyExtractCtxBufType                     contextBuffer,
  P2VAR(Cal_AsymPublicKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containing all AsymPublicKeyExtract service configurations.
 */
extern CONST(Cal_AsymPublicKeyExtractConfigType, CAL_CONST)
  Cal_AsymPublicKeyExtractConfigs[CAL_ASYMPUBKEYEXTRACT_CFG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE) #else */

#endif /* #ifndef CAL_ASYMPUBLICKEYEXTRACT_H */

