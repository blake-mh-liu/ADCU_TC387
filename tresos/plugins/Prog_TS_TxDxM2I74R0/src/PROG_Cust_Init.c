/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cust_Init.c                */
/*%%  |                             |  %%  \brief PROG custom Init feature       */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 *
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to
 * void into pointer to object.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned
 * memory sections.
 *
 */
 /* NOCOV List
 *
 * NOCOV-NCS_UNITARY_TEST:
 *   code is deactivated for test.
 *
 * Reason:
 * Test are performed under WINDOWS environment.
 *
 */

/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: INT.36
 * Converting a pointer to integer or integer to pointer
 *
 * Reason:
 * This variable contains a flash memory address that will not be subject to pointer arithmetics
 * no risk of alignment issues.
 *
 * CERTC-2) Deviated Rule: EXP.36
 * Do not cast pointers into more strictly aligned pointer types
 *
 * Reason:
 * Pointer assignment was done between Integer pointer and void pointer then to an integer pointer.
 * As end conversion type Integer pointer no alignment is expected.
 *
 * CERTC-3) Deviated Rule: DCL.40
 * Do not create incompatible declarations of the same function or object
 *
 * Reason:
 * Two functions are declared to  provide two different functionalities though.
 * they are almost similar in declarations they wont be functional impact.
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))
#include "fblFrameworkPublicApi.h"
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2)) */
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
#if (PROG_DOIP_SUPPORT_ENABLE == STD_ON)
    /* Deviation CERTC-3 */
u8 m_ubDoIpRoutingActivationRequestRxConfirmation;
    /* Deviation CERTC-3 */
u8 m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack;
#endif

u8 m_ubEvenToPost; /* Contains request information */
#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
#if PROG_MULTIPLE_TP_CONNECTIONS_ENABLE == STD_ON
#define PROG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
u8 ubPBL_RxPduId;
#define PROG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>
#endif /* PROG_MULTIPLE_TP_CONNECTIONS_ENABLE == STD_ON */
#endif /* PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON */
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))
NCS_PRI_FCT void PROG_FrameWorkInit(void);
#endif
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
/*-------------------------------------------------------------------------------*/

/*----------------------------{PROG_Entry_Alive}-----------------------------*/
void PROG_Entry_Alive(void)
{
    DBG_PROG_ENTRY_ALIVE_ENTRY();
    /* Nothing to do */
    DBG_PROG_ENTRY_ALIVE_EXIT();
}
/*----------------------------{end PROG_Entry_Alive}-------------------------*/

/*----------------------------{PROG_Entry_INIT}-----------------------------*/
void PROG_Entry_INIT(void)
{
#if ((((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_5)) && (PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_OFF)) || ((PROG_IMPL_VARIANT == PROG_IMPL_90) && (PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_OFF)) || (PROG_RESET_CAUSE_ENABLE == STD_ON))
    tProgResCause ubResetCause = PROG_RESET_CAUSE_ER;
    tProgBoolean  bSendResp    = PROG_FALSE;
#endif /*(PROG_RESET_CAUSE_ENABLE == STD_ON)*/

    DBG_PROG_ENTRY_INIT_ENTRY();

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
#if (PROG_BLPDUR_NETWORK_ETH_SUPPORTED != STD_ON)
    PROG_SimulateOpenProgSession();
#endif
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_10) ||(PROG_IMPL_VARIANT == PROG_IMPL_90) */

#if (((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_5))&&(PROG_RESPOND_TO_PROG_SESSION == STD_OFF))
    /* We need to simulate the open programming session in case of JLR customer and No Response is needed from Bootloader since
     * simulate open programming session which is called from Boot Manager happens during Preinit state and it will end
     * up in endless response pending if the transition to Programming session is not handled in Init state*/
    /* Verify if a downloading request have been made in application */
    if (PROG_TRUE ==  m_ubProgNoRpdProgSession)
    {
        PROG_SimulateOpenProgSession();
    }
#endif

