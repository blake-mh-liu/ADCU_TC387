/* *--------{ EB Automotive C Source File }-------- */


/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>
#include <TSAutosar.h>        /* Specific standard types */
/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM04_25_AVAILABLE == STD_ON )

#include <J1939Dcm_Lcfg.h>
#include <Dem.h>

/* Includes Development Error Tracer interfaces if enabled. */
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>



FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM04_25_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                VAR(uint8, AUTOMATIC) NodeId )
{
    /* Local variable that hold the return value */
    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00041,1 */
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00117,1 */
    /* The filter will be set for DM04 / DM25 . */
    CONST(Dem_J1939DcmSetFreezeFrameFilterType, AUTOMATIC) FreezeFrameKind =((J1939DCM_DM_PGN() == (uint16)0xFECD) ? DEM_J1939DCM_FREEZEFRAME : DEM_J1939DCM_EXPANDED_FREEZEFRAME);

    /* initialize the number of processed Freeze frames per one main function
     * if it reach the maximum Freeze Frames per main function , then the processing will be postponed * to the next Main function */
    VAR(uint8, AUTOMATIC) tNbOfProcessedFFPerCycle = (uint8)0x00;
    VAR(uint16, AUTOMATIC) resDataBufferIndex = (uint16)0x00;

#if( ( J1939DCM_SPN_CMVERSION == 0x03 ) || ( J1939DCM_SPN_CMVERSION == 0x04 ))
    /* Local variable that will hold DTC value for the masking process. */
    VAR(uint8, AUTOMATIC) mask_value0 = (uint8)0x00;
    VAR(uint8, AUTOMATIC) mask_value1 = (uint8)0x00;
#endif
    /* Local variable that hold the return status of function Dem_J1939DcmGetNextFreezeFrame. */
    VAR(Dem_ReturnGetNextFilteredElementType, AUTOMATIC) tGetNextNextFreezeFrame = DEM_FILTERED_OK;

    /* Local variable that hold the current DTC that match the filter. */
    VAR(uint32, AUTOMATIC) tDTC = (uint32)0x00;

    /* Local variable that hold the buffer size  passed to Dem_J1939DcmGetNextFreezeFrame . */
    VAR(uint16, AUTOMATIC) tBufSize = 0x00;
    /* Local variable that hold the current Occurrence counter that match the filter. */
    VAR(uint8, AUTOMATIC) tOccurrenceCounter = (uint8)0x00;

    DBG_J1939DCM_DM04_25_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);
    /* If is the first call then some variables are initialized.  */
    if( OpStatus == J1939DCM_INITIAL)
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00017,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00201.FreezeFrameKind,1 */
        /* Set the filter. */
        if( DEM_FILTER_ACCEPTED == Dem_J1939DcmSetFreezeFrameFilter(FreezeFrameKind,
                                                                NodeId ))
        {

            /* The current position in buffer is set only of first call. */
            J1939Dcm_CurPosInTxBuff = (J1939Dcm_MsgLenType)0x00;
            J1939Dcm_NbOfProcessedFFPerRequest = 0x00;
        }
        else
        {
            /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00018,1 */
            /* If filter is not set an NACK should be send. */
            tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
        }
    }

    /* loop to get related freeze frame to all matched DTC */
    while( tDmResponse == J1939DCM_DM_FUNCTION_OK  )
    {

        /* check if max freeze frames per one main function reached */
        if( tNbOfProcessedFFPerCycle < J1939DCM_MAXFREEZEFRAME_PER_MAINFUNCTION )
        {
          if((uint16)J1939DCM_COMMON_BUFFER_SIZE > ((uint16)J1939Dcm_CurPosInTxBuff + (uint16)0x05u))
          {
              /* update available buffer size */
              tBufSize=(uint16)J1939DCM_COMMON_BUFFER_SIZE-(uint16)J1939Dcm_CurPosInTxBuff -(uint16)0x05u;
              resDataBufferIndex = J1939Dcm_CurPosInTxBuff + (uint16)0x05u;
          }
          else
          {
              tBufSize= (uint16)0x0u;
              resDataBufferIndex = (uint16)0x0u;
          }

            /* get next freeze frame related to a matched DTC */
            /* the first five bytes of the buffer will be filled later if operation was successful */
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.DestBuffer,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.DestBuffer,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00021.MaxFreezeFrames,1 */
            /* freeze frame contents shall be filled through Dem */
            tGetNextNextFreezeFrame = Dem_J1939DcmGetNextFreezeFrame(&tDTC, &tOccurrenceCounter,&pMsgContext->resData[resDataBufferIndex],&tBufSize);

            /* check if get next freeze frame was successful , then process returned values and fill the response . */
            if(tGetNextNextFreezeFrame == DEM_FILTERED_OK )
            {

                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.BufSize,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.BufSize,1 */
                /* The frame length is placed in the response buffer. */
                pMsgContext->resData[J1939Dcm_CurPosInTxBuff] = (uint8)(tBufSize +4u);
#if(J1939DCM_SPN_CMVERSION == 0x01)
                {
                    /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version1,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.J1939DTC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.J1939DTC,1 */
                    /* The current DTC and the occurrence counter is placed in the response buffer. */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff+(J1939Dcm_MsgLenType)0x01] = J1939Dcm_get_uint8_from_uint32(tDTC, 16u);
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = J1939Dcm_get_uint8_from_uint32(tDTC, 8u);
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = J1939Dcm_get_uint8_from_uint32(tDTC, 0u);
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.OC,1 */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x04] = (tOccurrenceCounter | (uint8)0x80);
                }
#elif(J1939DCM_SPN_CMVERSION == 0x02)
                {
                    /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version2,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.J1939DTC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.J1939DTC,1 */
                    /* The current DTC and the occurrence counter is placed in the response buffer. */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff+(J1939Dcm_MsgLenType)0x01] = J1939Dcm_get_uint8_from_uint32(tDTC, 8u);
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = J1939Dcm_get_uint8_from_uint32(tDTC, 16u);
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = J1939Dcm_get_uint8_from_uint32(tDTC, 0u);
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.OC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.OC,1 */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x04] = (tOccurrenceCounter | (uint8)0x80);
                }
