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
/*%%   _____________________________   %%  \file PROG_Cust_SBL.c                 */
/*%%  |                             |  %%  \brief PROG custom SBL feature        */
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
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any other type
 *
 *   Reason:
 * Conversion is made specific to the project, will not have any impact.
 *
 * MISRAC2012-2) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 *
 *
 * MISRAC2012-3) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to
 * void into pointer to object.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned
 * memory sections.
 *
 * MISRAC2012-4) Deviated Rule: 8.4 (advisory)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined.
 *
 * Reason:
 * This variable need to be used in test environment
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
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))
#include "fblFrameworkPublicApi.h"
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2)) */

#include "board.h"
#if PROG_WATCHDOG_ENABLE == STD_ON
#include "Watchdog.h"
#endif
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#if PROG_ACTIVE_SBL_ENABLE == STD_ON
NCS_PRI_FCT ptSBL_StartUp_Code pSBL_StartUp_Code; /* Function Pointer to SBL start*/
NCS_PRI_VAR u32 m_ulSBLInfo;
#endif /* PROG_ACTIVE_SBL_ENABLE == STD_ON */
#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
NCS_PRI_VAR u8 m_aubActivateRoutineResponse[5];
#endif

#if PROG_SBL_HEADER_DEFINE == STD_ON
#define PROG_SBL_VALIDITY_START_SEC_CONST_8
#include <MemMap.h>
/* Deviation MISRAC2012-4 */
NCS_PRI_VAR const u32 m_ulSBLValidityFlag = PROG_SBL_VALIDITY_FLAG;
#define PROG_SBL_VALIDITY_STOP_SEC_CONST_8
#include <MemMap.h>

#if (PROG_SBL_HEADER_DEFINE == STD_ON)
#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
/* Deviation MISRAC2012-1 */
#define PROG_FLASH_PAGE_ADR (t_PROG_fctptr)&PROG_FlashPage
#else
#define PROG_FLASH_PAGE_ADR NULL_PTR
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_2) */
#endif /* (PROG_SBL_HEADER_DEFINE == STD_ON) */


