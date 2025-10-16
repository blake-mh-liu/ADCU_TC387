
#ifndef BLUPDATER_TRACE_H
#define BLUPDATER_TRACE_H
/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater layer                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Trace.h               */
/*%%  |                             |  %%  \brief BLUpdater trace debug mode     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.9.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*==================[inclusions]============================================*/


#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
#include "EB_Prj.h"

/*==================[macros]================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_ERASE_ENTRY
/** \brief Entry point of function BLU_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_ERASE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_ERASE_EXIT
/** \brief Exit point of function BLU_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_ERASE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_WRITE_ENTRY
/** \brief Entry point of function BLU_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_WRITE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_WRITE_EXIT
/** \brief Exit point of function BLU_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_WRITE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_MEMCMP_ENTRY
/** \brief Entry point of function BLU_MemCmp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_MEMCMP_ENTRY(pubMemoryAddress1,pubMemoryAddress2,ulMemorySize)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_MEMCMP_EXIT
/** \brief Exit point of function BLU_MemCmp()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLU_MEMCMP_EXIT(retval)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_COMPARE_ENTRY
/** \brief Entry point of function BLU_Compare()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_COMPARE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_COMPARE_EXIT
/** \brief Exit point of function BLU_Compare()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_COMPARE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_SECUREBOOTUPDATE_ENTRY
/** \brief Entry point of function BLU_SecureBootUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_SECUREBOOTUPDATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_SECUREBOOTUPDATE_EXIT
/** \brief Exit point of function BLU_SecureBootUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_SECUREBOOTUPDATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_FLASHASYNCHJOB_ENTRY
/** \brief Entry point of function BLU_FlashAsynchJob()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_FLASHASYNCHJOB_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_FLASHASYNCHJOB_EXIT
/** \brief Exit point of function BLU_FlashAsynchJob()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_FLASHASYNCHJOB_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_TRIGGERING_NRC78_ENTRY
/** \brief Entry point of function BLU_Triggering_NRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_TRIGGERING_NRC78_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_TRIGGERING_NRC78_EXIT
/** \brief Exit point of function BLU_Triggering_NRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_TRIGGERING_NRC78_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_START_ENTRY
/** \brief Entry point of function BLU_Start()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_START_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_START_EXIT
/** \brief Exit point of function BLU_Start()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_START_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_RESET_ENTRY
/** \brief Entry point of function BLU_Reset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_RESET_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_RESET_EXIT
/** \brief Exit point of function BLU_Reset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_RESET_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_INIT_ENTRY
/** \brief Entry point of function BLU_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_INIT_EXIT
/** \brief Exit point of function BLU_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_MANAGE_ENTRY
/** \brief Entry point of function BLU_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLU_MANAGE_EXIT
/** \brief Exit point of function BLU_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLU_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURIFTXCONFIRMATION_ENTRY
/** \brief Entry point of function BLUpdater_PduRIfTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURIFTXCONFIRMATION_ENTRY(TxPduId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURIFTXCONFIRMATION_EXIT
/** \brief Exit point of function BLUpdater_PduRIfTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURIFTXCONFIRMATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURIFRXINDICATION_ENTRY
/** \brief Entry point of function BLUpdater_PduRIfRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURIFRXINDICATION_ENTRY(RxPduId,PduInfoPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURIFRXINDICATION_EXIT
/** \brief Exit point of function BLUpdater_PduRIfRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURIFRXINDICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPCOPYTXDATA_ENTRY
/** \brief Entry point of function BLUpdater_PduRTpCopyTxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPCOPYTXDATA_ENTRY(TxPduId,PduInfoPtr,RetryInfoPtr,AvailableDataPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPCOPYTXDATA_EXIT
/** \brief Exit point of function BLUpdater_PduRTpCopyTxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPCOPYTXDATA_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPTXCONFIRMATION_ENTRY
/** \brief Entry point of function BLUpdater_PduRTpTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPTXCONFIRMATION_ENTRY(TxPduId,Result)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPTXCONFIRMATION_EXIT
/** \brief Exit point of function BLUpdater_PduRTpTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPTXCONFIRMATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPCOPYRXDATA_ENTRY
/** \brief Entry point of function BLUpdater_PduRTpCopyRxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPCOPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPCOPYRXDATA_EXIT
/** \brief Exit point of function BLUpdater_PduRTpCopyRxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPCOPYRXDATA_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPSTARTOFRECEPTION_ENTRY
/** \brief Entry point of function BLUpdater_PduRTpStartOfReception()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPSTARTOFRECEPTION_ENTRY(TxPduId,TpSduLength,BufferSizePtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPSTARTOFRECEPTION_EXIT
/** \brief Exit point of function BLUpdater_PduRTpStartOfReception()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPSTARTOFRECEPTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPRXINDICATION_ENTRY
/** \brief Entry point of function BLUpdater_PduRTpRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPRXINDICATION_ENTRY(RxPduId,Result)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLUPDATER_PDURTPRXINDICATION_EXIT
/** \brief Exit point of function BLUpdater_PduRTpRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLUPDATER_PDURTPRXINDICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif      /* BLUPDATER_TRACE_H */
/*==================[end of file]===========================================*/
