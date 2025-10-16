/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \version 5.21.4
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 * Reason:
 * The macro is used in function parameter declarations and definitions of structure member
 * where the number of parentheses matter.
 *
 */

#ifndef COMM_INT_H
#define COMM_INT_H

/*==================[inclusions]============================================*/

#include <ComM_DefProg_Cfg.h>
#include <ComM_BSW_Types.h>
#include <ComM_HsmComM.h>
#include <ComM_Types.h>
#include <ComM_Types_Int.h> /* PostBuild type definitions */
#ifdef COMM_PRECOMPILE_TIME_PBCFG_ACCESS
#include <ComM_PBcfg.h>
#endif
#if (defined TS_RELOCATABLE_CFG_ENABLE)
#error TS_RELOCATABLE_CFG_ENABLE already defined
#endif
#define TS_RELOCATABLE_CFG_ENABLE COMM_RELOCATABLE_CFG_ENABLE

#if (defined TS_PB_CFG_PTR_CLASS)
#error TS_PB_CFG_PTR_CLASS already defined
#endif
#define TS_PB_CFG_PTR_CLASS COMM_APPL_CONST

#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_NM_ACCESS_NEEDED == STD_ON))
#include <NmStack_Types.h>
#endif

#include <TSPBConfig.h>
/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.SchM,1 */
#include <SchM_ComM.h>
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#include <Os.h>
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
/*==================[macros]================================================*/


/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00103.NvM_SetRamBlockStatus,1, ComM.SWS_ComM_00157,1, ComM.EB_Ref.SWS_ComM_00140.NvM_SetRamBlockStatus,1 */
#if (defined COMM_PERS_DATA_MODIFIED)
#error COMM_PERS_DATA_MODIFIED already defined
#endif
#if ((COMM_NVM_ENABLED == STD_ON) &&                \
     ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)))
#define COMM_PERS_DATA_MODIFIED()                                      \
        ((void) NvM_SetRamBlockStatus(COMM_NVM_BLOCK_DESCRIPTOR, TRUE))
#else
#define COMM_PERS_DATA_MODIFIED()
#endif

/* Macros for the abstraction of the RTE callback functions.
 * The macros resolve to the required callback function names according to
 * the service API configuration (default, ASR40, ASR32)
 */

#if (defined COMM_EB_DEFAULT_RTE_NOTIFY)
#error COMM_EB_DEFAULT_RTE_NOTIFY already defined
#endif
#if ((COMM_INCLUDE_RTE == STD_ON) && \
    (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE))
/** \brief Signal the user the current communication mode via Rte
 *
 * The macro receives the user handle and gets the current communication mode
 * and propagates the arguments to the corresponding default RTE handle
 * function.
 *
 * If the default service API is set to NONE then the macro is defined empty.
 *
 * The return value of the RTE call is ignored on purpose because the ComM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#if (defined COMM_EB_DEFAULT_RTE_NOTIFY)
#error COMM_EB_DEFAULT_RTE_NOTIFY already defined
#endif
#define COMM_EB_DEFAULT_RTE_NOTIFY(user)      \
  do { \
    ComM_ASR40_ModeType CurComMMode; \
    if (E_OK == ComM_ASR40_GetCurrentComMode((user), &CurComMMode)) \
    { \
      ComM_RteNotify((user), CurComMMode); \
    } \
  } while (0)
#else
#define COMM_EB_DEFAULT_RTE_NOTIFY(user)
#endif

#if (defined COMM_EB_ASR40_RTE_NOTIFY)
#error COMM_EB_ASR40_RTE_NOTIFY already defined
#endif
#if ((COMM_INCLUDE_RTE == STD_ON) && \
     (COMM_ENABLE_ASR40_SERVICE_API == STD_ON))
/** \brief Signal the user the current communication mode via ASR40 Rte
 * callbacks
 *
 * The macro receives the user handle, gets the current communication mode and
 * propagates the arguments to the corresponding ASR40 RTE handle function.
 *
 * If the ASR40 service API is set to STD_OFF then the macro is defined empty.
 *
 * The return value of the RTE call is ignored on purpose because the ComM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#define COMM_EB_ASR40_RTE_NOTIFY(user)      \
  do { \
    ComM_ASR40_ModeType CurASR40ComMMode; \
    if (E_OK == ComM_ASR40_GetCurrentComMode((user), &CurASR40ComMMode)) \
    { \
      ComM_ASR40_RteNotify((user), (CurASR40ComMMode)); \
    } \
  } while (0)
#else
#define COMM_EB_ASR40_RTE_NOTIFY(user)
#endif

#if (defined COMM_EB_ASR32_RTE_NOTIFY)
#error COMM_EB_ASR32_RTE_NOTIFY already defined
#endif
#if ((COMM_INCLUDE_RTE == STD_ON) && \
     (COMM_ENABLE_ASR32_SERVICE_API == STD_ON))
/** \brief Signal the user the current communication mode via ASR32 Rte
 * callbacks
 *
 * The macro receives the user handle, gets the current communication mode and
 * propagates the arguments to the corresponding ASR32 RTE handle function.
 *
 * If the ASR32 service API is set to STD_OFF then the macro is defined empty.
 *
 * The return value of the RTE call is ignored on purpose because the ComM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#define COMM_EB_ASR32_RTE_NOTIFY(user)      \
  do { \
    ComM_ASR32_ModeType CurASR32ComMMode; \
    if (E_OK == ComM_ASR32_GetCurrentComMode((user), &CurASR32ComMMode)) \
    { \
      ComM_ASR32_RteNotify((user), (CurASR32ComMMode)); \
    } \
  } while (0)
#else
#define COMM_EB_ASR32_RTE_NOTIFY(user)
#endif

#if (defined COMM_EB_RTE_NOTIFY)
#error COMM_EB_RTE_NOTIFY already defined
#endif
#if (COMM_INCLUDE_RTE == STD_ON)
/** \brief Signal the user the current communication mode via ASR32 Rte
 * callbacks
 *
 * The macro receives the user handle and propagates the argument to the
 * corresponding sub-macros for the specific RTE handle functions.
 *
 * If the RTE is set to STD_OFF then the macro is defined empty.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_EB_RTE_NOTIFY(user)  COMM_EB_DEFAULT_RTE_NOTIFY((user));
#else /* (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#define COMM_EB_RTE_NOTIFY(user)      \
  do { \
      COMM_EB_ASR32_RTE_NOTIFY((user));\
      COMM_EB_ASR40_RTE_NOTIFY((user));\
      COMM_EB_DEFAULT_RTE_NOTIFY((user));\
  } while (0)
#endif /* (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#else
#define COMM_EB_RTE_NOTIFY(user, curcommod)
#endif

/** \brief User ID of a channel. */
#if (defined COMM_USERSOFCHANNEL)
#error COMM_USERSOFCHANNEL already defined
#endif
#define COMM_USERSOFCHANNEL(Channel,i)                  \
  (COMM_USER_OF_CHANNEL( COMM_INST(Channel),i) )

