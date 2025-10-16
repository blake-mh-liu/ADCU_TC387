#ifndef PROG_PUB_H
#define PROG_PUB_H

/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Pub.h                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

#include "PROG_Cfg.h"

#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"
#endif /* (PROG_CRY_PRESENT == STD_ON)*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/* Flag indicating if Response to Prog session from appli shall be done */
extern u8 m_ubSimulateProgSessionWithResponse;

/* Flag to indicate the Post Software Download Status */
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
extern u8 m_ubPostSoftwareDownloadStatus;
#endif /*(PROG_OTA_DUALBANK_USED += STD_ON))*/

#if (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)
/* Number of check memory failed requests */
extern u8 m_ubFailedCheckMemoryCount;
/* check memory routine status */
extern u8 m_ubCheckMemoryStatus;
#endif
#if (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)
/* Valid Application routine status */
extern u8 m_ubValidateMemoryStatus;
#endif
#if (PROG_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
extern u32 m_ulRsDelayTimer;
#endif/*(PROG_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
#if (PROG_CSMASR43_USED == STD_ON)
/* Array of Prog-Csm JobConf */
extern const tProgCsmJobConf m_astProgCsmJobConf[PROG_CSM_NUMCONF_JOBS];
#endif
#if (PROG_DOIP_SUPPORT_ENABLE == STD_ON)
extern u8 m_ubDoIpRoutingActivationRequestRxConfirmation;
extern u8 m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack;
#endif
#define PROG_TD_CALL  0x01U /*Macro to indicate that the PROG_VerificationOnTheFly API is called while in TD state*/
#define PROG_RTE_CALL 0x02U /*Macro to indicate that the PROG_VerificationOnTheFly API is called while in RTE state*/

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

#if (PROG_CSM_MAC_USED == STD_ON)
/** \brief Get the key used to compute MAC checksum
 **
 ** This function is called to get the key used for MAC computation
 **
 ** \param[out] pstMacKey Pointer to the Key
 **
 **/
extern void PROG_GetMacKey(Csm_SymKeyType* pstMacKey);
#endif

/** \brief Initialize PROG module **/
extern void PROG_Init(void);
/** \brief Manage function to be called periodically **/
extern void PROG_Manage(void);
/** \brief Manage function to be called as fast as possible to perform
 **               background actions **/
extern void PROG_BckdManage(void);
/** \brief Initialize PROG_SimulateExtendedSessionNoResponse function **/
extern void PROG_SimulateExtendedSessionNoResponse(void);
/** \brief Reception of a programming session request **/
extern void PROG_OpenProgrammingSession (void);
/** \brief request to close the programming session
 **
 ** This function is called to request the close of the programming session
 **
 ** \param[in] eUdsChangeReason reason why the close is requested
 **
 **/
extern void PROG_CloseProgrammingSession (tUdsChangeReason eUdsChangeReason);
/** \brief request to close the extended session
 **
 ** This function is called to request the close of the extended session
 **
 ** \param[in] eUdsChangeReason reason why the close is requested
 **
 **/
extern void PROG_CloseExtendedSession (tUdsChangeReason eUdsChangeReason);
/** \brief Reception of a streaming frame
 **
 ** This function is called on reception of a streaming frame
 **
 ** \param[in] ulReceivedDataLength Data Length in the received frame
 ** \param[in] aubData Pointer to buffer where received data are located
 **
 **/
extern void PROG_StreamingFrameReceived(u16 ulReceivedDataLength, u8* aubData);
/** \brief Inform of network status change
 **
 ** This function is called on change of the network status
 **
 ** \param[in] uwNetworkStatus new network status
 **
 **/
extern void PROG_SetNetworkStatus(u16 uwNetworkStatus);
/** \brief Request to simulation a programming session opening **/
extern void PROG_SimulateOpenProgSession(void);
/** \brief called on confirmation of frame transmission
 **
 ** This function is called on confirmation of a diagnostic response
 ** transmission
 **
 ** \param[in] uMsgIdx Identifier of the transmission frame
 ** \param[in] ebStatus status of the transmission
 **
 **/
extern void PROG_TpTxConf(tTpMsgIdx uMsgIdx, u8 ebStatus);

/** \brief called on frame reception
 **
 ** This function is called on a diagnostic frame reception
 **
 ** \param[in] uMsgIdx Identifier of the transmission frame
 ** \param[in] ebStatus status of the transmission
 **
 **/
extern void PROG_TpRxInd(tTpMsgIdx uMsgIdx, u8 ebStatus);

/** \brief called on frame reception
 **
 ** This function is called on a diagnostic frame reception
 **
 ** \param[in] ubStatus status of the transmission
 **
 **/
extern void PROG_TpStartOfReceptionInd(u8 ubStatus);

/** \brief Called on entry to Sleep state **/
extern void PROG_Entry_Sleep(void);

#if (PROG_LIMIT_NB_REQUEST_SEED_ENABLED ==STD_ON)
/** \brief Set the current Request seed counter value
 **
 ** \param[in] ubRequestSeedCounter request seed counter to set
 **
 **
 **/
extern void PROG_SetRequestSeedCounter(u8 ubRequestSeedCounter);

/** \brief Get the current Request seed counter value
 **
 ** \return value u8 request seed counter to get
 **
 **
 **/
extern u8 PROG_GetRequestSeedCounter(void);

/** \brief Set the current Request seed Timer
 **
 ** \param[in] ulRequestSeedTimer request seed timer to set
 **
 **
 **/
extern void PROG_SetRequestSeedTimer(u32 ulRequestSeedTimer);

/** \brief Set the current Request seed counter
 **
 ** \return value u32 request seed Timer to get
 **
 **
 **/
extern u32 PROG_GetRequestSeedTimer(void);
#endif

