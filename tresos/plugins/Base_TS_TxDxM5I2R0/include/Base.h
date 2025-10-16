#ifndef BASE_H
#define BASE_H
/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \version 5.2.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[includes]===============================================*/

#include <Base_Version.h>       /* This module's version declarations */

#include <TSAutosar.h>          /* includes Std_Types.h and other common header files */
#include <TSMem.h>
#include <TSMemS.h>
#include <TSAtomic_Assign.h>
#include <TSPBConfig.h>         /* includes other TSBPConfig_*.h files */
#include <TSCompiler_Default.h>
#include <Base_Modules.h>
#include <Base_Dbg.h>
#include <Compiler_Common.h>
#include <ComStack_Helpers.h>
#include <ComStack_Types.h>
#include <TransformerTypes.h>
#include <Can_GeneralTypes.h>
#include <Eth_GeneralTypes.h>
#include <Fr_GeneralTypes.h>
#include <Lin_GeneralTypes.h>


/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef BASE_H */
/*==================[end of file]============================================*/
