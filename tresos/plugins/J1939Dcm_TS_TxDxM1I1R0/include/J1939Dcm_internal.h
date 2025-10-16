/* *--------{ EB Automotive C Source File }-------- */
#ifndef  J1939DCM_INTERNAL_H
#define  J1939DCM_INTERNAL_H

/*==================[includes]===============================================*/
/* Include section */
#include <J1939Dcm_Cfg.h>
#include <J1939Dcm_Trace.h>

/* include J1939DCM internal types */
#include <J1939Dcm_internal_types.h>

/* include services headers */
#if( J1939DCM_REPORTDTCS_AVAILABLE == STD_ON)
#include <J1939Dcm_ReportDTC.h>
#endif /* J1939DCM_REPORTDTCS_AVAILABLE */

#if( J1939DCM_DM03_11_AVAILABLE == STD_ON)
#include <J1939Dcm_DM03_11.h>
#endif /* J1939DCM_DM03_11_AVAILABLE */

#if( J1939DCM_DM04_25_AVAILABLE == STD_ON)
#include <J1939Dcm_DM04_25.h>
#endif /* J1939DCM_DM04_25_AVAILABLE */

#if( J1939DCM_DM05_AVAILABLE == STD_ON)
#include <J1939Dcm_DM05.h>
#endif /* J1939DCM_DM05_AVAILABLE */

#if( J1939DCM_DM19_AVAILABLE == STD_ON)
#include <J1939Dcm_DM19.h>
#endif /* J1939DCM_DM19_AVAILABLE */

#if( J1939DCM_DM20_AVAILABLE == STD_ON)
#include <J1939Dcm_DM20.h>
#endif /* J1939DCM_DM20_AVAILABLE */

#if( J1939DCM_DM21_AVAILABLE == STD_ON)
#include <J1939Dcm_DM21.h>
#endif /* J1939DCM_DM21_AVAILABLE */

#if( J1939DCM_DM26_AVAILABLE == STD_ON)
#include <J1939Dcm_DM26.h>
#endif /* J1939DCM_DM26_AVAILABLE */

#if( J1939DCM_DM29_AVAILABLE == STD_ON)
#include <J1939Dcm_DM29.h>
#endif /* J1939DCM_DM29_AVAILABLE */

#if( J1939DCM_DM13_AVAILABLE == STD_ON)
#include <J1939Dcm_DM13.h>
#endif /* J1939DCM_DM13_AVAILABLE */

/*==================[macros]=================================================*/
/*Identifies the ISO 9141 communications port.*/
#define J1939DCM_ISO9141                  ((uint8)0x00)
/*Identifies the J1587 communication port.*/
#define J1939DCM_J1587                    ((uint8)0x01)
/*Identifies the J1850 communication port.*/
#define J1939DCM_J1850                    ((uint8)0x02)
/*Identifies the J1922 communication port.*/
#define J1939DCM_J1922                    ((uint8)0x03)
/*Identifies the J1939 Network #1, Primary Vehicle Network communication port.*/
#define J1939DCM_J1939_NETWORK_1          ((uint8)0x04)
/*Identifies the J1939 Network #2 communication port.*/
#define J1939DCM_J1939_NETWORK_2          ((uint8)0x05)
/*Identifies the J1939 Network #3 communication port.*/
#define J1939DCM_J1939_NETWORK_3          ((uint8)0x06)
/*Identifies the J1939 Network #4 communication port.*/
#define J1939DCM_J1939_NETWORK_4          ((uint8)0x07)
/*Identifies the "Other, Manufacture Specified Port" communication port.*/
#define J1939DCM_OTHER                    ((uint8)0x08)
/*Identifies the Proprietary Network #1 communication port.*/
#define J1939DCM_PROPRIETARY_NETWORK_1    ((uint8)0x09)
/*Identifies the Proprietary Network #2 communication port.*/
#define J1939DCM_PROPRIETARY_NETWORK_2    ((uint8)0x0A)

