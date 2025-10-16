/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BlPduR layer                                    */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Priv.h                   */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2016 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
#ifndef BLPDUR_PRIV_H
#define BLPDUR_PRIV_H

/*==================[macros]================================================*/


#if (defined BLPDUR_ENTER_CRITICAL_SECTION)      /* To prevent double declaration */
#error BLPDUR_ENTER_CRITICAL_SECTION already defined!
#endif /* #if (defined BLPDUR_ENTER_CRITICAL_SECTION) */

/** \brief Enter critical section */
#define BLPDUR_ENTER_CRITICAL_SECTION() SchM_Enter_BLPDUR_SCHM_BLPDUR_EXCLUSIVE_AREA_0()

#if (defined BLPDUR_EXIT_CRITICAL_SECTION)      /* To prevent double declaration */
#error BLPDUR_EXIT_CRITICAL_SECTION already defined!
#endif /* #if (defined BLPDUR_EXIT_CRITICAL_SECTION) */

/** \brief Exit critical section */
#define BLPDUR_EXIT_CRITICAL_SECTION() SchM_Exit_BLPDUR_SCHM_BLPDUR_EXCLUSIVE_AREA_0()

/*==================[type definitions]======================================*/


/*==================[external constants]====================================*/


/*==================[external data]=========================================*/

extern tBufferInfoType m_stTxBufferInfo;
extern u8* m_pubTxBuffer;
extern tBufferConfigType* m_pstRxCurrentBufferConfig;
extern u8 m_ubCurrentConnection;
#if (BLPDUR_USE_PROG == STD_ON)
#ifdef PROG_RESPOND_TO_PROG_SESSION
#if (PROG_RESPOND_TO_PROG_SESSION == STD_ON)
extern tSimRxReqStateType m_eSimRxReqState;
#endif
#endif
#endif

/*==================[external function declarations]========================*/

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
extern tBlPduRStatus BlPduR_LinTpTxMessage(u16 uwlen, u8* pubData);
extern void BlPduR_Lin_Init(void);
#endif

extern void BlPduR_TxConf(PduIdType uTxPduId, tBlPduRStatus eBlPduRStatus);
extern void BlPduR_RxInd(PduIdType RxPduId, tBlPduRStatus eBlPduRStatus);

/* buffer management functions */
extern tBufferConfigType* BlPduR_GetFreeBufCfg(PduLengthType TpSduLength);
extern tBufferConfigType* BlPduR_GetRxInProgressBuf(PduIdType RxPduId);
extern tBufferConfigType* BlPduR_GetNxtProcBuf(void);
extern tBufferConfigType* BlPduR_GetNxtQueuedRxBuf(void);
extern tBufferConfigType* BlPduR_GetNxtQueuedTxBuf(void);
uint32 BlPduR_GetRxCnt(void);
void BlPduR_IncrementRxCnt(void);
void BlPduR_ReleaseBuffers(tBufferInfoType* pBufferInfo);
void BlPduR_Buf_Init(void);
boolean BlPduR_CheckEndMkr(tBufferConfigType* curBufCfg );
u8 BlPduR_LastBuf(void);
/* connection treament functions */
void BlPduR_TpRxMsgManage (void);
void BlPduR_InitConnection (void);
extern tBlPduRStatus BlPduR_GetTreatmentStatus (void);

#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
void BlPduR_ConvertRxFuncPduId(PduIdType * pubRxPduId);
#endif


StatusType BlPduR_VerifyTesterFilter(PduIdType RxPduId); /* RQD_BLPDUR_PRIV_031 */

u8 GetConnNumByTxPdu(PduIdType TxPduId);

u8 BlpduR_GetConnNumByTxPdu(PduIdType TxPduId);

extern u8 m_ubGroupIdVal;
extern u8 m_ubCurrentRxId;
#endif      /* BLPDUR_PUB_H */
