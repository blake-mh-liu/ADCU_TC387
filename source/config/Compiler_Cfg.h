/**
 * \file
 *
 * \brief AUTOSAR ApplTemplates
 *
 * This file contains the implementation of the AUTOSAR
 * module ApplTemplates.
 *
 * \version 6.8.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/* This file is an user-specific file and will be delivered only as a template
 * which works together with all ACG-modules by EB.
 * The integrator needs to merge all Compiler_Cfg.h file of all module vendors.
 * Proposed process is specified in AUTOSAR_SWS_CompilerAbstraction
 * specification.
 */

/*==================[inclusions]=============================================*/

/*------------------[Compiler_Cfg extensions]--------------------------------*/
/** \def COMPILERCFG_EXTENSION_FILE
 ** \brief Includes an additional Compiler_CfgExt.h file if macro is available.
 ** 
 ** The macro COMPILERCFG_EXTENSION_FILE is generated in the Compiler_CfgInt.h
 ** file based on configuration in Compiler.xdm file. If the macro 
 ** COMPILERCFG_EXTENSION_FILE is defined, EB Compiler_Cfg.h file will include 
 ** an additional file Compiler_CfgExt.h. This file can be used to add memory
 ** and pointer classes of 3rd-party modules.
 */
#ifdef COMPILERCFG_EXTENSION_FILE
#include <Compiler_CfgExt.h>
#endif

/*==================[macros]=================================================*/


#endif /* if !defined( COMPILER_CFG_H ) */
/*==================[end of file]============================================*/
