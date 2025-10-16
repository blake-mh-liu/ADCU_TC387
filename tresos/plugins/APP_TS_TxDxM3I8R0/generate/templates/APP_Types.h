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
/*%%   _____________________________   %%  \file APP_Types.h                     */
/*%%  |                             |  %%  \brief APP layer types  */
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

#ifndef APP_TYPES_H
#define APP_TYPES_H

/** \brief Define APP_FALSE */
#define APP_FALSE               0U
/** \brief Define APP_TRUE */
#define APP_TRUE                1U
/** \brief definition of the tAppBoolean */
typedef u8 tAppBoolean;

/** \brief Define SOFT_RESET */
#define SOFT_RESET 0x00U
/** \brief Define POWER_ON */
#define POWER_ON   0x01U

#endif      /* APP_TYPES_H */
