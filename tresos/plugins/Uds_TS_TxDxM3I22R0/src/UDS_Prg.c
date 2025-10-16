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
/*%%   _____________________________   %%  \file UDS_Prg.c                       */
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

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * Variable is already has a unique declaration. no functional impact.
 */

/* NOCOV List
 *
 * NOCOV-EMPTYDEFAULT:
 *   defensive code.
 *
 * Reason:
 * Defensive case which shall never happen.
 *
 */
 /* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.31
 * Declare identifiers before using them
 *
 * Reason:
 * This Function is declare in PROG and define in demo module.
 * is used in this file,for conformance test purpose only.
 *
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: UDS                                                           */
#include "EB_Prj.h"
#include <UDS_Trace.h>                        /* Dbg related macros for EB */
#include "UDS_Priv.h"
/*                                                                               */
/*===============================================================================*/


/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */


/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */




/*                                                                               */
/*===============================================================================*/




/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/* Routine control type */
#define UDS_START_ROUTINE           (u8) 0x01U
#define UDS_STOP_ROUTINE            (u8) 0x02U
#define UDS_REQUEST_ROUTINE_RESULT  (u8) 0x03U

#define UDS_SUPPRESS_POS_RESP_MASK  (u8) 0x7FU

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */


/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */



/* Current session code (DSC service parameter) */
tUdsSessionProtType m_eSessionCode;
/* Current session index (DSC service parameter) */
tUdsSessionIndex m_eSessionIdx;



/* Current session mask
   Range : (UDS_SESSION_DEFAULT_MASK, UDS_SESSION_EXTENDED_DIAG,
    UDS_SESSION_PROGRAMMING_MASK) */
tUdsSessionProtMask m_eSessionMask;


/* Sessions time counter, to limit a Diagnostic session to UDS_SESS_TIMEOUT */
tUdsSessionTimeout m_uSessionTimeCnt;
#if (UDS_SRV_CFG2_MAX !=0)
/* Current data identifier */
u16 m_uwDid;
#endif

/* Current routine identifier */
#if (UDS_SRV_CFG3_MAX !=0)
u16 m_uwRi;
#endif

/* Current service index of the Diagnostic services configuration array */

tUdsSrvIdx m_uSrvIdx;

tUdsBoolean m_eSuppresPosRspMsgIndicationBit;

/* Current start service index */
tUdsSrvIdx m_uStartSrvIdx;

/* Current start sub-service index */
tUdsSrvIdx m_uStartSubSrvIdx;

/* addressing mode */
tUdsAddrMode m_eUdsAddrMode;
#if (UDS_SRV_CFG5_MAX !=0)
/* Is there an obd service in treatment */
/* Deviation MISRAC2012-1 */
tUdsBoolean m_eUdsObdService;
#endif

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)

tUdsLongRequestStr m_stLongRequest;
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

#if (UDS_SRV_CFG1_MAX !=0)
/** \brief Filtering of service / subservice and session of config1
 **
 ** This function filters service, subservice, session of config1 array
 ** m_astDiagSrvCfg1.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg1(PduLengthType *pulLen, u8 *aubUdsData);
/** \brief Filtering of service of config1
 **
 ** This function filters service of config1 array
 ** m_astDiagSrvCfg1.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering1(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of subservice of config1
 **
 ** This function filters subservice of config1 array
 ** m_astDiagSrvCfg1.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SubServiceFiltering1(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of service in a session of config1
 **
 ** This function filters service in a session of config1 array
 ** m_astDiagSrvCfg1.
 **
 ** \param[in] pulLen pointer on data length (request)
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SessionFiltering1 (const PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of subservice in a session of config1
 **
 ** This function filters subservice in a session of config1 array
 ** m_astDiagSrvCfg1.
 **
 ** \param[in] pulLen pointer on data length (request)
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SubServiceSessionFiltering1 (const PduLengthType *pulLen, const u8 *aubUdsData);
#endif
#if (UDS_SRV_CFG2_MAX !=0)
/** \brief Filtering of service, DID and session of config2
 **
 ** This function filters service, DID and session of config2 array
 ** m_astDiagSrvCfg2 (RDBI, IODBI, WDBI...).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg2(PduLengthType *pulLen, u8 *aubUdsData);
/** \brief Filtering of service of config2
 **
 ** This function filters service of config2 array
 ** m_astDiagSrvCfg2 (RDBI, IODBI, WDBI...).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering2(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of service in session of config2
 **
 ** This function filters service in session of config2 array
 ** m_astDiagSrvCfg2 (RDBI, IODBI, WDBI...).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SessionFiltering2(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of DID in session of config2
 **
 ** This function filters DID in session of config2 array
 ** m_astDiagSrvCfg2 (RDBI, IODBI, WDBI...).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_DidSessionFiltering2(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of DID of config2
 **
 ** This function filters DID of config2 array
 ** m_astDiagSrvCfg2 (RDBI, IODBI, WDBI...).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_DidFiltering(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Management of RDBI request
 **
 ** This function manages RDBI request (MULTI-DID)
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data (request, answer)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_RdbiManagement(PduLengthType *pulLen, u8 *aubUdsData);
#endif
#if (UDS_SRV_CFG3_MAX !=0)
/** \brief Filtering of service, RI, subservice and session of config3
 **
 ** This function filters service, RI, subservice and session of config3 array
 ** m_astDiagSrvCfg3 (RoutineControl RC).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg3(PduLengthType *pulLen, u8 *aubUdsData);
/** \brief Filtering of service of config3
 **
 ** This function filters service of config3 array
 ** m_astDiagSrvCfg3 (RoutineControl RC).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering3(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of service in session of config3
 **
 ** This function filters service in session of config3 array
 ** m_astDiagSrvCfg3 (RoutineControl RC).
 **
 ** \param[in] pulLen pointer on data length (request)
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SessionFiltering3 (const PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of RI in session of config3
 **
 ** This function filters RI in session of config3 array
 ** m_astDiagSrvCfg3 (RoutineControl RC).
 **
 ** \param[in] pulLen pointer on data length (request)
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_RiSessionFiltering3 (const PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of RI of config3
 **
 ** This function filters RI of config3 array
 ** m_astDiagSrvCfg3 (RoutineControl RC).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_RiFiltering(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Filtering of subservice of config3
 **
 ** This function filters subservice of config3 array
 ** m_astDiagSrvCfg3 (RoutineControl RC).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in] aubUdsData pointer on data (request)
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SubServiceFiltering3(PduLengthType *pulLen, const u8 *aubUdsData);
/** \brief Start of RoutineControl
 **
 ** This function calls configured callback in UDS for StartRoutineControl.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_StartRoutineControl(PduLengthType *pulLen, u8 *aubUdsData);
/** \brief Stop of RoutineControl
 **
 ** This function calls configured callback in UDS for StopRoutineControl.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_StopRoutineControl(PduLengthType *pulLen, u8 *aubUdsData);
/** \brief Get status of RoutineControl
 **
 ** This function calls configured callback in UDS to get status of RoutineControl
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_GetRoutineStatus(PduLengthType *pulLen, u8 *aubUdsData);
#endif
#if (UDS_SRV_CFG5_MAX !=0)
/** \brief Filtering of service of config5
 **
 ** This function filters service of config array
 ** m_astDiagSrvCfg5 (OBD).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering5(PduLengthType *pulLen, u8 *aubUdsData);
/** \brief Filtering of service of config5
 **
 ** This function filters service of config array
 ** m_astDiagSrvCfg5 (OBD).
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg5(PduLengthType *pulLen, u8 *aubUdsData);
#endif

/** \brief Get UDS response in case of negative answer
 **
 ** This function gets UDS data in case negative answer.
 ** For functional addressing, length is null in case of NRC 12 / 11 and 31.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** \param[in] eStatus input NRC
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE  pulLen and/or aubUdsData are NULL pointers
 ** \retval UDS_TRUE  when pulLen is different that zero
 **
 **/
NCS_PRI_FCT tUdsBoolean UDS_NegativeAnswer (PduLengthType *pulLen, u8 *aubUdsData, tUdsStatus eStatus);

/** \brief Get UDS response in case of positive answer
 **
 ** This function gets UDS data in case positive answer.
 ** If SPEC is configured, P2 / P2* values are added to data in response.
 **
 ** \param[in,out] pulLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE  pulLen and/or aubUdsData are NULL pointers
 ** \retval UDS_TRUE  when pulLen is different that zero
 **
 **/
#if (UDS_SPREC == UDS_SPREC_ON)
NCS_PRI_FCT tUdsBoolean UDS_PositiveAnswer (PduLengthType *pulLen, u8 *aubUdsData);
#else
NCS_PRI_FCT tUdsBoolean UDS_PositiveAnswer (const PduLengthType *pulLen, u8 *aubUdsData);
#endif

/** \brief Checks if UDS response shall be really sent depending m_eSuppresPosRspMsgIndicationBit
 **
 ** The function checks bit 8 of the second bytes and set
 ** m_eSuppresPosRspMsgIndicationBit with UDS_TRUE if the bit = 1 otherwise
 ** with UDS_FALSE if the bit = 0
 **
 ** \param[in] pulLen const pointer on data length (request)
 ** \param[in] aubUdsData const pointer on data (request)
 **
 ** \return Result of treatment
 ** \retval UDS_FALSE  pulLen and/or aubUdsData are NULL pointers
 ** \retval UDS_TRUE  when pulLen is different that zero
 **
 **/
NCS_PRI_FCT tUdsBoolean UDS_AnswerOrNot (const PduLengthType *pulLen, const u8 *aubUdsData);

/** \brief Update UDS session variable
 **
 ** The function updates current session and resets session timer to TIMEOUT.
 **
 ** \param[in] eUdsSessionType new session
 **
 ** \return Result of treatment
 ** \retval UDS_ACK status OK
 ** \retval UDS_ERR_COHE session unknown
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_DiagSession (tUdsSessionType eUdsSessionType);

/** \brief Get current session mask
 **
 ** The function gets current session mask
 **
 ** \param[in,out] eSessionMask
 **
 ** \return Result of treatment
 ** \retval UDS_ACK status OK
 ** \retval UDS_ERR_COHE session unknown
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SelectSessionMask(tUdsSessionMask *eSessionMask);

#if (UDS_SECURITY_CHECK == UDS_SECURITY_CHECK_ON)
/** \brief Check Security level
 **
 ** The function allows to check the security level
 **
 ** \param[in] ubCfgNb
 **
 ** \return Result of treatment
 ** \retval UDS_ACK status OK
 ** \retval UDS_NRC_33 security Access Denied
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_SecurityLevelCheck(u8 ubCfgNb);
#endif

#if UDS_FULL_RESPONSEPENDING == STD_ON
/** \brief Request UDS module to transmit message in a response pending context.
 **
 ** This Api request UDS module to transmit a diagnostic response after an asynchronous processing.
 ** It forwards the information to the BlPduR layer that will send the message.
 **
 ** \param[in] ulLen Length of the data to send
 ** \param[in] aubUdsData Pointer to the buffer containing the data to send
 **
 ** \return Result of treatment
 ** \retval UDS_ACK status OK
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_LongRequestResponseInd (PduLengthType ulLen, u8 *aubUdsData);
#endif

#if ( (UDS_SUPPLIERSERVICE_BA == STD_ON) || (UDS_SUPPLIERSERVICE_BB == STD_ON) || \
    (UDS_SUPPLIERSERVICE_BC == STD_ON) || (UDS_SUPPLIERSERVICE_BD == STD_ON) || \
    (UDS_SUPPLIERSERVICE_BE == STD_ON) )
/** \brief Supplier services request management
 **
 ** This function is responsible to dispatch the received supplier service request to the callback.
 **
 ** \param[in,out] pulLen received data length, response length (no response if 0)
 ** \param[in,out] aubUdsData received data pointer, data to transmit
 ** \param[in] eUdsAddrMode Addressing mode information (PHYSICAL 0x01U / FUNCTIONAL 0x02U / PHYSICAL_FUNCTIONAL 0x03U)
 ** \param[in] eUdsAddrType Addressing type information (DIAG 0x00U / OBD 0x01U / DIAG_OBD 0x02U)
 **
 ** \return Result of check
 ** \retval UDS_ACK Supplier request has been received successfully
 ** \retval UDS_NRC_xxx Negative response code.
 ** \retval UDS_ERR_COHE SDF error detected (no response)
 **
 **/
