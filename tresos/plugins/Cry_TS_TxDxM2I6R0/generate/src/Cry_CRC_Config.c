/* --------{ EB Automotive C Source File }-------- */

/*==================[includes]====================================================================*/

[!INCLUDE "../include/Cry_common.m"!][!//

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_CRC_Config.h>

#if (CRY_CRC_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryCrc/CryCrcConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryCrc/CryCrcConfig/*"!][!//
CONST(Cry_CRC_ConfigType, CRY_CONST) [!"node:name(.)"!] =
{
#if (CRY_CRC_SPEED_OPTIMIZED == STD_ON)
  [!"num:i(node:pos(.))"!]U,
#endif
  [!"node:value(./CryCrcType)"!],
  0x[!" text:toupper(substring-after(num:inttohex(node:value(./CryCrcPoly), 8),'x'))"!]U,
  [!"node:value(./CryCrcMaxBytesPerCycle)"!]U,
  0x[!" text:toupper(substring-after(num:inttohex(node:value(./CryCrcIputXor), 8),'x'))"!]U,
  0x[!" text:toupper(substring-after(num:inttohex(node:value(./CryCrcOputXor), 8),'x'))"!]U,
  [!IF "(node:value(./CryCrcIputReflect)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
  [!IF "(node:value(./CryCrcOputReflect)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
};


[!ENDLOOP!][!//
[!//
#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!IF "node:value(as:modconf('Cry')/CryGeneral/CryCrcImplementationVariant) = 'CRY_CRC_SPEED_OPTIMIZED'"!][!//

[!VAR "lastCrcPoly" = "''"!][!//
[!VAR "lastCrcType" = "''"!][!//
[!VAR "i" = "0"!][!//
uint8 Cry_CRC_LUT_idx[[!"num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!]U] = {[!//
[!LOOP "node:order(as:modconf('Cry')/CryCrc/CryCrcConfig/*, './CryCrcPoly', './CryCrcType')"!][!//
[!IF "($lastCrcPoly != node:value(./CryCrcPoly)) or ($lastCrcType != node:value(./CryCrcType))"!][!//
[!VAR "i" = "$i + 1"!][!//
[!ENDIF!][!//
[!VAR "lastCrcPoly" = "node:value(./CryCrcPoly)"!][!//
[!VAR "lastCrcType" = "node:value(./CryCrcType)"!][!//
[!"num:i($i - 1)"!]U, [!//
[!ENDLOOP!][!//
};

uint8 Cry_CFG_idx[[!"num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!]U] = {[!//
[!LOOP "node:order(as:modconf('Cry')/CryCrc/CryCrcConfig/*, './CryCrcPoly', './CryCrcType')"!][!//
[!VAR "CsmIter" = "node:name(.)"!][!//
[!"node:pos(as:modconf('Csm')/CsmChecksum/CsmChecksumConfig/*[./CsmChecksumInitConfiguration = $CsmIter])"!]U, [!//
[!ENDLOOP!][!//
};

uint8 Csm_CRC_LUT_idx[[!"num:i(count(as:modconf('Cry')/CryCrc/CryCrcConfig/*))"!]U] = {[!//
[!LOOP "as:modconf('Csm')/CsmChecksum/CsmChecksumConfig/*"!][!//
[!VAR "CsmIter" = "./CsmChecksumInitConfiguration"!][!//
[!"node:pos(as:modconf('Cry')/CryCrc/CryCrcConfig/*[node:name(.) = $CsmIter])"!]U, [!//
[!ENDLOOP!][!//
};

[!AUTOSPACING!]

 [!//
 [!VAR "valuSize" = "0"!][!//
 [!VAR "valuPtr" = "0"!][!//
 [!VAR "reflectedCRC" = "0"!][!//
 [!//
 CRY_CRC_BUFTYP Cry_CRC_LUT[[!"num:i($CryCRCLUTSize)"!]U][CRY_CRC_BUFTYP_SIZE] =
 {
 [!VAR "lastCrcPoly" = "''"!][!//
 [!VAR "lastCrcType" = "''"!][!//
 [!//
 [!LOOP "node:order(as:modconf('Cry')/CryCrc/CryCrcConfig/*, './CryCrcPoly', './CryCrcType')"!][!//

 [!IF "($lastCrcPoly != node:value(./CryCrcPoly)) or ($lastCrcType != node:value(./CryCrcType))"!][!//
 [!//
 [!VAR "reflectedCRC" = "0"!][!//
 [!VAR "valuPtr" = "node:value(./CryCrcPoly)"!][!//
 [!//
 [!IF "node:value(./CryCrcType) = 'CRY_CRC_8'"!][!//
 [!VAR "valuSize" = "8"!][!//
 [!ELSEIF "node:value(./CryCrcType) = 'CRY_CRC_16'"!][!//
 [!VAR "valuSize" = "16"!][!//
 [!ELSEIF "node:value(./CryCrcType) = 'CRY_CRC_32'"!][!//
 [!VAR "valuSize" = "32"!][!//
 [!ENDIF!][!//
 [!//
   {
   [!FOR "locLoopBit" = "0" TO "$valuSize - 1" STEP "4"!][!//
     [!VAR "idx" = "bit:and(num:i($valuPtr), 15)"!][!//
     [!VAR "shlVal" = "$valuSize - $locLoopBit - 4"!][!//
     [!VAR "B" = "text:split('0 8 4 12 2 10 6 14 1 9 5 13 3 11 7 15')[position() = $idx + 1]"!][!//
     [!VAR "ReflectNibleVal" = "bit:shl(num:i($B),$shlVal)"!][!//
     [!VAR "reflectedCRC" = "bit:or($reflectedCRC, $ReflectNibleVal)"!][!//
     [!VAR "valuPtr" = "bit:shr(num:i($valuPtr), 4)"!][!//
   [!ENDFOR!][!//
   [!//
   [!WS "4"!][!"num:i(0)"!]U,[!//
   [!FOR "locLoopByt" = "1" TO "255"!][!//
     [!VAR "locTempCrc" = "$locLoopByt"!][!//
     [!FOR "locLoopBit" = "0" TO "7"!][!//
       [!IF "bit:and($locTempCrc, 1) = 1"!][!//
         [!VAR "locTempCrc" = "bit:xor(num:i(bit:shr($locTempCrc, 1)), $reflectedCRC)"!][!//
       [!ELSE!][!//
         [!VAR "locTempCrc" = "bit:shr($locTempCrc, 1)"!][!//
       [!ENDIF!][!//
     [!ENDFOR!][!//
   [!" num:inttohex ($locTempCrc)"!]U,[!WS "1"!][!//
   [!ENDFOR!][!//
   },
 [!ENDIF!][!//
 [!VAR "lastCrcType" = "node:value(./CryCrcType)"!][!//
 [!VAR "lastCrcPoly" = "node:value(./CryCrcPoly)"!][!//
 [!ENDLOOP!][!//
 };

[!ENDIF!][!//

[!ELSE!][!//


[!ENDIF!][!//
/*==================[internal constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryCrc/CryCrcConfig/*) = 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONSTP2CONST(Cry_CRC_ConfigType, CRY_CONST, CRY_APPL_DATA) CryCrcConfigDummy = NULL_PTR;

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#else /* #if (CRY_CRC_ENABLED == TRUE) */

/* dummy definition to prevent empty translation unit */
typedef void Cry_CRCConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CRC_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/
