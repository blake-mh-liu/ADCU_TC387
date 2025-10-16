/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater layer                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Pub.h                 */
/*%%  |                             |  %%  \brief BLUpdater layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.9.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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

#ifndef BLUPDATER_PUB_H
#define BLUPDATER_PUB_H

#include "EB_Prj.h"
#include <ComStack_Types.h>
#include "BLUpdater_Cfg.h"

#if(ETH_PROTOCOL_SUPPORT == STD_ON)
extern u8 m_ubroutineActivationComIndication;
#endif
/** \brief API that executes all different activities of BLUpdater
 **
 ** This API is called for calling all actions of erase, write and compare for BLUpdater,
 ** trigger different operations in flash and provides the current status of flash
 **/
extern void BLU_Start(void);
/** \brief API that allows to initialize all parameters before calling any other functions
 **
 ** This API is used to initialize all parameters for Bootloader Updater
 **/
extern void BLU_Init(void);
/** \brief API that allows to achieve internal cyclic feature
 **
 ** This API is used to schedule internal cyclic feature
 **/
extern void BLU_Manage(void);
/** \brief API that will be used for transmission confirmation of message frame
 **
 ** \param[in] TxPduId Identification of the transmitted I-PDU.
 **
 **/
extern void BLUpdater_PduRIfTxConfirmation(PduIdType TxPduId);
/** \brief API that will be used for reception indication of message frame
 **
 ** \param[in] RxPduId Identification of the received I-PDU.
 ** \param[in] PduInfoPtr Pointer to the buffer (SduDataPtr) and its length (SduLength) containing the data to be copied by PDU Router module
 **/
extern void BLUpdater_PduRIfRxIndication(PduIdType RxPduId, PduInfoType * PduInfoPtr);

extern BufReq_ReturnType BLUpdater_PduRTpCopyTxData(PduIdType TxPduId, PduInfoType *PduInfoPtr, RetryInfoType *RetryInfoPtr,PduLengthType *AvailableDataPtr);

extern void BLUpdater_PduRTpTxConfirmation( PduIdType TxPduId,  NotifResultType  Result);

extern void BLUpdater_PduRTpCopyRxData( PduIdType RxPduId,
	                             P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
	                             P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA)  BufferSizePtr );

extern void BLUpdater_PduRTpStartOfReception(PduIdType  RxPduId, PduLengthType  TpSduLength, PduLengthType  *BufferSizePtr );

extern void BLUpdater_PduRTpRxIndication(PduIdType RxPduId, NotifResultType Result);

#endif