/* J1939DCM DM-13 Hold Signal Status */
#define J1939_DM13_HOLDSIGNAL_NOT_AVAILABLE         0xF0u
#define J1939_DM13_HOLDSIGNAL_ALL_DEVICE            0x00u
#define J1939_DM13_HOLDSIGNAL_MODIFIED_DEVICES      0x10u

/* J1939DCM DM-13 Start Stop Status */
#define J1939DCM_DM13_STOP_BROADCAST                0x00u
#define J1939DCM_DM13_START_BROADCAST               0x01u
#define J1939DCM_DM13_RESERVED                      0x02u
#define J1939DCM_DM13_DONT_CARE                     0x03u

/* J1939DCM DM-13 Maximum Channels Supported*/
#define J1939DCM_DM13_MAX_CHANNEL                   16u
#define J1939DCM_PDU_DATA_SIZE                      8u

/* J1939DCM DM-13 Broadcast Mode */
#define J1939DCM_DM13_NORMAL_MODE                   0x00u
#define J1939DCM_DM13_SETUP_MODE                    0x01u
#define J1939DCM_DM13_HOLD_MODE                     0x02u

/* J1939DCM DM-13 Timer Status */
#define J1939DCM_DM13_TIMER_CLEAR                   0x00u
#define J1939DCM_DM13_TIMER_SET                     0x01u

/* Default value of Normal Broadcast Mask */
#define J1939DCM_DM13_RESET_NORMAL_BROADCAST_MODE   0xFFFFu

#define J1939DCM_CLEAR                              0x00u
#define J1939DCM_SET                                0x01u

/* Indicates diffrent DTC SPN conversion methods */
#define J1939DCM_DTC_CM_01    (0x01)
#define J1939DCM_DTC_CM_02    (0x02)
#define J1939DCM_DTC_CM_03    (0x03)
#define J1939DCM_DTC_CM_04    (0x04)

/* used internally to verify that the new state is in the valid range and also to check if current state is online or not */
#define J1939DCM_CHECKSTATE         ((J1939Dcm_StateType)0x02U)

/* Indicates the initial call to the operation */
#define J1939DCM_INITIAL        ((J1939Dcm_OpStatusType)0x00)
/* Indicates that a pending return has been done on the previous call of the operation */
#define J1939DCM_PENDING        ((J1939Dcm_OpStatusType)0x78)

/* transmission mode types */
/* shows that a transport protocol is used for transmission */
#define J1939DCM_TX_PDU_ID_TP_TRANSMIT  ((uint8)0x80)
/* shows that a interface is used for transmission */
#define J1939DCM_TX_PDU_ID_IF_TRANSMIT  ((uint8)0x00)

#define J1939DCM_COMMON_BUFFER_LOCKED       ((uint8)0x01)

#define J1939DCM_CYCLIC_BUFFER_LOCKED       ((uint8)0x10)

/* macro used to reset the DM1 information: */
/*          - DM1 processing active */
/*          - Processing done pending Tx */
#define J1939DCM_RESET_DM1_REQUEST_INFO     ((uint8)0x2F)
/* macro used to reset the DMx information: */
/*          - DMx buffer locked */
/*          - DMx request present */
/*          - DMx processing active */
/*          - Processing done pending Tx */
#define J1939DCM_RESET_COMMON_REQUEST_INFO      ((uint8)0x78)

/* TxPduId states */
/* BIT0: if set transmission is on IF */
/* BIT1: if set transmission is on TP */
/* BIT2: if set a response to a DMx request is being sent */
/* BIT3: if set a response to a DM1 request is being sent */
/* shows that no activity is present on this TX_PDU_ID */
#define J1939DCM_TX_PDU_ID_IDLE     ((uint8)0x00)
/* shows that a DMx message is sent via IF */
#define J1939DCM_TX_IF_DMX_ACTIVE   ((uint8)0x05)
/* shows that a DMx message is sent via TP */
#define J1939DCM_TX_TP_DMX_ACTIVE   ((uint8)0x06)
/* shows that a DM1 message is sent via IF */
#define J1939DCM_TX_IF_DM1_ACTIVE   ((uint8)0x09)
/* shows that a DM1 message is sent via TP */
#define J1939DCM_TX_TP_DM1_ACTIVE   ((uint8)0x0A)

