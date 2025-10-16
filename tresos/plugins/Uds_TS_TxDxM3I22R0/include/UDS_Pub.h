#ifndef UDS_PUB_H
#define UDS_PUB_H

/*===============================================================================*/
/*                                                                               */
/*                                 CAN Layers                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                 UDS layer                                     */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Pub.h                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.22.0 BL3 */
/*%%  |   &       &    &            |  %%  Variant: ISO                  */
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

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Constants                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */

/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
#if (UDS_SRV_CFG1_MAX !=0)
/** \brief structure for Diagnostic services configuration 1, stored in ROM **/
extern const tUdsSrvCfg1 m_astDiagSrvCfg1[UDS_SRV_CFG1_MAX];
#endif
#if (UDS_SRV_CFG2_MAX !=0)
/** \brief structure for Diagnostic services configuration 2, stored in ROM **/
extern const tUdsSrvCfg2 m_astDiagSrvCfg2[UDS_SRV_CFG2_MAX];
#endif
#if (UDS_SRV_CFG3_MAX !=0)
/** \brief structure for Diagnostic services configuration 3, stored in ROM **/
extern const tUdsSrvCfg3 m_astDiagSrvCfg3[UDS_SRV_CFG3_MAX];
#endif
#if (UDS_SRV_CFG5_MAX !=0)
/** \brief structure for Diagnostic services configuration 5, stored in ROM **/
extern const tUdsSrvCfg5 m_astDiagSrvCfg5[UDS_SRV_CFG5_MAX];
#endif

#ifdef NCS_UNITARY_TEST
/** \brief Current session code **/
extern tUdsSessionProtType m_eSessionCode;
/** \brief Current session mask **/
extern tUdsSessionProtMask m_eSessionMask;
#endif

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/** \brief Initialize layer
 **
 ** This function initializes UDS layer, shall be called only once at ECU startup.
 ** Current sesssion is set to DEFAULT session.
 ** Sesssion timeout is deactivated.
 **
 **/
extern void UDS_Init (void);


/** \brief Treatment of diagnostic request
 **
 ** This function performs the processing of a received diagnostic request.
 ** It automatically handles the TesterPresent service as well as the status request
 ** of routine control request (RC).
 ** In the case of a configured service, the function calls the corresponding callback
 ** m_astDiagServiceCfg1[].pfuRxRequestInd, m_astDiagServiceCfg2[].pfuRxRequestInd,
 ** m_astDiagServiceCfg3[].pfuRxRequestInd or m_astDiagServiceCfg5[].pfuRxRequestInd
 ** In the case of a service not configured, the function automatically sends
 ** a negative appropriated response.
 **
 **
 ** \param[in,out] pulLen pointer on data length (request)
 ** \param[in,out] aubUdsData pointer on data (request)
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE  pulLen and/or aubUdsData are NULL pointers
 ** \retval UDS_TRUE  when pulLen is different that zero
 **
 **/
extern tUdsBoolean UDS_RxRequest (PduLengthType *pulLen, u8 *aubUdsData, PduLengthType ulUdsDataSize);


/** \brief Treatment of diagnostic request with addressing mode
 **
 ** This function performs the processing of a received diagnostic request with addressing mode.
 ** It automatically handles the TesterPresent service as well as the status request
 ** of routine control request (RC).
 ** In the case of a configured service, the function calls the corresponding callback
 ** m_astDiagServiceCfg1[].pfuRxRequestInd, m_astDiagServiceCfg2[].pfuRxRequestInd,
 ** m_astDiagServiceCfg3[].pfuRxRequestInd or m_astDiagServiceCfg5[].pfuRxRequestInd
 ** In the case of a service not configured with physical addressing mode,
 ** the function automatically sends a negative appropriated response.
 ** In the case of a service not configured with functional addressing mode,
 ** a negative answer is transmitted in specific cases only.
 ** Addressing mode comply to 14229-1:2005(E) specification.
 ** The diagnostic type is also evaluated to reject some services not defined in OBD diagnostic.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** \param[in] eUdsAddrMode addressing mode (request) (UDS_ADDR_PHYSICAL, UDS_ADDR_FUNCTIONAL)
 ** \param[in] eUdsAddrType diagnostic type (request) (UDS_TYPE_DIAG, UDS_TYPE_OBD, UDS_TYPE_DIAG_OBD)
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE  pulLen and/or aubUdsData are NULL pointers
 ** \retval UDS_TRUE  when pulLen is different that zero
 **
 **/
extern tUdsBoolean UDS_RxRequestWithAddrMode (PduLengthType *pulLen, u8 *aubUdsData, PduLengthType ulUdsDataSize, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);