#else
                {
                    /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version3,1 */
                    /* !LINKSTO J1939Dcm.SAE.SPNConversionMethod.Version4,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.J1939DTC,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.J1939DTC,1 */
                    /* The current DTC and the occurrence counter is placed in the response buffer. */
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff+(J1939Dcm_MsgLenType)0x01] = J1939Dcm_get_uint8_from_uint32(tDTC, 5u);
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x02] = J1939Dcm_get_uint8_from_uint32(tDTC, 13u);
                    /* Masking process is done to extract SPN and FMI for the converison method */
                    mask_value0 = J1939Dcm_get_uint8_from_uint32(tDTC, 16u);
                    mask_value0 = (uint8)(mask_value0 & (uint8)0xE0u);
                    mask_value1 = J1939Dcm_get_uint8_from_uint32(tDTC, 0u);
                    mask_value1 = (uint8)(mask_value1 & (uint8)0x1Fu);
                    pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x03] = (mask_value0 | mask_value1);
#if(J1939DCM_SPN_CMVERSION == 0x03)
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.OC,1 */
                        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.OC,1 */
                        pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x04] = (tOccurrenceCounter | (uint8)0x80);
                    }
#else
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM04.OC,1 */
                        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00020.DM25.OC,1 */
                        pMsgContext->resData[J1939Dcm_CurPosInTxBuff + (J1939Dcm_MsgLenType)0x04] = (tOccurrenceCounter & (uint8)0x7F);
                    }
#endif
                }
#endif

                /* increase the current cursor position by freeze frame length + 5 bytes for (1 byte frame length + 3 bytes DTC + 1 byte occurrence counter )*/
                J1939Dcm_CurPosInTxBuff += (J1939Dcm_MsgLenType)(tBufSize +5u);
                /* increment the number of processed freeze frames per one main function */
                tNbOfProcessedFFPerCycle++;
                J1939Dcm_NbOfProcessedFFPerRequest++;
            }
            /* check if get next freeze frame shall be postponed to the next main function */
            else if (tGetNextNextFreezeFrame == DEM_FILTERED_PENDING)
            {
                /* An pending is received. The next requested DTC will be postpone to the next main function.  */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00021.Pending,1 */
                tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
                break;

            }
            /* check if available buffer size is too small */
            else if (tGetNextNextFreezeFrame == DEM_FILTERED_BUFFER_TOO_SMALL)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00165.DET_ERROR,1 */
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.BUFFERTOOSMALL,1 */
        (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_MAINFUNCTION, J1939DCM_E_BUFFER_TOO_SMALL);

#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

                /* if available buffer size is too small an NACK should be send. */
                tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
                break;
            }

            else /* DEM_FILTERED_NO_MATCHING_ELEMENT */
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00022.DM25.Broadcast,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00022.DM25.NoBroadcast,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00022.DM04.Broadcast,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00022.DM04.NoBroadcast,1 */
                /* Check that No DTC was found  */
                if( J1939Dcm_NbOfProcessedFFPerRequest == 0x00u )
                {
                        pMsgContext->resData[0]=0x00;
                        pMsgContext->resData[1]=0x00;
                        pMsgContext->resData[2]=0x00;
                        pMsgContext->resData[3]=0x00;
                        pMsgContext->resData[4]=0x00;
                        pMsgContext->resData[5]=0xFF;
                        pMsgContext->resData[6]=0xFF;
                        pMsgContext->resData[7]=0xFF;
                        J1939Dcm_CurPosInTxBuff = (J1939Dcm_MsgLenType)0x08;
                }
                /* Nothing to do. Stop the loop because not all DTC match after all the above filter. */
                break;
            }

        }
        else
        {
            /* A pending response is necessary to avoid an OS error */
            tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
        }
    }

    /* Check if no pending is received. */
    if(tDmResponse != J1939DCM_DM_FUNCTION_PENDING)
    {
        /* Check if all function return OK. */
        if( tDmResponse == J1939DCM_DM_FUNCTION_OK )
        {
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

    DBG_J1939DCM_DM04_25_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;

}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM04_25_AVAILABLE */