/* marks a IF transmission */
#define J1939DCM_TX_IF      ((uint8)0x01)
/* marks a TP transmission */
#define J1939DCM_TX_TP      ((uint8)0x02)
/* marks a DMX transmission */
#define J1939DCM_TX_DMX     ((uint8)0x04)
/* marks a DM1 transmission */
#define J1939DCM_TX_DM1     ((uint8)0x08)
/* marks a DMX transmission IF */
#define  J1939DCM_TX_IF_DMX   ( ((uint8)J1939DCM_TX_IF) | ((uint8)J1939DCM_TX_DMX) )

#define J1939DCM_INIT_NOK       ((uint8)0)
#define J1939DCM_INIT_OK        ((uint8)1)

/* RxPduId states */
/* shows that no activity is present on this RX_PDU_ID */
#define J1939DCM_RX_PDU_ID_IDLE         ((uint8)0)
#define J1939DCM_RX_PDU_ID_BLOCKED_COMMON   ((uint8)2)


/* following line is to suppress warnings about function like macro */
/* this is intended and there is no risk for this */
/* ANALYSIS_REPORT_START_JUSTIFICATION (2014/07/30 : uidt8101) !-->  TOOL_NUMBER(PCLint:961) MISRA(M19.7) Here function like macros are used to increase readability and to ease the development <--! */
/* Exported Variables */
/*============================================================================*/

/* used from MainFunction to obtain the pointer to the DM processing function  */
#define J1939DCM_DM_FUNCTION()              J1939Dcm_ConfiguredDMs[J1939Dcm_MsgContext.DMIdx].DMFunctionPtr

/* used from transmitInternal to obtain the index of the TxPduId for the current DM */
#define J1939DCM_TXPDUID_IDX()              ( J1939Dcm_ConfiguredDMs[J1939Dcm_MsgContext.DMIdx].TxInfo & (uint8)0x7F )

/* used from transmitInternal to obtain the TxPduRefId for the current DM */
#define J1939DCM_TXPDUID_REF(i,TxRefIdValue)    do{ \
                                                    if((J1939Dcm_TxPduIds[(uint8)J1939DCM_TXPDUID_IDX()].J1939DcmTxPduId) == \
                                                        (J1939Dcm_ConfigPtr->J1939DcmTxPduRef[i].J1939DcmTxId)) \
                                                        { \
                                                            TxRefIdValue = J1939Dcm_ConfigPtr->J1939DcmTxPduRef[i].J1939DcmTxRefId; \
                                                            break; \
                                                        } \
                                                    else{ \
                                                        i++;} \
                                                } \
                                                while(i<J1939DCM_NB_OF_CONFIGURED_DMS);

/* used from J1939Dcm_ValidateMetadata to obtain the RxPduRefId for the Received DM */
#define J1939DCM_RXPDUID_REF(i,RxPduId,RxRefIdValue)    do{ \
                                                            if((RxPduId) == (J1939Dcm_ConfigPtr->J1939DcmRxPduRef[i].J1939DcmRxId)) \
                                                            { \
                                                                RxRefIdValue = J1939Dcm_ConfigPtr->J1939DcmRxPduRef[i].J1939DcmRxRefId; \
                                                                break; \
                                                            } \
                                                            else {  \
                                                                i++;} \
                                                        } \
                                                        while(i<J1939DCM_RX_SIZE);

/*RealChannel index is the return value for this macro, it is passed with 0 and stores the real channel index in the J1939Dcm_ComMChannels */
/*from the list of J1939DcmConfiguredChannels generated by XgeN*/
#define J1939DCM_GET_REAL_CHANNEL_INDEX(RealChIdx,ChIndex)    do{ \
                                                            if(J1939Dcm_ComMChannels[RealChIdx] == J1939Dcm_ConfigPtr->J1939DcmConfiguredChannels[ChIndex]) \
                                                            { \
                                                                break; \
                                                            } \
                                                            else {  \
                                                                RealChIdx++;} \
                                                        } \
                                                        while(RealChIdx<J1939DCM_NB_OF_GENERIC_COMMCHANNELS);