#if ((PROG_WRITE_FINGERPRINT_ENABLE == STD_ON) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** \brief Called on entry to WriteFingerprint state **/
extern void PROG_Entry_WriteFingerprint(void);
#endif
#if ((PROG_WRITE_FINGERPRINT_ENABLE == STD_ON) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** \brief Called on loop in WriteFingerprint state **/
extern void PROG_WriteFingerprintCheck(void);
#endif
#if (PROG_ECU_RESET_ENABLE == STD_ON)
/** \brief Called on entry to EcuReset state **/
extern void PROG_Entry_EcuReset(void);
#endif
/** \brief Called on entry to Reset state **/
extern void PROG_Entry_Reset(void);
/** \brief Called on entry to DefaultSession state **/
extern void PROG_Entry_DefaultSession(void);
/** \brief Called on entry to ProgrammingSession state **/
extern void PROG_Entry_ProgrammingSession(void);
/** \brief Called on entry to ExtendedSession state **/
extern void PROG_Entry_ExtendedSession(void);

#if ((PROG_SA_SEED_ENABLE == STD_ON) && (PROG_SECURITY_ENABLE == STD_ON))
/** \brief Called on entry to GetSeed state **/
extern void PROG_Entry_GetSeedCheck(void);
/** \brief Called on entry to GetSeed state **/
extern void PROG_Entry_GetSeed(void);
/** \brief API called to get seed **/
extern void PROG_Do_GetSeed(void);
#endif /* ((PROG_SA_SEED_ENABLE == STD_ON) && (PROG_SECURITY_ENABLE == STD_ON)) */

#if (PROG_SA_SEED_ENABLE == STD_ON)
/** \brief Called in GetSeed_Unlocked state **/
extern void PROG_GetSeed_Unlocked(void);
extern void PROG_GetSeedFailed(void);
#endif
extern void PROG_TriggerFailedEvent(void);
/** \brief Called in CHECK_MEMORY_FINISH state **/
extern void PROG_AnswerSuccesiveCheckMemoryRequests(void);

#if (PROG_SA_KEY_ENABLE == STD_ON)
/** \brief Called on entry to CompareKey state **/
extern void PROG_Entry_CompareKeyCheck(void);
/** \brief Called on entry to CompareKey state **/
extern void PROG_Entry_CompareKey(void);
/** \brief API called to get seed result **/
extern void PROG_Do_CompareKey(void);
extern void PROG_SendKey_Finish(void);
extern void PROG_CompareKey_Failed(void);
#endif /* (PROG_SA_KEY_ENABLE == STD_ON) */

/** \brief Called on entry to EraseCheck state **/
extern void PROG_Entry_EraseCheck(void);
/** \brief Called on entry to Erase state **/
extern void PROG_Entry_Erase(void);
/** \brief Called in Erase state **/
extern void PROG_Erase(void);
/** \brief Called on entry to EraseNRC78 state  **/
extern void PROG_Entry_EraseNRC78(void);
/** \brief Called on entry to EraseTransmitNRC78 state  **/
extern void PROG_Entry_EraseTransmitNRC78(void);

/** \brief Send the NRC_78 instantaneously to gain time **/
extern void PROG_SendNRC78(void);

#if (PROG_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
/** \brief Set the current Request seed delay timer value
 **
 ** \param[in] ulRsDelayTimer request seed delay timer value to set
 **
 **
 **/
extern void PROG_SetRsDelayTimer(u32 ulRsDelayTimer);

/** \brief Get the current Request seed delay timer value
 **
 ** \return value u32 request seed delay timer to get
 **
 **
 **/
extern u32 PROG_GetRsDelayTimer(void);
#endif

