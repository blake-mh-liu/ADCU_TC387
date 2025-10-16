/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \version 6.3.59
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */

#include <Com_Core_IPduGroup.h>    /* Header IPduGroup functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <Com_MemMap.h>
#endif

/**
 * \brief Com_ReceptionDMControl - enables or disables Rx I-PDU
 * Deadline Monitoring
 *
 * Function to enables/disables every RxDM of every Rx-IPdu according to the
 * passed states of the ComIpduGroups in the parameter ipduGroupVector.
 * Preconditions:
 * - COM must be initialized
 *
 * \param[in] ipduGroupVector - I-PDU group vector containing the activation
 * of RxDM (disable = 0/ enable = 1) for all Rx-Pdus.
 *
 * \ServiceID{0x06}
 * \Reentrancy{Non Reentrant}
 * \Synchronicity{Synchronous}
 */
FUNC(void, COM_CODE)  Com_ReceptionDMControl
(
   Com_IpduGroupVector ipduGroupVector
)
{
    DBG_COM_RECEPTIONDMCONTROL_ENTRY(ipduGroupVector);

#if (COM_DEV_ERROR_DETECT == STD_ON)

    /* check whether COM is initialized */

    if (Com_InitStatus == COM_EB_UNINIT)
    {
        COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_ReceptionDMControl);
    }
    /* check ipduGroupVector */
    else if (ipduGroupVector == NULL_PTR)
    {
        COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_ReceptionDMControl);
    }
    else

#endif /* COM_DEV_ERROR_DETECT */

    {

#if (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_ON)

        Com_ReceptionDMControl_UserCallout(ipduGroupVector);

#else

        Com_EB_HandlePduGroupRx(COM_IPDUGROUP_RXDM_CONTROL, ipduGroupVector, FALSE);

#endif /* (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_OFF) */
    }

    DBG_COM_RECEPTIONDMCONTROL_EXIT(ipduGroupVector);
}                               /* Com_ReceptionDMControl */

#if (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_ON)

/**
 * \brief Com_EnableReceptionDM - enables Rx I-PDU
 * Deadline Monitoring
 *
 * Function to enables RxDM of Rx-IPdu according to the
 * passed states of the ComIpduGroup in the parameter IpduGroupId.
 * Preconditions:
 * - COM must be initialized
 *
 * \param[in] IpduGroupId - Id of I-PDU group where reception DM shall be enabled.
 */
FUNC(void, COM_CODE) Com_EnableReceptionDM
(
   Com_IpduGroupIdType IpduGroupId
)
{
   DBG_COM_ENABLERECEPTIONDM_ENTRY(IpduGroupId);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether COM is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_EnableReceptionDM);
   }
   /* check IpduGroupId */
   else if (IpduGroupId >= COM_SUPPORTED_IPDU_GROUPS)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_EnableReceptionDM);
   }
   else

#endif /* COM_DEV_ERROR_DETECT */

   {

       COM_AtomicSetBit_8(&Com_IpduGroupVectorStateDM[IpduGroupId/8U], IpduGroupId % 8U);

       Com_EB_HandlePduGroupRx_MainFunction(COM_IPDUGROUP_RXDM_CONTROL, Com_IpduGroupVectorStateDM,
                                            IpduGroupId, FALSE);

   }

   DBG_COM_ENABLERECEPTIONDM_EXIT(IpduGroupId);
}                               /* Com_EnableReceptionDM */

/**
 * \brief Com_DisableReceptionDM - disables Rx I-PDU
 * Deadline Monitoring
 *
 * Function to disables RxDM of Rx-IPdu according to the
 * passed states of the ComIpduGroup in the parameter IpduGroupId.
 * Preconditions:
 * - COM must be initialized
 *
 * \param[in] IpduGroupId - Id of I-PDU group where reception DM shall be disabled.
 */
FUNC(void, COM_CODE) Com_DisableReceptionDM
(
   Com_IpduGroupIdType IpduGroupId
)
{
   DBG_COM_DISABLERECEPTIONDM_ENTRY(IpduGroupId);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether COM is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_DisableReceptionDM);
   }
   /* check IpduGroupId */
   else if (IpduGroupId >= COM_SUPPORTED_IPDU_GROUPS)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_DisableReceptionDM);
   }
   else

#endif /* COM_DEV_ERROR_DETECT */

   {

       COM_AtomicClearBit_8(&Com_IpduGroupVectorStateDM[IpduGroupId/8U], IpduGroupId % 8U);

       Com_EB_HandlePduGroupRx_MainFunction(COM_IPDUGROUP_RXDM_CONTROL, Com_IpduGroupVectorStateDM,
                                            IpduGroupId, FALSE);

   }

   DBG_COM_DISABLERECEPTIONDM_EXIT(IpduGroupId);
}                               /* Com_DisableReceptionDM */

#endif /* (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_OFF) */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
