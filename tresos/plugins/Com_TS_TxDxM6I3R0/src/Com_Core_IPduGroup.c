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


/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to
 * void into pointer to object.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned
 * memory sections.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 */

/*==================[inclusions]============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>                /* Module public API */
#include <Com_Priv.h>           /* Module private API */

#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */
#include <Com_Core_RxIPdu.h>    /* Header RxIPdu functions */
#include <Com_Core_IPduGroup.h>    /* Header IPduGroup functions */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <Com_MemMap.h>
#endif

static FUNC(void, COM_CODE) Com_EB_HandlePduGroupTx_hlp
(
    ComIPduRefType PduId,
    P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
    boolean Initialize
);

static FUNC(void, COM_CODE) Com_EB_HandlePduGroupRx_hlp
(
    ComIPduRefType PduId,
    Com_IpduGroupModeType mode,
    P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
    boolean Initialize
);

#if (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_OFF)

/** \brief Com_EB_HandlePduGroupRx - handle PDU groups
 * function which manages starting/stopping of Rx-Pdus and enabling/disabling
 * RxDM of Rx-Pdus
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 *
 * \param[in] mode - type of action which should be performed
 * (COM_IPDUGROUP_CONTROL, COM_IPDUGROUP_RXDM_CONTROL)
 * \param[in] ipduGroupVector - I-PDU group vector containing the activation
 * state (stopped = 0/ started = 1) for all IPdus.
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * in case of starting of Pdus
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_HandlePduGroupRx
(
   Com_IpduGroupModeType mode,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
   boolean Initialize
)
{

   ComIPduRefType const rxPduCount = Com_gConfigPtr->ComRxIPduArraySize;
   ComIPduRefType IPduId;


   /* loop over all Rx-Pdus */
   for (IPduId = 0U; IPduId < rxPduCount; IPduId++)
   {

       Com_EB_HandlePduGroupRx_hlp(IPduId, mode, ipduGroupVector, Initialize);

   }                            /* for (IPduId = 0U; IPduId < rxPduCount; IPduId++) */

   return;
}                               /* Com_EB_HandlePduGroupRx */

/** \brief Com_EB_HandlePduGroupTx - handle PDU groups
 * function which manages starting/stopping of Tx-Pdus
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 *
 * \param[in] ipduGroupVector - I-PDU group vector containing the activation
 * state (stopped = 0/ started = 1) for all IPdus.
 * \param[in] Initialize - defines if the Pdu should be initialized
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_HandlePduGroupTx
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
   boolean Initialize
)
{

   ComIPduRefType const txPduCount = Com_gConfigPtr->ComTxIPduArraySize;
   ComIPduRefType IPduId;


   /* loop over all Tx-Pdus */
   for (IPduId = 0U; IPduId < txPduCount; IPduId++)
   {

       Com_EB_HandlePduGroupTx_hlp(IPduId, ipduGroupVector, Initialize);

   }                            /* for (IPduId = 0U; IPduId < txPduCount; IPduId++) */

   return;
}                               /* Com_EB_HandlePduGroupTx */

#else

