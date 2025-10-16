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

#ifndef CAL_DECOMPRESS_H
#define CAL_DECOMPRESS_H

/*================================================================================================*/

/* !LINKSTO EB_CAL_0801_005, 1
 */

/*==================[includes]====================================================================*/

#include <Cal_Types.h>
#include <Cal_Decompress_Cfg.h>

#if (CAL_DECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief  Context buffer for the decompression service.
 **/
typedef Cal_AlignType Cal_DecompressCtxBufType[CAL_DECOMPRESS_CTX_BUF_SIZE];

/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 ** \struct  Cal_DecompressConfigType
 ** \brief   Structure representing the configuration of the decompression algorithm.
 **//**
 ** \var    Cal_DecompressConfigType::ConfigId
 ** \brief  Identifier for the current configuration.
 **//**
 ** \var    Cal_DecompressConfigType::PrimitiveStartFct
 ** \brief  Pointer to the start function of the underlying Cpl primitive.
 **//**
 ** \var    Cal_DecompressConfigType::PrimitiveUpdateFct
 ** \brief  Pointer to the update function of the underlying Cpl primitive.
 **//**
 ** \var    Cal_DecompressConfigType::PrimitiveFinishFct
 ** \brief  Pointer to the finish function of the underlying Cpl primitive.
 **//**
 ** \var    Cal_DecompressConfigType::PrimitiveConfigPtr
 ** \brief  Pointer to a Cpl configuration.
 **/
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void,                     AUTOMATIC, CAL_APPL_DATA) cfgId,
        VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void,                     AUTOMATIC, CAL_APPL_DATA) cfgId,
        VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2CONST(uint8,                    AUTOMATIC, CAL_APPL_DATA) iputBuf,
      P2VAR(uint32,                   AUTOMATIC, CAL_APPL_DATA) iputBufLen,
      P2VAR(uint8,                    AUTOMATIC, CAL_APPL_DATA) oputBuf,
      P2VAR(uint32,                   AUTOMATIC, CAL_APPL_DATA) oputBufLen
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void,                     AUTOMATIC, CAL_APPL_DATA) cfgId,
        VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
      P2VAR(uint8,                    AUTOMATIC, CAL_APPL_DATA) oputBuf,
      P2VAR(uint32,                   AUTOMATIC, CAL_APPL_DATA) oputBufLen
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_DecompressConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CAL_0804_015, 1
 */
/** \brief  Start decompression computation.
 **
 ** This function requests the start of the decompression for
 ** the given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]   cfgId          An identification of the configuration for which the start
 **                             of the decompression computation should be requested.
 ** \param[out]  contextBuffer  Holds the pointer to the buffer in which the context of this
 **                             service is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_DecompressStart
(
  VAR(Cal_ConfigIdType,         AUTOMATIC) cfgId,
  VAR(Cal_DecompressCtxBufType, AUTOMATIC) contextBuffer
);

/* !LINKSTO EB_CAL_0804_020, 1
 */
/** \brief  Update decompression computation.
 **
 ** This function requests the update of the decompression
 ** computation for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId               An identification of the configuration for which
 **                                     the update of the decompression computation should
 **                                     be requested.
 ** \param[in,out]  contextBuffer       Holds the pointer to the buffer in which the context of this
 **                                     service is stored.
 ** \param[in]      iputBuf             Holds a pointer to the data that shall be decompressed.
 ** \param[in/out]  iputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by iputBuf.
 **                                     On returning from this function the length of data from
 **                                     buffer iputBuf that was already processed/decompressed
 **                                     shall be stored.
 ** \param[out]     oputBuf             A pointer to the start of an array where the decompressed data
 **                                     shall be stored.
 ** \param[in,out]  oputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by oputBuf.
 **                                     On returning from this function the size of decompressed data
 **                                     (the result) which was written to the buffer oputBuf shall
 **                                     be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK            If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK        If no decompression computation has been started via
 **                               Cal_DecompressStart(), yet.
 ** \retval   CAL_E_SMALL_BUFFER  The provided buffer oputBuf is too small to store the full result.
 **                               So not the full buffer iputBuf wasn't decompressed, but only the
 **                               first iputBufLen bytes (on returning).
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_DecompressUpdate
(
      VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                    AUTOMATIC, CAL_APPL_DATA) iputBuf,
    P2VAR(uint32,                   AUTOMATIC, CAL_APPL_DATA) iputBufLen,
    P2VAR(uint8,                    AUTOMATIC, CAL_APPL_DATA) oputBuf,
    P2VAR(uint32,                   AUTOMATIC, CAL_APPL_DATA) oputBufLen
);

/* !LINKSTO EB_CAL_0804_025, 1
 */
/** \brief  Finish decompression computation.
 **
 ** This function requests the finishing of the decompression computation.
 ** The finish function of the configured primitive is called and its return
 ** value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the start
 **                                of the decompression computation should be requested.
 ** \param[out]     contextBuffer  Holds the pointer to the buffer in which the context of this
 **                                service is stored.
 ** \param[out]     oputBuf        A pointer to the start of an array where the decompressed data
 **                                shall be stored.
 ** \param[in,out]  oputBufLen     Holds a pointer to a memory location in which the length
 **                                information is stored.
 **                                On calling this function this parameter shall contain the
 **                                size of the buffer provided by oputBuf.
 **                                On returning from this function the size of decompressed data
 **                                (the result) which was written to the buffer oputBuf shall
 **                                be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK            If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK        If no decompression computation has been started via
 **                               Cal_DecompressStart(), yet.
 ** \retval   CAL_E_SMALL_BUFFER  The provided buffer oputBuf is too small to store the full result.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_DecompressFinish
(
    VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
    VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2VAR(uint8,                    AUTOMATIC, CAL_APPL_DATA) oputBuf,
  P2VAR(uint32,                   AUTOMATIC, CAL_APPL_DATA) oputBufLen
);

#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CAL_0806_505, 1
 */
/** \brief  Array containing all existing decompression service configurations
 **/
extern CONST(Cal_DecompressConfigType, CAL_CONST)
  Cal_DecompressConfigurations[CAL_DECOMPRESS_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_DECOMPRESS_ENABLED == STD_ON) */

#endif /* #ifndef CAL_DECOMPRESS_H */

/*==================[end of file]=================================================================*/

