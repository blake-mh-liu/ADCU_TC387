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
/*%%   _____________________________   %%  \file PROG_Impl_80.c                  */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2019 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 */
/* NOCOV List
 *
 *
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include "PROG_Decomp.h"

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

#if (PROG_IMPL_VARIANT == PROG_IMPL_80)

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

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/* Indicates the logical marker extracted from Erase or RD */
u8 m_ubLogicalMarker;
/* Read data buffer */
u8 m_aubReadDataBuffer[PROG_IMPL80_MAX_WRITTEN_DATA_NBR];
/* Data buffer to write */
u8 m_aubWriteDataBuffer[PROG_IMPL80_MAX_WRITTEN_DATA_NBR];
/* Error type in self-check */
u8 m_ubErrorType;
/* Define the size of each downloaded segment */
u32 m_aulDownloadedSegSize[PROG_SEGMENT_NB];
/* Tool signature stored in RAM */
u16 m_uwToolSignature;
/* Routine identifier */
u16 m_uwRoutineId;
/* Structures of programming flags */
tProgrammingFlags m_stProgrammingFlags;
/* List of request routine result flags */
u8 m_aubRequestRoutineResult[PROG_ROUTINE_RESULT_NB];
/* Buffer used to store received RC buffer */
tProgRequestRoutineData  m_stRequestRoutineData;
/* CRC16 value for application and calibration */
NCS_PRI_VAR u16 m_auwCrcValue;

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/** \brief Allows to compute the inversed CRC16 (reverse of CCITT)
 **
 ** \param[in] aubData data request
 ** \param[in] uwLen UDS status
 ** \param[in] uwCrcInit preset value of the CRC
 **
 ** \return Reverse CRC value
 **
 **/
NCS_PRI_FCT u16 PROG_CalculateInversedCrc16_Impl80(const u8 *aubData, u16 uwLen, const u16 uwCrcInit);

#if PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON
/** \brief Allows to verify the compliance of RD parameters
 **
 ** \param[in] pubUdsData data request
 ** \param[in/out] eUdsStatus UDS status
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Check succeed
 ** \retval PROG_E_NOT_OK  Check failed
 **
 **/
NCS_PRI_FCT tProgStatus PROG_ControlRDParameters_Impl80(const u8 * pubUdsData, tUdsStatus * eUdsStatus);
#endif /* PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/** \brief Allows to verify the compliance of TD parameters for key appli
 **
 ** \param[in] pubUdsData data request
 ** \param[in] ulLength length of the buffer
 **
 ** \return void
 **
 **/
NCS_PRI_FCT void PROG_ControlKeyAppliWritingParameters_Impl80(const u8 * pubUdsData, u16 ulLength);

/** \brief Allows to verify the compliance of TD parameters for data writing
 **
 ** \param[in] pubUdsData data request
 ** \param[in] ulLength length of the buffer
 **
 ** \return void
 **
 **/
NCS_PRI_FCT void PROG_ControlDataWritingParameters_Impl80(const u8 * pubUdsData, u16 ulLength);

/** \brief Allows to verify the compliance of TD parameters for log zone
 **
 ** \param[in] pubUdsData data request
 ** \param[in] ulLength length of the buffer
 **
 ** \return void
 **
 **/
NCS_PRI_FCT void PROG_ControlZIWritingParameters_Impl80(const u8 * pubUdsData, u16 ulLength);

/** \brief Check the write status of the current operation
 **
 ** \param[in] eProgStatus job status
 **
 ** \return void
 **
 **/
NCS_PRI_FCT void PROG_WriteStatusCheck_Impl80(tProgStatus eProgStatus);

/** \brief Allows to verify the consistency of address and size during TD
 **
 ** \param[in] ulStartAddress address where write
 ** \param[in] ulDataSize size of data to write
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Check succeed
 ** \retval PROG_E_NOT_OK  Check failed
 **
 **/
NCS_PRI_FCT tProgStatus PROG_AddressSizeConsistencyCheck(tProgAddressType ulStartAddress, u32 ulDataSize);

#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

/** \brief Allows to compare byte by byte the written data
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Check succeed
 ** \retval PROG_E_NOT_OK  Check failed
 **
 **/
NCS_PRI_FCT tProgStatus PROG_CompareByteByByte_Impl80(void);

/** \brief Allows to retrieve the index of the routine control in the status table
 **
 ** \param[in] uwRoutineId routine identifier
 ** \param[in/out] ubTableRtneIndex routine index in the status table
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Index found
 ** \retval PROG_E_NOT_OK  Index not found
 **
 **/
NCS_PRI_FCT tProgStatus PROG_GetLookUpIndex_Impl80(u16 uwRoutineId, u8 *ubTableRtneIndex);

/** \brief Allows to get the status of the routine control
 **
 ** \param[in] uwRoutineId routine identifier
 **
 ** \return Result of treatment
 ** \retval INIT  Routine in initialization status
 ** \retval PENDING  Routine is pending
 ** \retval SUCCESS  Routine is successful
 ** \retval FAIL  Routine is failed
 **
 **/
NCS_PRI_FCT u8 PROG_GetRoutineResult_Impl80(u16 uwRoutineId);

/** \brief Allows to manage the data to write during TD of application and/or calibration **/
NCS_PRI_FCT void PROG_AppCalibWriteCheck_Impl80(void);

/** \brief Allows to get the segment information
 **
 ** \param[in]  ubLogicMarker logical marker
 ** \param[out] pstSegment segment structurer
 **
 ** \return void
 **
 **/
NCS_PRI_FCT void PROG_GetBlockInfos_Impl80(u8 ubLogicMarker, tSegmentType * pstSegment);
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*------------------------{PROG_Init_Impl80}--------------------------*/
void PROG_Init_Impl80(void)
{
    u16 uwIdx;

    m_uwToolSignature = 0x0000U;
    m_ubErrorType     = 0x00U;

    /* Initialize flags and tokens */
    m_stProgrammingFlags.ubWriteOk      = PROG_TRUE;
    m_stProgrammingFlags.ubProgInit     = PROG_FALSE;
    m_stProgrammingFlags.ubTunBlank     = PROG_FALSE;
    m_stProgrammingFlags.ubGlobalBlank  = PROG_FALSE;
    m_stProgrammingFlags.ubAuthorizeLog = PROG_FALSE;
    m_stProgrammingFlags.ubRDOk         = PROG_FALSE;
    m_stProgrammingFlags.ubRDLogOk      = PROG_FALSE;
    m_stProgrammingFlags.ubRDKeyAppliOk = PROG_FALSE;
    m_stProgrammingFlags.ubLCBaudOk     = PROG_FALSE;
    m_stProgrammingFlags.ubLCProgOk     = PROG_FALSE;

    /* Reset buffer used for writing */
    for (uwIdx = 0U; uwIdx < PROG_IMPL80_MAX_WRITTEN_DATA_NBR; uwIdx++)
    {
        m_aubWriteDataBuffer[uwIdx] = 0xFF;
    }
    /* Initialize segment's size */
    for (uwIdx = 0U; uwIdx < PROG_SEGMENT_NB; uwIdx++)
    {
        m_aulDownloadedSegSize[uwIdx] = 0U;
    }
    /* Initialize status of routine request */
    for (uwIdx = 0U; uwIdx < PROG_ROUTINE_RESULT_NB; uwIdx++)
    {
        m_aubRequestRoutineResult[uwIdx] = PROG_REQUEST_ROUTINE_RESULT_INIT;
    }
}
/*-------------------------{end PROG_Init_Impl80}---------------------------*/

#if PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON
/*------------------------{PROG_Entry_RD_Impl80}--------------------------*/
void PROG_Entry_RD_Impl80(void)
{
    tUdsStatus eUdsStatus;
    tProgStatus eProgStatus;

    /* Reset all variable of TD */
    m_stWriteInfo.ulDataToBeWritten   = 0U;
    m_stWriteInfo.ulWriteLength       = 0U;
    m_stWriteInfo.ulWrittenData       = 0U;
    m_stWriteInfo.ulAddressToWrite    = 0x00000000U;
    m_stWriteInfo.ulNewAddressToWrite = 0x00000000U;

    m_stPageBuffer.ulOldDataLength = 0U;

    m_stReprogInfo.ubBlockSequenceCounter = 1U;

    eProgStatus = PROG_ControlRDParameters_Impl80(&m_stDiagMessageInfo.pubData[1], &eUdsStatus);

    if (PROG_E_OK == eProgStatus)
    {
        m_stDiagMessageInfo.ulLength      = PROG_RD_RESPONSE_SIZE - 1U;
        m_stDiagMessageInfo.pubTxData[1U] = PROG_IMPL80_LENGTH_FORMAT_ID;
        m_stDiagMessageInfo.pubTxData[2U] = PROG_IMPL80_MAX_NUM_BLOCK_LENGTH;
    }

    /* Send response */
    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength,
            m_stDiagMessageInfo.pubTxData, eUdsStatus);
}
/*-------------------------{end PROG_Entry_RD_Impl80}---------------------------*/
#endif /* PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON */

#if PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON
/*------------------------{PROG_ControlRDParameters_Impl80}--------------------------*/
tProgStatus PROG_ControlRDParameters_Impl80(const u8 * pubUdsData, tUdsStatus * eUdsStatus)
{
    tProgStatus eProgStatus;
    u8          ubLogicMarker;
    u8          ubALFID;
    u8          ubMemAddress;
    u8          ubMemSize;
    u8          ubIndex;

    eProgStatus = PROG_E_OK;

    ubLogicMarker = (u8)pubUdsData[0U];
    ubALFID       = (u8)pubUdsData[1U];
    ubMemAddress  = (u8)pubUdsData[2U];
    ubMemSize     = (u8)pubUdsData[3U];

    if (  (ubALFID      != 0x11U)
        ||(ubMemAddress != 0x00U)
        ||(ubMemSize    != 0x00U)
       )
    {
        eProgStatus = PROG_E_NOT_OK;
        *eUdsStatus = UDS_NRC_31;
    }

    if (PROG_E_OK == eProgStatus)
    {
        m_ubLogicalMarker = ubLogicMarker;
        switch (m_ubLogicalMarker)
        {
            /* CASE: Key Appli download */
            case PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI:
                m_stProgrammingFlags.ubRDKeyAppliOk = PROG_TRUE;
                *eUdsStatus = UDS_ACK;
                break;

            /* CASE: Calibration or application + calibration download */
            case PROG_IMPL80_LOGICAL_MARKER_CALIB:
            case PROG_IMPL80_LOGICAL_MARKER_APP_CALIB:
                eProgStatus = PROG_E_NOT_OK;
                if (PROG_IMPL80_TOOL_SIGNATURE == m_uwToolSignature)
                {
                    if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
                    {
                        for (ubIndex = 0U; ubIndex < (PROG_BLOCK_NB-1U); ubIndex++)
                        {
                            /* Set erase status to not erased as RD received for application and calibration */
                            (void)PROG_CustomSetEraseStatus(ubIndex, PROG_E_NOT_ERASED);
                        }

                        if (PROG_TRUE == m_stProgrammingFlags.ubGlobalBlank)
                        {
                            eProgStatus = PROG_E_OK;
                        }
                    }
                    else
                    {
                        PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_CALIB, &m_stCurrentSegment);
                        /* Set erase status to not erased as RD received for calibration */
                        (void)PROG_CustomSetEraseStatus(m_stCurrentSegment.ubLogicalBlockId, PROG_E_NOT_ERASED);

                        if (PROG_TRUE == m_stProgrammingFlags.ubTunBlank)
                        {
                            eProgStatus = PROG_E_OK;
                        }
                    }
                }

                if (PROG_E_OK == eProgStatus)
                {
                    m_stProgrammingFlags.ubRDOk = PROG_TRUE;
                    *eUdsStatus                 = UDS_ACK;
                }
                else
                {
                    *eUdsStatus = UDS_NRC_70;
                }
                break;

            /* CASE: ZI download */
            case PROG_IMPL80_LOGICAL_MARKER_ZI:
                if (PROG_TRUE == m_stProgrammingFlags.ubAuthorizeLog)
                {
                    m_stProgrammingFlags.ubRDLogOk = PROG_TRUE;
                    eProgStatus                    = PROG_E_OK;
                    *eUdsStatus                    = UDS_ACK;
                }
                else
                {
                    eProgStatus = PROG_E_NOT_OK;
                    *eUdsStatus = UDS_NRC_70;
                }
                break;

            default:
                eProgStatus = PROG_E_NOT_OK;
                *eUdsStatus = UDS_NRC_31;
                break;
        }
    }
    return eProgStatus;
}
/*-------------------------{end PROG_ControlRDParameters_Impl80}---------------------------*/
#endif /* PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/*------------------------{PROG_TD_Impl80}--------------------------*/
void PROG_Entry_TD_Impl80(void)
{
    PROG_TD_Impl80();
}
/*-------------------------{end PROG_TD_Impl80}---------------------------*/
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/*------------------------{PROG_TD_Impl80}--------------------------*/
void PROG_TD_Impl80(void)
{
    switch (m_ubLogicalMarker)
    {
        case PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI:
            PROG_ControlKeyAppliWritingParameters_Impl80(&m_stDiagMessageInfo.pubData[0U], m_stDiagMessageInfo.ulLength);
            break;

        case PROG_IMPL80_LOGICAL_MARKER_CALIB:
        case PROG_IMPL80_LOGICAL_MARKER_APP_CALIB:
            PROG_ControlDataWritingParameters_Impl80(&m_stDiagMessageInfo.pubData[0U], m_stDiagMessageInfo.ulLength);
            break;

        case PROG_IMPL80_LOGICAL_MARKER_ZI:
            PROG_ControlZIWritingParameters_Impl80(&m_stDiagMessageInfo.pubData[0U], m_stDiagMessageInfo.ulLength);
            break;

        default:
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
            /* Push event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
    }
}
/*-------------------------{end PROG_TD_Impl80}---------------------------*/
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/*------------------------{PROG_ControlKeyAppliWritingParameters_Impl80}--------------------------*/
NCS_PRI_FCT void PROG_ControlKeyAppliWritingParameters_Impl80(const u8 * pubUdsData, u16 ulLength)
{
    u16 uwCalculatedCrc;

    /* Check RD Key Appli flag */
    if (PROG_TRUE == m_stProgrammingFlags.ubRDKeyAppliOk)
    {
        /* Set TD received */
        m_stWriteInfo.ubTDReceived = PROG_TRUE;
        if (PROG_IMPL80_BLOCK_SEQ_COUNT_APPLI_KEY == m_stDiagMessageInfo.pubData[1U])
        {
            uwCalculatedCrc = PROG_CalculateInversedCrc16_Impl80(pubUdsData, ulLength, PROG_IMPL80_CRC_INIT_VALUE);
            /* Check calculated CRC */
            if (PROG_IMPL80_CRC_REVERSED_CCITT == uwCalculatedCrc)
            {
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
                /* Push write event PROG_EVENT_WRITE_CHECK */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE_CHECK);
            }
            else
            {
                /* Send positive response with fault CRC $0A */
                m_stDiagMessageInfo.ubDiagStatus  = UDS_ACK;
                m_stDiagMessageInfo.ulLength      = PROG_TD_RESPONSE_SIZE;
                m_stDiagMessageInfo.pubTxData[2U] = PROG_IMPL80_FAULT_CRC;

                UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength,
                                        m_stDiagMessageInfo.pubTxData,
                                        m_stDiagMessageInfo.ubDiagStatus);
            }
        }
        else
        {
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_73;
            /* Push event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
    else
    {
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_24;
        /* Push event PROG_EVENT_FAILED*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
}
/*-------------------------{end PROG_ControlKeyAppliWritingParameters_Impl80}---------------------------*/
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/*------------------------{PROG_ControlDataWritingParameters_Impl80}--------------------------*/
NCS_PRI_FCT void PROG_ControlDataWritingParameters_Impl80(const u8 * pubUdsData, u16 ulLength)
{
    tProgStatus  eProgStatus;
    tProgBoolean eProgFirstCtrlOk;
    u16          uwCalculatedCrc;
#if (PROG_PRECOND_CHECK_ENABLE == STD_ON)
    tUdsStatus   eUdsStatus;
#endif /* (PROG_PRECOND_CHECK_ENABLE == STD_ON) */
    eProgFirstCtrlOk = PROG_FALSE;

    /* Check RD flag */
    if (PROG_TRUE == m_stProgrammingFlags.ubRDOk)
    {
        /* Set TD received */
        m_stWriteInfo.ubTDReceived = PROG_TRUE;

#if (PROG_PRECOND_CHECK_ENABLE == STD_ON)
        /* Check power supply is OK */
        eProgStatus = PROG_CustCheckProgPrecond(&eUdsStatus);
        if (PROG_E_OK == eProgStatus)
#endif /* (PROG_PRECOND_CHECK_ENABLE == STD_ON) */
        {
            if (m_stReprogInfo.ubBlockSequenceCounter == m_stDiagMessageInfo.pubData[1U])
            {
                uwCalculatedCrc = PROG_CalculateInversedCrc16_Impl80(pubUdsData, ulLength, PROG_IMPL80_CRC_INIT_VALUE);
                /* Check calculated CRC */
                if (PROG_IMPL80_CRC_REVERSED_CCITT == uwCalculatedCrc)
                {
                    eProgFirstCtrlOk = PROG_TRUE;
                }
                else
                {
                    /* Send positive response with fault CRC $0A */
                    m_stDiagMessageInfo.ubDiagStatus  = UDS_ACK;
                    m_stDiagMessageInfo.ulLength      = PROG_TD_RESPONSE_SIZE;
                    m_stDiagMessageInfo.pubTxData[2U] = PROG_IMPL80_FAULT_CRC;

                    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength,
                                            m_stDiagMessageInfo.pubTxData,
                                            m_stDiagMessageInfo.ubDiagStatus);
                }
            }
            else
            {
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_73;
                /* Push event PROG_EVENT_FAILED*/
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
        }
#if (PROG_PRECOND_CHECK_ENABLE == STD_ON)
        else
        {
            m_stDiagMessageInfo.ubDiagStatus = eUdsStatus;
            /* Push event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
#endif /* (PROG_PRECOND_CHECK_ENABLE == STD_ON) */
    }
    else
    {
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_24;
        /* Push event PROG_EVENT_FAILED*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }

    if (PROG_TRUE == eProgFirstCtrlOk)
    {
        /* Retrieve start address */
        m_stWriteInfo.ulNewAddressToWrite  = (u32)m_stDiagMessageInfo.pubData[4U] & 0x000000FFU;
        m_stWriteInfo.ulNewAddressToWrite |= (u32)(((u32)m_stDiagMessageInfo.pubData[3U]) << 8U);
        m_stWriteInfo.ulNewAddressToWrite |= (u32)(((u32)m_stDiagMessageInfo.pubData[2U]) << 16U);

        m_stWriteInfo.ulNewAddressToWrite += PROG_IMPL80_BASE_ADDR;
        /* Retrieve informative data size */
        m_stWriteInfo.ulDataToBeWritten = (u32)m_stDiagMessageInfo.pubData[5U];
        m_stPageBuffer.ulNewDataLength  = 0U;

        /* Check consistency of received parameters - REQ: Gen-REPROG-ST-67 */
        eProgStatus = PROG_AddressSizeConsistencyCheck(m_stWriteInfo.ulNewAddressToWrite, m_stWriteInfo.ulDataToBeWritten);
        if (PROG_E_OK == eProgStatus)
        {
            if (PROG_TRUE == m_stProgrammingFlags.ubWriteOk)
            {
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
                /* Push event PROG_EVENT_FAILED*/
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE_CHECK);
            }
            else
            {
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
                /* Push event PROG_EVENT_FAILED*/
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
        }
        else
        {
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
            /* Push event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
}
/*-------------------------{end PROG_ControlDataWritingParameters_Impl80}---------------------------*/
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/*------------------------{PROG_ControlZIWritingParameters_Impl80}--------------------------*/
NCS_PRI_FCT void PROG_ControlZIWritingParameters_Impl80(const u8 * pubUdsData, u16 ulLength)
{
    tProgStatus eProgStatus;
    u16         uwCalculatedCrc;

    /* Check RD flag */
    if (PROG_TRUE == m_stProgrammingFlags.ubRDLogOk)
    {
        /* Set TD received */
        m_stWriteInfo.ubTDReceived = PROG_TRUE;

        if (PROG_IMPL80_BLOCK_SEQ_COUNT_ZI == m_stDiagMessageInfo.pubData[1U])
        {
            uwCalculatedCrc = PROG_CalculateInversedCrc16_Impl80(pubUdsData, ulLength, PROG_IMPL80_CRC_INIT_VALUE);
            /* Check calculated CRC */
            if (PROG_IMPL80_CRC_REVERSED_CCITT == uwCalculatedCrc)
            {
                /* Check if there is enough space for ZI writing */
                eProgStatus = PROG_CustomCheckZIAvailableSpace();
                if (PROG_E_OK == eProgStatus)
                {
                    m_stDiagMessageInfo.ubDiagStatus  = UDS_ACK;
                    /* Push write event PROG_EVENT_WRITE_CHECK */
                    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE_CHECK);
                }
                else
                {
                    /* Space not enough for writing ZI */
                    /* Set ECU status to $F0 */
                    PROG_CustomSetECUStatus(PROG_IMPL80_ECU_STATUS_END_ALIGNEMENT);
                    m_stProgrammingFlags.ubAuthorizeLog = PROG_FALSE;
                    m_uwToolSignature = 0x0000U;

                    /* Send positive response with fault CRC $08 */
                    m_stDiagMessageInfo.ubDiagStatus  = UDS_ACK;
                    m_stDiagMessageInfo.ulLength      = PROG_TD_RESPONSE_SIZE;
                    m_stDiagMessageInfo.pubTxData[2U] = PROG_IMPL80_NO_MORE_SPACE_AVAILABLE;

                    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength,
                                            m_stDiagMessageInfo.pubTxData,
                                            m_stDiagMessageInfo.ubDiagStatus);
                }
            }
            else
            {
                /* Send positive response with fault CRC $0A */
                m_stDiagMessageInfo.ubDiagStatus  = UDS_ACK;
                m_stDiagMessageInfo.ulLength      = PROG_TD_RESPONSE_SIZE;
                m_stDiagMessageInfo.pubTxData[2U] = PROG_IMPL80_FAULT_CRC;

                UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength,
                                        m_stDiagMessageInfo.pubTxData,
                                        m_stDiagMessageInfo.ubDiagStatus);
            }
        }
        else
        {
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_73;
            /* Push event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
    else
    {
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_24;
        /* Push event PROG_EVENT_FAILED*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
}
/*-------------------------{end PROG_ControlZIWritingParameters_Impl80}---------------------------*/
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/*------------------------{PROG_AddressSizeConsistencyCheck}--------------------------*/
NCS_PRI_FCT tProgStatus PROG_AddressSizeConsistencyCheck(tProgAddressType ulStartAddress, u32 ulDataSize)
{
    tProgStatus eProgStatus;
    u32         ulExpectSize;
    u8          ubCalibIdx;
    u8          ubAppCalibIdx;
    u8          ubSegmentIdx;
    u8          ubFirstSegment;
    u8          ubNbSegments;

    eProgStatus = PROG_E_NOT_OK;

    ulExpectSize = ulDataSize + PROG_IMPL80_MIN_TD_SIZE;
    /* The size of the informative data versus the number of informative data received */
    if (m_stDiagMessageInfo.ulLength == ulExpectSize)
    {
        ubCalibIdx    = 0U;
        /* Use the last element containing all segments for "application + calibration" */
        ubAppCalibIdx = (PROG_BLOCK_NB - 1U);

        /* Identify the index of block "application + calibration" and block */
        if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == stCfgBlock[0U].uwBlockIdentifier)
        {
            ubCalibIdx = 1U;
        }

        if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
        {
            ubFirstSegment = stCfgBlock[ubAppCalibIdx].ubFirstSegmentId;
            ubNbSegments   = stCfgBlock[ubAppCalibIdx].ubSegmentNbr;
        }
        else
        /* No need to check PROG_IMPL80_LOGICAL_MARKER_CALIB == m_ubLogicalMarker as
           PROG_IMPL80_LOGICAL_MARKER_CALIB != m_ubLogicalMarker is unreachable here */
        {
            ubFirstSegment = stCfgBlock[ubCalibIdx].ubFirstSegmentId;
            ubNbSegments   = stCfgBlock[ubCalibIdx].ubSegmentNbr;
        }

        for (ubSegmentIdx = 0U; ubSegmentIdx < ubNbSegments; ubSegmentIdx++)
        {
            if (  ((u32)ulStartAddress >= stConfigSegment[ubSegmentIdx + ubFirstSegment].ulStartAddress)
                &&( ((u32)ulStartAddress + ulDataSize) <= (stConfigSegment[ubSegmentIdx + ubFirstSegment].ulEndAddress + 1U)) )
            {
                /* Save the current segment index */
                m_stCurrentSegment.ubSegmentId = ubSegmentIdx + ubFirstSegment;
                /* Update segement list with new size */
                m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId] += ulDataSize;

                eProgStatus = PROG_E_OK;
                break;
            }
        }
    }

    return eProgStatus;
}
/*-------------------------{end PROG_AddressSizeConsistencyCheck}---------------------------*/
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

/*------------------------{PROG_GetBlockInfos_Impl80}--------------------------*/
void PROG_GetBlockInfos_Impl80(u8 ubLogicMarker, tSegmentType * pstSegment)
{
    u8 ubBlockIndex;

    ubBlockIndex = 1U;

    /* Identify the index of block */
    if (ubLogicMarker == stCfgBlock[0U].uwBlockIdentifier)
    {
        ubBlockIndex = 0U;
    }

    pstSegment->ubSegmentId      = stCfgBlock[ubBlockIndex].ubFirstSegmentId;
    pstSegment->ubSegmentNbr     = stCfgBlock[ubBlockIndex].ubSegmentNbr;
    pstSegment->ubLogicalBlockId = ubBlockIndex;
}
/*-------------------------{end PROG_GetBlockInfos_Impl80}---------------------------*/

#if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON
/*------------------------{PROG_Entry_RTE_Impl80}--------------------------*/
void PROG_Entry_RTE_Impl80(void)
{
    tProgStatus eProgStatus;
    u8          ubIndex;
    u8          ubMaxSegments;

    if ( ((PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
        ||(PROG_IMPL80_LOGICAL_MARKER_CALIB     == m_ubLogicalMarker))
       &&(m_stPageBuffer.ulOldDataLength != 0U) )
    {
        /* Save the length for comparison */
        m_stWriteInfo.ulWriteLength = m_stPageBuffer.ulOldDataLength;

        (void)PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                 PROG_MEM_OPERATION_TYPE_WRITE,
                                 m_stWriteInfo.ulAddressToWrite,
                                 m_stPageBuffer.ulOldDataLength,
                                 &m_stPageBuffer.aubData[0U]);
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;

        switch (m_ubLogicalMarker)
        {
            case PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI:
                if (PROG_TRUE == m_stProgrammingFlags.ubRDKeyAppliOk)
                {
                    m_stProgrammingFlags.ubRDKeyAppliOk = PROG_FALSE;
                    eProgStatus                         = PROG_E_OK;
                }
                break;

            case PROG_IMPL80_LOGICAL_MARKER_APP_CALIB:
            case PROG_IMPL80_LOGICAL_MARKER_CALIB:
                if (PROG_TRUE == m_stProgrammingFlags.ubRDOk)
                {
                    if(PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
                    {
                        /* Store the size of the new downloaded segments for application + calibration*/
                        ubIndex = 0U;
                        ubMaxSegments = PROG_SEGMENT_NB;
                    }
                    else
                    {
                        PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_CALIB, &m_stCurrentSegment);
                        /* Store the size of the new downloaded segments only for calibration*/
                        ubIndex = m_stCurrentSegment.ubSegmentId;
                        ubMaxSegments = m_stCurrentSegment.ubSegmentNbr + m_stCurrentSegment.ubSegmentId;
                    }
                    for (/* No init */; ubIndex < ubMaxSegments; ubIndex++)
                    {
                        PROG_CustomStoreDownloadedSegmentSize(&m_aulDownloadedSegSize[ubIndex], ubIndex);
                    }
                    /* Reset RD flag */
                    m_stProgrammingFlags.ubRDOk = PROG_FALSE;
                    eProgStatus                 = PROG_E_OK;
                }
                break;

            case PROG_IMPL80_LOGICAL_MARKER_ZI:
                if (PROG_TRUE == m_stProgrammingFlags.ubRDLogOk)
                {
                    m_stProgrammingFlags.ubRDLogOk = PROG_FALSE;
                    eProgStatus                    = PROG_E_OK;
                }
                break;

            default:
                eProgStatus = PROG_E_NOT_OK;
                break;
        }
        if (PROG_E_OK == eProgStatus)
        {
            m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
            /* Emit event PROG_EVENT_FINISHED */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
        }
        else
        {
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_24;
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
}
/*-------------------------{end PROG_Entry_RTE_Impl80}---------------------------*/
#endif /* PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON */

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/*------------------------{PROG_ControlSelfCheckParameters_Impl80}--------------------------*/
tUdsStatus PROG_ControlSelfCheckParameters_Impl80(PduLengthType *puwLen, u8 * pubData)
{
    tUdsStatus eUdsStatus;
    u8         ubRtneStatus;

    if ((NULL_PTR != puwLen) && (NULL_PTR != pubData))
    {
        /* Retrieve routine identifier */
        m_uwRoutineId  = (u16)((u16)pubData[3U] & 0x00FFU);
        m_uwRoutineId |= (u16)(((u16)pubData[2U] << 8U) & 0xFF00U);

        /* Positive response will be sent */
        eUdsStatus = UDS_ACK;

        if (PROG_FALSE == m_stProgrammingFlags.ubWriteOk)
        {
            /* Prepare response */
            *puwLen = 6U;
            /* Request is not ok */
            pubData[4U] = PROG_REQUEST_ROUTINE_RESULT_FAIL;
            pubData[5U] = PROG_IMPL80_ERROR_WRITING;
        }
        else
        {
            /* Get the routine status */
            ubRtneStatus = PROG_GetRoutineResult_Impl80(m_uwRoutineId);

            /* If self-check request is not already started */
            if (PROG_REQUEST_ROUTINE_RESULT_PENDING != ubRtneStatus)
            {
                /* Store request information */
                m_stDiagMessageInfo.pubData      = pubData;
                m_stDiagMessageInfo.pubTxData    = pubData;
                m_stDiagMessageInfo.ulLength     = *puwLen;
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

                /* Reset tuning and global erase flag */
                m_stProgrammingFlags.ubTunBlank    = PROG_FALSE;
                m_stProgrammingFlags.ubGlobalBlank = PROG_FALSE;

                /* Store the routine status */
                PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_PENDING);
                /* Push the event PROG_EVENT_REQ_CHECKMEMORY */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_REQ_CHECKMEMORY);
            }
            /* Prepare response pending */
            *puwLen = 5U;
            /* Request is pending */
            pubData[4] = PROG_REQUEST_ROUTINE_RESULT_PENDING;
        }
    }
    else
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    return eUdsStatus;
}
/*-------------------------{end PROG_ControlSelfCheckParameters_Impl80}---------------------------*/
#endif  /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/*------------------------{PROG_Entry_SelfCheck_Impl80}--------------------------*/
void PROG_Entry_SelfCheck_Impl80(void)
{
#if (PROG_CRC_CALCULATION == PROG_TD_CRC16)
    tProgStatus      eProgStatus;
    tProgEraseStatus eEraseStatus;
    tProgAddressType ulCrcAddress;
    u32              ulReadLength;
    u8               ubCrcSegIndex;
    u8               aubCrcVal[2U];
    u8               ubIndex;

    m_stDataProgVerification.uwVal = PROG_CRC16_INIT_VAL;

    /* Start application CRC verification */
    m_ubLogicalMarker = PROG_IMPL80_LOGICAL_MARKER_APP_CALIB;
    /* Identify the "application" info */
    PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_APP_CALIB, &m_stCurrentSegment);

    /* Check if application is erased */
    eEraseStatus = PROG_CustomGetEraseStatus(m_stCurrentSegment.ubLogicalBlockId);
    if (PROG_E_ERASED != eEraseStatus)
    {
        /* Retrieve the latest sizes for each segments */
        for (ubIndex = 0U; ubIndex < PROG_SEGMENT_NB; ubIndex++)
        {
            PROG_CustomGetDownloadedSegmentSize(&m_aulDownloadedSegSize[ubIndex], ubIndex);
        }

        /* Get segment address of the first segment Id */
        m_stCurrentSegment.ulStartAddress =
                stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress;

        /* Segment ID where CRC (application) is stored */
        ubCrcSegIndex = m_stCurrentSegment.ubSegmentId + (m_stCurrentSegment.ubSegmentNbr - 1U);
        /* Remove CRC from calculation */
        m_aulDownloadedSegSize[ubCrcSegIndex] -= PROG_CRC_BYTE_LENGTH;
        ulCrcAddress = stConfigSegment[ubCrcSegIndex].ulStartAddress + m_aulDownloadedSegSize[ubCrcSegIndex];

        /* Retrieve the value of the CRC */
        eProgStatus = PROG_MemDataAccess(
                                m_astCfgMemory[stConfigSegment[ubCrcSegIndex].ubMemoryIdx].eMemoryType,
                                PROG_MEM_OPERATION_TYPE_READ,
                                ulCrcAddress,
                                PROG_CRC_BYTE_LENGTH,
                                &aubCrcVal[0U]);

        m_auwCrcValue = (u16)(((u16)aubCrcVal[0U] << 8U) | (u16)aubCrcVal[1U]);

        if (PROG_E_OK == eProgStatus)
        {
            if (m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId] > PROG_CRC_CALC_SIZE)
            {
                ulReadLength = PROG_CRC_CALC_SIZE;
            }
            else
            {
                ulReadLength = m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId];
            }
            /* Remove read length */
            m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId] -= ulReadLength;

            /* Read data */
            eProgStatus = PROG_MemDataAccess(
                                    m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                    PROG_MEM_OPERATION_TYPE_READ,
                                    m_stCurrentSegment.ulStartAddress,
                                    ulReadLength,
                                    &m_aubCrcData[0]);

            if (PROG_E_OK == eProgStatus)
            {
                /* Call CRC API */
                PROG_CalcCrc16(&m_aubCrcData[0], ulReadLength, &m_stDataProgVerification.uwVal);
                /* Update next address */
                m_stCurrentSegment.ulStartAddress += ulReadLength;
            }
            else
            {
                eProgStatus = PROG_E_NOT_OK;
            }
        }
    }
    else
    {
        eProgStatus   = PROG_E_NOT_OK;
    }

    if (PROG_E_NOT_OK == eProgStatus)
    {
        /* Application CRC verification failed */
        m_ubErrorType = PROG_IMPL80_SOFTWARE_NOT_OK;

        /* Push EVENT_FAILED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /* Set routine status to failed */
        PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_FAIL);
    }
    else
    {
        /* Nothing to do */
    }
#else
    /* CHECK: NOPARSE */
    /* NOCOV-FEATURE_NOT_USED */
    /* CRC mandatory as ACT not yet considered */
    /* Application CRC verification failed */
    m_ubErrorType = PROG_IMPL80_SOFTWARE_NOT_OK;
    /* Push EVENT_FAILED */
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    /* Set routine status to failed */
    PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_FAIL);
    /* CHECK: PARSE */