#if (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT)
    /* Start sleep timeout */
    m_ubBootInDefaultSession = PROG_TRUE;
    PROG_SetSleepTimeout(PROG_SLEEP_TIMEOUT);
#endif /* (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT) */

#if ( ((PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_5) || (PROG_IMPL_VARIANT == PROG_IMPL_40)) && (PROG_RESPOND_TO_PROG_SESSION == STD_ON))
    /* If an answer to Open Programming session shall be sent */
    if (PROG_TRUE == m_ubSendResponsetoOpenProgramming)
    {
        /* Send response to DSC02 */
        PROG_SendDsc02Resp();
    }
#endif
#if ((PROG_RESET_CAUSE_ENABLE == STD_ON) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_5) && (PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_OFF) || ((PROG_IMPL_VARIANT == PROG_IMPL_90) && (PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_OFF)))
    /* Get the reset cause */
    PROG_CustomGetResetCause(&ubResetCause, &bSendResp);
    /* and send response if needed */
    PROG_SendRespAfterReset(ubResetCause,bSendResp);
#endif /*(PROG_RESET_CAUSE_ENABLE == STD_ON)*/

    /* set initialization flag to true */
    m_ubProgIsInit = TRUE;

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    PROG_SecurityComputeBootChecksum();
#endif

#if (PROG_BLU_ACTIVE == STD_ON)
    if(PROG_TRUE == PROG_CustomIsBLUDownloadInProgress())
    {
        /* Simulate the open programming session request to switch the session
        from Default to the Programming and go to the Programming Session state */
        PROG_SimulateOpenProgSessionNoResponse();
    }
#endif /* (PROG_BLU_ACTIVE == STD_ON) */

    DBG_PROG_ENTRY_INIT_EXIT();
}
/*----------------------------{end PROG_Entry_INIT}-------------------------*/

/*----------------------------{PROG_Exit_INIT}-----------------------------*/
void PROG_Exit_INIT(void)
{
    DBG_PROG_EXIT_INIT_ENTRY();
#if (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT)
    /* Stop sleep timeout */
    PROG_SetSleepTimeout(0U);
    m_ubBootInDefaultSession = PROG_FALSE;
#endif /* (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT) */
    DBG_PROG_EXIT_INIT_EXIT();
}
/*----------------------------{end PROG_Entry_INIT}-------------------------*/

#if PROG_PRE_INIT_ENABLE == STD_ON
/*----------------------------{PROG_Entry_PreInit}-----------------------------*/
void PROG_Entry_PreInit(void)
{
#if (((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_90) ||(PROG_IMPL_VARIANT == PROG_IMPL_91)) && \
    ((!defined(NCS_UNITARY_TEST)) || (((defined(NCS_UNITARY_TEST)) && (!defined(EB_INTEGRATION_TEST))) && (PROG_IMPL_VARIANT != PROG_IMPL_10) && (PROG_IMPL_VARIANT != PROG_IMPL_90) && (PROG_IMPL_VARIANT != PROG_IMPL_91))))
    u32 ulIdx;
#if((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    u32 ulSegIdx;
    u32 ulsize;
#endif
    u8* pubAddress;
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)) */

#if ((PROG_RESET_CAUSE_ENABLE == STD_ON) && (PROG_BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON))
    tProgResCause ubResetCause  = 0xFFU;
    tProgBoolean  ubSendResp    = PROG_FALSE;
#endif /*((PROG_RESET_CAUSE_ENABLE == STD_ON) && (PROG_BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON))*/

    DBG_PROG_ENTRY_PREINIT_ENTRY();

#if (PROG_IMPL_VARIANT == PROG_IMPL_1)
    /* Deviation MISRAC2012-2 */
    /* Deviation CERTC-2 */
    pulProgFramework_Api_Array_Ptr = getFunctionPointerListAddressOfOemBoot();
