/**
 * \file
 *
 * \brief AUTOSAR J1939Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Nm.
 *
 * \version 1.1.13
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* This file generated from the configuration of J1939Nm module . */

[!CODE!]
[!INCLUDE "J1939Nm_Vars.m"!][!//
#ifndef J1939NM_EXTERNALS_H
#define J1939NM_EXTERNALS_H
[!//
/*==================[includes]===============================================*/
#include <J1939Nm_Types.h>

[!IF "node:exists(J1939NmGeneral/J1939NmUserCallout)"!]
#define J1939NM_START_SEC_CODE
#include <J1939Nm_MemMap.h>

extern FUNC(void, J1939NM_CODE) [!"J1939NmGeneral/J1939NmUserCallout"!](
    VAR(NetworkHandleType, AUTOMATIC) channel,
    VAR(uint8, AUTOMATIC) sourceAddress,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) name
);

#define J1939NM_STOP_SEC_CODE
#include <J1939Nm_MemMap.h>
[!ENDIF!]
#endif /* ifndef J1939NM_EXTERNALS_H */
/*==================[end of file]============================================*/
[!ENDCODE!]