#if (defined ComM_Notify)
#error ComM_Notify already defined
#endif

#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
#define ComM_Notify(a,b)                ComM_Notify2Arg(a,b)
#else
#define ComM_Notify(a,b)                ComM_Notify1Arg(b)
#endif

/** \brief Multicore EcuM set PNC passive wakeup indication operation id */
#if (defined COMM_MULTICORE_ECUM_WAKEUP_EMIT_PNCPASSIVE_WAKEUP_IND)
#error COMM_MULTICORE_ECUM_WAKEUP_EMIT_PNCPASSIVE_WAKEUP_IND already defined
#endif
#define COMM_MULTICORE_ECUM_WAKEUP_EMIT_PNCPASSIVE_WAKEUP_IND 0U

/** \brief Multicore Evaluate PNC operation id */
#if (defined COMM_MULTICORE_EVALUATE_PNC)
#error COMM_MULTICORE_EVALUATE_PNC already defined
#endif
#define COMM_MULTICORE_EVALUATE_PNC 1U

/** \brief Multicore Evaluate channel operation id */
#if (defined COMM_MULTICORE_EVALUATE_CHANNEL)
#error COMM_MULTICORE_EVALUATE_CHANNEL already defined
#endif
#define COMM_MULTICORE_EVALUATE_CHANNEL 2U

/** \brief Multicore emit request status changed operation id */
#if (defined COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED)
#error COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED already defined
#endif
#define COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED 3U

/** \brief Multicore evaluate PNC and emit request status changed operation id */
#if (defined COMM_MULTICORE_PNC_MAINFUNCTION_OPERATIONS)
#error COMM_MULTICORE_PNC_MAINFUNCTION_OPERATIONS already defined
#endif
#define COMM_MULTICORE_PNC_MAINFUNCTION_OPERATIONS 4U

/** \brief Multicore Notify rte operation id */
#if (defined COMM_MULTICORE_NOTIFY_RTE)
#error COMM_MULTICORE_NOTIFY_RTE already defined
#endif
#define COMM_MULTICORE_NOTIFY_RTE 5U

/** \brief Multicore clear user request operation id */
#if (defined COMM_MULTICORE_CLEAR_USER_REQUEST)
#error COMM_MULTICORE_CLEAR_USER_REQUEST already defined
#endif
#define COMM_MULTICORE_CLEAR_USER_REQUEST 6U

/** \brief Multicore prevent wakeup set to true operation id */
#if (defined COMM_MULTICORE_COMM_PREVENT_WAKEUP_TRUE)
#error COMM_MULTICORE_COMM_PREVENT_WAKEUP_TRUE already defined
#endif
#define COMM_MULTICORE_COMM_PREVENT_WAKEUP_TRUE 7U

/** \brief Multicore prevent wakeup set to false operation id */
#if (defined COMM_MULTICORE_COMM_PREVENT_WAKEUP_FALSE)
#error COMM_MULTICORE_COMM_PREVENT_WAKEUP_FALSE already defined
#endif
#define COMM_MULTICORE_COMM_PREVENT_WAKEUP_FALSE 8U

/** \brief Multicore limit to no com set to true operation id */
#if (defined COMM_MULTICORE_COMM_LIMIT_NOCOM_TRUE)
#error COMM_MULTICORE_COMM_LIMIT_NOCOM_TRUE already defined
#endif
#define COMM_MULTICORE_COMM_LIMIT_NOCOM_TRUE 9U

/** \brief Multicore limit to no com set to false operation id */
#if (defined COMM_MULTICORE_COMM_LIMIT_NOCOM_FALSE)
#error COMM_MULTICORE_COMM_LIMIT_NOCOM_FALSE already defined
#endif
#define COMM_MULTICORE_COMM_LIMIT_NOCOM_FALSE 10U

/** \brief Multicore emit wakeup inhibition operation id */
#if (defined COMM_MULTICORE_EMIT_WAKEUP_INHIBITION)
#error COMM_MULTICORE_EMIT_WAKEUP_INHIBITION already defined
#endif
#define COMM_MULTICORE_EMIT_WAKEUP_INHIBITION 11U

/** \brief Multicore emit limit to no com operation id */
#if (defined COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM)
#error COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM already defined
#endif
#define COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM 12U

/** \brief Multicore evaluate channel and emit request status changed */
#if (defined COMM_MULTICORE_CHANNEL_EVALUATE_CHANNEL_AND_EMIT_REQ_STATUS_CHANGED)
#error COMM_MULTICORE_CHANNEL_EVALUATE_CHANNEL_AND_EMIT_REQ_STATUS_CHANGED already defined
#endif
#define COMM_MULTICORE_CHANNEL_EVALUATE_CHANNEL_AND_EMIT_REQ_STATUS_CHANGED 13U

/** \brief Multicore EcuM set passive startup status operation id */
#if (defined COMM_MULTICORE_ECUM_WAKEUP_INDICATION)
#error COMM_MULTICORE_ECUM_WAKEUP_INDICATION already defined
#endif
#define COMM_MULTICORE_ECUM_WAKEUP_INDICATION 14U

/** \brief Multicore emit limit to no com operation id */
#if (defined COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM_ALL_CHANNELS)
#error COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM_ALL_CHANNELS already defined
#endif
#define COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM_ALL_CHANNELS 15U

/** \brief Multicore emit request status changed operation id */
#if (defined COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED_ALL_CHANNELS)
#error COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED_ALL_CHANNELS already defined
#endif
#define COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED_ALL_CHANNELS 16U

/** \brief Invalid function index */
#if (defined COMM_MULTICORE_INVALID_FCT_INDEX)
#error COMM_MULTICORE_INVALID_FCT_INDEX already defined
#endif
#define COMM_MULTICORE_INVALID_FCT_INDEX 255U

/** \brief In case of Polyspace test COMM_PRECOMPILE_TIME_PBCFG_ACCESS is defined.
 **        Polyspace has issues with expanding postbuild macros.
 **        Macro has to be expanded manually
 */