#endif
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    #if ((!defined(NCS_UNITARY_TEST)) || (((defined(NCS_UNITARY_TEST)) && (!defined(EB_INTEGRATION_TEST))) && (PROG_IMPL_VARIANT != PROG_IMPL_10)&& (PROG_IMPL_VARIANT != PROG_IMPL_90) && (PROG_IMPL_VARIANT != PROG_IMPL_91)))
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
#if(PROG_IMPL_VARIANT == PROG_IMPL_90)
    /* reset SBL area to 0 */
    for(ulSegIdx = 0U; ulSegIdx < PROG_SEGMENT_NB; ulSegIdx++)
    {
        /* Deviation MISRAC2012-1 */
        pubAddress = (u8*)stConfigSegment[ulSegIdx].ulStartAddress;
        ulsize = ((stConfigSegment[ulSegIdx].ulEndAddress - stConfigSegment[ulSegIdx].ulStartAddress) + 1U);
        for(ulIdx = 0U; ulIdx < ulsize ; ulIdx++)
        {
            pubAddress[ulIdx] = 0U;
        }
    }
#elif (PROG_IMPL_VARIANT == PROG_IMPL_91)
    /* reset HSM Partition area to 0 */
    for(ulSegIdx = 0U; ulSegIdx < PROG_SEGMENT_NB; ulSegIdx++)
    {
        if(stConfigSegment[ulSegIdx].ePartitionType == PROG_HSM_PARTITION)
        {
            /* Deviation MISRAC2012-1 */
            pubAddress = (u8*)stConfigSegment[ulSegIdx].ulStartAddress;
            ulsize = ((stConfigSegment[ulSegIdx].ulEndAddress - stConfigSegment[ulSegIdx].ulStartAddress) + 1U);
            for(ulIdx = 0U; ulIdx < ulsize ; ulIdx++)
            {
                pubAddress[ulIdx] = 0U;
            }
        }
    }
#else
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    pubAddress = (u8*)stConfigSegment[0].ulStartAddress;

    /* reset SBL area to 0 */
    for(ulIdx = 0U; ulIdx < ((stConfigSegment[0].ulEndAddress - stConfigSegment[0].ulStartAddress) + 1U); ulIdx++)
    {
        pubAddress[ulIdx] = 0U;
    }
#endif
/* CHECK: PARSE */
#endif
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_90)) */

#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))
    PROG_FrameWorkInit();
#endif  /* (PROG_IMPL_VARIANT == PROG_IMPL_1) */

#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
#if PROG_MULTIPLE_TP_CONNECTIONS_ENABLE == STD_ON
    /*Set the CurrentRxPduId in EB*/
    EB_SetCurrentRxPdu(ubPBL_RxPduId);
#endif

    PROG_SimulateOpenProgSession();

    /* Set ECU in security level 1 at entry in SBL */
    PROG_SetSecurityLevel(1U);
#else /* PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON */

#if PROG_IMPL_VARIANT == PROG_IMPL_20
    /* Check if a SBA ticket is present and valid */
    m_ubEvenToPost = PROG_ValidateSBATicket();
#if (PROG_BLPDUR_NETWORK_ETH_SUPPORTED != STD_ON)
    PROG_HsmEmit(&PROG_HsmScPROG, m_ubEvenToPost);
#endif
#else
#if (PROG_BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)
    m_ubEvenToPost = PROG_HSM_PROG_EV_PROG_EVENT_INIT;
#if (PROG_RESET_CAUSE_ENABLE == STD_ON)
    /* Get the reset cause */
    PROG_CustomGetResetCause(&ubResetCause, &ubSendResp);
    if((ubSendResp == PROG_TRUE) && ((ubResetCause == PROG_RESET_CAUSE_ER)||(ubResetCause == PROG_RESET_CAUSE_DSC01)||(ubResetCause == PROG_RESET_CAUSE_BLU)))
    {
        m_ubSendResponseafterReset = PROG_TRUE;
    }
#endif
#else
    /*Go directly to init state*/
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_INIT);
#endif
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_20 */
#endif

#if ( (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT) && ( (PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_20)))
    /* Start sleep timeout */
    m_ubBootInDefaultSession = PROG_TRUE;
    PROG_SetSleepTimeout(PROG_SLEEP_TIMEOUT);
