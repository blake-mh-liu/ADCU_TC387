#ifndef PLATFORMS_MACROS_H
#define PLATFORMS_MACROS_H

/** EB_Automotive_C_Source_File */

[!SELECT "as:modconf('McalExt')[1]"!][!//
[!VAR "PlatformMacroDefineConfig" = "num:i(count(PlatformMacroDefine/*))"!][!//
[!IF "$PlatformMacroDefineConfig > num:i(0)"!][!//
[!VAR "LoopCounter" = "'PlatformMacroDefine'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
  [!NOCODE!][!//
    [!VAR "SymbolicName" = "node:name(.)"!]
  [!ENDNOCODE!][!//
#define [!"$SymbolicName"!]              [!"(./PlatformMacroValue)"!]
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
#endif /* ifndef PLATFORMS_MACROS_H */

/*==================[end of file]===========================================*/