/** \brief Com_EB_HandlePduGroupRx_MainFunction - handle PDU groups per main
 * function which manages starting/stopping of Rx-Pdus and enabling/disabling
 * RxDM of Rx-Pdus
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 *
 * \param[in] mode - type of action which should be performed
 * (COM_IPDUGROUP_CONTROL, COM_IPDUGROUP_RXDM_CONTROL)
 * \param[in] ipduGroupVector - I-PDU group vector containing the activation
 * state (stopped = 0/ started = 1) for all IPdus.
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * in case of starting of Pdus
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_HandlePduGroupRx_MainFunction
(
   Com_IpduGroupModeType mode,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
   Com_IpduGroupIdType IpduGroupId,
   boolean Initialize
)
{
  Com_MainFunctionRx_IdxType ComMainFunctionsRx_Idx = 0U;

   /* interate through all main Rx main functions and get main func IDs */
  /* Deviation TASKING-1 */
  for (ComMainFunctionsRx_Idx = 0U; ComMainFunctionsRx_Idx < COM_MAIN_FUNCS_RX; ComMainFunctionsRx_Idx++)
  {

      CONSTP2CONST(ComMainfunctionRxType, AUTOMATIC, COM_APPL_CONST) MainRxInfoPtr =
      COM_GET_CONFIG_ELEMENT(ComMainfunctionRxType,
                             Com_gConfigPtr->ComMainfunctionRxRef,
                             ComMainFunctionsRx_Idx);

      CONSTP2CONST(ComIPduGroupMaskType, AUTOMATIC, COM_APPL_CONST) MaskPtr =
          COM_GET_CONFIG_ELEMENT(ComIPduGroupMaskType,
                           Com_gConfigPtr->ComIPduGroupMaskRef,
                           MainRxInfoPtr->ComIPduGroupMaskRef * COM_IPDU_GROUP_VECTOR_NUM_BYTES);

      boolean toBeAssociated = FALSE;

      /* get assosiaction of IpduGroup to Com main func */
      TS_GetBit(&MaskPtr[IpduGroupId/8U], IpduGroupId % 8U, uint8, toBeAssociated);

      if(toBeAssociated)
      {
          ComIPduRefType PduIdCount = 0U;
          for (PduIdCount = 0U; PduIdCount < MainRxInfoPtr->ComMainPduIDListSize; PduIdCount++)
          {
            /* get starting element of pduId list from the corresponding Rx main function sector */
            /* Deviation MISRAC2012-1 <+2> */
            ComIPduRefType PduId = * COM_GET_CONFIG_ELEMENT(ComIPduRefType, MainRxInfoPtr->ComMainPduIDListRef, PduIdCount);

            Com_EB_HandlePduGroupRx_hlp(PduId, mode, ipduGroupVector, Initialize);
          }
      }

  }

   return;
}                               /* Com_EB_HandlePduGroupRx_MainFunction */

/** \brief Com_EB_HandlePduGroupTx_MainFunction - handle PDU groups per main
 * function which manages starting/stopping of Tx-Pdus
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 *
 * \param[in] ipduGroupVector - I-PDU group vector containing the activation
 * state (stopped = 0/ started = 1) for all IPdus.
 * \param[in] ipduGroupVector_mainfunction - I-PDU group vector containing the association
 * to the com main function for the I-PDU group.
 * \param[in] Initialize - defines if the Pdu should be initialized
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_HandlePduGroupTx_MainFunction
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
   Com_IpduGroupIdType IpduGroupId,
   boolean Initialize
)
{
  Com_MainFunctionTx_IdxType ComMainFunctionsTx_Idx = 0U;

   /* interate through all main Tx main functions and get main func IDs */
  /* Deviation TASKING-1 */
  for (ComMainFunctionsTx_Idx = 0U; ComMainFunctionsTx_Idx < COM_MAIN_FUNCS_TX; ComMainFunctionsTx_Idx++)
  {
      CONSTP2CONST(ComMainfunctionTxType, AUTOMATIC, COM_APPL_CONST) MainTxInfoPtr =
      COM_GET_CONFIG_ELEMENT(ComMainfunctionTxType,
                             Com_gConfigPtr->ComMainfunctionTxRef,
                             ComMainFunctionsTx_Idx);

      CONSTP2CONST(ComIPduGroupMaskType, AUTOMATIC, COM_APPL_CONST) MaskPtr =
          COM_GET_CONFIG_ELEMENT(ComIPduGroupMaskType,
                                 Com_gConfigPtr->ComIPduGroupMaskRef,
                                 MainTxInfoPtr->ComIPduGroupMaskRef * COM_IPDU_GROUP_VECTOR_NUM_BYTES);

      boolean toBeAssociated = FALSE;

      /* get assosiaction of IpduGroup to Com main func */
      TS_GetBit(&MaskPtr[IpduGroupId/8U], IpduGroupId % 8U, uint8, toBeAssociated);

      if(toBeAssociated)
      {
          ComIPduRefType PduIdCount = 0U;
          /* loop over main function Tx-Pdus */
          for (PduIdCount = 0U; PduIdCount < MainTxInfoPtr->ComMainPduIDListSize; PduIdCount++)
          {
            /* get starting element of pduId list from the corresponding Tx main function struct */
           ComIPduRefType PduId = * COM_GET_CONFIG_ELEMENT(ComIPduRefType, MainTxInfoPtr->ComMainPduIDListRef, PduIdCount);

           Com_EB_HandlePduGroupTx_hlp(PduId, ipduGroupVector, Initialize);
          }
      }

  }           /* for (ComMainFunctionsTx_Idx = 0U; ComMainFunctionsTx_Idx < COM_MAIN_FUNCS_TX; ComMainFunctionsTx_Idx++) */

   return;
}                               /* Com_EB_HandlePduGroupTx_MainFunction */