#if (defined COMM_MANUAL_EXPAND_MACRO)
#error COMM_MANUAL_EXPAND_MACRO already defined
#endif
#ifdef COMM_PRECOMPILE_TIME_PBCFG_ACCESS
#if (COMM_RELOCATABLE_CFG_ENABLE == STD_ON)
#define COMM_MANUAL_EXPAND_MACRO STD_ON
#else /* COMM_RELOCATABLE_CFG_ENABLE */
#define COMM_MANUAL_EXPAND_MACRO STD_OFF
#endif /* COMM_RELOCATABLE_CFG_ENABLE */
#else /* COMM_PRECOMPILE_TIME_PBCFG_ACCESS */
#define COMM_MANUAL_EXPAND_MACRO STD_OFF
#endif /* COMM_PRECOMPILE_TIME_PBCFG_ACCESS */

/** \brief Represent the mask on the last 3 bits.
 ** This macro is used for getting the bit index from a uint8
 */
#if (defined MASK_3_BITS)
#error MASK_3_BITS already defined
#endif
#define MASK_3_BITS  0x07U
/** \brief Represent the 3 LSB masked by MASK_3_BITS
 ** This macro is used for getting the byte index from an array of uint8
 ** The 5 MSB represents the byte array index
 */
#if (defined SHIFT_3_BITS)
#error SHIFT_3_BITS already defined
#endif
#define SHIFT_3_BITS 0x03U

/** \brief Returns a pointer to a dynamic post build element.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param type The data type of the post-build member.
 ** \param element The symbol of post-build member to access.
 ** \retval Pointer the post-build member within the ConfigLayoutType
 ** structure. */
#if (defined COMM_PBCFG_ACCESS)
#error COMM_PBCFG_ACCESS already defined
#endif
#define COMM_PBCFG_ACCESS(type, element) \
    (TS_UNCHECKEDGETCFG(ComM_ConfigPtr, type, COMM, (element)))

/**
 ** \brief Returns the number of users assigned to a channel.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param channel the ID of the channel
 ** \retval the number of mapped users
 **/
#if (defined COMM_NUM_USERS_OF_CHANNEL)
#error COMM_NUM_USERS_OF_CHANNEL already defined
#endif
#define COMM_NUM_USERS_OF_CHANNEL(channel) (uint8) \
  ( (ComM_ConfigPtr->NumUsersOfAllChannel)[(channel)+1U] - \
    (ComM_ConfigPtr->NumUsersOfAllChannel)[(channel)] )

/**
 ** \brief Returns the user ID of a user assigned to a channel.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param channel the ID of the channel
 ** \param user index in the array of mapped users
 ** \retval the ID of the user
 **/
#if (defined COMM_USER_OF_CHANNEL)
#error COMM_USER_OF_CHANNEL already defined
#endif
#if (COMM_MANUAL_EXPAND_MACRO == STD_ON)
#define COMM_USER_OF_CHANNEL(channel,user) (uint8)\
  ((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &ComM_Configuration)[ComM_Configuration.RootCfg.pUsersOfAllChannel]) \
  [ComM_Configuration.RootCfg.NumUsersOfAllChannel[(channel)] + (user)]
#else
#define COMM_USER_OF_CHANNEL(channel,user) (uint8)\
   ( COMM_PBCFG_ACCESS(uint8,ComM_ConfigPtr->pUsersOfAllChannel)[ \
       (ComM_ConfigPtr->NumUsersOfAllChannel)[(channel)] + (user) ])
#endif

/**
 ** \brief Returns the number of channels assigned to a user.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param user the ID of the User
 ** \retval the number of mapped channels
 **/
#if (defined COMM_NUM_CHANNELS_OF_USER)
#error COMM_NUM_CHANNELS_OF_USER already defined
#endif
#define COMM_NUM_CHANNELS_OF_USER(user) (uint8) \
  ( (ComM_ConfigPtr->NumChannelsOfAllUser)[(user)+1U] - \
    (ComM_ConfigPtr->NumChannelsOfAllUser)[(user)] )

/**
 ** \brief Returns the number of channels directly assigned to a user(not via a pnc).
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param user the ID of the User
 ** \retval the number of mapped channels
 **/
#if (defined COMM_DIRECT_NUM_CHANNELS_OF_USER)
#error COMM_DIRECT_NUM_CHANNELS_OF_USER already defined
#endif
#define COMM_DIRECT_NUM_CHANNELS_OF_USER(user) (uint8) \
  ( (ComM_ConfigPtr->DirectNumChannelsOfAllUser)[(user)+1U] - \
    (ComM_ConfigPtr->DirectNumChannelsOfAllUser)[(user)] )

/**
 ** \brief Returns the channel ID of a channel assigned to a user.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param user the ID of the user
 ** \param channel index in the array of mapped channels
 ** \retval the ID of the channel
 **/
#if (defined COMM_CHANNEL_OF_USER)
#error COMM_CHANNEL_OF_USER already defined
#endif
#if (COMM_MANUAL_EXPAND_MACRO == STD_ON)
#define COMM_CHANNEL_OF_USER(user,channel) (uint8) \
  ((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &ComM_Configuration)[ComM_Configuration.RootCfg.pChannelsOfAllUser]) \
  [ComM_Configuration.RootCfg.NumChannelsOfAllUser[(user)] + (channel)]
#else
#define COMM_CHANNEL_OF_USER(user,channel) (uint8) \
   ( COMM_PBCFG_ACCESS(uint8,ComM_ConfigPtr->pChannelsOfAllUser)[ \
       (ComM_ConfigPtr->NumChannelsOfAllUser)[(user)] + (channel) ])
#endif

#if ( COMM_PNC_SUPPORT == STD_ON )

/**
 ** \brief Evalutes TRUE if PNC support is enabled (FALSE if not).
 **/
#if (defined COMM_PNC_ENABLED)
#error COMM_PNC_ENABLED already defined
#endif
#define COMM_PNC_ENABLED ( (ComM_ConfigPtr->ComMPncEnabled) )


/**
 ** \brief Returns the number of channels associated with a PNC.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the index (not the ID) of the PNC
 ** \retval the number of mapped channels
 **/
#if (defined COMM_NUM_CHANNELS_OF_PNC)
#error COMM_NUM_CHANNELS_OF_PNC already defined
#endif
#define COMM_NUM_CHANNELS_OF_PNC(pnc) (uint8) \
  ( (ComM_ConfigPtr->NumChannelsOfAllPnc)[(pnc)+1U] - \
    (ComM_ConfigPtr->NumChannelsOfAllPnc)[(pnc)] )

/**
 ** \brief Returns a channel ID assigned to a PNC.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the index (not the ID) of the PNC
 ** \param channel index in the array of mapped channels
 ** \retval the ID of the channel
 **/
#if (defined COMM_CHANNEL_OF_PNC)
#error COMM_CHANNEL_OF_PNC already defined
#endif
#if (COMM_MANUAL_EXPAND_MACRO == STD_ON)
#define COMM_CHANNEL_OF_PNC(pnc,channel) (uint8)\
  ((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &ComM_Configuration)[ComM_Configuration.RootCfg.pChannelsOfAllPnc]) \
  [ComM_Configuration.RootCfg.NumChannelsOfAllPnc[(pnc)] + (channel)]