#if PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON
/** \brief Called receiving a RD request
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_RD_Check(void);
#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called receiving a RD request after a RTE
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_Guard_RD_Check_RTEFinish(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called receiving a RD request after a RD
**
** \return Result of check
** \retval PROG_E_OK RD request accepted
** \retval PROG_E_NOT_OK RD request not accepted
**
**/
extern tProgStatus PROG_Guard_RD_Check_RDFinish(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called receiving a RD request after a write finger print or CheckMemory
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_Guard_RD_FlashEnabled(void);
#endif

/** \brief Called during transition from RTE_DECOMP_WRITE_CHECK to RTE state **/
extern void PROG_Guard_RTE_Decomp_Check(void);

/** \brief Called on entry to RD state **/
extern void PROG_Entry_RD(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called on entry to RD SIGNATURE state **/
extern void PROG_Entry_RD_Signature(void);

/** \brief Called on entry to RD Finish state **/
extern void PROG_Entry_RD_Finish(void);

/** \brief Called on entry to RD Failed state **/
extern void PROG_Entry_RD_Failed(void);
#endif

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/** \brief Called on entry to TD state **/
extern void PROG_Entry_TD(void);
/** \brief Called on entry to Streaming state **/
extern void PROG_Entry_Streaming(void);
/** \brief Called in Streaming state **/
extern void PROG_Streaming(void);
/** \brief Called on entry to TD_Failed state **/
extern void PROG_Entry_TD_Failed(void);
/** \brief Called on entry to Write state **/
extern void PROG_Entry_Write(void);
/** \brief Called in Write state **/
extern void PROG_Write(void);
/** \brief Called in WriteCheck state **/
extern void PROG_WriteCheck(void);
/** \brief Called in WriteCheck state **/
extern tProgStatus PROG_VerifyCryptoState(void);
/** \brief Called in WriteCheck state **/
extern void Prog_Update_OldDataLength(void);
/** \brief Called in WriteCheck state **/
extern void Prog_Update_NewDataLength(void);
/** \brief Called in WriteCheck state **/
extern void Prog_Update_LastNewDataLength(void);
/** \brief Called on exit from TD_Write state **/
extern void PROG_Exit_TD_Write(void);
/** \brief Called in TD state **/
extern tProgStatus PROG_TD(void);

#if ((PROG_CRC_CALCULATION != PROG_NO_CRC) || (PROG_SIGNATURE_CALCULATION == STD_ON) || (PROG_HASH_CALCULATION == STD_ON))
/** \brief Called in CRC state **/
extern tProgStatus PROG_VerificationOnTheFly(u8 ubHsmevent);
extern tProgStatus PROG_CRC(void);
extern void PROG_Do_CheckHash(void);
extern void PROG_Entry_CheckHash(void);
#endif
extern void PROG_Do_CheckSignature(void);
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
extern void PROG_Entry_TD_Header(void);
extern void PROG_SignerInfoCheck(void);
extern void PROG_Entry_ValidateSignerInfo(void);
extern void PROG_SignatureCheck(void);
extern void PROG_Entry_ValidateSignature(void);
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_20 */
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

extern void PROG_HSMUpdate_TD(void);
extern void PROG_Entry_HSMUpdate_TDFinish(void);
extern void PROG_HSMStatusManage(void);

#if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON
/** \brief Called on entry to RTEFailed state **/
extern void PROG_Entry_RTEFailed(void);
/** \brief Called on entry to RTE state **/
extern void PROG_Entry_RTE(void);
#if ((PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** \brief Called on exit to RTE Decrypt state **/
extern void PROG_Exit_RTE_Decrypt(void);
#endif
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)  || (PROG_IMPL_VARIANT == PROG_IMPL_2) || \
     (PROG_IMPL_VARIANT == PROG_IMPL_3)  || (PROG_IMPL_VARIANT == PROG_IMPL_4) || \
     (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)|| \
     (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)|| \
     (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
/** \brief Called on cyclically in RTE state **/
extern void PROG_RTE(void);
#endif /* (PROG_IMPL_VARIANT != PROG_IMPL_20) && (PROG_IMPL_VARIANT != PROG_IMPL_30)*/
/** \brief Called on entry to RTEFinish state **/
extern void PROG_Entry_RTEFinish(void);

#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
extern void PROG_ComputeMessageDigest(void);
extern void PROG_MessageDigestCheck(void);
#endif /* #if (PROG_IMPL_VARIANT == PROG_IMPL_20) */
#endif /* #if (PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON) */
/** \brief Called to send negative response
 **
 ** \param[in] eUdsStatus Error code to use in negative response
 **/
extern void PROG_Send_NRC(tUdsStatus eUdsStatus);
/** \brief Check if SBL is valid and compatible
 **
 ** \return Result of check
 ** \retval PROG_E_OK SBL is valid and compatible with PBL
 ** \retval PROG_E_NOT_OK SBL is not valid and/or incompatible with PBL
 **
 **/
extern tProgStatus PROG_ActiveSBL_Check(void);
/** \brief Called on entry to ActiveSBL state **/
extern void PROG_Entry_ActiveSBL(void);
/** \brief Called on entry to SblSynch state **/
extern void PROG_Entry_SblSynch(void);
/** \brief Called to perform the jump to SBL **/
extern void PROG_JumpToSBL(void);
/** \brief Called on entry to AutoControl state **/
extern void PROG_Entry_AutoControl(void);
#if PROG_AUTOCONTROL_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2)||\
    (PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)|| \
    (PROG_IMPL_VARIANT == PROG_IMPL_5))
/** \brief manage asynchronous autocontrol **/
extern void PROG_AutoControl_Process(void);
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2) ||\
          (PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)|| \
          (PROG_IMPL_VARIANT == PROG_IMPL_5))*/
#endif /* PROG_AUTOCONTROL_ENABLE == STD_ON */

#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_60)))
/* Exclude doxygen extract as Api already exist in PROG_Cbk.c */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** \brief Check if application is valid
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid
 **
 **/

extern tProgBoolean PROG_IsValidApplication(void);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif

#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60))
/* Exclude doxygen extract as Api already exist in PROG_Cbk.c */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** \brief API that invalidate the application marker
 **
 ** This API is before starting the erasing routine.
 ** It shall invalidate the application or the current erased section to make sure no jump to the application will be done
 ** if an error occurred and the application is not fully erased or reprogrammed
 **
 ** \param[in] Erased Start address of the segment that will be erased
 ** \param[in] ulEraseLength requested erase length
 ** \param[in] ErrorCode UDS error code that shall be return in case of error during API treatment
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment (ErrorCode shall be filled in this case)
 **/
extern tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif

#if (PROG_UPDATE_PSI_ENABLE == STD_ON)
/** \brief Called on entry to UpdatePSI state **/
extern void PROG_Entry_UpdatePSI(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
/** \brief Called to write one or more flash pages
 **
 ** This API can be called by the Framework to write one or more
 ** specific flash pages.
 **
 ** \param[in] ulAddress Address of the first page to write
 ** \param[in] ubPages number of pages to write
 ** \param[in] pulDataBuffer pointer to the buffer of data to write
 ** \param[in] uwDataBufferLenght Exact length of data to write
 **
 ** \return Result of the write operation
 ** \retval PROG_FLASH_PAGE_E_OK write is successfull
 ** \retval PROG_FLASH_PAGE_E_NOT_OK write is not successfull
 **/
extern u8 PROG_FlashPage(u32 ulAddress, u8 ubPages, u32* pulDataBuffer, u16 uwDataBufferLenght);
/** \brief Called by the Flash driver to know if the page can be written
 **
 ** This API is called by the Flash driver to know if it is authorized to write a Flash pages.
 ** The API will forward the request to the framework
 **
 ** \param[in] uAddr pointer on Address of the page to write
 **
 ** \return Result of the check
 ** \retval PROG_NO_SKIP_PAGE page can be written
 ** \retval others write is not allowed
 **/
extern u8 PROG_SkipPage(u32* uAddr);
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_2) */
#if PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE == STD_ON
/** \brief Called to verify if CheckProgDependencies routine can be executed
 **
 ** \return Result of check
 ** \retval PROG_E_OK check is allowed
 ** \retval PROG_E_NOT_OK check is not allowed
 **
 **/
