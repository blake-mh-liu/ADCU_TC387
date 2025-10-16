/* --------{ EB Automotive C Source File }-------- */

#ifndef CPL_ARLEDECOMPRESS_CFG_H
#define CPL_ARLEDECOMPRESS_CFG_H

/* !LINKSTO EB_CPL_0801_078, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_079, 1
 */
#include <Std_Types.h>
#include <Cpl_Version.h>
#include <Cpl_Common.h>

/*==================[macros]======================================================================*/

/* !LINKSTO EB_CPL_0806_516, 1
 */
/** \brief  This macro encodes whether the ARLEDecompress primitive is configured.
 **/
[!IF "num:i(0) != num:i(count(as:modconf('Cpl')/CplArleDecompress/CplArleDecompressConfig/*))"!][!//
#define  CPL_ARLEDECOMPRESS_ENABLED          STD_ON
[!ELSE!][!//
#define  CPL_ARLEDECOMPRESS_ENABLED          STD_OFF
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/* !LINKSTO EB_CPL_ARLE_CFG_TYPE, 1 */
/** \brief  Type for representing a ARLEDecompress configuration.
 **/
typedef struct
{
  uint8 dummyParameter;
}
Cpl_ARLEDecompressConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplArleDecompress/CplArleDecompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

[!LOOP "as:modconf('Cpl')/CplArleDecompress/CplArleDecompressConfig/*"!][!//
extern CONST(Cpl_ARLEDecompressConfigType, CPL_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CPL_ARLEDECOMPRESS_CFG_H */

/*==================[end of file]=================================================================*/