#else
#define COMM_CHANNEL_OF_PNC(pnc,channel) (uint8)\
   ( COMM_PBCFG_ACCESS(uint8,ComM_ConfigPtr->pChannelsOfAllPnc)[ \
       (ComM_ConfigPtr->NumChannelsOfAllPnc)[(pnc)] + (channel) ])
#endif

/**
 ** \brief Returns the number of PNCs associated with a channel.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param channel the id of the channel
 ** \retval the number of mapped PNCs
 **/
#if (defined COMM_NUM_PNCS_OF_CHANNEL)
#error COMM_NUM_PNCS_OF_CHANNEL already defined
#endif
#define COMM_NUM_PNCS_OF_CHANNEL(channel) (uint16) \
  ( (ComM_ConfigPtr->NumPncOfAllCh)[(channel)+1U] - \
    (ComM_ConfigPtr->NumPncOfAllCh)[(channel)] )

/**
 ** \brief Returns a PNC ID assigned to a channel.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param channel the ID of the channel
 ** \param pnc index in the array of mapped PNCs
 ** \retval the ID of the PNC
 **/
#if (defined COMM_PNC_OF_CHANNEL)
#error COMM_PNC_OF_CHANNEL already defined
#endif
#if (COMM_MANUAL_EXPAND_MACRO == STD_ON)
#define COMM_PNC_OF_CHANNEL(channel,pnc) (uint16)\
  ((uint16 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &((uint16 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &ComM_Configuration)[ComM_Configuration.RootCfg.pPNCsOfAllChannel]) \
  [ComM_Configuration.RootCfg.NumPncOfAllCh[(channel)] + (pnc)]
#else
#define COMM_PNC_OF_CHANNEL(channel,pnc) (uint16)\
   ( COMM_PBCFG_ACCESS(uint16,ComM_ConfigPtr->pPNCsOfAllChannel)[ \
       (ComM_ConfigPtr->NumPncOfAllCh)[(channel)] + (pnc) ])
#endif

/**
 ** \brief Returns the number of PNCs associated with a user.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param user the id of the user
 ** \retval the number of mapped PNCs
 **/
#if (defined COMM_NUM_PNCS_OF_USER)
#error COMM_NUM_PNCS_OF_USER already defined
#endif
#define COMM_NUM_PNCS_OF_USER(user) (uint16) \
  ( (ComM_ConfigPtr->NumPncOfAllUser)[(user)+1U] - \
    (ComM_ConfigPtr->NumPncOfAllUser)[(user)] )

/**
 ** \brief Returns a PNC index (NOT THE ID) assigned to a user.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param user the ID of the user
 ** \param pnc index in the array of mapped PNCs
 ** \retval the index of the PNC
 **/
#if (defined COMM_PNC_OF_USER)
#error COMM_PNC_OF_USER already defined
#endif
#if (COMM_MANUAL_EXPAND_MACRO == STD_ON)
#define COMM_PNC_OF_USER(user,pnc) (uint16)\
  ((uint16 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &((uint16 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &ComM_Configuration)[ComM_Configuration.RootCfg.pPncOfAllUser]) \
  [ComM_Configuration.RootCfg.NumPncOfAllUser[(user)] + (pnc)]
#else
#define COMM_PNC_OF_USER(user,pnc) (uint16)\
   ( COMM_PBCFG_ACCESS(uint16,ComM_ConfigPtr->pPncOfAllUser)[ \
       (ComM_ConfigPtr->NumPncOfAllUser)[(user)] + (pnc) ])
#endif

/**
 ** \brief Returns the number of users associated with a PNC.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the index of the PNC
 ** \retval the number of mapped PNCs
 **/
#if (defined COMM_NUM_USERS_OF_PNC)
#error COMM_NUM_USERS_OF_PNC already defined
#endif
#define COMM_NUM_USERS_OF_PNC(pnc) (uint8) \
  ( (ComM_ConfigPtr->NumUsersOfAllPnc)[(pnc)+1U] - \
    (ComM_ConfigPtr->NumUsersOfAllPnc)[(pnc)] )

/**
 ** \brief Returns a user id assigned to a PNC.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the index of the PNC
 ** \param user index in the array of mapped users
 ** \retval the ID of the user
 **/
#if (defined COMM_USER_OF_PNC)
#error COMM_USER_OF_PNC already defined
#endif
#if (COMM_MANUAL_EXPAND_MACRO == STD_ON)
#define COMM_USER_OF_PNC(pnc,user) (uint8)\
  ((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &((uint8 const * AUTOMATIC COMM_APPL_CONST)(void const * AUTOMATIC COMM_APPL_CONST) \
  &ComM_Configuration)[ComM_Configuration.RootCfg.pUsersOfAllPnc]) \
  [ComM_Configuration.RootCfg.NumUsersOfAllPnc[(pnc)] + (user)]
#else
#define COMM_USER_OF_PNC(pnc,user) (uint8)\
   ( COMM_PBCFG_ACCESS(uint8,ComM_ConfigPtr->pUsersOfAllPnc)[ \
       (ComM_ConfigPtr->NumUsersOfAllPnc)[(pnc)] + (user) ])
#endif

#if (COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON)
/**
 ** \brief Returns the if the pnc is top level coordinator.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the index of the PNC
 ** \retval if the pnc is top level coordinator or not
 **/
#if (defined COMM_IS_TOP_LEVEL_COORDINATOR)
#error COMM_IS_TOP_LEVEL_COORDINATOR already defined
#endif
#define COMM_IS_TOP_LEVEL_COORDINATOR(pnc) (boolean)((ComM_ConfigPtr->IsTopLevelCoordinator)[(pnc)])

/**
 ** \brief Returns mask for synchronized shut down channel base on ComMPncGatewayType set to COMM_GATEWAY_TYPE_PASSIVE.
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the mask index
 ** \retval pn mask value
 **/
#if (defined COMM_SYNCHRONIZED_SHUTDOWN_PNC_MASK)
#error COMM_SYNCHRONIZED_SHUTDOWN_PNC_MASK already defined
#endif
#define COMM_SYNCHRONIZED_SHUTDOWN_PNC_MASK(index) (uint8)((ComM_ConfigPtr->SynchronizedShutDownPncMask)[(index)])

/**
 ** \brief Returns if the pnc has mixed chanlles with gateway tye set to active and gateway type set to passive
 **
 ** This macro will function for both post-build selectable (by reference) and
 ** loadable (by offset) variants.
 **
 ** \param pnc the mask index
 ** \retval if pnc has mixed gawatay type channels active and gayeway type passive
 **/
#if (defined COMM_IS_PNC_ACTIVE_MIXED_WITH_PASSIVE)
#error COMM_IS_PNC_ACTIVE_MIXED_WITH_PASSIVE already defined
#endif
#define COMM_IS_PNC_ACTIVE_MIXED_WITH_PASSIVE(pnc) (boolean)((ComM_ConfigPtr->IsPncActiveMixedWithPassive)[(pnc)])

#endif /* #if (COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) */

#endif /* ( COMM_PNC_SUPPORT == STD_ON ) */

/**
 ** \brief Returns between two numbers
 **
 ** \param a
 ** \param b
 ** \retval max(a,b)
 **/
#if (defined COMM_MAX)
#error COMM_MAX already defined
#endif
#define COMM_MAX(A,B) (((A) > (B)) ? (A):(B))

/**
 ** \brief Check if events are present in the channel HSM queue
 **
 ** This macro can be used to scheduale channel HSM execution
 ** only if events are pending.
 **
 ** \param hsmInstance HSM instance number
 ** \retval
 **/
#if (defined COMM_CH_HSM_EVENT_PENDING)
#error COMM_CH_HSM_EVENT_PENDING already defined
#endif
#define COMM_CH_HSM_EVENT_PENDING(hsmInstance) \
    (ComM_HsmScComM.instances[(hsmInstance)].evQueueFill != 0U)

/**
 ** \brief Check if events are present in the PNC HSM queue
 **
 ** This macro can be used to scheduale PNC HSM execution
 ** only if events are pending.
 **
 ** \param hsmInstance HSM instance number
 ** \retval
 **/
#if (defined COMM_PNC_HSM_EVENT_PENDING)
#error COMM_PNC_HSM_EVENT_PENDING already defined
#endif
#define COMM_PNC_HSM_EVENT_PENDING(hsmInstance) \
    (ComM_HsmScComMPnc.instances[(hsmInstance)].evQueueFill != 0U)


/** \brief Enter user exclusive area */
#if (defined COMM_USER_ENTER_EXCLUSIVE_AREA)
#error COMM_USER_ENTER_EXCLUSIVE_AREA already defined
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_USER_ENTER_EXCLUSIVE_AREA(User) ComM_Multicore_UserEnterExclusiveArea_FctPtr_List[User]()
#else /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
#define COMM_USER_ENTER_EXCLUSIVE_AREA(User) ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0()
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/

/** \brief Exit user exclusive area */
#if (defined COMM_USER_EXIT_EXCLUSIVE_AREA)
#error COMM_USER_EXIT_EXCLUSIVE_AREA already defined
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_USER_EXIT_EXCLUSIVE_AREA(User) ComM_Multicore_UserExitExclusiveArea_FctPtr_List[User]()
#else /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
#define COMM_USER_EXIT_EXCLUSIVE_AREA(User) ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0()
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/

/** \brief Enter channel and pnc exclusive area */
#if (defined COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA)
#error COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA already defined
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(HsmInstPtr , Channel) ComM_ChannelPncEnterExclusiveArea((HsmInstPtr), (Channel))
#else /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
#define COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(HsmInstPtr , Channel) ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0()
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/

/** \brief Exit channel and pnc exclusive area */
#if (defined COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA)
#error COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA already defined
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(HsmInstPtr , Channel) ComM_ChannelPncExitExclusiveArea((HsmInstPtr), (Channel))
#else /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
#define COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(HsmInstPtr , Channel) ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0()
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/


/** \brief Enter inhibition exclusive area */
#if (defined COMM_INHIBITION_ENTER_EXCLUSIVE_AREA)
#error COMM_INHIBITION_ENTER_EXCLUSIVE_AREA already defined
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_INHIBITION_ENTER_EXCLUSIVE_AREA() SchM_Enter_ComM_1_Inhibition_SCHM_COMM_EXCLUSIVE_AREA_INHIBITION()
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#define COMM_INHIBITION_ENTER_EXCLUSIVE_AREA() ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0()
#endif

/** \brief Exit inhibition exclusive area */
#if (defined COMM_INHIBITION_EXIT_EXCLUSIVE_AREA)
#error COMM_INHIBITION_EXIT_EXCLUSIVE_AREA already defined
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#define COMM_INHIBITION_EXIT_EXCLUSIVE_AREA() SchM_Exit_ComM_1_Inhibition_SCHM_COMM_EXCLUSIVE_AREA_INHIBITION()
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#define COMM_INHIBITION_EXIT_EXCLUSIVE_AREA() ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0()
#endif

#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (defined COMM_BUSSM_REQUEST_COM_MODE)
#error COMM_BUSSM_REQUEST_COM_MODE already defined
#endif
#define COMM_BUSSM_REQUEST_COM_MODE(channel, mode)  \
  (ComM_BusSmRequestComModeMcFpList[COMM_INST(channel)](COMM_INST(channel), (mode)))
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */

/** \brief Set an event for a specific ComM channel */
#if (defined COMM_EMIT)
#error COMM_EMIT already defined
#endif
#define COMM_EMIT(a,b) (void)COMM_HSMEMITINST((&ComM_HsmScComM), (a), (b))

#if (defined COMM_EMIT_TO_SELF)
#error COMM_EMIT_TO_SELF already defined
#endif
#define COMM_EMIT_TO_SELF(a,b) (void)COMM_HSMEMITTOSELFINST((&ComM_HsmScComM), (a), (b))

/** \brief Set an event for a specific ComM PN Channel */
#if (defined COMM_PNC_EMIT)
#error COMM_PNC_EMIT already defined
#endif
#define COMM_PNC_EMIT(a,b) (void)COMM_HSMEMITINST((&ComM_HsmScComMPnc), (a), (b))

#if (defined COMM_GATEWAY_TYPE_NONE)
#error COMM_GATEWAY_TYPE_NONE already defined
#endif
#define COMM_GATEWAY_TYPE_NONE 0U

#if (defined COMM_GATEWAY_TYPE_ACTIVE)
#error COMM_GATEWAY_TYPE_ACTIVE already defined
#endif
#define COMM_GATEWAY_TYPE_ACTIVE 1U

#if (defined COMM_GATEWAY_TYPE_PASSIVE)
#error COMM_GATEWAY_TYPE_PASSIVE already defined
#endif
#define COMM_GATEWAY_TYPE_PASSIVE 2U

#if (defined COMM_MULTICORE_OP_WAKEUPSLEEPREQUEST)
#error COMM_MULTICORE_OP_WAKEUPSLEEPREQUEST already defined
#endif
#define COMM_MULTICORE_OP_WAKEUPSLEEPREQUEST 1U

#if (defined COMM_MULTICORE_OP_PNCNMREQUEST)
#error COMM_MULTICORE_OP_PNCNMREQUEST already defined
#endif
#define COMM_MULTICORE_OP_PNCNMREQUEST 2U

/*==================[type definitions]======================================*/

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
/** \brief Function pointer type for channel to channel operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_ChToChSchmSend_FctPtr) (P2CONST(ComM_Ch_To_Ch_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for user to inhibition operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_UserToInhibitionPncSchmSend_FctPtr) (uint8 data);
/** \brief Function pointer type for channel to master pnc operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_ChToMasterPncSchmSend_FctPtr) (P2CONST(ComM_Ch_To_MasterPnc_DataType, AUTOMATIC, RTE_APPL_DATA) data);
#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief Function pointer type for master pnc to channel operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_MasterPncToChSchmSend_FctPtr) (P2CONST(ComM_MasterPnc_To_Ch_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for master pnc to channel operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_EvaluateChannelMasterPncToChSchmSend_FctPtr) (P2CONST(ComM_EvaluateChannel_MasterPnc_To_Ch_DataType, AUTOMATIC, RTE_APPL_DATA) data);
#endif /* #if (COMM_PNC_SUPPORT == STD_ON) */
/** \brief Function pointer type for Signal send operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_SignalSchmSend_FctPtr) (P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for user to master pnc operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_UserToMasterPncSchmSend_FctPtr) (P2CONST(ComM_User_To_MasterPnc_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for user to channel send operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_UserToChSchmSend_FctPtr) (P2CONST(ComM_User_To_Ch_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for channel to user operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_ChToUserSchmSend_FctPtr) (P2CONST(ComM_Ch_To_User_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for inhibition to channel operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_InhibitionToChSchmSend_FctPtr) (P2CONST(ComM_Inhibition_To_Ch_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for channel to inhibition operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_ChToInhibitionSchmSend_FctPtr) (P2CONST(ComM_Ch_To_Inhibition_DataType, AUTOMATIC, RTE_APPL_DATA) data);

#if (COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON)
/** \brief Function pointer type for channel to master pnc operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_SynchShutDownChToMasterPncSend_FctPtr) (P2CONST(ComM_SynchShutDown_Ch_To_MasterPnc_DataType, AUTOMATIC, RTE_APPL_DATA) data);
/** \brief Function pointer type for master pnc to ch operation */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Multicore_SynchShutDownMasterPncToChSend_FctPtr) (P2CONST(ComM_SynchShutDown_MasterPnc_To_Ch_DataType, AUTOMATIC, RTE_APPL_DATA) data);
#endif /* #if (COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) */
/** \brief Function pointer type for channel to inhibition operation */
typedef P2FUNC( void,           COMM_APPL_CONST, ComM_Multicore_ExclusiveArea_FctPtr) (void);
#if (COMM_DCM_ENABLED == STD_ON)
/** \brief Function pointer type for Dcm notifications */
typedef P2FUNC( Std_ReturnType, COMM_APPL_CONST, ComM_Dcm_Notif_FctPtr) (uint8 NetworkId);
/** \brief Type for Comm to Dcm notification function pointers */
typedef struct
{
  ComM_Dcm_Notif_FctPtr FullComNotif;
  ComM_Dcm_Notif_FctPtr SilentComNotif;
  ComM_Dcm_Notif_FctPtr NoComNotif;
} ComM_Dcm_Notif_Type;
#endif /* #if (COMM_DCM_ENABLED == STD_ON) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_ON)
/** \brief Function pointer type for BusSM Request */
typedef Std_ReturnType (*ComM_BusSM_RequestComMode_FctPtr)(uint8 network, uint8 ComM_Mode);
/** \brief Function pointer type Master Core send signal */
typedef Std_ReturnType (*ComM_Multicore_SignalSchmSend_FctPtr)(P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) data);

#if (COMM_DCM_ENABLED == STD_ON)
/** \brief Function pointer type for Dcm notifications */
typedef Std_ReturnType (*ComM_Dcm_Notif_FctPtr)(uint8 NetworkId);

/** \brief Type for Comm to Dcm notification function pointers */
typedef struct
{
  ComM_Dcm_Notif_FctPtr FullComNotif;
  ComM_Dcm_Notif_FctPtr SilentComNotif;
  ComM_Dcm_Notif_FctPtr NoComNotif;
} ComM_Dcm_Notif_Type;
#endif /* #if (COMM_DCM_ENABLED == STD_ON) */
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief Type for Tx signals configuration */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
typedef struct
{
#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)
  ComM_Multicore_SignalSchmSend_FctPtr SchMSendFctPtr;
  uint16 MulticoreTxBufferIndex;
  Com_SignalIdType ComHandleId;
  uint8            SignalOsApplication;
  uint8            TxSignalKind;
#else /*#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)*/
  Com_SignalIdType ComHandleId;
  uint8            TxSignalKind;
#endif /*#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0) */
} ComM_TxSignal_Struct_Type;
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
typedef struct
{
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_TX_BUFFERS != 0)
  ComM_Multicore_SignalSchmSend_FctPtr SchMSendFctPtr;
  uint16 MulticoreTxBufferIndex;
  Com_SignalIdType ComHandleId;
  uint8 CoreId;
  uint8            TxSignalKind;
#else /*#if (COMM_NO_OF_TX_BUFFERS != 0)*/
  Com_SignalIdType ComHandleId;
  uint8            TxSignalKind;
#endif /*#if (COMM_NO_OF_TX_BUFFERS != 0) */
#else /*#if (COMM_MULTICORE_ENABLED == STD_ON) */
  Com_SignalIdType ComHandleId;
  uint8            TxSignalKind;
#endif /*#if (COMM_MULTICORE_ENABLED == STD_ON)*/
} ComM_TxSignal_Struct_Type;
#endif /*COMM_OS_APPLICATION_MULTICORE_ENABLED*/

/** \brief Type for Rx signals configuration */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
typedef struct
{
  Com_SignalIdType ComHandleId;
#if (COMM_MULTICORE_NO_OF_RX_BUFFERS != 0)
  uint16 MulticoreRxBufferIndex;
  boolean isLocalOsApplication;
#endif /* #if (COMM_MULTICORE_NO_OF_RX_BUFFERS != 0) */
} ComM_RxSignal_Struct_Type;
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
typedef struct
{
  Com_SignalIdType ComHandleId;
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_RX_BUFFERS != 0)
  uint16 MulticoreRxBufferIndex;
  boolean isLocalCore;
#endif /* #if (COMM_NO_OF_RX_BUFFERS != 0) */
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
} ComM_RxSignal_Struct_Type;
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#if (COMM_NUM_TX_SIGNALS > 0U)
/** \brief Type for PNC to EIRA Signal mapping */
typedef struct
{
  P2CONST(uint8, TYPEDEF, COMM_APPL_CONST) TxSignalList;
  uint8 NumTxSignal;
}ComM_PncTxSigMapType;
#endif
#endif

/**
 ** \brief Type to allow declaration of a do-action function pointer.
 **
 ** Replace HSM do-action. This type allow declaration of a function
 ** pointer which can be used to register a function cyclic execution
 ** in a state_entry and stop this cyclic execution by set to NULL on
 ** state_exit.
 **
 ** \param instIdx HSM instance number
 ** \retval void
 **/
typedef void (*ComM_DoActionType)(uint8 instIdx);



#if(COMM_VLAN_SUPPORT)
/**
 ** \brief Represent link between managed channel and managing channel.
 **
 ** \param managedCh    - channel which reference a managing channel
 ** \param managingCh   - channel referenced by a managed channel
 **/
typedef struct
{
    uint8  managedCh;
    uint8  managingCh;
}ComM_VlanTableStructType;

#endif

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>

/* !LINKSTO ComM.SWS_ComM_00976,1 */
/** \brief Notify Mode Transition of ComM channels to RTE ,DCM and BSWM.
 **
 ** This function notifies the mode change of all ComM channels to RTE(if RTE
 ** enabled) , DCM and BSWM.
 **
 ** \param[in] Channel Network channel on which the mode transition
 **                    has occurred.
 ** \param[in] ComMode Maximum allowed communication mode. */
FUNC(void, COMM_CODE) ComM_Notify(
  uint8         Channel,
  ComM_ModeType ComMMode);

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
/** \brief Channel and PNC enter exclusive area */
FUNC(void, COMM_CODE) ComM_ChannelPncEnterExclusiveArea(const ComM_HsmStatechartPtrType sc, const uint16 idx);
/** \brief Channel and PNC exit exclusive area */
FUNC(void, COMM_CODE) ComM_ChannelPncExitExclusiveArea(const ComM_HsmStatechartPtrType sc, const uint16 idx);
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/

/** \brief Proxy function for SchM_Enter_ComM_SCHM_COMM_EXCLUSIVE_AREA_0
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation unit ComM.c
 **
 ** \return No return value. */
FUNC(void, COMM_CODE) ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0 (
  void);

/** \brief Proxy function for SchM_Exit_ComM_SCHM_COMM_EXCLUSIVE_AREA_0
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation unit ComM.c
 **
 ** \return No return value. */
FUNC(void, COMM_CODE) ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0 (
  void);

/** \brief Evaluate ComM Communication Channels
 ** This function checks the ComM channel mode and emits specific event
 ** related to ComMode.
 ** If the ComM_CurrentChannelRequest RTE interface is enabled, it also
 ** signals the current state of this interface to the RTE.
 ** \param[in] Channel Network channel on which the mode transition
 ** has occurred. */
FUNC(void, COMM_CODE) ComM_EvaluateChannel
(
  uint8 Channel
);

/** \brief Wrapper function to access the ComM_UserRequestedComMode array
 *
 * Accessor function to retrieve the requested communication mode of a
 * given user.
 *
 * \param[in] User A user Id
 * \return The requested communication mode of a given user
 */
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetUserRequestedComMode
(
    uint8 User
);

/** \brief Wrapper function to access the ComM_RequestedComMode, ComM_RequestedComModeWithoutPnc array
 *
 * Accessor function to set the current requested communication mode.
 *
 * \param[in] Channel Network channel of interest
 * \param[in] ComMode The requested communication mode
 * \param[in] ComModeWithoutPncRequest The requested communication mode (user, managed, managing)
 */
FUNC(void, COMM_CODE) ComM_EB_SetRequestedComMode
(
  uint8 Channel,
  ComM_ASR40_ModeType ComMode,
  ComM_ASR40_ModeType ComModeWithoutPncRequest,
  ComM_ASR40_ModeType ComModeWakeupSleepRequest
);

#if (COMM_INCLUDE_RTE == STD_ON)
#if (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE)

/** \brief Signal mode of a channel to a specific user via RTE
 *
 * The function receives a user and translates its channel mode into
 * the values expected by the RTE. The reported values depend
 * on the AUTOSAR service API selected as default.
 *
 * \param[in] User  User of channel whose mode must be reported via RTE */
FUNC(void, COMM_CODE) ComM_RteNotify(
    uint8               User,
    ComM_ASR40_ModeType CurComMMode
);

#endif /* (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE) */

#if (COMM_ENABLE_ASR32_SERVICE_API == STD_ON)

/** \brief Signal mode of a channel to a specific user via RTE
 *
 * The function receives a user and translates its channel mode into
 * the ASR32 values expected by the RTE.
 *
 * \param[in] User  User of channel whose mode must be reported via RTE */
FUNC(void, COMM_CODE) ComM_ASR32_RteNotify(
    uint8               User,
    ComM_ASR32_ModeType CurComMMode
);

#endif /* (COMM_ENABLE_ASR32_SERVICE_API == STD_ON) */

#if (COMM_ENABLE_ASR40_SERVICE_API == STD_ON)

/** \brief Signal mode of a channel to a specific user via RTE
 *
 * The function receives a user and translates its channel mode into
 * the ASR40 values expected by the RTE.
 *
 * \param[in] User  User of channel whose mode must be reported via RTE */
FUNC(void, COMM_CODE) ComM_ASR40_RteNotify(
    uint8               User,
    ComM_ASR40_ModeType CurComMMode
);

#endif /* (COMM_ENABLE_ASR40_SERVICE_API == STD_ON) */
#endif /* (COMM_INCLUDE_RTE == STD_ON) */

#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief Wrapper function to access the ComM_PNCRequestedComMode array
 *
 * Accessor function to retrieve the requested communication mode of a
 * given PNC.
 *
 * \param[in] Channel
 * \param[in] PncPos
 * \return The requested communication mode of the given PNC
 */
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetPncRequestedComMode
(
  uint8 Channel,
  PNCHandleType PncPos
);

#if (COMM_0_PNC_VECTOR_AVOIDANCE == STD_ON)
/** \brief Wrapper function to access the ComM_PNCRequestedComMode0PncVectorAvoidance array
 *
 * Accessor function to retrieve the requested communication mode of a
 * given PNC.
 *
 * \param[in] Channel
 * \param[in] PncPos
 * \return The requested communication mode of the given PNC
 */
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetPncRequestedComMode0PncVectorAvoidance
(
  uint8 Channel,
  PNCHandleType PncPos
);
#endif
#endif /* (COMM_PNC_SUPPORT == STD_ON) */
/** \brief Send RTE mode notification if not allready sent.
 *
 * \param[in] instIdx HSM instance index.
 */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
extern FUNC(void, COMM_CODE) ComM_RteNotificationDoAction(uint8 instIdx);
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */

#if (COMM_INCLUDE_RTE == STD_ON)
/** \brief Notify Mode Transition of ComM channels to RTE
 **
 ** This function notifies the mode change of all ComM channels to RTE(if RTE
 ** enabled)
 **
 ** \param[in] Channel Channel Network channel on which the mode transition
 **                    has occurred.
 */
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_SwitchCurrentRteMode(COMM_PDL_SF(uint8 Channel));
#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && \
     (COMM_NUM_USERS > 0))
