[!VAR "CRY_SHA1_ENABLED"!][!IF "count(as:modconf('Cry')/CrySHA1/CrySHA1Config/*) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!ENDVAR!][!//
[!VAR "CRY_SHA2_ENABLED"!][!IF "count(as:modconf('Cry')/CrySHA2/CrySHA2Config/*) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!ENDVAR!][!//
[!VAR "CRY_SHA3_ENABLED"!][!IF "count(as:modconf('Cry')/CrySHA3/CrySHA3Config/*) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!ENDVAR!][!//
[!//
[!IF "($CRY_SHA1_ENABLED = 'STD_ON') or ($CRY_SHA2_ENABLED = 'STD_ON')"!][!//
[!VAR "CRY_SHA1_STATE_WORDS"!]5U[!ENDVAR!][!//
[!VAR "CRY_SHA256_STATE_WORDS"!]8U[!ENDVAR!][!//
[!ENDIF!][!//
[!//
[!IF "($CRY_SHA1_ENABLED = 'STD_ON') or ($CRY_SHA2_ENABLED = 'STD_ON')"!][!//
[!IF "$CRY_SHA2_ENABLED = 'STD_ON'"!][!//
[!VAR "CRY_SHA_STATE_WORDS" = "$CRY_SHA256_STATE_WORDS"!][!//
[!ELSE!][!//
[!VAR "CRY_SHA_STATE_WORDS" = "$CRY_SHA1_STATE_WORDS"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!//

[!VAR "CryCRCLUTSize" = "0"!][!//
[!VAR "lastCrcPoly" = "''"!][!//
[!VAR "lastCrcType" = "''"!][!//
[!//
[!LOOP "node:order(as:modconf('Cry')/CryCrc/CryCrcConfig/*, './CryCrcPoly', './CryCrcType')"!][!//

[!IF "($lastCrcPoly != node:value(./CryCrcPoly)) or ($lastCrcType != node:value(./CryCrcType))"!][!//
[!VAR "CryCRCLUTSize" = "$CryCRCLUTSize + 1"!][!//
[!ENDIF!][!//
[!VAR "lastCrcType" = "node:value(./CryCrcType)"!][!//
[!VAR "lastCrcPoly" = "node:value(./CryCrcPoly)"!][!//
[!ENDLOOP!][!//

