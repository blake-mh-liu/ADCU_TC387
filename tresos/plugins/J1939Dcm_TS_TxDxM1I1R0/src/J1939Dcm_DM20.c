/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>

/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM20_AVAILABLE == STD_ON )

#include <Dem.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00063,1 */
FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM20_RequestProcessing(   VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                                VAR(uint8, AUTOMATIC) NodeId )
{

    /* Local variable that will hold the return value of function Dem_J1939DcmGetNextFilteredRatio
     * (This function --Dem_J1939DcmGetNextFilteredRatio-- should be called until return DEM_FILTERED_NO_MATCHING_ELEMENT ) */
    VAR(Dem_ReturnGetNextFilteredElementType, AUTOMATIC) tJ1939DcmGetNextFilteredRatio = DEM_FILTERED_OK;

    /* Temporally counter that defines the number of ignition cycles. */
    VAR(uint16, AUTOMATIC) tIgnitionCycleCounter = (uint16)0x00;

    /* Displays the number of times that the vehicle has been operated in the specified OBD monitoring conditions. */
    VAR(uint16, AUTOMATIC) tOBDMonitoringConditionsEncountered = (uint16)0x00;

    /* Contain the SPN of the system monitor for which Monitor ratio is being reported. */
    VAR(uint16, AUTOMATIC) tSPN = (uint16)0x00;

    /* The number of times a vehicle has been operated such that all conditions to detect a malfunction have been encountered */
    VAR(uint16, AUTOMATIC) tNumerator = (uint16)0x00;

    /* The number of driving cycle where this Applicable System Monitor could be operated per regulatory requirements. */
    VAR(uint16, AUTOMATIC) tDenominator = (uint16)0x00;

    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

    /* The maximum sequence counter threshold per MainFunction is reached (see J1939DcmMaxRatiosPerMainFunction). */
    VAR(uint8, AUTOMATIC) tNbOfProcessedDTCPerCycle = (uint8)0x00;

    DBG_J1939DCM_DM20_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* If is the first call then some variables are initialized.  */
    if( OpStatus == J1939DCM_INITIAL)
    {

        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00023,1 */

        /* Set the filter. */
        if( DEM_FILTER_ACCEPTED == Dem_J1939DcmSetRatioFilter(    &tIgnitionCycleCounter,
                                                                &tOBDMonitoringConditionsEncountered,
                                                                NodeId ))
        {

            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00024.IgnitionCnt,1 */
            pMsgContext->resData[0] = (uint8)(tIgnitionCycleCounter);
            pMsgContext->resData[1] = (uint8)(tIgnitionCycleCounter>>0x08);
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00024.OBDMonitoringEncountered,1 */
            pMsgContext->resData[2] = (uint8)(tOBDMonitoringConditionsEncountered);
            pMsgContext->resData[3] = (uint8)(tOBDMonitoringConditionsEncountered>>0x08);

            /* The current position in buffer is set only of first call. */
            J1939Dcm_CurPosInTxBuff = (J1939Dcm_MsgLenType)0x04;
        }
        else
        {
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00025,1 */
            /* If filter is not set an NACK should be send. */
            tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
        }
    }

    /* Call the function until an DEM_FILTERED_PENDING/DEM_FILTERED_NO_MATCHING_ELEMENT is received
     *  or the buffer cannot hold all available information.  */
    while( ( (J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x07) <= pMsgContext->resMaxDataLen ) &&
            (tDmResponse == J1939DCM_DM_FUNCTION_OK) )
    {

        /* If the limit per cycle is reached we stop the processing in current main function.
         * The processing will continue in the next main function. */
        if( tNbOfProcessedDTCPerCycle < J1939DCM_MAXRATIOS_PER_MAINFUNCTION )
        {
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00203.SubsequentCall,1*/
            /* Gets the next filtered Ratio. */
            tJ1939DcmGetNextFilteredRatio = Dem_J1939DcmGetNextFilteredRatio( &tSPN, &tNumerator, &tDenominator);

            /* In case of positive response the corresponding info shall be copied to the response message. */
            if( tJ1939DcmGetNextFilteredRatio == DEM_FILTERED_OK )
            {

                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00027.SPN,1 */
                /* All available information from DEM is putted in the response message. */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff] = (uint8)(tSPN);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x01] = (uint8)(tSPN>>0x08);
                /* DEM function will return for SPN an uint16 but accordingly with SAE J1939-73 the SPN should have 3 bytes.
                 * The most significant 5 bits will be set to all ones. */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = (uint8)0xF8;
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00027.Numerator,1 */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = (uint8)(tNumerator);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x04] = (uint8)(tNumerator>>0x08);
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00027.Denumerator,1 */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x05] = (uint8)(tDenominator);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x06] = (uint8)(tDenominator>>0x08);

                /* Update the position in the response buffer with length for SPN, numerator, denominator.  */
                J1939Dcm_CurPosInTxBuff += (J1939Dcm_MsgLenType)0x07;

                /* Increase the number of processed items  per MainFunction. */
                tNbOfProcessedDTCPerCycle++;

            }
            else if (tJ1939DcmGetNextFilteredRatio == DEM_FILTERED_PENDING)
            {
                /* An pending is received. The next requested DTC will be postpone to the next main function.  */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00028.Pending,1 */
                tDmResponse = J1939DCM_DM_FUNCTION_PENDING;

            }
            else if (tJ1939DcmGetNextFilteredRatio == DEM_FILTERED_BUFFER_TOO_SMALL)
            {
                tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
            }
            else /* DEM_FILTERED_NO_MATCHING_ELEMENT */
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00029.NoMatchingElement,1 */
                /* Nothing to do. Stop the loop because not all DTC match after all the above filter. */
                break;
            }
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00028.MaxRatios,1 */
            /* A pending response is necessary to avoid an OS error */
            tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
        }

    }


    /* Check if an pending is received. */
    if(tDmResponse != J1939DCM_DM_FUNCTION_PENDING)
    {
        /* Check if all function return Ok. */
        if( tDmResponse == J1939DCM_DM_FUNCTION_OK )
        {
            /* Update the length for cyclic DM. */
            pMsgContext->resDataLen = J1939Dcm_CurPosInTxBuff;

            /* Mark information as an positive response should be send. */
            pMsgContext->Response = J1939DCM_NORMAL_RESPONSE;
        }
        else
        {
            /* Mark information as an negative acknowledgement should be send. */
            pMsgContext->Response = J1939DCM_ACK_RESPONSE;
            pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        }
    }
    DBG_J1939DCM_DM20_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM20_AVAILABLE */

