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

#ifndef DCM_HSMDCMINT_H
#define DCM_HSMDCMINT_H

/* Internal interface for the Dcm state
 * machine.
 *
 * This header must only be included by
 * Dcm_HsmDcmData.c and Dcm_HsmDcmFnct.c.
 */

 /* MISRA-C:2012 Deviation List
  *
  *  MISRAC2012-1) Deviated Rule: 20.7 (required)
  *     "Expressions resulting from the expansion of macro parameters shall
  *     be enclosed in parentheses."
  *
  *     Reason:
  *     The macro is used in function parameter declarations and definitions
  *     where the number of parentheses matter.
  */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <Dcm_Hsm.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/* *** State indices and IDs for states *** */

#if (defined DCM_HSM_DCM_SIDX_TOP)
  #error "DCM_HSM_DCM_SIDX_TOP is already defined"
#endif
#define DCM_HSM_DCM_SIDX_TOP                                     0U
#if (defined DCM_HSM_DCM_SIDX_INSERVICE)
  #error "DCM_HSM_DCM_SIDX_INSERVICE is already defined"
#endif
#define DCM_HSM_DCM_SIDX_INSERVICE                               1U
#if (defined DCM_HSM_DCM_SIDX_PERIODICPROCESSINGUUDT)
  #error "DCM_HSM_DCM_SIDX_PERIODICPROCESSINGUUDT is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PERIODICPROCESSINGUUDT                  2U
#if (defined DCM_HSM_DCM_SIDX_PERIODICSENDINGUUDT)
  #error "DCM_HSM_DCM_SIDX_PERIODICSENDINGUUDT is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PERIODICSENDINGUUDT                     3U
#if (defined DCM_HSM_DCM_SIDX_PERIODICSENDINGUUDTFINISHING)
  #error "DCM_HSM_DCM_SIDX_PERIODICSENDINGUUDTFINISHING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PERIODICSENDINGUUDTFINISHING            4U
#if (defined DCM_HSM_DCM_SIDX_PERIODICPROCESSING)
  #error "DCM_HSM_DCM_SIDX_PERIODICPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PERIODICPROCESSING                      5U
#if (defined DCM_HSM_DCM_SIDX_PERIODICRESPONSEPROCESSING)
  #error "DCM_HSM_DCM_SIDX_PERIODICRESPONSEPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PERIODICRESPONSEPROCESSING              6U
#if (defined DCM_HSM_DCM_SIDX_ROEPROCESSING)
  #error "DCM_HSM_DCM_SIDX_ROEPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_ROEPROCESSING                           7U
#if (defined DCM_HSM_DCM_SIDX_ROERESPONSEPROCESSING)
  #error "DCM_HSM_DCM_SIDX_ROERESPONSEPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_ROERESPONSEPROCESSING                   8U
#if (defined DCM_HSM_DCM_SIDX_WAITFORROEPROCESSINGCANCELLATION)
  #error "DCM_HSM_DCM_SIDX_WAITFORROEPROCESSINGCANCELLATION is already defined"
#endif
#define DCM_HSM_DCM_SIDX_WAITFORROEPROCESSINGCANCELLATION        9U
#if (defined DCM_HSM_DCM_SIDX_REQUESTPROCESSING)
  #error "DCM_HSM_DCM_SIDX_REQUESTPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_REQUESTPROCESSING                       10U
#if (defined DCM_HSM_DCM_SIDX_WAITFORAPPL)
  #error "DCM_HSM_DCM_SIDX_WAITFORAPPL is already defined"
#endif
#define DCM_HSM_DCM_SIDX_WAITFORAPPL                             11U
#if (defined DCM_HSM_DCM_SIDX_SENDRP)
  #error "DCM_HSM_DCM_SIDX_SENDRP is already defined"
#endif
#define DCM_HSM_DCM_SIDX_SENDRP                                  12U
#if (defined DCM_HSM_DCM_SIDX_SENDRPFORCED)
  #error "DCM_HSM_DCM_SIDX_SENDRPFORCED is already defined"
#endif
#define DCM_HSM_DCM_SIDX_SENDRPFORCED                            13U
#if (defined DCM_HSM_DCM_SIDX_SENDRPNORMAL)
  #error "DCM_HSM_DCM_SIDX_SENDRPNORMAL is already defined"