NCS_PRI_FCT tUdsStatus UDS_RxSupplierRequest (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);
#endif

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */


/*----------------------------------{UDS_Init}--------------------------------*/
void UDS_Init (void)
{
    DBG_UDS_INIT_ENTRY();

    /* Implements 000-07-D028-D-80101-1
       At power on, the current session is "Default Diagnostic" */
    m_eSessionCode = UDS_SESSION_PROT_DEFAULT;

    m_eSessionMask = UDS_SESSION_PROT_DEFAULT_MASK;

    /* Per default, default session always configured to index 0.
       This is ensure through the source code generator           */
    m_eSessionIdx = UDS_DEFAULT_SESSION_INDEX;

    /* All the actives sessions are closed, there is no need to check timeout */
    m_uSessionTimeCnt = 0U;

#if (UDS_SRV_CFG5_MAX !=0)
    /* Deactive Obd service flag */
    m_eUdsObdService = UDS_FALSE;
#endif

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
    /* Initialize long request variable */
    m_stLongRequest.m_eState = UDS_LONG_REQ_OFF;
    m_stLongRequest.m_ubCnt = 0U;
    m_stLongRequest.m_paubData = NULL_PTR;
    m_stLongRequest.m_ulLen = 0U;
    m_stLongRequest.m_ubtRespPending = UDS_FALSE;
#endif

    /* Initialize addressing mode */
    m_eUdsAddrMode = UDS_ADDR_PHYSICAL;

    DBG_UDS_INIT_EXIT();
}
/*----------------------------------{end UDS_Init}----------------------------*/


/*----------------------------------{UDS_RxRequest}--------------------------------*/
tUdsBoolean UDS_RxRequest (PduLengthType *pulLen, u8 *aubUdsData, PduLengthType ulUdsDataSize)
{
    tUdsBoolean eUdsBoolean;

    DBG_UDS_RXREQUEST_ENTRY(pulLen,aubUdsData,ulUdsDataSize);
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR) || (ulUdsDataSize < UDS_LEN_NRC) || (*pulLen > ulUdsDataSize))
    {
        /* When the returned length is equal to NULL, or aubUdsData = NULL */
        /* return UDS_FALSE */
        eUdsBoolean = UDS_FALSE;
    }

    else
    {
        /* call generic function with default parameter */
        eUdsBoolean = UDS_RxRequestWithAddrMode (pulLen, aubUdsData, ulUdsDataSize, UDS_ADDR_PHYSICAL, UDS_TYPE_DIAG_OBD);
    }

    DBG_UDS_RXREQUEST_EXIT(eUdsBoolean);

    return eUdsBoolean;

}
/*----------------------------------{end UDS_RxRequest}----------------------------*/


#if ( (UDS_SUPPLIERSERVICE_BA == STD_ON) || (UDS_SUPPLIERSERVICE_BB == STD_ON) || \
    (UDS_SUPPLIERSERVICE_BC == STD_ON) || (UDS_SUPPLIERSERVICE_BD == STD_ON) || \
    (UDS_SUPPLIERSERVICE_BE == STD_ON) )
/*----------------------------------{UDS_RxSupplierRequest}--------------------------------*/
tUdsStatus UDS_RxSupplierRequest (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    tUdsStatus eUdsStatus;

    switch (aubUdsData[0])
    {
#if (UDS_SUPPLIERSERVICE_BA == STD_ON)
        case UDS_SRV_BA:
            eUdsStatus = UDS_CustomSupplier_BA (pulLen, aubUdsData, eUdsAddrMode, eUdsAddrType);
            break;
#endif

#if (UDS_SUPPLIERSERVICE_BB == STD_ON)
        case UDS_SRV_BB:
            eUdsStatus = UDS_CustomSupplier_BB (pulLen, aubUdsData, eUdsAddrMode, eUdsAddrType);
            break;
#endif

#if (UDS_SUPPLIERSERVICE_BC == STD_ON)
        case UDS_SRV_BC:
            eUdsStatus = UDS_CustomSupplier_BC (pulLen, aubUdsData, eUdsAddrMode, eUdsAddrType);
            break;
#endif

#if (UDS_SUPPLIERSERVICE_BD == STD_ON)
        case UDS_SRV_BD:
            eUdsStatus = UDS_CustomSupplier_BD (pulLen, aubUdsData, eUdsAddrMode, eUdsAddrType);
            break;
#endif

#if (UDS_SUPPLIERSERVICE_BE == STD_ON)
        case UDS_SRV_BE:
            eUdsStatus = UDS_CustomSupplier_BE (pulLen, aubUdsData, eUdsAddrMode, eUdsAddrType);
            break;
#endif

        default:
            eUdsStatus = UDS_NRC_11;
            break;
    }

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
    /* Long request */
    if (UDS_NRC_78 == eUdsStatus)
    {
        m_stLongRequest.m_aubDiagNack78Data[0] = UDS_NRC;
        m_stLongRequest.m_aubDiagNack78Data[1] = aubUdsData[0];
        m_stLongRequest.m_aubDiagNack78Data[2] = eUdsStatus;

        /* Set timer to send the NRC78 */
        m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2Val) - UDS_P2_ADJUST;

        m_stLongRequest.m_eState = UDS_LONG_REQ_ON;

        /* Nothing to answer because NRC78 answer will be sent later */
        *pulLen = 0U;
    }
#endif

    return eUdsStatus;
}
/*----------------------------------{end UDS_RxSupplierRequest}----------------------------*/
#endif

/*----------------------------------{UDS_RxRequestWithAddrMode}--------------------------------*/
tUdsBoolean UDS_RxRequestWithAddrMode (PduLengthType *pulLen, u8 *aubUdsData, PduLengthType ulUdsDataSize, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    tUdsBoolean eUdsBoolean;

    DBG_UDS_RXREQUESTWITHADDRMODE_ENTRY(pulLen,aubUdsData,ulUdsDataSize,eUdsAddrMode,eUdsAddrType);

    m_eSuppresPosRspMsgIndicationBit = UDS_FALSE;
    m_eUdsAddrMode = eUdsAddrMode; /* set mode to physical or functional */

#if (UDS_SRV_CFG5_MAX !=0)
    m_eUdsObdService = UDS_FALSE; /* Set the OBD service flag to false */
#endif

    /* Implements 000-07-D028-D-80602-1 */
    /* If the received request is empty, no answer (it is ignored) */
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR) || (ulUdsDataSize < UDS_LEN_NRC) || (*pulLen > ulUdsDataSize))
    {
        /* When the returned length is equal to NULL, or aubUdsData = NULL */
        /* return UDS_FALSE */
        eUdsBoolean = UDS_FALSE;
    }

    /* If the received request is not empty, treatment */
    else
    {

        /* UDS status of the different fonction */
        tUdsStatus eUdsStatus;

        eUdsBoolean = UDS_TRUE;

        m_uSrvIdx = 0U;
        m_uStartSrvIdx = 0U;
        m_uStartSubSrvIdx = 0U;

        switch(m_eSessionCode)
        {
            case UDS_SESSION_PROT_DEFAULT :
            case UDS_SESSION_PROT_OTHER_01:
            case UDS_SESSION_PROT_OTHER_02:
            case UDS_SESSION_PROT_OTHER_03:
            case UDS_SESSION_PROT_OTHER_04:
            case UDS_SESSION_PROT_PROGRAMMING :
            case UDS_SESSION_PROT_EXTENDED_DIAG :
            case UDS_SESSION_PROT_SUPPLIER :
                /* Nothing to do */
                break;

            default :
                /* Indicate of range error */
                m_eSessionCode = UDS_SESSION_PROT_DEFAULT;
                NCS_SdfVariableRangeError (SDF_UDS_SESSION_CODE);
                eUdsBoolean = UDS_FALSE;
                break;
        }
        /* CHECK: NOPARSE */
        /* NOCOV-DEFENSIVE */
        if(eUdsBoolean == UDS_TRUE)
        /* CHECK: PARSE */
        {
            /* Check if it is necessary to send the positive answer */
            switch (aubUdsData[0])
            {
                case UDS_SRV_DSC:
                case UDS_SRV_ER:
                case UDS_SRV_SA:
                case UDS_SRV_TP:
                case UDS_SRV_CDTCS:
                case UDS_SRV_LC:
                case UDS_SRV_RC:
                case UDS_SRV_CC:
                case UDS_SRV_RDTCI:
                case UDS_SRV_ARS:
                    eUdsBoolean = UDS_AnswerOrNot(pulLen,aubUdsData);
                    break;

                default:
                    /* Nothing to do */
                    break;
            }
        }
        else
        {
            /* Nothing do do */
        }

        if(eUdsBoolean == UDS_TRUE)
        {
            /* Manage the filtering of the different request */
            /* according the service                         */
            switch (aubUdsData[0])
            {
                case UDS_SRV_DSC:
                case UDS_SRV_ER:
                case UDS_SRV_SA:
                case UDS_SRV_TP:
                case UDS_SRV_CDTCS:
                case UDS_SRV_RMBA:
                case UDS_SRV_WMBA:
                case UDS_SRV_CDTCI:
                case UDS_SRV_RDTCI:
                case UDS_SRV_RD:
                case UDS_SRV_RU:
                case UDS_SRV_TD:
                case UDS_SRV_RTE:
                case UDS_SRV_LC:
                case UDS_SRV_CC:
                case UDS_SRV_ARS:
                    /* For specific PSA requirement:                                                 */
                    /* Initial condition: 2 Physical TP channels configured (DIAG & OBD) in TP layer */
                    /* Usecase: if a service (ex: SA) configured only in Physical mode in UDS layer  */
                    /* is  received, NRC_11 shall be returned                                        */
                    if ((eUdsAddrType == UDS_TYPE_DIAG) || (eUdsAddrType == UDS_TYPE_DIAG_OBD))
                    {
#if (UDS_SRV_CFG1_MAX !=0)
                        eUdsStatus = UDS_FilteringCfg1(pulLen,aubUdsData);
#else
                        eUdsStatus = UDS_NRC_11;
#endif
                    }
                    else
                    {
                        eUdsStatus = UDS_NRC_11;
                    }
                    break;
#if (UDS_SRV_CFG2_MAX !=0)
                case UDS_SRV_RDBI:
                case UDS_SRV_IOCBI:
                case UDS_SRV_WDBI:
                case UDS_SRV_RSDBI:
                    if ((eUdsAddrType == UDS_TYPE_DIAG) || (eUdsAddrType == UDS_TYPE_DIAG_OBD))
                    {
                        eUdsStatus = UDS_FilteringCfg2(pulLen,aubUdsData);
                    }
                    else
                    {
                        eUdsStatus = UDS_NRC_11;
                    }
                    break;
#endif
#if (UDS_SRV_CFG3_MAX !=0)
                case UDS_SRV_RC:
                    if ((eUdsAddrType == UDS_TYPE_DIAG) || (eUdsAddrType == UDS_TYPE_DIAG_OBD))
                    {
                        eUdsStatus = UDS_FilteringCfg3(pulLen,aubUdsData);
                    }
                    else
                    {
                        eUdsStatus = UDS_NRC_11;
                    }
                    break;
#endif
#if (UDS_SRV_CFG5_MAX !=0)
                case UDS_SRV_OBD_SID_00:
                case UDS_SRV_OBD_SID_01:
                case UDS_SRV_OBD_SID_02:
                case UDS_SRV_OBD_SID_03:
                case UDS_SRV_OBD_SID_04:
                case UDS_SRV_OBD_SID_05:
                case UDS_SRV_OBD_SID_06:
                case UDS_SRV_OBD_SID_07:
                case UDS_SRV_OBD_SID_08:
                case UDS_SRV_OBD_SID_09:
                case UDS_SRV_OBD_SID_10:
                case UDS_SRV_OBD_SID_11:
                case UDS_SRV_OBD_SID_12:
                case UDS_SRV_OBD_SID_13:
                case UDS_SRV_OBD_SID_14:
                case UDS_SRV_OBD_SID_15:
                    /* Set the current OBD service to true */
                    m_eUdsObdService = UDS_TRUE;

                    if ((eUdsAddrType == UDS_TYPE_OBD) || (eUdsAddrType == UDS_TYPE_DIAG_OBD))
                    {
                        eUdsStatus = UDS_FilteringCfg5(pulLen,aubUdsData);
                    }
                    else
                    {
                        eUdsStatus = UDS_NRC_11;
                    }
                    break;
#endif

#if ( (UDS_SUPPLIERSERVICE_BA == STD_ON) || (UDS_SUPPLIERSERVICE_BB == STD_ON) || \
    (UDS_SUPPLIERSERVICE_BC == STD_ON) || (UDS_SUPPLIERSERVICE_BD == STD_ON) || \
    (UDS_SUPPLIERSERVICE_BE == STD_ON) )
                case UDS_SRV_BA:
                case UDS_SRV_BB:
                case UDS_SRV_BC:
                case UDS_SRV_BD:
                case UDS_SRV_BE:
                    /* System supplier services */
                    eUdsStatus = UDS_RxSupplierRequest(pulLen, aubUdsData, eUdsAddrMode, eUdsAddrType);
                    break;
#endif

                default:
                    eUdsStatus = UDS_NRC_11;
                    break;
            }

            /* Implements 000-07-D028-D-80603-1 */
            /* Fill the buffer data and length with negative code */
            if(eUdsStatus != UDS_ACK)
            {
                switch(eUdsStatus)
                {
                    /* CHECK: NOPARSE */
                    /* NOCOV-DEFENSIVE */
                    /* If there is SDF error desactive the ECU response */
                    case UDS_ERR_COHE:
                        *pulLen = 0U;
                        break;
                    /* CHECK: PARSE */

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
                    /* OSCUDS-96 : If a response pending is requested by the application */
                    /* set the returned value with UDS_NRC_78 to indicate to the EB layer */
                    /* that the Rx segmentation channel must be locked to avoid interlacing */
                    /* The Rx segmentation channel will be unlocked on final response transmission. */
                    case UDS_NRC_78:
                        /* Extension : set UDS_NRC_78 instead of UDS_FALSE or UDS_TRUE */
                        eUdsBoolean = UDS_NRC_78;
                        *pulLen = 0U;
                        break;
#endif

                    default:
                        if (aubUdsData[0] == UDS_SRV_SA)
                        {
/* Deviation CERTC-1 */
                            PROG_TriggerFailedEvent();
                        }
                        eUdsBoolean = UDS_NegativeAnswer (pulLen, aubUdsData, eUdsStatus);
                        break;

                }
            }
            /* Implements 000-07-D028-D-80604-1 */
            else if(m_eSuppresPosRspMsgIndicationBit == UDS_FALSE)
            {
                /* This is a positive answer, transform the service identifier */
                eUdsBoolean = UDS_PositiveAnswer(pulLen,aubUdsData);
            }
            else
            {
                /* No need to send the positive answer */
                if (UDS_SRV_DSC == aubUdsData[0])
                {
                    if((aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK) != 0x01U)
                    /*reload the session timer in casethe request to change a session is different than default session and SPRMIB is TRUE*/
                    {
                        m_uSessionTimeCnt = (tUdsSessionTimeout) UDS_SESS_TIMEOUT + 1U;
                    }
                    (void)UDS_DiagSession((tUdsSessionType)(aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK));
                }
                *pulLen = 0U;
            }

        }/* End if(eUdsBoolean == UDS_TRUE) */
        else
        {
            /* No need to send the positive answer */
            *pulLen = 0U;
        }
    }

    DBG_UDS_RXREQUESTWITHADDRMODE_EXIT(eUdsBoolean);

    return eUdsBoolean;
}
/*----------------------------------{end UDS_RxRequestWithAddrMode}----------------------------*/