/** \brief Clear User request
 **
 ** This function clears usres request in case of mode limitation
 ** and in case of all channels of a user are in no communication
 **
 ** \param[in] Channel Channel Network channel on which the mode transition
 **            has occurred.
 ** \param[in] isChannelContext specifies if function is called from user or channel context
 */
extern FUNC(void, COMM_CODE) ComM_ClearUserRequest_Helper
(
  uint8   instIdx,
  boolean isChannelContext
);
#endif /* #if  (COMM_MODE_LIMITATION_ENABLED == STD_ON) && \
        *      (COMM_NUM_USERS > 0))
        */
#if (COMM_NUM_USERS != 0U)
/** \brief Handles evaluate channel for specific user
 **
 ** This function calls evaluate channel for user specified by input parameter
 **
 ** \param[in] User (specifies the user for which pncs the evaluate channel shall be called)
 ** \param[in] isUserContext specifies if function is called from user or channel context
 **
 ** \return Standard Return Code
 ** \retval E_OK No Errors.
 ** \retval COMM_E_MODE_LIMITATION Mode limitation is active for a channel linked to the user
 */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModeChannel_Helper
(
  ComM_ASR40_UserHandleType User,
  boolean isUserContext
);
#endif /* #if (COMM_NUM_USERS != 0U) */

