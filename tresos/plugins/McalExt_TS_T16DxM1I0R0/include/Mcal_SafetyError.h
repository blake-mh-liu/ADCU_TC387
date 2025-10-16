/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Mcal_SafetyError.h                                         **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-08                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Safety Error Roporting header definition file              **
**                                                                            **
**  SPECIFICATION(S) : Safety requirements.                                   **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef _MCAL_SAFETY_ERROR_H
#define _MCAL_SAFETY_ERROR_H

/*
Note: Elektrobit Automotive GmbH modified the original code provided
      by the third party supplier. The modification is provided for
      convenience.
      Please use the modification on your discretion and account, or
      use the unmodified files provided with this distribution. 
      Please see for the reasons in the file ImportantNotes.txt for tag
      
      Infineon Specific Test code has been removed
      
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
/*#if (APP_SW == TEST_APP)
#include "Test_Mcal_SafetyError.h"
#endif *//*#if (APP_SW == TEST_APP)*/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define MCAL_SAFETY_ERROR_RELEASE_MAJOR_VERSION 4U
#define MCAL_SAFETY_ERROR_RELEASE_MINOR_VERSION 2U

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern void Mcal_ReportSafetyError(uint16 ModuleId, uint8 InstanceId, \
                                   uint8 ApiId, uint8 ErrorId);

#endif /* End of _MCAL_SAFETY_ERROR_H */

