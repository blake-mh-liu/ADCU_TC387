/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0008,1 */

#ifndef CRY_BASE64_H
#define CRY_BASE64_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Decode a Base64 encoded string
 **
 ** This function decodes a Base64 encoded string. The following holds:
 ** 1) The newline characters '\n' and '\r' are ignored in the input string.
 ** 2) If a padding is used, the padding must use the correct number of padding
 **    characters at the end of the input string.
 ** 3) If other characters than '\n' and '\r' occur after the last padding
 **    character, this is treated as an error.
 ** 4) If the output buffer is too small to accomodate the result,
 **    CSM_E_SMALL_BUFFER is returned.
 ** 5) If the last block of encoded characters only contains a single
 **    byte, this is considered an error (since the last decoded byte is
 **    missing two bits)
 **
 ** \param[in]    Encoding           The string to be decoded
 ** \param[in]    EncodingLength     The length of the encoded string
 **
 ** \param[out]      Result          The result of the decoding
 ** \param[in,out]   ResultLengthPtr Must contain the length of the result buffer
 **                                  (on calling). Shall contain the length of the
 **                                  decoded string on returning.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      Decoding was successful
 ** \retval   CSM_E_NOT_OK  The input did not conform to the expected format
 ** \retval   CSM_E_SMALL_BUFFER The output buffer was to small to accomodate
 **                              the result
 **/

extern FUNC(Csm_ReturnType, CRY_CODE) Cry_Base64Decode
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Encoding,
  uint32                                   EncodingLength,
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)   Result,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA)  ResultLengthPtr
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #ifndef CRY_BASE64_H */
