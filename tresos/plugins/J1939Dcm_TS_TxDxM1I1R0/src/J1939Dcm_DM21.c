/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>
#include <TSAutosar.h>        /* Specific standard types */
/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM21_AVAILABLE == STD_ON )

#include <Dem.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>


FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM21_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                VAR(uint8, AUTOMATIC) NodeId)
{
    /* Local variable that hold the return value */
    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

    /* Contain the Diagnostic Readiness 2 value computed by DEM. */
    VAR(Dem_J1939DcmDiagnosticReadiness2Type, AUTOMATIC) tDataValue = {(uint16)0x00, (uint16)0x00, (uint16)0x00, (uint16)0x00 };

    DBG_J1939DCM_DM21_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* suppress compiler warning */
    TS_PARAM_UNUSED(OpStatus);
    /* Call associate DEM function. */
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00064,1 */

    if( E_OK == Dem_J1939DcmReadDiagnosticReadiness2( &tDataValue, NodeId ) )
    {
        /* Put the information from DEM to the response buffer. */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00065.EncodeData,1 */
        pMsgContext->resData[0] = (uint8)(tDataValue.DistanceTraveledWhileMILisActivated);
        pMsgContext->resData[1] = (uint8)(tDataValue.DistanceTraveledWhileMILisActivated>>0x08);
        pMsgContext->resData[2] = (uint8)(tDataValue.DistanceSinceDTCsCleared);
        pMsgContext->resData[3] = (uint8)(tDataValue.DistanceSinceDTCsCleared>>0x08);
        pMsgContext->resData[4] = (uint8)(tDataValue.MinutesRunbyEngineWhileMILisActivated);
        pMsgContext->resData[5] = (uint8)(tDataValue.MinutesRunbyEngineWhileMILisActivated>>0x08);
        pMsgContext->resData[6] = (uint8)(tDataValue.TimeSinceDiagnosticTroubleCodesCleared);
        pMsgContext->resData[7] = (uint8)(tDataValue.TimeSinceDiagnosticTroubleCodesCleared>>0x08);

        pMsgContext->resDataLen = (J1939Dcm_MsgLenType)0x08;

        pMsgContext->Response = J1939DCM_NORMAL_RESPONSE;
    }
    else
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00067,1 */
        pMsgContext->Response = J1939DCM_ACK_RESPONSE;
        pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
    }
    DBG_J1939DCM_DM21_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM21_AVAILABLE */

