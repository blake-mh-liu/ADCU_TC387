[!AUTOSPACING!]
#################################################################
# This makefile exports parameters derived from the
# project configuration into variables for make
[!MACRO "GetModuleName","PluginName"!]
  [!IF "contains($PluginName, '_Aurix2G')"!]
[!"substring-before($PluginName, '_Aurix2G')"!][!//
  [!ELSEIF "contains($PluginName, '_')"!]
[!"substring-before($PluginName, '_')"!][!//
  [!ELSE!]
[!"$PluginName"!][!//
  [!ENDIF!]
[!ENDMACRO!]
[!MACRO "GetModuleVariant","PluginName"!]
  [!IF "contains($PluginName, '_Aurix2G')"!]
    [!IF "contains(substring-after($PluginName, '_Aurix2G'), '_')"!]
[!"substring-before(substring-after($PluginName, '_Aurix2G'), '_')"!][!//
    [!ELSE!]
[!"substring-after($PluginName, '_')"!][!//
    [!ENDIF!]
  [!ELSE!]
[!"''"!][!//
  [!ENDIF!]
[!ENDMACRO!]
[!MACRO "GetModuleVariantSuffix","PluginName"!]
  [!IF "contains($PluginName, '_Aurix2G')"!]
[!"substring-after($PluginName, '_')"!][!//
  [!ELSE!]
[!"''"!][!//
  [!ENDIF!]
[!ENDMACRO!]

[!SELECT "as:modconf('McalExt')[1]"!][!//
[!VAR "PlatformIncludePaths" = "num:i(count(IncludePaths/*))"!][!//
[!IF "$PlatformIncludePaths > num:i(0)"!][!//
[!VAR "LoopCounter" = "'IncludePaths'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
[!"IncludePathsStrategy"!]  +=            [!"(./IncludePathsMakeFile)"!]
[!ENDLOOP!][!//
[!ENDIF!][!//

[!VAR "PlatformModuleIncludeFiles" = "num:i(count(FilesToBuild/*))"!][!//
[!IF "$PlatformModuleIncludeFiles > num:i(0)"!][!//
[!VAR "LoopCounter" = "'FilesToBuild'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
[!"BuildStrategy"!]  +=            [!"(./FilePathToBuild)"!]
[!ENDLOOP!][!//
[!ENDIF!][!//


# variables defining module versions and locations of the plugins
[!LOOP "text:order(text:split($enabledModules))"!]
  [!VAR "moduleName"!][!CALL "GetModuleName", "PluginName"="."!][!ENDVAR!]
  [!VAR "moduleVariant"!][!CALL "GetModuleVariantSuffix", "PluginName"="."!][!ENDVAR!]
  [!IF "$moduleVariant != '' and $moduleVariant != 'Os_' and $moduleVariant != 'Ioc_' and $moduleVariant != 'MicroOs_'"!]
McalExt_[!"$moduleName"!]_USED      :=true
  [!ENDIF!]
[!ENDLOOP!]


[!ENDSELECT!][!//

[!IF "node:exists(as:modconf("Os")[1])"!]
PREPROCESSOR_DEFINES += TS_MCALEXT_IRQ_USE_OS
TS_MCALEXT_IRQ_USE_OS_KEY = MCALEXT_IRQ_USE_OS
TS_MCALEXT_IRQ_USE_OS_VALUE = 1
[!ENDIF!]
