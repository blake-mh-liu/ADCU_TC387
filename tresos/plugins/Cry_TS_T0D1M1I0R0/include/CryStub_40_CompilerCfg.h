/**
 * \file
 *
 * \brief AUTOSAR Cry
 *
 * This file contains the implementation of the AUTOSAR
 * module Cry.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CRYSTUB_40_COMPILER_CFG_H
#define CRYSTUB_40_COMPILER_CFG_H

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[memory and pointer class of a module]-------------------*/

#if (defined CRYSTUB_40_CODE)
#error CRYSTUB_40_CODE already defined
#endif
#define CRYSTUB_40_CODE

#if (defined CRYSTUB_40_CONST)
#error CRYSTUB_40_CONST already defined
#endif
#define CRYSTUB_40_CONST

#if (defined CRYSTUB_40_APPL_DATA)
#error CRYSTUB_40_APPL_DATA already defined
#endif
#define CRYSTUB_40_APPL_DATA

#if (defined CRYSTUB_40_APPL_CONST)
#error CRYSTUB_40_APPL_CONST already defined
#endif
#define CRYSTUB_40_APPL_CONST

#if (defined CRYSTUB_40_APPL_CODE)
#error CRYSTUB_40_APPL_CODE already defined
#endif
#define CRYSTUB_40_APPL_CODE

#if (defined CRYSTUB_40_VAR_NOINIT)
#error CRYSTUB_40_VAR_NOINIT already defined
#endif
#define CRYSTUB_40_VAR_NOINIT

#if (defined CRYSTUB_40_VAR_POWER_ON_INIT)
#error CRYSTUB_40_VAR_POWER_ON_INIT already defined
#endif
#define CRYSTUB_40_VAR_POWER_ON_INIT

#if (defined CRYSTUB_40_VAR_FAST)
#error CRYSTUB_40_VAR_FAST already defined
#endif
#define CRYSTUB_40_VAR_FAST

#if (defined CRYSTUB_40_VAR)
#error CRYSTUB_40_VAR already defined
#endif
#define CRYSTUB_40_VAR

#endif /* #ifndef CRYSTUB_40_COMPILER_CFG_H */

/*==================[end of file]============================================*/
