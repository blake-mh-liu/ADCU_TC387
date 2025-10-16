/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BlPduR layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Prg.c                      */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2016 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.2 (required)
 * There shall be no dead code
 *
 *
 *   Reason:
 * The function has been optimised by the compiler.
 *
 *
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: BlPduR                                                           */
#include "BlPduR_Prj.h"
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */
#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
#if (STD_ON==BLPDUR_NETWORK_FLEXRAY_SUPPORTED)
#include "FrIf_Api.h"
#if (STD_ON==BLPDUR_FRSM_ENABLEALLSLOTS)
#include "FrSM.h"
#endif
#endif
#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
#include <PduR_BlPduR.h>
#endif /*(BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)*/
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
#define FRCYCL_UNUSED 0xFFu

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* Tx Buffer info structure */
tBufferInfoType m_stTxBufferInfo = { 0U, 0U, BLPDUR_BUFF_IDLE, 0U, 0U, FALSE};
/* Pointer to the Tx buffer used */
u8* m_pubTxBuffer = NULL_PTR;

#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
/* Tab to store the pointer Rx Buffer configuration information  use for multiple buffer
   The pointer are stored in the order of treatment */

#endif

#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
/* Timeout value before selected default multiple ID configuration */
NCS_PRI_VAR u32 m_ulMultipleIdSelectTimeout;
#endif
/* Group ID value allowed */
u8 m_ubGroupIdVal;
#endif



/* Store the connection number of the tester who successfully unlocks the ECU. */

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
#if (BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)
/* Counter to schedule the Lin module */
NCS_PRI_VAR u8 m_ubLinManageCnt;
#endif /*(BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)*/
#if (BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)
/* Counter to schedule the Ltp module */
NCS_PRI_VAR u8 m_ubLtpManageCnt;
#endif /*(BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)*/

#if (BLPDUR_USE_UDS_MANAGE_CNT == STD_ON)
/* Counter to schedule the UDS module */
NCS_PRI_VAR u8 m_ubDiagManageCnt;
#endif /*(BLPDUR_USE_DIAG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)
/* Counter to schedule the Prog module */
NCS_PRI_VAR u8 m_ubProgManageCnt;
#endif /*(BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_SA_MANAGE_CNT == STD_ON)
/* Counter to schedule the SA module */
NCS_PRI_VAR u8 m_ubSAManageCnt;
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
NCS_PRI_VAR u16 m_uwBlPduRTpBsVal;
NCS_PRI_VAR u16 m_uwBlPduRTpStminVal;
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/
#if (BLPDUR_USE_PROG == STD_ON)
#ifdef PROG_RESPOND_TO_PROG_SESSION
#if (PROG_RESPOND_TO_PROG_SESSION == STD_ON)
/* Initialize the state for the Simulate Rx Request treatment */
tSimRxReqStateType m_eSimRxReqState = BLPDUR_SIM_RX_REQ_UNINITIALIZED;
#endif /*(PROG_RESPOND_TO_PROG_SESSION == STD_ON)*/
#endif /*PROG_RESPOND_TO_PROG_SESSION*/
#endif /*(BLPDUR_USE_PROG == STD_ON)*/
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
/**
 ** \brief This service is used to select the identifier group used at runtime
 **
 ** \param[in] ubGroupID Group Id value
 **/
NCS_PRI_FCT void BlPduR_SelectGroupID(u8 ubGroupID);
#endif /* (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION) */

/*===============================================================================*/