#define PROG_SBL_HEADER_START_SEC_CONST_8
#include <MemMap.h>
/* Deviation MISRAC2012-4 */
volatile const t_secondary_bootloader_interface m_stSBLHeader =
                            {
                                PROG_SBL_SOFTWARE_VERSION, /* Software version */
                                {0x32U, 0x31U, 0x54U, 0x30U, 0x39U, 0x33U, 0x49U, 0x41U, 0x31U, 0x31U, 0x31U, 0x31U, 0x32U, 0x32U, 0x32U, 0x34U},
                                /* Deviation MISRAC2012-1 */
                                {NULL_PTR, PROG_FLASH_PAGE_ADR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR,
                                /* Deviation MISRAC2012-3 */
                                NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                                /* Deviation MISRAC2012-2 */
                                /* Deviation CERTC-1 */
                                (u32)&m_ulSBLValidityFlag
                            };
#define PROG_SBL_HEADER_STOP_SEC_CONST_8
#include <MemMap.h>
#endif

#if PROG_ACTIVE_SBL_ENABLE == STD_ON
#define PROG_SBL_HEADER_START_SEC_CONST_8
#include <MemMap.h>
#ifndef NCS_UNITARY_TEST
volatile const t_secondary_bootloader_interface m_stSblHeaderAddr = {0U}; /* Variable located at address of SBL Header */
#else
/* Remove const for unit test */
t_secondary_bootloader_interface m_stSblHeaderAddr; /* Variable located at address of SBL Header */
u32 m_ulAddrSBLValidityFlagAddr; /* Variable located at address of SBL Header */
#endif
#define PROG_SBL_HEADER_STOP_SEC_CONST_8
#include <MemMap.h>
#if  ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10)|| (PROG_IMPL_VARIANT == PROG_IMPL_90))
/* Variable located at address of PBL version info*/
/* Deviation MISRAC2012-4 */
NCS_PRI_VAR const u8 m_aubPblVersInfo[16] =    {0x32U, 0x31U, 0x54U, 0x30U, 0x39U, 0x33U, 0x49U, 0x41U,
                                                0x31U, 0x31U, 0x31U, 0x31U, 0x32U, 0x32U, 0x32U, 0x34U};
#endif
#endif /* #if PROG_ACTIVE_SBL_ENABLE == STD_ON */
/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
#define PROG_SBL_REF_STRING_OFF  4U

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
#if PROG_ACTIVE_SBL_ENABLE == STD_ON
/** \brief called to get information for SBL
 **
 ** This function is called to get information that shall be passed to SBL
 ** during SBL jump
 **/
NCS_PRI_FCT tProgStatus PROG_GetSBLInfo(void);
/** \brief called to check the SBL compatibility
 **
 ** This function is called to check the SBL compatibility
 ** during SBL jump
 **
 ** \param[in] pubRefStringPBL pointer to PBL data
 **
 **/
NCS_PRI_FCT tProgStatus PROG_CheckSBLCompatibility(const u8 *pubRefStringPBL);
#endif

#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
/** \brief called to transmit the SBL jump response  **/
NCS_PRI_FCT void PROG_TransmitActiveSBLResponse(void);
#endif
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */


/*---------------------------{PROG_Entry_ActiveSBL}-----------------------------*/
void PROG_Entry_ActiveSBL(void)
{
    DBG_PROG_ENTRY_ACTIVESBL_ENTRY();
#if PROG_ACTIVE_SBL_ENABLE == STD_ON
    /*Send NRC78 response*/
    UDS_StopNRC78Timer();
#endif /* PROG_ACTIVE_SBL_ENABLE == STD_ON */
    DBG_PROG_ENTRY_ACTIVESBL_EXIT();
}
/*--------------------------{End PROG_Entry_ActiveSBL}---------------------------*/

/*---------------------------{PROG_JumpToSBL}-----------------------------*/
void PROG_JumpToSBL(void)
{
#if PROG_ACTIVE_SBL_ENABLE == STD_ON
    u32 ulAddressSBL;
    tProgStatus ubSBLAddressCheck;
#if PROG_MULTIPLE_TP_CONNECTIONS_ENABLE == STD_ON
    u8 ubCurrentRxPduId;
#endif

    DBG_PROG_JUMPTOSBL_ENTRY();

    /*Get SBLaddress*/
#if (PROG_IMPL_VARIANT == PROG_IMPL_3)
    ulAddressSBL = PROG_CustomGetSBLStartAddress();
#else
    ulAddressSBL = PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[4U]);
#endif
    /*Checking Correct SBL Start Address*/
    ubSBLAddressCheck = PROG_CustomCheckSBLStartAddress(ulAddressSBL);
    if(ubSBLAddressCheck == PROG_E_OK)
    {
        /* Deviation MISRAC2012-1 */
        /* Deviation CERTC-1 */
        pSBL_StartUp_Code = (ptSBL_StartUp_Code)ulAddressSBL;

#if (PROG_BLPDUR_SUPPORT_ENABLE == STD_ON)
        /* store the active connection to provide response from the Target SW using the same connection(For BL-3) */
        BlPduR_StoreConnectionInfo();
#endif /*(PROG_BLPDUR_SUPPORT_ENABLE == STD_ON)*/

#if PROG_MULTIPLE_TP_CONNECTIONS_ENABLE == STD_ON
        EB_GetCurrentRxPdu(&ubCurrentRxPduId);
#endif

        /* Stop all communications on the network */
        EB_Com_Deactivate();

#if PROG_WATCHDOG_ENABLE == STD_ON
        /* Triger watchdog before jumping in SBL */
        Watchdog_Trigger();
#endif

        /* Disable interrupt  before the jump */
        (void) BoardDisableInterrupts();
        /* jump in SBL*/
#if PROG_MULTIPLE_TP_CONNECTIONS_ENABLE == STD_ON
        pSBL_StartUp_Code(m_ulSBLInfo, ubCurrentRxPduId);
#else
        pSBL_StartUp_Code(m_ulSBLInfo);
#endif
    }
    else
    {
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
        m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_FINISHED_NOK|PROG_ROUTINE_TYPE_1);
        UDS_LongRequestEnd(5U, m_stDiagMessageInfo.pubTxData, UDS_ACK);
#else
        UDS_LongRequestEnd(3U, m_stDiagMessageInfo.pubTxData, UDS_NRC_22);
#endif
    }
