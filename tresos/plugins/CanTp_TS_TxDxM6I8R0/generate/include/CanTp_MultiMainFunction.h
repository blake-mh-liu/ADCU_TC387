/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \version 6.8.63
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!CODE!]
[!AUTOSPACING!]
#ifndef CANTP_MULTIMAINFUNCTION_H
#define CANTP_MULTIMAINFUNCTION_H

/*==================[includes]===============================================*/
[!INCLUDE "../../generate_macros/CanTp_Precompile.m"!][!//
[!INCLUDE "../../generate_macros/CanTp_PostBuild.m"!][!//
#include <TSAutosar.h>              /* EB specific standard types */
[!IF "CanTpGeneral/CanTpGptUsageEnable = 'true'"!]
#include <Gpt.h>
[!ENDIF!][!//
#include <CanTp_InternalLib.h>      /* internal macros and variables */
#include <CanTp_Cfg.h>              /* CanTp configuration */
[!IF "CanTpJumpTable/CanTpJumpTableMode != 'OFF'"!][!//
#include <CanTp_ExitTableTypes.h>   /* CanTp jumptable type definitions */
[!ENDIF!][!//

/*==================[macros]=================================================*/
[!IF "CanTpGeneral/CanTpDedicatedChannelProcessingSupport = 'true'"!][!//
[!LOOP "as:modconf('CanTp')[1]/CanTpGeneral/CanTpChannelProcessing/*"!][!//
[!VAR "ChannelProcessingName" = "as:name(.)"!][!//
[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
#define CanTp_MainFunction_[!"$ChannelProcessingName"!]() CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MainFunction_[!"$ChannelProcessingName"!]()
[!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]

/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/


[!IF "CanTpGeneral/CanTpDedicatedChannelProcessingSupport = 'true'"!][!//
[!LOOP "as:modconf('CanTp')[1]/CanTpGeneral/CanTpChannelProcessing/*"!][!//
[!VAR "ChannelProcessingName" = "as:name(.)"!][!//
[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_START_SEC_CODE
#include <CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MemMap.h>
#endif
[!ELSE!]
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif
[!ENDIF!]
/**\brief Dedicated Main function of the CanTp for each partition.
 **
 ** This function is the main function for scheduling CanTP.
 **
 ** \ServiceID{0x06}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
extern FUNC(void, CANTP_CODE) CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MainFunction_[!"$ChannelProcessingName"!](void);
[!ELSE!]
extern FUNC(void, CANTP_CODE) CanTp_MainFunction_[!"$ChannelProcessingName"!](void);
[!ENDIF!]

[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_STOP_SEC_CODE
#include <CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MemMap.h>
#endif
[!ELSE!]
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif
[!ENDIF!]
[!ENDLOOP!][!//

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif
/**\brief Decoupled Rx Main function of the CanTp.
 **
 ** This function is the main function for scheduling CanTP Rx channels.
 **
 ** \ServiceID{0x06}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
 
extern FUNC(void, CANTP_CODE) CanTp_Decoupled_MainFunction_Rx(uint8 rx_channel);

/**\brief Decoupled Tx Main function of the CanTp.
 **
 ** This function is the main function for scheduling CanTP Tx channels.
 **
 ** \ServiceID{0x06}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANTP_CODE) CanTp_Decoupled_MainFunction_Tx(uint8 tx_channel);

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif
[!ENDIF!]

/*==================[end of file]============================================*/
#endif /* ifndef CANTP_MULTIMAINFUNCTION_H */
[!ENDCODE!][!//
