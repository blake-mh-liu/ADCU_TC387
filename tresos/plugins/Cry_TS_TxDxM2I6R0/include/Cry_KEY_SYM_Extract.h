/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_KEY_SYM_Extract,1 */

#ifndef CRY_KEY_SYM_EXTRACT_H
#define CRY_KEY_SYM_EXTRACT_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                        /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_KEY_SYM_ExtractConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

#if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Start KEY_SYM extract computation.
 **
 ** This function requests the start of the KEY_SYM extract computation
 ** for the given configuration.
 ** The start is performed in Cry_KEY_SYM_ExtractMainFunction().
 **
 ** \param[in]      cfgPtr  A pointer to the configuration for which the start of the symmetrical
 **                         key extraction is requested.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_NOT_OK  ---
 ** \retval   CSM_E_BUSY    If a service of the KEY_SYM extract computation is
 **                         already running.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_KEY_SYM_ExtractStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/** \brief  Update KEY_SYM extract computation.
 **
 ** This function requests the update of the KEY_SYM extract computation
 ** for the given data.
 ** The update is performed in Cry_KEY_SYM_ExtractMainFunction().
 **
 ** \param[in]      dataPtr     A pointer to the start of an array which
 **                             contains the key that have to extract in
 **                             a CSM-conforming format.
 ** \param[in]      dataLength  Length of the key in bytes.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no KEY_SYM extract computation has been
 **                         started via Csm_SymKeyExtractStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_KEY_SYM_ExtractUpdate
(
      P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
              uint32                            dataLength
);

/** \brief  Finish KEY_SYM extract computation.
 **
 ** This function requests the finishing of the KEY_SYM extract computation
 ** and the storing of the extracted key data in the given buffer.
 ** The finish is performed in Cry_KEY_SYM_ExtractMainFunction().
 **
 ** \param[out]      keyPtr  A pointer to the structure where to store the
 **                         result.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no KEY_SYM extract computation has been
 **                         started via Csm_SymKeyExtractStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_KEY_SYM_ExtractFinish
(
  P2VAR(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/** \brief  Perform the KEY_SYM extract computation tasks.
 **
 ** This function performs the actual KEY_SYM extract computation tasks
 ** which have been requested by the service functions. The function calls
 ** the main function of the configured primitive to perform the tasks.
 **/
extern FUNC(void, CRY_CODE) Cry_KEY_SYM_ExtractMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON) */

#endif /* #ifndef CRY_KEY_SYM_EXTRACT_H */
