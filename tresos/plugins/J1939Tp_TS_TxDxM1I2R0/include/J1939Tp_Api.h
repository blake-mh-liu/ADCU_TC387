/**
 * \file
 *
 * \brief AUTOSAR J1939Tp
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Tp.
 *
 * \version 1.2.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef J1939TP_API_H
#define J1939TP_API_H

/*==================[inclusions]=============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR COM types */
#include <J1939Tp_Version.h>      /* J1939TP version declaration */
#include <J1939Tp_Cfg.h>          /* J1939TP configuration */
#include <J1939Tp_Typedefs.h>        /* J1939TP type definitions */
#include <J1939Tp_Types_Int.h>    /* J1939TP PostBuild type definitions */
#if (J1939TP_PBCFGM_SUPPORT_ENABLED == STD_ON)

#include <PbcfgM_Api.h>         /* Post build configuration manager */
#endif /* J1939TP_PBCFGM_SUPPORT_ENABLED */

/*==================[macros]=================================================*/

/*------------------[API service IDs]----------------------------------------*/

/*------------------[Development error codes]--------------------------------*/

/*------------------[Development runtime error codes]--------------------------------*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#define J1939TP_START_SEC_CODE
#include <J1939Tp_MemMap.h>

/** \brief Validate configuration
 **
 ** Checks if the post build configuration fits to the link time configuration part.
 **
 ** \return E_OK if the given module configurations is valid otherwise E_NOT_OK.
 **
 ** \ServiceID{0x60}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC( Std_ReturnType, J1939TP_CODE) J1939Tp_IsValidConfig
  (
    P2CONST(void,AUTOMATIC,J1939TP_APPL_CONST) voidConfigPtr
  );

#define J1939TP_STOP_SEC_CODE
#include <J1939Tp_MemMap.h>


/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef J1939TP_API_H */
/*==================[end of file]============================================*/