#endif /* (PROG_CRC_CALCULATION == PROG_TD_CRC16) */
}
/*-------------------------{end PROG_Entry_SelfCheck_Impl80}---------------------------*/
#endif /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/*------------------------{PROG_Do_SelfCheck_Impl80}--------------------------*/
void PROG_Do_SelfCheck_Impl80(void)
{
#if (PROG_CRC_CALCULATION == PROG_TD_CRC16)
    tProgStatus      eProgStatus;
    tProgEraseStatus eEraseStatus;
    tProgAddressType ulCrcAddress;
    u32              ulReadLength;
    u8               ubCrcSegIndex;
    u8               aubCrcVal[2U];

    eProgStatus = PROG_E_OK;

    if (m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId] != 0U)
    {
        if (m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId] > PROG_CRC_CALC_SIZE)
        {
            ulReadLength = PROG_CRC_CALC_SIZE;
        }
        else
        {
            ulReadLength = m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId];
        }
        /* Remove read length */
        m_aulDownloadedSegSize[m_stCurrentSegment.ubSegmentId] -= ulReadLength;

        /* Read data */
        eProgStatus = PROG_MemDataAccess(
                                m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                PROG_MEM_OPERATION_TYPE_READ,
                                m_stCurrentSegment.ulStartAddress,
                                ulReadLength,
                                &m_aubCrcData[0]);

        if (PROG_E_OK == eProgStatus)
        {
            /* Call CRC API */
            PROG_CalcCrc16(&m_aubCrcData[0], ulReadLength, &m_stDataProgVerification.uwVal);
            /* Update next address */
            m_stCurrentSegment.ulStartAddress += ulReadLength;
        }
        else
        {
            eProgStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        if (m_stCurrentSegment.ubSegmentNbr > 1U)
        {
            /* Next segment */
            m_stCurrentSegment.ubSegmentId++;
            m_stCurrentSegment.ubSegmentNbr--;

           /* Get segment address of the first segment Id */
            m_stCurrentSegment.ulStartAddress =
                    stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress;

        }
        else
        {
            /* Compare expected CRC versus calculated */
            if (m_auwCrcValue != m_stDataProgVerification.uwVal)
            {
                /* CRC check failed */
                eProgStatus = PROG_E_NOT_OK;
            }
            else
            {
                if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
                {
                    m_stDataProgVerification.uwVal = PROG_CRC16_INIT_VAL;

                    /* Start calibration CRC check */
                    m_ubLogicalMarker = PROG_IMPL80_LOGICAL_MARKER_CALIB;
                    /* Identify the "calibration" info */
                    PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_CALIB, &m_stCurrentSegment);

                    /* Check if calibration is erased */
                    eEraseStatus = PROG_CustomGetEraseStatus(m_stCurrentSegment.ubLogicalBlockId);
                    if (PROG_E_ERASED != eEraseStatus)
                    {
                        /* Get segment address of the first segment Id */
                        m_stCurrentSegment.ulStartAddress =
                                stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress;

                        /* Segment ID where CRC (calibration) is stored */
                        ubCrcSegIndex = m_stCurrentSegment.ubSegmentId + (m_stCurrentSegment.ubSegmentNbr - 1U);
                        /* Remove CRC from calculation */
                        m_aulDownloadedSegSize[ubCrcSegIndex] -= PROG_CRC_BYTE_LENGTH;
                        ulCrcAddress = stConfigSegment[ubCrcSegIndex].ulStartAddress + m_aulDownloadedSegSize[ubCrcSegIndex];

                        /* Retrieve the value of the CRC */
                        eProgStatus = PROG_MemDataAccess(
                                                m_astCfgMemory[stConfigSegment[ubCrcSegIndex].ubMemoryIdx].eMemoryType,
                                                PROG_MEM_OPERATION_TYPE_READ,
                                                ulCrcAddress,
                                                PROG_CRC_BYTE_LENGTH,
                                                &aubCrcVal[0U]);

                        m_auwCrcValue = (u16)(((u16)aubCrcVal[0U] << 8U) | (u16)aubCrcVal[1U]);
                    }
                    else
                    {
                        /* Calibration erased */
                        eProgStatus = PROG_E_NOT_OK;
                    }
                }
                else
                {
                    /* Push EVENT_CRC_FINISH */
                    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRC_FINISH);
                    /* Set routine status to success */
                    PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_SUCCESS);
                }
            }
        }
    }

    if (PROG_E_NOT_OK == eProgStatus)
    {
        if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
        {
            /* Application CRC verification failed */
            m_ubErrorType = PROG_IMPL80_SOFTWARE_NOT_OK;
        }
        else
        {
            /* Calibration CRC verification failed */
            m_ubErrorType = PROG_IMPL80_CALIBRATION_NOT_OK;
        }
        /* Push EVENT_FAILED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /* Set routine status to failed */
        PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_FAIL);
    }
    else
    {
        /* Nothing to do */
    }