#endif
#define DCM_HSM_DCM_SIDX_SENDRPNORMAL                            14U
#if (defined DCM_HSM_DCM_SIDX_REQUESTCANCELLING)
  #error "DCM_HSM_DCM_SIDX_REQUESTCANCELLING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_REQUESTCANCELLING                       15U
#if (defined DCM_HSM_DCM_SIDX_CANCELNOGENERALREJECT)
  #error "DCM_HSM_DCM_SIDX_CANCELNOGENERALREJECT is already defined"
#endif
#define DCM_HSM_DCM_SIDX_CANCELNOGENERALREJECT                   16U
#if (defined DCM_HSM_DCM_SIDX_WAITFORPROTOCOL)
  #error "DCM_HSM_DCM_SIDX_WAITFORPROTOCOL is already defined"
#endif
#define DCM_HSM_DCM_SIDX_WAITFORPROTOCOL                         17U
#if (defined DCM_HSM_DCM_SIDX_WAITFORTXANDPROTOCOL)
  #error "DCM_HSM_DCM_SIDX_WAITFORTXANDPROTOCOL is already defined"
#endif
#define DCM_HSM_DCM_SIDX_WAITFORTXANDPROTOCOL                    18U
#if (defined DCM_HSM_DCM_SIDX_CANCELWITHGENERALREJECT)
  #error "DCM_HSM_DCM_SIDX_CANCELWITHGENERALREJECT is already defined"
#endif
#define DCM_HSM_DCM_SIDX_CANCELWITHGENERALREJECT                 19U
#if (defined DCM_HSM_DCM_SIDX_FINISHING)
  #error "DCM_HSM_DCM_SIDX_FINISHING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_FINISHING                               20U
#if (defined DCM_HSM_DCM_SIDX_CONFIRMINGOK)
  #error "DCM_HSM_DCM_SIDX_CONFIRMINGOK is already defined"
#endif
#define DCM_HSM_DCM_SIDX_CONFIRMINGOK                            21U
#if (defined DCM_HSM_DCM_SIDX_CONFIRMINGNOK)
  #error "DCM_HSM_DCM_SIDX_CONFIRMINGNOK is already defined"
#endif
#define DCM_HSM_DCM_SIDX_CONFIRMINGNOK                           22U
#if (defined DCM_HSM_DCM_SIDX_SENDING)
  #error "DCM_HSM_DCM_SIDX_SENDING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_SENDING                                 23U
#if (defined DCM_HSM_DCM_SIDX_NORMALSENDING)
  #error "DCM_HSM_DCM_SIDX_NORMALSENDING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_NORMALSENDING                           24U
#if (defined DCM_HSM_DCM_SIDX_NORMALSENDINGCANCELLING)
  #error "DCM_HSM_DCM_SIDX_NORMALSENDINGCANCELLING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_NORMALSENDINGCANCELLING                 25U
#if (defined DCM_HSM_DCM_SIDX_NORMALSENDINGPROCESSING)
  #error "DCM_HSM_DCM_SIDX_NORMALSENDINGPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_NORMALSENDINGPROCESSING                 26U
#if (defined DCM_HSM_DCM_SIDX_PGBUFSENDING)
  #error "DCM_HSM_DCM_SIDX_PGBUFSENDING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PGBUFSENDING                            27U
#if (defined DCM_HSM_DCM_SIDX_PGBUFSENDINGPROCESSING)
  #error "DCM_HSM_DCM_SIDX_PGBUFSENDINGPROCESSING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PGBUFSENDINGPROCESSING                  28U
#if (defined DCM_HSM_DCM_SIDX_PGBUFDATAAVAILABLE)
  #error "DCM_HSM_DCM_SIDX_PGBUFDATAAVAILABLE is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PGBUFDATAAVAILABLE                      29U
#if (defined DCM_HSM_DCM_SIDX_PGBUFDATAREQUESTED)
  #error "DCM_HSM_DCM_SIDX_PGBUFDATAREQUESTED is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PGBUFDATAREQUESTED                      30U
#if (defined DCM_HSM_DCM_SIDX_PGBUFSENDINGCANCELLING)
  #error "DCM_HSM_DCM_SIDX_PGBUFSENDINGCANCELLING is already defined"
