/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>
#include <TSAutosar.h>        /* Specific standard types */
/*===================================================END OF INCLUDES ===========================================*/
#if (J1939DCM_DM03_11_AVAILABLE == STD_ON)

#include <J1939Dcm_Lcfg.h>
#include <Dem.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM03_11_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                VAR(uint8, AUTOMATIC) NodeId )
{


    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_PENDING;

    /* The filter will be set for DM11 to clear/reset for active DTCs. */
    CONST(Dem_J1939DcmSetClearFilterType, AUTOMATIC) tDTCTypeFilter = ((J1939DCM_DM_PGN() != (uint16)0xFECC) ? DEM_J1939DTC_CLEAR_ALL : DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE);

    /* Call the function from DEM to clear DTCs. */
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00037,1 */
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00048,1 */

    VAR(Dem_ReturnClearDTCType, AUTOMATIC) tReturnClearDTCType = Dem_J1939DcmClearDTC( tDTCTypeFilter, NodeId);

    DBG_J1939DCM_DM03_11_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* suppress compiler warning */
    TS_PARAM_UNUSED(OpStatus);

    /* Finish request only for case different of pending. */
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00038,1 */
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00049,1 */
    if( tReturnClearDTCType != DEM_CLEAR_PENDING)
    {
        /* An positive acknowledgment(PACK) will be sent to J1939Rm_SendAck */
        if( tReturnClearDTCType == DEM_CLEAR_OK)
        {
            /* Mark information as an positive response should be send. */
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00039,1 */
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00050,1 */
            pMsgContext->Response = J1939DCM_ACK_RESPONSE;
            pMsgContext->Acknowledge = J1939DCM_ACK_POSITIVE;
        }
        else
        {
            /* An negative acknowledgment(NACK) will be sent to J1939Rm_SendAck */
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00040,1 */
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00051,1 */
            pMsgContext->Response = J1939DCM_ACK_RESPONSE;
            pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        }

        tDmResponse = J1939DCM_DM_FUNCTION_OK;
    }

    DBG_J1939DCM_DM03_11_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>


#endif /* J1939DCM_DM03_11_AVAILABLE */