/* used from transmitInternal to obtain the type of transmission for the current DM */
#define J1939DCM_CHECK_DM_TRANSMISSION_MODE_IS_TP() ( ( J1939Dcm_ConfiguredDMs[J1939Dcm_MsgContext.DMIdx].TxInfo & (uint8)0x80 ) != (uint8)0 )

/* used from transmitInternal to obtain the index of the ComMChannel for the current DM */
#define J1939DCM_COMMCHANNEL_IDX()          J1939Dcm_ConfigPtr->J1939DcmTxPduRef[J1939Dcm_MsgContext.DMIdx].J1939DcmChannelIdx

#define J1939DCM_DM_PGN()               J1939Dcm_ConfiguredDMs[J1939Dcm_MsgContext.DMIdx].PGN

#define J1939DCM_COMMCHANEL_SYMBOLICNAME()      J1939Dcm_ComMChannels[ J1939DCM_COMMCHANNEL_IDX() ]

#define J1939DCM_SPECIAL_INFO()             J1939Dcm_ConfiguredDMs[J1939Dcm_MsgContext.DMIdx].SpecialInfo

/* ---------------------- Begin Macros for general request state ---------------------- */


/* J1939Dcm_GeneralStatus is used as a bit field that holds the general status of J1939Dcm */
/* and it contains following informations: */
/* BIT0 : shows if the common buffer is locked */
/* BIT1 : shows if a DMx(different than DM1) request is present */
/* BIT2 : shows if DMx request processing is active */
/* BIT3 : not used for now */
/* BIT4 : shows if the DM1 dedicated buffer is locked */
/* BIT5 : shows if a DM1 request processing is present  */
/* BIT6 : shows if DM1 request processing is active */
/* BIT7 : shows that request is processed but transmission is needed */

/* this macro is used to unlock the common buffer */
#define J1939DCM_RESET_COMMON_BUFFER_LOCKED()       ( J1939Dcm_GeneralStatus &= (uint8)0xFE )

/* this macro is used to set DMx request present */
#define J1939DCM_SET_DMX_REQUEST_PRESENT()      ( J1939Dcm_GeneralStatus |= (uint8)0x02 )

/* this macro is used to check if DMx request is present */
#define J1939DCM_CHECK_DMX_REQUEST_PRESENT()        ( ( J1939Dcm_GeneralStatus & (uint8)0x02 ) != (uint8)0x00 )

/* this macro is used to reset information that DMx request is present */
#define J1939DCM_RESET_DMX_REQUEST_PRESENT()        ( J1939Dcm_GeneralStatus &= (uint8)0xFD )

/* this macro is used to check if a DMx request is currently processing */
#define J1939DCM_CHECK_DMX_REQUEST_PROCESSING_ACTIVE()  ( ( J1939Dcm_GeneralStatus & (uint8)0x04 ) != (uint8)0x00 )

/* this macro is used to set information that a DMx request is currently processing */
#define J1939DCM_SET_DMX_REQUEST_PROCESSING_ACTIVE()    ( J1939Dcm_GeneralStatus |= (uint8)0x04 )

/* this macro is used to check if the DM1 buffer is unlocked */
#define J1939DCM_CHECK_DM1_BUFFER_UNLOCKED()        ( ( J1939Dcm_GeneralStatus & (uint8)0x10 ) == (uint8)0x00 )

/* this macro is used to set info that DM1 buffer is locked */
#define J1939DCM_SET_DM1_BUFFER_LOCKED()         ( J1939Dcm_GeneralStatus |= (uint8)0x10 )

/* this macro is used to unlock the DM1 buffer */
#define J1939DCM_RESET_DM1_BUFFER_LOCKED()      ( J1939Dcm_GeneralStatus &= (uint8)0xEF )

