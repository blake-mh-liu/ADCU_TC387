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
/*%%   _____________________________   %%  \file PROG_Comp.c                      */
/*%%  |                             |  %%  \brief PROG cryptography feature      */
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
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
#if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))
#include "PROG_Decomp.h"
#include "Cal.h"
#endif
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */

#if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))
/* Decompression context structure for CAL/CPL libraries */
Cal_DecompressCtxBufType m_stProgCplContext;
#endif

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

#if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))
/* decompression status */
tProgDecompressStateType m_uProgDecompStatus;

/* Input buffer context */
NCS_PRI_VAR tInBuffContext m_stInBuffContext;

/* Output buffer context */
NCS_PRI_VAR tOutBuffContext m_stOutBuffContext;

/* Total size of compressed data */
NCS_PRI_VAR u32 m_ulCompressedDataSize;
#endif

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

#if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))
/*---------------------------{PROG_DecompressInit}-------------------------------*/
tProgStatus PROG_DecompressInit(u32 ulCompressedDataSize)
{
    Cal_ReturnType eCplStatus;
    tProgStatus eProgStatus;

    DBG_PROG_DECOMPRESSINIT_ENTRY(ulCompressedDataSize);

    eCplStatus = Cal_DecompressStart(PROG_CALDECOMPRESS_CFGID, m_stProgCplContext);

    m_stOutBuffContext.ulBufLength    = 0U;
    m_stOutBuffContext.ulBufPosition  = 0U;
    m_stOutBuffContext.ulBufLostBytes = 0U;

    m_stInBuffContext.ulDecompIdx     = 0U;
    m_stInBuffContext.ulBufLength     = 0U;
    m_stInBuffContext.ulDecompCount   = 0U;

    m_uProgDecompStatus               = PROG_DECOMP_INIT;
#if(PROG_IMPL_VARIANT != PROG_IMPL_20)
    m_ulCompressedDataSize            = ulCompressedDataSize;
#else
    m_ulCompressedDataSize            = ulCompressedDataSize - PROG_COMP_HEADER_SIZE;
#endif
    m_stInBuffContext.paubBuf         = NULL_PTR;

    if (CAL_E_OK == eCplStatus)
    {
        eProgStatus = PROG_E_OK;
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
    }
    DBG_PROG_DECOMPRESSINIT_EXIT(eProgStatus);
    return eProgStatus;
}
/*--------------------------{End PROG_DecompressInit}----------------------------*/

/*---------------------------{PROG_DecompInputParamInit}-------------------------*/
void PROG_DecompInputParamInit(void)
{
    DBG_PROG_DECOMPINPUTPARAMINIT_ENTRY();
    m_stInBuffContext.ulDecompIdx = 0U;
    m_stInBuffContext.ulBufLength = 0U;
    DBG_PROG_DECOMPINPUTPARAMINIT_EXIT();
}
/*--------------------------{End PROG_DecompInputParamInit}----------------------*/