extern tProgStatus PROG_Check_Prg_Dep_Check(void);
/** \brief Called to send CheckProgDependencies routine response  **/
extern void PROG_Entry_CheckDependenciesFinish(void);
/** \brief Called to calculate the CRC for CheckProgDependencies routine **/
extern void PROG_Do_CheckPrgDependencies(void);
#endif /* PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE == STD_ON */

#if ((PROG_CRC_CALCULATION == PROG_TD_CRC16) || ( (PROG_CRC_CALCULATION == PROG_NO_CRC) && \
    ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))))
/** \brief Called to calculate CRC
 **
 ** \param[in] aubCrcData Data to add in the CRC calculation
 ** \param[in] ulReadLength Data length to add in the CRC calculation
 ** \param[out] uwCrcValue Pointer to variable where to set the CRC result
 **/
extern void PROG_CalcCrc16(const u8 * aubCrcData, u32 ulReadLength, u16 * uwCrcValue);
#endif /*(PROG_CRC_CALCULATION == PROG_TD_CRC16)*/
#if (PROG_CRC_CALCULATION == PROG_TD_CRC32)
/** \brief Called to calculate CRC
 **
 ** \param[in] aubCrcData Data to add in the CRC calculation
 ** \param[in] ulReadLength Data length to add in the CRC calculation
 ** \param[out] ulCrcValue Pointer to variable where to set the CRC result
 **/
extern void PROG_CalcCrc32(const u8 * aubCrcData, u32 ulReadLength, u32 * ulCrcValue);
#endif
/** \brief Called on entry to INIT state **/
extern  void PROG_Entry_INIT(void);
/** \brief Called on entry to INIT state **/
extern  void PROG_Exit_INIT(void);

/** \brief Called on entry to PreInit state **/
extern  void PROG_Entry_PreInit(void);
/** \brief Called in PreInit state **/
extern  void PROG_PreInit(void);

/* HsmStub.c  */
/** \brief Called on entry to Alive state **/
extern  void PROG_Entry_Alive(void);
/** \brief Called on entry to EraseFinish state **/
extern void PROG_Entry_EraseFinish(void);

/** \brief Called before going to PROG_Erase state
 **
 ** \return Result of check
 ** \retval PROG_E_OK Erase request accepted
 ** \retval PROG_E_NOT_OK Erase request not accepted
 **
 **/
extern tProgStatus PROG_Erase_Guard(void);

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called receiving a Erase request after completion Erase Request
 **
 ** \return Result of check
 ** \retval PROG_E_OK Erase request accepted
 ** \retval PROG_E_NOT_OK Erase request not accepted
 **
 **/
extern tProgStatus PROG_Guard_Erase_Check_EraseFinish(void);
#endif

#if PROG_IMPL_VARIANT == PROG_IMPL_20
extern void PROG_Entry_ValidateSBASignerInfo(void);
extern void PROG_SBASignerInfoCheck(void);
extern void PROG_Entry_ValidateSBASignature(void);
extern void PROG_SBASignatureCheck(void);
extern void PROG_Entry_DecompHeader(void);
extern void PROG_CheckDecompHeaderStatus(void);
#endif /* #if PROG_INI_IMPL == PROG_IMPL_20 */
#if (PROG_NETWORK_MANAGEMENT_ENABLE == STD_ON)
/** \brief Function providing the network status
 ** \return Network Status
 **
 **/
extern u16 PROG_GetNetworkStatus(void);
#endif

#define PROG_GET_DID_F0F3_START_SEC_CODE
#include <MemMap.h>
/** \brief Called by external module to get data of DID F0F3
 **
 ** This API is called by an external value to get the data of the DID F0F3
 ** (EcuId)
 **
 ** \param[out] aubData DID data
 **
 **/
extern void PROG_GetDidF0F3(u8 *aubData);
#define PROG_GET_DID_F0F3_STOP_SEC_CODE
#include <MemMap.h>

#define PROG_GET_DID_F0F6_START_SEC_CODE
#include <MemMap.h>
/** \brief Called by external module to get data of DID F0F6
 **
 ** This API is called by an external value to get the data of the DID F0F6
 ** (EcuId)
 **
 ** \param[out] aubData DID data
 **
 **/
extern void PROG_GetDidF0F6(u8 *aubData);
#define PROG_GET_DID_F0F6_STOP_SEC_CODE
#include <MemMap.h>


/** \brief Finishing the checksum  calculation
 **
 ** \return state
 ** \retval PROG_E_OK Calculation finished successfully
 ** \retval PROG_E_BUSY Calculation in progress
 ** \retval PROG_E_NOT_OK Calculation finished on error
 **
 **/
extern tProgStatus PROG_RangeChecksumFinish(void);

/** \brief Init of the Checksum Calculation */
extern void PROG_Entry_ChecksumByRange(void);

/** \brief Update the programming status
 **
 ** \param[in] ulProgrammingStatusMask the mask for a specific failure
 ** \param[in] ubStatus failure status (0 - present, 1 - not present)
 **
 **/
extern void PROG_SetProgrammingStatus(u32 ulProgrammingStatusMask, tProgBoolean ubStatus);

/** \brief Function providing the programming pre-conditions check status
 **
 ** \return Programming Pre-conditions check Status
 **
 **/
extern tProgStatus PROG_CheckProgrammingPreCondition(void);

