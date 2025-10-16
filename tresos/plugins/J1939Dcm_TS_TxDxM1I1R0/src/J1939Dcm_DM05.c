/* *--------{ EB Automotive C Source File }-------- */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 2.7 (Advisory)
 *    There should be no unused parameters in functions.
 *
 *    Reason:
 *    - this parameter should be considered just for compilation however it is untied
 */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>
#include <TSAutosar.h>        /* Specific standard types */
/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM05_AVAILABLE == STD_ON )

#include <Dem.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>


/* Deviation MISRAC2012-1 <1> */
FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM05_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                VAR(uint8, AUTOMATIC) NodeId )
{
    /* Local variable that hold the return value */
    J1939Dcm_DmResponseType tDmResponse = J1939DCM_DM_FUNCTION_OK;

    /* Contain the Diagnostic Readiness 1 value computed by DEM. */
    Dem_J1939DcmDiagnosticReadiness1Type tDataValue = {(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,
                                                                        (uint16)0x00,(uint16)0x00 };

    DBG_J1939DCM_DM05_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* suppress compiler warning */
    TS_PARAM_UNUSED(OpStatus);

    /* Call specific readiness function. */
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00042,1 */
    if( E_OK == Dem_J1939DcmReadDiagnosticReadiness1( &tDataValue, NodeId ))
    {
        /* Put the information from DEM to the response buffer. */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00043.EncodeData,1 */
        pMsgContext->resData[0] = tDataValue.ActiveTroubleCodes;
        pMsgContext->resData[1] = tDataValue.PreviouslyActiveDiagnosticTroubleCodes;
        pMsgContext->resData[2] = tDataValue.OBDCompliance;
        pMsgContext->resData[3] = tDataValue.ContinuouslyMonitoredSystemsSupport_Status;
        pMsgContext->resData[4] = (uint8)(tDataValue.NonContinuouslyMonitoredSystemsSupport);
        pMsgContext->resData[5] = (uint8)(tDataValue.NonContinuouslyMonitoredSystemsSupport>>0x08);
        pMsgContext->resData[6] = (uint8)(tDataValue.NonContinuouslyMonitoredSystemsStatus);
        pMsgContext->resData[7] = (uint8)(tDataValue.NonContinuouslyMonitoredSystemsStatus>>0x08);

        pMsgContext->resDataLen = (J1939Dcm_MsgLenType)0x08;

        pMsgContext->Response = J1939DCM_NORMAL_RESPONSE;
    }
    else
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00045,1 */
        pMsgContext->Response = J1939DCM_ACK_RESPONSE;
        pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
    }
    DBG_J1939DCM_DM05_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;

}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM05_AVAILABLE */

