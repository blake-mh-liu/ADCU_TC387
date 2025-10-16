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
 * \brief Com_IpduGroupControl - starts/stops  I-PDU
 *
 * Function to start/stop every Rx-Ipdu and Tx-Ipdu according to the passed
 * states of the ComIpduGroups in the parameter ipduGroupVector.
 * Preconditions:
 * - COM must be initialized
 *
 * \param[in] ipduGroupVector - I-PDU group vector containing the activation
 * state (stopped = 0/ started = 1) for all IPdus.
 * \param[in] Initialize - flag to request initialization of the I-PDUs which
 * are newly started
 */
FUNC(void, COM_CODE) Com_IpduGroupControl
(
   Com_IpduGroupVector ipduGroupVector,
   boolean Initialize
)
{
   DBG_COM_IPDUGROUPCONTROL_ENTRY(ipduGroupVector,Initialize);
#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether COM is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_IpduGroupControl);
   }
   /* check ipduGroupVector */
   else if (ipduGroupVector == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_IpduGroupControl);
   }
   else

#endif /* COM_DEV_ERROR_DETECT */

   {
#if (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_ON)

      Com_IpduGroupControl_UserCallout(ipduGroupVector, Initialize);

#else

      DBG_COM_EB_HANDLEPDUGROUPRX_ENTRY(ipduGroupVector,Initialize);
      Com_EB_HandlePduGroupRx(COM_IPDUGROUP_CONTROL, ipduGroupVector, Initialize);
      DBG_COM_EB_HANDLEPDUGROUPRX_EXIT(ipduGroupVector,Initialize);

      DBG_COM_EB_HANDLEPDUGROUPTX_ENTRY(ipduGroupVector,Initialize);
      Com_EB_HandlePduGroupTx(ipduGroupVector, Initialize);
      DBG_COM_EB_HANDLEPDUGROUPTX_EXIT(ipduGroupVector,Initialize);

#endif /* (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_ON) */
   }

   DBG_COM_IPDUGROUPCONTROL_EXIT(ipduGroupVector,Initialize);
}                               /* Com_IpduGroupControl */

#if (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_ON)

/**
 * \brief Com_IpduGroupStart - starts I-PDU
 *
 * Function to start Rx-Ipdu and Tx-Ipdu according to there ComIpduGroup.
 * Preconditions:
 * - COM must be initialized
 *
 * \param[in] IpduGroupId - Id of I-PDU group to be started.
 * \param[in] Initialize - flag to request initialization of the data
 * in the I-PDUs of this I-PDU group
 */
FUNC(void, COM_CODE) Com_IpduGroupStart
(
   Com_IpduGroupIdType IpduGroupId,
   boolean initialize
)
{
   DBG_COM_IPDUGROUPSTART_ENTRY(IpduGroupId,initialize);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether COM is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_IpduGroupStart);
   }
   /* check IpduGroupId */
   else if (IpduGroupId >= COM_SUPPORTED_IPDU_GROUPS)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_IpduGroupStart);
   }
   else

#endif /* COM_DEV_ERROR_DETECT */

   {

       COM_AtomicSetBit_8(&Com_IpduGroupVectorState[IpduGroupId/8U], IpduGroupId % 8U);
       COM_AtomicSetBit_8(&Com_IpduGroupVectorStateDM[IpduGroupId/8U], IpduGroupId % 8U);

       /* check if Tx or Rx Main function or unassigned */
       if(IpduGroupId < (uint16)(Com_gConfigPtr->ComRxIpduGroupVectorBitEnd) )
       {
           Com_EB_HandlePduGroupRx_MainFunction(COM_IPDUGROUP_CONTROL, Com_IpduGroupVectorState,
                                                IpduGroupId, initialize);
       }
       else if(IpduGroupId >= Com_gConfigPtr->ComTxIpduGroupVectorBitStart)
       {
           Com_EB_HandlePduGroupTx_MainFunction(Com_IpduGroupVectorState,
                                                IpduGroupId, initialize);
       }
       else
       {
           Com_EB_HandlePduGroupRx_MainFunction(COM_IPDUGROUP_CONTROL, Com_IpduGroupVectorState,
                                                IpduGroupId, initialize);
           Com_EB_HandlePduGroupTx_MainFunction(Com_IpduGroupVectorState,
                                                IpduGroupId, initialize);
       }

   }

   DBG_COM_IPDUGROUPSTART_EXIT(IpduGroupId,initialize);
}                               /* Com_IpduGroupStart */

/**
 * \brief Com_IpduGroupStop - stops I-PDU
 *
 * Function to stop Rx-Ipdu and Tx-Ipdu according to there ComIpduGroup.
 * Preconditions:
 * - COM must be initialized
 *
 * \param[in] IpduGroupId - Id of I-PDU group to be started.
 */
FUNC(void, COM_CODE) Com_IpduGroupStop
(
   Com_IpduGroupIdType IpduGroupId
)
{
   DBG_COM_IPDUGROUPSTOP_ENTRY(IpduGroupId);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether COM is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_IpduGroupStop);
   }
   /* check IpduGroupId */
   else if (IpduGroupId >= COM_SUPPORTED_IPDU_GROUPS)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_IpduGroupStop);
   }
   else

#endif /* COM_DEV_ERROR_DETECT */

   {

       COM_AtomicClearBit_8(&Com_IpduGroupVectorState[IpduGroupId/8U], IpduGroupId % 8U);
       COM_AtomicClearBit_8(&Com_IpduGroupVectorStateDM[IpduGroupId/8U], IpduGroupId % 8U);

       /* check if Tx or Rx Main function or unassigned */
       if(IpduGroupId < (uint16)(Com_gConfigPtr->ComRxIpduGroupVectorBitEnd) )
       {
           Com_EB_HandlePduGroupRx_MainFunction(COM_IPDUGROUP_CONTROL, Com_IpduGroupVectorState,
                                                IpduGroupId, FALSE);
       }
       else if(IpduGroupId >= Com_gConfigPtr->ComTxIpduGroupVectorBitStart)
       {
           Com_EB_HandlePduGroupTx_MainFunction(Com_IpduGroupVectorState,
                                                IpduGroupId, FALSE);
       }
       else
       {
           Com_EB_HandlePduGroupRx_MainFunction(COM_IPDUGROUP_CONTROL, Com_IpduGroupVectorState,
                                                IpduGroupId, FALSE);
           Com_EB_HandlePduGroupTx_MainFunction(Com_IpduGroupVectorState,
                                                IpduGroupId, FALSE);
       }

   }

   DBG_COM_IPDUGROUPSTOP_EXIT(IpduGroupId);
}                               /* Com_IpduGroupStop */

#endif /* (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_OFF) */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
