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

#ifndef DCM_DSP_SVCH_REQUESTCONTROLOFONBOARDSYSTSTCOMP_H
#define DCM_DSP_SVCH_REQUESTCONTROLOFONBOARDSYSTSTCOMP_H

/*==================[inclusions]=================================================================*/

#include <Std_Types.h>         /* AUTOSAR standard types */
#include <Dcm_Int.h>

#if((DCM_DSP_USE_SERVICE_0X08 == STD_ON) || \
    ((DCM_DSP_USE_SERVICE_0X31 == STD_ON) && \
     (DCM_DSP_NUM_REQUESTCONTROL_CFG != 0) && \
     (DCM_DSP_ENABLE_OBD_MIRROR == STD_ON)))

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief The generic service handler for OBD service 0x08
 **
 ** \param[in] OpStatus Operation status
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestControlOfOnBoardSysTstComp_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

/** \brief An adaptor to use the functionality of OBD service 0x08 (RequestControl)
 **        also for UDS service 0x31 (RoutineControl)
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK      Request accepted
 ** \retval E_NOT_OK  Request failed, ErrorCode is written
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReqCtrlViaRoutineCtrl_UDSShell(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* #if((DCM_DSP_USE_SERVICE_0X08 == STD_ON) || \
              ((DCM_DSP_USE_SERVICE_0X31 == STD_ON) && \
               (DCM_DSP_NUM_REQUESTCONTROL_CFG != 0) && \
               (DCM_DSP_ENABLE_OBD_MIRROR == STD_ON))) */

#endif /* ifndef DCM_DSP_SVCH_REQUESTCONTROLOFONBOARDSYSTSTCOMP_H */
/*==================[end of file]================================================================*/

