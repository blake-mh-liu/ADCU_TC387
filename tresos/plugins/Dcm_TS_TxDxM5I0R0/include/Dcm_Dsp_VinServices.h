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

#ifndef DCM_DSP_VINSERVICES_H
#define DCM_DSP_VINSERVICES_H

/* !LINKSTO Dcm.Dsn.File.VinServices.PublicApi,1 */
/* This file contains the public API of the VIN services software unit. */

/*==================[inclusions]=================================================================*/

#include <Std_Types.h>         /* AUTOSAR standard types */
#include <Dcm_Int.h>
#include <Dcm_RequestVehicleInformation_Cfg.h>
#include <Dcm_Dsp_SvcH_RequestVehicleInformation.h>

/*==================[macros]=====================================================================*/
/* Check if the lock mechanism for VinServices unit is needed */
#if ((DCM_DSP_USE_VINSERVICES == STD_ON) && (DCM_DSP_VEHINFO_NUM > 0))
/** \brief Enables the use of lock mechanism for VinServices unit */
#define DCM_DSP_VINSERVICES_LOCK_MECHANISM_ENABLED STD_ON

/** \brief Macros for LockStatus used in InputOutputControlByIdentifier and WriteDataByIdentifier
 **        services.
 */
#define DCM_TRYING_LOCK                            (0x00U)
#define DCM_EXECUTING_SERVICE                      (0x01U)

#else
/** \brief Disables the use of lock mechanism for DidServices unit */
#define DCM_DSP_VINSERVICES_LOCK_MECHANISM_ENABLED STD_OFF
#endif

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

#if (DCM_DSP_USE_VINSERVICES == STD_ON)

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if (DCM_DSP_VINSERVICES_LOCK_MECHANISM_ENABLED == STD_ON)
/** \brief Function to lock the VinServices when they need to be used exclusively by one user
 **
 ** \retval DCM_E_OK                Service successfully locked
 ** \retval DCM_E_RESOURCE_LOCKED   Service locked and not available
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_VinServices_LockService(void);

/** \brief Function to unlock the VinServices after they were locked
 **/
extern FUNC(void, DCM_CODE) Dcm_Dsp_VinServices_UnlockService(void);
#endif /* #if (DCM_DSP_VINSERVICES_LOCK_MECHANISM_ENABLED == STD_ON) */

/** \brief Function used to initialize the InfoType
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_VinServices_HelperInit(
  Dcm_DspVehInfoInfoTypeType  VehInfoInfoType,
  P2VAR(Dcm_DspReqVehInfoContextType, AUTOMATIC, DCM_VAR) svcContext,
  P2VAR(Dcm_DspMsgBufferCfgType, AUTOMATIC, DCM_VAR) ResBuffer);

/** \brief Function used to execute an InfoType
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_VinServices_HelperExecute(
  Dcm_OpStatusType OpStatus,
  Dcm_DspVehInfoInfoTypeType VehInfoInfoType,
  P2VAR(Dcm_DspReqVehInfoContextType, AUTOMATIC, DCM_VAR) svcContext);

/** \brief Function used for canceling the execution of an InfoType
 **/
extern FUNC(void, DCM_CODE) Dcm_Dsp_VinServices_HelperCancel(
  P2VAR(Dcm_DspReqVehInfoContextType, AUTOMATIC, DCM_VAR) svcContext);

/** \brief Return the availability data for the requested availability InfoTypeID
 *
 *  \param InfoTypeID       [in] The requested availability InfoTypeID.
 *  \param AvailabilityData [in] The availibility data for the requested InfoTypeID

 * \retval DCM_E_OK         The availibility data was updated
 * \retval DCM_E_NOT_OK     The availibility data was not updated
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_VinServices_GetAvailabilityInfoTypeId(
  Dcm_DspVehInfoInfoTypeType InfoTypeID,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) AvailabilityData);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if(DCM_DSP_USE_VINSERVICES == STD_ON) */

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* ifndef DCM_DSP_VINSERVICES_H */
/*==================[end of file]================================================================*/