/** \brief Check memory programming  **/
extern void PROG_Entry_CheckMemory(void);
#if (PROG_CHECK_MEMORY_ENABLE == STD_ON)
/** \brief Called on entry to CHECK_MEMORY_FINISH state  **/
extern void PROG_Entry_CheckMemoryFinish(void);
#endif
#if (((PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)) && (PROG_CHECK_MEMORY_ENABLE == STD_ON))
/** \brief Check memory programming  **/
extern void PROG_Exit_CheckMemory(void);
/** \brief Called on exit to CHECK_MEMORY_FINISH state  **/
extern void PROG_Exit_CheckMemoryFinish(void);
#endif
/** \brief Check memory programming  **/
#if (((PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || (PROG_IMPL_VARIANT == PROG_IMPL_60))  && (PROG_CHECK_MEMORY_ENABLE == STD_ON))
extern void PROG_Entry_CheckMemoryCompute(void);
extern void PROG_Entry_SignatureCheck(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)
/** \brief Called on entry to CHECK_MEMORY_FAILED state  **/
extern void PROG_Impl10_Entry_CheckMemoryFailed(void);
/** \brief Called on entry to RTE_COMPARE_HASH state  **/
extern void PROG_Impl10_CompareDataBlockHash(void);
/** \brief Called on entry to HASH_CHECK**/
extern void PROG_Impl10_CheckDataBlocksResult(void);
/** \brief Called on entry to SIGNATURE_CHECK **/
extern void PROG_Impl10_Entry_SignatureCheck(void);
/** \brief Called on entry to RTE_COMPARE_HASH **/
extern void PROG_Impl10_FinalizeHash(void);
/** \brief Called while RTE_COMPARE_HASH is active, it updates the hash calculation according to the length mentioned in VBT **/
extern void PROG_Impl10_Do_HashMoreUnwrittenData(void);
/** \brief Called on entry to MAC_GENERATATION, it generates the mac for each software part **/
extern void PROG_Impl10_GenerateMac(void);
/** \brief Called on guard of check memory to check whether it is allowed or not  **/
extern tProgStatus PROG_Impl10_CheckMemoryAllowed(void);
/** \brief Called during the write production key state to check if hash is finished **/
extern void PROG_Impl10_Do_CheckHashOfKey(void);
/** \brief Called on when the hash calculation is finished  **/
extern void PROG_Impl10_Entry_WriteKeyFinished(void);
/** \brief Called upon the reception of write key request  **/
extern void PROG_Impl10_Entry_CheckReceivedKey(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)
/** \brief Called on entry to CHECK_MEMORY_FAILED state  **/
extern void PROG_Impl90_Entry_ValidateFailed(void);
/** \brief Called on entry to CHECK_APPLICATION_VALIDITY status  **/
extern void PROG_Impl90_ApplicationValidatyStatus(void);
/** \brief Called on entry to CHECK_MEMORY_FINISH state  **/
extern void PROG_Impl90_Entry_ValidateFinish(void);
/** \brief Called on entry to TRANSMIT_NRC78 **/
extern void PROG_Impl90_TransmitNRC78(void);
/** \brief Called on entry to SIGNATURE_CHECK **/
extern void PROG_Impl90_Entry_SignatureCheck(void);
/** \brief Called on entry to RTE_COMPARE_HASH state  **/
extern void PROG_Impl90_CompareDataBlockHash(void);
/** \brief Called on entry to HASH_CHECK**/
extern void PROG_Impl90_CheckDataBlocksResult(void);
/** \brief Called on entry to RTE_COMPARE_HASH **/
extern void PROG_Impl90_FinalizeHash(void);
/** \brief Called while RTE_COMPARE_HASH is active, it updates the hash calculation according to the length mentioned in VBT **/
extern void PROG_Impl90_Do_HashMoreUnwrittenData(void);
/** \brief Called during the write production key state to check if hash is finished **/
extern void PROG_Impl90_Do_CheckHashOfKey(void);
/** \brief Called on when the hash calculation is finished  **/
extern void PROG_Impl90_Entry_WriteKeyFinished(void);
/** \brief Called upon the reception of write key request  **/
extern void PROG_Impl90_Entry_CheckReceivedKey(void);
/** \brief Called upon the reception of read public key hash request  **/
extern void PROG_EntryPublicKeyHash(void);
/** \brief Called during read public key hash phase to check if hash calculation is finished  **/
extern void PROG_DoPublicKeyHash(void);
/** \brief Called on when the hash calculation is finished  **/
extern void PROG_FinishPublicKeyHash(void);
/** \brief Called on transition from Read Public Key hash to Request Download  **/
extern tProgStatus PROG_PBL_RD_Check (void);
/** \brief Called on entry to HASH_CRYPTO_FAILURE state  **/
extern void PROG_FailedPublicKeyHash(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)
/** \brief Called upon the reception of Update switching key routine  **/
extern void PROG_Impl90_Entry_UpdateSwitchingKeys_ValidateHeader(void);
/** \brief Called entry to CHECK_UPDATE_OR_SWITCHING_KEY_HEADERVERIFY state  **/
extern void PROG_Impl90_Entry_Routine_SignatureCheck(void);
/** \brief Called while PROG_EVENT_CRYPTO_FINISH is active, it updates and switches the keys based on request **/
extern void PROG_Impl90_Entry_UpdateSwitchingKey_PerformAction(void);
/** \brief Called entry to PROG_EVENT_UPDATE_SWITCHING_KEYS_FINISHED state  **/
extern void PROG_Impl90_Entry_UpdateSwitchingKeyFinished(void);
/** \brief Called entry to PROG_EVENT_FAILED state  **/
extern void PROG_Impl90_Entry_UpdateSwitchingKeyFailed(void);
#endif

#if ((PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK) || (PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT) || ((PROG_ERASE_ALL == STD_OFF) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID)))
/** \brief Look for block index corresponding to block ID provided in fingerprint
 **
 ** \param[in] uwBlockIdent block identifier
 ** \param[out] pubBlockId index of the matching segment in configuration
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Index found
 ** \retval PROG_E_NOT_OK Index not found
 **
 **/
tProgStatus PROG_FindBlockIndexInTable(u16 uwBlockIdent, u8 * pubBlockId);
#endif /* ((PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK) || (PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT) || ((PROG_ERASE_ALL == STD_OFF) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID))) */

#if (PROG_ENABLE_DOWNGRADE_PROTECTION == STD_ON)
/** \brief Get the start address of the pseudo flash driver block
 **
 ** \return Start Address of the pseudo flash driver
 **
 **/