#endif /* (PROG_CRC_CALCULATION == PROG_TD_CRC16) */
}
/*-------------------------{end PROG_Do_SelfCheck_Impl80}---------------------------*/
#endif /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/*------------------------{PROG_Entry_CheckMemoryFinish_Impl80}--------------------------*/
void PROG_Entry_CheckMemoryFinish_Impl80(void)
{
    if (PROG_TRUE == m_stProgrammingFlags.ubProgInit)
    {
        /* Enable LOG zone writing */
        m_stProgrammingFlags.ubAuthorizeLog = PROG_TRUE;
    }
    else
    {
        /* Forbid LOG zone writing */
        m_stProgrammingFlags.ubAuthorizeLog = PROG_FALSE;
    }
}
/*-------------------------{end PROG_Entry_CheckMemoryFinish_Impl80}---------------------------*/
#endif /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/*------------------------{PROG_Entry_ACT_Check_Impl80}--------------------------*/
void PROG_Entry_ACT_Check_Impl80(void)
{
    /* No ACT for now so finish the processing */
    /* Push EVENT_FINISHED */
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
}
/*-------------------------{end PROG_Entry_ACT_Check_Impl80}---------------------------*/
#endif /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

#if PROG_CHECK_MEMORY_ENABLE == STD_ON
/*------------------------{PROG_ACT_Check_Impl80}--------------------------*/
void PROG_ACT_Check_Impl80(void)
{
    /* No ACT, nothing to do */
}
/*-------------------------{end PROG_ACT_Check_Impl80}---------------------------*/
#endif /* PROG_CHECK_MEMORY_ENABLE == STD_ON */