#else
    DBG_PROG_JUMPTOSBL_ENTRY();
#endif /* PROG_ACTIVE_SBL_ENABLE == STD_ON */

    DBG_PROG_JUMPTOSBL_EXIT();
}
/*---------------------------{End PROG_JumpToSBL}-----------------------------*/


/*----------------------------{PROG_Entry_SblSynch}-----------------------------*/
void PROG_Entry_SblSynch(void)
{
    DBG_PROG_ENTRY_SBLSYNCH_ENTRY();
#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT == PROG_IMPL_11) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    PROG_TransmitActiveSBLResponse();
#endif /*( PROG_IMPL_VARIANT == PROG_IMPL_11) || (PROG_IMPL_VARIANT == PROG_IMPL_91)*/
#endif /* PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON    */
    DBG_PROG_ENTRY_SBLSYNCH_EXIT();
}
/*----------------------------{end PROG_Entry_SblSynch}-------------------------*/

/*-------------------------------{PROG_TransmitActiveSBLResponse}-------------------------------*/
#if PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON
NCS_PRI_FCT void PROG_TransmitActiveSBLResponse(void)
{
#if ((PROG_IMPL_VARIANT == PROG_IMPL_11)|| (PROG_IMPL_VARIANT == PROG_IMPL_91))
  PduLengthType ulLen;


  ulLen = 5U;
  /* transmit SBL active response */
  m_aubActivateRoutineResponse[0] = 0x71;
  m_aubActivateRoutineResponse[1] = 0x01;
  m_aubActivateRoutineResponse[2] = 0x03;
  m_aubActivateRoutineResponse[3] = 0x01;
  m_aubActivateRoutineResponse[4] = (u8)(PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);
  (void)EB_Send_TPFrame( (u16)ulLen, m_aubActivateRoutineResponse);
#endif

}
#endif /* PROG_ACTIVE_SBL_RESPONSE_ENABLE == STD_ON */
/*----------------------------{end PROG_TransmitActiveSBLResponse}--------------------------------*/

/*---------------------------{PROG_ActiveSBL_Check}-----------------------------*/

tProgStatus PROG_ActiveSBL_Check(void)
{
    tProgStatus eProgStatus;

    DBG_PROG_ACTIVESBL_CHECK_ENTRY();

#if (PROG_ACTIVE_SBL_ENABLE == STD_ON)

    /* Check if SBL headr is present */
    eProgStatus = PROG_GetSBLInfo();

    if (PROG_E_NOT_OK == eProgStatus)
    {
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
        m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_FINISHED_NOK|PROG_ROUTINE_TYPE_1);
        UDS_LongRequestEnd(5U, m_stDiagMessageInfo.pubTxData, UDS_ACK);
#else
        UDS_LongRequestEnd(3U, m_stDiagMessageInfo.pubTxData, UDS_NRC_22);
#endif
    }
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
    /* Check if the SBL check memory is a success. If not, send routine status not ok */
    else
    {
      if(PROG_E_NOT_OK == m_ubSblVerficationStatus)
      {
        m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_FINISHED_NOK|PROG_ROUTINE_TYPE_1);
        UDS_LongRequestEnd(5U, m_stDiagMessageInfo.pubTxData, UDS_ACK);
        eProgStatus = PROG_E_NOT_OK;
      }
    }