/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

#if (UDS_SRV_CFG1_MAX !=0)
/*----------------------------------{UDS_FilteringCfg1}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg1(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* NRC11 / serviceNotSupported / SNS */
        eUdsStatus = UDS_ServiceFiltering1(pulLen, aubUdsData);

        if(eUdsStatus == UDS_ACK)
        {
            /* NRC7F / serviceNotSupportedInActiveSession / SNSIAS */
            eUdsStatus = UDS_SessionFiltering1(pulLen, aubUdsData);

            if(eUdsStatus == UDS_ACK)
            {
                switch (aubUdsData[0])
                {
                    /* Services with subfunction */
                    case UDS_SRV_DSC:
                    case UDS_SRV_ER:
                    case UDS_SRV_SA:
                    case UDS_SRV_CC:
                    case UDS_SRV_TP:
                    case UDS_SRV_RDTCI:
                    case UDS_SRV_CDTCS:
                    case UDS_SRV_LC:
                    case UDS_SRV_ARS:
                        /* NRC13 (Minimal =  2) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
                        if (*pulLen >= 2U)
                        {
                            /* NRC12 / subFunctionNotSupported / SFNS */
                            eUdsStatus = UDS_SubServiceFiltering1(pulLen, aubUdsData);

                            if(eUdsStatus == UDS_ACK)
                            {
                                /* NRC7E / subFunctionNotSupportedInActiveSession / SFNSIAS */
                                eUdsStatus = UDS_SubServiceSessionFiltering1(pulLen, aubUdsData);
                            }
                            else
                            {
                                /* Nothing to do */
                            }
                        }
                        else
                        {
                            eUdsStatus = UDS_NRC_13;
                        }
                        break;

                    case UDS_SRV_RD:
                        /* NRC13 (Minimal =  5) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
                        if (*pulLen < 5U)
                        {
                            eUdsStatus = UDS_NRC_13;
                        }
                        break;

                    default:
                        /* Nothing to do */
                        break;
                }

                if(eUdsStatus == UDS_ACK)
                {
#if (UDS_SECURITY_CHECK == UDS_SECURITY_CHECK_ON)
                    /* NRC33 / securityAccessDenied / SAD */
                    eUdsStatus = UDS_SecurityLevelCheck(UDS_CFG_1);

                    if(eUdsStatus == UDS_ACK)
#endif

                    {
                        /* NRC13 (Nominal) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
                        if ((*pulLen == m_astDiagSrvCfg1[m_uSrvIdx].ulReqLen) || (m_astDiagSrvCfg1[m_uSrvIdx].ulReqLen == 0U))
                        {

                            /* If configured, indicate the received service */
                            /* and wait for the answer parameters */
                            /* (length and data) */

                            /* Individual callback for each service */
                            if (m_astDiagSrvCfg1[m_uSrvIdx].pfuRxMsgInd != NULL_PTR)
                            {
                                /* Indicate the received service */
                                /* Individual callback for each service */
                                eUdsStatus = m_astDiagSrvCfg1[m_uSrvIdx].pfuRxMsgInd(pulLen, aubUdsData);

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
                                /* Long request */
                                if (UDS_NRC_78 == eUdsStatus)
                                {
                                    m_stLongRequest.m_aubDiagNack78Data[0] = UDS_NRC;
                                    m_stLongRequest.m_aubDiagNack78Data[1] = aubUdsData[0];
                                    m_stLongRequest.m_aubDiagNack78Data[2] = eUdsStatus;

                                    /* Set timer to send the NRC78 */

                                    m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2Val) - UDS_P2_ADJUST;

                                    m_stLongRequest.m_eState = UDS_LONG_REQ_ON;

                                    /* Nothing to answer because NRC78 answer will be sent later */
                                    *pulLen = 0U;
                                }
                                else
                                {
                                    /* Nothing to do */
                                }
#endif
                            }
                        }
                        else
                        {
                            eUdsStatus = UDS_NRC_13;
                        }
                    }
                }
            }
            else
            {
                /* Nothing to do */
            }
        }
        else
        {
            /* Nothing to do */
        }
    }
    return eUdsStatus;
}
/*----------------------------------{end UDS_FilteringCfg1}----------------------------*/


