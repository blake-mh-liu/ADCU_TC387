/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>

/*===================================================END OF INCLUDES ===========================================*/
#if (J1939DCM_REPORTDTCS_AVAILABLE == STD_ON)

#include <Dem.h>

#include <J1939Dcm_Lcfg.h>

#define  J1939DCM_START_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

/* Variable used to store the number of filter DTC's\Records depending on the received sub-function */
VAR(uint16, J1939DCM_VAR) J1939Dcm_NumberOfFilteredItems;

#define  J1939DCM_STOP_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

/* ================Start internal functions prototype section ====================== */

INLINE FUNC(void, J1939DCM_CODE) J1939Dcm_InternalGetNumberOfFilteredDTC( P2VAR(J1939Dcm_DmResponseType, AUTOMATIC, AUTOMATIC) DMRspCode );

/* ================Stop internal functions prototype section ====================== */

INLINE FUNC(void, J1939DCM_CODE) J1939Dcm_InternalGetNumberOfFilteredDTC( P2VAR(J1939Dcm_DmResponseType, AUTOMATIC, AUTOMATIC) DMRspCode )
{

    /* Holds the status of the function Dem_J1939DcmGetNumberOfFilteredDTC. */
    VAR(Dem_ReturnGetNumberOfFilteredDTCType, AUTOMATIC) tReturnNbOfFilteredDTC = DEM_NUMBER_OK;


    /* Call the function that gives the number of DTC that match the previous filter. */
    tReturnNbOfFilteredDTC = Dem_J1939DcmGetNumberOfFilteredDTC(&J1939Dcm_NumberOfFilteredItems) ;

    DBG_J1939DCM_INTERNALGETNUMBEROFFILTEREDDTC_ENTRY(DMRspCode);
    /* Check if the function return OK. */
    if( tReturnNbOfFilteredDTC == DEM_NUMBER_OK )
    {
#if( J1939DCM_DM01_AVAILABLE == STD_ON )
        /* Maximum 20 DTCs will be transmitted for cyclic DM.
         * The cyclic DM will stay always on the first position in table J1939Dcm_SelectDTCFilters. */
        if(    ( J1939Dcm_NumberOfFilteredItems > (uint8)20 ) &&
            ( J1939DCM_DM_PGN() == (uint16)0xFECA )
        )
        {   /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00116,1 */
            J1939Dcm_NumberOfFilteredItems = (uint8)20;
        }
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */

    }
    else if(tReturnNbOfFilteredDTC == DEM_NUMBER_PENDING)
    {
        /* An pending is received. postpone function Dem_J1939DcmGetNumberOfFilteredDTC call at next main function. */
        *DMRspCode = J1939DCM_DM_FUNCTION_PENDING;
    }
    else
    {
        /* Get number of filter DTC is failed */
        *DMRspCode = J1939DCM_DM_FUNCTION_NOT_OK;
    }
    DBG_J1939DCM_INTERNALGETNUMBEROFFILTEREDDTC_EXIT(DMRspCode);
}