/*------------------------{PROG_VerificationOnTheFly_Impl80}--------------------------*/
/* CHECK: NOPARSE */
/* NOCOV-FEATURE_NOT_USED */
void PROG_VerificationOnTheFly_Impl80(void)
{
    /* Nothing to do */
}
/* CHECK: PARSE */
/*-------------------------{end PROG_VerificationOnTheFly_Impl80}---------------------------*/

#if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON
/*------------------------{PROG_Do_RTE_Impl80}--------------------------*/
void PROG_Do_RTE_Impl80(void)
{
    tProgStatus eProgStatus;
    u8          ubIndex;
    u8          ubMaxSegments;

    eProgStatus = PROG_E_NOT_OK;

    if (  (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
        ||(PROG_IMPL80_LOGICAL_MARKER_CALIB     == m_ubLogicalMarker) )
    {
        eProgStatus = PROG_MemJobResult(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType);

        if (PROG_E_OK == eProgStatus)
        {
            /* Compare byte by byte */
            eProgStatus = PROG_CompareByteByByte_Impl80();
            if (PROG_E_OK == eProgStatus)
            {
                if (PROG_TRUE == m_stProgrammingFlags.ubRDOk)
                {
                    if(PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
                    {
                        /* Store the size of the new downloaded segments for application + calibration*/
                        ubIndex = 0U;
                        ubMaxSegments = PROG_SEGMENT_NB;
                    }
                    else
                    {
                        PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_CALIB, &m_stCurrentSegment);
                        /* Store the size of the new downloaded segments only for calibration*/
                        ubIndex = m_stCurrentSegment.ubSegmentId;
                        ubMaxSegments = m_stCurrentSegment.ubSegmentNbr + m_stCurrentSegment.ubSegmentId;
                    }
                    for (/* No init */; ubIndex < ubMaxSegments; ubIndex++)
                    {
                        PROG_CustomStoreDownloadedSegmentSize(&m_aulDownloadedSegSize[ubIndex], ubIndex);
                    }
                    /* Reset RD ok flag */
                    m_stProgrammingFlags.ubRDOk = PROG_FALSE;
                }
                else
                {
                    eProgStatus = PROG_E_NOT_OK;
                }
            }
        }
    }
    if (PROG_E_OK == eProgStatus)
    {
        m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
        /* Emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }
    else if (PROG_E_BUSY != eProgStatus)
    {
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_24;
        /* Emit event PROG_EVENT_FAILED*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    else
    {
        /* Nothing to do */
    }
}
/*-------------------------{end PROG_Do_RTE_Impl80}---------------------------*/
#endif /* PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON */

/*------------------------{PROG_AppCalibWriteCheck_Impl80}--------------------------*/
NCS_PRI_FCT void PROG_AppCalibWriteCheck_Impl80(void)
{
    tProgStatus eProgStatus;
    u16         uwIdx;
    u32         ulMinValueToWrite;
    u32         ulRemainingDataToWrite;
    u32         ulAddressDelta;

  ulMinValueToWrite = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ulMinValueToWrite;

  eProgStatus            = PROG_E_BYPASS;
  ulAddressDelta         = 0U;
  ulRemainingDataToWrite = 0U;

  if (0U < m_stWriteInfo.ulWriteLength)
  {
      if (0U < m_stPageBuffer.ulOldDataLength)
      {
          m_stWriteInfo.ulDataToBeWritten = (u32)m_stPageBuffer.ulOldDataLength;
          ulRemainingDataToWrite          = (u32)m_stPageBuffer.ulOldDataLength;
          m_stPageBuffer.ulOldDataLength  = 0U;
          eProgStatus                     = PROG_E_OK;
      }
      else
      {
          /* Wait and send TD_END_EVENT */
          m_ubWaitCryptoBeforeTdEnd = PROG_TRUE;
      }
  }
  else
  {
      /* Is there data from previous TD not written */
      if (0U < m_stPageBuffer.ulOldDataLength)
      {
          /* Update size of data that will be written */
          m_stWriteInfo.ulWriteLength = (u32)m_stPageBuffer.ulOldDataLength;

          /* Copy the previous unwritten data */
          for (uwIdx = 0U; uwIdx < m_stPageBuffer.ulOldDataLength; uwIdx++)
          {
              m_aubWriteDataBuffer[uwIdx] = m_stPageBuffer.aubData[uwIdx];
          }
      }

      /* Compute remaining data to write */
      ulRemainingDataToWrite = m_stWriteInfo.ulDataToBeWritten + (u32)m_stPageBuffer.ulOldDataLength - m_stWriteInfo.ulWrittenData;

      /* Check if successive addresses */
      if ( (m_stWriteInfo.ulAddressToWrite + m_stPageBuffer.ulOldDataLength) == m_stWriteInfo.ulNewAddressToWrite)
      {
          eProgStatus = PROG_E_OK;
      }
      /* Are both addresses in the same page size */
      else if (  (m_stWriteInfo.ulAddressToWrite / ulMinValueToWrite) ==
                      (m_stWriteInfo.ulNewAddressToWrite / ulMinValueToWrite) )
      {
          ulAddressDelta = m_stWriteInfo.ulNewAddressToWrite - m_stWriteInfo.ulAddressToWrite;
          eProgStatus    = PROG_E_OK;
      }
      else
      {
          if (0U < m_stPageBuffer.ulOldDataLength)
          {
              /* Save received data length as old length to write them next */
              m_stPageBuffer.ulOldDataLength = (u16)m_stWriteInfo.ulDataToBeWritten;
              /* Emit event PROG_EVENT_WRITE */
              PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE);
          }
          else
          {
              m_stWriteInfo.ulAddressToWrite = m_stWriteInfo.ulNewAddressToWrite;
              eProgStatus = PROG_E_OK;
          }
      }
  }
  if (PROG_E_OK == eProgStatus)
  {
      /* Copy the new received data */
      for (uwIdx = 0U; uwIdx < m_stWriteInfo.ulDataToBeWritten; uwIdx++)
      {
          m_aubWriteDataBuffer[uwIdx + (u16)m_stPageBuffer.ulOldDataLength + (u16)ulAddressDelta] =
                                      m_stDiagMessageInfo.pubData[(u16)PROG_IMPL80_INFO_DATA_FIRST_BYTE_IN_TD + uwIdx + (u16)m_stPageBuffer.ulNewDataLength];
      }
      /* Is there enough data to write */
      if ((ulRemainingDataToWrite + ulAddressDelta) >= ulMinValueToWrite)
      {
          /* Align data that will be written */
          m_stWriteInfo.ulWriteLength = (u32)(ulRemainingDataToWrite + ulAddressDelta) / ulMinValueToWrite;
          m_stWriteInfo.ulWriteLength = ulMinValueToWrite * m_stWriteInfo.ulWriteLength;

          m_stPageBuffer.ulNewDataLength = (u16)(m_stWriteInfo.ulWriteLength - (u32)m_stPageBuffer.ulOldDataLength - ulAddressDelta);
          m_stPageBuffer.ulOldDataLength = (u16)(ulRemainingDataToWrite + ulAddressDelta - m_stWriteInfo.ulWriteLength);
          /* Save remaining data */
          for (uwIdx = 0U; uwIdx < m_stPageBuffer.ulOldDataLength; uwIdx++)
          {
              m_stPageBuffer.aubData[uwIdx] = m_aubWriteDataBuffer[uwIdx + m_stWriteInfo.ulWriteLength];
          }
          /* Emit event PROG_EVENT_WRITE */
          PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE);
      }
      else
      {
          /* Save remaining data and length */
          for (uwIdx = 0U; uwIdx < (ulRemainingDataToWrite + ulAddressDelta); uwIdx++)
          {
              m_stPageBuffer.aubData[uwIdx] = m_aubWriteDataBuffer[uwIdx];
          }

          m_stPageBuffer.ulOldDataLength = (u16)(ulRemainingDataToWrite + ulAddressDelta);
          /* Wait and send TD_END_EVENT */
          m_ubWaitCryptoBeforeTdEnd = PROG_TRUE;
      }
  }
}
/*-------------------------{end PROG_AppCalibWriteCheck_Impl80}---------------------------*/

