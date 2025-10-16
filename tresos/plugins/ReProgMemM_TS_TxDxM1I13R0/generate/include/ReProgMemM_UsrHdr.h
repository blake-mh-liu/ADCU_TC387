/**
 * \file
 *
 * \brief AUTOSAR ReProgMemM
 *
 * This file contains the implementation of the AUTOSAR
 * module ReProgMemM.
 *
 * \version 1.13.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef REPROGMEMM_USRHDR_H
#define REPROGMEMM_USRHDR_H

/* this just contains the inclusion directive for the user supplied header */

/*==================[inclusions]============================================*/

[!LOOP "as:modconf('ReProgMemM')/ReProgMemMHeaderFiles/ReProgMemMUserHeader/*"!][!//
[!IF "normalize-space(.) != ''"!][!//
#include <[!"normalize-space(.)"!]>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]================================================*/

/*==================[external function declarations]========================*/

/*==================[ end of external function declarations]================*/

#endif /* ifndef REPROGMEMM_USRHDR_H */

/*==================[end of file ReProgMemM_UsrHdr.h]==================================*/
