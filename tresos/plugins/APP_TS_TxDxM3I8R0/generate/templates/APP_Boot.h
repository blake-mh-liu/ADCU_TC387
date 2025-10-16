/*********************************************************************************/
/*                                                                               */
/*                                  BOOT Stack                                   */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                APP                                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Boot.h                      */
/*%%  |                             |  %%                                        */
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
[!AUTOSPACING!]
#ifndef APP_BOOT_H
#define APP_BOOT_H

[!IF "node:exists(as:modconf('BM'))"!]
/* Specific BOOT value */
#define GO_IN_BOOT          0x00FF5500U
#define GO_IN_APP           0xAA005500U
[!ENDIF!]
[!IF "as:modconf('EB')/General/Protocol_Type = 'FLEXRAY'"!]
typedef u16 tNetworkStatus;
#define FR_NS_INIT               0x0000U
#define FR_NS_NORMAL             0x0001U
#define FR_NS_BOOT               0x1000U
#define FR_NS_UNDEFINED          0x2000U
[!ENDIF!]
extern u8 ubAPPFirstCall;

/* Address where is stored the start application address */
extern u32* __APPL_STARTUP_CODE; 

[!IF "node:exists(as:modconf('ProgVCC'))"!]
[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'"!]
/* Callback call by PROG module */
extern tProgStatus APP_MemStartErasing(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode);
[!ENDIF!]
[!ENDIF!]
#endif      /* APP_BOOT_H */

