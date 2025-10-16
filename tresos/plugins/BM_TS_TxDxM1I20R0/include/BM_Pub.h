#ifndef BM_PUB_H
#define BM_PUB_H

/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Pub.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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

#include "BM_Cfg.h"

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if ((BM_CSM_HASH_USED == STD_ON) || (BM_CSM_MAC_USED == STD_ON))
#include "Csm.h"
#endif
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
#if (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER)
/** \brief Initial Boot Manager Startup
 **
 ** Called at the startup of the ECU to check if we start
 ** the Application, BLUpdater or the Bootloader
 **
 ** This function handles:
 ** - The check of application validity flag
 ** - The check of BLUpdater validity flag
 ** - The check of Bootloader validity flag
 **
 **/
extern void BM_InitialBootStartUp(void);
#else
/** \brief Bootmanager startup
 **
 ** If the Initial Boot Manager exists, it's called by the Initial Boot Manager StartUp if the bootloader should be started
 ** Other, at the very beginning of the ECU startup shall be the first one called.
 **
 ** This function handles:
 ** - The hardware initialization
 ** - The check of the boot flag
 ** - The validity of application
 ** - The initialization of all EB layer if bootloader shall be started
 **
 **/
extern void BM_StartUp(void);


/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)
/** \brief Manage BM layer
 **
 ** This function will ensure the good behaviour of the startup timeout of 5ms
 ** requested before checking the application validity.
 **
 ** BM_Manage shall be called at the same period and after EB_Manage.
 **
 **/
extern void BM_Manage (void);
#endif

#if ((BM_CSM_HASH_USED == STD_ON) || (BM_CSM_MAC_USED == STD_ON))
/** \brief CSM notification callback
 **
 ** \param[in] result Csm calculation result
 **
 ** \return status
 ** \retval E_OK
 **
 **/
#if (BM_CSM_ASR43_USED == STD_ON)
extern FUNC(void, CSM_APPL_CODE) BM_CsmNotification(P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job, Std_ReturnType result);
#else
extern Std_ReturnType BM_CsmNotification(Csm_ReturnType result);
#endif
#endif
#endif /* (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER) */
/*===============================================================================*/

#endif      /* BM_PUB_H */
