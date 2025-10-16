/**
 * \file
 *
 * \brief AUTOSAR MemIf
 *
 * This file contains the implementation of the AUTOSAR
 * module MemIf.
 *
 * \version 5.11.20
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef MEMIF_INTERNAL_CFG_H
#define MEMIF_INTERNAL_CFG_H
[!VAR "MemIf_InternalCfg" = "'true'"!][!//
[!INCLUDE "MemIf_CommonCfg.m"!][!//

/*==================[includes]==============================================*/
[!//
/* !LINKSTO MemIf.SWS_MemIf_00037,1 */
#include <Std_Types.h>                            /* AUTOSAR standard types     */
#include <TSAutosar.h>                            /* EB specific standard types */

/* include lower layer headers */
[!LOOP "as:modconf('Ea')"!][!//
#include <[!CALL "HEADER_NAME", "ModName" = "'Ea'"!]>
[!ENDLOOP!][!//
[!//
[!LOOP "as:modconf('Fee')"!][!//
#include <[!CALL "HEADER_NAME", "ModName" = "'Fee'"!]>
[!ENDLOOP!][!//

/*==================[macros]================================================*/

[!IF "$NumDevices = 1"!][!//
/* !LINKSTO MemIf.SWS_MemIf_00019,1 */
[!/* *** determine device prefix *** */!][!/*
  */!][!IF "count(as:modconf('Ea')) = 1"!][!/*
    */!][!VAR "Prefix"!]Ea_[!ENDVAR!][!/*
  */!][!ELSE!][!/*
    */!][!VAR "Prefix"!]Fee_[!ENDVAR!][!/*
  */!][!ENDIF!][!//
[!//
[!IF "node:existsAndFalse(MemIfGeneral/MemIfMemAccUsage)"!]
#if (defined MEMIF_SETMODE_FCTPTR)
#error MEMIF_SETMODE_FCTPTR is already defined
#endif /* if (defined MEMIF_SETMODE_FCTPTR) */
/* function pointers for the function pointer arrays */
#define MEMIF_SETMODE_FCTPTR {[!"$Prefix"!]SetMode}
[!ENDIF!][!//

#if (defined MEMIF_READ_FCTPTR)
#error MEMIF_READ_FCTPTR is already defined
#endif /* if (defined MEMIF_READ_FCTPTR) */
#define MEMIF_READ_FCTPTR {[!"$Prefix"!]Read}

#if (defined MEMIF_WRITE_FCTPTR)
#error MEMIF_WRITE_FCTPTR is already defined
#endif /* if (defined MEMIF_READ_FCTPTR) */
#define MEMIF_WRITE_FCTPTR {[!"$Prefix"!]Write}

#if (defined MEMIF_CANCEL_FCTPTR)
#error MEMIF_CANCEL_FCTPTR is already defined
#endif /* if (defined MEMIF_READ_FCTPTR) */
#define MEMIF_CANCEL_FCTPTR {[!"$Prefix"!]Cancel}

#if (defined MEMIF_GETSTATUS_FCTPTR)
#error MEMIF_GETSTATUS_FCTPTR is already defined
#endif /* if (defined MEMIF_READ_FCTPTR) */
#define MEMIF_GETSTATUS_FCTPTR {[!"$Prefix"!]GetStatus}

#if (defined MEMIF_GETJOBRESULT_FCTPTR)
#error MEMIF_GETJOBRESULT_FCTPTR is already defined
#endif /* if (defined MEMIF_GETJOBRESULT_FCTPTR) */
#define MEMIF_GETJOBRESULT_FCTPTR {[!"$Prefix"!]GetJobResult}

#if (defined MEMIF_INVALIDATEBLOCK_FCTPTR)
#error MEMIF_INVALIDATEBLOCK_FCTPTR is already defined
#endif /* if (defined MEMIF_GETJOBRESULT_FCTPTR) */
#define MEMIF_INVALIDATEBLOCK_FCTPTR {[!"$Prefix"!]InvalidateBlock}

#if (defined MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR)
#error MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR is already defined
#endif /* if (defined MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR) */
#define MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR {[!"$Prefix"!]EraseImmediateBlock}
[!ENDIF!][!//
[!//
[!//
[!IF "$NumDevices > 1"!][!//
/* !LINKSTO MemIf.SWS_MemIf_00020,1 */
[!IF "node:existsAndFalse(MemIfGeneral/MemIfMemAccUsage)"!]
#if (defined MEMIF_SETMODE_FCTPTR)
#error MEMIF_SETMODE_FCTPTR is already defined
#endif /* if (defined MEMIF_SETMODE_FCTPTR) */
/* function pointers for the function pointer arrays */
#define MEMIF_SETMODE_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]SetMode,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}
[!ENDIF!][!//

#if (defined MEMIF_READ_FCTPTR)
#error MEMIF_READ_FCTPTR is already defined
#endif /* if (defined MEMIF_READ_FCTPTR) */
#define MEMIF_READ_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]Read,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

#if (defined MEMIF_WRITE_FCTPTR)
#error MEMIF_WRITE_FCTPTR is already defined
#endif /* if (defined MEMIF_WRITE_FCTPTR) */
#define MEMIF_WRITE_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]Write,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

#if (defined MEMIF_CANCEL_FCTPTR)
#error MEMIF_CANCEL_FCTPTR is already defined
#endif /* if (defined MEMIF_CANCEL_FCTPTR) */
#define MEMIF_CANCEL_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]Cancel,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

#if (defined MEMIF_GETSTATUS_FCTPTR)
#error MEMIF_GETSTATUS_FCTPTR is already defined
#endif /* if (defined MEMIF_GETSTATUS_FCTPTR) */
#define MEMIF_GETSTATUS_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]GetStatus,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

#if (defined MEMIF_GETJOBRESULT_FCTPTR)
#error MEMIF_GETJOBRESULT_FCTPTR is already defined
#endif /* if (defined MEMIF_GETJOBRESULT_FCTPTR) */
#define MEMIF_GETJOBRESULT_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]GetJobResult,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

#if (defined MEMIF_INVALIDATEBLOCK_FCTPTR)
#error MEMIF_INVALIDATEBLOCK_FCTPTR is already defined
#endif /* if (defined MEMIF_INVALIDATEBLOCK_FCTPTR) */
#define MEMIF_INVALIDATEBLOCK_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]InvalidateBlock,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

#if (defined MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR)
#error MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR is already defined
#endif /* if (defined MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR) */
#define MEMIF_ERASEIMMEDIATEBLOCK_FCTPTR \
{\
[!LOOP "text:split($Prefixes, ';')"!][!//
[!IF "(.) != '&_'"!][!//
  [!"."!]EraseImmediateBlock,\
[!ELSE!][!//
  NULL_PTR,\
[!ENDIF!][!//
[!ENDLOOP!][!//
}

[!ENDIF!][!//
/*==================[type definitions]======================================*/

/*==================[external data]=========================================*/

#endif /* ifndef MEMIF_INTERNAL_CFG_H */
/*==================[end of file]===========================================*/
