/* --------{ EB Automotive C Source File }-------- */
#ifndef CRY_CCM_COMMON_H
#define CRY_CCM_COMMON_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm.h>
#include <Cry_CcmDecryptConfig.h>  /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_CcmEncryptConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

/*==================[macros]======================================================================*/

#if (defined CRY_CCM_BLOCK_LEN)
#error CRY_CCM_BLOCK_LEN is already defined
#endif
/** \brief Size of a CCM block. */
#define CRY_CCM_BLOCK_LEN     16U

/*==================[type definitions]============================================================*/

/*---[enum]---------------------------------------------------------------------------------------*/

/** \brief  CCM algorithm implementation state machine states.
 **/
typedef enum
{
  CRY_CCM_ENC_S_UNINIT,
  CRY_CCM_ENC_S_WAIT_FOR_INIT,
  CRY_CCM_ENC_S_INITIALIZED,
  CRY_CCM_ENC_S_FORMAT_DATA,
  CRY_CCM_ENC_S_ENC_B0,
  CRY_CCM_ENC_S_GEN_MAC,
  CRY_CCM_ENC_S_WAIT_SB_ST,
  CRY_CCM_ENC_S_ENC_MAC,
  CRY_CCM_ENC_S_MOV_ADATA,
  CRY_CCM_ENC_S_ENC_PAYLOAD,
  CRY_CCM_ENC_S_CP_COPY_TAG,
  CRY_CCM_ENC_S_CP_PLAINTEXT
}
Cry_CcmCryptStateType;

/** \brief  MAC calculation state machine states.
 **/
typedef enum
{
  CRY_CBC_ENC_S_UNINIT,
  CRY_CBC_ENC_S_REQ_SB_ST,
  CRY_CBC_ENC_S_WAIT_SB_ST,
  CRY_CBC_ENC_S_ENC_AAD,
  CRY_CBC_ENC_S_WAIT_AAD_UPD,
  CRY_CBC_ENC_S_CP_FROM_INP,
  CRY_CBC_ENC_S_REQ_SB_UPD,
  CRY_CBC_ENC_S_WAIT_SB_UPD,
  CRY_CBC_ENC_S_REQ_SB_FIN,
  CRY_CBC_ENC_S_WAIT_SB_FIN,
  CRY_CBC_ENC_S_SAVE_MAC
}
Cry_CcmCryptMACStateType;

/** \brief  Block encryption state machine states.
 **/
typedef enum
{
  CRY_AES_ENC_S_UNINIT,
  CRY_AES_ENC_S_REQ_SB_ST,
  CRY_AES_ENC_S_WAIT_SB_ST,
  CRY_AES_ENC_S_REQ_SB_UPD,
  CRY_AES_ENC_S_WAIT_SB_UPD,
  CRY_AES_ENC_S_REQ_SB_FIN,
  CRY_AES_ENC_S_WAIT_SB_FIN
}
Cry_CcmCryptBlockStateType;

/** \brief  Payload encryption state machine states.
 **/
typedef enum
{
  CRY_PLD_ENC_S_UNINIT,
  CRY_PLD_ENC_S_REQ_SB_ST,
  CRY_PLD_ENC_S_WAIT_SB_ST,
  CRY_PLD_ENC_S_CP_FROM_INP,
  CRY_PLD_ENC_S_REQ_SB_UPD,
  CRY_PLD_ENC_S_WAIT_SB_UPD,
  CRY_PLD_ENC_S_XOR_IN_DATA,
  CRY_PLD_ENC_S_CP_TO_OUTP,
  CRY_PLD_ENC_S_REQ_SB_FIN,
  CRY_PLD_ENC_S_WAIT_SB_FIN
}
Cry_CcmCryptPayloadStateType;

/*---[struct]-------------------------------------------------------------------------------------*/

/** \brief  CCM algorithm implementation context structure.
 **/
