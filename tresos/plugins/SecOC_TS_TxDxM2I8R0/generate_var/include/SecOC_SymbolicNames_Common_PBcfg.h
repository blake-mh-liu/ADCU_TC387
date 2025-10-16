/**
 * \file
 *
 * \brief AUTOSAR SecOC
 *
 * This file contains the implementation of the AUTOSAR
 * module SecOC.
 *
 * \version 2.8.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]


#ifndef SECOC_SYMBOLICNAMES_PBCFG_H
#define SECOC_SYMBOLICNAMES_PBCFG_H


/*==================[includes]===============================================*/

[!LOOP "variant:all()"!][!//
#include <SecOC_SymbolicNames[!"."!]_PBcfg.h>
[!ENDLOOP!][!//

/*==================[macros]=================================================*/

[!VAR "NoVariants" = "variant:size()"!][!//
[!IF "$NoVariants > 1 "!][!//
#if (defined SECOC_MAX)
#error SECOC_MAX already defined
#endif
#define SECOC_MAX(a,b) ((a>b)?(a):(b))

#if (defined SECOC_MAX_PDU_MEM_SIZE)
#error SECOC_MAX_PDU_MEM_SIZE already defined
#endif
#define SECOC_MAX_PDU_MEM_SIZE \
[!VAR "count" = "0"!][!//
[!LOOP "variant:all()"!][!//
[!IF "$count < $NoVariants - 1"!][!//
                                SECOC_MAX(SECOC_[!"."!]_PBCFG_PDU_MEM_SIZE, \
[!ELSE!][!//
                                SECOC_[!"."!]_PBCFG_PDU_MEM_SIZE \
[!ENDIF!][!//
[!VAR "count" = "$count + 1"!][!//
[!ENDLOOP!][!//
[!IF "$NoVariants > 2"!]
[!LOOP "$NoVariants - 2"!][!//
[                               ) \
[!ENDLOOP!][!//
[!ENDIF!][!//
                                )

#if (defined SECOC_MAX_INT_MEM_SIZE)
#error SECOC_MAX_INT_MEM_SIZE already defined
#endif
#define SECOC_MAX_INT_MEM_SIZE \
[!VAR "count" = "0"!][!//
[!LOOP "variant:all()"!][!//
[!IF "$count < $NoVariants - 1"!][!//
                                SECOC_MAX(SECOC_[!"."!]_PBCFG_INT_MEM_SIZE, \
[!ELSE!][!//
                                SECOC_[!"."!]_PBCFG_INT_MEM_SIZE \
[!ENDIF!][!//
[!VAR "count" = "$count + 1"!][!//
[!ENDLOOP!][!//
[!IF "$NoVariants > 2"!]
[!LOOP "$NoVariants - 2"!][!//
[                               ) \
[!ENDLOOP!][!//
[!ENDIF!][!//
                                )

#if (defined SECOC_PB_PDU_MEM_SIZE)
#error SECOC_PB_PDU_MEM_SIZE already defined
#endif
#define SECOC_PB_PDU_MEM_SIZE       SECOC_MAX_PDU_MEM_SIZE

#if (defined SECOC_PB_INT_MEM_SIZE)
#error SECOC_PB_INT_MEM_SIZE already defined
#endif
#define SECOC_PB_INT_MEM_SIZE       SECOC_MAX_INT_MEM_SIZE
[!ENDIF!][!//

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef SECOC_SYMBOLICNAMES_PBCFG_H */
/*==================[end of file]============================================*/
[!ENDCODE!]
