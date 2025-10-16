#ifndef CPL_ARLEDECOMPRESS_H
#define CPL_ARLEDECOMPRESS_H

/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_074, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_076, 1
 */
#include <Cal_Types.h>
#include <Cal_Decompress.h>

#include <Cpl_Common.h>
#include <Cpl_ARLEDecompress_Cfg.h>

#if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_START_PROTOTYPE, 1
 */
/** \brief  Start ARLE decompression computation.
 **
 ** This function requests the start of the ARLE decompression for
 ** the given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]      cfgPtr              Pointer to Cal module configuration which has to be used
 **                                     during the ARLE decompression computation.
 ** \param[in,out]  contextBuffer       Holds a pointer to the buffer in which the context of the
 **                                     service that calls the ARLE decompression is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressStart
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
);

/* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_UPDATE_PROTOTYPE, 1
 */
/** \brief  Update ARLE decompression computation.
 **
 ** This function requests the update of the ARLE decompression
 ** computation for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgPtr              Pointer to Cal module configuration which has to be used
 **                                     during the ARLE decompression computation.
 ** \param[in,out]  contextBuffer       Holds a pointer to the buffer in which the context of the
 **                                     service that calls the ARLE decompression is stored.
 ** \param[in]      iputBuf             Holds a pointer to the data that shall be processed.
 ** \param[in,out]  iputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by iputBuf.
 **                                     On returning from this function the length of data from
 **                                     buffer iputBuf that was already processed/decompressed shall
 **                                     be stored.
 ** \param[out]     oputBuf             Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  oputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by oputBuf.
 **                                     On returning from this function the size of decompressed
 **                                     data (the result) which was written to the buffer oputBuf
 **                                     shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer oputBuf is too small to store the
 **                                     complete result. This means that not all data in iputBuf
 **                                     could be processed/decompressed. Only iputBufLen bytes of
 **                                     iputBuf (on returning) were decompressed.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressUpdate
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                    AUTOMATIC, CPL_APPL_DATA) iputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) iputBufLen,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
);

/* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_FINISH_PROTOTYPE, 1
 */
/** \brief  Finish ARLE decompression computation.
 **
 ** This function requests the finishing of the ARLE decompression computation.
 ** The finish function of the configured primitive is called and its return
 ** value is returned.
 **
 ** \param[in]      cfgPtr              Pointer to Cal module configuration which has to be used
 **                                     during the ARLE decompression computation.
 ** \param[in,out]  contextBuffer       Holds a pointer to the buffer in which the context of the
 **                                     service that calls the ARLE decompression is stored.
 ** \param[out]     oputBuf             Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  oputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by oputBuf.
 **                                     On returning from this function the size of decompressed
 **                                     data (the result) which was written to the buffer oputBuf
 **                                     shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer oputBuf is too small to store the
 **                                     complete result.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressFinish
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
);

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON) */

#endif /* #ifndef CPL_ARLEDECOMPRESS_H */

/*==================[end of file]=================================================================*/
