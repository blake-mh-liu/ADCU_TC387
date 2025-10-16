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

#ifndef CAL_SYMKEYEXTRACT_H
#define CAL_SYMKEYEXTRACT_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_SymKeyExtract_Cfg.h>

#if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE)


/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** type representing the required context buffer for symmetrical key extraction.
 */
typedef Cal_AlignType Cal_SymKeyExtractCtxBufType[CAL_SYMKEYEXTRACT_CONTEXT_BUFFER_SIZE];



/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/** \brief structure representing the configuration of the symmetrical key extraction algorithm.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_SymKeyExtractCtxBufType             contextBuffer
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_SymKeyExtractCtxBufType              contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
    uint32                                   dataLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)         cfgPtr,
    Cal_SymKeyExtractCtxBufType                     contextBuffer,
    P2VAR(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_SymKeyExtractConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0418, 1
 */
/** \brief  Start symmetric key extraction.
 **
 ** This function performs the start of the symmetric key extraction for the
 ** given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the start of the symmetric key extraction shall be
 **                                requested.
 ** \param[out]     contextBuffer  A Pointer to a buffer where the context of the current
 **                                configuration of the SymKeyExtract service will be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_SymKeyExtractStart
(
  Cal_ConfigIdType            cfgId,
  Cal_SymKeyExtractCtxBufType contextBuffer
);

/* !LINKSTO CAL0425, 1
 */
/** \brief  Update symmetric key extraction.
 **
 ** This function performs the update of the symmetric key extraction for the
 ** given data. The update function of the configured primitive is called and
 ** its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the update of the symmetric key extraction shall be
 **                                requested.
 ** \param[in,out]  contextBuffer  A Pointer to a buffer which holds the context of the current
 **                                configuration of the SymKeyExtract service.
 ** \param[in]      dataPtr        A pointer to the start of an array which contains
 **                                a part of the key which should be extracted.
 ** \param[in]      dataLength     The amount of bytes of data.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK     If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK If no symmetric key extraction has been started
 **                        via Cal_SymKeyExtractStart() yet.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_SymKeyExtractUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_SymKeyExtractCtxBufType              contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
);

/* !LINKSTO CAL0432, 1
 */
/** \brief  Finish symmetric key extraction.
 **
 ** This function performs the finishing of the symmetric key extraction and
 ** the storing of the key in the given buffer. The finish function of the
 ** configured primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the finishing of the symmetric key extraction shall be
 **                                requested.
 ** \param[in,out]  contextBuffer  A Pointer to a buffer which holds the context of the current
 **                                configuration of the SymKeyExtract service.
 ** \param[out]     keyPtr         A pointer to the buffer where the extracted key
 **                                should be stored
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no symmetric key extraction has been started
 **                         via Cal_SymKeyExtractStart() yet.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_SymKeyExtractFinish
(
  Cal_ConfigIdType                                cfgId,
  Cal_SymKeyExtractCtxBufType                     contextBuffer,
  P2VAR(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containing all SymKeyExtract service configurations.
 */
extern CONST(Cal_SymKeyExtractConfigType, CAL_CONST)
  Cal_SymKeyExtractConfigurations[CAL_SYMKEYEX_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE) */

#endif /* #ifndef CAL_SYMKEYEXTRACT_H */

