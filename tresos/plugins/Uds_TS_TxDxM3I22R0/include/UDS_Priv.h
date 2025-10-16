#ifndef UDS_PRIV_H
#define UDS_PRIV_H

/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               UDS layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Priv.h                     */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.22.0 BL3 */
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


/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                            */

#if (UDS_SRV_CFG2_MAX !=0)
/** \brief Current data identifier **/
extern u16 m_uwDid;
#endif
#if (UDS_SRV_CFG3_MAX !=0)
/** \brief Current routine identifier **/
extern u16 m_uwRi;
#endif
/** \brief Current service index of the Diagnostic services configuration array **/

extern tUdsSrvIdx m_uSrvIdx;

extern tUdsBoolean m_eSuppresPosRspMsgIndicationBit;

/** \brief Current start service index **/
extern tUdsSrvIdx m_uStartSrvIdx;

/** \brief Current start sub-service index **/
extern tUdsSrvIdx m_uStartSubSrvIdx;

/** \brief addressing mode **/
extern tUdsAddrMode m_eUdsAddrMode;
#if (UDS_SRV_CFG5_MAX !=0)
/** \brief Is there an obd service in treatment **/
extern tUdsBoolean m_eUdsObdService;
#endif

/** \brief Current session index **/
extern tUdsSessionIndex m_eSessionIdx;
/** \brief Sessions time counter, to limit a Diagnostic session to UDS_SESS_TIMEOUT **/
extern tUdsSessionTimeout m_uSessionTimeCnt;

#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
/** \brief Long request behavior enabling **/
extern tUdsLongRequestStr m_stLongRequest;
#endif
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */


/* - PRivate Function Prototypes                                                  */



/*                                                                               */
/*-------------------------------------------------------------------------------*/


#endif      /* UDS_PRIV_H */