#endif
#define DCM_HSM_DCM_SIDX_PGBUFSENDINGCANCELLING                  31U
#if (defined DCM_HSM_DCM_SIDX_OUTOFSERVICE)
  #error "DCM_HSM_DCM_SIDX_OUTOFSERVICE is already defined"
#endif
#define DCM_HSM_DCM_SIDX_OUTOFSERVICE                            32U
#if (defined DCM_HSM_DCM_SIDX_OOSINIT)
  #error "DCM_HSM_DCM_SIDX_OOSINIT is already defined"
#endif
#define DCM_HSM_DCM_SIDX_OOSINIT                                 33U
#if (defined DCM_HSM_DCM_SIDX_OOSNOTIFIED)
  #error "DCM_HSM_DCM_SIDX_OOSNOTIFIED is already defined"
#endif
#define DCM_HSM_DCM_SIDX_OOSNOTIFIED                             34U
#if (defined DCM_HSM_DCM_SIDX_WAITFORFULLCOM)
  #error "DCM_HSM_DCM_SIDX_WAITFORFULLCOM is already defined"
#endif
#define DCM_HSM_DCM_SIDX_WAITFORFULLCOM                          35U
#if (defined DCM_HSM_DCM_NO_OF_STATES)
  #error "DCM_HSM_DCM_NO_OF_STATES is already defined"
#endif
#define DCM_HSM_DCM_NO_OF_STATES                                 36U
typedef uint8 Dcm_HsmDcmStateIdType;
/* typedefed type only used for debugging */

/* *** IDs for entry/axit and transition actions *** */

#if (defined DCM_HSM_DCM_AIDX_TOP_ENTRY)
  #error "DCM_HSM_DCM_AIDX_TOP_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_TOP_ENTRY                               0U
#if (defined DCM_HSM_DCM_AIDX_INSERVICE_ENTRY)
  #error "DCM_HSM_DCM_AIDX_INSERVICE_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_INSERVICE_ENTRY                         1U
#if (defined DCM_HSM_DCM_AIDX_INSERVICE_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_INSERVICE_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_INSERVICE_ACTION_1                      2U
#if (defined DCM_HSM_DCM_AIDX_PERIODICPROCESSINGUUDT_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_PERIODICPROCESSINGUUDT_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICPROCESSINGUUDT_ACTION_1         3U
#if (defined DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDT_ENTRY)
  #error "DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDT_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDT_ENTRY               4U
#if (defined DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDT_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDT_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDT_ACTION_1            5U
#if (defined DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDTFINISHING_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDTFINISHING_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDTFINISHING_ACTION_1   6U
#if (defined DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDTFINISHING_ACTION_2)
  #error "DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDTFINISHING_ACTION_2 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICSENDINGUUDTFINISHING_ACTION_2   7U
#if (defined DCM_HSM_DCM_AIDX_PERIODICPROCESSING_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_PERIODICPROCESSING_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICPROCESSING_ACTION_1             8U
#if (defined DCM_HSM_DCM_AIDX_PERIODICRESPONSEPROCESSING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_PERIODICRESPONSEPROCESSING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PERIODICRESPONSEPROCESSING_ENTRY        9U
#if (defined DCM_HSM_DCM_AIDX_ROEPROCESSING_ACTION_3)
  #error "DCM_HSM_DCM_AIDX_ROEPROCESSING_ACTION_3 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_ROEPROCESSING_ACTION_3                 10U
#if (defined DCM_HSM_DCM_AIDX_ROERESPONSEPROCESSING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_ROERESPONSEPROCESSING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_ROERESPONSEPROCESSING_ENTRY            11U
#if (defined DCM_HSM_DCM_AIDX_WAITFORROEPROCESSINGCANCELLATION_ENTRY)
  #error "DCM_HSM_DCM_AIDX_WAITFORROEPROCESSINGCANCELLATION_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_WAITFORROEPROCESSINGCANCELLATION_ENTRY 12U
#if (defined DCM_HSM_DCM_AIDX_REQUESTPROCESSING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_REQUESTPROCESSING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_REQUESTPROCESSING_ENTRY                13U
#if (defined DCM_HSM_DCM_AIDX_REQUESTPROCESSING_ACTION_3)
  #error "DCM_HSM_DCM_AIDX_REQUESTPROCESSING_ACTION_3 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_REQUESTPROCESSING_ACTION_3             14U
