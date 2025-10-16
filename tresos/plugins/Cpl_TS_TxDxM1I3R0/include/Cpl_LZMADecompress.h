#ifndef CPL_LZMADECOMPRESS_H
#define CPL_LZMADECOMPRESS_H

/*================================================================================================*/
/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_101, 1 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_103, 1 */
#include <Cal_Types.h>
#include <Cal_Decompress.h>

#include <Cpl_Common.h>
#include <Cpl_LZMADecompress_Cfg.h>


#if (CPL_LZMADECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/
/** \brief Data type to hold the probability for one symbol. */
typedef uint16 CProbType;

/*==================[external function declarations]==============================================*/

/* !LINKSTO EB_CPL_0804_101, 1 */
/** \brief  Start LZMA decompression computation.
 **
 ** This function requests the start of the LZMA decompression for
 ** the given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]      cfgPtr              Pointer to Cal module configuration which has to be used
 **                                     during the LZMA decompression computation.
 ** \param[in,out]  contextBuffer       Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZMA decompression is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressStart
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
);

/* !LINKSTO EB_CPL_0804_103, 1 */
/** \brief  Update LZMA decompression computation.
 **
 ** This function requests the update of the LZMA decompression
 ** computation for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgPtr              Pointer to Cal module configuration which has to be used
 **                                     during the LZMA decompression computation.
 ** \param[in,out]  contextBuffer       Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZMA decompression is stored.
 ** \param[in]      inputBuf             Holds a pointer to the data that shall be processed.
 ** \param[in,out]  inputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by inputBuf.
 **                                     On returning from this function the length of data from
 **                                     buffer inputBuf that was already processed/decompressed
 **                                     shall be stored.
 ** \param[out]     outputBuf             Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  outputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by outputBuf.
 **                                     On returning from this function the size of decompressed
 **                                     data (the result) which was written to the buffer outputBuf
 **                                     shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer outputBuf is too small to store the
 **                                     complete result. This means that not all data in inputBuf
 **                                     could be processed/decompressed. Only inputBufLen bytes of
 **                                     inputBuf (on returning) were decompressed.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressUpdate
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                    AUTOMATIC, CPL_APPL_DATA) inputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) inputBufLen,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) outputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) outputBufLen
);

/* !LINKSTO EB_CPL_0804_105, 1
 */
/** \brief  Finish LZMA decompression computation.
 **
 ** This function requests the finishing of the LZMA decompression computation.
 ** The finish function of the configured primitive is called and its return
 ** value is returned.
 **
 ** \param[in]      cfgPtr              Pointer to Cal module configuration which has to be used
 **                                     during the LZMA decompression computation.
 ** \param[in,out]  contextBuffer       Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZMA decompression is stored.
 ** \param[out]     outputBuf             Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  outputBufLen          Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **                                     On calling this function this parameter shall contain the
 **                                     size of the buffer provided by outputBuf.
 **                                     On returning from this function the size of decompressed
 **                                     data (the result) which was written to the buffer outputBuf
 **                                     shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressFinish
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) outputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) outputBufLen
);

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CPL_LZMADECOMPRESS_ENABLED == STD_ON) */

#endif /* #ifndef CPL_LZMADECOMPRESS_H */

/*==================[end of file]=================================================================*/
