/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_080, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_081, 1
 */
#include <Cpl_ARLEDecompress_Cfg.h>



#if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplArleDecompress/CplArleDecompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CPL_ARLE_CFG_TYPE, 1
 */
[!LOOP "as:modconf('Cpl')/CplArleDecompress/CplArleDecompressConfig/*"!][!//
CONST(Cpl_ARLEDecompressConfigType, CPL_CONST) [!"node:name(.)"!] =
{
  0u
};

[!ENDLOOP!][!//
[!//
#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!//
/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#else /* #if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_ArleDecompressConfig_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