/*---------------------------{PROG_DecompressData}-------------------------------*/
tProgStatus PROG_DecompressData(u8* pubData, PduLengthType ulDataLength)
{
    Cal_ReturnType eCplStatus;
    tProgStatus eProgStatus;
    u32 ulOutputLength;
    u32 ulInputLength;

    DBG_PROG_DECOMPRESSDATA_ENTRY(pubData, ulDataLength);

    m_stInBuffContext.ulBufLength += ulDataLength;

    if (m_stInBuffContext.ulBufLength != 0U)
    {
        if (NULL_PTR != pubData)
        {
            /* Update input buffer address */
            m_stInBuffContext.paubBuf = pubData;
        }

        ulInputLength = m_stInBuffContext.ulBufLength;

#if (PROG_DECOMP_SLICING_ENABLE == STD_ON)
        if (ulInputLength > PROG_DECOMP_SLICE_SIZE)
        {
            ulInputLength = PROG_DECOMP_SLICE_SIZE;
        }
        else
        {
            /*do nothing*/
        }
#endif /* (PROG_DECOMP_SLICING_ENABLE == STD_ON) */

        /* Calculate available place in buffer */
        if (m_stOutBuffContext.ulBufPosition < m_stOutBuffContext.ulBufLength)
        {
            ulOutputLength = PROG_DECOMP_OUT_BUF_SIZE - m_stOutBuffContext.ulBufLength - m_stOutBuffContext.ulBufLostBytes;
        }
        else
        {
            ulOutputLength = PROG_DECOMP_OUT_BUF_SIZE - m_stOutBuffContext.ulBufPosition;
        }
        m_uProgDecompStatus = PROG_DECOMP_IN_PROGRESS;

        eCplStatus = Cal_DecompressUpdate(PROG_CALDECOMPRESS_CFGID, m_stProgCplContext, &m_stInBuffContext.paubBuf[m_stInBuffContext.ulDecompIdx],
                    &ulInputLength, &m_stOutBuffContext.aubBuf[m_stOutBuffContext.ulBufPosition], &ulOutputLength);

        if((eCplStatus == CAL_E_OK) || (eCplStatus == CAL_E_SMALL_BUFFER))
        {
            /* Increment buffer length and position */
            m_stOutBuffContext.ulBufLength += ulOutputLength;
            m_stOutBuffContext.ulBufPosition += ulOutputLength;
            m_stInBuffContext.ulDecompIdx += ulInputLength;
            m_stInBuffContext.ulBufLength -= ulInputLength;
#if (PROG_RD_DATA_SIZE_TYPE == PROG_DECOMPRESSED_DATA_SIZE)
            m_stInBuffContext.ulDecompCount += ulOutputLength;
#else
            m_stInBuffContext.ulDecompCount += ulInputLength;
#endif
            eProgStatus = PROG_E_OK;

            /* If position reach maximum buffer size, set it back to 0 */
            if ((m_stOutBuffContext.ulBufPosition >= PROG_DECOMP_OUT_BUF_SIZE) || (eCplStatus == CAL_E_SMALL_BUFFER))
            {

                if ((m_stOutBuffContext.ulBufPosition < m_stOutBuffContext.ulBufLength)
                    && (m_stOutBuffContext.ulBufPosition < PROG_DECOMP_OUT_BUF_SIZE))
                {
                    /* Buffer is full wait next call */
                }
                else
                {
                    /* Store the number of bytes that will be unused at the end of the buffer */
                    m_stOutBuffContext.ulBufLostBytes = PROG_DECOMP_OUT_BUF_SIZE - m_stOutBuffContext.ulBufPosition;
                    m_stOutBuffContext.ulBufPosition = 0U;

                    /* Decompress next data at start of output buffer */
                    ulInputLength = m_stInBuffContext.ulBufLength;
                    ulOutputLength = PROG_DECOMP_OUT_BUF_SIZE - m_stOutBuffContext.ulBufLength - m_stOutBuffContext.ulBufLostBytes;
                    eCplStatus = Cal_DecompressUpdate(PROG_CALDECOMPRESS_CFGID, m_stProgCplContext, &m_stInBuffContext.paubBuf[m_stInBuffContext.ulDecompIdx],
                    &ulInputLength, &m_stOutBuffContext.aubBuf[m_stOutBuffContext.ulBufPosition], &ulOutputLength);

                    if((eCplStatus == CAL_E_OK) || (eCplStatus == CAL_E_SMALL_BUFFER))
                    {
                        /* Increment buffer length and position */
                        m_stOutBuffContext.ulBufLength += ulOutputLength;
                        m_stOutBuffContext.ulBufPosition += ulOutputLength;
                        m_stInBuffContext.ulDecompIdx += ulInputLength;
                        m_stInBuffContext.ulBufLength -= ulInputLength;
#if (PROG_RD_DATA_SIZE_TYPE == PROG_DECOMPRESSED_DATA_SIZE)
                        m_stInBuffContext.ulDecompCount += ulOutputLength;
#else
                        m_stInBuffContext.ulDecompCount += ulInputLength;
#endif
                        eProgStatus = PROG_E_OK;
                    }
                    else
                    {
                        eProgStatus = PROG_E_NOT_OK;
                    }


                }

            }

            if (m_stInBuffContext.ulBufLength == 0U)
            {
                m_uProgDecompStatus = PROG_DECOMP_FINISH;
            }

            if(eCplStatus == CAL_E_OK)
            {

                if(m_stInBuffContext.ulDecompCount == m_ulCompressedDataSize)
                {
                    /* All data have been decompressed */

                    eCplStatus = Cal_DecompressFinish(
                        PROG_CALDECOMPRESS_CFGID,
                        m_stProgCplContext,
                        &m_stOutBuffContext.aubBuf[m_stOutBuffContext.ulBufPosition],
                        &ulOutputLength
                        );

                    if(eCplStatus != CAL_E_OK)
                    {
                        eProgStatus = PROG_DECOMP_FAILED;
#if PROG_PEC_ENABLE == STD_ON
                        /* Set error in PEC */
                        m_uwPEC = PROG_ERR_COMPRESSION;
#endif
                    }
                    else
                    {
                        m_stOutBuffContext.ulBufLength += ulOutputLength;
                        m_stOutBuffContext.ulBufPosition += ulOutputLength;
                    }

                }
            }

        }
        else
        {
            eProgStatus = PROG_E_NOT_OK;
            m_uProgDecompStatus = PROG_DECOMP_FAILED;
#if PROG_PEC_ENABLE == STD_ON
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_COMPRESSION;
#endif
        }
    }
    else
    {
            if (m_ubDecompNotWritten == PROG_TRUE)
            {

                /* All data have been decompressed */
                /* Calculate available place in buffer */
                if (m_stOutBuffContext.ulBufPosition < m_stOutBuffContext.ulBufLength)
                {
                    ulOutputLength = PROG_DECOMP_OUT_BUF_SIZE - m_stOutBuffContext.ulBufLength - m_stOutBuffContext.ulBufLostBytes;
                }
                else
                {
                    ulOutputLength = PROG_DECOMP_OUT_BUF_SIZE - m_stOutBuffContext.ulBufPosition;
                }
                eCplStatus = Cal_DecompressFinish(
                    PROG_CALDECOMPRESS_CFGID,
                    m_stProgCplContext,
                    &m_stOutBuffContext.aubBuf[m_stOutBuffContext.ulBufPosition],
                    &ulOutputLength
                    );

                if(eCplStatus != CAL_E_OK)
                {
                    eProgStatus = PROG_DECOMP_FAILED;
#if PROG_PEC_ENABLE == STD_ON
                    /* Set error in PEC */
                    m_uwPEC = PROG_ERR_COMPRESSION;
#endif
                }
                else
                {
                    m_stOutBuffContext.ulBufLength += ulOutputLength;
                    m_stOutBuffContext.ulBufPosition += ulOutputLength;
                }
            }
        m_uProgDecompStatus = PROG_DECOMP_FINISH;
        eProgStatus = PROG_E_OK;
    }

    DBG_PROG_DECOMPRESSDATA_EXIT(eProgStatus);
    return eProgStatus;
}
/*--------------------------{End PROG_DecompressData}----------------------------*/