typedef struct
{
  /** \brief  Length of the input data.  **/
          uint32                                           iputTextLength;
  /** \brief  Length of the input data.  **/
          uint32                                           inDataLen;
  /** \brief  Length of the output data.  **/
          uint32                                           oputTextLength;
  /** \brief  Temporary variable to store how much of a block is filled.  **/
          uint32                                            blockFilled;
  /** \brief  How much of the aData is left.  **/
          uint32                                           leftAData;
#if (CRY_CCM_DEC_ENABLED == STD_ON)
  /** \brief  How much of the plain text was processed.  **/
          uint32                                           processedPT;
#endif
  /** \brief  Pointer to the output buffer length.  **/
    P2VAR(uint32,                  TYPEDEF, CRY_APPL_DATA) oputTextLengthPtr;
  /** \brief  Pointer to the output buffer.  **/
    P2VAR(uint8,                   TYPEDEF, CRY_APPL_DATA) oputTextPtr;
  /** \brief  Pointer to a temporary buffer.  **/
    P2VAR(uint8,                   TYPEDEF, CRY_APPL_DATA) processPtr;
  /** \brief  Pointer to the input buffer.  **/
  P2CONST(uint8,                   TYPEDEF, CRY_APPL_DATA) iputTextPtr;
  /** \brief  Pointer to the input buffer.  **/
  P2CONST(uint8,                   TYPEDEF, CRY_APPL_DATA) initInDataPtr;
  /** \brief  Pointer to the key.  **/
  P2CONST(Csm_SymKeyType,          TYPEDEF, CRY_APPL_DATA) keyPtr;
  /** \brief  Pointer to the configuration.  **/
  P2CONST(Cry_CcmCryptConfigType,  TYPEDEF, CRY_APPL_DATA) cfgPtr;
  /** \brief  CCM algorithm state machine state.  **/
          Cry_CcmCryptStateType                            ctxState;
  /** \brief  Payload encryption/decryption state machine state.  **/
          Cry_CcmCryptPayloadStateType                     payloadState;
  /** \brief  MAC calculation state machine state.  **/
          Cry_CcmCryptMACStateType                         macState;
  /** \brief  Block encryption/decryption state machine state.  **/
          Cry_CcmCryptBlockStateType                       blockEncState;
  /** \brief  Flag to indicate if the aData was MAC-ed.  **/
          boolean                                          aDataProcessed;
#if (CRY_CCM_DEC_ENABLED == STD_ON)
  /** \brief  Buffer to store decrypted payload.  **/
          uint8                                            plainText[CRY_MAX_PAYLOAD_SIZE];
#endif
  /** \brief  Temporary buffer to store encryption/decryption result.  **/
          uint8                                            block[CRY_CCM_BLOCK_LEN];
  /** \brief  Initialization vector for encryption/decryption.  **/
          uint8                                            IV[CRY_CCM_BLOCK_LEN];
  /** \brief  Encrypted initialization vector.  **/
          uint8                                            encIV[CRY_CCM_BLOCK_LEN];
  /** \brief  Padded MAC needed for final tag.  **/
          uint8                                            paddedMac[CRY_CCM_BLOCK_LEN];
  /** \brief  Encrypted MAC needed for final tag.  **/
          uint8                                            encMac[CRY_CCM_BLOCK_LEN];
  /** \brief  Formated header for MAC calculation.  **/
          uint8                                            B0Mac[CRY_CCM_BLOCK_LEN];
  /** \brief  Formated header for payload encryption/decryption.  **/
          uint8                                            B0Enc[CRY_CCM_BLOCK_LEN];
  /** \brief  Buffer to store first block of the aData.  **/
          uint8                                            aad[CRY_CCM_BLOCK_LEN];
  /** \brief  Buffer in which the last encryption block is stored.  **/
          uint8                                            lastCipherText[CRY_CCM_BLOCK_LEN];
  /** \brief  Flag to indicate if the encryption was finished.  **/
          boolean                                          encFinished;
}
Cry_CCMCtxType;

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Format the header for encryption/decryption and MAC generation/verification
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 ** \param[in]      payloadLen  Length of the payload.
 **/
extern FUNC(void, CRY_CODE) Cry_CCMFormatHeader
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx,
 uint32                                           payloadLen
);

/** \brief  Format the header for the authentificated data
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_CCMFormatAad
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Block encryption with AES-128
 **
 ** \param[in,out]  ctx                Pointer to context structure.
 **
 ** \param[in]      iputTextPtr        A pointer to the start of an array which contains the
 **                                    constant plain text that shall be encrypted.
 ** \param[in]      iputTextLength     Length of the constant plain text in bytes.
 ** \param[out]     oputTextPtr        A pointer to the start of an array where the encrypted
 **                                    text will be stored.
 ** \param[in,out]  oputTextLengthPtr  Holds a pointer to a memory location in which the length
 **                                    information in bytes is stored.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK            If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK        If the service has not been started.
 ** \retval   CSM_E_SMALL_BUFFER  If the result buffer is too small for the encrypted data.
 ** \retval   CSM_E_BUSY          If the service is currently processing.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CCMBlockEnc
(
    P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx,
  P2CONST(uint8,           AUTOMATIC, CRY_APPL_DATA) iputTextPtr,
          uint32                                     iputTextLength,
    P2VAR(uint8,           AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
    P2VAR(uint32,          AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
);

/** \brief  Block encryption start in CTR mode.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CTRReqStart
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Block encryption update in CTR mode.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CTRReqUpdate
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Block encryption finish in CTR mode.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CTRReqFinish
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Block encryption start in CBC mode.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCReqStart
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Block encryption update in CBC mode.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCReqUpdate
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Block encryption finish in CBC mode.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCReqFinish
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Encrypt the authentificated data in CBC mode
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK            If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK        If the service has not been started.
 ** \retval   CSM_E_SMALL_BUFFER  If the result buffer is too small for the encrypted data.
 ** \retval   CSM_E_BUSY          If the service is currently processing.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCEncAad
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Copy data from input for the payload encryption.
 **
 ** \param[in,out]  ctx         Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_CTRCopyFromInput
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
);

/** \brief  Increment the IV.
 **
 ** \param[in,out]  IV         Pointer to IV.
 **/
extern FUNC(void, CRY_CODE) Cry_CCMInc
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) IV
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

/** \endcond  */

#endif /* #ifndef CRY_CCM_COMMON_H */
