/**
 * \file
 *
 * \brief AUTOSAR J1939Rm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Rm.
 *
 * \version 1.1.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef J1939RM_INT_H
#define J1939RM_INT_H

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 * Reason:
 * The macro is used in function parameter declarations and definitions where the number of
 * parentheses matter.
 *
 */

/*===============================[includes]=================================*/

#include <TSAutosar.h>          /* EB specific standard types */

#include <J1939Rm_Api.h>              /* Types and decl. from public API */
#include <J1939Rm_Cfg.h>          /* Module configuration */
#include <ComStack_Types.h>     /* Include for PduInfoType */

#if (defined TS_RELOCATABLE_CFG_ENABLE)
#error TS_RELOCATABLE_CFG_ENABLE is already defined
#endif
#define TS_RELOCATABLE_CFG_ENABLE J1939RM_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig.h>           /* relocatable post-build macros */
#include <TSPBConfig_Access.h>

/*===========================[macro definitions]============================*/
#undef TS_RELOCATABLE_CFG_ENABLE
#endif /* ifndef J1939RM_INT_H */

/*==============================[end of file]===============================*/