/*----------------------------------{UDS_ServiceFiltering1}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering1(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }

    else
    {
        if(*pulLen != 0U)
        {
            while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG1_MAX))
            {
                /* search for service and mode (func / phy or both) */
                if ((m_astDiagSrvCfg1[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((u8)(m_astDiagSrvCfg1[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode))
                {
                    /* service/mode found */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++;
                }
            }

            if (eFlagFound == UDS_TRUE)
            {
                /* Save the start service index */
                m_uStartSrvIdx = m_uSrvIdx;

                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_11;
            }
        }
        else
        {
            eUdsStatus = UDS_NRC_11;
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_ServiceFiltering1}----------------------------*/


/*----------------------------------{UDS_SubServiceFiltering1}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SubServiceFiltering1(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    u8 ubSubSrv;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* received length must not be checked as it is checked before UDS_SubServiceFiltering1 calling */

        /* start from service found before */
        m_uSrvIdx = m_uStartSrvIdx;

        /* Mask the SuppresPosRspMsgIndicationBit */
        switch (aubUdsData[0])
        {
            case UDS_SRV_DSC:
            case UDS_SRV_ER:
            case UDS_SRV_SA:
            case UDS_SRV_TP:
            case UDS_SRV_CDTCS:
            case UDS_SRV_LC:
            case UDS_SRV_ARS:
            case UDS_SRV_CC:
            case UDS_SRV_RDTCI:
                ubSubSrv = (u8) (aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK);
                break;

            /* CHECK: NOPARSE */
            /* NOCOV-EMPTYDEFAULT */
            default:
                ubSubSrv = aubUdsData[1];
                break;
            /* CHECK: PARSE */
        }

        while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG1_MAX))
        {
            /* search for service and subsrv and mode (func / phy or both) */
            if ((m_astDiagSrvCfg1[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                (((u8)(m_astDiagSrvCfg1[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode) &&
                (m_astDiagSrvCfg1[m_uSrvIdx].ubSubSrvId == ubSubSrv)))
            {
                /* service/subsrv/mode are OK */
                eFlagFound = UDS_TRUE;
            }
            else
            {
                m_uSrvIdx++ ;
            }
        }

        /* If the sub-service has been found return positiv answer else */
        /* return a NCR_12 */
        /* Implements 000-07-D028-D-80901-1                        */
        if (eFlagFound == UDS_TRUE)
        {
            /* Save the start sub-service index */
            m_uStartSubSrvIdx = m_uSrvIdx;

            eUdsStatus = UDS_ACK;
        }
        else
        {
            eUdsStatus = UDS_NRC_12;
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_SubServiceFiltering1}----------------------------*/


/*----------------------------------{UDS_SessionFiltering1}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SessionFiltering1 (const PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;
    tUdsSessionMask eSessionMask;

    eFlagFound = UDS_FALSE;
    eSessionMask = UDS_SESSION_DEFAULT_MASK;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Start from service found previously */
        m_uSrvIdx = m_uStartSrvIdx;

        eUdsStatus = UDS_SelectSessionMask(&eSessionMask);

        if (eUdsStatus == UDS_ACK)
        {
            while ((eFlagFound == UDS_FALSE) && (m_uSrvIdx < UDS_SRV_CFG1_MAX))
            {
                /* Check if the service and session is implemented */
                if ((m_astDiagSrvCfg1[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((m_astDiagSrvCfg1[m_uSrvIdx].eSessionMasks & eSessionMask) != 0U))
                {
                    /* service/session are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }

            }

            if (eFlagFound == UDS_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            /* Service is implemented in the ECU but not in the */
            /* session return a NCR_7F                          */
            /* Implements 000-07-D028-D-81001-1                 */
            else
            {
                eUdsStatus = UDS_NRC_7F;
            }
        }
    }

    return (eUdsStatus);
}
/*----------------------------------{end UDS_SessionFiltering1}----------------------------*/


/*----------------------------------{UDS_SubServiceSessionFiltering1}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SubServiceSessionFiltering1 (const PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;
    u8 ubSubSrv;
    tUdsSessionMask eSessionMask;

    eFlagFound = UDS_FALSE;
    eSessionMask = UDS_SESSION_DEFAULT_MASK;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Mask the SuppresPosRspMsgIndicationBit */
        switch (aubUdsData[0])
        {
            case UDS_SRV_DSC:
            case UDS_SRV_ER:
            case UDS_SRV_SA:
            case UDS_SRV_TP:
            case UDS_SRV_CDTCS:
            case UDS_SRV_LC:
            case UDS_SRV_CC:
            case UDS_SRV_RDTCI:
                ubSubSrv = (u8) (aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK);
                break;

            /* CHECK: NOPARSE */
            /* NOCOV-EMPTYDEFAULT */
            default:
                ubSubSrv = aubUdsData[1];
                break;
            /* CHECK: PARSE */
        }

        /* Reinit search service found */
        m_uSrvIdx = m_uStartSubSrvIdx;

        eUdsStatus = UDS_SelectSessionMask(&eSessionMask);

        if (eUdsStatus == UDS_ACK)
        {
            while ((eFlagFound == UDS_FALSE) && (m_uSrvIdx < UDS_SRV_CFG1_MAX))
            {
                /* Search for service/subservice and session */
                if (((m_astDiagSrvCfg1[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    (m_astDiagSrvCfg1[m_uSrvIdx].ubSubSrvId == ubSubSrv)) &&
                    ((m_astDiagSrvCfg1[m_uSrvIdx].eSessionMasks & eSessionMask) != 0U))
                {
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }

            }

            /* If service/sub-service/session are OK return positiv answer */
            /* Implements 000-07-D028-D-81003-1                            */
            if (eFlagFound == UDS_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            /* Service et Sub-service is implemented in the ECU but not in the */
            /* session return a NCR_7E                                         */
            /* Implements 000-07-D028-D-81002-1                                */
            else
            {
                eUdsStatus = UDS_NRC_7E;
            }
        }
    }

    return (eUdsStatus);
}
/*----------------------------------{end UDS_SubServiceSessionFiltering1}----------------------------*/
#endif /* End #if (UDS_SRV_CFG1_MAX) */

#if (UDS_SRV_CFG2_MAX !=0)
/*----------------------------------{UDS_FilteringCfg2}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg2(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    PduLengthType ulMinLength;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* NRC_11 / serviceNotSupported / SNS */
        eUdsStatus = UDS_ServiceFiltering2(pulLen, aubUdsData);

        if(eUdsStatus == UDS_ACK)
        {
            /* NRC_7F / serviceNotSupportedInActiveSession / SNSIAS */
            eUdsStatus = UDS_SessionFiltering2(pulLen, aubUdsData);

            if(eUdsStatus == UDS_ACK)
            {
                switch (aubUdsData[0])
                {
                    case UDS_SRV_RDBI:
                        eUdsStatus = UDS_RdbiManagement(pulLen,aubUdsData);
                        break;

                    case UDS_SRV_IOCBI:
                    case UDS_SRV_WDBI:
                    case UDS_SRV_RSDBI:
                        if (UDS_SRV_RSDBI == aubUdsData[0])
                        {
                            /* Min length is 3 for RSDBI SI(1) + DID (2) */
                            ulMinLength = 3U;
                        }
                        else
                        {
                            /* Min length is 4 */
                            /* for WDBI SI(1) + DID(2) + DREC(1) */
                            /* for IOCBLI SI(1) + DID(2) + IOCP(1) */
                            ulMinLength = 4U;
                        }

                        if (*pulLen >= ulMinLength)
                        {
                            m_uwDid = (u16) ((u16)((u16)aubUdsData[1] << 8U) + ((u16)aubUdsData[2]));

                            /* NRC_31 / requestOutOfRange / ROOR */
                            eUdsStatus = UDS_DidFiltering(pulLen, aubUdsData);

                            if(eUdsStatus == UDS_ACK)
                            {
                                /* Session Filtering */
                                eUdsStatus = UDS_DidSessionFiltering2(pulLen, aubUdsData);

                                if(eUdsStatus == UDS_ACK)
                                {
                                    if ((*pulLen == m_astDiagSrvCfg2[m_uSrvIdx].ulReqLen) || (m_astDiagSrvCfg2[m_uSrvIdx].ulReqLen == 0U))
                                    {
#if (UDS_SECURITY_CHECK == UDS_SECURITY_CHECK_ON)
                                        /* NRC33 / securityAccessDenied / SAD */
                                        eUdsStatus = UDS_SecurityLevelCheck(UDS_CFG_2);

                                        if(eUdsStatus == UDS_ACK)
#endif
                                        {
                                            /* Individual callback for each service */
                                            if (m_astDiagSrvCfg2[m_uSrvIdx].pfuRxMsgInd != NULL_PTR)
                                            {
                                                /* Indicate the received service
.                                                    Individual callback for each service */
                                                eUdsStatus =
                                                    m_astDiagSrvCfg2[m_uSrvIdx].pfuRxMsgInd
                                                    (pulLen, aubUdsData);

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
                                                /* Long request */
                                                if (UDS_NRC_78 == eUdsStatus)
                                                {
                                                    m_stLongRequest.m_aubDiagNack78Data[0] = UDS_NRC;
                                                    m_stLongRequest.m_aubDiagNack78Data[1] = aubUdsData[0];
                                                    m_stLongRequest.m_aubDiagNack78Data[2] = eUdsStatus;

                                                    /* Set timer to send the NRC78 */
                                                    m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2Val) - UDS_P2_ADJUST;


                                                    m_stLongRequest.m_eState = UDS_LONG_REQ_ON;

                                                    /* Nothing to answer because NRC78 answer will be sent later */
                                                    *pulLen = 0U;
                                                }
#endif

                                                /* Individual callback for each service */
                                            }
                                        }
                                    }
                                    else
                                    {
                                        eUdsStatus = UDS_NRC_13;
                                    }
                                }
                            }
                        }
                        else
                        {
                            eUdsStatus = UDS_NRC_13;
                        }
                        break;

                    /* CHECK: NOPARSE */
                    /* NOCOV-EMPTYDEFAULT*/
                    default:
                        /* Nothing to do */
                        break;
                    /* CHECK: PARSE */
                }
            }
        }
    }
    return eUdsStatus;
}
/*----------------------------------{end UDS_FilteringCfg2}----------------------------*/

/*----------------------------------{UDS_ServiceFiltering2}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering2(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        if(*pulLen != 0U)
        {
            while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG2_MAX))
            {
                /* search for service and mode (func / phy or both) */
                if ((m_astDiagSrvCfg2[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((u8)(m_astDiagSrvCfg2[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode))
                {
                    /* service/mode are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }
            }
            /* If the service has been found return positiv answer else */
            /* return a NCR_11                                          */
            /* Implements 000-07-D028-D-81201-1                         */
            if (eFlagFound == UDS_TRUE)
            {
                /* Save the start service index */
                m_uStartSrvIdx = m_uSrvIdx;

                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_11;
            }
        }
        else
        {
            eUdsStatus = UDS_NRC_11;
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_ServiceFiltering2}----------------------------*/

/*----------------------------------{UDS_SessionFiltering2}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SessionFiltering2 (PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;
    tUdsSessionMask eSessionMask;

    eFlagFound = UDS_FALSE;
    eSessionMask = UDS_SESSION_DEFAULT_MASK;

    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Start for service found */
        m_uSrvIdx = m_uStartSrvIdx;

        eUdsStatus = UDS_SelectSessionMask(&eSessionMask);

        if (eUdsStatus == UDS_ACK)
        {
            while ((eFlagFound == UDS_FALSE) && (m_uSrvIdx < UDS_SRV_CFG2_MAX))
            {
                /* Check if the service and session is implemented */
                if ((m_astDiagSrvCfg2[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((m_astDiagSrvCfg2[m_uSrvIdx].eSessionMasks & eSessionMask) != 0U))
                {
                    /* service/session are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }
            }

            /* If service/session are OK return positive answer */
            if (eFlagFound == UDS_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            /* Service is implemented in the ECU but not in the */
            /* session return a NCR_7F                          */
            else
            {
                eUdsStatus = UDS_NRC_7F;
            }
        }
    }

    return (eUdsStatus);
}
/*----------------------------------{end UDS_SessionFiltering2}----------------------------*/

/*----------------------------------{UDS_DidSessionFiltering2}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_DidSessionFiltering2 (PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;
    tUdsSessionMask eSessionMask;

    eFlagFound = UDS_FALSE;
    eSessionMask = UDS_SESSION_DEFAULT_MASK;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Start for service found */
        m_uSrvIdx = m_uStartSrvIdx;

        eUdsStatus = UDS_SelectSessionMask(&eSessionMask);

        if (eUdsStatus == UDS_ACK)
        {
            while ((eFlagFound == UDS_FALSE) && (m_uSrvIdx < UDS_SRV_CFG2_MAX))
            {
                /* Check if the service and DID and session is implemented */
                if (((m_astDiagSrvCfg2[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    (m_astDiagSrvCfg2[m_uSrvIdx].uwDid == m_uwDid)) &&
                    ((m_astDiagSrvCfg2[m_uSrvIdx].eSessionMasks & eSessionMask) != 0U))
                {
                    /* service/DID/session are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++;
                }
            }

            /* If service/session are OK return positiv answer */
            if (eFlagFound == UDS_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            /* Service + DID is implemented in the ECU but not in the */
            /* session return a UDS_NRC_INVALID_DID                   */
            else
            {
                eUdsStatus = UDS_NRC_INVALID_DID;
            }
        }
    }

    return (eUdsStatus);
}
/*----------------------------------{end UDS_DidSessionFiltering2}----------------------------*/

/*----------------------------------{UDS_DidFiltering}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_DidFiltering(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* received length must not be checked as it is checked before UDS_DidFiltering calling */

        m_uSrvIdx = m_uStartSrvIdx;

        while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG2_MAX))
        {
            /* search for service and did and mode (func / phy or both) */
            if ((m_astDiagSrvCfg2[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                ((m_astDiagSrvCfg2[m_uSrvIdx].uwDid == m_uwDid) &&
                ((u8)(m_astDiagSrvCfg2[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode)))
            {
                /* service/did/mode are OK */
                eFlagFound = UDS_TRUE;
            }
            else
            {
                m_uSrvIdx++ ;
            }
        }

        /* If the DID has been found return positive answer else */
        /* return a NCR_31                                       */
        if (eFlagFound == UDS_TRUE)
        {
            eUdsStatus = UDS_ACK;
        }
        else
        {
            /* Non implemented Did */
            eUdsStatus = UDS_NRC_31;
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_DidFiltering}----------------------------*/

/*----------------------------------{UDS_RdbiManagement}------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_RdbiManagement(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    u8 ubTableCfgIdx[UDS_SRV_CFG_RDBI_MAX] = {0};
    PduLengthType ulLocalRDBILength;
    u32 ulTableCfgLength;
    PduLengthType ulIdx;
    u8 ubLocalDidIdx;
    PduLengthType ulLocalLength;

    eUdsStatus = UDS_ERR_COHE;
    ulLocalLength = 0U;
    ulTableCfgLength = 0U;
    ulIdx = 1U;

    /* NRC13 incorrectMessageLengthOrInvalidFormat / IMLOIF */
    /* Min =  3 (SID + DID) */
    /* modulo 2 */
    /* Max = SID + 2*n(DIDs) */
    if (*pulLen == 3U)
    {
        /* Loop on all the DIDs into the request */
        while ((ulIdx < (*pulLen - 1U)) && (eUdsStatus != UDS_NRC_33))
        {
            /* Retrieve the next DID */
            m_uwDid = (u16)((u16)((u16)aubUdsData[ulIdx] << 8U) + ((u16)aubUdsData[ulIdx+1U]));
            ulIdx += 2U;

            eUdsStatus = UDS_DidFiltering(pulLen, aubUdsData);

            if(eUdsStatus == UDS_ACK)
            {
                eUdsStatus = UDS_DidSessionFiltering2(pulLen, aubUdsData);

                /* Record the service position from the layer configuration */
                /* This service will be treated after the loop. */
                if(eUdsStatus == UDS_ACK)
                {
#if (UDS_SECURITY_CHECK == UDS_SECURITY_CHECK_ON)
                    /* NRC33 / securityAccessDenied / SAD */
                    eUdsStatus = UDS_SecurityLevelCheck(UDS_CFG_2);

                    if(eUdsStatus == UDS_ACK)
#endif
                    {
                        ubTableCfgIdx[ulTableCfgLength] = m_uSrvIdx;
                        ulTableCfgLength++;
                    }
                }
            }
        }

        if(eUdsStatus != UDS_NRC_33)
        {
            /* At least one DID is valid into the request. */
            if (0U != ulTableCfgLength)
            {
                /* Reinit variables */
                eUdsStatus = UDS_ACK;
                ulIdx = 0U;

                /* Loop on each valid DID and build the response (concatenation of all the DID responses). */
                while (((ulIdx < ulTableCfgLength) && (UDS_ACK == eUdsStatus)) && (*pulLen > 0U))
                {
                    ubLocalDidIdx = ubTableCfgIdx[ulIdx];

                    /* To provide in callack the same buffer structure for mono/multi DID, write the SRV before the DID. */
                    /* In case of multi-DID, the overwritten byte will be restored after the callback treatment. */
                    if (m_astDiagSrvCfg2[ubLocalDidIdx].pfuRxMsgInd != NULL_PTR)
                    {
                        /* Save LocalLength (total data in buffer) in pulLen */
                        *pulLen = 3U;

                        /* Individual callback for each service */
                        eUdsStatus =
                            m_astDiagSrvCfg2[ubLocalDidIdx].pfuRxMsgInd(pulLen, &aubUdsData[0]);

                        /* Length = 1 or 2 so SRV (1)+ DID (2) are taken into account -> 3 */
                        if ((*pulLen == 1U) || (*pulLen == 2U))
                        {
                            *pulLen= 3U;
                        }
                    }
                    else
                    {
                        /* no callback means no data -> only SRV (1)+ DID (2) are taken into account -> 3 */
                        *pulLen= 3U;
                    }

                    /* Length = 0 no UDS response expected */
                    if (*pulLen > 0U)
                    {
                        if((ulLocalLength + *pulLen) > UDS_RX_PHYS_BUFFERSIZE)
                        {
                          eUdsStatus = UDS_NRC_14;
                          *pulLen = 3U;
                        }
                        else
                        {
                          for(ulLocalRDBILength = 1U; ulLocalRDBILength < *pulLen; ulLocalRDBILength++)
                          {
                              aubUdsData[ulLocalLength+ulLocalRDBILength] = aubUdsData[ulLocalRDBILength];
                          }

                          /* Update the global response length */
                          ulLocalLength += (*pulLen - 1U);
                          ulIdx++;
                        }
                    }
                }
                /* Length = 0 no UDS response expected */
                if (*pulLen > 0U)
                {
                    /* Set the final length */
                    *pulLen = (ulLocalLength+1U);
                }

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
                /* Long request */
                if (UDS_NRC_78 == eUdsStatus)
                {
                    m_stLongRequest.m_aubDiagNack78Data[0] = UDS_NRC;
                    m_stLongRequest.m_aubDiagNack78Data[1] = aubUdsData[0];
                    m_stLongRequest.m_aubDiagNack78Data[2] = eUdsStatus;

                    /* Set timer to send the NRC78 */
                    m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2Val) - UDS_P2_ADJUST;

                    m_stLongRequest.m_eState = UDS_LONG_REQ_ON;

                    /* Nothing to answer because NRC78 answer will be sent later */
                    *pulLen = 0U;
                }
#endif
            }
            else
            {
                eUdsStatus = UDS_NRC_31;
            }
        }
    }
    else
    {
        eUdsStatus = UDS_NRC_13;
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_RdbiManagement}---------------------------*/
#endif /* End #if (UDS_SRV_CFG2_MAX) */

#if (UDS_SRV_CFG3_MAX !=0)
/*----------------------------------{UDS_FilteringCfg3}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg3(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Implements 000-07-D028-D-81503-1 */
        /* Service Filtering */
        eUdsStatus = UDS_ServiceFiltering3(pulLen, aubUdsData);

        if(eUdsStatus == UDS_ACK)
        {
            /* Session Filtering */
            eUdsStatus = UDS_SessionFiltering3(pulLen, aubUdsData);

            if(eUdsStatus == UDS_ACK)
            {
                /* NRC13 (Minimal =  4) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
                if (*pulLen >= 4U)
                {
                    m_uwRi = (u16)((u16)((u16)aubUdsData[2] << 8U) + ((u16)aubUdsData[3]));

                    /* DID Filtering */
                    eUdsStatus = UDS_RiFiltering(pulLen, aubUdsData);

                    if(eUdsStatus == UDS_ACK)
                    {
                        eUdsStatus = UDS_RiSessionFiltering3(pulLen, aubUdsData);

                        if(eUdsStatus == UDS_ACK)
                        {
#if (UDS_SECURITY_CHECK == UDS_SECURITY_CHECK_ON)
                            /* NRC33 / securityAccessDenied / SAD */
                            eUdsStatus = UDS_SecurityLevelCheck(UDS_CFG_3);

                            if(eUdsStatus == UDS_ACK)
#endif
                            {
                                switch (aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK)
                                {
                                    case UDS_START_ROUTINE:
                                        eUdsStatus = UDS_StartRoutineControl(pulLen, aubUdsData);
                                        break;

                                    case UDS_STOP_ROUTINE:
                                        eUdsStatus = UDS_StopRoutineControl(pulLen, aubUdsData);
                                        break;

                                    case UDS_REQUEST_ROUTINE_RESULT:
                                        eUdsStatus = UDS_GetRoutineStatus(pulLen, aubUdsData);
                                        break;

                                    default:
                                        eUdsStatus = UDS_NRC_12;
                                        break;
                                }

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
                                /* Long request */
                                if (UDS_NRC_78 == eUdsStatus)
                                {
                                    m_stLongRequest.m_aubDiagNack78Data[0] = UDS_NRC;
                                    m_stLongRequest.m_aubDiagNack78Data[1] = aubUdsData[0];
                                    m_stLongRequest.m_aubDiagNack78Data[2] = eUdsStatus;

                                    /* Set timer to send the NRC78 */
                                    m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2Val) - UDS_P2_ADJUST;


                                    m_stLongRequest.m_eState = UDS_LONG_REQ_ON;

                                    /* Nothing to answer because NRC78 answer will be sent later */
                                    *pulLen = 0U;
                                }
#endif
                            }
                        }
                        else
                        {
                            /* Nothing to do */
                        }
                    }
                    else
                    {
                        /* Nothing to do */
                    }
                }
                /* Implements 000-07-D028-D-81501-1 */
                else
                {
                    /* Bad length, Negative answer */
                    eUdsStatus = UDS_NRC_13;
                }
            }
            else
            {
                /* Nothing to do */
            }
        }
        else
        {
            /* Nothing to do */
        }
    }
    return eUdsStatus;
}
/*----------------------------------{end UDS_FilteringCfg3}----------------------------*/


/*----------------------------------{UDS_ServiceFiltering3}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering3(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        if(*pulLen != 0U)
        {
            /* Search the first service equal to aubUdsData[0] into the */
            /* configuration 1 array                                    */
            while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG3_MAX))
            {
                /* search for service and mode (func / phy or both) */
                if ((m_astDiagSrvCfg3[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((u8)(m_astDiagSrvCfg3[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode))
                {
                    /* service/mode are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }
            }
            /* If the service has been found return positiv answer else */
            /* return a NCR_11                                          */
            /* Implements 000-07-D028-D-81601-1                         */
            if (eFlagFound == UDS_TRUE)
            {
                /* Save the start service index */
                m_uStartSrvIdx = m_uSrvIdx;

                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_11;
            }
        }
        else
        {
            eUdsStatus = UDS_NRC_11;
        }
    }
    return eUdsStatus;
}
/*----------------------------------{end UDS_ServiceFiltering3}----------------------------*/


/*----------------------------------{UDS_SubServiceFiltering3}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SubServiceFiltering3(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    u8 ubSubSrv;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {

        /* If length configured is 0, received length must be checked */
        /* here lenth min for service (1) / RI (2) / subservice (1) is 4 */
        if(*pulLen >= 4U)
        {
            m_uSrvIdx = m_uStartSrvIdx;

            /* Mask the SuppresPosRspMsgIndicationBit */
            ubSubSrv = (u8) (aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK);

            while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG3_MAX))
            {
                /* search for service and subservice and RI and mode (func / phy or both) */
                if (((m_astDiagSrvCfg3[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    (m_astDiagSrvCfg3[m_uSrvIdx].ubSubSrvId == ubSubSrv)) &&
                    ((m_astDiagSrvCfg3[m_uSrvIdx].uwRi == m_uwRi) &&
                    ((u8)(m_astDiagSrvCfg3[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode)))
                {
                    /* service/mode found */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++;
                }
            }

            if (eFlagFound == UDS_TRUE)
            {
                /* Save the start sub-service index */
                m_uStartSubSrvIdx = m_uSrvIdx;

                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_12;
            }
        }
        else
        {
            eUdsStatus = UDS_NRC_12;
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_SubServiceFiltering3}----------------------------*/


/*----------------------------------{UDS_SessionFiltering3}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SessionFiltering3 (const PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;
    tUdsSessionMask eSessionMask;

    eFlagFound = UDS_FALSE;
    eSessionMask = UDS_SESSION_DEFAULT_MASK;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        m_uSrvIdx = m_uStartSrvIdx;

        eUdsStatus = UDS_SelectSessionMask(&eSessionMask);

        if (eUdsStatus == UDS_ACK)
        {
            while ((eFlagFound == UDS_FALSE) && (m_uSrvIdx < UDS_SRV_CFG3_MAX))
            {
                /* Check if the service and session is implemented */
                if ((m_astDiagSrvCfg3[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((m_astDiagSrvCfg3[m_uSrvIdx].eSessionMasks & eSessionMask) != 0U))
                {
                    /* service/session are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }
            }

            if (eFlagFound == UDS_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            /* Service is implemented in the ECU but not in the*/
            /* session return a NCR_7F                         */
            /* Implements 000-07-D028-D-81801-1                */
            else
            {
                eUdsStatus = UDS_NRC_7F;
            }
        }
    }

    return (eUdsStatus);
}
/*----------------------------------{end UDS_SessionFiltering3}----------------------------*/


/*----------------------------------{UDS_RiSessionFiltering3}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_RiSessionFiltering3 (const PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;
    tUdsSessionMask eSessionMask;

    eFlagFound = UDS_FALSE;
    eSessionMask = UDS_SESSION_DEFAULT_MASK;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        m_uSrvIdx = m_uStartSrvIdx;

        eUdsStatus = UDS_SelectSessionMask(&eSessionMask);

        if (eUdsStatus == UDS_ACK)
        {
            /* Check if the service and RI and session is implemented */
            while ((eFlagFound == UDS_FALSE) && (m_uSrvIdx < UDS_SRV_CFG3_MAX))
            {
                if (((m_astDiagSrvCfg3[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    (m_astDiagSrvCfg3[m_uSrvIdx].uwRi == m_uwRi)) &&
                    ((m_astDiagSrvCfg3[m_uSrvIdx].eSessionMasks & eSessionMask) != 0U))
                {
                    /* service/RI/session are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }
            }


            /* If service/sub-service/session are OK return positiv answer */
            /* Implements 000-07-D028-D-81003-1                            */
            if (eFlagFound == UDS_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            /* Service et Sub-service is implemented in the ECU but not in the */
            /* session return a NCR_7E                                         */
            /* Implements 000-07-D028-D-81002-1                                */
            else
            {
                eUdsStatus = RC_NRC_IMPLEMENTATION;
            }
        }
    }

    return (eUdsStatus);
}
/*----------------------------------{end UDS_RiSessionFiltering3}----------------------------*/


/*----------------------------------{UDS_RiFiltering}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_RiFiltering(PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* received length must not be checked as it is checked before UDS_RiFiltering calling */

        m_uSrvIdx = m_uStartSrvIdx;

        /* Search the first service / RI */
        while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG3_MAX))
        {
            /* search for service and RI and mode (func / phy or both) */
            if ((m_astDiagSrvCfg3[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                ((m_astDiagSrvCfg3[m_uSrvIdx].uwRi == m_uwRi) &&
                ((u8)(m_astDiagSrvCfg3[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode)))
            {
                /* service/mode found */
                eFlagFound = UDS_TRUE;
            }
            else
            {
                m_uSrvIdx++;
            }
        }

        if(eFlagFound == UDS_TRUE)
        {
            eUdsStatus = UDS_ACK;
        }
        else
        {
            eUdsStatus = UDS_NRC_31;
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_RiFiltering}----------------------------*/


/*----------------------------------{UDS_StartRoutineControl}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_StartRoutineControl(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Sub-service filtering */
        eUdsStatus = UDS_SubServiceFiltering3(pulLen, aubUdsData);

        if (UDS_ACK == eUdsStatus)
        {
            /* NRC13 (Nominal) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
            if ((*pulLen == m_astDiagSrvCfg3[m_uSrvIdx].ulReqLen) ||
                                   (m_astDiagSrvCfg3[m_uSrvIdx].ulReqLen == 0U))
            {
                /* If configured, indicate the received service */
                /* and wait for the answer parameters   */
                /* (length and data)                    */
                /* Implements 000-07-D028-D-82101-1     */
                /* Individual callback for each service */
                if (m_astDiagSrvCfg3[m_uSrvIdx].pfuRxMsgInd != NULL_PTR)
                {
                    /* Indicate the received service        */
                    /* Individual callback for each service */
                    eUdsStatus = m_astDiagSrvCfg3[m_uSrvIdx].pfuRxMsgInd
                                    (pulLen, aubUdsData);
                }
                else
                {
                    /* Nothing to do */
                }
            }
            else
            {
                eUdsStatus = UDS_NRC_13;
            }
        }
        else
        {
            /* Nothing to do */
        }
    }

    return eUdsStatus;

}
/*----------------------------------{end UDS_StartRoutineControl}----------------------------*/


/*----------------------------------{UDS_StopRoutineControl}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_StopRoutineControl(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Sub-service filtering */
        eUdsStatus = UDS_SubServiceFiltering3(pulLen, aubUdsData);

        if (UDS_ACK == eUdsStatus)
        {
            /* NRC13 (Nominal) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
            if ((*pulLen == m_astDiagSrvCfg3[m_uSrvIdx].ulReqLen) ||
                                   (m_astDiagSrvCfg3[m_uSrvIdx].ulReqLen == 0U))
            {
                /* If configured, indicate the received service */
                /* and wait for the answer parameters */
                /* (length and data) */
                /* Implements 000-07-D028-D-82201-1 */
                /* Individual callback for each service */
                if (m_astDiagSrvCfg3[m_uSrvIdx].pfuRxMsgInd != NULL_PTR)
                {
                    /* Indicate the received service */
                    /* Individual callback for each service */
                    eUdsStatus = m_astDiagSrvCfg3[m_uSrvIdx].pfuRxMsgInd
                            (pulLen, aubUdsData);
                }
                else
                {
                    /* Nothing to do */
                }
            }
            else
            {
                eUdsStatus = UDS_NRC_13;
            }
        }
        else
        {
            /* Nothing to do */
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_StopRoutineControl}----------------------------*/


/*----------------------------------{UDS_GetRoutineStatus}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_GetRoutineStatus(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Sub-service filtering */
        eUdsStatus = UDS_SubServiceFiltering3(pulLen, aubUdsData);

        if (UDS_ACK == eUdsStatus)
        {
            /* NRC13 (Nominal) / incorrectMessageLengthOrInvalidFormat / IMLOIF */
            if ((*pulLen == m_astDiagSrvCfg3[m_uSrvIdx].ulReqLen) ||
                                   (m_astDiagSrvCfg3[m_uSrvIdx].ulReqLen == 0U))
            {
                /* If configured, indicate the received service */
                /* and wait for the answer parameters */
                /* (length and data) */
                /* Implements 000-07-D028-D-82201-1 */
                /* Individual callback for each service */
                if (m_astDiagSrvCfg3[m_uSrvIdx].pfuRxMsgInd != NULL_PTR)
                {
                    /* Indicate the received service */
                    /* Individual callback for each service */
                    eUdsStatus = m_astDiagSrvCfg3[m_uSrvIdx].pfuRxMsgInd
                                 (pulLen, aubUdsData);
                }
            }
            else
            {
                eUdsStatus = UDS_NRC_13;
            }
        }
        else
        {
            /* Nothing to do */
        }
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_GetRoutineStatus}----------------------------*/
#endif /* End #if (UDS_SRV_CFG3_MAX) */


#if (UDS_SRV_CFG5_MAX !=0)
/*----------------------------------{UDS_FilteringCfg5}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_FilteringCfg5(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;

    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }

    else
    {
        /* Implements 000-07-D028-D-80703-1 */
        /* Service Filtering */
        eUdsStatus = UDS_ServiceFiltering5(pulLen, aubUdsData);

        if(eUdsStatus == UDS_ACK)
        {
            /* The request length is correct (1) or */
            /* the length must not be checked now (2) */
            /* (it will be checked in the request callback) */
            if ( (*pulLen == m_astDiagSrvCfg5[m_uSrvIdx].ulReqLen) ||
                  (m_astDiagSrvCfg5[m_uSrvIdx].ulReqLen == 0U) )
            {
                /* Individual callback for each service */
                if (m_astDiagSrvCfg5[m_uSrvIdx].pfuRxMsgInd != NULL_PTR)
                {
                    eUdsStatus = m_astDiagSrvCfg5[m_uSrvIdx].pfuRxMsgInd
                                (pulLen, aubUdsData);

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
                    /* Long request */
                    if (UDS_NRC_78 == eUdsStatus)
                    {
                        m_stLongRequest.m_aubDiagNack78Data[0] = UDS_NRC;
                        m_stLongRequest.m_aubDiagNack78Data[1] = aubUdsData[0];
                        m_stLongRequest.m_aubDiagNack78Data[2] = eUdsStatus;

                        /* Set timer to send the NRC78 */
                        m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2Val) - UDS_P2_ADJUST;

                        m_stLongRequest.m_eState = UDS_LONG_REQ_ON;

                        /* Nothing to answer because NRC78 answer will be sent later */
                        *pulLen = 0U;
                    }
#endif
                }
                else
                {
                    /* Nothing to do */
                }
            } /* if ((*pulLen == m_astDiagSrvCfg1[m_uSrvIdx].ulReqLen) || */
            /*       (m_astDiagSrvCfg1[uSrvIdx].ulReqLen == 0))   */

            /* Implements 000-07-D028-D-XXXXX-1 */
            else
            {
                /* Bad length */
                eUdsStatus = UDS_NRC_13;
            }

        } /* End if(eUdsStatus == UDS_ACK) */

        else
        {
            /* Nothing to do */
        }
    }

    return eUdsStatus;

}
/*----------------------------------{end UDS_FilteringCfg5}----------------------------*/


/*----------------------------------{UDS_ServiceFiltering5}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_ServiceFiltering5(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tUdsBoolean eFlagFound;

    eFlagFound = UDS_FALSE;

    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    else
    {
        if(*pulLen != 0U)
        {
            /* Search the first service equal to aubUdsData[0] into the    */
            /* configuration 5 array                                       */
            while ((UDS_FALSE == eFlagFound) && (m_uSrvIdx < UDS_SRV_CFG5_MAX))
            {
                /* search for service and mode (func / phy or both) */
                if ((m_astDiagSrvCfg5[m_uSrvIdx].ubSrvId == aubUdsData[0]) &&
                    ((u8)(m_astDiagSrvCfg5[m_uSrvIdx].ubAddrMode & m_eUdsAddrMode) == m_eUdsAddrMode))
                {
                    /* service/mode are OK */
                    eFlagFound = UDS_TRUE;
                }
                else
                {
                    m_uSrvIdx++ ;
                }
            }
            if (eFlagFound == UDS_TRUE)
            {
                /* Save the start service index */
                m_uStartSrvIdx = m_uSrvIdx;

                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_11;
            }
        }
        else
        {
            eUdsStatus = UDS_NRC_11;
        }
    }
    return eUdsStatus;
}
/*----------------------------------{end UDS_ServiceFiltering5}----------------------------*/
#endif


/*----------------------------------{UDS_NegativeAnswer}--------------------------------*/
NCS_PRI_FCT tUdsBoolean UDS_NegativeAnswer (PduLengthType *pulLen, u8 *aubUdsData, tUdsStatus eStatus)
{
    tUdsBoolean eUdsBoolean;
    eUdsBoolean = UDS_TRUE;

    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsBoolean = UDS_FALSE;
    }
    else
    {
        if (m_eUdsAddrMode == UDS_ADDR_FUNCTIONAL)
        {
            switch(eStatus)
            {
                /* According to ISO 14229-1:2013(E)                                                 */
                /* Following negative response must not be sent if addressing mode is functional    */
                /* RequestOutOfRange */
                case UDS_NRC_31:
                /* ServiceNotSupported */
                case UDS_NRC_11:
                /* SubServiceNotSupported */
                case UDS_NRC_12:
                /* sub-functionNotSupportedInActiveSession */
                case UDS_NRC_7E:
                /* serviceNotSupportedInActiveSession*/
                case UDS_NRC_7F:
                    *pulLen = 0U;
#if (UDS_RELOAD_TSTOPDIAG == UDS_RELOAD_TSTOPDIAG_ON)
                    /* Reload Session timer since no response expected */
                    UDS_ReloadTStopDiag();
#endif
                    break;

                default:
                    /* Implements 000-07-D028-D-80201-1 */
                    /* Negative answer, NCRXX */
                    aubUdsData[2] = eStatus;
                    aubUdsData[1] = aubUdsData[0];
                    aubUdsData[0] = UDS_NRC;
                    *pulLen = UDS_LEN_NRC;
                    break;
            }
        }
        else
        {
            /* Implements 000-07-D028-D-80201-1 */
            /* Negative answer, NCRXX */
            aubUdsData[2] = eStatus;
            aubUdsData[1] = aubUdsData[0];
            aubUdsData[0] = UDS_NRC;
            *pulLen = UDS_LEN_NRC;
        }
    }

    return eUdsBoolean;
}
/*----------------------------------{end UDS_NegativeAnswer}----------------------------*/


/*----------------------------------{UDS_PositiveAnswer}--------------------------------*/
#if (UDS_SPREC == UDS_SPREC_ON)
NCS_PRI_FCT tUdsBoolean UDS_PositiveAnswer (PduLengthType *pulLen, u8 *aubUdsData)
#else
NCS_PRI_FCT tUdsBoolean UDS_PositiveAnswer (const PduLengthType *pulLen, u8 *aubUdsData)
#endif
{
    tUdsBoolean eUdsBoolean;
    eUdsBoolean = UDS_TRUE;

    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsBoolean = UDS_FALSE;
    }
    else
    {
        /* Check if the length is different of 0 */
        if(*pulLen != 0U)
        {
            /* DSCPR management */
            if (UDS_SRV_DSC == aubUdsData[0])
            {
                (void)UDS_DiagSession((tUdsSessionType)(aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK));
#if (UDS_SPREC == UDS_SPREC_ON)
                *pulLen += 4U;
                if( *pulLen == 6U )
                {
                    aubUdsData[2] = (u8) ((u16)((m_stSessionInfo[m_eSessionIdx].uwP2Val)*UDS_MANAGE_PERIOD) >> 8U);
                    aubUdsData[3] = (u8) ((m_stSessionInfo[m_eSessionIdx].uwP2Val)*UDS_MANAGE_PERIOD);
                    aubUdsData[4] = (u8) ((u16)(((m_stSessionInfo[m_eSessionIdx].uwP2StarVal)*UDS_MANAGE_PERIOD)/10U) >> 8U);
                    aubUdsData[5] = (u8) ((((m_stSessionInfo[m_eSessionIdx].uwP2StarVal)*UDS_MANAGE_PERIOD)/10U) & 0xFFU);
                }
                else
                {
                    eUdsBoolean = UDS_FALSE;
                }
#endif
            }


            /* Add 0x40 to the first byte else doesn't the following bytes */
            /* Implements 000-07-D028-D-80301-2                            */
            /* Implements 000-07-D028-D-80302-1                            */
            aubUdsData[0] = (u8) (aubUdsData[0] + UDS_ACK);
#if (UDS_SPREC == UDS_SPREC_ON)
            /* User callout to be called in valid context */
            if( UDS_TRUE == eUdsBoolean )
#endif
            {
                UDS_CustomPositiveAnswerInd(pulLen,aubUdsData);
            }
        }
        else
        {
            eUdsBoolean = UDS_FALSE;
        }
    }
    return eUdsBoolean;
}
/*----------------------------------{end UDS_PositiveAnswer}----------------------------*/


/*----------------------------------{UDS_AnswerOrNot}--------------------------------*/
NCS_PRI_FCT tUdsBoolean UDS_AnswerOrNot (const PduLengthType *pulLen, const u8 *aubUdsData)
{
    tUdsBoolean eUdsBoolean;
#if (UDS_TIMEOUT_CHECK == UDS_TIMEOUT_CHECK_ON)
    tUdsBoolean eBMTimeout;
#endif
    eUdsBoolean = UDS_TRUE;

    if ((pulLen == NULL_PTR) || (aubUdsData == NULL_PTR))
    {
        eUdsBoolean = UDS_FALSE;
    }
    else
    {
#if (UDS_TIMEOUT_CHECK == UDS_TIMEOUT_CHECK_ON)
        eBMTimeout = UDS_CustomIsBMCountTimeout(aubUdsData);
        if(UDS_TRUE == eBMTimeout)
#endif
        {
            /* If the bit 8 of the second byte = 1 set m_eSuppresPosRspMsgIndicationBit */
            /* with UDS_TRUE else  set m_eSuppresPosRspMsgIndicationBit with UDS_FALSE  */
            /* Implements 000-07-D028-D-80401-1                                         */
            if(NCS_TST_BIT_SET (aubUdsData[1], 0x80U, u8))
            {
                m_eSuppresPosRspMsgIndicationBit = UDS_TRUE;
            }
            else
            {
                m_eSuppresPosRspMsgIndicationBit = UDS_FALSE;
            }
        }
#if (UDS_TIMEOUT_CHECK == UDS_TIMEOUT_CHECK_ON)
        else
        {
            eUdsBoolean = UDS_FALSE;
        }
#endif
    }

    return eUdsBoolean;

}
/*----------------------------------{end UDS_AnswerOrNot}----------------------------*/


/*----------------------------------{UDS_DiagSession}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_DiagSession (tUdsSessionType eUdsSessionType)
{
    tUdsStatus eUdsStatus;
    tUdsSessionProtType eUdsSessTypeProt;
    tUdsSessionType eUdsSessOld;
    tUdsSessionProtMask eUdsTmpSessProtMask;
    u8 eUdsSessionLoopIncCnt;
    u8 eUdsTmpSessionIdx;
    eUdsStatus = UDS_ACK;

    /* Translate the input parameter to an internal protected value (SDF)
       If session not found, the default value will be taken              */
    eUdsTmpSessionIdx = UDS_DEFAULT_SESSION_INDEX;
    for(eUdsSessionLoopIncCnt = 0;eUdsSessionLoopIncCnt < UDS_CONFIGURABLE_SESSION_MAX; eUdsSessionLoopIncCnt++)
    {
      if(m_stSessionInfo[eUdsSessionLoopIncCnt].ubSessionValue == eUdsSessionType)
      {
        eUdsTmpSessionIdx = eUdsSessionLoopIncCnt;
      }
      else
      {
        /* Nothing to do */
      }
    }

    eUdsSessTypeProt = m_stSessionInfo[eUdsTmpSessionIdx].ubSessionProtValue;
    eUdsTmpSessProtMask = m_stSessionInfo[eUdsTmpSessionIdx].ubSessionProtMaskValue;

    switch(m_eSessionCode)
    {
        case UDS_SESSION_PROT_DEFAULT :
            /* If there is any opened session,
            this is a session entry */

            /* Save the old session before memorize the new one */
            eUdsSessOld = UDS_GetCurrentSession();

            /* Memorise the asked session code */
            m_eSessionCode = eUdsSessTypeProt;
            /* Store the new session index based on eUdsSessTypeProt */
            m_eSessionIdx = eUdsTmpSessionIdx;

            /* Indicate the session entry */
            UDS_SessionStatusInd (eUdsSessionType, eUdsSessOld, UDS_SESSION_CHANGE_REQUESTED);

            break;

        case UDS_SESSION_PROT_OTHER_01:
        case UDS_SESSION_PROT_OTHER_02:
        case UDS_SESSION_PROT_OTHER_03:
        case UDS_SESSION_PROT_OTHER_04:
        case UDS_SESSION_PROT_PROGRAMMING :
        case UDS_SESSION_PROT_EXTENDED_DIAG :
        case UDS_SESSION_PROT_SUPPLIER :
            /* If a session is open, and the asked session    */
            /* is the standard one, close the current session */
            if(eUdsSessTypeProt == UDS_SESSION_PROT_DEFAULT)
            {
                /* The session timeout is stopped */
                m_uSessionTimeCnt = 1U;
            }
            else
            {
                /* Nothing to do */
            }


            /* Save the old session before memorize the new one */
            eUdsSessOld = UDS_GetCurrentSession();

            /* Memorize the requested session code */
            m_eSessionCode = eUdsSessTypeProt;
            /* Memorize the requested session index */
            m_eSessionIdx = eUdsTmpSessionIdx;

            /* Indicate the session entry */
            UDS_SessionStatusInd (eUdsSessionType, eUdsSessOld, UDS_SESSION_CHANGE_REQUESTED);
            break;

        default :
            /* Indicate of range error */
            m_eSessionCode = UDS_SESSION_PROT_DEFAULT;
            m_eSessionIdx = UDS_DEFAULT_SESSION_INDEX;
            NCS_SdfVariableRangeError (SDF_UDS_SESSION_CODE);
            eUdsStatus = UDS_ERR_COHE;
            break;
    }


    if(eUdsStatus == UDS_ACK)
    {
        /* Initialise the session mask according to the session type */
        /* Initialise the timeout session to UDS_SESS_TIMEOUT for    */
        /* the programming and the extended diag session             */
        /* Implements 000-07-D028-D-80501-1                          */
        /* Implements 000-07-D028-D-80503-1                          */
        m_eSessionMask = eUdsTmpSessProtMask;
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_DiagSession}----------------------------*/


/*----------------------------------{UDS_SelectSessionMask}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SelectSessionMask(tUdsSessionMask *eSessionMask)
{
    tUdsStatus eUdsStatus;

    eUdsStatus = UDS_ACK;

    switch(m_eSessionMask)
    {
        case UDS_SESSION_PROT_OTHER_01_MASK:
            *eSessionMask = UDS_SESSION_OTHER_01_MASK;
            break;
        case UDS_SESSION_PROT_OTHER_02_MASK:
            *eSessionMask = UDS_SESSION_OTHER_02_MASK;
            break;
        case UDS_SESSION_PROT_OTHER_03_MASK:
            *eSessionMask = UDS_SESSION_OTHER_03_MASK;
            break;
        case UDS_SESSION_PROT_OTHER_04_MASK:
            *eSessionMask = UDS_SESSION_OTHER_04_MASK;
            break;
        case UDS_SESSION_PROT_DEFAULT_MASK:
            *eSessionMask = UDS_SESSION_DEFAULT_MASK;
            break;
        case UDS_SESSION_PROT_PROGRAMMING_MASK:
            *eSessionMask = UDS_SESSION_PROGRAMMING_MASK;
            break;
        case UDS_SESSION_PROT_EXTENDED_DIAG_MASK:
            *eSessionMask = UDS_SESSION_EXTENDED_DIAG_MASK;
            break;
        case UDS_SESSION_PROT_SUPPLIER_MASK:
            *eSessionMask = UDS_SESSION_SUPPLIER_MASK;
            break;

        default :
            /* Indicate of range error */
            m_eSessionMask = UDS_SESSION_PROT_DEFAULT_MASK;
            NCS_SdfVariableRangeError (SDF_UDS_SESSION_MASK);
            eUdsStatus = UDS_ERR_COHE;
            break;
    }

    return eUdsStatus;
}
/*----------------------------------{end UDS_SelectSessionMask}----------------------------*/


/*-------------------------------------------------------------------------------*/
/* - Public Callbacks                                                            */


#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
/*----------------------------------{UDS_LongRequestEnd}--------------------------------*/
void UDS_LongRequestEnd (PduLengthType ulLen, u8 *aubUdsData, tUdsStatus eStatus)
{
    DBG_UDS_LONGREQUESTEND_ENTRY(ulLen,aubUdsData,eStatus);

    if ((m_stLongRequest.m_eState == UDS_LONG_REQ_ON) && (aubUdsData != NULL_PTR))
    {
        /* Positive answer */
        if(eStatus==UDS_ACK)
        {
            if ( m_eSuppresPosRspMsgIndicationBit == UDS_TRUE )
            {
                /* The Positive Response shall not be sent */
                if (UDS_SRV_DSC == aubUdsData[0])
                {
                    (void)UDS_DiagSession((tUdsSessionType)(aubUdsData[1] & UDS_SUPPRESS_POS_RESP_MASK));
                }
                ulLen = 0U;
#if (UDS_RELOAD_TSTOPDIAG == UDS_RELOAD_TSTOPDIAG_ON)
                /* Reload Session timer since no response expected */
                UDS_ReloadTStopDiag();
#endif
            }
            else
            {
                /* This is a positive answer, transform the service identifier */
                (void)UDS_PositiveAnswer(&ulLen, aubUdsData);
            }
        }
        else
        {
            (void)UDS_NegativeAnswer (&ulLen, aubUdsData, eStatus);
        }

        /* UDS_Manage will send the response */
        m_stLongRequest.m_paubData = aubUdsData;
        m_stLongRequest.m_ulLen = ulLen;
        m_stLongRequest.m_eState = UDS_LONG_REQ_END;
    }

    DBG_UDS_LONGREQUESTEND_EXIT();
}
/*----------------------------------{end UDS_LongRequestEnd}----------------------------*/
#endif


/*----------------------------------{UDS_Manage}--------------------------------*/
void UDS_Manage (void)
{
    tUdsSessionType eUdsSessOld;

    DBG_UDS_MANAGE_ENTRY();

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON) && (UDS_EXT_RESPONSEPENDING_MANAGE_CALL == STD_OFF)
    /* Manage  response pending */
    UDS_ResponsePending_Manage();
#endif

    switch(m_eSessionCode)
    {
        case UDS_SESSION_PROT_DEFAULT:
            break;
        case UDS_SESSION_PROT_OTHER_01:
        case UDS_SESSION_PROT_OTHER_02:
        case UDS_SESSION_PROT_OTHER_03:
        case UDS_SESSION_PROT_OTHER_04:
        case UDS_SESSION_PROT_PROGRAMMING :
        case UDS_SESSION_PROT_EXTENDED_DIAG :
        case UDS_SESSION_PROT_SUPPLIER :

            /* The session timeout is elapsed, then current session is closed */
            if (m_uSessionTimeCnt != 0U)
            {
                if (m_uSessionTimeCnt == 1U)
                {
                    /* Save the old session before memorize the new one */
                    eUdsSessOld = UDS_GetCurrentSession();
                    m_eSessionCode = UDS_SESSION_PROT_DEFAULT;
                    m_eSessionIdx = UDS_DEFAULT_SESSION_INDEX;
                    m_eSessionMask = UDS_SESSION_PROT_DEFAULT_MASK;

                    /* Indicate the session closing */
                    UDS_SessionStatusInd (m_stSessionInfo[m_eSessionIdx].ubSessionValue, eUdsSessOld, UDS_SESSION_TIMEOUT);
                }
                /* The session timeout is not elapsed, the management */
                else
                {
                    m_uSessionTimeCnt --;
                }
            }
            break;

        default:
            /* Indicate of range error */
            m_eSessionCode = UDS_SESSION_PROT_DEFAULT;
            m_eSessionIdx = UDS_DEFAULT_SESSION_INDEX;
            NCS_SdfVariableRangeError (SDF_UDS_SESSION_CODE);
            break;
    }

    DBG_UDS_MANAGE_EXIT();
}
/*----------------------------------{end UDS_Manage}----------------------------*/
#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
/*------------------------------{UDS_ResponsePending_Manage}--------------------------------------------*/
void UDS_ResponsePending_Manage (void)
{
    tUdsStatus eUdsStatus;

    DBG_UDS_RESPONSEPENDING_MANAGE_ENTRY();

    /* Long request management */
    switch (m_stLongRequest.m_eState)
    {
        case UDS_LONG_REQ_END:
            if (UDS_FALSE == m_stLongRequest.m_ubtRespPending)
            {
                /* Stop the long request management */
                m_stLongRequest.m_eState = UDS_LONG_REQ_OFF;

                /* Send response */
                /* it is the last transmission, it is not required to lock the channel anymore */
                (void)UDS_LongRequestResponseInd (m_stLongRequest.m_ulLen, m_stLongRequest.m_paubData);
            }
            break;

        case  UDS_LONG_REQ_ON:
            #if(TIMER_RESPONSE_PENDING_CHECK == TIMER_RESPONSE_PENDING_CHECK_OFF)
            /* Manage response for long request */
            if (m_stLongRequest.m_ubCnt == 1U)
            {
                /* Notify the application for the P2/P2* expiration */
                UDS_P2AboutToExpireInd();
            }
            #endif
            if (m_stLongRequest.m_ubCnt == 0U)
            {
                /* It's time to send cyclic NRC_78 */
                /* To be done only if the previous response is completed */
                if (UDS_FALSE == m_stLongRequest.m_ubtRespPending)
                {

                    /* The NRC78 answer timer is reloaded */
                    m_stLongRequest.m_ubCnt = (m_stSessionInfo[m_eSessionIdx].uwP2StarVal) - UDS_P2STAR_ADJUST;

                    eUdsStatus = UDS_LongRequestResponseInd (UDS_LEN_NRC, m_stLongRequest.m_aubDiagNack78Data);

                    /* A final response shall be given independent of the suppressPosRspMsgIndicationBit value  */
                    m_eSuppresPosRspMsgIndicationBit = UDS_FALSE;

                    /* If the transmission is started, lock the NRC_78 channel until acknowledge reception */
                    if (UDS_ACK == eUdsStatus)
                    {
                        m_stLongRequest.m_ubtRespPending = UDS_TRUE;
                    }

                }
            }
            /* The session timeout is not elapsed, the management */
            else
            {
            #if(TIMER_RESPONSE_PENDING_CHECK == TIMER_RESPONSE_PENDING_CHECK_OFF)
                m_stLongRequest.m_ubCnt --;
            #endif
            }
            break;

        default:
            /* No long request */
            /* Nothing to do */
            break;
    }

    DBG_UDS_RESPONSEPENDING_MANAGE_EXIT();
}
#endif
/*--------------------------{end UDS_ResponsePending_Manage}----------------------------*/
/*--------------------------{UDS_ResponsePending_TimCntManage}----------------------------------*/
#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
void UDS_ResponsePending_TimCntManage(void)
{
#if(TIMER_RESPONSE_PENDING_CHECK == TIMER_RESPONSE_PENDING_CHECK_ON)
    /* Manage response for long request */
    if (m_stLongRequest.m_ubCnt == 1U)
    {
        UDS_P2AboutToExpireInd();
    }
    if(m_stLongRequest.m_eState == UDS_LONG_REQ_ON)
    {
        if(m_stLongRequest.m_ubCnt > 0U)
        {
          m_stLongRequest.m_ubCnt--;
        }
    }
#endif
}
#endif
/*--------------------------{end UDS_ResponsePending_TimCntManage}----------------------------------*/


#if (UDS_RELOAD_TSTOPDIAG == UDS_RELOAD_TSTOPDIAG_ON)
/*----------------------------------{UDS_ReloadTStopDiag}--------------------------------*/
void UDS_ReloadTStopDiag (void)
{
    DBG_UDS_RELOADTSTOPDIAG_ENTRY();

    switch(m_eSessionCode)
    {
        case UDS_SESSION_PROT_DEFAULT :
            /* Nothing to do */
            break;

        case UDS_SESSION_PROT_OTHER_01:
        case UDS_SESSION_PROT_OTHER_02:
        case UDS_SESSION_PROT_OTHER_03:
        case UDS_SESSION_PROT_OTHER_04:
        case UDS_SESSION_PROT_PROGRAMMING :
        case UDS_SESSION_PROT_EXTENDED_DIAG :
        case UDS_SESSION_PROT_SUPPLIER :
            {
                /* Protection of the session time counter reload
                    (this allow the UDS_Manage () callback to interrupt
                    the counter reload without disabling interrupts) */
                tUdsSessionProtType eSessionCodeOld;
                eSessionCodeOld = m_eSessionCode;

                /* The session timeout is reloaded */
                m_uSessionTimeCnt = (tUdsSessionTimeout) UDS_SESS_TIMEOUT + 1U;

                /* Memorise the asked session code */
                m_eSessionCode = eSessionCodeOld;
            }
            break;

        default :
            /* Indicate of range error */
            m_eSessionCode = UDS_SESSION_PROT_DEFAULT;
            NCS_SdfVariableRangeError (SDF_UDS_SESSION_CODE);
            break;
    }

    DBG_UDS_RELOADTSTOPDIAG_EXIT();
}
/*----------------------------------{end UDS_ReloadTStopDiag}----------------------------*/

/*----------------------------------{UDS_StopSessionTimer}--------------------------------*/
void UDS_StopSessionTimer (void)
{
    DBG_UDS_STOPSESSIONTIMER_ENTRY();

    /* The session timeout is stopped */
    m_uSessionTimeCnt = 0U;

    DBG_UDS_STOPSESSIONTIMER_EXIT();
}
/*----------------------------------{end UDS_StopSessionTimer}----------------------------*/
#endif


#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
/*----------------------------------{UDS_LongRequestRespTxConf}--------------------------------*/
void UDS_LongRequestRespTxConf(void)
{
    DBG_UDS_LONGREQUESTRESPTXCONF_ENTRY();

    m_stLongRequest.m_ubtRespPending = UDS_FALSE;

    DBG_UDS_LONGREQUESTRESPTXCONF_EXIT();
}
/*----------------------------------{end UDS_LongRequestRespTxConf}----------------------------*/


/*----------------------------------{UDS_StopNRC78Timer}--------------------------------*/
void UDS_StopNRC78Timer(void)
{
    DBG_UDS_STOPNRC78TIMER_ENTRY();

    m_stLongRequest.m_ubCnt = 0U;

    DBG_UDS_STOPNRC78TIMER_EXIT();
}
/*----------------------------------{end UDS_StopNRC78Timer}----------------------------*/
#endif


#if (UDS_SRV_CFG5_MAX !=0)
/*----------------------------------{UDS_IsOBDService}--------------------------------*/
tUdsBoolean UDS_IsOBDService(void)
{
    DBG_UDS_ISOBDSERVICE_ENTRY();

    DBG_UDS_ISOBDSERVICE_EXIT(m_eUdsObdService);

    return m_eUdsObdService;
}
/*----------------------------------{end UDS_IsOBDService}----------------------------*/
#endif


/*----------------------------------{UDS_GetCurrentSession}--------------------------------*/
tUdsSessionType UDS_GetCurrentSession(void)
{
    tUdsSessionType eSessionCode;

    DBG_UDS_GETCURRENTSESSION_ENTRY();

    switch(m_eSessionCode)
    {
        case UDS_SESSION_PROT_DEFAULT :
            eSessionCode = m_stSessionInfo[UDS_DEFAULT_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_PROGRAMMING :
            eSessionCode = m_stSessionInfo[UDS_PROGRAMMING_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_EXTENDED_DIAG :
            eSessionCode = m_stSessionInfo[UDS_EXTENDED_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_SUPPLIER :
            eSessionCode = m_stSessionInfo[UDS_SUPPLIER_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_OTHER_01:
            eSessionCode = m_stSessionInfo[UDS_OTHER_01_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_OTHER_02:
            eSessionCode = m_stSessionInfo[UDS_OTHER_02_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_OTHER_03:
            eSessionCode = m_stSessionInfo[UDS_OTHER_03_SESSION_INDEX].ubSessionValue;
            break;
        case UDS_SESSION_PROT_OTHER_04:
            eSessionCode = m_stSessionInfo[UDS_OTHER_04_SESSION_INDEX].ubSessionValue;
            break;
        default:
            eSessionCode = m_stSessionInfo[UDS_DEFAULT_SESSION_INDEX].ubSessionValue;
            break;
    }

    DBG_UDS_GETCURRENTSESSION_EXIT(eSessionCode);

    return eSessionCode;
}
/*----------------------------------{end UDS_GetCurrentSession}----------------------------*/


#if (UDS_SECURITY_CHECK == UDS_SECURITY_CHECK_ON)
/*----------------------------------{UDS_SecurityLevelCheck}--------------------------------*/
NCS_PRI_FCT tUdsStatus UDS_SecurityLevelCheck(u8 ubCfgNb)
{
    tUdsStatus eUdsStatus;
    u8 eUdsSecurityLevel;
    u8 eUdsCurrentSecurityLevel;

    eUdsStatus = UDS_NRC_33;
    eUdsSecurityLevel = 0U;

    switch (ubCfgNb)
    {
        case UDS_CFG_1:
            eUdsSecurityLevel = m_astDiagSrvCfg1[m_uSrvIdx].ubSecLev;
            break;

#if (UDS_SRV_CFG2_MAX !=0)
        case UDS_CFG_2:
            eUdsSecurityLevel = m_astDiagSrvCfg2[m_uSrvIdx].ubSecLev;
            break;
#endif

#if (UDS_SRV_CFG3_MAX !=0)
        case UDS_CFG_3:
            eUdsSecurityLevel = m_astDiagSrvCfg3[m_uSrvIdx].ubSecLev;
            break;
#endif

        default:
            eUdsStatus = UDS_ERR_COHE;
            break;
    }

    /* Check if the security check is needed */
    if (0U != eUdsSecurityLevel)
    {
        /* Get the current security level*/
        eUdsCurrentSecurityLevel = UDS_SECURITY_LEVEL_CHECK_CBK();

        /* Check if the security level match */
        if (eUdsCurrentSecurityLevel == eUdsSecurityLevel)
        {
            eUdsStatus = UDS_ACK;
        }
    }
    else if(UDS_ERR_COHE == eUdsStatus)
    {
        /* Return UDS_ERR_COHE status */
    }
    else
    {
        eUdsStatus = UDS_ACK;
    }


    return eUdsStatus;
}
/*----------------------------------{end UDS_SecurityLevelCheck}----------------------------*/
#endif

/*------------------------------{UDS_LongRequestResponseInd}--------------------------------*/
#if (UDS_FULL_RESPONSEPENDING == STD_ON)
NCS_PRI_FCT tUdsStatus UDS_LongRequestResponseInd (PduLengthType ulLen, u8 *aubUdsData)
{
    BlPduR_Send_TPFrame(ulLen, aubUdsData);

    return UDS_ACK;
}
#endif
/*------------------------------{end UDS_LongRequestResponseInd}----------------------------*/
#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
tUdsStatus UDS_IsPending(void)
{
    tUdsStatus eUdsStatus;

    DBG_UDS_ISPENDING_ENTRY();

    if (m_stLongRequest.m_eState == UDS_LONG_REQ_ON)
    {
        eUdsStatus = UDS_TRUE;
    }
    else
    {
        eUdsStatus = UDS_FALSE;
    }
    DBG_UDS_ISPENDING_EXIT(eUdsStatus);
    return eUdsStatus;
}
#endif

/*------------------------------{Start UDS_Authentication}----------------------------*/
tUdsStatus UDS_Service_Authentication(PduLengthType *puwLen, u8 *aubUdsData)
{

    tUdsStatus eUdsStatus;

    aubUdsData[2] = 0xA2;
    *puwLen = 3U; /* 1 byte response + 2 bytes service and its sub function */
    /* Set positive response */
    eUdsStatus = UDS_ACK;

    return eUdsStatus;
}
/*------------------------------{End UDS_Authentication}----------------------------*/
/*===============================================================================*/
