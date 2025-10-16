/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_AES_Encrypt,1 */

#ifndef CRY_AES_ENCRYPT_H
#define CRY_AES_ENCRYPT_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                    /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_AES_EncryptConfig.h>  /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_AES_Common.h>

#if (CRY_AES_ENCRYPT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Start AES block encryption computation.
 **
 ** This function requests the start of the AES encryption computation for the given configuration.
 ** The start is performed in Cry_AES_Encrypt_MainFunction().
 **
 ** \param[in]    cfgPtr  A pointer to the configuration for which the start of the AES encryption
 **                       is requested.
 ** \param[in]    keyPtr  A pointer to the key which should be used in the AES block
 **                       encryption computation.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_NOT_OK  ---
 ** \retval   CSM_E_BUSY    If a service of the AES block encryption computation is
 **                         already running.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_EncryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/** \brief  Update AES block encryption computation.
 **
 ** This function requests the update of the AES block encryption computation for the
 ** given data.
 ** The update is performed in Cry_AES_Encrypt_MainFunction().
 **
 ** \param[in]      iputTextPtr        A pointer to the start of an array which contains the
 **                                    constant plain text that shall be encrypted.
 ** \param[in]      iputTextLength     Length of the constant plain text in bytes.
 ** \param[out]     oputTextPtr        A pointer to the start of an array where the encrypted
 **                                    text will be stored.
 ** \param[in,out]  oputTextLengthPtr  Holds a pointer to a memory location in which the length
 **                                    information in bytes is stored. On calling this function this
 **                                    parameter shall contain the size of the buffer provided
 **                                    by oputTextPtr. When the request has finished, the amount
 **                                    of data that has been encrypted shall be stored.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no AES block encryption computation has been started via
 **                         Csm_SymBlockEncryptStart(), yet.
 **                         Or if the provided buffer is too small to store the result.
 ** \retval   CSM_E_BUSY    If the main function is currently processing a requested service.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_EncryptUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) iputTextPtr,
          uint32                            iputTextLength,
    P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
);

/** \brief  Finish AES block encryption computation.
 **
 ** This function requests the finishing of the AES block encryption computation and
 ** the storing of the encrypted text in the given buffer.
 ** The finish is performed in Cry_AES_Encrypt_MainFunction().
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no AES block encryption computation has been started via
 **                         Csm_SymBlockEncryptStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing a requested service.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_EncryptFinish
(
  void
);

/** \brief  Perform the AES block encryption computation tasks.
 **
 ** This function performs the actual AES block encryption computation tasks
 ** which have been requested by the service functions. The function calls the
 ** main function of the configured primitive to perform the tasks.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_EncryptMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_AES_ENCRYPT_ENABLED == STD_ON) */

#endif /* #ifndef CRY_AES_ENCRYPT_H */
