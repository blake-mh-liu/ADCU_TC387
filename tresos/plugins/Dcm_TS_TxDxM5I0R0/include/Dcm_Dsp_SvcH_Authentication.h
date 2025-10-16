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

/* !LINKSTO Dcm.Dsn.File.AuthenticationSvcH.PublicApi,1 */
/* This file contains the public API of the Diagnostic Service Authentication. */

#ifndef DCM_DSP_SVCH_AUTHENTICATION_H
#define DCM_DSP_SVCH_AUTHENTICATION_H

/*==================[inclusions]=================================================================*/

#include <Dcm_Int.h>                                              /* Module internal definitions */

#if (DCM_DSP_USE_SERVICE_0X29 == STD_ON)

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the generic service handler for UDS service 0x29
 */

extern FUNC(void, DCM_CODE) Dcm_Dsp_Authentication_Init(void);

/** \brief The generic service handler for UDS service 0x29
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed with success
 ** \retval E_NOT_OK           Operation completed with failure
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 */

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#if (DCM_0X29_0X00_SSVC_ENABLED == STD_ON)
/** \brief Internal sub-service handler DeAuthenticate(0x00) for UDS service 0x29
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK               Operation completed with success
 ** \retval E_NOT_OK           Operation completed with failure
 */

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_DeAuthenticate_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_0X29_0X00_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X01_SSVC_ENABLED == STD_ON)
/** \brief Internal sub-service handler VerifyCertificateUnidirectional(0x01) for UDS service 0x29
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK               Operation completed with success
 ** \retval E_NOT_OK           Operation completed with failure
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 */

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_VerifyCertificateUnidirectional_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_0X29_0X01_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/** \brief Internal sub-service handler VerifyCertificateBidirectional(0x02) for UDS service 0x29
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK               Operation completed with success
 ** \retval E_NOT_OK           Operation completed with failure
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 */

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_VerifyCertificateBidirectional_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X03_SSVC_ENABLED == STD_ON)
/** \brief Internal sub-service handler ProofOfOwnership(0x03) for UDS service 0x29
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK               Operation completed with success
 ** \retval E_NOT_OK           Operation completed with failure
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 */

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_ProofOfOwnership_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_0X29_0X03_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X08_SSVC_ENABLED == STD_ON)
/** \brief Internal sub-service handler AuthenticationConfiguration(0x08) for UDS service 0x29
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK               Operation completed with success
 ** \retval E_NOT_OK           Operation completed with failure
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_AuthenticationConfiguration_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_0X29_0X08_SSVC_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* #if (DCM_DSP_USE_SERVICE_0X29 == STD_ON) */
#endif /* #ifndef DCM_DSP_SVCH_AUTHENTICATION_H */
/*==================[end of file]================================================================*/
