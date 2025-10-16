/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_CRC_CONFIG_H
#define CRY_CRC_CONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>
[!INCLUDE "Cry_common.m"!][!//

/*==================[macros]======================================================================*/

#if (defined CRY_CRC_BUFTYP_SIZE)
#error CRY_CRC_BUFTYP_SIZE is already defined
#endif
#define  CRY_CRC_BUFTYP_SIZE  256U
#if (defined CRY_CRC_ENABLED)
#error CRY_CRC_ENABLED is already defined
#endif
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!][!//
#define CRY_CRC_ENABLED TRUE
[!ELSE!][!//
#define CRY_CRC_ENABLED FALSE
[!ENDIF!][!//

/** \brief parameter configuration used to set the variant the way it's calculated LUT
 **/
#if (defined CRY_CRC_SPEED_OPTIMIZED)
#error CRY_CRC_SPEED_OPTIMIZED is already defined
#endif
[!IF "node:value(as:modconf('Cry')/CryGeneral/CryCrcImplementationVariant) = 'CRY_CRC_SPEED_OPTIMIZED'"!][!//
#define CRY_CRC_SPEED_OPTIMIZED STD_ON
[!ELSE!][!//
#define CRY_CRC_SPEED_OPTIMIZED STD_OFF
[!ENDIF!][!//

#if (CRY_CRC_ENABLED == TRUE)

#if (defined CRY_CRC_BUFLEN)
#error CRY_CRC_BUFLEN is already defined
#endif
[!VAR "CryCrcMax" = "'0'"!][!//
[!VAR "CryCrcTmp" = "'0'"!][!//
[!//
[!LOOP "as:modconf('Cry')/CryCrc/CryCrcConfig/*"!][!//
[!IF "(node:value(./CryCrcType)) = 'CRY_CRC_8' "!][!VAR "CryCrcTmp" = "'1'       "!][!ENDIF!][!//
[!IF "(node:value(./CryCrcType)) = 'CRY_CRC_16'"!][!VAR "CryCrcTmp" = "'2'       "!][!ENDIF!][!//
[!IF "(node:value(./CryCrcType)) = 'CRY_CRC_32'"!][!VAR "CryCrcTmp" = "'4'       "!][!ENDIF!][!//
[!IF "$CryCrcTmp                 >   $CryCrcMax"!][!VAR "CryCrcMax" = "$CryCrcTmp"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!IF "$CryCrcMax = '1'"!]#define  CRY_CRC_BUFTYP  uint8[!ENDIF!][!//
[!IF "$CryCrcMax = '2'"!]#define  CRY_CRC_BUFTYP  uint16[!ENDIF!][!//
[!IF "$CryCrcMax = '4'"!]#define  CRY_CRC_BUFTYP  uint32[!ENDIF!]
#define  CRY_CRC_BUFLEN  [!"$CryCrcMax"!]U     /* == sizeof(CRY_CRC_BUFTYP) */

/*==================[type definitions]============================================================*/

/*---[enum]---------------------------------------------------------------------------------------*/

/** \brief  Type of the configured order of CRC polynom.
 **/
typedef enum
{
  CRY_CRC_8  = 1,
  CRY_CRC_16 = 2,
  CRY_CRC_32 = 4
}
Cry_CRC_Type;

/*---[struct]-------------------------------------------------------------------------------------*/

/** \brief  Configuration type for representing a configured CRC.
 **/
typedef struct
{
#if (CRY_CRC_SPEED_OPTIMIZED == STD_ON)
  uint32       nodeIndex;
#endif
  Cry_CRC_Type typeCrc;
  uint32       polyCrc;
  uint32       mbpcCrc;
  uint32       iputXor;
  uint32       oputXor;
  boolean      iputReflect;
  boolean      oputReflect;
}
Cry_CRC_ConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryCrc/CryCrcConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryCrc/CryCrcConfig/*"!][!//
extern CONST(Cry_CRC_ConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

[!IF "node:value(as:modconf('Cry')/CryGeneral/CryCrcImplementationVariant) = 'CRY_CRC_SPEED_OPTIMIZED'"!][!//
/** \brief  Lookup tables with precalculated values needed for CRC calculation.
 **/
extern CRY_CRC_BUFTYP Cry_CRC_LUT[[!"num:i($CryCRCLUTSize)"!]U][CRY_CRC_BUFTYP_SIZE];

/** \brief  Mapping between the Cry configuration ID and Csm configuration ID.
 **/
extern uint8 Cry_CRC_LUT_idx[[!"num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!]U];

/** \brief  Mapping between the Csm configuration ID and Cry configuration ID.
 **/
extern uint8 Csm_CRC_LUT_idx[[!"num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!]U];

/** \brief  Mapping between given Cry configuration ID and Csm configuration ID.
 **/
extern uint8 Cry_CFG_idx[[!"num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!]U];
[!ENDIF!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//
[!ENDIF!][!//


/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CRC_ENABLED == TRUE) */

#endif /* #ifndef CRY_CRC_CONFIG_H */