/*This function support DM01,DM02,DM06,DM12,DM23,DM28*/
FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_ReportDTC_RequestProcessing(    VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                            P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                            VAR(uint8, AUTOMATIC) NodeId)
{

    /* Hold the lamp status when the filter Dem_J1939DcmSetDTCFilter is accepted. */
    VAR(Dem_J1939DcmLampStatusType, AUTOMATIC) tLampStatus = (Dem_J1939DcmLampStatusType)0x00;

    /* Local variable that hold the return status of function Dem_J1939DcmGetNextFilteredDTC. */
    VAR(Dem_ReturnGetNextFilteredElementType, AUTOMATIC) tGetNextFilteredDTC = DEM_FILTERED_OK;

    /* Local variable that will hold the current DTC that match the filter. */
    VAR(uint32, AUTOMATIC) tDTC = (uint32)0x00;

#if( ( J1939DCM_SPN_CMVERSION == 0x03 ) || ( J1939DCM_SPN_CMVERSION == 0x04 ))
    /* Local variable that will hold DTC value for the masking process. */
    VAR(uint8, AUTOMATIC) mask_value0 = (uint8)0x00;
    VAR(uint8, AUTOMATIC) mask_value1 = (uint8)0x00;
#endif
    /* Local variable that will hold the current Occurrence counter that match the filter. */
    VAR(uint8, AUTOMATIC) tOccurrenceCounter = (uint8)0x00;

    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

    /* Initialize the number of processed DTC in one main function.
     * If this number reach the maximum number allowed then the processing should be postponed in the next main function. */
    VAR(uint8, AUTOMATIC) tNbOfProcessedDTCPerCycle = (uint8)0x00;

    DBG_J1939DCM_REPORTDTC_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* If is the first call then some variables are initialized.  */
    if( OpStatus == J1939DCM_INITIAL)
    {
        /* The number of filtered DTC that match the current filter is reset. */
        J1939Dcm_NumberOfFilteredItems = (uint16)0x00;

        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00010,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00035,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00033,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00046,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00052,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00068,1 */
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00074,1 */

        /* Set the filter. */
        if( DEM_FILTER_ACCEPTED == Dem_J1939DcmSetDTCFilter(    J1939Dcm_SelectDTCFilters[J1939DCM_SPECIAL_INFO()].u8DTCStatusFilter,
                                    J1939Dcm_SelectDTCFilters[J1939DCM_SPECIAL_INFO()].u8DTCKind,
                                    NodeId,
                                    &tLampStatus )
        )
        {
             /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00011,1 */
            /* If at least one DTC should be reported then lamp status information is put into buffer. */
            pMsgContext->resData[0] = (uint8)(tLampStatus>>0x08);
            pMsgContext->resData[1] = (uint8)(tLampStatus);

            /* The current position in buffer is reseted. */
            J1939Dcm_CurPosInTxBuff = (J1939Dcm_MsgLenType)0x02;
        }
        else
        {
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00012,1 */
            /* The filter was not set. Stop further processing. */
            tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
        }
    }

    /* Check if the filter was set OK and if Dem_J1939DcmGetNumberOfFilteredDTC was not returned pending in the previous call. */
    if(    ( tDmResponse == J1939DCM_DM_FUNCTION_OK ) &&     /* if no error */
        ( J1939Dcm_NumberOfFilteredItems == (uint16)0x00 )    /* number of filtered items not yet obtained */
    )
    {
        /* Get the number of DTC that match the filter. */
        J1939Dcm_InternalGetNumberOfFilteredDTC(&tDmResponse);
    }


    /* Function Dem_J1939DcmGetNextFilteredDTC is called until all filtered DTC are processed or
     *  an DEM_FILTERED_NO_MATCHING_ELEMENT is received. */
    while(    ( J1939Dcm_NumberOfFilteredItems > (uint16)0x00 ) &&
        ((((uint32)J1939Dcm_CurPosInTxBuff + (uint32)0x04) <= (uint32)pMsgContext->resMaxDataLen ) &&
        ( tDmResponse == J1939DCM_DM_FUNCTION_OK ))
    )
    {


        /* Request next DTC that match the previously filter. */
        tGetNextFilteredDTC = Dem_J1939DcmGetNextFilteredDTC( &tDTC, &tOccurrenceCounter );

        /* Check the return status for current DTC */
        if( tGetNextFilteredDTC == DEM_FILTERED_OK )
        {
#if (J1939DCM_SPN_CMVERSION == 0x01)
            {
                /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version1,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00075.J1939DTC,1 */
                /* The current DTC and the occurrence counter is placed in the response buffer. */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff] = J1939Dcm_get_uint8_from_uint32(tDTC, 16u);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x01] = J1939Dcm_get_uint8_from_uint32(tDTC, 8u);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = J1939Dcm_get_uint8_from_uint32(tDTC, 0u);
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.OccurenceCounter,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00075.OC,1 */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = (tOccurrenceCounter | (uint8)0x80);
            }
#elif (J1939DCM_SPN_CMVERSION == 0x02)
            {
                /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version2,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00075.J1939DTC,1 */
                /* The current DTC and the occurrence counter is placed in the response buffer. */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff] = J1939Dcm_get_uint8_from_uint32(tDTC, 8u);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x01] = J1939Dcm_get_uint8_from_uint32(tDTC, 16u);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = J1939Dcm_get_uint8_from_uint32(tDTC, 0u);
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.OccurenceCounter,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.OC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00075.OC,1 */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = (tOccurrenceCounter | (uint8)0x80);
            }
