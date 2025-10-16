/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 APP configuration                             */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Cbk.h                       */
/*%%  |                             |  %%  \brief APP layer include plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.8.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/

#ifndef APP_CBK_H
#define APP_CBK_H

/** \brief Callback to get reset type (HW or SW)
 **
 ** Callback to get reset type reason (at startup)
 ** or after a software reset
 **
 ** \return Reset type information
 ** \retval SOFT_RESET SW reset
 ** \retval POWER_ON Start Up
 **
 **/
extern u8 APP_GetResetType(void);

#endif      /* APP_CBK_H */
