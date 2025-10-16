#ifndef CPL_LZMADECOMPRESS_CFG_H
#define CPL_LZMADECOMPRESS_CFG_H

/*================================================================================================*/
/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_105, 1 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_107, 1 */
#include <Std_Types.h>
#include <Cpl_Version.h>

/*==================[macros]======================================================================*/
/* !LINKSTO EB_CPL_0806_101, 1 */
/** \brief  Macro encodes whether the LZMADecompress primitive is configured.
 **/
[!IF "num:i(0) != num:i(count(as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*))"!][!//
#define  CPL_LZMADECOMPRESS_ENABLED          STD_ON

/** \brief    Maximum size of the dictionary */
#define  MAX_DICT_SIZE         [!"num:i(num:max(as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*/CplLzmaDecompressDictionarySize))"!]U

/** \brief    Maximum value of LP parameter */
#define  MAX_LP                [!"num:i(num:max(as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*/CplLzmaDecompressLP))"!]U

/** \brief    Maximum value of LC parameter */
#define  MAX_LC                [!"num:i(num:max(as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*/CplLzmaDecompressLC))"!]U

[!ELSE!][!//
#define  CPL_LZMADECOMPRESS_ENABLED          STD_OFF
[!ENDIF!][!//

/* !LINKSTO EB_CPL_0806_102, 1 */
/** \brief  Type for representing a LZMADecompress configuration.
 **/
typedef struct
{
  /** Dictionary Size parameter.
   *  The dictionary size affects what how many pairs of
   *  (length, distance) can be stored at one time.
   */
  uint32 dictSize;

  /**
   * Number of literal position bits
   *
   * LP affects what kind of alignment in the uncompressed data is
   * assumed when encoding literals. A literal is a single 8-bit byte.
   */
  uint8  lp;

  /**
   * Number of literal context bits
   *
   * How many of the highest bits of the previous uncompressed
   * byte (the literal) are taken into account when predicting
   * the bits of the next literal.
   *
   * E.g. in typical English text, an upper-case letter is
   * often followed by a lower-case letter, and a lower-case
   * letter is usually followed by another lower-case letter.
   * In the US-ASCII character set, the highest three bits are 010
   * for upper-case letters and 011 for lower-case letters.
   * When LC is at least 3, the literal coding can take advantage of
   * this property in the uncompressed data.
   */
  uint8  lc;

  /** Number of position bits
   *
   *  PB affects what kind of alignment in the uncompressed data is
   *  assumed in general.
   */
  uint8  pb;
} Cpl_LZMADecompressConfigType;

[!IF "count(as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Generate symbolic names for the configuration structures. */
[!LOOP "as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*"!][!//
extern CONST(Cpl_LZMADecompressConfigType, CPL_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

[!//
#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CPL_LZMADECOMPRESS_CFG_H */

/*==================[end of file]=================================================================*/