#if (defined DCM_HSM_DCM_AIDX_SENDRP_ENTRY)
  #error "DCM_HSM_DCM_AIDX_SENDRP_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_SENDRP_ENTRY                           15U
#if (defined DCM_HSM_DCM_AIDX_SENDRP_EXIT)
  #error "DCM_HSM_DCM_AIDX_SENDRP_EXIT is already defined"
#endif
#define DCM_HSM_DCM_AIDX_SENDRP_EXIT                            16U
#if (defined DCM_HSM_DCM_AIDX_SENDRPFORCED_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_SENDRPFORCED_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_SENDRPFORCED_ACTION_1                  17U
#if (defined DCM_HSM_DCM_AIDX_REQUESTCANCELLING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_REQUESTCANCELLING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_REQUESTCANCELLING_ENTRY                18U
#if (defined DCM_HSM_DCM_AIDX_WAITFORPROTOCOL_ENTRY)
  #error "DCM_HSM_DCM_AIDX_WAITFORPROTOCOL_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_WAITFORPROTOCOL_ENTRY                  19U
#if (defined DCM_HSM_DCM_AIDX_WAITFORTXANDPROTOCOL_ENTRY)
  #error "DCM_HSM_DCM_AIDX_WAITFORTXANDPROTOCOL_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_WAITFORTXANDPROTOCOL_ENTRY             20U
#if (defined DCM_HSM_DCM_AIDX_CANCELWITHGENERALREJECT_ENTRY)
  #error "DCM_HSM_DCM_AIDX_CANCELWITHGENERALREJECT_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_CANCELWITHGENERALREJECT_ENTRY          21U
#if (defined DCM_HSM_DCM_AIDX_CANCELWITHGENERALREJECT_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_CANCELWITHGENERALREJECT_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_CANCELWITHGENERALREJECT_ACTION_1       22U
#if (defined DCM_HSM_DCM_AIDX_CONFIRMINGOK_ENTRY)
  #error "DCM_HSM_DCM_AIDX_CONFIRMINGOK_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_CONFIRMINGOK_ENTRY                     23U
#if (defined DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY)
  #error "DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY                    24U
#if (defined DCM_HSM_DCM_AIDX_SENDING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_SENDING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_SENDING_ENTRY                          25U
#if (defined DCM_HSM_DCM_AIDX_NORMALSENDINGCANCELLING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_NORMALSENDINGCANCELLING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_NORMALSENDINGCANCELLING_ENTRY          26U
#if (defined DCM_HSM_DCM_AIDX_PGBUFDATAAVAILABLE_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_PGBUFDATAAVAILABLE_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PGBUFDATAAVAILABLE_ACTION_1            27U
#if (defined DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_ACTION_1            28U
#if (defined DCM_HSM_DCM_AIDX_PGBUFSENDINGCANCELLING_ENTRY)
  #error "DCM_HSM_DCM_AIDX_PGBUFSENDINGCANCELLING_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_PGBUFSENDINGCANCELLING_ENTRY           29U
#if (defined DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_2)
  #error "DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_2 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_2                  30U
#if (defined DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_4)
  #error "DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_4 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_4                  31U
#if (defined DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_7)
  #error "DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_7 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_7                  32U
#if (defined DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_8)
  #error "DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_8 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_8                  33U
#if (defined DCM_HSM_DCM_AIDX_OOSINIT_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_OOSINIT_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_OOSINIT_ACTION_1                       34U
#if (defined DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY)
  #error "DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY is already defined"
#endif
#define DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY                      35U
#if (defined DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_1)
  #error "DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_1 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_1                36U
#if (defined DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_2)
  #error "DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_2 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_2                37U
#if (defined DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_3)
  #error "DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_3 is already defined"
#endif
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_3                38U
#if (defined DCM_HSM_DCM_NO_OF_ACTIONS)
  #error "DCM_HSM_DCM_NO_OF_ACTIONS is already defined"
#endif
#define DCM_HSM_DCM_NO_OF_ACTIONS                               39U

typedef uint8 Dcm_HsmDcmActionIdType;
/* typedefed type only used for debugging */

/* *** IDs for guards *** */
#if (defined DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_2)
  #error "DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_2 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_2                     0U
#if (defined DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_3)
  #error "DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_3 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_3                     1U
#if (defined DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_4)
  #error "DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_4 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_4                     2U
#if (defined DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_5)
  #error "DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_5 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_5                     3U