#endif /* (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT) */

    DBG_PROG_ENTRY_PREINIT_EXIT();
}
/*----------------------------{end PROG_Entry_PreInit}-------------------------*/

/*----------------------------{PROG_FrameWorkInit}-----------------------------*/
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))
NCS_PRI_FCT void PROG_FrameWorkInit(void)
{
    u8 ubIdx;
    u32* pulAddress;
    u8 ubBaseIdx;
#ifndef NCS_UNITARY_TEST
    tpulGetAddress pfulGetStartErase = (tpulGetAddress)pulProgFramework_Api_Array_Ptr[15]; /*Address of getEraseAreaStartAddressBySwPartId Api*/
    tpulGetAddress pfulGetEndErase = (tpulGetAddress)pulProgFramework_Api_Array_Ptr[16]; /*Address of getEraseAreaEndAddressBySwPartId Api*/
    tpulGetAddress pfulGetStartReprog = (tpulGetAddress)pulProgFramework_Api_Array_Ptr[17]; /*Address of getProgramAreaStartAddressBySwPartId Api*/
    tpulGetAddress pfulGetEndReprog = (tpulGetAddress)pulProgFramework_Api_Array_Ptr[18]; /*Address of getProgramAreaEndAddressBySwPartId Api*/
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_1)
    ubBaseIdx = 1U;
#else /* PROG_IMPL_VARIANT == PROG_IMPL_2 */
    ubBaseIdx = 0U;
#endif

    for(ubIdx = 0U; ubIdx < 2U; ubIdx++)
    {
#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetStartErase(ubIdx,PROG_FRAMEWORK_PARTID_1);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getEraseAreaStartAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_1);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx].ulEraseStartAddress = (tProgAddressType)pulAddress;
        }

#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetEndErase(ubIdx,PROG_FRAMEWORK_PARTID_1);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getEraseAreaEndAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_1);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx].ulEraseEndAddress = (tProgAddressType)pulAddress;
        }

#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetStartReprog(ubIdx,PROG_FRAMEWORK_PARTID_1);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getProgramAreaStartAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_1);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx].ulStartAddress = (tProgAddressType)pulAddress;
        }

#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetEndReprog(ubIdx,PROG_FRAMEWORK_PARTID_1);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getProgramAreaEndAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_1);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx].ulEndAddress = (tProgAddressType)pulAddress;
        }
    }

    for(ubIdx = 0U; ubIdx < 2U; ubIdx++)
    {
#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetStartErase(ubIdx,PROG_FRAMEWORK_PARTID_2);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getEraseAreaStartAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_2);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx + 2U].ulEraseStartAddress = (tProgAddressType)pulAddress;
        }

#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetEndErase(ubIdx,PROG_FRAMEWORK_PARTID_2);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getEraseAreaEndAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_2);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx + 2U].ulEraseEndAddress = (tProgAddressType)pulAddress;
        }

#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetStartReprog(ubIdx,PROG_FRAMEWORK_PARTID_2);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getProgramAreaStartAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_2);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx + 2U].ulStartAddress = (tProgAddressType)pulAddress;
        }

#ifndef NCS_UNITARY_TEST
        pulAddress = pfulGetEndReprog(ubIdx,PROG_FRAMEWORK_PARTID_2);
#else
        /* Deviation MISRAC2012-2 */
        /* Deviation CERTC-2 */
        pulAddress = getProgramAreaEndAddressBySwPartId(ubIdx,PROG_FRAMEWORK_PARTID_2);
#endif
        if(pulAddress != NULL_PTR)
        {
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            stConfigSegment[ubIdx + ubBaseIdx + 2U].ulEndAddress = (tProgAddressType)pulAddress;
        }
    }
}
#endif /* #if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_1)) */
/*----------------------------{end PROG_FrameWorkInit}-------------------------*/
#endif /* PROG_PRE_INIT_ENABLE == STD_ON */

