/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_106, 1 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_108, 1 */
#include <Cpl_LZMADecompress_Cfg.h>

#if (CPL_LZMADECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CPL_0806_102, 1 */
[!LOOP "as:modconf('Cpl')/CplLzmaDecompress/CplLzmaDecompressConfig/*"!][!//
CONST(Cpl_LZMADecompressConfigType, CPL_CONST) [!"node:name(.)"!] =
{
  [!"./CplLzmaDecompressDictionarySize"!]U,
  [!"./CplLzmaDecompressLP"!]U,
  [!"./CplLzmaDecompressLC"!]U,
  [!"./CplLzmaDecompressPB"!]U
};

[!ENDLOOP!][!//
[!//
#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#else /* #if (CPL_LZMADECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_LzmaDecompressConfig_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_LZMADECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
