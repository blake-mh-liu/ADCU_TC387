/*===============================================================================*/
/*                                                                               */
/*                                 SA LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Decomp.c                     */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.25.0 BL3 */
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
/* NOCOV List
 *
 * NOCOV-UNREACHABLE_CODE:
 *   Default in switch not reachable.
 *
 * Reason:
 * The default case is mandatory but couldn't be reach without setting specifically
 * the internal variable to a wrong value
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "SA_Priv.h"

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

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

#if ((SA_COMPRESSION_STATE == SA_COMPRESSION_ENABLED) && (PROG_CAL_PRESENT == STD_OFF))
/* Decompression algorithm variable */
static u8 m_aubLZSS_window[LZSS_WINDOW_SIZE];
tDecompressStateType m_uDecompressState;
u16 m_uwWinPos;
u8 m_ubOutByte;
u16 m_uwMatchPos;
u8 m_ubMatchLen;
u8 m_ubBitCount;

/* decompression status */
tDecompressStateType m_uDecompStatus;

/* Input buffer variable */
u8* m_pubInDecompBuf;
PduLengthType m_ulInBufLength;
u16 m_uwDecompIdx;

/* Output buffer variables */
u8 m_aubOutDecompBuf[SA_DECOMP_OUT_BUF_SIZE];
u16 m_uwOutBufPosition;
u16 m_uwOutBufLength;

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/** \brief Decompression algorithm
 **
 ** This function implement the LZSS algorithm than decompress bit by bit
 **
 ** \param[in] inBit bit to decompress
 **
 **/
NCS_PRI_FCT void SA_DecompressBit(u8 inBit);
/** \brief Store decompressed byte
 **
 ** This function strore in the otput buffer the decompress bytes
 **
 ** \param[in] ubDecompByte byte decompressed to store
 **
 **/
NCS_PRI_FCT void SA_DecompressedDataOut(u8 ubDecompByte);

/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{SA_DecompressInit}--------------------------------*/
void SA_DecompressInit(void)
{
    u16 uwIdx;

    m_uDecompressState = SA_DECOMP_INIT;
    m_uwWinPos = 1U;

    /* decompression status */
    m_uDecompStatus = SA_DECOMP_INIT;

    /* Input buffer variable */
    m_ulInBufLength = 0U;
    m_uwDecompIdx = 0U;

    /* Output buffer variables */
    m_uwOutBufPosition = 0U;
    m_uwOutBufLength = 0U;

    for (uwIdx = 0U; uwIdx < SA_DECOMP_OUT_BUF_SIZE; uwIdx++)
    {
        m_aubOutDecompBuf[uwIdx] = 0U;
    }
}
/*----------------------------------{end SA_DecompressInit}----------------------------*/

/*----------------------------------{SA_DecompInputParamInit}--------------------------------*/
void SA_DecompInputParamInit(void)
{
    /* Reinit Input param */
    m_ulInBufLength = 0U;
    m_uwDecompIdx = 0U;
}
/*----------------------------------{end SA_DecompInputParamInit}----------------------------*/

/*----------------------------------{SA_DecompressData}--------------------------------*/
void SA_DecompressData(u8* pubData, PduLengthType ulDataLength)
{
    m_pubInDecompBuf = pubData;
    /* Set decompression status to in progress */
    m_uDecompStatus = SA_DECOMP_IN_PROGRESS;
    /* Increment the number of data to decompress */
    m_ulInBufLength += ulDataLength;
}
/*----------------------------------{end SA_DecompressData}----------------------------*/

/*----------------------------------{SA_DecompressManage}--------------------------------*/
void SA_DecompressManage(void)
{
    u8 ubIdx;

    if (m_ulInBufLength > 0U)
    {
        for (ubIdx = 0U; ubIdx < 8U; ubIdx++)
        {
            if ((m_pubInDecompBuf[m_uwDecompIdx] & (u8) (1U << (7U - ubIdx)))
                    != 0U)
            {
                SA_DecompressBit(1U);
            }
            else
            {
                SA_DecompressBit(0U);
            }
        }
        /* Decrement the number of data in the input buffer */
        m_ulInBufLength--;

        if(m_ulInBufLength == 0U)
        {
            m_uDecompStatus = SA_DECOMP_FINISH;
        }

        m_uwDecompIdx++;
    }
    else
    {
        m_uDecompStatus = SA_DECOMP_FINISH;
    }
}
/*----------------------------------{end SA_DecompressManage}----------------------------*/

