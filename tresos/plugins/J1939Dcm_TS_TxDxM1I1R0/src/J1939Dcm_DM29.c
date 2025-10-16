/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>

/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM29_AVAILABLE == STD_ON )

#include <Dem.h>

#define  J1939DCM_START_SEC_VAR_CLEARED_8
#include <J1939Dcm_MemMap.h>
static VAR(uint8, J1939DCM_VAR) J1939Dcm_SetFilter_NextReport;
static VAR(uint8, J1939DCM_VAR)  J1939Dcm_DTCNbOfProcessedItems;
#define  J1939DCM_STOP_SEC_VAR_CLEARED_8
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_CONST_UNSPECIFIED
#include <J1939Dcm_MemMap.h>
static CONST(J1939Dcm_SetDTCFilterType, J1939DCM_CONST) J1939Dcm_DTCFilters[0x05] = {
                                                        { DEM_J1939DTC_PENDING, DEM_DTC_KIND_EMISSION_REL_DTCS },
                                                        { DEM_J1939DTC_PENDING, DEM_DTC_KIND_ALL_DTCS },
                                                        { DEM_J1939DTC_ACTIVE, DEM_DTC_KIND_EMISSION_REL_DTCS },
                                                        { DEM_J1939DTC_PREVIOUSLY_ACTIVE, DEM_DTC_KIND_EMISSION_REL_DTCS },
                                                        { DEM_J1939DTC_PERMANENT, DEM_DTC_KIND_EMISSION_REL_DTCS } };
#define  J1939DCM_STOP_SEC_CONST_UNSPECIFIED
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM29_RequestProcessing(   VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                                                P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                                                VAR(uint8, AUTOMATIC) NodeId )
{

    /* Holds the status of the function Dem_J1939DcmGetNumberOfFilteredDTC. */
    VAR(Dem_ReturnGetNumberOfFilteredDTCType, AUTOMATIC) tReturnNbOfFilteredDTC = DEM_NUMBER_OK;

    /* Hold the lamp status when the filter Dem_J1939DcmSetDTCFilter is accepted. */
    VAR(Dem_J1939DcmLampStatusType, AUTOMATIC) tLampStatus = (uint16)0x00;

    /* Temporally counter that will cycle between all 5 different filters.  */
    VAR(uint8, AUTOMATIC) tCtr = (uint8)0x00;

    /* Will contain the number of DTCs that match the previous applied filter. */
    VAR(uint16, AUTOMATIC) tNumberOfFilteredItems = (uint16)0x00;

    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

    DBG_J1939DCM_DM29_REQUESTPROCESSING_ENTRY(OpStatus, pMsgContext, NodeId);

    /* If is the first call then some variables are initialised.  */
    if( OpStatus == J1939DCM_INITIAL)
    {
        /* Current number of filters from J1939Dcm_DTCFilters that are applied.  */
        J1939Dcm_DTCNbOfProcessedItems = (uint8)0x00;

        /* Mark info to apply the current filter. */
        J1939Dcm_SetFilter_NextReport = (uint8)0x01;
    }

    /* Cycle between all 5 filters that will be applied one by one. */
    for(tCtr = J1939Dcm_DTCNbOfProcessedItems; ((tCtr < (uint8)0x05) && (tDmResponse == J1939DCM_DM_FUNCTION_OK)); tCtr++)
    {

        /* Check if the current filter can be applied. */
        if(J1939Dcm_SetFilter_NextReport == (uint8)0x01)
        {
            /* Set the filter. */

            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00076,1 */
            if( DEM_FILTER_ACCEPTED != Dem_J1939DcmSetDTCFilter(    J1939Dcm_DTCFilters[tCtr].u8DTCStatusFilter,
                                                                    J1939Dcm_DTCFilters[tCtr].u8DTCKind,
                                                                    NodeId,
                                                                    &tLampStatus ))
            {
                /* The filter was not set. Stop further processing. */
                tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
            }
        }

        /* If the filter was successful applied. */
        if(tDmResponse == J1939DCM_DM_FUNCTION_OK)
        {
            /* Call the function that gives the number of DTC that match the previous filter. */
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00077,1 */
            tReturnNbOfFilteredDTC = Dem_J1939DcmGetNumberOfFilteredDTC( &tNumberOfFilteredItems ) ;

            /* Check if the function return OK. */
            if( tReturnNbOfFilteredDTC == DEM_NUMBER_OK )
            {

                /* Put the number of DTCs that match the applied filter on his position in the response. */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00078,1 */
                pMsgContext->resData[tCtr] = (uint8)tNumberOfFilteredItems;

                /* Set info because the next filter can be applied. */
                J1939Dcm_SetFilter_NextReport = (uint8)0x01;

                /* Go to the next filter.  */
                J1939Dcm_DTCNbOfProcessedItems++;

            }
            else if(tReturnNbOfFilteredDTC == DEM_NUMBER_PENDING)
            {
                /* An pending is received. postpone function Dem_J1939DcmGetNumberOfFilteredDTC call at next main function. */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00079,1 */
                tDmResponse = J1939DCM_DM_FUNCTION_PENDING;

                /* Set info to not set the filter again because an pending is received and Dem_J1939DcmGetNumberOfFilteredDTC should be called again.   */
                J1939Dcm_SetFilter_NextReport = (uint8)0x00;

            }
            else
            {
                /* An negative acknowledgement will be send. */
                tDmResponse = J1939DCM_DM_FUNCTION_NOT_OK;
            }
        }
    }

    /* Check if an pending is received. */
    if(tDmResponse != J1939DCM_DM_FUNCTION_PENDING)
    {
        /* Check if all function return OK. */
        if( tDmResponse == J1939DCM_DM_FUNCTION_OK )
        {
            /* Accordingly with SAE J1939-73 the unused bytes 5,6,7 shall be set to 0xFF. */
            pMsgContext->resData[5] = (uint8)0xFF;
            pMsgContext->resData[6] = (uint8)0xFF;
            pMsgContext->resData[7] = (uint8)0xFF;

            /* Update the length for cyclic DM. */
            pMsgContext->resDataLen = (J1939Dcm_MsgLenType)0x08;

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
    DBG_J1939DCM_DM29_REQUESTPROCESSING_EXIT(tDmResponse, OpStatus, pMsgContext, NodeId);
    return tDmResponse;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM29_AVAILABLE */

