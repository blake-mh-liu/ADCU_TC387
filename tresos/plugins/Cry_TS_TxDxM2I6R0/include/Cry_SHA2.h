/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_SHA2,1 */

#ifndef CRY_SHA2_H
#define CRY_SHA2_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>            /* !LINKSTO EB_CRY_0002,1 */

#include <Cry_SHA2Config.h> /* !LINKSTO EB_CRY_0002,1 */

#if (CRY_SHA2_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start SHA2 computation
 **
 ** This function requests the start of the SHA computation for the
 ** given configuration. The start is performed in Cry_SHA2MainFunction()
 **
 ** \param[in]    cfgPtr  A pointer to the configuration for which the start of the SHA
 **                       computation should be requested.
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_BUSY    If a service of the SHA compuation is already running
 **
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA2Start
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/** \brief  Update SHA2 computation.
 **
 ** This function requests the update of the SHA computation for the
 ** given data. The update is performed in Cry_SHA2MainFunction().
 **
 ** \param[in] dataPtr  A pointer to the start of an array which contains a part of the
 **                     data for which the SHA digest should be created.
 ** \param[in] dataLength  The amount of bytes of data
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_BUSY    If the main function is processing a requested service at the moment
 ** \retval   CSM_E_NOT_OK  If no SHA computation has been started via Cry_SHA2Start(), yet.
 **
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA2Update
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
);

/** \brief  Finish SHA2 computation
 **
 ** This function requests the finishing of the SHA computation and
 ** the storing of the hash digest in the given result buffer. The finishing
 ** is performed in Cry_SHA2MainFunction().
 **
 ** \param[out] resultPtr Pointer to the start of a buffer where the hash digest should be stored
 **
 ** \param[in,out] resultLengthPtr  a pointer to a variable which contains the maximal allowed
 ** length in bytes for the hash and where the actual length in bytes of the hash should be stored
 **
 ** \param[in] truncationAllowed If this flag is ::TRUE and the hash digest is longer than
 ** the given result buffer, the hash is truncated to the buffer length. If
 ** this flag is ::FALSE and the hash digest is longer than the given result
 ** buffer, an error code of ::CSM_E_SMALL_BUFFER is returned
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_BUSY    If the main function is processing a requested service at the moment
 ** \retval   CSM_E_NOT_OK  If no SHA computation has been started via Cry_SHA2Start(), yet.
 **
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA2Finish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 truncationAllowed
);

/** \brief  Perform the SHA2 tasks
 **
 **  This function performs the actual SHA computation tasks which
 **  have been requested by the service functions. When a task has finished, the
 **  function Csm_HashServiceCallbackNotification() is called to
 **  inform the CSM of the result. If the complete SHA2 computation has
 **  finished, additionally the function Csm_HashServiceFinishNotification() is
 **  called.
 **
 **/
extern FUNC(void, CRY_CODE) Cry_SHA2MainFunction
(
  void
);
/** \brief  Algorithm identifier of hash algorithm
 **
 **  This function returns the algorithm identifier of the hash algorithm
 **  defined in the given configuration. See RFC 3279 for examples
 **
 ** \param[in] cfgPtr an pointer to the configuration for which the algorithm identifier
 ** should be returned
 **
 ** \param[out] AlgorithmIdLengthPtr  a pointer to a variable where the actual length of the
 ** algorithm identifier should be stored
 **
 ** \returns  Algorithm Id
 **
 **/
extern FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_SHA2AlgorithmId
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) AlgorithmIdLengthPtr
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_SHA2_ENABLED == STD_ON) */

#endif