/*----------------------------------{SA_DecompressBit}--------------------------------*/
NCS_PRI_FCT void SA_DecompressBit(u8 inBit)
{
    u8 ubIdx;

    switch (m_uDecompressState)
    {
        case SA_DECOMP_INIT:
            if (inBit == 1U)
            { /* If bit is 1, next byte is uncompressed */
                m_uDecompressState = SA_DECOMP_UNCOMPRESSED;
                m_ubBitCount = 7U;
            }
            else
            { /* If bit is 1, compressed data follows, first position */
                m_uDecompressState = SA_DECOMP_COMPRESSPOS;
                m_ubBitCount = (u8) (LZSS_INDEX_BIT_COUNT - 1U);
            }
            m_ubOutByte = 0U;
            m_uwMatchPos = 0U;
            m_ubMatchLen = 0U;
            break;

        case SA_DECOMP_UNCOMPRESSED:
            m_ubOutByte += (u8) (inBit << m_ubBitCount); /* accumulate bit by bit */
            if (m_ubBitCount > 0U)
            {
                m_ubBitCount--;
            }
            else
            {
                m_uDecompressState = SA_DECOMP_INIT; /* byte finished, back to init state*/
                m_aubLZSS_window[m_uwWinPos] = m_ubOutByte; /* Add byte to window */
                m_uwWinPos = (u16) ((m_uwWinPos + 1U)
                        & (u16) (LZSS_WINDOW_SIZE - 1U)); /* Increase window position */
                SA_DecompressedDataOut(m_ubOutByte); /* output new byte to CRC handler */
            }
            break;

        case SA_DECOMP_COMPRESSPOS:
            m_uwMatchPos += (u16) ((u16) inBit << m_ubBitCount); /* accumulate bit by bit */
            if (m_ubBitCount > 0U)
            {
                m_ubBitCount--;
            }
            else
            {
                m_uDecompressState = SA_DECOMP_COMPRESSLEN; /* position completed, next is length */
                m_ubBitCount = LZSS_LENGTH_BIT_COUNT - 1U;
                if (m_uwMatchPos == LZSS_END_OF_STREAM)
                {
                    m_uDecompressState = SA_DECOMP_INIT;
                    /* what to do? */
                }
            }
            break;

        case SA_DECOMP_COMPRESSLEN:
            m_ubMatchLen += (u8) (inBit << m_ubBitCount); /* accumulate bit by bit */
            if (m_ubBitCount > 0U)
            {
                m_ubBitCount--;
            }
            else
            {
                m_uDecompressState = SA_DECOMP_INIT; /* length complete, next bit is compressed/uncompressed flag */
                m_ubMatchLen = (u8) (m_ubMatchLen + (LZSS_BREAK_EVEN + 1U)); /* add break even length to get true length */
                for (ubIdx = 0U; ubIdx < m_ubMatchLen; ubIdx++)
                { /* For every byte in match */
                    m_ubOutByte = m_aubLZSS_window[(u16) ((u16) (m_uwMatchPos + ubIdx)
                            & (u16) (LZSS_WINDOW_SIZE - 1U))]; /* Get matching byte from window */
                    m_aubLZSS_window[m_uwWinPos] = m_ubOutByte; /* Add matched byte to current window position */
                    m_uwWinPos = (u16) ((m_uwWinPos + 1U)
                            & (u16) (LZSS_WINDOW_SIZE - 1U)); /* Increase window position */
                    SA_DecompressedDataOut(m_ubOutByte); /* output new byte to CRC handler */
                }
            }
            break;
/* CHECK: NOPARSE */
/* NOCOV-UNREACHABLE_CODE */
        default:
            m_uDecompressState = SA_DECOMP_INIT;
            break;
/* CHECK: PARSE */
    }
}
/*----------------------------------{end SA_DecompressBit}----------------------------*/

/*----------------------------------{SA_DecompressedDataOut}--------------------------------*/
NCS_PRI_FCT void SA_DecompressedDataOut(u8 ubDecompByte)
{
    /* Save the new bytes decompressed */
    m_aubOutDecompBuf[m_uwOutBufPosition] = ubDecompByte;

    /* Increment the number of useful data into the output buffer */
    m_uwOutBufLength++;

    m_uwOutBufPosition++;

    /* Increment or reset the Index */
    if (m_uwOutBufPosition >= SA_DECOMP_OUT_BUF_SIZE)
    {
        m_uwOutBufPosition = 0U;
    }
}
/*----------------------------------{end SA_DecompressedDataOut}----------------------------*/

/*----------------------------------{SA_GetDecompressedData}--------------------------------*/
tDecompressStateType SA_GetDecompressedData(u8** pubDecompData,
    PduLengthType* pulDecompressLength)
{
    tDecompressStateType eSaState;
    /* Check if pointer are not NULL */
    if (pulDecompressLength != NULL_PTR)
    {
        if (m_uwOutBufPosition < m_uwOutBufLength)
        {
            /* return the length of available data */
            *pulDecompressLength = (PduLengthType)m_uwOutBufLength - (PduLengthType)m_uwOutBufPosition;
            /* return pointer to data to write */
            *pubDecompData = &m_aubOutDecompBuf[((SA_DECOMP_OUT_BUF_SIZE
                    - m_uwOutBufLength) + m_uwOutBufPosition)];
            /* return in progress since not all data are returned */
            eSaState = SA_DECOMP_IN_PROGRESS;
        }
        else
        {
            /* return the length of available data */
            *pulDecompressLength = m_uwOutBufLength;
            /* return pointer to data to write */
            *pubDecompData = &m_aubOutDecompBuf[m_uwOutBufPosition
                    - m_uwOutBufLength];

            eSaState = m_uDecompStatus;
        }
    }
    else
    {
        eSaState = SA_ERR_NULL_PTR;
    }

    return eSaState;
}
/*----------------------------------{end SA_GetDecompressedData}----------------------------*/

/*----------------------------------{SA_DecompWriteDataConfirmation}--------------------------------*/
void SA_DecompWriteDataConfirmation(u16 uwLength)
{
    if (uwLength >= m_uwOutBufLength)
    {
        m_uwOutBufLength = 0U;
    }
    else
    {
        m_uwOutBufLength -= uwLength;
    }
}
/*----------------------------------{end SA_DecompWriteDataConfirmation}----------------------------*/
#endif