/** \brief Handle EcuM PNC wakeup indication.
 **
 ** This functions handle channels passive wakeup, following a EcuM PNC wakeup request.
 **
 ** \param[in] Index of the PNC for which wakeup indication was received.
 ** \param[in] isComMEcuMWakeUpIndicationContext specifies if function is called from EcuM wakeup indication or not
 */
extern FUNC(void,COMM_CODE) ComM_PNCWakeUpIndication_ChannelHandle(PNCHandleType pncIdx, boolean isPncContext);

extern FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication_Helper
(
  NetworkHandleType Channel,
  boolean isComMEcuMWakeUpIndicationContext
);

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)
extern FUNC(void, COMM_CODE) ComM_Multicore_Inhibition_To_Ch_Helper
(
  P2CONST(ComM_Inhibition_To_Ch_DataType, AUTOMATIC, AUTOMATIC) data
);
#endif /* #if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)
extern FUNC(void, COMM_CODE) ComM_Multicore_Ch_To_Inhibition_Helper
(
  P2CONST(ComM_Ch_To_Inhibition_DataType, AUTOMATIC, AUTOMATIC) data
);
#endif /* #if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
extern FUNC(void, COMM_CODE) ComM_Multicore_EvaluateChannel_MasterPnc_To_Ch_Helper
(
  P2CONST(ComM_EvaluateChannel_MasterPnc_To_Ch_DataType, AUTOMATIC, COMM_APPL_DATA) data
);
#endif /* #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
extern FUNC(void, COMM_CODE) ComM_Multicore_SynchShutDown_MasterPnc_To_Ch_Helper
(
  P2CONST(ComM_SynchShutDown_MasterPnc_To_Ch_DataType, AUTOMATIC, COMM_APPL_DATA) data
);
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)

