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
/*%%   _____________________________   %%  \file BLUpdater_Priv.h                */
/*%%  |                             |  %%  \brief BLUpdater layer source plugin file */
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

#ifndef BLUPDATER_PRIV_H
#define BLUPDATER_PRIV_H



/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
/* Counter for triggering periodically NRC 78 */
extern u16 m_uwCount;
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */

/* Global status of different operations asked to Flash driver */
#if (BLU_FLASHWRAPPER_ENABLED == STD_ON)
extern tFlashStatus m_ubFlashStatus;
#elif (BLU_REPROGMEMM_ENABLED == STD_ON)
extern Std_ReturnType m_ubFlashStatus;
#endif
/* Global status of current operation in progress (Write, Erase, Compare) */
extern tBLUOperation m_ubCurrentBLUOperation;

/* Contains request information */
extern PduInfoType m_stDiagMessageInfo;
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */


/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

#endif
