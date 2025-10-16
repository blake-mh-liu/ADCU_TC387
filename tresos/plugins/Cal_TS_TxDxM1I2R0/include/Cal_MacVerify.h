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

#ifndef CAL_MACVERIFY_H
#define CAL_MACVERIFY_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_MacVerify_Cfg.h>

#if (CAL_MAC_VERIFY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0742, 1
 */
/* !LINKSTO CAL0730, 1
 */
/** \brief type which specifies the array size of the context buffer required for the Mac
 *         verification.
 */
typedef Cal_AlignType Cal_MacVerifyCtxBufType[CAL_MACVERIFY_CONTEXT_BUFFER_SIZE];



/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_MacVerifyConfigType
 * \brief Structure representing the configuration of the Mac verification
 *         algorithm.
 *//**
 * \var Cal_MacVerifyConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_MacVerifyConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_MacVerifyConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_MacVerifyConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_MacVerifyConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void,           AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_MacVerifyCtxBufType                           contextBuffer,
    P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void,  AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_MacVerifyCtxBufType                  contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
    uint32                                   dataLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void,               AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_MacVerifyCtxBufType                               contextBuffer,
    P2CONST(uint8,              AUTOMATIC, CAL_APPL_DATA) MacPtr,
    uint32                                                MacLength,
    P2VAR(Cal_VerifyResultType, AUTOMATIC, CAL_APPL_DATA) resultPtr
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_MacVerifyConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0128, 1
 */
/** \brief  Start MAC verify computation.
 **
 ** This function performs the start of the MAC verification for the given
 ** configuration.
 **
 ** \param[in]      cfgId          An identification of the configuration for which
 **                                the start of the MAC verify computation should be
 **                                requested.
 ** \param[out]     contextBuffer  Holds the pointer to the buffer in which the context of this
 **                                service can be stored.
 ** \param[in]      keyPtr         A pointer to the key which should be used in the
 **                                MAC verify computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  If the request failed.

 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_MacVerifyStart
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacVerifyCtxBufType                           contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);

/* !LINKSTO CAL0134, 1
 */
/** \brief  Update MAC verify computation.
 **
 ** This function performs the update of the MAC verify computation
 ** for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which
 **                                the update of the MAC verify computation should be
 **                                requested.
 ** \param[in,out]  contextBuffer  Holds the pointer to the buffer in which the context of this
 **                                service is stored.
 ** \param[in]      dataPtr        A pointer to the start of an array
 **                                which contains the constant data
 **                                for which a MAC shall be verified.
 ** \param[in]      dataLength     Length of the constant data in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no MAC verify computation has been started
 **                         via Cal_MacVerifyStart(), yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_MacVerifyUpdate
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacVerifyCtxBufType                           contextBuffer,
  P2CONST(uint8,  AUTOMATIC, CAL_APPL_DATA)         dataPtr,
  uint32                                            dataLength
);

/* !LINKSTO CAL0141, 1
 */
/** \brief  Finish MAC verify computation.
 **
 ** This function performs the finishing of the MAC verify computation.
 ** The finish function of the configured primitive is called and its
 ** return value is returned.
 **
 ** \param[in]      cfgId                An identification of the configuration for which
 **                                      the finish of the MAC verify computation should be
 **                                      requested.
 ** \param[in,out]  contextBuffer        Holds the pointer to the buffer in which the context of
 **                                      this service is stored.
 ** \param[in]      MacPtr               A pointer to the start of an array
 **                                      which holds the MAC which shall be verified.
 ** \param[in]      MacLength            The length information of the Mac which shall be verified.
 ** \param[out]     resultPtr            A Pointer to the cerification result.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK              If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK          If no MAC verify computation has been started
 **                                 via Cal_MacVerifyStart(), yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_MacVerifyFinish
(
  Cal_ConfigIdType                                      cfgId,
  Cal_MacVerifyCtxBufType                               contextBuffer,
  P2CONST(uint8,              AUTOMATIC, CAL_APPL_DATA) MacPtr,
  uint32                                                MacLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, CAL_APPL_DATA) resultPtr
);

#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containing all configurations of the MacVerify service.
 */
extern CONST(Cal_MacVerifyConfigType, CAL_CONST)
  Cal_MacVerifyConfigurations[CAL_MACVRFY_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_MAC_VERIFY_ENABLED == TRUE) */

#endif /* #ifndef CAL_MACVERIFY_H */