/*------------------------{PROG_WriteCheck_Impl80}--------------------------*/
void PROG_WriteCheck_Impl80(void)
{
    if (m_ubWaitCryptoBeforeTdEnd != PROG_FALSE)
    {
        m_ubWaitCryptoBeforeTdEnd = PROG_FALSE;
        /* emit event PROG_EVENT_TD_END now */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_TD_END);

        if (m_stDiagMessageInfo.ubDiagStatus == UDS_ACK)
        {
            /* Writing OK */
            m_stDiagMessageInfo.pubTxData[2U] = PROG_IMPL80_WRITING_OK;
        }
    }
    /* Check if no error happened */
    else if (UDS_ACK == m_stDiagMessageInfo.ubDiagStatus)
    {
        if (  (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
            ||(PROG_IMPL80_LOGICAL_MARKER_CALIB     == m_ubLogicalMarker) )
        {
            /* Call WriteCheck sub-function */
            PROG_AppCalibWriteCheck_Impl80();
        }
        else if (  (PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI == m_ubLogicalMarker)
                 ||(PROG_IMPL80_LOGICAL_MARKER_ZI        == m_ubLogicalMarker) )
        {
            /* Push event PROG_EVENT_WRITE */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE);
        }
        else
        {
            /* This case shall not happen */
            /* Write is failed */
            m_stProgrammingFlags.ubWriteOk = PROG_FALSE;
            /* Negative response */
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
    else
    {
        if (m_stWriteInfo.ubTDReceived == TRUE)
        {
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
        else
        {
            /* Nothing to do */
        }
    }
}
/*-------------------------{end PROG_WriteCheck_Impl80}---------------------------*/

/*------------------------{PROG_Entry_Write_Impl80}--------------------------*/
void PROG_Entry_Write_Impl80(void)
{
    tProgStatus eProgStatus;

    switch (m_ubLogicalMarker)
    {
        case PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI:
            /* Trigger the writing of KEY APPLI */
            eProgStatus = PROG_CustomWriteKeyAppli(&m_stDiagMessageInfo.pubData[PROG_IMPL80_KEY_APPLI_FIRST_BYTE_IN_TD], PROG_IMPL80_APPLI_KEY_LENGTH);
            break;

        case PROG_IMPL80_LOGICAL_MARKER_APP_CALIB:
        case PROG_IMPL80_LOGICAL_MARKER_CALIB:
            /* Trigger the writing of the received TD */
            eProgStatus = PROG_MemDataAccess(
                                m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                PROG_MEM_OPERATION_TYPE_WRITE,
                                m_stWriteInfo.ulAddressToWrite,
                                m_stWriteInfo.ulWriteLength,
                                &m_aubWriteDataBuffer[0U]);
            break;

        case PROG_IMPL80_LOGICAL_MARKER_ZI:
            /* Trigger the writing of ZI */
            eProgStatus = PROG_CustomWriteZI(&m_stDiagMessageInfo.pubData[PROG_IMPL80_ZI_FIRST_BYTE_IN_TD], PROG_IMPL80_LOG_ZONE_LENGTH);
            break;

        default:
            eProgStatus = PROG_E_NOT_OK;
            break;
    }

    PROG_WriteStatusCheck_Impl80(eProgStatus);
}
/*-------------------------{end PROG_Entry_Write_Impl80}---------------------------*/

/*------------------------{PROG_Write_Impl80}--------------------------*/
void PROG_Write_Impl80(void)
{
    tProgStatus eProgStatus;

    switch (m_ubLogicalMarker)
    {
        case PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI:
        case PROG_IMPL80_LOGICAL_MARKER_ZI:
            /* Get job result for key appli or ZI */
            eProgStatus = PROG_CustomGetWriteJobResult(m_ubLogicalMarker);
            break;

        case PROG_IMPL80_LOGICAL_MARKER_APP_CALIB:
        case PROG_IMPL80_LOGICAL_MARKER_CALIB:
            /* Get job result */
            eProgStatus = PROG_MemJobResult(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType);
            break;

        default:
            eProgStatus = PROG_E_NOT_OK;
            break;
    }

    PROG_WriteStatusCheck_Impl80(eProgStatus);
}
/*-------------------------{end PROG_Write_Impl80}---------------------------*/

/*------------------------{PROG_WriteStatusCheck_Impl80}--------------------------*/
NCS_PRI_FCT void PROG_WriteStatusCheck_Impl80(tProgStatus eProgStatus)
{
    u16 uwIdx;

    if (PROG_E_OK == eProgStatus)
    {
        /* Case writing application and/or calibration */
        if (  (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
            ||(PROG_IMPL80_LOGICAL_MARKER_CALIB     == m_ubLogicalMarker) )
        {
            /* Compare byte by byte */
            eProgStatus = PROG_CompareByteByByte_Impl80();
            if (PROG_E_OK == eProgStatus)
            {
                /* Increase number of written data */
                m_stWriteInfo.ulWrittenData += m_stWriteInfo.ulWriteLength;

                /* Update next address to write */
                m_stWriteInfo.ulAddressToWrite += m_stWriteInfo.ulWriteLength;

                /* Reset buffer used for writing */
                for (uwIdx = 0U; uwIdx < PROG_IMPL80_MAX_WRITTEN_DATA_NBR; uwIdx++)
                {
                    m_aubWriteDataBuffer[uwIdx] = 0xFFU;
                }
                /* Emit event PROG_EVENT_WRITE_CHECK */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE_CHECK);
            }
        }
        else
        {
            /* Case writing log zone */
            if (PROG_IMPL80_LOGICAL_MARKER_ZI == m_ubLogicalMarker)
            {
                /* Set ECU status to $F0 */
                PROG_CustomSetECUStatus(PROG_IMPL80_ECU_STATUS_END_ALIGNEMENT);
                m_stProgrammingFlags.ubAuthorizeLog = PROG_FALSE;
                m_uwToolSignature = 0x0000U;
            }
            /* Allow to push TD event */
            m_ubWaitCryptoBeforeTdEnd = PROG_TRUE;
            /* Emit event PROG_EVENT_WRITE_CHECK */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WRITE_CHECK);
        }
    }

    if ( (PROG_E_OK   != eProgStatus)
       &&(PROG_E_BUSY != eProgStatus))
    {
        if (  (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
            ||(PROG_IMPL80_LOGICAL_MARKER_CALIB     == m_ubLogicalMarker) )
        {
            /* Write is failed */
            m_stProgrammingFlags.ubWriteOk = PROG_FALSE;
        }
        else if (PROG_IMPL80_LOGICAL_MARKER_ZI == m_ubLogicalMarker)
        {
            (void)PROG_CustomUpdateLogSaveMarkingByte(PROG_IMPL80_LOG_SAVE_MARKING_RESET);
        }
        else
        {
            /* Nothing to do */
        }
        /* Negative response */
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;

        /* Emit event PROG_EVENT_FAILED*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    else
    {
        /* Nothing to do */
    }
}
/*-------------------------{end PROG_WriteStatusCheck_Impl80}---------------------------*/

/*------------------------{PROG_ControlEraseParameters_Impl80}--------------------------*/
tUdsStatus PROG_ControlEraseParameters_Impl80(PduLengthType *puwLen, u8 * pubData)
{
    tUdsStatus eUdsStatus;
    u8         ubRtneStatus;

    /* Retrieve routine identifier */
    m_uwRoutineId  = (u16)((u16)pubData[3U] & 0x00FFU);
    m_uwRoutineId |= (u16)(((u16)pubData[2U] << 8U) & 0xFF00U);
    /* Retrieve logical marker */
    m_ubLogicalMarker = pubData[4U];
    /* Retrieve tool signature */
    m_uwToolSignature  = (u16)pubData[6U];
    m_uwToolSignature |= (u16)(((u16)pubData[5U]) << 8U);

    /* Get the routine status */
    ubRtneStatus = PROG_GetRoutineResult_Impl80(m_uwRoutineId);

    /* In case new erase request while the current is in progress */
    if (PROG_REQUEST_ROUTINE_RESULT_PENDING == ubRtneStatus)
    {
        /* Prepare response pending */
        *puwLen = 5U;
        /* Request is pending */
        pubData[4] = PROG_REQUEST_ROUTINE_RESULT_PENDING;
        /* Positive response */
        eUdsStatus = UDS_ACK;
    }
    else
    {
        if (  ((PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker) || (PROG_IMPL80_LOGICAL_MARKER_CALIB == m_ubLogicalMarker))
              &&(PROG_IMPL80_TOOL_SIGNATURE == m_uwToolSignature)
           )
        {
            /* Update status of the request to pending */
            PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_PENDING);
            /* Prepare response pending */
            *puwLen = 5U;
            /* Request is pending */
            pubData[4] = PROG_REQUEST_ROUTINE_RESULT_PENDING;
            /* Positive response */
            eUdsStatus = UDS_ACK;
        }
        else
        {
            /* Reset the tool signature as error occurs here */
            m_uwToolSignature = 0x0000U;
            eUdsStatus        = UDS_NRC_31;
        }
    }
    return eUdsStatus;
}
/*-------------------------{end PROG_ControlEraseParameters_Impl80}---------------------------*/

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID))
/*------------------------{PROG_EraseFirstCheck_Impl80}--------------------------------*/
tProgStatus PROG_EraseFirstCheck_Impl80(void)
{
    tProgEraseStatus eEraseStatus;
    tProgStatus      eProgStatus;

    /* Update internal parameters */
    m_stProgrammingFlags.ubProgInit    = PROG_TRUE;
    m_stProgrammingFlags.ubWriteOk     = PROG_TRUE;
    m_stProgrammingFlags.ubTunBlank    = PROG_FALSE;
    m_stProgrammingFlags.ubGlobalBlank = PROG_FALSE;

    eProgStatus = PROG_E_OK;

    /* Calibration is always erased no matter logical marker */
    /* Identify the index of block "calibration" */
    PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_CALIB, &m_stCurrentSegment);

    /* Check if logical block (calibration) is already erased */
    eEraseStatus = PROG_CustomGetEraseStatus(m_stCurrentSegment.ubLogicalBlockId);
    if (PROG_E_ERASED == eEraseStatus)
    {
        m_stProgrammingFlags.ubTunBlank = PROG_TRUE;
        if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
        {
            /* Identify the index of block "application" */
            PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_APP_CALIB, &m_stCurrentSegment);

            /* Check if logical block (application) is already erased */
            eEraseStatus = PROG_CustomGetEraseStatus(m_stCurrentSegment.ubLogicalBlockId);
            if (PROG_E_ERASED == eEraseStatus)
            {
                m_stProgrammingFlags.ubGlobalBlank = PROG_TRUE;
                /* Positive response shall be sent */
                eProgStatus = PROG_E_BYPASS;
            }
        }
        else
        {
            /* Positive response shall be sent */
            eProgStatus = PROG_E_BYPASS;
        }
    }
    else
    {
        /* Erase started. Inhibit application */
        PROG_CustomSetECUStatus(PROG_IMPL80_ECU_STATUS_APP_INHIBITED);
    }
    if (PROG_E_OK == eProgStatus)
    {
        /* Get segment address */
        m_stCurrentSegment.ulStartAddress =
                stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress;

        /* Get segment size */
        m_stCurrentSegment.ulSize =
                stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseEndAddress
                        - stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress;
    }

    return eProgStatus;
}
/*-------------------------{end PROG_EraseFirstCheck_Impl80}---------------------------*/
#endif /* ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID)) */

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID))
/*------------------------{PROG_EraseStatusCheck_Impl80}--------------------------------*/
void PROG_EraseStatusCheck_Impl80(tProgStatus eProgStatus)
{
    tProgEraseStatus eEraseStatus;
    tProgStatus      eEraseComplete;

#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
    u32 ulNextAddress = 0U;
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */

    eEraseComplete = PROG_E_NOT_OK;
    while((PROG_E_OK == eProgStatus) && (m_stCurrentSegment.ubSegmentNbr >= 1U))
    {
#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
        /* Perform Erase status check only if the Memory type is not RAM, as erase sector by sector operation is not meant for RAM */
        if (PROG_MEM_TYPE_RAM != m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType)
        {
            /* Get next sector address */
            ulNextAddress = PROG_MemGetNextSectorAddr(
                                m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                m_stCurrentSegment.ulStartAddress);
        }
        else
        {
            /* Nothing to do */
        }
        if((ulNextAddress     < (m_stCurrentSegment.ulStartAddress + m_stCurrentSegment.ulSize)) && \
           (PROG_MEM_TYPE_RAM != m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType))
        {
            m_stCurrentSegment.ulSize -= ulNextAddress-m_stCurrentSegment.ulStartAddress;
            m_stCurrentSegment.ulStartAddress = ulNextAddress;

            if (m_ubNbSectEraseCnt < PROG_NB_OF_SECTOR_TO_ERASE_BEFORE_SENDING_NRC78)
            {
                m_ubNbSectEraseCnt++;

                /* Perform erasing of the current block */
                eProgStatus = PROG_MemDataAccess(
                                    m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                    PROG_MEM_OPERATION_TYPE_ERASE,
                                    m_stCurrentSegment.ulStartAddress,
                                    m_stCurrentSegment.ulSize, NULL_PTR);
            }
            else
            {
                /* Reset counter of number sector to erase */
                m_ubNbSectEraseCnt = 0U;
                /* Emit event PROG_EVENT_WAIT_NRC78 */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_WAIT_NRC78);

                /* Set Status to BUSY to leave the loop */
                eProgStatus = PROG_E_BUSY;
            }
        }
        else
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */
        {
            if(m_stCurrentSegment.ubSegmentNbr > 1U)
            {
                /* Set next segment to be erased */
                m_stCurrentSegment.ubSegmentId++;

                /* get next segment address*/
                m_stCurrentSegment.ulStartAddress =
                        stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress;

                /* get next segment size */
                m_stCurrentSegment.ulSize =
                        stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseEndAddress
                                - stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress;

                /* Perform erasing of the current block */
                eProgStatus = PROG_MemDataAccess(
                                      m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                      PROG_MEM_OPERATION_TYPE_ERASE,
                                      m_stCurrentSegment.ulStartAddress,
                                      m_stCurrentSegment.ulSize, NULL_PTR);

#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
                m_ubNbSectEraseCnt++;
#endif
            }
            /* decrement number of segments */
            m_stCurrentSegment.ubSegmentNbr--;
        }
    }

    if (PROG_E_OK == eProgStatus)
    {
        if (PROG_IMPL80_LOGICAL_MARKER_APP_CALIB == m_ubLogicalMarker)
        {
            if (PROG_FALSE == m_stProgrammingFlags.ubTunBlank)
            {
                /* Calibration erased successfully */
                m_stProgrammingFlags.ubTunBlank = PROG_TRUE;

                /* Erase successful. Inhibit application */
                PROG_CustomSetECUStatus(PROG_IMPL80_ECU_STATUS_CLEARING_APP_INHIBITED);
                /* Set Erase status for block calibration */
                (void)PROG_CustomSetEraseStatus(m_stCurrentSegment.ubLogicalBlockId, PROG_E_ERASED);

                /* Identify the index of block "application" */
                PROG_GetBlockInfos_Impl80(PROG_IMPL80_LOGICAL_MARKER_APP_CALIB, &m_stCurrentSegment);

                /* Check if logical block (application) is already erased */
                eEraseStatus = PROG_CustomGetEraseStatus(m_stCurrentSegment.ubLogicalBlockId);
                if (PROG_E_ERASED == eEraseStatus)
                {
                    m_stProgrammingFlags.ubGlobalBlank = PROG_TRUE;
                    /* Erase is finished successfully */
                    PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_SUCCESS);
                    /* Erase completed */
                    eEraseComplete = PROG_E_OK;
                }
                else
                {
                    /* Get segment address */
                    m_stCurrentSegment.ulStartAddress =
                            stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress;

                    /* Get segment size */
                    m_stCurrentSegment.ulSize =
                            stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseEndAddress
                                    - stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress;

                    /* Perform erasing of the current block */
                    eProgStatus = PROG_MemDataAccess(
                                          m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                          PROG_MEM_OPERATION_TYPE_ERASE,
                                          m_stCurrentSegment.ulStartAddress,
                                          m_stCurrentSegment.ulSize, NULL_PTR);

                    if (PROG_E_NOT_OK == eProgStatus)
                    {
                        eEraseComplete = PROG_E_NOT_OK;
                    }
                }
            }
            else
            {
                /* Application erased successfully */
                m_stProgrammingFlags.ubGlobalBlank = PROG_TRUE;
                /* Set Erase status for block Application */
                (void)PROG_CustomSetEraseStatus(m_stCurrentSegment.ubLogicalBlockId, PROG_E_ERASED);
                /* Erase is finished successfully */
                PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_SUCCESS);
                /* Erase completed */
                eEraseComplete = PROG_E_OK;
            }
        }
        /* Only calibration */
        else
        {
            /* Calibration erased successfully */
            m_stProgrammingFlags.ubTunBlank = PROG_TRUE;

            /* Erase successful. Inhibit application */
            PROG_CustomSetECUStatus(PROG_IMPL80_ECU_STATUS_CLEARING_APP_INHIBITED);
            /* Set Erase status for block calibration */
            (void)PROG_CustomSetEraseStatus(m_stCurrentSegment.ubLogicalBlockId, PROG_E_ERASED);

            /* Erase is finished successfully */
            PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_SUCCESS);
            /* Erase completed */
            eEraseComplete = PROG_E_OK;
        }
    }
    else if (PROG_E_BUSY != eProgStatus)
    {
        /* Erase failed. Inhibit application */
        PROG_CustomSetECUStatus(PROG_IMPL80_ECU_STATUS_APP_INHIBITED);
        /* Erase failed. Update status to fail */
        PROG_UpdateRequestRoutineResult_Impl80(m_uwRoutineId, PROG_REQUEST_ROUTINE_RESULT_FAIL);
        /* Erase completed with failure */
        eEraseComplete = PROG_E_OK;
    }
    else
    {
        /* Nothing to do */
    }

    if (PROG_E_NOT_OK != eEraseComplete)
    {
#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
        /* Reset counter of number sector to erase */
        m_ubNbSectEraseCnt = 0U;
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */
        /* Emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }
}
/*-------------------------{end PROG_EraseStatusCheck_Impl80}---------------------------*/
#endif /* ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID)) */

/*------------------------{PROG_CompareByteByByte_Impl80}--------------------------*/
NCS_PRI_FCT tProgStatus PROG_CompareByteByByte_Impl80(void)
{
    tProgStatus eProgStatus;
    u16         uwIndex;

    /* Read data written */
    eProgStatus = PROG_MemDataAccess(
                        m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                        PROG_MEM_OPERATION_TYPE_READ,
                        m_stWriteInfo.ulAddressToWrite,
                        m_stWriteInfo.ulWriteLength,
                        &m_aubReadDataBuffer[0U]);

    /* Compare the written data versus received data */
    for (uwIndex = 0U; (uwIndex < m_stWriteInfo.ulWriteLength) && (PROG_E_OK == eProgStatus); uwIndex++)
    {
        if (m_aubWriteDataBuffer[uwIndex] != m_aubReadDataBuffer[uwIndex])
        {
            /* check failed */
            eProgStatus = PROG_E_NOT_OK;
        }
    }
    return eProgStatus;
}
/*-------------------------{end PROG_CompareByteByByte_Impl80}---------------------------*/

/*------------------------{PROG_GetLookUpIndex_Impl80}--------------------------*/
NCS_PRI_FCT tProgStatus PROG_GetLookUpIndex_Impl80(u16 uwRoutineId, u8 *ubTableRtneIndex)
{
    tProgStatus eProgStatus;
    u8          ubIndex;

    eProgStatus = PROG_E_NOT_OK;
    for (ubIndex = 0U; ubIndex < PROG_ROUTINE_RESULT_NB; ubIndex++)
    {
        if (stCfgRoutineResultTable[ubIndex].uwRoutineId == uwRoutineId)
        {
            *ubTableRtneIndex = stCfgRoutineResultTable[ubIndex].ubRoutineIndexList;
            eProgStatus       = PROG_E_OK;
            break;
        }
    }
    return eProgStatus;
}
/*-------------------------{end PROG_GetLookUpIndex_Impl80}---------------------------*/

/*------------------------{PROG_UpdateRequestRoutineResult_Impl80}--------------------------*/
void PROG_UpdateRequestRoutineResult_Impl80(u16 uwRoutineId, tProgRequestRoutineResult eReqRtneResult)
{
    tProgStatus eProgStatus;
    u8          ubIndexList = 0U;

    /* Look for the corresponding index */
    eProgStatus = PROG_GetLookUpIndex_Impl80(uwRoutineId, &ubIndexList);
    if (PROG_E_OK == eProgStatus)
    {
        m_aubRequestRoutineResult[ubIndexList] = eReqRtneResult;
    }
}
/*-------------------------{end PROG_UpdateRequestRoutineResult_Impl80}---------------------------*/

/*------------------------{PROG_GetRoutineResult_Impl80}--------------------------*/
NCS_PRI_FCT u8 PROG_GetRoutineResult_Impl80(u16 uwRoutineId)
{
    tProgStatus eProgStatus;
    u8          ubRet;
    u8          ubIndexList = 0U;

    ubRet = PROG_REQUEST_ROUTINE_RESULT_INIT;
    /* Look for the corresponding index */
    eProgStatus = PROG_GetLookUpIndex_Impl80(uwRoutineId, &ubIndexList);
    if (PROG_E_OK == eProgStatus)
    {
        ubRet = m_aubRequestRoutineResult[ubIndexList];
    }
    return ubRet;
}
/*-------------------------{end PROG_GetRoutineResult_Impl80}---------------------------*/

/*------------------------{PROG_GetRequestRoutineResult_Impl80}--------------------------*/
tUdsStatus PROG_GetRequestRoutineResult_Impl80(PduLengthType *puwLen, u8 *aubUdsData)
{
    tUdsStatus  eUdsStatus;
    tProgStatus eProgStatus;
    u16         uwRoutineId;
    u8          ubRtneIdInTable;

    eUdsStatus = UDS_NRC_31;

    if ((NULL_PTR != puwLen) && (NULL_PTR != aubUdsData))
    {
        uwRoutineId  = (u16)((u16)aubUdsData[3U] & 0x00FFU);
        uwRoutineId |= (u16)(((u16)aubUdsData[2U] << 8U) & 0xFF00U);

        /* Look for the corresponding index */
        eProgStatus = PROG_GetLookUpIndex_Impl80(uwRoutineId, &ubRtneIdInTable);
        if (PROG_E_OK == eProgStatus)
        {
            aubUdsData[4U] = m_aubRequestRoutineResult[ubRtneIdInTable];
            *puwLen        = 5U;
            eUdsStatus     = UDS_ACK;

            if (PROG_REQUEST_ROUTINE_RESULT_FAIL == m_aubRequestRoutineResult[ubRtneIdInTable])
            {
                /* If routine is erase */
                if (PROG_IMPL80_ERASE_ROUTINE_ID == uwRoutineId)
                {
                    eUdsStatus = UDS_NRC_72;
                }

                /* If routine is self-check */
                if (PROG_IMPL80_SELF_CHECK_ROUTINE_ID == uwRoutineId)
                {
                    aubUdsData[5U] = m_ubErrorType;
                    *puwLen        = 6U;
                }
            }
            else if (PROG_REQUEST_ROUTINE_RESULT_INIT == m_aubRequestRoutineResult[ubRtneIdInTable])
            {
                /* If status requested without receiving prior a start request */
                eUdsStatus = UDS_NRC_24;
            }
            else
            {
                /* Nothing to do */
            }
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        eUdsStatus = UDS_ERR_COHE;
    }
    return eUdsStatus;
}
/*-------------------------{end PROG_GetRequestRoutineResult_Impl80}---------------------------*/

/*------------------------{PROG_CalculateInversedCrc16_Impl80}--------------------------*/
NCS_PRI_FCT u16 PROG_CalculateInversedCrc16_Impl80(const u8 *aubData, u16 uwLen, const u16 uwCrcInit)
{
    u16 uwCrcValue;
    u16 uwIdx1, uwIdx2;

    /* Set the CRC value to preset value */
    uwCrcValue = uwCrcInit;

    if(aubData != NULL_PTR)
    {
        for (uwIdx1 = 0U; uwIdx1 < uwLen ; uwIdx1++)
        {
            /* XOR(Crc,data byte) */
            uwCrcValue = (u16)(uwCrcValue ^ ((u16)aubData[uwIdx1]));

            for (uwIdx2 = 0U; uwIdx2 < 8U; uwIdx2++)
            {
                if ( (u16)(uwCrcValue & 0x0001U) != 0U)
                {
                    /* XOR(CRC,Polynomial) */
                    uwCrcValue = (u16)((u16)(uwCrcValue >> 1U) ^ PROG_IMPL80_CRC_POLYNOMIAL);
                }
                else
                {
                    /* Shift right CRC */
                    uwCrcValue = (u16) (uwCrcValue >> 1U);
                }
            }
        }
    }
    return uwCrcValue;
}
/*-------------------------{end PROG_CalculateInversedCrc16_Impl80}---------------------------*/

#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_80) */