#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>
/** \brief Channels enter exclusive area list */
extern CONST(ApplicationType, COMM_CONST) ComM_Multicore_ChannelOsApplication_List[COMM_NUM_CHANNELS];
#if (COMM_NUM_USERS > 0)
extern CONST(ApplicationType, COMM_CONST) ComM_Multicore_UserOsApplication_List[COMM_NUM_USERS];
#endif /* #if (COMM_NUM_USERS > 0) */
#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
/** \brief Channel enter exclusive area function pointer list */
extern CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_ChannelEnterExclusiveArea_FctPtr_List[COMM_NUM_CHANNELS];
/** \brief Channel exit exclusive area function pointer list */
extern CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_ChannelExitExclusiveArea_FctPtr_List[COMM_NUM_CHANNELS];

#if (COMM_NUM_USERS > 0)
/** \brief User enter exclusive area function pointer list */
extern CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_UserEnterExclusiveArea_FctPtr_List[COMM_NUM_USERS];
/** \brief User exit exclusive area function pointer list */
extern CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_UserExitExclusiveArea_FctPtr_List[COMM_NUM_USERS];
#endif /*#if (COMM_NUM_USERS > 0)*/

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#if (COMM_INCLUDE_RTE == STD_ON)
#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>


/** \brief Status flag indicating if the Rte could be notified successfully. */
extern VAR(boolean, COMM_VAR) ComM_RteNotificationSuccessful[USER_ARRAY_SIZE];