/** \brief Reload session timer
 **
 ** This function checks the state of the current session (standard or other).
 ** If the current session is non standard (diagnostic or programming session for example),
 ** the timer T_Stop_Diag is reloaded with its maximum value: m_uUdsSessTimeout.
 ** It allows the ECU to maintain the current session for a duration equal to T_Stop_Diag (5 s).
 ** This functionality can be used for the NRC78 periodic answers, if the request treatment needs more than T_Stop_Diag to be completed.
 **
 **/
extern void UDS_ReloadTStopDiag (void);

/** \brief Stop session timer
 **
 ** This function allows to deactivate the T_Stop_Diag timer.
 **
 **/
extern void UDS_StopSessionTimer (void);


/** \brief Response pending completion: final response received from the application
 **
 ** This API shall be called in order to provide an answer after an long processing request.
 ** This suppose that a callback (configured on a service) has generated a NRC 78 answer.
 **
 ** The complete data buffer must have been updated by the application starting from index0.
 ** The 3 first data bytes have been written with "7F <service> 78" on first NACK_78 response.
 **
 ** \param[in] ulLen data length
 ** \param[in] aubUdsData pointer on response data
 ** \param[in] eStatus Diagnostic response status (UDS_ACK for positive response, UDS_NRC_xxx for negative response)
 **
 **/
extern void UDS_LongRequestEnd (PduLengthType ulLen, u8 *aubUdsData, tUdsStatus eStatus);


/** \brief Response pending treatment: transmission acknowledgement for intermediate NRC_78 or final response
 **
 ** This API is useful for response pending management.
 ** It shall be called on transmission acknowledgement for intermediate NRC_78 message.
 ** The aim is to ensure that the transport protocol layer is not already treating NRC_78 message,
 ** when the final response is given by the application.
 ** If a NRC_78 message is under transmission, the final response transmission is delayed until TxConf notification.
 **
 **/
extern void UDS_LongRequestRespTxConf(void);

/** \brief Response pending treatment: transmission acknowledgement for intermediate NRC_78 or final response
 **
 ** This API is useful for response pending management.
 ** It shall be called on Receive indication of received tester present to check if last processed request was response pending.
 ** The aim is to ensure that S3 timer is not reloaded when a functional tester present is received after a response pending,
 **
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE  NRC_78 response is not previously sent
 ** \retval UDS_TRUE  NRC_78 response was previously sent
 **/
extern tUdsStatus UDS_IsPending(void);


#if (UDS_SRV_CFG5_MAX !=0)
/** \brief Test if the current service is OBD type
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE Current service is not OBD type
 ** \retval UDS_TRUE  Current service is OBD type
 **
 **/
extern tUdsBoolean UDS_IsOBDService(void);
#endif


#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
/** \brief Response pending management: Stop NRC78 timer.
 **
 ** API used internally in bootloader to stop NRC78 timer
 ** while FLASH erasing treatment (code execution from RAM).
 **
 **/
extern void UDS_StopNRC78Timer(void);
#endif


/** \brief Accessor for the current session
 **
 ** Accessor for the current session.
 **
 ** \return Session type
 ** \retval UDS_SESSION_DEFAULT Default session
 ** \retval UDS_SESSION_PROGRAMMING  Programming session
 ** \retval UDS_SESSION_EXTENDED_DIAG  Extended session
 ** \retval UDS_SESSION_SUPPLIER  Supplier session
 ** \retval UDS_SESSION_OTHER_0x  Other session (01/02/03/04)
 **
 **/
extern tUdsSessionType UDS_GetCurrentSession(void);


/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/** \brief Regular tick of the layer
 **
 ** Ensure cyclic tasks of the layer: response pending, it ensures cyclic NRC_78 message transmissions
 ** and final response transmission.
 **
 **/
extern void UDS_ResponsePending_Manage (void);

/** \brief Regular tick of the layer
 **
 ** Ensure cyclic tasks of the layer: it manages the session counter and throws timeout notification.
 ** If session timeout occurs, the layer automatically switches to the default diagnostic session.
 **
 **/
extern void UDS_Manage (void);

/*                                                                               */

/** \brief Response Pending Manage from ISR of STM Timer
 **
 ** External NRC_78 (response pending) timeout increment, allowing increment under interrupt using
 ** hardware timer.
 ** This API is called from ISR of STM timer if TIMER_RESPONSE_PENDING_CHECK is enabled in
 ** UDS configuration
 **/
extern void UDS_ResponsePending_TimCntManage (void);
/*                                                                               */

/** \brief Service 0x29 Support
 **
 ** API used internally in bootloader to send a positive response for service 0x29
 ** while service 0x29 requesting from Tester (code execution from RAM).
 **
 **/
extern tUdsStatus UDS_Service_Authentication(PduLengthType *puwLen, u8 *aubUdsData);
/*===============================================================================*/
#endif      /* UDS_PUB_H */