#else
            {
                /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version3,1 */
                /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version4,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.J1939DTC,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.J1939DTC,1 */
                /* The current DTC and the occurrence counter is placed in the response buffer. */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff] = J1939Dcm_get_uint8_from_uint32(tDTC , 5u);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x01] = J1939Dcm_get_uint8_from_uint32(tDTC, 13u);
                /* Masking process is done to extract SPN and FMI for the converison method */
                mask_value0 = J1939Dcm_get_uint8_from_uint32(tDTC, 16u);
                mask_value0 = (uint8)(mask_value0 & (uint8)0xE0u);
                mask_value1 = J1939Dcm_get_uint8_from_uint32(tDTC, 0u);
                mask_value1 = (uint8)(mask_value1 & (uint8)0x1Fu);
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = (mask_value0 | mask_value1);
#if(J1939DCM_SPN_CMVERSION == 0x03)
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.OccurenceCounter,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00075.OC,1 */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = (tOccurrenceCounter | (uint8)0x80);
                }
#else
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00014.OccurenceCounter,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00034.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00036.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00047.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00053.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00069.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00075.OC,1 */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = (tOccurrenceCounter & (uint8)0x7F);
                }
#endif
            }
#endif

            /* Update the remaining DTC that match the previously filter. */
            J1939Dcm_NumberOfFilteredItems--;

            /* Update the position in the response buffer with length for DTC and occurrence counter.  */
            J1939Dcm_CurPosInTxBuff += (J1939Dcm_MsgLenType)0x04;

            /* Check if still are DTC to be processed. */
            if( J1939Dcm_NumberOfFilteredItems > (uint16)0x00 )
            {
                /* increase the number of processed items */
                tNbOfProcessedDTCPerCycle++;

                /* if the limit per cycle is reached we stop the processing for now */
                if( tNbOfProcessedDTCPerCycle >= J1939DCM_MAXDTCS_PER_MAINFUNCTION     /* max number of records is reached */ )
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00015.MaxDTCsPerMainFunction,1 */
                    /* A pending response is necessary to avoid an OS error */
                    tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
                }
            }
        }
        else
        {
            if (tGetNextFilteredDTC == DEM_FILTERED_PENDING)
            {
                /* An pending is received. The next requested DTC will be postpone to the next main function.  */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00015.Pending,1 */
                tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
            }
            else    /* DEM_FILTERED_NO_MATCHING_ELEMENT */
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00016.NoBroadcast,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00016.Broadcast,1 */
                J1939Dcm_NumberOfFilteredItems = (uint16)0;
            }
        }
    }

    /* Check if an pending is received. */
    if( tDmResponse != J1939DCM_DM_FUNCTION_PENDING )
    {
        /* Check if all function return Ok. */
        if( tDmResponse == J1939DCM_DM_FUNCTION_OK )
        {
            if( J1939Dcm_CurPosInTxBuff < (J1939Dcm_MsgLenType)0x08 )
            {
                /* padding is needed */
                /* If is only one DTC to report then unused bytes 7 and 8 of the CAN frame shall be set to 0xFF.
                 * Accordingly with J1939-21 doc. */
                pMsgContext->resData[6] = (uint8)0xFF;
                pMsgContext->resData[7] = (uint8)0xFF;

                /* check if no DTC was found */
                if( J1939Dcm_CurPosInTxBuff < (J1939Dcm_MsgLenType)0x06 )
                {
                    /* in case of no DTC's we write zeros */
                    pMsgContext->resData[2] = (uint8)0x00;
                    pMsgContext->resData[3] = (uint8)0x00;
                    pMsgContext->resData[4] = (uint8)0x00;
                    pMsgContext->resData[5] = (uint8)0x00;
                }

                /* Add 2 padding bytes for case when no more that 1 DTC is to send. */
                J1939Dcm_CurPosInTxBuff = (J1939Dcm_MsgLenType)0x08;
            }

            /* Update the length for cyclic DM. */
            pMsgContext->resDataLen = J1939Dcm_CurPosInTxBuff;

            /* Mark information as an positive response should be send. */
            pMsgContext->Response = J1939DCM_NORMAL_RESPONSE;
        }
        else
        {
            /* Mark information as an negative acknowledgment should be send. */
            pMsgContext->Response = J1939DCM_ACK_RESPONSE;
            pMsgContext->Acknowledge = J1939DCM_ACK_NEGATIVE;
        }
    }
    DBG_J1939DCM_REPORTDTC_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);

    return tDmResponse;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_REPORTDTCS_AVAILABLE */