#endif
#else
    /* Activate SBL is not supported in the current BL variant */
    eProgStatus = PROG_E_NOT_OK;
    UDS_LongRequestEnd(3U, m_stDiagMessageInfo.pubTxData, UDS_NRC_31);
#endif

    DBG_PROG_ACTIVESBL_CHECK_EXIT(eProgStatus);

    return eProgStatus;
}

/*---------------------------{End PROG_ActiveSBL_Check}-----------------------------*/

/*----------------------------{PROG_GetSBLInfo}-------------------------*/
#if PROG_ACTIVE_SBL_ENABLE == STD_ON
NCS_PRI_FCT tProgStatus PROG_GetSBLInfo(void)
{
    tProgStatus eProgStatus;
#if (PROG_IMPL_VARIANT == PROG_IMPL_1)
    u32* pulSBLLocalInfo;
    u8* pubRefStringPBL;
#endif
    u32 volatile const * pulSBLValidityInfo;
    u32 *pulSBLValidityFlag;

    pulSBLValidityInfo = (u32 volatile const *)(&m_stSblHeaderAddr.ulSBLValidityFlagAddr);

    /* Check if the address to check the SBL validity flag is not NULL_PTR */
    if(*pulSBLValidityInfo != 0x00000000U)
    {
        /* Deviation MISRAC2012-2 */
         /* Deviation CERTC-1 */
        pulSBLValidityFlag = (u32*)*pulSBLValidityInfo;
        /* Check if the validity flag is set */
        if(*pulSBLValidityFlag == PROG_SBL_VALIDITY_FLAG)
        {
#if (PROG_IMPL_VARIANT == PROG_IMPL_1)
            setSblRamAddress(&m_stSblHeaderAddr);
            /* Deviation MISRAC2012-3 */
           /* Deviation CERTC-2 */
            pulSBLLocalInfo = getFunctionPointerListAddressOfOemBoot();

            /* Deviation MISRAC2012-2 */
           /* Deviation CERTC-1 */
            m_ulSBLInfo = (u32) pulSBLLocalInfo;
            /* Deviation MISRAC2012-3 */
            pubRefStringPBL = getOemBootRefStringAddress();

            eProgStatus = PROG_CheckSBLCompatibility(pubRefStringPBL);
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_1) */
#if ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_90))
            m_ulSBLInfo = 0U;

            eProgStatus = PROG_CheckSBLCompatibility(m_aubPblVersInfo);
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_10)|| (PROG_IMPL_VARIANT == PROG_IMPL_90)) */
        }
        else
        {
            eProgStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    return eProgStatus;
}
#endif /* PROG_ACTIVE_SBL_ENABLE == STD_ON */
/*----------------------------{end PROG_GetSBLInfo}---------------------*/

/*----------------------------{PROG_CheckSBLCompatibility}-------------------------*/
#if PROG_ACTIVE_SBL_ENABLE == STD_ON
NCS_PRI_FCT tProgStatus PROG_CheckSBLCompatibility(const u8 *pubRefStringPBL)
{
    tProgStatus eProgStatus;

    eProgStatus = PROG_E_OK;

    /* Check µc compatibility */
    if (m_stSblHeaderAddr.referenceString[0] != pubRefStringPBL[0])
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    /* Check HW version compatibility */
    if (m_stSblHeaderAddr.referenceString[1] != pubRefStringPBL[1])
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    /* Check application compatibility */
    if (m_stSblHeaderAddr.referenceString[2] != pubRefStringPBL[2])
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    /* Check customer compatibility */
    if (m_stSblHeaderAddr.referenceString[3] != pubRefStringPBL[3])
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    /* Check OEM-ID compatibility */
    if (m_stSblHeaderAddr.referenceString[4] != pubRefStringPBL[4])
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    /* Check project number compatibility */
    if (m_stSblHeaderAddr.referenceString[5] != pubRefStringPBL[5])
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    return eProgStatus;
}
#endif /* PROG_ACTIVE_SBL_ENABLE == STD_ON */
/*----------------------------{end PROG_CheckSBLCompatibility}---------------------*/