/* this macro is used to set DM1 request is present */
#define J1939DCM_SET_DM1_REQUEST_PRESENT()      ( J1939Dcm_GeneralStatus |= (uint8)0x20 )

/* this macro is used to check if DM1 request is present */
#define J1939DCM_CHECK_DM1_REQUEST_PRESENT()        ( ( J1939Dcm_GeneralStatus & (uint8)0x20 ) != (uint8)0x00 )

/* this macro is used to reset information that DMx request is present */
#define J1939DCM_RESET_DM1_REQUEST_PRESENT()        ( J1939Dcm_GeneralStatus &= (uint8)0xDF )

/* this macro is used to check if a DM1 request is currently processing */
#define J1939DCM_CHECK_DM1_REQUEST_PROCESSING_ACTIVE()  ( ( J1939Dcm_GeneralStatus & (uint8)0x40 ) != (uint8)0x00 )

/* this macro is used to set information that a DM1 request is currently processing */
#define J1939DCM_SET_DM1_REQUEST_PROCESSING_ACTIVE()    ( J1939Dcm_GeneralStatus |= (uint8)0x40 )

/* this macro is used to check if the common buffer is unlocked */
#define J1939DCM_CHECK_COMMON_BUFFER_UNLOCKED()     ( ( J1939Dcm_GeneralStatus & (uint8)0x01 ) == (uint8)0x00 )

/* this macro is used to lock the common or DM1 buffer */
#define J1939DCM_SET_COMMON_BUFFER_LOCKED()         ( J1939Dcm_GeneralStatus |= (uint8)0x01 )

/* this macro is used to set DMx request is present */
#define J1939DCM_SET_REQUEST_PRESENT( a )       ( J1939Dcm_GeneralStatus |= (uint8)a )

/* this macro is used for reseting DM information */
#define J1939DCM_RESET_DM_INFO( a )         ( J1939Dcm_GeneralStatus &= (uint8)a )

/* this macro is used to check if a DM(DM1 or DMx) is currently being processed */
#define J1939DCM_CHECK_DM_REQUEST_PROCESSING_ACTIVE()      ( ( J1939Dcm_GeneralStatus & (uint8)0x44 ) != (uint8)0x00 )

/* this macro is used to check if DM processing is over but a transmission is still needed */
#define J1939DCM_CHECK_DM_PROCESSING_DONE_TX_NEEDED()   ( ( J1939Dcm_GeneralStatus & (uint8)0x80 ) != (uint8)0x00 )

/* this macro is used to check if DM processing is over but a transmission is still needed */
#define J1939DCM_SET_DM_PROCESSING_DONE_TX_NEEDED() ( J1939Dcm_GeneralStatus |= (uint8)0x80 )

/* this macro is set info that DM processing is over but a transmission is still needed */
#define J1939DCM_RESET_DM_PROCESSING_DONE_TX_NEEDED()   ( J1939Dcm_GeneralStatus &= (uint8)0x7F )
/* ---------------------- End Macros for general request state ------------------------ */

/* the line bellow is added to restore lint warnings after this line for PCLINT 960 function like macro */
/* ANALYSIS_REPORT_END_JUSTIFICATION */

#define J1939Dcm_get_uint8_from_uint32(a, b)  (uint8)((uint32)0x000000FF & (uint32) ((uint32)(a) >> (uint8)(b))) 

/*==================[external data]==========================================*/
#define J1939DCM_START_SEC_VAR_CLEARED_8
#include <J1939Dcm_MemMap.h>

/* Variable that holds J1939Dcm general status, shows if a DM is active */
extern VAR(uint8, J1939DCM_VAR) J1939Dcm_GeneralStatus;

#if(J1939DCM_DM01_AVAILABLE == STD_ON)
extern VAR(uint8, J1939DCM_VAR) J1939Dcm_DM1Buffer[J1939DCM_DM01_BUFFER_SIZE];

