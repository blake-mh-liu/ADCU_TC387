#ifndef PROG_DECOMP_H
#define PROG_DECOMP_H

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
/*%%   _____________________________   %%  \file PROG_Decomp.h                   */
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
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
[!AUTOSPACING!]
[!IF "General/Enable_Compression = 'true'"!]
#if (PROG_CAL_PRESENT == STD_ON)
#include "PROG_Cfg.h"

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/* Size of decompression buffer */
#define PROG_DECOMP_OUT_BUF_SIZE    [!"num:i(General/Decomp_Out_Buffer_size)"!]U
#define PROG_COMP_HEADER_SIZE       8U

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

typedef u8 tProgDecompressStateType;
#define PROG_DECOMP_IDLE                0x00U
#define PROG_DECOMP_INIT                0x01U
#define PROG_DECOMP_FINISH              0x02U
#define PROG_DECOMP_FAILED              0x03U
#define PROG_DECOMP_IN_PROGRESS         0x04U

typedef struct
{
    /* Pointer to compressed data */
    u8  * paubBuf;
    /* Length of compressed data */
    u32 ulBufLength;
    /* Index in the compressed data buffer from where data shall be decompressed */
    u32 ulDecompIdx;
    /* Number of data that have been decompressed */
    u32 ulDecompCount;
} tInBuffContext;

typedef struct
{
    u8 aubBuf[PROG_DECOMP_OUT_BUF_SIZE];
    /* Position of first available entry */
    u32 ulBufPosition;
    u32 ulBufLength;
    /* Number of lost slots in out buffer in case of too small buffer */
    u32 ulBufLostBytes;
    u8 aubDecompPageBuffer[PROG_MIN_VAL_TO_WRITE];
} tOutBuffContext;


/** \brief Initialize decompression wrapper
 **
 ** \param[in] ulCompressedDataSize: size of data to decompress
 ** \return Result of init
 ** \retval PROG_E_OK Init is ok
 ** \retval PROG_E_NOT_OK Init failed
 **
 **/
extern tProgStatus PROG_DecompressInit(u32 ulCompressedDataSize);

/** \brief reinit decompression input param
 **
 ** This function Reinitializes the input decompression parameter after each TD
 **
 **/
extern void PROG_DecompInputParamInit(void);

/** \brief manage function of decompression wrapper (to be called cyclically) **/
void PROG_DecompressManage(void);

/** \brief Request data decompression
 **
 ** \param[in] pubData: data to be decompress
 ** \param[in] ulDataLength: length of data to be decompress
 **
 **/
extern tProgStatus PROG_DecompressData(u8* pubData, PduLengthType ulDataLength);

/** \brief Get decompressed data
 **
 ** \param[in] pubDecompData: pointer to location of decompressed data
 ** \param[in] pulDecompressLength: length of decompressed data
 ** \return Result of decompression
 ** \retval PROG_DECOMP_INIT No decompressed data
 ** \retval PROG_DECOMP_FINISH All data have been decompressed
 ** \retval PROG_DECOMP_FAILED Decompression has failed
 ** \retval PROG_DECOMP_IN_PROGRESS Decompression is not finished (but some decompressed data are available)
 **
 **/
extern tProgDecompressStateType PROG_GetDecompressedData(u8** pubDecompData,
    PduLengthType* pulDecompressLength);

/** \brief Confirm the number of decompressed data that have been get
 **
 ** \param[in] uwLength: length of data that have been get
 ** \param[in] pulDecompressLength: length of decompressed data
 **
 **/
extern void PROG_DecompWriteDataConfirmation(u16 uwLength);

/*                                                                               */
/*-------------------------------------------------------------------------------*/
#endif /* #if (PROG_CAL_PRESENT == STD_ON) */
[!ENDIF!]
#endif      /* PROG_DECOMP_H */
