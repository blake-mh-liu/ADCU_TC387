/**EB_Automotive_C_Source_File */

#ifndef PLATFORMS_MODULES_H
#define PLATFORMS_MODULES_H

[!SELECT "as:modconf('McalExt')[1]"!][!//
[!VAR "PlatformModuleDefineConfig" = "num:i(count(PlatformModuleDefine/*))"!][!//
[!IF "$PlatformModuleDefineConfig > num:i(0)"!][!//
[!VAR "LoopCounter" = "'PlatformModuleDefine'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
[!NOCODE!][!//
    [!VAR "SymbolicName" = "node:name(.)"!]
  [!ENDNOCODE!][!//
#define [!"$SymbolicName"!]              [!"(./PlatformModuleValue)"!]

[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
#endif /* ifndef PLATFORMS_MODULES_H */

/*==================[end of file]===========================================*/