tProgAddressType PROG_GetPseudoFlashDriverAddress(void);

/** \brief Get the block identifier by using the its index in the configured table
 **
 ** \param[in] ubLogicalBlockIndex index of the block identifier in the Prog plugin
 **
 ** \return Block identifier
 **
 **/
u16 PROG_GetBlockIdByIndex(u8 ubLogicalBlockIndex);

/** \brief Get the block downgrade protection flag by using the its index in the configured table
 **
 ** \param[in] ubLogicalBlockIndex index of the block identifier in the Prog plugin
 **
 ** \return Block downgrade protection flag value
 **
 **/
tProgBoolean PROG_GetBlockDowngradeFlagByIndex(u8 ubLogicalBlockIndex);
#endif /* (PROG_ENABLE_DOWNGRADE_PROTECTION == STD_ON) */

/** \brief Compare the expected and the calculated CRCs
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK Compare OK
 ** \retval PROG_E_BUSY Compare in progress
 ** \retval PROG_E_NOT_OK Compare finished on error
 **
 **/
extern tProgStatus PROG_CRC_Compare(void);

/** \brief API for CRC calculation on all downloaded segments
 **
 **/
extern void PROG_CheckSegmentListCrc(void);



/** \brief Called to do the Coherency Check treatment
 **
 **/
extern void PROG_Do_CoherencyCheck(void);


#if PROG_IMPL_VARIANT == PROG_IMPL_50
/** \brief Called to do the Coherency Pre Check treatment
 **
 **/
extern void PROG_Entry_CoherencyPreCheck(void);
#endif /* #if PROG_IMPL_VARIANT == PROG_IMPL_50 */


/** \brief Check programming request
 **
 ** \return Programming Request Check Status
 **
 **/
extern tProgBoolean PROG_CheckProgrammingRequest(void);



extern void PROG_SwitchApplicationMode(void);


extern tProgBoolean PROG_CheckValidAppl (void);

#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)
/** \brief API for checking the programming counter
 **
 ** \param[in] ubBlockId BlockID
 **
 **/
extern tProgStatus PROG_CheckProgrammingCounter(u8 ubBlockId);
#endif /*#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)*/


#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)
/** \brief API for getting the programming counter lock value (maximum programming counter) for a specific block
 **
 ** \param[in] ubBlockId BlockID
 **
 ** \param[out] puwProgCntMax Programming Counter lock value
 **
 ** \return Operation status
 ** \retval PROG_E_OK Block index has been found
 ** \retval PROG_E_NOT_OK Block index has not been found
 **
 **/
extern tProgStatus PROG_GetProgCntrLockVal(u8 ubBlockId, u16* puwProgCntMax);
#endif /*#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)*/


/** \brief Called on VerifyPartialSoftwareChecksum routine reception
 **
 **/
extern void PROG_Entry_PartialVerificationCrc(void);

/** \brief Called on VerifyPartialSoftwareChecksum routine reception
 **
 **/
extern void PROG_Exit_PartialVerificationCrc(void);


/** \brief This API allow to perform the partial software CRC computation over all programmed segment
 **
 **/
extern void PROG_CheckPartialSegmentListCrc(void);


/** \brief This API allow to perform the partial software CVN check
 **
 **/
#if (PROG_CVN_CHECK == STD_ON)
extern tProgStatus PROG_CheckPartialSwCvnStatus(tProgStatus eProgStatus);
#endif /* PROG_CVN_CHECK == STD_ON */

#if ((PROG_AUTHENTICATED_BOOT_ENABLE == STD_ON) && (PROG_BOOT_VERIFICATION == STD_ON))
/** \brief API for getting the previously computed Bootloader checksum
 **
 ** \param[out] pubComputedChecksum Computed Checksum (if return is PROG_E_OK)
 **
 ** \return Operation status
 ** \retval PROG_E_OK Checksum has been provide
 ** \retval PROG_E_NOT_OK Checksum is invalid and cannot be provided
 **
 **/
extern tProgStatus PROG_GetComputedBootloaderChecksum(u8 * pubComputedChecksum);
#endif


#if ((PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON) || (PROG_DECOMP_FLASH_ROUTINES == STD_ON))
/** \brief Returns the value of m_ubFlashRoutinesPresent, that represents the presence
 **        of the flash routines in RAM
 **
 ** This function is called to verify the presence of the flash routines
 **
 ** \return Result of treatment
 ** \retval PROG_TRUE Flash routines are present in RAM
 ** \retval PROG_FALSE Flash routines are not present in RAM
 **/
extern tProgBoolean PROG_DrvDown_IsFlashRoutinesPresent(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_50)
/** \brief Entry function for Resume verification state  **/
extern void PROG_Entry_ResumeVerification(void);

/** \brief Entry function for Resume verification state  **/
extern void PROG_Entry_Resume_Finish(void);

/** \brief Provide next segment to verify
 **
 ** This function is called after verification of a segment to get
 ** information of the next segment
 **
 **/
extern void PROG_ResReprog_CheckSegmentListVerif(void);
#endif

/** \brief Send response in the case of a failure on secure checksum calculation
 **
 ** This function is called at the end of the Check Memory in the case of
 **  a failure on secure checksum calculation
 **
 **/
extern void PROG_Entry_SecureChecksumFailed(void);

#if(PROG_SA_AUTHENTICATION_METHOD == PROG_SA_AUTHENTICATION_0001 )
#if(PROG_SA_SECUREDKEYS_STATUSREAD == STD_ON )
/** \brief Read the Keys status used for Security Unlock
 **
 ** This function is called when the Read DID request is received for
 ** reading the Secured Keys Programming Status
 **
 **/
extern tUdsStatus PROG_ReadKeyProgrammedStatus(PduLengthType *pulLen, u8 *aubUdsData);
#endif
#endif

#if((PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31))