/*--------------------------{PROG_GetDecompressedData}---------------------------*/
tProgDecompressStateType PROG_GetDecompressedData(u8** pubDecompData,
    PduLengthType* pulDecompressLength)
{
    tProgDecompressStateType eProgDecompState;
    u16 uwIdx;

    DBG_PROG_GETDECOMPRESSEDDATA_ENTRY(pubDecompData, pulDecompressLength);

    if((m_uProgDecompStatus == PROG_DECOMP_IN_PROGRESS) || (m_uProgDecompStatus == PROG_DECOMP_FINISH))
    {
        if ((m_stOutBuffContext.ulBufPosition < m_stOutBuffContext.ulBufLength))
        {
            /* The decompressed data shall be read in two times ( data start at the end of the buffer and continue at start of the buffer */
            /* return the length of available data */
            *pulDecompressLength = (u16)(m_stOutBuffContext.ulBufLength - m_stOutBuffContext.ulBufPosition);

            if((*pulDecompressLength != (u16)m_stOutBuffContext.ulBufLength) && (*pulDecompressLength < PROG_MIN_VAL_TO_WRITE))
            {
                /* Data size is inferior to page size and shall be temporary buffered in a buffer page */
                /* to be written at same time that data at start of the buffer */

                for(uwIdx = 0U; uwIdx < *pulDecompressLength; uwIdx++)
                {
                    m_stOutBuffContext.aubDecompPageBuffer[uwIdx] =
                        m_stOutBuffContext.aubBuf[(
                            ((PROG_DECOMP_OUT_BUF_SIZE
                            - m_stOutBuffContext.ulBufLostBytes
                            - m_stOutBuffContext.ulBufLength)
                            + m_stOutBuffContext.ulBufPosition)
                            + uwIdx
                        )];
                }

                for(; (uwIdx < PROG_MIN_VAL_TO_WRITE) && (uwIdx < m_stOutBuffContext.ulBufLength) ; uwIdx++)
                {
                    m_stOutBuffContext.aubDecompPageBuffer[uwIdx] = m_stOutBuffContext.aubBuf[uwIdx-*pulDecompressLength];
                }

                /* return pointer to data to write */
                *pubDecompData = m_stOutBuffContext.aubDecompPageBuffer;
                *pulDecompressLength = uwIdx;
            }
            else
            {
                /* return pointer to data to write */
                *pubDecompData =
                    &m_stOutBuffContext.aubBuf[(
                        (PROG_DECOMP_OUT_BUF_SIZE
                        - m_stOutBuffContext.ulBufLostBytes
                        - m_stOutBuffContext.ulBufLength)
                        + m_stOutBuffContext.ulBufPosition
                    )];
            }

            if(*pulDecompressLength != (u16)m_stOutBuffContext.ulBufLength)
            {
                /* return in progress since not all data are returned */
                eProgDecompState = PROG_DECOMP_IN_PROGRESS;
            }
            else
            {
                eProgDecompState = m_uProgDecompStatus;
            }
        }
        else
        {
            /* return the length of available data */
            *pulDecompressLength = (u16)m_stOutBuffContext.ulBufLength;
            /* return pointer to data to write */

            *pubDecompData = &m_stOutBuffContext.aubBuf[m_stOutBuffContext.ulBufPosition
                    - m_stOutBuffContext.ulBufLength];


            eProgDecompState = m_uProgDecompStatus;
        }
    }
    else
    {
        eProgDecompState = m_uProgDecompStatus;
    }

    DBG_PROG_GETDECOMPRESSEDDATA_EXIT(eProgDecompState);
    return eProgDecompState ;
}
/*-----------------------{end PROG_GetDecompressedData}--------------------------*/

/*-------------------{PROG_DecompWriteDataConfirmation}--------------------------*/
void PROG_DecompWriteDataConfirmation(u16 uwLength)
{
    DBG_PROG_DECOMPWRITEDATACONFIRMATION_ENTRY(uwLength);
    if (uwLength >= m_stOutBuffContext.ulBufLength)
    {
        m_stOutBuffContext.ulBufLength = 0U;
    }
    else
    {
        m_stOutBuffContext.ulBufLength -= uwLength;
    }
    if ((m_stOutBuffContext.ulBufPosition >= m_stOutBuffContext.ulBufLength))
    {
        /* Lost byte shall be reset (available again) */
        m_stOutBuffContext.ulBufLostBytes = 0;

    }
    DBG_PROG_DECOMPWRITEDATACONFIRMATION_EXIT();
}
/*---------------------{end PROG_DecompWriteDataConfirmation}--------------------*/

#endif /* #if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))*/
