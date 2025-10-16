/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef DCM_DSP_SVCH_CLEARDIAGNOSTICINFORMATION_H
#define DCM_DSP_SVCH_CLEARDIAGNOSTICINFORMATION_H

/* !LINKSTO Dcm.Dsn.File.ClearDiagInfo.PublicApi,1 */
/* This file contains the public API of the implementation of the Diagnostic
 * Service ClearDiagnosticInformation. */

/*==================[inclusions]==================================================================*/

#include <Std_Types.h>         /* AUTOSAR standard types */
#include <Dcm_Int.h>

#include <Dcm_Cfg.h>
#include <Dcm_Dsl_Cfg.h>

#if (DCM_DSP_USE_SERVICE_0X14 == STD_ON)

#include <Dcm_Dsp_DemFacade.h>

#if (DCM_DEM_CLIENT_REF_USED == STD_ON)
#include <Dem.h>
#endif /* #if (DCM_DEM_CLIENT_REF_USED == STD_ON) */

/*==================[macro definitions]========================================================== */

#if (defined DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED)
  #error "DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED is already defined"
#endif
#if( ((DCM_HAS_ROE_TYPE2 == STD_ON) && (DCM_ROE_NUM_ROEONDTCSTATUSCHANGE > 0U)) ||\
      (DCM_NUM_STACKS > 1U) )
#define DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED  STD_ON
#else
#define DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED  STD_OFF
#endif

/*==================[type declarations]===========================================================*/

#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)

/** \brief This type contains the information needed while processing service
 * ClearDiagnosticInformation(0x14) */
typedef struct
{
  /** \brief This flag indicates if referenced DemClient is locked by that protocol */
  boolean DemClientOwner;
}
Dcm_ClearDiagnosticInfoContextType;

#endif /* #if ((DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

/*==================[external constant declarations]==============================================*/

/*==================[external data declarations]==================================================*/

/*==================[external function declarations]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the control structures for services 0x14
 */
extern FUNC(void, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_Init(void);

/** \brief Implement DEM access service 0x14
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_DSP_USE_SERVICE_0X14 == STD_ON) */

#endif /* ifndef DCM_DSP_SVCH_CLEARDIAGNOSTICINFORMATION_H */

/*==================[end of file]=================================================================*/
