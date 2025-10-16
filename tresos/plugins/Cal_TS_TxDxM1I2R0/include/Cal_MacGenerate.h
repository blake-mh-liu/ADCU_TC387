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

#ifndef CAL_MACGENERATE_H
#define CAL_MACGENERATE_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_MacGenerate_Cfg.h>

#if (CAL_MAC_GENERATE_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type which specifies the array size of the context buffer required for the Mac generation.
 */
typedef Cal_AlignType Cal_MacGenerateCtxBufType[CAL_MACGENERATE_CTX_BUF_SIZE];


/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_MacGenerateConfigType
 * \brief Structure representing the configuration of the Mac generation
 *         algorithm.
 *//**
 * \var Cal_MacGenerateConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_MacGenerateConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_MacGenerateConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_MacGenerateConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_MacGenerateConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void,           AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_MacGenerateCtxBufType                         contextBuffer,
    P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void,  AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_MacGenerateCtxBufType                contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
    uint32                                   dataLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void,  AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_MacGenerateCtxBufType                contextBuffer,
    P2VAR(uint8,   AUTOMATIC, CAL_APPL_DATA) resultPtr,
    P2VAR(uint32,  AUTOMATIC, CAL_APPL_DATA) resultLengthPtr,
    boolean                                  truncationIsAllowed
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_MacGenerateConfigType;


/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0108, 1
 */
/** \brief  Start MAC generate computation.
 **
 ** This function performs the start of the MAC generate for the given
 ** configuration.
 **
 ** \param[in]      cfgId          An identification of the configuration for which
 **                                the start of the MAC generate computation should be
 **                                requested.
 ** \param[out]     contextBuffer  Holds the pointer to the buffer in which the context of this
 **                                service can be stored.
 ** \param[in]      keyPtr         A pointer to the key which should be used in the
 **                                MAC generate computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  If the request failed.

 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_MacGenerateStart
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacGenerateCtxBufType                         contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);

/* !LINKSTO CAL0114, 1
 */
/** \brief  Update MAC generate computation.
 **
 ** This function performs the update of the MAC generate computation
 ** for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which
 **                                the update of the MAC generate computation should be
 **                                requested.
 ** \param[in,out]  contextBuffer  Holds the pointer to the buffer in which the context of this
 **                                service is stored.
 ** \param[in]      dataPtr        A pointer to the start of an array
 **                                which contains the constant data
 **                                for which a MAC shall be generated.
 ** \param[in]      dataLength     Length of the constant data in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no MAC generate computation has been started
 **                         via Cal_MacGenerateStart(), yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_MacGenerateUpdate
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacGenerateCtxBufType                         contextBuffer,
  P2CONST(uint8,  AUTOMATIC, CAL_APPL_DATA)         dataPtr,
  uint32                                            dataLength
);

/* !LINKSTO CAL0121, 1
 */
/** \brief  Finish MAC generate computation.
 **
 ** This function performs the finishing of the MAC generate computation.
 ** The finish function of the configured primitive is called and its
 ** return value is returned.
 **
 ** \param[in]      cfgId                An identification of the configuration for which
 **                                      the finish of the MAC generate computation should be
 **                                      requested.
 ** \param[in,out]  contextBuffer        Holds the pointer to the buffer in which the context of
 **                                      this service is stored.
 ** \param[out]     resultPtr            A pointer to the start of an array
 **                                      which will hold the generated MAC.
 **                                      If the result does not fit into the given
 **                                      buffer, and truncation is allowed, the result
 **                                      shall be truncated.
 ** \param[in,out]  resultLengthPtr      Holds a pointer to a memory location
 **                                      in which the length information is stored.
 **                                      On calling this function this parameter
 **                                      shall contain the size of the buffer
 **                                      provided by resultPtr. When the
 **                                      request has finished, the actual length of
 **                                      the returned MAC shall be stored.
 ** \param[out]     truncationIsAllowed  A flag that states whether a truncation of
 **                                      the calculated Mac is allowed.
 **                                      TRUE  = truncation is allowed.
 **                                      FALSE = truncation is not allowed.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK              If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK          If no MAC generate computation has been started
 **                                 via Cal_MacGenerateStart(), yet.
 ** \retval   CAL_E_SMALL_BUFFER    If the provided buffer is too small to store the result and
 **                                 truncation was not allowed.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_MacGenerateFinish
(
  Cal_ConfigIdType                        cfgId,
  Cal_MacGenerateCtxBufType               contextBuffer,
  P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) resultLengthPtr,
  boolean                                 truncationIsAllowed
);

#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containg all configurations for the MacGenerate service.
 */
extern CONST(Cal_MacGenerateConfigType, CAL_CONST)
  Cal_MacGenerateConfigurations[CAL_MACGEN_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_MAC_GENERATE_ENABLED == TRUE) */

#endif /* #ifndef CAL_MACGENERATE_H */

