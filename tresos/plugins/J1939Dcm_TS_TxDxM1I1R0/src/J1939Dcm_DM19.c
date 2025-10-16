/* --------{ EB Automotive C Source File }-------- */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 2.7 (Advisory)
 *    There should be no unused parameters in functions.
 *
 *    Reason:
 *    - this parameter should be considered just for compilation however it is unused
 */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>

/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM19_AVAILABLE == STD_ON )

#include <Rte_J1939Dcm.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>


/* Deviation MISRAC2012-1 <1> */
FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM19_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                VAR(uint8, AUTOMATIC) NodeId)
{
    /* Local variable that will hold the Calibration Verification Number. */
    VAR(uint32, AUTOMATIC) tCalibrationVerificationNumber = (uint32)0x00;

    /* Local variable used to handle different kind of responses. */
    VAR(Std_ReturnType, AUTOMATIC) tRetval = E_OK;

    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

    DBG_J1939DCM_DM19_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* suppress compiler warning */
    TS_PARAM_UNUSED(NodeId);

    /* If is the first call then the current position in Tx buffer is initialized. */
    if( OpStatus == J1939DCM_INITIAL)
    {
        /* The current position in buffer is reseted. */
        J1939Dcm_CurPosInTxBuff = (J1939Dcm_MsgLenType)0x00;
    }

    /* Check if available number of bytes from TxBuffer is enough to hold all available info.
     * 1. Calibration Verification Number will have 4 bytes.
     * 2. Calibration ID will be 16 bytes.
     */
    if( pMsgContext->resMaxDataLen >= (J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x14) )
    {

        /* Call the Rte function in order to have the CVNs. */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00059,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00097,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00061.CalibrationID,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00062.CalibrationID,1 */
        tRetval = Rte_Call_J1939Dcm_CalibrationInformation_GetCalibrationVerificationNumber( &tCalibrationVerificationNumber,
                &pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x04]);

        /* Put the calibration verification number only if CVN calculation is finished and completed or
         *  calculation is finished, but not all CVNs returned yet. */
        if( (tRetval == E_OK) || (tRetval == E_NEXT) )
        {


            if(tRetval == E_NEXT)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00061.ReTriggerCVN,1 */
                tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
            }

            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00061.CVN,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00062.CVN,1 */
            /* Least significant bytes will be send first. */
            pMsgContext->resData[J1939Dcm_CurPosInTxBuff] = J1939Dcm_get_uint8_from_uint32(tCalibrationVerificationNumber,0);
            pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)1] = J1939Dcm_get_uint8_from_uint32(tCalibrationVerificationNumber,8);
            pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)2] = J1939Dcm_get_uint8_from_uint32(tCalibrationVerificationNumber,16);
            pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)3] = J1939Dcm_get_uint8_from_uint32(tCalibrationVerificationNumber,24);

            /* Update the current position in TxBuffer with 20 bytes because this is the length for entire calibration information. */
            J1939Dcm_CurPosInTxBuff += (J1939Dcm_MsgLenType)0x14;
        }
        else
        {
            tDmResponse = J1939DCM_DM_FUNCTION_NOT_READY;
        }
    }
    else
    {
        /* The buffer cannot hold all available information. */
        tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
    }

    /* Continue only if all CVNs are returned. */
    if(tDmResponse != J1939DCM_DM_FUNCTION_PENDING)
    {
        /* An positive response will be send in case the calculation is finished and completed. */
        if( tDmResponse == J1939DCM_DM_FUNCTION_OK )
        {
            pMsgContext->Response = J1939DCM_NORMAL_RESPONSE;

            /* Update the length that will be send. */
            pMsgContext->resDataLen = J1939Dcm_CurPosInTxBuff;

        }
        /* The CVN calculation is not finished yet */
        else if( tDmResponse == J1939DCM_DM_FUNCTION_NOT_READY )
        {

            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00060,1 */
            pMsgContext->Response = J1939DCM_ACK_RESPONSE;
            pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;

        }
        /* The available space in TxBuffer cannot hold all CVNs.*/
        else
        {
            /* Mark information as an negative acknowledgment should be send. */
            pMsgContext->Response = J1939DCM_ACK_RESPONSE;
            pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        }
    }
    DBG_J1939DCM_DM19_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM19_AVAILABLE */

