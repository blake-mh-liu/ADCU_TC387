/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_CRC_H
#define CRY_CRC_H

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_Cry_CRC,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_CRC_Config.h>

#if (CRY_CRC_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Start CRC calculation.
 **
 ** This function requests the start of the CRC calculation
 ** for the given configuration.
 ** The start is performed in Cry_CRCMainFunction().
 **
 ** \param[in]      cfgId   An identification of the configuration for
 **                         which the start of the CRC calculation should
 **                         be requested.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_NOT_OK  ---
 ** \retval   CSM_E_BUSY    If a service of the CRC calculation is
 **                         already running.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_CRCStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/** \brief  Update of CRC calculation.
 **
 ** This function requests the update of the CRC calculation for the
 ** given data.
 ** The update is performed in Cry_CRCMainFunction().
 **
 ** \param[in]      dataPtr     A pointer to the start of an array which
 **                             contains the data for which the CRC
 **                             shall be calculated.
 ** \param[in]      dataLength  The amount of bytes of data.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no CRC calculation has been started
 **                         via Csm_SymKeyExtractStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_CRCUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
      VAR(uint32, AUTOMATIC               ) dataLength
);

/** \brief  Finish CRC calculation.
 **
 ** This function requests the finishing of the CRC calculation
 ** and the storing of the calculated CRC result in the given buffer.
 ** The finish is performed in Cry_CRCMainFunction().
 **
 ** \param[out]     resultPtr            A pointer to the buffer where the
 **                                      calculated CRC result should be stored.
 **                                      If the result does not fit into the
 **                                      given buffer, and truncation is allowed,
 **                                      the result will be truncated.
 ** \param[out]     resultLengthPtr      On calling the function it is the amount
 **                                      of bytes of resultPtr. After finishing of
 **                                      function call it is the actual length of
 **                                      the calculated CRC result.
 ** \param[in]      truncationIsAllowed  A flag that states wheter a truncation of
 **                                      the calculated CRC result is allowed.
 **                                      TRUE  = truncation is allowed.
 **                                      FALSE = truncation is not allowed.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no CRC calculation has been started
 **                         via Csm_SymKeyExtractStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_CRCFinish
(
  P2VAR(uint8,   AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
    VAR(boolean, AUTOMATIC               ) truncationIsAllowed
);

/** \brief  Perform the CRC calculation tasks.
 **
 ** This function performs the actual CRC calculation tasks which have
 ** been requested by the service functions. The function calls the
 ** main function of the configured primitive to perform the tasks.
 **/
FUNC(void, CRY_CODE) Cry_CRCMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CRC_ENABLED == TRUE) */

#endif /* #ifndef CRY_CRC_H */