extern VAR(uint8, J1939DCM_VAR) J1939Dcm_NbOfDTCTrigeredByDEM;
#endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */

#if( J1939DCM_MSG_LENGTH_8_BITS == STD_ON)
extern VAR(J1939Dcm_MsgLenType, J1939DCM_VAR) J1939Dcm_CurPosInTxBuff;
#endif /* ( J1939DCM_MSG_LENGTH_8_BITS == STD_ON) */

extern VAR(uint8, J1939DCM_VAR) J1939Dcm_CommonBuffer[J1939DCM_COMMON_BUFFER_SIZE];

#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
extern VAR(uint8, J1939DCM_VAR) J1939Dcm_TimeoutMonitorFlag;
#endif /*( J1939DCM_IF_TX_AVAILABLE == STD_ON )*/

extern VAR(uint8, J1939DCM_VAR) J1939Dcm_ChannelsState[J1939DCM_NB_OF_GENERIC_COMMCHANNELS];

extern VAR(NetworkHandleType, J1939DCM_VAR) J1939Dcm_ComMChannels[J1939DCM_NB_OF_GENERIC_COMMCHANNELS] ;
#define J1939DCM_STOP_SEC_VAR_CLEARED_8
#include <J1939Dcm_MemMap.h>

#define J1939DCM_START_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

#if( J1939DCM_MSG_LENGTH_16_BITS ==STD_ON)
extern VAR(J1939Dcm_MsgLenType, J1939DCM_VAR) J1939Dcm_CurPosInTxBuff;
#endif /* ( J1939DCM_MSG_LENGTH_16_BITS ==STD_ON) */

#if(J1939DCM_DM01_AVAILABLE == STD_ON)
extern VAR(uint16, J1939DCM_VAR) J1939Dcm_CyclesTillNextDM1Transmit;
#endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */

#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
extern VAR(uint16, J1939DCM_VAR) J1939Dcm_TimeoutCycles;
#endif /*( J1939DCM_IF_TX_AVAILABLE == STD_ON ) */

#if(J1939DCM_DM13_AVAILABLE == STD_ON)
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00129,1 */
/* Holds the BroadcastStatusMask information to be reported to BSWM Module*/
extern VAR(uint16, J1939DCM_VAR) J1939Dcm_DM13_BroadcastStatusMask;
#endif

#if(J1939DCM_DM04_25_AVAILABLE == STD_ON)
/* Variable that holds the number of processed Freeze frames per DM04/DM25 request. */
extern VAR(uint16, J1939DCM_VAR) J1939Dcm_NbOfProcessedFFPerRequest;
#endif /* (J1939DCM_DM04_25_AVAILABLE == STD_ON) */

#define J1939DCM_STOP_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

#define J1939DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Dcm_MemMap.h>

#if(J1939DCM_DM13_AVAILABLE == STD_ON)
/* Holds the J1939Dcm DM-13 status information*/
extern VAR(J1939Dcm_DM13_StatusInfoType, J1939DCM_VAR) J1939Dcm_DM13_StatusInfo;
#endif
/* message context used by J1939Dcm */
extern VAR(J1939Dcm_MsgContextType, J1939DCM_VAR) J1939Dcm_MsgContext;

/*Post Build Configuration pointer*/
extern P2CONST(J1939Dcm_ConfigType, J1939DCM_VAR, J1939DCM_APPL_CONST)
  J1939Dcm_ConfigPtr;

#define J1939DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Dcm_MemMap.h>

#define J1939DCM_START_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

/*==================[external function declarations]========================*/
extern FUNC(void, J1939DCM_CODE) J1939Dcm_Memcpy(   P2VAR(uint8, AUTOMATIC, J1939DCM_VAR) lp_Dst,
                            P2CONST(uint8, AUTOMATIC, AUTOMATIC) lp_Src,
                            VAR(uint32, AUTOMATIC) luw_Nb );

#define  J1939DCM_STOP_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

#endif  /* Notice: the file ends with a blank new line to avoid compiler warnings */