#if PROG_PRE_INIT_ENABLE == STD_ON
/*----------------------------{PROG_PreInit}-----------------------------*/
void PROG_PreInit(void)
{
#if(PROG_BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)
#if (((PROG_RESPOND_TO_PROG_SESSION == STD_ON) || (PROG_RESET_CAUSE_ENABLE == STD_ON)) && ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_5) || (PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_5) || (PROG_IMPL_VARIANT == PROG_IMPL_10) ||(PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_40)))
    tProgResCause ubResetCause = PROG_RESET_CAUSE_ER;
    tProgBoolean  bSendResp    = PROG_FALSE;
#endif
#endif

#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
    u8 ubfrCycle = 0U;
    DBG_PROG_PREINIT_ENTRY();
if(EB_TRUE==EB_IsNetworkSynchronized(&ubfrCycle))
{
    /* Activate AllSlots mode (FlexRay only) */
    EB_AllSlots();
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_SBL_SYNCH);
}
#elif (PROG_BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)
    DBG_PROG_PREINIT_ENTRY();
#if (((PROG_RESPOND_TO_PROG_SESSION == STD_ON) || (PROG_RESET_CAUSE_ENABLE == STD_ON)) && ((PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_5) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_5) || (PROG_IMPL_VARIANT == PROG_IMPL_10) ||(PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_40)))
    /* If an answer to Open Programming session shall be sent */
    /* wait that the socket is connected */
#if((PROG_IMPL_VARIANT != PROG_IMPL_60) && (PROG_IMPL_VARIANT != PROG_IMPL_20))
    PROG_CustomGetResetCause(&ubResetCause, &bSendResp);
#endif
    if ((PROG_TRUE == m_ubSendResponsetoOpenProgramming)
#if((PROG_IMPL_VARIANT != PROG_IMPL_60) && (PROG_IMPL_VARIANT != PROG_IMPL_20))
        || (ubResetCause == PROG_RESET_CAUSE_BLU)
#endif
    )
    {
#if (PROG_DOIP_SUPPORT_ENABLE == STD_ON)
        /* wait that the Routine Activation is confirmed */
        if ((m_ubDoIpRoutingActivationRequestRxConfirmation == TRUE) || (m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack == TRUE) )
        {
            /* Event to send the response for Programming request */
            PROG_HsmEmit(&PROG_HsmScPROG, m_ubEvenToPost);
        }
#else
        if (BlPduR_IsTcpConnectionReestablished() == BLPDUR_TRUE)
        {
            /* Event to send after SBA ticket validation or not */
            PROG_HsmEmit(&PROG_HsmScPROG, m_ubEvenToPost);
        }
#endif
    }
    /* If an answer to Default session or ECU reset session shall be sent */
    /* wait that the socket is connected */
#if (PROG_RESET_CAUSE_ENABLE == STD_ON)
    else if (PROG_TRUE == m_ubSendResponseafterReset)
    {
#if (PROG_DOIP_SUPPORT_ENABLE == STD_ON)
        /* wait that the Routine Activation is confirmed */
          if ((m_ubDoIpRoutingActivationRequestRxConfirmation == TRUE) || (m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack == TRUE) )
        {
            /* Event to send the response for ECU reset or default session reset*/
            PROG_HsmEmit(&PROG_HsmScPROG, m_ubEvenToPost);
        }
#endif /*(PROG_DOIP_SUPPORT_ENABLE == STD_ON)*/
    }
#endif
    /* If no answer to Open Programming session shall be sent */
    /* Post the event to go out of PRE_INIT state */
    else
    {
        /* Event to send after SBA ticket validation or not */
        PROG_HsmEmit(&PROG_HsmScPROG, m_ubEvenToPost);
    }
#else
    DBG_PROG_PREINIT_ENTRY();
    /* Post the event to go out of PRE_INIT state */
    PROG_HsmEmit(&PROG_HsmScPROG, m_ubEvenToPost);
#endif  /*((PROG_RESPOND_TO_PROG_SESSION == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_40)))*/
#endif  /*(PROG_BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)*/
    DBG_PROG_PREINIT_EXIT();
}
#endif /* PROG_PRE_INIT_ENABLE == STD_ON */
/*----------------------------{end PROG_PreInit}-------------------------*/