/** \brief Called on Logical Block Hash routine reception
 **
 **/
extern void PROG_Entry_LogicalBlockHash(void);

/** \brief Called to calculate the hash of the logical block requested
 **
 **/
extern tProgStatus PROG_ComputeBlockHash(void);

/** \brief Called after hash calculation success to send a response with the hash
 **
 **/
extern void PROG_LogicalBlockHashFinish(void);
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31))*/

/** \brief Manage HSM related actions
 **
 ** This function is called in the state machine during Check Memory in order to
 **  update the MAC value of a memory block.
 **
 **/
extern void PROG_HsmManage(void);

/** \brief Manage HSM Firmware Update related actions
 **
 ** This function is used to Init Update and Finish the data block handling
 ** during the HSM Firmware update process.
 **
 **/
extern void PROG_HsmFwUpdate(void);

#if ((PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31))
/** \brief HSM related Entry actions
 **
 ** This function is called in the state machine during Check Programming Dependency in order to
 **  start the MAC for a memory block.
 **
 **/
extern void PROG_IMPL30_HSMEntry(void);

/** \brief Signature Handler for Impl30
 **
 ** This function is called in the state machine during Check Programming Dependency in order to
 **  perform the Signature Verification for the Programmed Segment.
 **
 **/
extern void PROG_IMPL30_SignatureHandling(tSignatureHandlingstatus m_setCHSstatus);

#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_30)*/

/** \brief Called on entry of DECRYPT_UPDATE state
 **
 **
 ** This function is called to update the decryption of data
 **
 ** \return void
 **/
extern void PROG_Entry_DecryptionUpdate(void);

/** \brief Called on do of DECRYPT_UPDATE state
 **
 **
 ** This function is called to launch the writing after decryption has finished
 **
 ** \return void
 **/
extern void PROG_Do_DecryptionUpdate(void);

/** \brief Called on entry of DECRYPT_FINISH state
 **
 **
 ** This function is called to finish the decryption
 **
 ** \return void
 **/
extern void PROG_Entry_DecryptionFinish(void);

/** \brief Called on do of DECRYPT_FINISH state
 **
 **
 ** This function is called to finish the decryption
 **
 ** \return void
 **/
extern void PROG_Do_DecryptionFinish(void);

/** \brief Called on do of EVENT_WRITE state
 **
 **
 ** This function is called to finish the writing of remaining decompressed data
 **
 ** \return void
 **/
extern void PROG_Entry_RTEDecompFinish(void);

#if ((PROG_IMPL_VARIANT == PROG_IMPL_3) ||(PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
extern tProgStatus PROG_Guard_SignatureVerificationEnable_check(void);

/** \brief Called receiving a SubmitSignature request after a RTE
 **
 ** \return Result of check
 ** \retval PROG_E_OK SubmitSignature request accepted
 ** \retval PROG_E_NOT_OK SubmitSignature request not accepted
 **
 **/

extern tProgStatus PROG_Guard_CheckValidApplication(void);

/** \brief Called receiving a CheckValidApplication request after a RTE
 **
 ** \return Result of check
 ** \retval PROG_E_OK CheckValidApplication request accepted
 ** \retval PROG_E_NOT_OK CheckValidApplication request not accepted
 **
 **/
/** \brief Send response in the case of a failure on secure checksum calculation/Signature verification
 **
 ** This function is called at when Submit Signature Routine is received and in the event of
 **  a failure on secure checksum calculation or Signature Verification
 **
 **/
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))

extern void PROG_Entry_ValidationFailed(void);

/** \brief Send response upon successful completion of secure checksum calculation/Signature verification
 **
 ** This function is called at when Submit Signature Routine is received and in the event of
 **  a successful operation completion of secure checksum calculation and/or Signature Verification
 **
 **/
extern void PROG_Entry_ValidationFinish(void);

/** \brief Perform Signature verification for the requested RC Submit Signature
 **
 ** This function is called when Submit Signature Routine is received,
 **  for performing Signature Verification
 **
 **/
extern void PROG_Entry_SignatureVerify(void);
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5)) */
/** \brief called on Entry to RC Check Valid Application
 **
 ** This function is called at when Check Valid Application Routine is received for integrity checks, essentials SW parts presence
 **
 **/
extern void PROG_Entry_Validate_Application(void);

/** \brief Perform checks for validating application for the requested RC Check Valid Application
 **
 ** This function is called when Check Valid Application is received,
 **  for performing  compatiblity checks before validating application
 **
 **/
extern void PROG_Do_CheckValidateApplication(void);

/** \brief Perform checks and informs HSM for Valid Bank Durning Check Valid Application
 **
 ** This function is called when Check Valid Application is received,
 **  for performing Anti-Rollback functions after successful completion of Compatibility Checks of Logical Blocks
 **
 **/
extern void PROG_Do_CheckAntiRollback(void);

/** \brief Send response upon successful completion of Valid software check
 **
 ** This function is called when Anti-Rollback is received and in the event of
 **  a successful operation completion of Valid software check
 **
 **/
extern void PROG_CheckValidateApplicationFinish(void);

/** \brief Send response upon failure of CheckValidateApplication
 **
 ** This function is called when Check Valid Application is received and in the event of
 **  a failure operation completion of CheckValidateApplication
 **
 **/
extern void PROG_CheckValidateApplicationFailed(void);

/** \brief Start Application checksum computation
 **
 ** This function is called before sending response to CheckMemory
 ** request  or Submit Signature Request for authenticated block
 ** to perform Application checksum computation
 **
 **/
extern void PROG_SecurityComputeAppChecksum(void);

/** \brief Checks the HSM Firmware Update Process
 **
 ** This function is used to check if the request for HSM Firmware Update
 ** is received.
 **/
extern void PROG_SecurityCheckHsmFwUpdate(void);

/** \brief Resume BLU Download
 **
 ** This function is called in the state machine to restore the state of bootloader saved
 **  before ECU reset in order to resume the BLU download
 **
 **/