#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>

/** \brief Function pointer to routine schedualed from channel main function */
extern VAR(ComM_DoActionType, COMM_VAR) ComM_RteNotificationDoActFkp;

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)*/

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>

extern P2CONST(ComM_ConfigType,AUTOMATIC,COMM_APPL_CONST) ComM_ConfigPtr;

#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_NM_ACCESS_NEEDED == STD_ON))
extern VAR(Nm_ModeType,COMM_VAR) ComM_LastNmMode[COMM_NUM_CHANNELS];
#endif

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
























#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
extern VAR(boolean, COMM_VAR) ComM_EvaluateChannel_MasterPnc_To_Ch_Status[COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
#endif /*  #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
extern VAR(boolean, COMM_VAR) ComM_SynchShutDown_MasterPnc_To_Ch_Status[COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */

#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
extern VAR(ComM_EvaluateChannel_MasterPnc_To_Ch_DataType, COMM_VAR) ComM_EvaluateChannel_MasterPnc_To_Ch;
#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /*  #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
extern VAR(ComM_SynchShutDown_MasterPnc_To_Ch_DataType, COMM_VAR) ComM_SynchShutDown_MasterPnc_To_Ch;
#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#undef TS_RELOCATABLE_CFG_ENABLE
#undef TS_PB_CFG_PTR_CLASS

#endif /* ifndef COMM_INT_H */
/*==================[end of file]===========================================*/
