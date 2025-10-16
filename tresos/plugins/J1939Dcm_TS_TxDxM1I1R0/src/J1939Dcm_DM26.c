/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>
#include <TSAutosar.h>        /* Specific standard types */
/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM26_AVAILABLE == STD_ON )

#include <Dem.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM26_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                VAR(uint8, AUTOMATIC) NodeId )
{
    /* Local variable that hold the return value */
    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

    /* Contain the Diagnostic Readiness 3 value computed by DEM. */
    VAR(Dem_J1939DcmDiagnosticReadiness3Type, AUTOMATIC) tDataValue = {(uint16)0x00, (uint8)0x00, (uint8)0x00, (uint16)0x00, (uint16)0x00 };

    DBG_J1939DCM_DM26_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* suppress compiler warning */
    TS_PARAM_UNUSED(OpStatus);
    /* Call associate DEM function. */
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00070,1 */
    if( E_OK == Dem_J1939DcmReadDiagnosticReadiness3( &tDataValue, NodeId ) )
    {
        /* Put the information from DEM to the response buffer. */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00071.EncodeData,1 */
        pMsgContext->resData[0] = (uint8)(tDataValue.TimeSinceEngineStart);
        pMsgContext->resData[1] = (uint8)(tDataValue.TimeSinceEngineStart>>0x08);
        pMsgContext->resData[2] = tDataValue.NumberofWarmupsSinceDTCsCleared;
        pMsgContext->resData[3] = tDataValue.ContinuouslyMonitoredSystemsEnableCompletedStatus;
        pMsgContext->resData[4] = (uint8)(tDataValue.NonContinuouslyMonitoredSystemsEnableStatus);
        pMsgContext->resData[5] = (uint8)(tDataValue.NonContinuouslyMonitoredSystemsEnableStatus>>0x08);
        pMsgContext->resData[6] = (uint8)(tDataValue.NonContinuouslyMonitoredSystems);
        pMsgContext->resData[7] = (uint8)(tDataValue.NonContinuouslyMonitoredSystems>>0x08);

        pMsgContext->resDataLen = (J1939Dcm_MsgLenType)0x08;

        pMsgContext->Response = J1939DCM_NORMAL_RESPONSE;
    }
    else
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00073,1 */
        pMsgContext->Response = J1939DCM_ACK_RESPONSE;
        pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
    }

    DBG_J1939DCM_DM26_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;

}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM26_AVAILABLE */