#if (defined DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_1)
  #error "DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_1 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_1                    4U
#if (defined DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_2)
  #error "DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_2 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_2                    5U
#if (defined DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_3)
  #error "DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_3 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_3                    6U
#if (defined DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_4)
  #error "DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_4 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_4                    7U
#if (defined DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_7)
  #error "DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_7 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_7                    8U
#if (defined DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_8)
  #error "DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_8 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_8                    9U
#if (defined DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_2)
  #error "DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_2 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_2                 10U
#if (defined DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_3)
  #error "DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_3 is already defined"
#endif
#define DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_3                 11U

#if (defined DCM_HSM_DCM_NO_OF_GUARDS)
  #error "DCM_HSM_DCM_NO_OF_GUARDS is already defined"
#endif
#define DCM_HSM_DCM_NO_OF_GUARDS                                12U

typedef uint8 Dcm_HsmDcmGuardIdType;
/* typedefed type only used for debugging */

/*==================[external function declarations]========================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* function declarations of state entry, exit, guard, action functions
 * defined in Dcm_fnct.c */

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfTopEntry(
  DCM_PDL_SF(const uint8 instIdx));



/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfInServiceEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'if (RetryTimer==0) CallService(PENDING)' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfInServiceAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Free Tx Buffer; Dcm_Dsl_Supervisor_ProtocolFree();' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicProcessingUUDTAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicSendingUUDTEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'While samples and TxPduIds available' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicSendingUUDTAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'While UUDT confirmations missing' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicSendingUUDTFinishingAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Free Tx Buffer; Dcm_Dsl_SupervisorProtocolFree();' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicSendingUUDTFinishingAction2(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Free Tx Buffer; Dcm_Dsl_SupervisorProtocolFree();' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicProcessingAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPeriodicResponseProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Free Tx Buffer; Dcm_Dsl_Supervisor_ProtocolFree();
   Dcm_Dsp_ServiceProcessorInit();' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfROEProcessingAction3(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfROEResponseProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForRoeProcessingCancellationEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRequestProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Free Tx Buffer; Stop and free P2Timer;
   Dcm_Dsl_SupervisorProtocolFree();' */
 /* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRequestProcessingAction3(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'RpCntr >= Limit' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForApplGuard2(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'RpCntr < Limit' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForApplGuard3(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'RpCntr >= Limit' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForApplGuard4(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'RpCntr < Limit' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForApplGuard5(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendRpEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendRpExit(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'CallService(FORCE_RCRRP_OK);' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendRpForcedAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRequestCancellingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForProtocolEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForTxAndProtocolEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfCancelWithGeneralRejectEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'if(GR pending) {Dcm_Dsl_TxConnectionCancelTransmit(TxConnection)}' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfCancelWithGeneralRejectAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfConfirmingOkEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfConfirmingNOkEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfNormalSendingCancellingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'DspInternal_UpdatePage();' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPgBufDataAvailableAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Dcm_Dsl_BufferGive(TxBuffer, TxConnection);
   Dcm_Dsl_TxConnectionProcessNextTxBuffer(TxBuffer, TxConnection)' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPgBufDataRequestedAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPgBufSendingCancellingEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'TxEnabled' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard1(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard '!TxEnabled' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard2(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Dcm_Dsl_Supervisor_ProtocolFree()' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction2(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'TxEnabled' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard3(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard '!TxEnabled' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard4(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Dcm_Dsl_Supervisor_ProtocolFree()' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction4(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'TxEnabled' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard7(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Set-up Protocol' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction7(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard '!TxEnabled' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard8(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Dcm_Dsl_Supervisor_ProtocolFree()' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction8(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'ComM_DCM_ActiveDiagnostic(); Set-up Protocol' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOosInitAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOosNotifiedEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'if (RetryTimer == 0) ReassessChannelState' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComAction1(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard 'ResponseRequired' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComGuard2(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Fill response' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComAction2(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard '!ResponseRequired' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComGuard3(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Dcm_Dsl_Supervisor_ProtocolFree();' */
/* Deviation MISRAC2012-1 <+3> */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComAction3(
  DCM_PDL_SF(const uint8 instIdx));


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* defined DCM_HSMDCMINT_H */
/*==================[end of file]===========================================*/