#endif /* (COM_EB_IPDUGROUPSTARTSTOP_ENABLE == STD_OFF) */

static FUNC(void, COM_CODE) Com_EB_HandlePduGroupRx_hlp
(
   ComIPduRefType PduId,
   Com_IpduGroupModeType mode,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
   boolean Initialize
)
{
     /* Deviation MISRAC2012-1 <+2> */
     CONSTP2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr =
         COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, PduId);

#if (COM_PBCFG_VARIANT_SUPPORT_ENABLED == STD_ON)
     if( !Com_IsBitSet_8(&(IPduPtr)->ComRxIPduFlags, COM_RXIPDUFLAG_RX_IPDU_DUMMY) )
#endif /* (COM_PBCFG_VARIANT_SUPPORT_ENABLED == STD_ON) */
     {

       if(IPduPtr->ComIPduGroupMaskRef != COM_IPDUGROUPMASK_REF_INVALID)
       {
         /* Deviation MISRAC2012-1 <+2> */
         CONSTP2CONST(ComIPduGroupMaskType, AUTOMATIC, COM_APPL_CONST) MaskPtr =
             COM_GET_CONFIG_ELEMENT(ComIPduGroupMaskType,
                 Com_gConfigPtr->ComIPduGroupMaskRef,
                 IPduPtr->ComIPduGroupMaskRef * COM_IPDU_GROUP_VECTOR_NUM_BYTES);

         boolean toBeActivated = FALSE;
         boolean activate = FALSE;
         uint16 iPduGroupVectorByte =
             (uint16)(Com_gConfigPtr->ComRxIpduGroupVectorByteEnd);

         /* loop over all bytes of the vector */
         do {

           iPduGroupVectorByte--;

           activate =
               ((MaskPtr[iPduGroupVectorByte] & ipduGroupVector[iPduGroupVectorByte]) != FALSE)
               ? TRUE
                   : FALSE;

           toBeActivated = (toBeActivated || activate) ? TRUE: FALSE;

         } while(iPduGroupVectorByte != 0U);

         Com_EB_HandleRxIPdu(mode,
             toBeActivated,
  #if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
             IPduPtr,
  #endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */
             Initialize,
             PduId);
       }

     }

   return;
}                               /* Com_EB_HandlePduGroupRx_hlp */


static FUNC(void, COM_CODE) Com_EB_HandlePduGroupTx_hlp
(
    ComIPduRefType PduId,
    P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector,
    boolean Initialize
)
{
     /* Deviation MISRAC2012-1 <+2> */
     CONSTP2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr =
         COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, PduId);

#if (COM_PBCFG_VARIANT_SUPPORT_ENABLED == STD_ON)
     if( !Com_IsBitSet_8(&(IPduPtr)->ComTxIPduFlags, COM_TXIPDUFLAG_TX_IPDU_DUMMY) )
#endif /* (COM_PBCFG_VARIANT_SUPPORT_ENABLED == STD_ON) */
     {

       if(IPduPtr->ComIPduGroupMaskRef != COM_IPDUGROUPMASK_REF_INVALID)
       {
         /* Deviation MISRAC2012-1 <+2> */
         CONSTP2CONST(ComIPduGroupMaskType, AUTOMATIC, COM_APPL_CONST) MaskPtr =
             COM_GET_CONFIG_ELEMENT(ComIPduGroupMaskType,
                 Com_gConfigPtr->ComIPduGroupMaskRef,
                 IPduPtr->ComIPduGroupMaskRef * COM_IPDU_GROUP_VECTOR_NUM_BYTES);

         boolean toBeActivated = FALSE;
         uint16 iPduGroupVectorByte =
             (uint16)(Com_gConfigPtr->ComTxIpduGroupVectorByteStart);

         /* loop over all bytes of the vector */
         do {

           boolean activate =
               ((MaskPtr[iPduGroupVectorByte] & ipduGroupVector[iPduGroupVectorByte]) != FALSE)
               ? TRUE
                   : FALSE;

           toBeActivated = (toBeActivated || activate) ? TRUE : FALSE;

           iPduGroupVectorByte++;

         } while(iPduGroupVectorByte != COM_IPDU_GROUP_VECTOR_NUM_BYTES);

         Com_EB_HandleTxIPdu(toBeActivated, IPduPtr, Initialize, PduId);
       }

     }

   return;
}                               /* Com_EB_HandlePduGroupTx_hlp */


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>
#endif