extern void PROG_Entry_BLU_Resume(void);


#if (PROG_IMPL_VARIANT == PROG_IMPL_80)

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/** \brief API called on the entry of the Self check state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_SelfCheck_Impl80(void);

/** \brief API called on the entry of the Self check state
 **
 ** \return void
 **
 **/
extern void PROG_Do_SelfCheck_Impl80(void);

/** \brief API called on the entry of the check memory finish state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_CheckMemoryFinish_Impl80(void);

/** \brief API called on the entry of the ACT check state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_ACT_Check_Impl80(void);

/** \brief API called on the do of the ACT check state
 **
 ** \return void
 **
 **/
extern void PROG_ACT_Check_Impl80(void);
#endif /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

/** \brief API called on the TD CRC state
 **
 ** \return void
 **
 **/
extern void PROG_VerificationOnTheFly_Impl80(void);

/** \brief API called on the entry of the write state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_Write_Impl80(void);

/** \brief API called on the do of the write state
 **
 ** \return void
 **
 **/
extern void PROG_Write_Impl80(void);

/** \brief API called on the do of the write check state
 **
 ** \return void
 **
 **/
extern void PROG_WriteCheck_Impl80(void);

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID))
/** \brief API called on the entry of erase state
 **
 ** \return Operation status
 ** \retval PROG_E_OK at least calibration and/or application shall be erased
 ** \retval PROG_E_BYPASS no erase to perform, areas are blank
 **
 **/
extern tProgStatus PROG_EraseFirstCheck_Impl80(void);
#endif /* ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID)) */

#if PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON
/** \brief API called on the entry of the RD state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_RD_Impl80(void);
#endif /* PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/** \brief API called on the entry of the TD state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_TD_Impl80(void);

/** \brief API called in TD state
 **
 ** \return void
 **
 **/
extern void PROG_TD_Impl80(void);
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

#if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON
/** \brief API called on the entry of the RTE state
 **
 ** \return void
 **
 **/
extern void PROG_Entry_RTE_Impl80(void);

/** \brief API called on the do of the RTE state
 **
 ** \return void
 **
 **/
extern void PROG_Do_RTE_Impl80(void);
#endif /* PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON */

/** \brief API called on processing a routine control
 **
 ** It allows to get the current routine status
 **
 ** \return UDS status
 ** \retval UDS_NRC_XXX Negative response code
 ** \retval UDS_ACK no erase to perform, areas are blank
 **
 **/
extern tUdsStatus PROG_GetRequestRoutineResult_Impl80(PduLengthType *puwLen, u8 *aubUdsData);

#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_80) */
#if (PROG_CSMASR43_USED ==STD_ON)
/** \brief Set the preconditions before start of a new Crypto ASR 4.3 job
 **
 ** This function is called in the Prog module before the start of the crypto operation.
 **
 **/
extern Csm_ReturnType PROG_CsmSetPreConditions(const u8 * ubKeyPtr, u8 ubProgCsmJobTabId);

/** \brief Fetches the datasize and the datapointer for the current Crypto ASR 4.3 job
 **
 ** This function is called to fetch the datasize and the datapointer for the current
 ** Crypto ASR 4.3 job update mode operation.
 **
 **/
extern void PROG_SetCryptoDataSizeDataAdr(u8 const * pubData, u32 ulDataSize);

/** \brief Cancels all the Csm jobs before start of a new Crypto ASR 4.3 job
 **
 ** This function is called to cancel all the Csm jobs before the start of a new crypto operation.
 **
 **/
extern Csm_ReturnType PROG_CsmCancelActiveJobs(void);

/** \brief Manages the asynchronous crypto operation
 **
 ** This function is called to manage the asynchronous crypto operation for the Crypto ASR v4.3 stack integration.
 **
 **/
extern void PROG_CsmManage(void);

/** \brief TxConf notification for the Prog-Crypto Interface layer
 **
 ** This function is called to indicate the Txconf of the transmistted message, especially for the notification
 ** of the NRC78 message transmission.
 **
 **/
extern void PROG_TxConfNotification(void);

#endif /* (PROG_CSMASR43_USED == STD_ON) */
#if (PROG_CRY_PRESENT == STD_ON)
/** \brief Evaluates the Csm status returned to the Prog module
 **
 ** This function is called to cancel all the Csm jobs before the start of a new crypto operation.
 **
 **/
extern void PROG_CsmCheckResult(Csm_ReturnType eCsmStatus);
#endif /*(PROG_CRY_PRESENT == STD_ON)*/

#if ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
extern tProgStatus PROG_ERASE_Check (void);
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
extern tProgStatus PROG_SA2_RD_Check (void);
#endif

#if (PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)
u8 PROG_GetMultBufProcesingValue(void);
u8 PROG_GetMultBufResPendingValue(void);
#endif

#if((PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
/** \brief Manage CMAC Generation for unsigned blocks
 **
 ** This function is called in the state machine during Check Valid Application
 **  to trigger generation of MAC value of unsigned memory blocks.
 **
 **/
extern void PROG_UnsignedMacGenerate(void);
#endif

#if((PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
extern void PROG_ReadLengthOfVDS(u8 ubSignBlkId, u32* pulLength);
#endif

/** \brief Called receiving an Erase request after compare key in SBL.
 **
 ** \return Result of check
 ** \retval PROG_E_OK Erase request accepted
 ** \retval PROG_E_NOT_OK Erase request not accepted
 **
 **/
extern tProgStatus PROG_SBL_Erase_Guard(void);

/** \brief Called receiving an RD request during the SBL SYNC state.
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_Guard_RD_HSMFwUpdate(void);

/** \brief Called receiving an RD request during the SBL SYNC state for PBL and SBL.
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_SBL_RD_Check(void);
/*                                                                               */
/*-------------------------------------------------------------------------------*/

#endif      /* PROG_PUB_H */