u8 BlpduR_GetConnNumByTxPdu(PduIdType TxPduId)
{ /* RQD_BLPDUR_PRG_058  */
    u8 ubIdx;
    u8 result = BLPDUR_NO_ACTIVE_CONNECTION;
    BLPDUR_ENTER_CRITICAL_SECTION();
    for(ubIdx = 0U; ubIdx < (BLPDUR_MAX_PDU_CONNECTION); ubIdx++)
    {
        if (stPduConnection[ubIdx].TxPdu==TxPduId)
        {
            result = ubIdx;
            break;
        }
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    return result;
}

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{BlPduR_Init}--------------------------------*/
void BlPduR_Init(void)
{
    DBG_BLPDUR_INIT_ENTRY();

    /* Initialization of the communication stack */
    BlPduR_Init1(); /* RQD_BLPDUR_INIT_020 */

    /* Initialization of the rest of the bootloader stack */
    BlPduR_Init2();

#if ((BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON) && (BLPDUR_NETWORK_CAN_SUPPORTED == STD_ON))
    m_uwBlPduRTpBsVal = BLPDUR_BS_DEFAULT;
    m_uwBlPduRTpStminVal = BLPDUR_STMIN_DEFAULT;
#endif
    BlPduR_Buf_Init();
    DBG_BLPDUR_INIT_EXIT();
}
/*----------------------------------{end BlPduR_Init}----------------------------*/

/*----------------------------------{BlPduR_Init1}--------------------------------*/

void BlPduR_Init1(void)
{
    DBG_BLPDUR_INIT1_ENTRY();

    BlPduR_Custom_Com_Init(); /* RQD_BLPDUR_INIT_001 */

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
    BlPduR_Lin_Init(); /* RQD_BLPDUR_INIT_002 */
#endif

    DBG_BLPDUR_INIT1_EXIT();
}

/*----------------------------------{end BlPduR_Init1}----------------------------*/

/*----------------------------------{BlPduR_Init2}--------------------------------*/
void BlPduR_Init2(void)
{
    DBG_BLPDUR_INIT2_ENTRY();


    BlPduR_InitConnection(); /* RQD_BLPDUR_INIT_010 */

#if (BLPDUR_USE_UDS_MANAGE_CNT == STD_ON)
    m_ubDiagManageCnt = 0U; /* RQD_BLPDUR_INIT_012 */
#endif /*(BLPDUR_USE_DIAG_MANAGE_CNT == STD_ON)*/

    /* RQD_BLPDUR_INIT_017 Initialization of manage counters */
#if (BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)
    m_ubProgManageCnt = 0U;
#endif /*(BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_SA_MANAGE_CNT == STD_ON)
    m_ubSAManageCnt = 0U;
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
    /* Initialize timeout */   /* RQD_BLPDUR_INIT_014 */
    m_ulMultipleIdSelectTimeout = BLPDUR_MULTIPLE_ID_TIMEOUT;
    /* Set the group ID as not yet selected */
    BLPDUR_ENTER_CRITICAL_SECTION();
    m_ubGroupIdVal = BLPDUR_MULTIPLE_ID_NO_SEL;
    BLPDUR_EXIT_CRITICAL_SECTION();
#elif (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_EXTERNAL_NOTIFICATION)
    {
        /* Initialize connection and treatment status */
        uint32 temp_groupval;
        /* Retrieve the Group Id number */ /*  RQD_BLPDUR_INIT_015 */
        temp_groupval = BlPduR_GetGroupIdVal();
        BLPDUR_ENTER_CRITICAL_SECTION();
        m_ubGroupIdVal = temp_groupval;
        /* Check if value is in range */
        if(m_ubGroupIdVal >= BLPDUR_MULTIPLE_ID_CONF_MAX)
        {   /* RQD_BLPDUR_INIT_016 */
            /* if value is out of range set default group */
            m_ubGroupIdVal = BLPDUR_ID_GROUP_DEFAULT;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
    }
#else
    /* Nothing to do */
#endif
#endif

    /* Init RQD_BLPDUR_INIT_018 */
#if (BLPDUR_USE_UDS == STD_ON)
    UDS_Init ();
#endif /*(BLPDUR_USE_UDS == STD_ON)*/
#if (BLPDUR_USE_REPROGMEMM == STD_ON)
    ReProgMemM_Init();
#elif (BLPDUR_USE_FLASH == STD_ON)
    FLASH_Init ();
#endif  /*(BLPDUR_USE_REPROGMEMM == STD_ON)*/
#if (BLPDUR_USE_PROG == STD_ON)
    PROG_Init ();
#endif /*(BLPDUR_USE_PROG == STD_ON)*/
#if (BLPDUR_USE_SA == STD_ON)
    SA_Init ();
#endif /*(BLPDUR_USE_SA == STD_ON)*/

    DBG_BLPDUR_INIT2_EXIT();
}
/*----------------------------------{end BlPduR_Init2}----------------------------*/

#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
/*----------------------------------{BlPduR_GetTpParameter}-------------------------*/
u16 BlPduR_GetTpParameter(tTpParameterId ubParameterId)
{
    u16 uwParameterValue;

    if(ubParameterId == BLPDUR_TP_BS)
    {  /* RQD_BLPDUR_TP_PARAM_010 */
        uwParameterValue = m_uwBlPduRTpBsVal;
    }
    else /* if(ubParameterId == BLPDUR_TP_STMIN) */
    {   /* RQD_BLPDUR_TP_PARAM_011 */
        uwParameterValue = m_uwBlPduRTpStminVal;
    }

    return uwParameterValue;
}
/*----------------------------------{end BlPduR_GetTpParameter}----------------------*/

/*----------------------------------{BlPduR_TpChangeParameter}-------------------------*/
tBlPduRStatus BlPduR_TpChangeParameter(tTpParameterId ubParameterId, u16 uwParameterValue)
{
    Std_ReturnType ePdurStatus;
    tBlPduRStatus eBlPdurStatus;
    u8 ubRxPduId;
    u8 ubIdx;
    u8 ubRxPduIdFound;

    /*Get the current Physical RxPduId*/
    /* Parse the table in order to find the current connection */
    ubRxPduId = 0U; /* RQD_BLPDUR_TP_PARAM_001 */
    ubRxPduIdFound = FALSE;
    for (ubIdx = 0U; ((BLPDUR_MAX_RX_PDU_NUM > ubIdx) && (TRUE != ubRxPduIdFound)); ubIdx++)
    {
        /* Filter on Addressing type Physical */
        if(BLPDUR_PHYSICAL == stRxPdu[ubIdx].AddressingType)
        {
            if (m_ubCurrentConnection == stRxPdu[ubIdx].ConnectionNum)
            {
                ubRxPduId = stRxPdu[ubIdx].RxPduId; /* RQD_BLPDUR_TP_PARAM_001 */
                ubRxPduIdFound = TRUE;
            }
            else
            {
                /* nothing to do */
            }
        }
        else
        {
            /* Functional RxPdu, nothing to do */
        }

    }

    if(TRUE == ubRxPduIdFound)
    {   /* RQD_BLPDUR_TP_PARAM_002 */
        /*Change the parameter for the found Physical RxPduId*/
        ePdurStatus = PduR_BlPduRTpChangeParameter(ubRxPduId, ubParameterId, uwParameterValue);

        if(E_OK == ePdurStatus)
        {
            if(ubParameterId == BLPDUR_TP_BS)
            {   /* RQD_BLPDUR_TP_PARAM_003 */
                m_uwBlPduRTpBsVal = uwParameterValue;
            }
            else /* if(ubParameterId == BLPDUR_TP_STMIN) */
            {   /* RQD_BLPDUR_TP_PARAM_004 */
                m_uwBlPduRTpStminVal = uwParameterValue;
            }
            eBlPdurStatus = BLPDUR_E_OK;
        }
        else
        {   /* RQD_BLPDUR_TP_PARAM_005 */
            eBlPdurStatus = BLPDUR_E_NOT_OK;
        }
    }
    else /* ubRxPduIdFound = FALSE */
    {   /* RQD_BLPDUR_TP_PARAM_006 */
        eBlPdurStatus = BLPDUR_E_NOT_OK;
    }

    return eBlPdurStatus;
}
/*----------------------------------{end BlPduR_TpChangeParameter}----------------------*/
#endif /*(BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)*/

/*----------------------------------{BlPduR_Manage}--------------------------------*/
void BlPduR_Manage(void)
{
    DBG_BLPDUR_MANAGE_ENTRY();

    /* Process the Tp Rx Message */
    BlPduR_TpRxMsgManage();

#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
    /* Check if the counter is activated */
    if(m_ulMultipleIdSelectTimeout > 0U)
    {
        /* If the counter timeout select default group ID */
        if(m_ulMultipleIdSelectTimeout == 1U)
        {  /* RQD_BLPDUR_MANAGE_022 */
            /* Select the default ID group */
            BlPduR_SelectGroupID(BLPDUR_ID_GROUP_DEFAULT);
            m_ulMultipleIdSelectTimeout = 0U;
        }
        else
        {    /* RQD_BLPDUR_MANAGE_021 */
            /* decrement counter */
            m_ulMultipleIdSelectTimeout--;
        }
    }
#endif

#if (BLPDUR_NETWORK_CAN_SUPPORTED == STD_ON)
    /* CanTp Main Function RQD_BLPDUR_MANAGE_023 */
    CanTp_MainFunction();
#endif /*(BLPDUR_AUTOSAR_CAN == STD_ON)*/

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
#if (BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)
    /* Scheduler for Lin RQD_BLPDUR_MANAGE_024 */
    if (m_ubLinManageCnt == ((LIN_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubLinManageCnt = 0U;

        LIN_Manage ();
    }
    else
    {
        m_ubLinManageCnt++;
    }
#else
    LIN_Manage();
#endif /* (BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)
    /* Scheduler for Lin */ /* RQD_BLPDUR_MANAGE_025 */
    if (m_ubLtpManageCnt == ((LTP_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubLtpManageCnt = 0U;

        LTP_Manage (); /* RQD_BLPDUR_MANAGE_028 */
    }
    else
    {
        m_ubLtpManageCnt++; /* RQD_BLPDUR_MANAGE_024 RQD_BLPDUR_MANAGE_027 */
    }
#else
    LTP_Manage(); /* RQD_BLPDUR_MANAGE_026 */
#endif /* BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)*/
#endif /* (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)*/

#if (BLPDUR_USE_UDS == STD_ON)
    /* Scheduler for Diagnostic */
#if (BLPDUR_USE_UDS_MANAGE_CNT == STD_ON)
    if (m_ubDiagManageCnt >= ((UDS_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubDiagManageCnt = 0U;

        /* Diagnostic management */
        UDS_Manage ();
    }
    else
    {
        m_ubDiagManageCnt ++; /* RQD_BLPDUR_MANAGE_030 */
    }
#else
    /* Diagnostic management */
    UDS_Manage (); /* RQD_BLPDUR_MANAGE_032 */
#endif /*(BLPDUR_USE_DIAG_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_USE_UDS == STD_ON)*/


#if(BLPDUR_USE_PROG == STD_ON)
#if (BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)
    /* Scheduler for PROG */
    if (m_ubProgManageCnt >= ((PROG_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    { /* RQD_BLPDUR_MANAGE_031 */
        m_ubProgManageCnt = 0U;

        /* PROG */
        PROG_Manage(); /* RQD_BLPDUR_MANAGE_034 */
    }
    else
    {
        m_ubProgManageCnt ++; /* RQD_BLPDUR_MANAGE_033 */
    }
#else
    /* PROG management */
    PROG_Manage(); /* RQD_BLPDUR_MANAGE_035 */
#endif /*(BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_USE_PROG == STD_ON)*/

#if(BLPDUR_USE_SA == STD_ON)
#if (BLPDUR_USE_SA_MANAGE_CNT == STD_ON)
    /* Scheduler for SA */
    if (m_ubSAManageCnt >= ((SA_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubSAManageCnt = 0U;

        /* SA management */
        SA_Manage(); /* RQD_BLPDUR_MANAGE_037 */
    }
    else
    {
        m_ubSAManageCnt ++; /* RQD_BLPDUR_MANAGE_036 */
    }
#else
    /* SA management */
    SA_Manage(); /* RQD_BLPDUR_MANAGE_038 */
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_SA_PROG == STD_ON)*/

    DBG_BLPDUR_MANAGE_EXIT();

}
/*----------------------------------{end BlPduR_Manage}----------------------------*/

/*----------------------------{BlPduR_SelectGroupID}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
NCS_PRI_FCT void BlPduR_SelectGroupID(u8 ubGroupID)
{
    DBG_BLPDUR_SELECTGROUPID_ENTRY(ubGroupID);
    BLPDUR_ENTER_CRITICAL_SECTION();
    /* Check if the group ID is already known */
    if(m_ubGroupIdVal == BLPDUR_MULTIPLE_ID_NO_SEL)
    {   /* RQD_BLPDUR_MULTIPLE_ID_001 */
        /* Stop the counter for default selection */
        m_ulMultipleIdSelectTimeout = 0U;
        /* Set the group ID */
        m_ubGroupIdVal = ubGroupID;
    } /* RQD_BLPDUR_MULTIPLE_ID_002 */
    BLPDUR_EXIT_CRITICAL_SECTION();
    DBG_BLPDUR_SELECTGROUPID_EXIT();
}
#endif
/*-------------------------{end BlPduR_SelectGroupID}-----------------------------*/

/*----------------------------{CanLPduReceiveCalloutFunction}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE == STD_ON)
FUNC(boolean, COM_APPL_CODE) BlPduR_GroupIdFrameFilter(Can_HwHandleType Hrh,Can_IdType CanId,uint8 CanDlc,const uint8 *CanSduPtr)
{
    boolean RetVal;
    uint8 Idx;
    Can_IdType LocalCanID;

    DBG_BLPDUR_GROUPIDFRAMEFILTER_ENTRY(Hrh, CanId, CanDlc, CanSduPtr);

    OSC_PARAM_UNUSED(Hrh);
    OSC_PARAM_UNUSED(CanDlc);
    OSC_PARAM_UNUSED(CanSduPtr);

    RetVal = BLPDUR_FALSE;

    LocalCanID = (uint32)(CanId & 0x1FFFFFFFU);
    BLPDUR_ENTER_CRITICAL_SECTION();
    /* If the group ID is already selected */
    if (BLPDUR_MULTIPLE_ID_NO_SEL != m_ubGroupIdVal)
    {
        /* For all the ID in the active group */
        for (Idx = 0U; (Idx < stMultipleIdConfig[m_ubGroupIdVal].NumOfIdInGroup) && (RetVal == BLPDUR_FALSE); Idx++)
        {
            /* return TRUE If the ID is found */
            if (LocalCanID == stMultipleIdConfig[m_ubGroupIdVal].GroupCanIdPtr[Idx])
            {   /* RQD_BLPDUR_MULTIPLE_ID_023 */
                RetVal = BLPDUR_TRUE;
            } /* RQD_BLPDUR_MULTIPLE_ID_022 */
        } /*  RQD_BLPDUR_MULTIPLE_ID_021 */
    } /* RQD_BLPDUR_MULTIPLE_ID_020 */

#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
    /* If ID wasn't found in active group or no group were selected yet */
    if (BLPDUR_FALSE == RetVal)
    {
        /* Check if the ID is the one used to select the group ID */
        if (BLPDUR_MULTIPLE_ID_CAN_SELECT_IDENT == LocalCanID)
        {   /* RQD_BLPDUR_MULTIPLE_ID_025 */
            RetVal = BLPDUR_TRUE;
        } /* RQD_BLPDUR_MULTIPLE_ID_026 */
    } /* RQD_BLPDUR_MULTIPLE_ID_024 */
#endif

    /* In case that NM message must not be filtered */
#if ((BLPDUR_NM_MESSAGE_ENABLE == STD_ON) && (BLPDUR_NM_MESSAGE_GROUP_ENABLE == STD_OFF))
    /* If ID wasn't found in active group or */
    /* no group were selected yet and */
    /* it was not the architecture message */
    if (BLPDUR_FALSE == RetVal)
    {
        /* Check if the ID is the NM message which must not be filtered */
        if (BLPDUR_NM_MESSAGE_ID_CAN == LocalCanID)
        {   /* RQD_BLPDUR_MULTIPLE_ID_028 */
            RetVal = BLPDUR_TRUE;
        } /* RQD_BLPDUR_MULTIPLE_ID_029 */
    } /* RQD_BLPDUR_MULTIPLE_ID_030 */
#endif

    DBG_BLPDUR_GROUPIDFRAMEFILTER_EXIT(RetVal);
    BLPDUR_EXIT_CRITICAL_SECTION();
    return RetVal;
}
#endif
/*-------------------------{end CanLPduReceiveCalloutFunction}-----------------------------*/

/*----------------------------{BlPduR_ConvertRxFuncPduId}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
void BlPduR_ConvertRxFuncPduId(PduIdType * pubRxPduId)
{
    u8 LoopIndex;
    u8 IdFound = FALSE;
    BLPDUR_ENTER_CRITICAL_SECTION();
    if (BLPDUR_FUNCTIONAL == stRxPdu[*pubRxPduId].AddressingType)
    {
        for (LoopIndex=0; ((LoopIndex < (BLPDUR_MAX_RX_PDU_NUM + BLPDUR_SHARED_RX_PDU_NUM)) && (IdFound == FALSE)); LoopIndex++)
        {
            if ( *pubRxPduId == stRxPdu[LoopIndex].RxPduId)
            {
                /* Check if Pdu belong to active group */
                if (stRxPdu[LoopIndex].GroupId == m_ubGroupIdVal)
                {   /* RQD_BLPDUR_MESSAGE_001 */
                    /* Id found, Convert id */
                    *pubRxPduId = LoopIndex;
                    /* exit loop */
                    IdFound = TRUE;
                }
            } /* RQD_BLPDUR_MESSAGE_004 */
        } /* RQD_BLPDUR_MESSAGE_003 RQD_BLPDUR_MESSAGE_005 */
    }
    else
    {   /* RQD_BLPDUR_MESSAGE_002 */
        /* no translation for physical pdu */
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
}
#endif
/*-------------------------{end BlPduR_ConvertRxFuncPduId}-----------------------------*/
/*-------------------------{BlPduR_IsTcpConnectionReestablished}-------------------------------*/
#if (BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)
tBlPduRBoolean BlPduR_IsTcpConnectionReestablished(void)
{
    tBlPduRBoolean RetVal;
    PduIdType uwBlPduRTxPduId;
    PduIdType uwPduRTargetPduId;
    SoAd_SoConIdType SoConIdPtr;
    SoAd_SoConModeType ModePtr;

    DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_ENTRY();

    RetVal = BLPDUR_FALSE;

#if (PROG_BLPDUR_SUPPORT_ENABLE == STD_ON)
    /* Retrieve connection information needed to send the response */
    BlPduR_RetrieveConnectionInfo(); /* RQD_BLPDUR_CONNECTION_020 */
#endif /*(PROG_BLPDUR_SUPPORT_ENABLE == STD_ON)*/

    /* Get the transmission Pdu Id of BlPduR */
    uwBlPduRTxPduId = stPduConnection[m_ubCurrentConnection].TxPdu;

    /* Get the corresponding TargetPduId of PduR (corresponding to PduId of SoAd) */
    uwPduRTargetPduId = PduR_ConfigLayout.PduR_RTabUpTpTx[uwBlPduRTxPduId].TargetPduId;

    /* Get the socket connection Id */
    if (SoAd_GetSoConId(uwPduRTargetPduId, &SoConIdPtr) == E_OK)
    {
        /* Check if the connection mode is retrieved successfully */
        if (SoAd_GetSoConMode(SoConIdPtr, &ModePtr) == E_OK)
        {
            if (ModePtr == SOAD_SOCON_ONLINE)
            {
                RetVal = BLPDUR_TRUE; /* RQD_BLPDUR_CONNECTION_021 */
            }
        }
    }

    DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_EXIT(RetVal);
    return RetVal;
}
#endif
/*-------------------------{end BlPduR_IsTcpConnectionReestablished}-------------------------------*/
/*----------------------------{BlPduR_IsNetworkSynchronized}---------------------------*/
u8 BlPduR_IsNetworkSynchronized (u8 * frCycle)
{
    u8 returnval;
#if (STD_ON==BLPDUR_NETWORK_FLEXRAY_SUPPORTED)
    u16 frMacroTick = 0U;

    /*  RQD_BLPDUR_FLEXRAY_001 */
    if (FrIf_GetGlobalTime(FR_CCINDEX, frCycle, &frMacroTick) == E_OK)
    {
        /*Fr is Synchronized*/
        returnval=BLPDUR_E_OK;
    }
    else
    {
        /*Fr is not yet Synchronized*/
        returnval = BLPDUR_E_NOT_OK;
    }
#else
    *frCycle = FRCYCL_UNUSED;
    returnval = BLPDUR_E_OK;
#endif
    return returnval;
}
/*----------------------------{ end BlPduR_IsNetworkSynchronized}----------------------*/
/*----------------------------{BlPduR_AllSlots}----------------------------------------*/
void BlPduR_AllSlots(void)
{
#if (STD_ON==BLPDUR_NETWORK_FLEXRAY_SUPPORTED)
#if (STD_ON==BLPDUR_FRSM_ENABLEALLSLOTS)
    /* Request AllSlots mode */
    (void)FrSM_AllSlots(0U); /* RQD_BLPDUR_FLEXRAY_004 */
#endif
#endif
}
/*----------------------------{ end BlPduR_AllSlots}-----------------------------------*/

/*----------------------------{BlPduR_RxIndication}------------------------------*/
#if (((BLPDUR_MULTIPLE_ID_ENABLE == STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION))\
    || (BLPDUR_NM_MESSAGE_ENABLE == STD_ON))
FUNC(void, PDUR_CODE) BlPduR_RxIndication
(
   PduIdType RxPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{

#if ((BLPDUR_MULTIPLE_ID_ENABLE == STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION))

    u8 ubArchitectureId;
    u8 ubGroupID;
    u8 ubGroupIdx;

#endif /* ((BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)) */

    DBG_BLPDUR_RXINDICATION_ENTRY(RxPduId,PduInfoPtr);

#if ((BLPDUR_MULTIPLE_ID_ENABLE == STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION))

    /* Test if it is the Pdu Id of the architecture message */
    if (BLPDUR_MULTIPLE_ID_PDU_ID == RxPduId)
    {
        /* Initialize Id Group */
        ubGroupID = BLPDUR_MULTIPLE_ID_NO_SEL;

        /* Retrieve the architecture ID from the PDU */
        ubArchitectureId = PduInfoPtr->SduDataPtr[BLPDUR_MULTIPLE_ID_BYTE_IDX_IN_DATA];

        /* For all group ID configured */
        for(ubGroupIdx = 0U; ubGroupIdx < BLPDUR_ID_GROUP_NUM; ubGroupIdx++)
        {
            /* Check if the architecture ID is present in the group ID */
            if(stMultipleIdConfig[ubGroupIdx].ArchitectureId == ubArchitectureId)
            {   /* RQD_BLPDUR_MULTIPLE_ID_010 */
                /* Select the correct group ID */
                ubGroupID = ubGroupIdx;
            }   /* RQD_BLPDUR_MULTIPLE_ID_011 */
        }

        /* Check if Group ID is in the configured range */
        /* If not wait for a known ID */
        if (ubGroupID < BLPDUR_MULTIPLE_ID_CONF_MAX)
        {   /* RQD_BLPDUR_MULTIPLE_ID_013 */
            /* Call API to select received group ID */
            BlPduR_SelectGroupID(ubGroupID);
        }   /* RQD_BLPDUR_MULTIPLE_ID_012 */
    } /* RQD_BLPDUR_MULTIPLE_ID_031 */
#endif

#if (BLPDUR_NM_MESSAGE_ENABLE == STD_ON)
    /* Test if it is the Rx Pdu Id of the NM message */
    if (BLPDUR_NM_MESSAGE_PDU_ID == RxPduId)
    {/* RQD_BLPDUR_NM_MESSAGE_ID_001 */
#if (BLPDUR_USE_PROG == STD_ON)
        /* PduValue cast to be compatible with old prototype format */
        PROG_TpRxInd((u8)(RxPduId & 0x00FFU), BLPDUR_E_OK);
#endif
    } /* RQD_BLPDUR_NM_MESSAGE_ID_002 */
#endif


    DBG_BLPDUR_RXINDICATION_EXIT();
}
#endif
/*-------------------------{end BlPduR_RxIndication}-----------------------------*/
