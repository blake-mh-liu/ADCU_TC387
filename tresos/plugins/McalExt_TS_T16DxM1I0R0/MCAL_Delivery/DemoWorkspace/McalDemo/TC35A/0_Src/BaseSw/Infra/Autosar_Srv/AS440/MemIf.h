#ifndef MEMIF_H /* SWS_NvM_00446 { */
#define MEMIF_H
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : MemIf.h                                                    **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-24                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Header file containing exported interfaces and type        **
**                 definitions of MemIf module                                **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_MemoryAbstractionInterface,AUTOSAR         **
**                     Release 4.4.0                                          **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "Mcal_Version.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Function Like Macro Definitions                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
#if(MCAL_AR_VERSION == MCAL_AR_440)
/* SWS_MemIf_00064 */
typedef enum
{
  MEMIF_UNINIT,
  MEMIF_IDLE,
  MEMIF_BUSY,
  MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

/* SWS_MemIf_00065 */
typedef enum
{
  MEMIF_JOB_OK,
  MEMIF_JOB_FAILED,
  MEMIF_JOB_PENDING,
  MEMIF_JOB_CANCELED,
  MEMIF_BLOCK_INCONSISTENT,
  MEMIF_BLOCK_INVALID
} MemIf_JobResultType;

/* SWS_MemIf_00066 */
typedef enum
{
  MEMIF_MODE_SLOW,
  MEMIF_MODE_FAST
} MemIf_ModeType;
#endif
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#endif /* } MEMIF_TYPES_H_INCLUDED */

