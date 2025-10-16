/**
 * \file
 *
 * \brief AUTOSAR StbM
 *
 * This file contains the implementation of the AUTOSAR
 * module StbM.
 *
 * \version 5.0.9
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 10.8
 *    The value of a composite expression shall not be cast to a different
 *    essential type category or a wider essential type.
 *
 *    Reason:
 *    Bounds are checked before doing the cast. This is necessary to avoid
 *    warnings on certain compilers like tasking, or diab).
 *
 *  MISRAC2012-2) Deviated Rule: 8.9 (Advisory)
 *    An object should be defined at block scope if its identifier only appears in a single
 *    function.
 *
 *    Reason:
 *    - The AUTOSAR memory mapping requires that functions are mapped in SEC_CODE memory sections.
 *    - Objects at block scope require a different memory mapping, e.g. to a SEC_VAR section,
 *    which leads to nested memory sections, which is not supported by some compilers.
 *
 *  MISRAC2012-3) Deviated Rule: 8.4 (Advisory)
 *    A compatible declaration shall be visible when an object or function with external linkage
 *    is defined
 *
 *    Reason:
 *    StbM_TimerCallback is declared by the Gpt.
 *
 *  MISRAC2012-4) Deviated Rule: 2.1 (required)
 *    A project shall not contain unreachable code.
 *
 *    Reason:
 *    the code is reachable in other configurations.
 */


/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 *
 * TASKING-3) Deviated Rule: W589
 * W589: pointer assumed to be nonzero - test removed
 *
 * Reason:
 * Defensive programming check which checks pointer to be different from NULL_PTR
 *
 * TASKING-4) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * Condition is not always true in other configurations
 *
 * TASKING-5) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * Condition is not always false in other configurations
 */


/*==[Includes]================================================================*/
#include <TSAutosar.h>
#include <TSAtomic_Assign.h>

#include <StbM_Trace.h>
#include <SchM_StbM.h>         /* AUTOSAR BSW scheduler */
#include <StbM.h>
#include <StbM_Int.h>


#if (STBM_NVM_USED == STD_ON)
#include <NvM.h>
#endif /* (STBM_NVM_USED == STD_ON) */

#include <Atomics.h>

#if (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON)
/* If StbM module contains at least 1 time base which has StbMLocalTimeHardware set to EthTSynGlobalTimeDomain,
   include EthIf header in order to have access to EthIf_GetCurrentTime API */
/* !LINKSTO StbM.SWS_StbM_00246,1 */
#include <EthIf.h>
#endif /* (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON) */

#if ((STBM_SYNCMASTER_LINKEDTO_ETHTSYN_TIMEDOMAIN == STD_ON) || (STBM_SYNCSLAVE_LINKEDTO_ETHTSYN_TIMEDOMAIN == STD_ON))
/* include EthTSyn header for EthTSyn_SetProtocolParam or EthTSyn_GetProtocolParam APIs,  only if there is at least one EthTSyn time domain referencing an StbM time base */
/* !LINKSTO StbM.dsn.EthTSynInclusion,1 */
/* !LINKSTO StbM.EB.AtLeastOneEthTSynTDLinkedToStbMTimeBase.EthTSynInclusion.Needed,1 */
#include <EthTSyn.h>
#endif /* ((STBM_SYNCMASTER_LINKEDTO_ETHTSYN_TIMEDOMAIN == STD_ON) || (STBM_SYNCSLAVE_LINKEDTO_ETHTSYN_TIMEDOMAIN == STD_ON)) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON))
#include <StbM_CanTSyn.h>
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)) */

#if ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON))
#include <StbM_FrTSyn.h>
#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)) */

#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
#include <StbM_EthTSyn.h>
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */

#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef STBM_VENDOR_ID /* configuration check */
#error STBM_VENDOR_ID must be defined
#endif

#if (STBM_VENDOR_ID != 1U) /* vendor check */
#error STBM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef STBM_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error STBM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (STBM_AR_RELEASE_MAJOR_VERSION != 4U)
#error STBM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef STBM_AR_RELEASE_MINOR_VERSION /* configuration check */
#error STBM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (STBM_AR_RELEASE_MINOR_VERSION != 7U )
#error STBM_AR_RELEASE_MINOR_VERSION wrong (!= 7U)
#endif

#ifndef STBM_AR_RELEASE_REVISION_VERSION /* configuration check */
#error STBM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (STBM_AR_RELEASE_REVISION_VERSION != 0U )
#error STBM_AR_RELEASE_REVISION_VERSION wrong (!= 0U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef STBM_SW_MAJOR_VERSION /* configuration check */
#error STBM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (STBM_SW_MAJOR_VERSION != 5U)
#error STBM_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#ifndef STBM_SW_MINOR_VERSION /* configuration check */
#error STBM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (STBM_SW_MINOR_VERSION < 0U)
#error STBM_SW_MINOR_VERSION wrong (< 0U)
#endif

#ifndef STBM_SW_PATCH_VERSION /* configuration check */
#error STBM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (STBM_SW_PATCH_VERSION < 9U)
#error STBM_SW_PATCH_VERSION wrong (< 9U)
#endif

/*==[Macros]==================================================================*/

#if (defined STBM_INIT)
#error STBM_INIT is already defined.
#endif
/** \brief Status value: the StbM module is initialized */
#define STBM_INIT                                 1U

#if (defined STBM_NOINIT)
#error STBM_NOINIT is already defined.
#endif
/** \brief Status value: the StbM module is not initialized */
#define STBM_NOINIT                               0U

#if (defined STBM_OFFSET_TIMEBASE_ID_OFFSET)
#error STBM_OFFSET_TIMEBASE_ID_OFFSET is already defined.
#endif
/** \brief Offset value of the Id of a offset time base */
#define STBM_OFFSET_TIMEBASE_ID_OFFSET           16U


#if (defined STBM_MIN_ALLOWED_PURE_TIMEBASE_ID)
#error STBM_MIN_ALLOWED_PURE_TIMEBASE_ID is already defined.
#endif
/** \brief Minimum value for Pure Local Time Base Ids */
#define STBM_MIN_ALLOWED_PURE_TIMEBASE_ID                     32U

#if (defined STBM_MAX_ALLOWED_PURE_TIMEBASE_ID)
#error STBM_MAX_ALLOWED_PURE_TIMEBASE_ID is already defined.
#endif
/** \brief  Maximum value for Pure Local Time Base Ids */
#define STBM_MAX_ALLOWED_PURE_TIMEBASE_ID                     128U

#if (defined STBM_MAX_ALLOWED_TIMEBASE_ID)
#error STBM_MAX_ALLOWED_TIMEBASE_ID is already defined.
#endif
/** \brief Maximum allowed value for Time Base Ids */
#define STBM_MAX_ALLOWED_TIMEBASE_ID                        65535U

#if (defined STBM_NS_PER_SEC)
#error STBM_NS_PER_SEC is already defined.
#endif
/** \brief 1 second expressed in nanoseconds */
#define STBM_NS_PER_SEC                  1000000000U

#if (defined STBM_NS_PER_MICROSEC)
#error STBM_NS_PER_MICROSEC is already defined.
#endif
/** \brief 1 microsecond expressed in nanoseconds */
#define STBM_NS_PER_MICROSEC                  1000U

#if (defined STBM_SEC_PER_MICROSEC)
#error STBM_SEC_PER_MICROSEC is already defined.
#endif
/** \brief 1 seccond expressed in microseconds */
#define STBM_SEC_PER_MICROSEC                  1000000U

#if (defined STBM_MAX_USER_DATA_LENGTH)
#error STBM_MAX_USER_DATA_LENGTH is already defined.
#endif
/** \brief Maximum user data length for the StbM_UserDataType structure */
#define STBM_MAX_USER_DATA_LENGTH                  3U

#if (defined STBM_NANOSEC_MAX_VALID_VALUE)
#error STBM_NANOSEC_MAX_VALID_VALUE is already defined.
#endif
/** \brief Maximum valid value of the nanosecond field in StbM_TimeStampType structure */
#define STBM_NANOSEC_MAX_VALID_VALUE                   999999999U

#if (defined STBM_MAX_NEGATIVE_SINT32_VALUE)
#error STBM_MAX_NEGATIVE_SINT32_VALUE is already defined.
#endif
/** \brief Maximum negative value of sint32 type */
#define STBM_MAX_NEGATIVE_SINT32_VALUE                  -2147483647

#if (defined STBM_MAX_POSITIVE_SINT32_VALUE)
#error STBM_MAX_POSITIVE_SINT32_VALUE is already defined.
#endif
/** \brief Maximum positive value of sint32 type */
#define STBM_MAX_POSITIVE_SINT32_VALUE                  2147483647

#if (defined STBM_INVALID_SEGMENTID)
#error STBM_INVALID_SEGMENTID is already defined.
#endif
/** \brief Invalid value for SegmentId */
#define STBM_INVALID_SEGMENTID          0xFFU

#if (defined STBM_INVALID_CURRENTCYCLE)
#error STBM_INVALID_CURRENTCYCLE is already defined.
#endif
/** \brief Invalid value for currentCycle */
#define STBM_INVALID_CURRENTCYCLE       0x40U

#if (defined STBM_INVALID_CURRENTMACROTICKS)
#error STBM_INVALID_CURRENTMACROTICKS is already defined.
#endif
/** \brief Invalid value for currentMacroticks */
#define STBM_INVALID_CURRENTMACROTICKS  0xFFFFU

#if (defined STBM_INVALID_MACROTICKDURATION)
#error STBM_INVALID_MACROTICKDURATION is already defined.
#endif
/** \brief Invalid value for macrotickDuration */
#define STBM_INVALID_MACROTICKDURATION  0x0U

#if (defined STBM_INVALID_CYCLELENGTH)
#error STBM_INVALID_CYCLELENGTH is already defined.
#endif
/** \brief Invalid value for cycleLength */
#define STBM_INVALID_CYCLELENGTH         0x0U

#if (defined STBM_FLAG_SET)
#error STBM_FLAG_SET is already defined.
#endif
/** \brief Sets a flag
 **
 ** This macro sets the flag given by \p flag in variable
 ** given by \p var.
 **
 ** \param[in] var   Variable where flag shall be set
 ** \param[in] flag  flag (bit position) which shall be set to 1.
 */
#define STBM_FLAG_SET(var,flag)      ((var)  |= (flag))

#if (defined STBM_FLAG_DELETE)
#error STBM_FLAG_DELETE is already defined.
#endif
/** \brief Deletes a flag
 **
 ** This macro deletes the flag given by \p flag in variable
 ** given by \p var.
 ** Note: This macro shall only be used if \p var is of type uint!
 **
 ** \param[in] var   Variable where flag shall be deleted
 ** \param[in] flag  flag (bit position) which shall be set to 0.
 */
#define STBM_FLAG_DELETE(var,flag)   ((var)  &= (~((uint8)(flag))))

#if (defined STBM_FLAG_IS_SET)
#error STBM_FLAG_IS_SET is already defined.
#endif
/** \brief Checks a flag
 **
 ** This macro checks the flag given by \p flag in variable
 ** given by \p var.
 **
 ** \param[in] var   Variable where flag shall be checked
 ** \param[in] flag  flag (bit position) which shall be checked for 1.
 */
#define STBM_FLAG_IS_SET(var,flag)   (((var) & (flag)) != 0U)


#if (defined STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE)
#error STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE is already defined.
#endif /* (defined STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE) */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
 /** \brief Check validity of time base Id
 **
 ** This macro checks for:
 **    - SYNC Id not configured (sync id within [0, 15] interval, which is greater or equal than 0 + number of sync time bases) or
 **    - OFSFET Id not configured range (offset id within [16, 31] interval, which is greater or equal than 16 + number of offset time bases) or
 **    - PURE Id not configured (pure id within [32, 127] interval, which is greater or equal than 32 + number of pure time bases)
 **    - invalid ids within the RESERVED range ( ids from [128, 65535] interval)
 ** It evaluates to 'TRUE' if the given Id is invalid.
 **
 ** \param[in] id - ID of the time-base.
 */
#if(STBM_NUMBER_OF_SYNC_TIMEBASES == 0U)
#define STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(id)                                                  \
        (                                                                                                             \
             ( (id) < STBM_MIN_ALLOWED_PURE_TIMEBASE_ID )                                                             \
          || (    (((id) >= STBM_MIN_ALLOWED_PURE_TIMEBASE_ID) && ((id) < STBM_MAX_ALLOWED_PURE_TIMEBASE_ID))         \
               && ((id) >= (STBM_MIN_ALLOWED_PURE_TIMEBASE_ID + STBM_NUMBER_OF_PURE_TIMEBASES))                       \
          )                                                                                                           \
          || ( (id) >= STBM_MAX_ALLOWED_PURE_TIMEBASE_ID )                                                            \
        )
#else

#define STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(id)                                                  \
        (    (   ((id) < STBM_OFFSET_TIMEBASE_ID_OFFSET)                                                              \
              && ((id) >= STBM_NUMBER_OF_SYNC_TIMEBASES)                                                              \
             )                                                                                                        \
          || (   (((id) >= STBM_OFFSET_TIMEBASE_ID_OFFSET) && ((id) <= (STBM_MIN_ALLOWED_PURE_TIMEBASE_ID - 1U)))     \
              && ((id) >= (STBM_OFFSET_TIMEBASE_ID_OFFSET + STBM_NUMBER_OF_OFFSET_TIMEBASES))                         \
             )                                                                                                        \
          || (    (((id) >= STBM_MIN_ALLOWED_PURE_TIMEBASE_ID) && ((id) < STBM_MAX_ALLOWED_PURE_TIMEBASE_ID))         \
               && ((id) >= (STBM_MIN_ALLOWED_PURE_TIMEBASE_ID + STBM_NUMBER_OF_PURE_TIMEBASES))                       \
             )                                                                                                        \
          || ( (id) >= STBM_MAX_ALLOWED_PURE_TIMEBASE_ID )                                                            \
        )
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES == 0U) */


#if(STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

#if (defined STBM_CUSTOMER_ID_NOT_CONFIGURED) /* to prevent double declaration */
#error STBM_CUSTOMER_ID_NOT_CONFIGURED is already defined
#endif

#define STBM_CUSTOMER_ID_NOT_CONFIGURED(commonId, customerId)                             \
        (customerId >= StbM_CommonTimeBaseCfg[(commonId)].numberOfNotificationCustomers)  \

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */


#endif /* STBM_DEV_ERROR_DETECT == STD_ON */


#if (defined STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE)
#error STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE is already defined.
#endif /* (defined STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE) */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
 /** \brief Check validity of time base Id
 **
 ** This macro checks for:
 **    - SYNC Id not configured (sync id within [0, 15] interval, which is greater or equal than 0 + number of sync time bases) or
 **    - OFSFET Id not configured range (offset id within [16, 31] interval, which is greater or equal than 16 + number of offset time bases) or
 **    - invalid ids within the PURE - RESERVED range ( ids from [32, 65535] interval)
 ** It evaluates to 'TRUE' if the given Id is invalid.
 **
 ** \param[in] id - ID of the time-base.
 */
#if(STBM_NUMBER_OF_SYNC_TIMEBASES == 0U)
#define STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(id) TRUE
#else /* (STBM_NUMBER_OF_SYNC_TIMEBASES == 0U) */
#define STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(id)                                                  \
        (    (   ((id) < STBM_OFFSET_TIMEBASE_ID_OFFSET)                                                              \
              && ((id) >= STBM_NUMBER_OF_SYNC_TIMEBASES)                                                              \
             )                                                                                                        \
          || (   (((id) >= STBM_OFFSET_TIMEBASE_ID_OFFSET) && ((id) <= (STBM_MIN_ALLOWED_PURE_TIMEBASE_ID - 1U)))     \
              && ((id) >= (STBM_OFFSET_TIMEBASE_ID_OFFSET + STBM_NUMBER_OF_OFFSET_TIMEBASES))                         \
             )                                                                                                        \
          || ( (id) >= STBM_MIN_ALLOWED_PURE_TIMEBASE_ID )                                                             \
        )

#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES == 0U) */
#endif /* STBM_DEV_ERROR_DETECT == STD_ON */


#if (defined STBM_COMMON_INDEX_TO_TIMEBASEID)
#error STBM_COMMON_INDEX_TO_TIMEBASEID is already defined.
#endif /* (defined STBM_COMMON_INDEX_TO_TIMEBASEID) */

#if(STBM_NUMBER_OF_SYNC_TIMEBASES == 0U)
#define STBM_COMMON_INDEX_TO_TIMEBASEID(id) ((id) + 32U)
#else
#if(STBM_NUMBER_OF_OFFSET_TIMEBASES != 0U)
#if(STBM_NUMBER_OF_PURE_TIMEBASES != 0U)
#define STBM_COMMON_INDEX_TO_TIMEBASEID(id)                                                                     \
        (                                                                                                       \
          ((id) >= (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES))                           \
          ? (((id) - (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES)) + 32U)                  \
          : STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID(id)                                                   \
        )
#else /* (STBM_NUMBER_OF_PURE_TIMEBASES == 0U) */
#define STBM_COMMON_INDEX_TO_TIMEBASEID(id) (STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID(id))
#endif /* (STBM_NUMBER_OF_PURE_TIMEBASES != 0U) */
#else /* (STBM_NUMBER_OF_OFFSET_TIMEBASES == 0U) */
#if(STBM_NUMBER_OF_PURE_TIMEBASES != 0U)
#define STBM_COMMON_INDEX_TO_TIMEBASEID(id)                                                                     \
        (                                                                                                       \
          ((id) >= STBM_NUMBER_OF_SYNC_TIMEBASES)                                                               \
          ? (((id) - STBM_NUMBER_OF_SYNC_TIMEBASES) + 32U)                                                      \
          : (id)                                                                                                \
        )
#else /* (STBM_NUMBER_OF_PURE_TIMEBASES == 0U) */
#define STBM_COMMON_INDEX_TO_TIMEBASEID(id)  (id)
#endif /* (STBM_NUMBER_OF_PURE_TIMEBASES != 0U) */
#endif /* (STBM_NUMBER_OF_OFFSET_TIMEBASES != 0U) */


#if (defined STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID)
#error STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID is already defined.
#endif /* (defined STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID) */

#if(STBM_NUMBER_OF_OFFSET_TIMEBASES != 0U)
#define STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID(id)                   \
        (                                                                   \
          ((id) >= STBM_NUMBER_OF_SYNC_TIMEBASES)                           \
          ? (((id) - STBM_NUMBER_OF_SYNC_TIMEBASES) + 16U)                  \
          : (id)                                                            \
        )
#else /* (STBM_NUMBER_OF_OFFSET_TIMEBASES == 0U) */
#define STBM_SYNC_OR_OFFSET_COMMON_INDEXTO_TIMEBASEID(id)  (id)
#endif /* (STBM_NUMBER_OF_OFFSET_TIMEBASES != 0U) */
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES == 0U) */




#if (defined STBM_IS_SYNC_TIMEBASE_ID)
#error STBM_IS_SYNC_TIMEBASE_ID is already defined.
#endif /* (defined STBM_IS_SYNC_TIMEBASE_ID) */
/** \brief Check validity of time base Id
 **
 ** This macro checks if the given time base Id is a valid sync time base.
 ** It evaluates to 'TRUE' if the given Id is a valid  time base id.
 **
 ** \param[in] id - ID of the time-base.
 */
#define STBM_IS_SYNC_TIMEBASE_ID(id) ((id) < STBM_OFFSET_TIMEBASE_ID_OFFSET)



#if (defined STBM_IS_PURE_TIMEBASE_ID)
#error STBM_IS_PURE_TIMEBASE_ID is already defined.
#endif /* (defined STBM_IS_PURE_TIMEBASE_ID) */
/** \brief Check validity of time base Id
 **
 ** This macro checks if the given time base Id is a valid pure time base.
 ** It evaluates to 'TRUE' if the given Id is a valid pure time base id.
 **
 ** \param[in] id - ID of the time-base.
 */
#define STBM_IS_PURE_TIMEBASE_ID(id) ( ((id) >= STBM_MIN_ALLOWED_PURE_TIMEBASE_ID) && ((id) < STBM_MAX_ALLOWED_PURE_TIMEBASE_ID) )


#if (defined STBM_IS_OFFSET_TIMEBASE_ID)
#error STBM_IS_OFFSET_TIMEBASE_ID is already defined.
#endif /* (defined STBM_IS_OFFSET_TIMEBASE_ID) */
/** \brief Check validity of time base Id
 **
 ** This macro checks if the given time base Id is a valid offset time base.
 ** It evaluates to 'TRUE' if the given Id is a valid offset time base id.
 **
 ** \param[in] id - ID of the time-base.
 */
#define STBM_IS_OFFSET_TIMEBASE_ID(id) ( ((id) >= STBM_OFFSET_TIMEBASE_ID_OFFSET) && ((id) < (STBM_MIN_ALLOWED_PURE_TIMEBASE_ID)) )



#if (defined STBM_IS_COMMON_INDEX_A_PURE_TIMEBASE_ID)
#error STBM_IS_COMMON_INDEX_A_PURE_TIMEBASE_ID is already defined.
#endif /* (defined STBM_IS_COMMON_INDEX_A_PURE_TIMEBASE_ID) */
/** \brief Check validity of time base Id
 **
 ** This macro checks if the given common index is a pure time base id.
 ** It evaluates to 'TRUE' if the given Id is a pure time base id.
 **
 ** \param[in] id - common index.
 */
#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
#define STBM_IS_COMMON_INDEX_A_PURE_TIMEBASE_ID(id) ((id) >=  (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES))
#else
#define STBM_IS_COMMON_INDEX_A_PURE_TIMEBASE_ID(id) TRUE
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */


#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
#if (defined STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED)
#error STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED is already defined.
#endif
/** \brief Checks threshold value
 **
 ** This macro checks if the threshold value (StbMTimeLeapFutureThreshold) is
 ** disabled for a given time base.
 ** It evaluates to 'TRUE' if the treshold is disabled.
 **
 ** \param[in] commonId - common Id of a time base
 */
#define STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED(commonId)                            \
        (                                                                             \
              ( StbM_CommonTimeBaseCfg[(commonId)].timeleapFutureValueNs == 0U )      \
           && ( StbM_CommonTimeBaseCfg[(commonId)].timeleapFutureValueSec == 0U )     \
        )

#if (defined STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED)
#error STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED is already defined.
#endif /* defined STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED */
/** \brief Checks threshold value
 **
 ** This macro checks if the threshold value (StbMTimeLeapPastThreshold) is
 ** disabled for a given time base.
 ** It evaluates to 'TRUE' if the threshold is disabled.
 **
 ** \param[in] commonId - common Id of a time base
 */
#define STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED(commonId)                            \
        (                                                                           \
              ( StbM_CommonTimeBaseCfg[(commonId)].timeleapPastValueNs == 0U )      \
           && ( StbM_CommonTimeBaseCfg[(commonId)].timeleapPastValueSec == 0U )     \
        )

#if (defined STBM_ASSIGN_TIMESTAMP)
#error STBM_ASSIGN_TIMESTAMP is already defined.
#endif /* defined STBM_ASSIGN_TIMESTAMP */
#else

#if (defined STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED)
#error STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED is already defined.
#endif /* defined STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED */
#define STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED(commonId) TRUE

#if (defined STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED)
#error STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED is already defined.
#endif
#define STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED(commonId) TRUE

#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */

#if (defined STBM_OFFSET_CORRECTION_DISABLED)
#error STBM_OFFSET_CORRECTION_DISABLED is already defined.
#endif
/** \brief Checks threshold value
 **
 ** This macro checks if the threshold value (StbMOffsetCorrectionJumpThreshold) is
 ** disabled for a given sync time base.
 ** It evaluates to 'TRUE' if the threshold is disabled.
 **
 ** \param[in] commonId - common Id of time base
 */

#define STBM_OFFSET_CORRECTION_DISABLED(commonId)                                                                         \
        (                                                                                                                 \
                ( StbM_CommonTimeBaseCfg[(commonId)].offsetCorrectionJumpThresholdNs == 0U )                              \
             && ( StbM_CommonTimeBaseCfg[(commonId)].offsetCorrectionJumpThresholdSec == 0U )                             \
        )

#if (defined STBM_TIMELEAP_OR_OFFSET_DISABLED)
#error STBM_TIMELEAP_OR_OFFSET_DISABLED is already defined.
#endif
/** \brief Checks threshold value
 **
 ** This macro checks if timeleap or offset feature is
 ** disabled for a given time base.
 ** It evaluates to 'TRUE' if the treshold is disabled.
 **
 ** \param[in] commonId - common Id of time base
 */
#if ((STBM_OFFSET_CORRECTION_USED == STD_ON) && (STBM_TIMELEAP_DETECTION_USED == STD_ON))
#define STBM_TIMELEAP_OR_OFFSET_DISABLED(commonId)                                         \
        (                                                                                  \
              (!STBM_OFFSET_CORRECTION_DISABLED(commonId))                                 \
           || (!STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED(commonId))                          \
           || (!STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED(commonId))                        \
        )
#elif (STBM_OFFSET_CORRECTION_USED == STD_ON)
#define STBM_TIMELEAP_OR_OFFSET_DISABLED(commonId)                                         \
        (                                                                                  \
              (!STBM_OFFSET_CORRECTION_DISABLED(commonId))                                 \
        )
#else
#define STBM_TIMELEAP_OR_OFFSET_DISABLED(commonId)                                         \
        (                                                                                  \
              (!STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED(commonId))                          \
           || (!STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED(commonId))                        \
        )
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) && (STBM_TIMELEAP_DETECTION_USED == STD_ON) */

#if (defined STBM_TIME_RECORDING_DISABLED)
#error STBM_TIME_RECORDING_DISABLED is already defined.
#endif
/** \brief Checks if time recording is enabled on a certain time base
 **
 ** This macro takes any common time base id and checks if that time base uses
 ** time recording.
 ** (common time base index received)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - (common time base index)
 */
#define STBM_TIME_RECORDING_DISABLED(commonId)                           \
        ( StbM_CommonTimeBaseCfg[(commonId)].numberOfBlocks == 0U )

#if (defined STBM_STORE_AND_LOAD_TIME_NVM_DISABLED)
#error STBM_STORE_AND_LOAD_TIME_NVM_DISABLED is already defined.
#endif
/** \brief Checks if NvM is enabled on a certain time base
 **
 ** This macro takes any common time base id and checks if that time base stores the TimeStamp in NvM at SHUTDOWN
 ** and load it from NvM at INITIALIZATION phase
 ** (common time base index received)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - (common time base index)
 */
#define STBM_STORE_AND_LOAD_TIME_NVM_DISABLED(commonId)                           \
        ( StbM_CommonTimeBaseCfg[(commonId)].NvMBlockId == 0U)


#if (defined STBM_GET_SHARED_MEMORY_INDEX)
#error STBM_GET_SHARED_MEMORY_INDEX is already defined.
#endif
/** \brief Gets the shared memory index for this time base
 **
 ** This macro takes any time base id and gives back the corresponding index in the shared memory
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - common id
 */
#define STBM_GET_SHARED_MEMORY_INDEX(commonId) (StbM_CommonTimeBaseCfg[commonId].timeBaseSharesDataIdx)


#if (defined STBM_GET_NVM_BLOCK_ID)
#error STBM_GET_NVM_BLOCK_ID is already defined.
#endif
/** \brief Gets the related NvM Block Id
 **
 ** This macro takes any time base id and gives back the corresponding NvM Block Id
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync or offset)
 */
#define STBM_GET_NVM_BLOCK_ID(commonId) (StbM_CommonTimeBaseCfg[commonId].NvMBlockId)


#if (defined STBM_SLAVE_RATE_CORRECTION_DISABLED)
#error STBM_SLAVE_RATE_CORRECTION_DISABLED is already defined.
#endif
/** \brief Checks if rate correction is enabled on a certain time base
 **
 ** This macro takes any time base id and checks if that time base uses
 ** rate correction.
 ** (id is a common index)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - timebase ID (any - sync or offset)
 */
#define STBM_SLAVE_RATE_CORRECTION_DISABLED(commonId)                                \
(                                                                                    \
      ( StbM_CommonTimeBaseCfg[(commonId)].rateCorrectionIntervalNs == 0U )          \
   && ( StbM_CommonTimeBaseCfg[(commonId)].rateCorrectionIntervalSec == 0U )         \
)

#if (defined STBM_SLAVE_RATE_CORRECTION_TO_COMMON_DISABLED)
#error STBM_SLAVE_RATE_CORRECTION_TO_COMMON_DISABLED is already defined.
#endif
/** \brief Checks if rate correction is enabled on a certain time base
 **
 ** This macro takes any time base id and checks if that time base uses
 ** rate correction.
 ** (id is converted to a common index)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync or offset)
 */
#define STBM_SLAVE_RATE_CORRECTION_TO_COMMON_DISABLED(id) (STBM_SLAVE_RATE_CORRECTION_DISABLED(STBM_TIMEBASE_ID_TO_COMMON_INDEX((id))))

#if (defined STBM_MASTER_IS_SYSTEM_WIDE_MASTER)
#error STBM_MASTER_IS_SYSTEM_WIDE_MASTER is already defined.
#endif
/** \brief Checks if time base is sytem wide global master
 **
 ** This macro takes any common time base id and checks if that time base is
 ** a sytem wide global master.
 ** (a common index will be received)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - common timebase index
 */
#define STBM_MASTER_IS_SYSTEM_WIDE_MASTER(commonId)                                                             \
        (                                                                                                       \
              ( StbM_CommonTimeBaseCfg[(commonId)].masterRcArrayIndex != STBM_INVALID_INDEX )                   \
           && ( StbM_CommonTimeBaseCfg[(commonId)].systemWideMaster == STBM_SYSTEM_WIDE_MASTER_ENABLED )    \
        )


#if (defined STBM_MASTER_RATE_CORRECTION_DISABLED)
#error STBM_MASTER_RATE_CORRECTION_DISABLED is already defined.
#endif
/** \brief Checks if rate correction is enabled on a certain time base
 **
 ** This macro takes any time base id and checks if that time base uses
 ** rate correction.
 ** (the id must be a common index)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync or offset)
 */
#define STBM_MASTER_RATE_CORRECTION_DISABLED(commonId)                                         \
        (                                                                                      \
              ( StbM_CommonTimeBaseCfg[(commonId)].masterRcArrayIndex == STBM_INVALID_INDEX )  \
        )

#if (defined STBM_MASTER_RATE_CORRECTION_TO_COMMON_DISABLED)
#error STBM_MASTER_RATE_CORRECTION_TO_COMMON_DISABLED is already defined.
#endif
/** \brief Checks if rate correction is enabled on a certain time base
 **
 ** This macro takes any time base id and checks if that time base uses
 ** rate correction.
 ** (the id is transformed to a common index)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync or offset)
 */
#define STBM_MASTER_RATE_CORRECTION_TO_COMMON_DISABLED(id) (STBM_MASTER_RATE_CORRECTION_DISABLED(STBM_TIMEBASE_ID_TO_COMMON_INDEX((id))))


#if (defined STBM_EXPIRE_TIME_IS_ZERO)
#error STBM_EXPIRE_TIME_IS_ZERO is already defined.
#endif
/** \brief Checks if expire time is zero
 **
 ** This macro checks if nanoseconds and seconds are equal to zero in expire time
 ** are zero.
 ** It evaluates to 'TRUE' if the expire time is zero.
 **
 ** \param[in] expireTime - the evaluated expireTime
 */
#define STBM_EXPIRE_TIME_IS_ZERO(expireTime)                     \
        (                                                        \
              ( (*expireTime).nanoseconds == 0U )                \
           && ( (*expireTime).seconds == 0U )                    \
        )


#if (defined STBM_VIRTUAL_LOCAL_TIME_IS_ZERO)
#error STBM_VIRTUAL_LOCAL_TIME_IS_ZERO is already defined.
#endif
/** \brief Checks if virtualLocalTime  is zero
 **
 ** This macro checks if all the values in a virtualLocalTime
 ** are zero.
 ** It evaluates to 'TRUE' if the virtualLocalTime is zero.
 **
 ** \param[in] virtualLocalTime - the evaluated virtualLocalTime
 */
#define STBM_VIRTUAL_LOCAL_TIME_IS_ZERO(virtualLocalTime)        \
        (                                                        \
              ( (virtualLocalTime).nanosecondsLo == 0U )         \
           && ( (virtualLocalTime).nanosecondsHi == 0U )         \
        )

#if (defined STBM_TIME_STAMP_AND_VIRTUAL_LOCAL_TIME_IS_ZERO)
#error STBM_TIME_STAMP_AND_VIRTUAL_LOCAL_TIME_IS_ZERO is already defined.
#endif
/** \brief Checks if timestamp and virtualLocalTime is zero
 **
 ** This macro checks if all the values in a timestamp and
 ** virtualLocalTime are zero.
 ** It evaluates to 'TRUE' if the timestamp and virtualLocalTime is zero.
 **
 ** \param[in] timestamp - the evaluated timestamp
 ** \param[in] virtualLocalTime - the evaluated virtualLocalTime
 */
#define STBM_TIME_STAMP_AND_VIRTUAL_LOCAL_TIME_IS_ZERO(timestamp,virtualLocalTime)        \
        (                                                        \
              ( (timestamp)->nanoseconds == 0U )               \
           && ( (timestamp)->seconds == 0U )                   \
           && ( (timestamp)->secondsHi == 0U )                 \
           && ( (virtualLocalTime)->nanosecondsLo == 0U )      \
           && ( (virtualLocalTime)->nanosecondsHi == 0U )      \
        )

#if (defined STBM_ASSIGN_TIMESTAMP)
#error STBM_ASSIGN_TIMESTAMP is already defined.
#endif
/** \brief Copies time part of the StbM_TimeStampType
 **
 ** This macro copies the time members (nanoseconds, seconds and secondsHi)
 ** of a structure of type StbM_TimeStampType.
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_TIMESTAMP(dst,src)                  \
        do                                              \
        {                                               \
          (dst).nanoseconds = (src).nanoseconds;        \
          (dst).seconds = (src).seconds;                \
          (dst).secondsHi = (src).secondsHi;            \
        } while (0)


#if (defined STBM_ASSIGN_TIMESTAMP_TO_EXTENDEDTIMESTAMP)
#error STBM_ASSIGN_TIMESTAMP_TO_EXTENDEDTIMESTAMP is already defined.
#endif
/** \brief Copies time part of the StbM_TimeStampType into StbM_TimeStampExtendedType
 **
 ** This macro copies the time members (nanoseconds, seconds and secondsHi) of a structure of type StbM_TimeStampType,
 ** into the time members (nanoseconds and seconds) of a structure of type StbM_TimeStampExtendedType.
 **     StbM_TimeStampExtendedType                   StbM_TimeStampType
 **         nanoseconds                   <-              nanoseconds
 **         seconds                       <-              seconds
 **         seconds << 32                 <-              secondsHi
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_TIMESTAMP_TO_EXTENDEDTIMESTAMP(dst,src)               \
        do                                                                \
        {                                                                 \
          (dst).nanoseconds = (src).nanoseconds;                          \
          (dst).seconds = ((uint64)(src).secondsHi << 32U) | (src).seconds;  \
        } while (0)

#if (defined STBM_ASSIGN_VIRTUAL_LOCAL_TIME)
#error STBM_ASSIGN_VIRTUAL_LOCAL_TIME is already defined.
#endif
/** \brief Copies time part of the StbM_VirtualLocalTimeType
 **
 ** This macro copies the time members (nanosecondsHi, nanosecondsLo)
 ** of a structure of type StbM_VirtualLocalTimeType.
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_VIRTUAL_LOCAL_TIME(dst,src)             \
        do                                                  \
        {                                                   \
          (dst).nanosecondsLo = (src).nanosecondsLo;        \
          (dst).nanosecondsHi = (src).nanosecondsHi;        \
        } while (0)



#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)

#if (defined STBM_ASSIGN_SYNC_RECORDTABLEBLOCK)
#error STBM_ASSIGN_SYNC_RECORDTABLEBLOCK is already defined.
#endif
/** \brief Copies sync measurement data of the StbM_SyncRecordTableBlockType
 **
 ** This macro copies the time members
 ** of a structure of type StbM_SyncRecordTableBlockType.
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_SYNC_RECORDTABLEBLOCK(dst,src)                   \
        do                                                           \
        {                                                            \
          (dst).TimeBaseStatus      = (src).TimeBaseStatus;          \
          (dst).GlbSeconds          = (src).GlbSeconds;              \
          (dst).GlbNanoSeconds      = (src).GlbNanoSeconds;          \
          (dst).VirtualLocalTimeLow = (src).VirtualLocalTimeLow;     \
          (dst).LocSeconds          = (src).LocSeconds;              \
          (dst).LocNanoSeconds      = (src).LocNanoSeconds;          \
          (dst).PathDelay           = (src).PathDelay;               \
          (dst).RateDeviation       = (src).RateDeviation;           \
        } while (0)

#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)

#if (defined STBM_ASSIGN_OFFSET_RECORDTABLEBLOCK)
#error STBM_ASSIGN_OFFSET_RECORDTABLEBLOCK is already defined.
#endif
/** \brief Copies offset measurement data of the StbM_OffsetRecordTableBlockType
 **
 ** This macro copies the time members
 ** of a structure of type StbM_OffsetRecordTableBlockType.
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_OFFSET_RECORDTABLEBLOCK(dst,src)                \
        do                                                          \
        {                                                           \
          (dst).TimeBaseStatus      = (src).TimeBaseStatus;         \
          (dst).GlbSeconds          = (src).GlbSeconds;             \
          (dst).GlbNanoSeconds      = (src).GlbNanoSeconds;         \
        } while (0)

#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */



#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

#if (defined STBM_ASSIGN_CUSTOMERID_TIMEBASEID_EXPIRETIME)
#error STBM_ASSIGN_CUSTOMERID_TIMEBASEID_EXPIRETIME is already defined.
#endif
/** \brief Copies expire time data of the StbM_CustomerTimerExpireTimeDataType
 **        to the expire time data of the node of type StbM_CustomerTimerExpireTimeNodeDataType.
 **
 ** This macro copies the expire time data members
 ** (timeBaseId, customerId, customerTimerExpireTime) from a structure of type StbM_CustomerTimerExpireTimeDataType
 ** to a structure of type StbM_CustomerTimerExpireTimeNodeDataType.
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_CUSTOMERID_TIMEBASEID_EXPIRETIME(dst,src)   \
        do                                                                      \
        {                                                                       \
          (dst).timeBaseId = (src).timeBaseId;                                  \
          (dst).customerId = (src).customerId;                                  \
          (dst).customerTimerExpireTime = (src).customerTimerExpireTime;        \
        } while (0)

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if (defined STBM_ASSIGN_SHORTTIMESTAMP)
#error STBM_ASSIGN_SHORTTIMESTAMP is already defined.
#endif
/** \brief Copies time part of the StbM_TimeStampType to StbM_TimeStampShortType
 **
 ** This macro copies the time members (nanoseconds, seconds)
 ** of a structure of type StbM_TimeStampType to a structure of type StbM_TimeStampShortType (nanoseconds, seconds).
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_SHORTTIMESTAMP(dst,src)      \
        do                                              \
        {                                               \
          (dst).nanoseconds = (src).nanoseconds;        \
          (dst).seconds = (src).seconds;                \
        } while (0)

#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */



#if (defined STBM_INIT_TIMESTAMP_0)
#error STBM_INIT_TIMESTAMP_0 is already defined.
#endif
/** \brief Initialize time part of the StbM_TimeStampType
 **
 ** This macro initializes with 0 the time members (nanoseconds, seconds and secondsHi)
 ** of a structure of type StbM_TimeStampType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_TIMESTAMP_0(dst)           \
        do                                   \
        {                                    \
          (dst).nanoseconds = 0U;            \
          (dst).seconds = 0U;                \
          (dst).secondsHi = 0U;              \
          (dst).timeBaseStatus = 0U;         \
        } while (0)

#if (defined STBM_INIT_TIMETUPLE_0)
#error STBM_INIT_TIMETUPLE_0 is already defined.
#endif
/** \brief Initialize the StbM_VirtualLocalTimeType
 **
 ** This macro initializes with 0 the time members (nanosecondsLo, nanosecondsHi)
 ** of a structure of type StbM_VirtualLocalTimeType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_TIMETUPLE_0(dst)                            \
        do                                                    \
        {                                                     \
          (dst).globalTime.nanoseconds = 0U;                  \
          (dst).globalTime.seconds = 0U;                      \
          (dst).globalTime.secondsHi = 0U;                    \
          (dst).globalTime.timeBaseStatus = 0U;               \
          (dst).virtualLocalTime.nanosecondsLo = 0U;          \
          (dst).virtualLocalTime.nanosecondsHi = 0U;          \
        } while (0)

#if (defined STBM_INIT_VIRTUAL_LOCAL_TIME_1)
#error STBM_INIT_VIRTUAL_LOCAL_TIME_1 is already defined.
#endif
/** \brief Initialize time part of the StbM_VirtualLocalTimeType with 1ns
 **
 ** This macro initializes the virtual local time with 1ns
 ** of a structure of type StbM_VirtualLocalTimeType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_VIRTUAL_LOCAL_TIME_1(dst)        \
        do                                         \
        {                                          \
          (dst).nanosecondsLo = 1U;                \
          (dst).nanosecondsHi = 0U;                \
        } while (0)

#if (defined STBM_INIT_VIRTUAL_LOCAL_TIME_0)
#error STBM_INIT_VIRTUAL_LOCAL_TIME_0 is already defined.
#endif
/** \brief Initialize time part of the StbM_VirtualLocalTimeType with 0ns
 **
 ** This macro initializes the virtual local time with 0ns
 ** of a structure of type StbM_VirtualLocalTimeType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_VIRTUAL_LOCAL_TIME_0(dst)        \
        do                                         \
        {                                          \
          (dst).nanosecondsLo = 0U;                \
          (dst).nanosecondsHi = 0U;                \
        } while (0)


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if (defined STBM_ASSIGN_PORT_ID)
#error STBM_ASSIGN_PORT_ID is already defined.
#endif
/** \brief Copies clockIdentity and portNumber of the StbM_PortIdType
 **
 ** This macro copies the members (clockIdentity, portNumber)
 ** of a structure of type StbM_PortIdType.
 **
 ** \param[in] dst - Destination struct for assignment
 ** \param[in] src - Source struct for assignment
 */
#define STBM_ASSIGN_PORT_ID(dst, src)                \
        do                                           \
        {                                            \
          (dst).clockIdentity = (src).clockIdentity; \
          (dst).portNumber = (src).portNumber;       \
        } while (0)



#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */




#if  (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

#if (defined STBM_INIT_LOCALTIMECALL_0)
#error STBM_INIT_LOCALTIMECALL_0 is already defined.
#endif
/** \brief Initialize time part of the StbM_LocalTimeCallType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_LocalTimeCallType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_LOCALTIMECALL_0(dst)                             \
        do                                                         \
        {                                                          \
          (dst).localTime.timeBaseStatus = 0U;                     \
          (dst).localTime.nanoseconds = 0U;                        \
          (dst).localTime.seconds = 0U;                            \
          (dst).localTime.secondsHi = 0U;                          \
          (dst).retVal = 0U;                                       \
        } while (0)

#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */


#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)

#if (defined STBM_INIT_SYNCRECORDTABLEBLOCK_0)
#error STBM_INIT_SYNCRECORDTABLEBLOCK_0 is already defined.
#endif
/** \brief Initialize time part of the StbM_SyncRecordTableBlockType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_SyncRecordTableBlockType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_SYNCRECORDTABLEBLOCK_0(dst)                      \
        do                                                         \
        {                                                          \
          (dst).GlbSeconds = 0U;                                   \
          (dst).GlbNanoSeconds = 0U;                               \
          (dst).TimeBaseStatus = 0U;                               \
          (dst).VirtualLocalTimeLow = 0U;                          \
          (dst).RateDeviation = 0U;                                \
          (dst).LocSeconds = 0U;                                   \
          (dst).LocNanoSeconds = 0U;                               \
          (dst).PathDelay = 0U;                                    \
        } while (0)

#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */



#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)

#if (defined STBM_INIT_OFFSETRECORDTABLEBLOCK_0)
#error STBM_INIT_OFFSETRECORDTABLEBLOCK_0 already defined.
#endif
/** \brief Initialize time part of the StbM_OffsetRecordTableBlockType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_OffsetRecordTableBlockType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_OFFSETRECORDTABLEBLOCK_0(dst)                    \
        do                                                         \
        {                                                          \
          (dst).GlbSeconds = 0U;                                   \
          (dst).GlbNanoSeconds = 0U;                               \
          (dst).TimeBaseStatus = 0U;                               \
        } while (0)

#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)

#if (defined STBM_INIT_CANTIMEMASTERMEASUREMENT_0)
#error STBM_INIT_CANTIMEMASTERMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_CanTimeMasterMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_CanTimeMasterMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_CANTIMEMASTERMEASUREMENT_0(dst)                  \
        do                                                         \
        {                                                          \
          (dst).sequenceCounter = 0U;                              \
          (dst).syncEgressTimestamp.nanosecondsLo = 0U;            \
          (dst).syncEgressTimestamp.nanosecondsHi = 0U;            \
          (dst).preciseOriginTimestamp.nanoseconds = 0U;           \
          (dst).preciseOriginTimestamp.seconds = 0U;               \
          (dst).segmentId = STBM_INVALID_SEGMENTID;                \
        } while (0)

#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)

#if (defined STBM_INIT_CANTIMESLAVEMEASUREMENT_0)
#error STBM_INIT_CANTIMESLAVEMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_CanTimeSlaveMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_CanTimeSlaveMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_CANTIMESLAVEMEASUREMENT_0(dst)                   \
        do                                                         \
        {                                                          \
          (dst).sequenceCounter = 0U;                              \
          (dst).syncIngressTimestamp.nanosecondsLo = 0U;           \
          (dst).syncIngressTimestamp.nanosecondsHi = 0U;           \
          (dst).preciseOriginTimestamp.nanoseconds = 0U;           \
          (dst).preciseOriginTimestamp.seconds = 0U;               \
          (dst).referenceLocalTimestamp.nanosecondsLo = 0U;        \
          (dst).referenceLocalTimestamp.nanosecondsHi = 0U;        \
          (dst).referenceGlobalTimestamp.nanoseconds = 0U;         \
          (dst).referenceGlobalTimestamp.seconds = 0U;             \
          (dst).segmentId = STBM_INVALID_SEGMENTID;                \
        } while (0)

#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)

#if (defined STBM_INIT_FRTIMEMASTERMEASUREMENT_0)
#error STBM_INIT_FRTIMEMASTERMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_FrTimeMasterMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_FrTimeMasterMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_FRTIMEMASTERMEASUREMENT_0(dst)                    \
        do                                                          \
        {                                                           \
          (dst).sequenceCounter = 0U;                               \
          (dst).referenceTimestamp.nanosecondsLo = 0U;              \
          (dst).referenceTimestamp.nanosecondsHi = 0U;              \
          (dst).preciseOriginTimestamp.nanoseconds = 0U;            \
          (dst).preciseOriginTimestamp.seconds = 0U;                \
          (dst).segmentId = STBM_INVALID_SEGMENTID;                 \
          (dst).currentCycle = STBM_INVALID_CURRENTCYCLE;           \
          (dst).currentMacroticks = STBM_INVALID_CURRENTMACROTICKS; \
          (dst).macrotickDuration = STBM_INVALID_MACROTICKDURATION; \
          (dst).cycleLength = STBM_INVALID_CYCLELENGTH;             \
        } while (0)

#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)

#if (defined STBM_INIT_FRTIMESLAVEMEASUREMENT_0)
#error STBM_INIT_FRTIMESLAVEMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_FrTimeSlaveMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_FrTimeSlaveMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_FRTIMESLAVEMEASUREMENT_0(dst)                     \
        do                                                          \
        {                                                           \
          (dst).sequenceCounter = 0U;                               \
          (dst).syncIngressTimestamp.nanosecondsLo = 0U;            \
          (dst).syncIngressTimestamp.nanosecondsHi = 0U;            \
          (dst).preciseOriginTimestampSec.nanoseconds = 0U;         \
          (dst).preciseOriginTimestampSec.seconds = 0U;             \
          (dst).currentCycle = STBM_INVALID_CURRENTCYCLE;           \
          (dst).CurrentMacroticks = STBM_INVALID_CURRENTMACROTICKS; \
          (dst).FCNT = 0U;                                          \
          (dst).macrotickDuration = STBM_INVALID_MACROTICKDURATION; \
          (dst).cycleLength = STBM_INVALID_CYCLELENGTH;             \
          (dst).referenceLocalTimestamp.nanosecondsLo = 0U;         \
          (dst).referenceLocalTimestamp.nanosecondsHi = 0U;         \
          (dst).referenceGlobalTimestampSec.nanoseconds = 0U;       \
          (dst).referenceGlobalTimestampSec.seconds = 0U;           \
          (dst).segmentId = STBM_INVALID_SEGMENTID;                 \
        } while (0)

#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */



#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)

#if (defined STBM_INIT_ETHTIMEMASTERMEASUREMENT_0)
#error STBM_INIT_ETHTIMEMASTERMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_EthTimeMasterMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_EthTimeMasterMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_ETHTIMEMASTERMEASUREMENT_0(dst)                  \
        do                                                         \
        {                                                          \
          (dst).sequenceId = 0U;                                   \
          (dst).sourcePortId.clockIdentity = 0U;                   \
          (dst).sourcePortId.portNumber = 0U;                      \
          (dst).syncEgressTimestamp.nanosecondsLo = 0U;            \
          (dst).syncEgressTimestamp.nanosecondsHi = 0U;            \
          (dst).preciseOriginTimestamp.nanoseconds = 0U;           \
          (dst).preciseOriginTimestamp.seconds = 0U;               \
          (dst).correctionField = 0U;                              \
        } while (0)


#if (defined STBM_INIT_ETHTIMESLAVEMEASUREMENT_0)
#error STBM_INIT_ETHTIMESLAVEMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_EthTimeSlaveMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_EthTimeSlaveMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_ETHTIMESLAVEMEASUREMENT_0(dst)                   \
        do                                                         \
        {                                                          \
          (dst).sequenceId = 0U;                                   \
          (dst).sourcePortId.clockIdentity = 0U;                   \
          (dst).sourcePortId.portNumber = 0U;                      \
          (dst).syncIngressTimestamp.nanosecondsLo = 0U;           \
          (dst).syncIngressTimestamp.nanosecondsHi = 0U;           \
          (dst).preciseOriginTimestamp.nanoseconds = 0U;           \
          (dst).preciseOriginTimestamp.seconds = 0U;               \
          (dst).correctionField = 0U;                              \
          (dst).pDelay = 0U;                                       \
          (dst).referenceLocalTimestamp.nanosecondsLo = 0U;        \
          (dst).referenceLocalTimestamp.nanosecondsHi = 0U;        \
          (dst).referenceGlobalTimestamp.nanoseconds = 0U;         \
          (dst).referenceGlobalTimestamp.seconds = 0U;             \
        } while (0)



#if (defined STBM_INIT_PDELAYRESPONDERMEASUREMENT_0)
#error STBM_INIT_PDELAYRESPONDERMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_PdelayResponderMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_PdelayResponderMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_PDELAYRESPONDERMEASUREMENT_0(dst)                \
        do                                                         \
        {                                                          \
          (dst).sequenceId = 0U;                                   \
          (dst).requestPortId.clockIdentity = 0U;                  \
          (dst).requestPortId.portNumber = 0U;                     \
          (dst).responsePortId.clockIdentity = 0U;                 \
          (dst).responsePortId.portNumber = 0U;                    \
          (dst).requestReceiptTimestamp.nanosecondsLo = 0U;        \
          (dst).requestReceiptTimestamp.nanosecondsHi = 0U;        \
          (dst).responseOriginTimestamp.nanosecondsLo = 0U;        \
          (dst).responseOriginTimestamp.nanosecondsHi = 0U;        \
          (dst).referenceLocalTimestamp.nanosecondsLo = 0U;        \
          (dst).referenceLocalTimestamp.nanosecondsHi = 0U;        \
          (dst).referenceGlobalTimestamp.nanoseconds = 0U;         \
          (dst).referenceGlobalTimestamp.seconds = 0U;             \
        } while (0)


#if (defined STBM_INIT_PDELAYINITIATORMEASUREMENT_0)
#error STBM_INIT_PDELAYINITIATORMEASUREMENT_0 already defined.
#endif
/** \brief Initialize time part of the StbM_PdelayInitiatorMeasurementType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_PdelayInitiatorMeasurementType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_PDELAYINITIATORMEASUREMENT_0(dst)                \
        do                                                         \
        {                                                          \
          (dst).sequenceId = 0U;                                   \
          (dst).requestPortId.clockIdentity = 0U;                  \
          (dst).requestPortId.portNumber = 0U;                     \
          (dst).responsePortId.clockIdentity = 0U;                 \
          (dst).responsePortId.portNumber = 0U;                    \
          (dst).requestOriginTimestamp.nanosecondsLo = 0U;         \
          (dst).requestOriginTimestamp.nanosecondsHi = 0U;         \
          (dst).responseReceiptTimestamp.nanosecondsLo = 0U;       \
          (dst).responseReceiptTimestamp.nanosecondsHi = 0U;       \
          (dst).requestReceiptTimestamp.nanoseconds = 0U;          \
          (dst).requestReceiptTimestamp.seconds = 0U;              \
          (dst).responseOriginTimestamp.nanoseconds = 0U;          \
          (dst).responseOriginTimestamp.seconds = 0U;              \
          (dst).referenceLocalTimestamp.nanosecondsLo = 0U;        \
          (dst).referenceLocalTimestamp.nanosecondsHi = 0U;        \
          (dst).referenceGlobalTimestamp.nanoseconds = 0U;         \
          (dst).referenceGlobalTimestamp.seconds = 0U;             \
          (dst).pdelay = 0U;                                       \
        } while (0)

#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */

#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

#if (defined STBM_INIT_SENDCUSTOMERNOTIFICATION_0)
#error STBM_INIT_SENDCUSTOMERNOTIFICATION_0 already defined.
#endif
/** \brief Initialize time part of the StbM_SendCustomerNotificationType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_SendCustomerNotificationType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_SENDCUSTOMERNOTIFICATION_0(dst)                \
        do                                                       \
        {                                                        \
          (dst).timeBaseId = 0U;                                 \
          (dst).customerId = 0U;                                 \
          (dst).calcDeviation = 0U;                              \
        } while (0)


#if (defined STBM_INIT_GPTCALLPAIR_0)
#error STBM_INIT_GPTCALLPAIR_0 already defined.
#endif
/** \brief Initialize time part of the StbM_GptCallPairType
 **
 ** This macro initializes with 0 the time members
 ** of a structure of type StbM_GptCallPairType.
 **
 ** \param[in] dst - Destination struct for assignment
 */
#define STBM_INIT_GPTCALLPAIR_0(dst)                          \
        do                                                    \
        {                                                     \
          (dst).expireTimeDiff.timeBaseStatus = 0U;           \
          (dst).expireTimeDiff.nanoseconds = 0U;              \
          (dst).expireTimeDiff.seconds = 0U;                  \
          (dst).expireTimeDiff.secondsHi = 0U;                \
          (dst).arrayIndex = 0U;                              \
        } while (0)

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */






#if ((STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED ==STD_ON))
#if (defined STBM_CHECK_TIMELEAP_FOR_NOTIFICATION)
#error STBM_CHECK_TIMELEAP_FOR_NOTIFICATION is already defined.
#endif
/** \brief Sets status notification flags for the timeleap feature
 **
 ** This macro checks if a timeleap flag(PAST/FUTURE) needs to be set or
 ** reset in the status notification events variable in order to be later
 ** reported
 **
 ** \param[in] timeLeapFlag - timeleap flag to be checked
 */
#define STBM_CHECK_TIMELEAP_FOR_NOTIFICATION(timeLeapFlag,notificationEvt,notificationEvtRemoved)  \
        do                                                                                         \
        {                                                                                          \
          if(STBM_FLAG_IS_SET(flags, (timeLeapFlag)))                                              \
          {                                                                                        \
            STBM_FLAG_SET(tmpStatusNotification, (notificationEvt));                               \
          }                                                                                        \
          else if(STBM_FLAG_IS_SET(oldTimeleapFlags, (timeLeapFlag)))                              \
          {                                                                                        \
            STBM_FLAG_SET(tmpStatusNotification, (notificationEvtRemoved));                        \
          }                                                                                        \
          else                                                                                     \
          {                                                                                        \
            /* nothing to do */                                                                    \
          }                                                                                        \
        } while (0)

#endif /* (STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED ==STD_ON) */

#if (STBM_TIMEOUTS_USED == STD_ON)

#if (defined STBM_RESTART_TIMEOUT)
#error STBM_RESTART_TIMEOUT is already defined.
#endif
/** \brief Restarts timeout counting for the given time base
 **
 ** This macro restarts the timeout counting for the given time base by
 ** loading the timeout value from configuration. If timeout handling of
 ** a time base is disabled (per configuration) the value stays zero and
 ** timeout handling is not active for this time base.
 ** This macro also reloads an already running timeout counter.
 **
 ** \param[in] id - Id of the time base
 */
#define STBM_RESTART_TIMEOUT(id)                                                  \
        do                                                                        \
        {                                                                         \
          StbM_TimeBaseTimeout[(id)] = StbM_CommonTimeBaseCfg[(id)].timeoutValue; \
        } while (0)

#endif /* STBM_TIMEOUTS_USED == STD_ON */



#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)

#if (defined STBM_RESTART_SHAREDDATA_TIMEOUT)
#error STBM_RESTART_SHAREDDATA_TIMEOUT is already defined.
#endif
/** \brief Restarts timeout counting for the given time base
 **
 ** This macro restarts the timeout counting for the given time base by
 ** loading the timeout value from configuration. If timeout handling of
 ** a time base is disabled (per configuration) the value stays zero and
 ** timeout handling is not active for this time base.
 ** This macro also reloads an already running timeout counter.
 **
 ** \param[in] id - Id of the time base
 */
#define STBM_RESTART_SHAREDDATA_TIMEOUT(id)                                                   \
        do                                                                                    \
        {                                                                                     \
          StbM_SharedDataTimeout[(id)] = StbM_CommonTimeBaseCfg[(id)].sharedDataTimeoutValue; \
        } while (0)

#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


#if (defined STBM_OFFSET_ID_TO_0BASED_INDEX)
#error STBM_OFFSET_ID_TO_0BASED_INDEX is already defined.
#endif
/** \brief Converts offset Id to zero-based config index
 **
 ** This macro takes the given offset timebase id and calculates an index for all
 ** configuration structures used to store information about offset timebases only.
 ** This means the access structure shall have as many elements as the number of
 ** existing offset time bases.
 ** Note:  Accessing this macro with IDs other than an existing offset ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - Offset timebase ID
 */
#define STBM_OFFSET_ID_TO_0BASED_INDEX(id) ( (uint8)(id) - STBM_OFFSET_TIMEBASE_ID_OFFSET )


#if (defined STBM_PURE_ID_TO_0BASED_INDEX)
#error STBM_PURE_ID_TO_0BASED_INDEX is already defined.
#endif /* STBM_PURE_ID_TO_0BASED_INDEX */
/** \brief Converts pure Id to zero-based config index
 **
 ** This macro takes the given pure timebase id and calculates an index for all
 ** configuration structures used to store information about sync and pure timebases only.
 ** This means the access structure shall have as many elements as the number of
 ** existing sync + pure time bases.
 ** Note:  Accessing this macro with IDs other than an existing sync or pure ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - Pure timebase ID
 */
#define STBM_PURE_ID_TO_0BASED_INDEX(id) ( STBM_NUMBER_OF_SYNC_TIMEBASES \
                                           + STBM_NUMBER_OF_OFFSET_TIMEBASES \
                                           + ((uint8)(id) - STBM_MIN_ALLOWED_PURE_TIMEBASE_ID) \
                                         )

#if (defined STBM_OFFSET_ID_TO_COMMON_INDEX)
#error STBM_OFFSET_ID_TO_COMMON_INDEX is already defined.
#endif
/** \brief Converts offset Id to common config index
 **
 ** This macro takes the given offset timebase id and calculates an index for all
 ** configuration structures used to store information about all timebases
 ** (offset and Synchronized).
 ** This means the access structure shall have as many elements as the number of
 ** existing offset time bases plus the number of existing synchronized time bases.
 ** Note:  Accessing this macro with IDs other than an existing offset ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - Offset timebase ID
 */
#define STBM_OFFSET_ID_TO_COMMON_INDEX(id) ( STBM_OFFSET_ID_TO_0BASED_INDEX((id)) \
                                             + STBM_NUMBER_OF_SYNC_TIMEBASES      \
                                           )


#if (defined STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX)
#error STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX is already defined.
#endif /* STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX */
/** \brief Converts sync or pure Id to common config index
 **
 ** This macro takes the given sync or pure timebase id and calculates an index for all
 ** configuration structures used to store information about all timebases
 ** (synchronized, offset and pure).
 ** This means the access structure shall have as many elements as the number of
 ** existing offset time bases plus the number of existing synchronized time bases
 ** plus the number of existing pure time bases.
 ** Note:  Accessing this macro with IDs other than an existing sync or pure ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - Sync or Pure timebase ID
 */
#if(STBM_NUMBER_OF_PURE_TIMEBASES > 0U)
#define STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX(id) ( (STBM_IS_PURE_TIMEBASE_ID((id)))          \
                                                   ? (STBM_PURE_ID_TO_0BASED_INDEX((id)))  \
                                                   : ((uint8)(id))                         \
                                                 )
#else
#define STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX(id) ((uint8)(id))
#endif


#if (defined STBM_TIMEBASE_ID_IS_OFFSET)
#error STBM_TIMEBASE_ID_IS_OFFSET is already defined.
#endif
/** \brief Checks for an offset timebase id
 **
 ** This macro checks if the given Id is not a Synchronized or a Pure time base Id
 ** It evaluates to 'TRUE' if the given Id is an offset Id. (id >= 16 && id < 32)
 ** Note:  This macro does not evaluate if the Id is out of range.
 **
 ** \param[in] id - timebase ID (any - sync or offset)
 */
#if(STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_TIMEBASE_ID_IS_OFFSET(id) ( ((id) >= STBM_OFFSET_TIMEBASE_ID_OFFSET) && ((id) < STBM_MIN_ALLOWED_PURE_TIMEBASE_ID) )
#else /* (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U) */
#define STBM_TIMEBASE_ID_IS_OFFSET(id) (boolean)FALSE
#endif /* (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U) */

#if (defined STBM_GET_SYNC_TIMEBASE_INDEX_FROM_ZERO_BASED_OFFSET)
#error STBM_GET_SYNC_TIMEBASE_INDEX_FROM_ZERO_BASED_OFFSET is already defined.
#endif
/** \brief Gets the related synchronized time base index
 **
 ** This macro takes an offset time base id and converts it into the configuration index
 ** of the underlying synchronized time base.
 ** Note:  Accessing this macro with IDs other than an existing offset ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - zero based offset(!) timebase ID
 */
#if (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_GET_SYNC_TIMEBASE_INDEX_FROM_ZERO_BASED_OFFSET(id)                    \
        StbM_OffsetTimeBaseCfg[(id)].syncTimeBaseIndex
#else /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */
#define STBM_GET_SYNC_TIMEBASE_INDEX_FROM_ZERO_BASED_OFFSET(id) (0U)
#endif /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */


#if (defined STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET)
#error STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET is already defined.
#endif
/** \brief Gets the related synchronized time base index
 **
 ** This macro takes an offset time base id and converts it into the configuration index
 ** of the underlying synchronized time base.
 ** Note:  Accessing this macro with IDs other than an existing offset ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - offset(!) timebase ID
 */
#if (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET(id)                    \
        StbM_OffsetTimeBaseCfg[STBM_OFFSET_ID_TO_0BASED_INDEX((id))].syncTimeBaseIndex
#else /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */
#define STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET(id) (0U)
#endif /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */



#if (defined STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE)
#error STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE is already defined.
#endif /* STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE */
/** \brief Gets the related synchronized time base index
 **
 ** This macro takes a sync or pure time base id and converts it into the configuration index
 ** of the synchronized time bases.
 ** Note:  Accessing this macro with IDs other than an existing sync or pure ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - sync or pure(!) timebase ID
 */
#define STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE(id)         \
        (                                                          \
          STBM_IS_PURE_TIMEBASE_ID(id)                             \
          ? (STBM_PURE_ID_TO_0BASED_INDEX(id))                     \
          : ((uint8)(id))                                          \
        )


#if (defined STBM_GET_SYNC_TIMEBASE_INDEX)
#error STBM_GET_SYNC_TIMEBASE_INDEX is already defined.
#endif
/** \brief Gets the related synchronized time base index
 **
 ** This macro takes any time base id and converts it into the configuration index
 ** of the underlying synchronized time base.
 ** (in case the Id refers to a sync time base the own index is calculated)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync, offset or pure)
 */

#if (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_GET_SYNC_TIMEBASE_INDEX(id)                         \
        (                                                        \
          STBM_TIMEBASE_ID_IS_OFFSET((id))                       \
          ? STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET((id))       \
          : STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE((id)) \
        )
#else /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */
#define STBM_GET_SYNC_TIMEBASE_INDEX(id) (STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE((id)))
#endif /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */


#if (defined STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX)
#error STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX is already defined.
#endif
/** \brief Gets the related synchronized time base index
 **
 ** This macro takes any time base id and converts it into the configuration index
 ** of the underlying synchronized time base.
 ** (in case the Id refers to a sync time base the own index is calculated)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync, offset or pure)
 */

#if (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX(id)                  \
        (                                                            \
          STBM_TIMEBASE_ID_IS_OFFSET((id))                           \
          ? STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET((id))           \
          : ((uint8)(id))                                            \
        )
#else /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */
#define STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX(id) ((uint8)(id))
#endif /* STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U */


#if (defined STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX)
#error STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX is already defined.
#endif
/** \brief Gets the related related time base index in the StbM_SlaveRateCorrectionData[] array
 ** from a time base configuration
 **
 ** This macro takes a time base id and converts it into the index of the
 ** StbM_SlaveRateCorrectionData[] array.
 ** Note:  Accessing this macro with IDs other than an existing offset ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - common(!) timebase ID
 */
#define STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonId)            \
        StbM_CommonTimeBaseCfg[(commonId)].intervalArrayIndex

#if (defined STBM_GET_SLAVE_RATEDATA_TO_COMMON_TIMEBASE_INDEX)
#error STBM_GET_SLAVE_RATEDATA_TO_COMMON_TIMEBASE_INDEX is already defined.
#endif
/** \brief Gets the related time base index in the StbM_SlaveRateCorrectionData[] array
 **
 ** This macro takes any time base id and converts it into the StbM_SlaveRateCorrectionData[]
 ** index of the time base.
 ** (id will be translated to a common index)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - timebase ID (any - sync or offset)
 */
#define STBM_GET_SLAVE_RATEDATA_TO_COMMON_TIMEBASE_INDEX(id) (STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX((id)))

#if (defined STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX)
#error STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX is already defined.
#endif
/** \brief Gets the related time base index in the StbM_MasterRateCorrectionData[] array
 **
 ** This macro takes any time base id and converts it into the StbM_MasterRateCorrectionData[]
 ** index of the time base.
 ** (the id will be translated to a common index)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - timebase ID (any - sync or offset)
 */
#define STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonId)            \
        StbM_CommonTimeBaseCfg[(commonId)].masterRcArrayIndex

#if (defined STBM_SLAVE_OR_MASTER_RATE_CORRECTION_DISABLED)
#error STBM_SLAVE_OR_MASTER_RATE_CORRECTION_DISABLED is already defined.
#endif
/** \brief Checks if rate correction is used
 **
 ** This macro checks if slave or master rate correction
 ** is used for a given sync or offset time base.
 ** It evaluates to 'TRUE' if the treshold is disabled.
 **
 ** \param[in] id - Id of time base
 */
#if ((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) && (STBM_MASTER_RATE_CORRECTION_USED == STD_ON))
#define STBM_SLAVE_OR_MASTER_RATE_CORRECTION_DISABLED(id)                           \
        (                                                                           \
              (!STBM_SLAVE_RATE_CORRECTION_TO_COMMON_DISABLED(id))                  \
           || (!STBM_MASTER_RATE_CORRECTION_TO_COMMON_DISABLED(id))                 \
        )
#elif (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
#define STBM_SLAVE_OR_MASTER_RATE_CORRECTION_DISABLED(id)                           \
        (                                                                           \
              (!STBM_SLAVE_RATE_CORRECTION_TO_COMMON_DISABLED(id))                  \
        )
#else
#define STBM_SLAVE_OR_MASTER_RATE_CORRECTION_DISABLED(id)                           \
        (                                                                           \
              (!STBM_MASTER_RATE_CORRECTION_TO_COMMON_DISABLED(id))                 \
        )
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) && (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */

#if (defined STBM_GET_MASTER_RATE_DEVIATION_MAX)
#error STBM_GET_MASTER_RATE_DEVIATION_MAX is already defined.
#endif
/** \brief Gets the related time base StbMMasterRateDeviationMax value
 **
 ** This macro takes any common time base id and converts it into the
 ** related StbMMasterRateDeviationMax value.
 ** (a common index will be received)
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] commonId - common timebase ID index
 */
#define STBM_GET_MASTER_RATE_DEVIATION_MAX(commonId)              \
        StbM_CommonTimeBaseCfg[(commonId)].masterRateDeviationMax

#if (defined STBM_GET_NOTIFICATION_MASK)
#error STBM_GET_NOTIFICATION_MASK is already defined.
#endif
/** \brief Gets the related StbMStatusNotificationMask value from
 ** from a time base configuration
 **
 ** This macro takes a time base id and converts it into the
 ** related StbMStatusNotificationMask value
 ** Note:  Accessing this macro with IDs other than an existing common ID leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - common(!) timebase ID
 */
#define STBM_GET_NOTIFICATION_MASK(id)                        \
        StbM_CommonTimeBaseCfg[(id)].statusNotificationMask

#if (defined STBM_TIMEBASE_ID_TO_COMMON_INDEX)
#error STBM_TIMEBASE_ID_TO_COMMON_INDEX is already defined.
#endif
/** \brief Converts any timebase Id to common config index
 **
 ** This macro takes the given (synchronized, offset or pure) timebase id and calculates
 ** an index for all configuration structures used to store information about all timebases
 ** (synchronized, offset and pure).
 ** This means the access structure shall have as many elements as the number of
 ** existing offset time bases plus the number of existing synchronized time bases,
 ** plus the number of existing pure time bases.
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - Any timebase ID (sync, offset, pure)
 */
#if (STBM_NUMBER_OF_PURE_TIMEBASES > 0U)

#if (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_TIMEBASE_ID_TO_COMMON_INDEX(id)                                               \
        (                                                                                  \
          STBM_TIMEBASE_ID_IS_OFFSET((id))                                                 \
          ? STBM_OFFSET_ID_TO_COMMON_INDEX(id)                                             \
          : STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX(id)                                       \
        )
#else
#define STBM_TIMEBASE_ID_TO_COMMON_INDEX(id)  (STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX(id))
#endif

#else /* (STBM_NUMBER_OF_PURE_TIMEBASES > 0U) */

#if (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)
#define STBM_TIMEBASE_ID_TO_COMMON_INDEX(id)                                               \
        (                                                                                  \
          STBM_TIMEBASE_ID_IS_OFFSET((id))                                                 \
          ? STBM_OFFSET_ID_TO_COMMON_INDEX(id)                                             \
          : ((uint8)(id))                                                                  \
        )
#else
#define STBM_TIMEBASE_ID_TO_COMMON_INDEX(id)  ((uint8)(id))
#endif

#endif /* (STBM_NUMBER_OF_PURE_TIMEBASES > 0U) */



#if (defined STBM_SYNC_OFFSET_TIMEBASE_ID_TO_COMMON_INDEX)
#error STBM_SYNC_OFFSET_TIMEBASE_ID_TO_COMMON_INDEX is already defined.
#endif /* STBM_SYNC_OFFSET_TIMEBASE_ID_TO_COMMON_INDEX */
/** \brief Converts a sync of offset Id to common config index
 **
 ** This macro takes the given (synchronized, offset) timebase id and calculates
 ** an index for all configuration structures used to store information about all timebases
 ** (synchronized, offset).
 ** This means the access structure shall have as many elements as the number of
 ** existing offset time bases plus the number of existing synchronized time bases.
 ** Note:  Accessing this macro with IDs other than an existing ID (of any type) leads
 **        to out-of-bounds access!
 **
 ** \param[in] id - Any timebase ID (sync, offset)
 */
#define STBM_SYNC_OFFSET_TIMEBASE_ID_TO_COMMON_INDEX(id)                                   \
        (                                                                                  \
          STBM_TIMEBASE_ID_IS_OFFSET((id))                                                 \
          ? STBM_OFFSET_ID_TO_COMMON_INDEX(id)                                             \
          : ((uint8)(id))                                                                  \
        )



#if (defined STBM_IS_SLAVE_PORT_CONNECTED)
#error STBM_IS_SLAVE_PORT_CONNECTED is already defined.
#endif
/** \brief Checks if time base has a slave port
 **
 ** This macro checks if the given time base has a connected time domain configured
 ** as time slave.
 ** This is the case when a time base has the role of a time slave or time gateway.
 **
 ** \param[in] id - Any timebase ID
 */
#define STBM_IS_SLAVE_PORT_CONNECTED(id)                                                   \
        (                                                                                  \
          StbM_SyncTimeBaseCfg[STBM_GET_SYNC_TIMEBASE_INDEX(id)].role != STBM_ROLE_MASTER  \
        )


#if (defined STBM_ONLY_MASTER_PORT_CONNECTED)
#error STBM_ONLY_MASTER_PORT_CONNECTED is already defined.
#endif
/** \brief Checks if time base has only a master port connected
 **
 ** This macro checks if the given time base has a connected time domain configured
 ** as time master.
 ** This is the case when a time base has the role of a time master.
 **
 ** \param[in] id - Any timebase ID
 */
#define STBM_ONLY_MASTER_PORT_CONNECTED(id)                                                   \
        (                                                                                   \
          StbM_SyncTimeBaseCfg[STBM_GET_SYNC_TIMEBASE_INDEX(id)].role == STBM_ROLE_MASTER   \
        )

#if (defined STBM_ONLY_SLAVE_PORT_CONNECTED)
#error STBM_ONLY_SLAVE_PORT_CONNECTED is already defined.
#endif
/** \brief Checks if time base has only a slave port connected
 **
 ** This macro checks if the given time base has a connected time domain configured
 ** as time slave.
 ** This is the case when a time base has the role of a time slave.
 **
 ** \param[in] id - Any timebase ID
 */
#define STBM_ONLY_SLAVE_PORT_CONNECTED(id)                                                   \
        (                                                                                  \
          StbM_SyncTimeBaseCfg[STBM_GET_SYNC_TIMEBASE_INDEX(id)].role == STBM_ROLE_SLAVE   \
        )


#if ((STBM_SETBUSPROTOCOLPARAM_ACTIVE == STD_ON) || (STBM_GETBUSPROTOCOLPARAM_ACTIVE == STD_ON))
#if (defined STBM_IS_TIMEBASE_CONNECTED_TO_ETHTSYN_TIMEDOMAIN)
#error STBM_IS_TIMEBASE_CONNECTED_TO_ETHTSYN_TIMEDOMAIN is already defined.
#endif
/** \brief Checks if time base is connected to a EthTSyn time domain
 **
 ** This macro checks if the given time base has a EthTSyn time domain connected
 **
 ** \param[in] id - SYNC timebase ID
 */
#define STBM_IS_TIMEBASE_CONNECTED_TO_ETHTSYN_TIMEDOMAIN(id)                                                          \
        (                                                                                                             \
          StbM_SyncTimeBaseCfg[id].isTimeBaseLinkedToEthTSynTimeDomain == STBM_TIMEBASE_LINKED_TO_ETHTSYN_TIMEDOMAIN  \
        )
#endif /* ((STBM_SETBUSPROTOCOLPARAM_ACTIVE == STD_ON) || (STBM_GETBUSPROTOCOLPARAM_ACTIVE == STD_ON)) */



#if (defined STBM_UINT32_TO_Q)
#error STBM_UINT32_TO_Q is already defined.
#endif
/** \brief Converts number from uint32 to Q
 **
 ** This macro converts number from uint32 to Q
 **
 ** \param[in] id - number to convert
 */
#define STBM_UINT32_TO_Q(x) ((x) * STBM_FACTOR_Q)

#if (defined STBM_UINT64_TO_Q)
#error STBM_UINT64_TO_Q is already defined.
#endif
/** \brief Converts number from uint64 to Q
 **
 ** This macro converts number from uint64 to Q
 **
 ** \param[in] id - number to convert
 */
#define STBM_UINT64_TO_Q(x) StbM_Umul32_64((x), STBM_FACTOR_Q)

#if (defined STBM_NSECS_TO_SECS)
#error STBM_NSECS_TO_SECS is already defined.
#endif
/** \brief Converts nanoseconds to seconds
 **
 ** This macro converts nanoseconds to seconds
 **
 ** \param[in] id - number to convert
 */
#define STBM_NSECS_TO_SECS(x) StbM_Udiv64_32((x), STBM_NSECS_PER_SEC)

#if (defined STBM_SECS_TO_NSECS)
#error STBM_SECS_TO_NSECS is already defined.
#endif
/** \brief Converts seconds to nanoseconds
 **
 ** This macro converts  seconds to nanoseconds
 **
 ** \param[in] id - number to convert
 */
#define STBM_SECS_TO_NSECS(x) StbM_Umul32_64((x), STBM_NSECS_PER_SEC)

#if (defined STBM_NR_FROM_PPM)
#error STBM_NR_FROM_PPM is already defined.
#endif
/** \brief Converts from ppm to number
 **
 ** This macro converts from ppm to number
 **
 ** \param[in] id - number to convert
 */
#define STBM_NR_FROM_PPM(x) StbM_Udiv64_32((x), STBM_FACTOR_PPM)

#if (defined STBM_UINT64_TO_PPM)
#error STBM_StbM_UINT64_TO_PPM is already defined.
#endif
/** \brief Converts uint64 number to ppm
 **
 ** This macro converts uint64 number to ppm
 **
 ** \param[in] id - number to convert
 */
#define STBM_UINT64_TO_PPM(x) StbM_Umul32_64((x), STBM_FACTOR_PPM)

#if (defined STBM_UINT64_TO_BETTER_PRECISION)
#error STBM_UINT64_TO_BETTER_PRECISION is already defined.
#endif
/** \brief Converts uint64 number to ppm
 **
 ** This macro converts uint64 number to ppm
 **
 ** \param[in] id - number to convert
 */
#define STBM_UINT64_TO_BETTER_PRECISION(x) StbM_Umul32_64((x), STBM_FACTOR_MORE_PRECISION)

#if (defined STBM_Q_TO_UINT32)
#error STBM_Q_TO_UINT32 is already defined.
#endif
/** \brief Converts Q number to uint32
 **
 ** This macro converts Q number to uint32
 **
 ** \param[in] id - number to convert
 */
#define STBM_Q_TO_UINT32(x) ((x) / STBM_FACTOR_Q)

#if (defined STBM_Q_TO_UINT64)
#error STBM_Q_TO_UINT64 is already defined.
#endif
/** \brief Converts Q number to uint64
 **
 ** This macro converts Q number to uint64
 **
 ** \param[in] id - number to convert
 */
#define STBM_Q_TO_UINT64(x) StbM_Udiv64_32((x), STBM_FACTOR_Q)

#if (defined STBM_RATE_DEVIATION_UNSIGNED)
#error STBM_RATE_DEVIATION_UNSIGNED is already defined.
#endif
/** \brief Get rate deviation as unsigned
 **
 ** This macro substracts 1 in ppm(1.000.000) from the
 ** rate correction to obtain the rate deviation but positive
 **
 ** \param[in] id - rate correction
 */
#define STBM_RATE_DEVIATION_UNSIGNED(rrc_ppm)                          \
             (                                                         \
               ((rrc_ppm) > (uint32)STBM_FACTOR_PPM)                   \
               ? ((rrc_ppm) - (uint32)STBM_FACTOR_PPM)                 \
               : ((uint32)STBM_FACTOR_PPM - (rrc_ppm))                 \
             )

#if (defined STBM_RATE_CORRECTION_USED)
#error STBM_RATE_CORRECTION_USED already defined!
#endif /* #if (defined STBM_RATE_CORRECTION_USED)*/
/** \brief Check if Rate Correction enabled(slave or master) */
#define STBM_RATE_CORRECTION_USED \
((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_MASTER_RATE_CORRECTION_USED == STD_ON))

#if (defined STBM_TIMESTAMP_MODIFIED)
#error STBM_TIMESTAMP_MODIFIED already defined
#endif /* #if (defined STBM_TIMESTAMP_MODIFIED) */
/** \brief This macro notifies NvM module each time a TimeStamp was changed */
#if (STBM_NVM_USED == STD_ON)
#define STBM_TIMESTAMP_MODIFIED(commonId)                                    \
        ((void) NvM_SetRamBlockStatus(STBM_GET_NVM_BLOCK_ID(commonId), TRUE))
#endif /* (STBM_NVM_USED == STD_ON) */

#if(STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

#if (defined STBM_ISLISTEMPTY)
#error STBM_ISLISTEMPTY is already defined.
#endif
/** \brief Checks if timestamp is zero
 **
 ** This macro checks if all the values in a timestamp
 ** are zero.
 ** It evaluates to 'TRUE' if the timestamp is zero.
 **
 ** \param[in] timestamp - the evaluated timestamp
 */
#define STBM_ISLISTEMPTY()       (Head == NULL_PTR)


#if (defined STBM_IS_DATA_FROM_NODES_EQUAL)
#error STBM_IS_DATA_FROM_NODES_EQUAL is already defined.
#endif
/** \brief Checks if 2 expiry points are equal or not
 **
 ** This macro cheks if expiryPoint1 is equal with expiryPoint2 (timeBaseId, customerId, nanoseconds, seconds and secondsHi)
 **
 ** \param[in] expiryPoint1 - First time stamp
 ** \param[in] expiryPoint2 - Second time stamp
 */
#define STBM_IS_DATA_FROM_NODES_EQUAL(expiryPoint1,expiryPoint2)                                              \
  ((expiryPoint1->timeBaseId == expiryPoint2.timeBaseId) &&                                                   \
   (expiryPoint1->customerId == expiryPoint2.customerId) &&                                                   \
   (expiryPoint1->customerTimerExpireTime.seconds == expiryPoint2.customerTimerExpireTime.seconds) &&         \
   (expiryPoint1->customerTimerExpireTime.nanoseconds == expiryPoint2.customerTimerExpireTime.nanoseconds) && \
   (expiryPoint1->customerTimerExpireTime.secondsHi == expiryPoint2.customerTimerExpireTime.secondsHi))

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */


/*==[Types]===================================================================*/

#if ((STBM_OS_COUNTER_USED == STD_ON) || (STBM_GPT_USED == STD_ON) || (STBM_OSGETTIMESTAMP_USED == STD_ON))
/** \brief Virtual Local Time Stamps config
 **
 ** This type contains all the Virtual Local Time sources
 ** of synchronized time bases
 */
typedef struct
{
#if (STBM_GPT_USED == STD_ON)
  VAR(StbM_VirtualLocalTimeType, STBM_VAR) StbM_VirtualLocalTime_Gpt[STBM_NUMBER_OF_GPT_TIMEBASES];  /**< Virtual Local Time of StbM based on Gpt */
  VAR(Gpt_ValueType, STBM_VAR) StbM_PreviousGptTicks[STBM_NUMBER_OF_GPT_TIMEBASES];  /**< Variable used to store the previous Gpt tick value */
#endif /* STBM_GPT_USED == STD_ON */
#if (STBM_OS_COUNTER_USED == STD_ON)
  VAR(StbM_VirtualLocalTimeType, STBM_VAR) StbM_VirtualLocalTime_OsCounter;  /**< Virtual Local Time of StbM, based on Os Counter */
  VAR(TickType, STBM_VAR) StbM_PreviousOsTicks_OsCounter;  /**< Variable used to store the previous Os counter tick value */
#endif /* STBM_OS_COUNTER_USED == STD_ON */
#if (STBM_OSGETTIMESTAMP_USED == STD_ON)
  VAR(StbM_VirtualLocalTimeType, STBM_VAR) StbM_VirtualLocalTime_OSGetTimeStamp;  /**< Virtual Local Time of StbM, taken through OSGetTimeStamp API */
  VAR(os_timestamp_t, STBM_VAR) StbM_PreviousOsTicks_OSGetTimeStamp;  /**< Variable used to store the previous Os tick value, which was retrieved through OSGetTimeStamp API */
#endif /* STBM_OSGETTIMESTAMP_USED == STD_ON */
} StbM_VirtualLocalTimeSourcesType;
#endif /* ((STBM_OS_COUNTER_USED == STD_ON) || (STBM_GPT_USED == STD_ON) || (STBM_OSGETTIMESTAMP_USED == STD_ON)) */

/*==[Declaration of functions with internal linkage]==========================*/

#define STBM_START_SEC_CODE
#include <StbM_MemMap.h>


/** \brief Calculates the actual time of the synchronized time base and updates it
 **
 ** This function calculates the actual time for a synchronized time base.
 ** Dependent on the configuration the time provider is the EthTSyn, Gpt or the Os module.
 **
 ** \param[in] syncTimeBaseIndex - Id (=index) of the synchronized time base
 ** \param[out] timeStampPtr - actual obtained time
 */
STATIC FUNC(void, STBM_CODE) StbM_CalculateLocalTimeAndUpdate
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
);

#if ( STBM_SOURCE_TIMEBASES_USED == STD_ON)
/** \brief clones Copies Time Base data from the souce to the destination
 **
 ** This function clones Copies Time Base data from Source Time Base to Destination Time Base.
 ** Dependent on the configuration StbMSourceTimeBase.
 **
 ** \param[in] srcIndex - Id (=index) of the synchronized source time base
 ** \param[in] destIndex - Id (=index) of the synchronized destination time base
 ** \param[in] cloneCfg - Refines how source Time Base is cloned to destination
 */
STATIC FUNC(Std_ReturnType, STBM_CODE)  StbM_CloneTimeBase_Internal(uint8 srcIndex, uint8 destIndex, StbM_CloneConfigType cloneCfg );

/** \brief clones Copies Time Base data from the souce to the destination
 **
 ** This function clones Copies Time Base data from source time base to destination time base for
 ** update counter and rate correction.
 ** Dependent on the configuration StbMSourceTimeBase.
 **
 ** \param[in] srcIndex - Id (=index) of the synchronized source time base
 ** \param[in] destIndex - Id (=index) of the synchronized destination time base
 ** \param[in] cloneCfg - Refines how source Time Base is cloned to destination
 */
STATIC FUNC(Std_ReturnType, STBM_CODE)  StbM_Clone_Internal_Update_Counter_Rate(uint8 srcIndex, uint8 destIndex, StbM_CloneConfigType cloneCfg );

/** \brief Check if pendding request exist when StbM_BusSetGlobalTime() is called.
 **
 ** This function checks if pendding request exist when StbM_BusSetGlobalTime() is called.
 ** Dependent on the configuration StbMSourceTimeBase.
 **
 ** \param[in] srcIndex - Id (=index) of the synchronized source time base
 */
STATIC FUNC(void, STBM_CODE)  StbM_Check_Pending_Clone_Request(uint8 srcIndex);

/** \brief Check if pendding request exist when timeout happens in StbM_Mainfunction().
 **
 ** This function checks if pendding request exist when timeout happens in StbM_Mainfunction().
 ** Dependent on the configuration StbMSourceTimeBase.
 **
 ** \param[in] srcIndex - Id (=index) of the synchronized source time base
 */
#if (STBM_TIMEOUTS_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Check_Pending_Clone_When_Timeout(uint8 srcIndex);
#endif /* (STBM_TIMEOUTS_USED == STD_ON) */
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */

#if ((STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) || (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON))
/** \brief Calculate the actual time of the synchronized time base
 **
 ** This function calculates the actual time for a synchronized time base.
 ** Dependent on the configuration the time provider is the EthTSyn or the Os module.
 **
 ** \param[in] syncTimeBaseIndex - Id (=index) of the synchronized time base
 ** \param[out] timeStampPtr - actual obtained time
 **
 ** \return if the time base was successfully updated
 ** \retval E_OK update successful
 ** \retval E_NOT_OK update failed
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateLocalTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
);
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) || (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON) */

/** \brief Get time
 **
 ** This function calls the time getter function from configuration and
 ** return the time and sync status.
 **
 ** \param[in] syncTimeBaseIndex - Id (=index) of the synchronized time base
 ** \param[out] timeStampPtr - actual obtained time
 ** \param[in] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[in] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 ** \param[in] localTimePtr - current local time
 **
 ** \return if the time base was successfully obtained
 ** \retval E_OK successful
 ** \retval E_NOT_OK failed
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
);

/** \brief Get time Sub
 **
 ** Function to obtain time.
 **
 ** \param[in] syncTimeBaseIndex - Id (=index) of the synchronized time base
 ** \param[in] timeStampPtr - actual obtained time
 ** \param[in] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[in] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 ** \param[in] localTimePtr - current local time
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeSub
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
);

/** \brief Get current time (either normal timeStamp or extended timeStamp)
 **
 ** This function gets the current time stamp (either normal or extended)
 **
 ** \param[in]  timeBaseId - Id of the time base
 ** \param[out] timeStamp - actual obtained time
 ** \param[out] userData - set user data
 **
 ** \return if the time base was successfully obtained
 ** \retval E_OK successful
 ** \retval E_NOT_OK failed
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeCommon
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
);


/** \brief Set global time base
 **
 ** This function set the global time of all connected time domains
 ** derived from a given sync time base
 **
 ** \param[in] syncTimeBaseIndex - Id (=index) of the synchronized time base
 ** \param[in] timeStampPtr - Time stamp containing the current time.
 **
 ** \return if the time base was successfully updated
 ** \retval E_OK time of all connected time domains set with success
 ** \retval E_NOT_OK setting the time of one or more time domains failed
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTimeBase
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);

/** \brief Internal set global time function
 **
 ** Sets a new global time that has to be valid for the system.
 ** Origin is some Software component (master) or a <Bus>TSyn module (slave).
 ** Note: The behavior of the function differs dependent on the timeBaseId.
 **
 ** If the timeBaseId is a Id pointing to a synchronized time base, the timestamp
 ** value given by timeStampPtr overwrites the old value.
 **
 ** If the timeBaseId is a Id pointing to an offset time base, the underlying
 ** synchronized time base is not overwritten. Instead the difference between the
 ** timestamp given by timeStampPtr and the current time of the synchronized time base
 ** is stored for this offset time base.
 ** This avoids jumps in time, but allows to restore the absolute value (which is
 ** the timestamp of the sync time base plus the timestamp of the offset time base.
 **
 **
 ** \param[in] timeBaseId - ID of the time-base (any).
 ** \param[in] timeStampPtr - Time stamp containing the current time.
 ** \param[in] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[in] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 ** \param[in] checkGlobalTimeBit - this parameter will be TRUE for calls comming
 ** from StbM_SetGlobalTime() and StbM_UpdateGlobalTime so the check for the
 ** GLOBAL_TIME_BIT for offset can be done. And it will be FALSE for calls
 ** comming from StbM_BusSetGlobalTime() because the check should not be
 ** performed for slave time bases.
 **
 ** \return the success/failure of the function call
 ** \retval E_OK In case of successful call of the function.
 ** \retval E_NOT_OK In case of unsuccessful call of the function.
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTimeInternal
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr,
  boolean checkGlobalTimeBit
);

/** \brief Calculates sum of timestamps
 **
 ** This function calculates and returns the sum of two timestamps.
 ** The secondHi part of the time stamp must not overflow.
 **
 ** \param[in] timeStampAugendPtr - Points to the first timestamp to summarize
 ** \param[in] timeStampAddendPtr - Points to the second timestamp to summarize
 ** \param[out] timeStampSumPtr - Points to the memory location where the sum of the
 **                               timestamps shall be stored
 **
 ** \return Status of sum operation
 ** \retval E_OK operation successful
 ** \retval E_NOT_OK operation failed - overflow in value range
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SumTimeStamps
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampAugendPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampAddendPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampSumPtr
);

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopySyncMeasurementDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_VAR) syncRecordTableBlocks
);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyOffsetMeasurementDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_VAR) offsetRecordTableBlocks
);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
/** \brief Send Sync Measurement Data to user, block by block
 **
 ** This function sends available measurement data to user, block by block.
 */
STATIC FUNC(void, STBM_CODE) StbM_SendSyncMeasurementDataBlockByBlock
(
  uint8 timeBaseIdx,
  boolean isCallbackConfigured,
  uint32 blockStartIdx,
  uint32 blockStopIdx,
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_VAR) syncRecordTableBlocks
);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
/** \brief Send Offset Measurement Data to user, block by block
 **
 ** This function sends available measurement data to user, block by block.
 */
STATIC FUNC(void, STBM_CODE) StbM_SendOffsetMeasurementDataBlockByBlock
(
  uint8 timeBaseIdx,
  boolean isCallbackConfigured,
  uint32 blockStartIdx,
  uint32 blockStopIdx,
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_VAR) offsetRecordTableBlocks
);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */



/** \brief Check if new measurement data is available and send it to user
 **
 ** This function checks if new measurement data was written in the time recording table
 ** and if there was indeed new data, sends it to the user
 */
STATIC FUNC(void, STBM_CODE) StbM_CheckIfNewMeasurementDataIsAvailableAndSend
(
  boolean isSyncTimeBase,
  uint8 timeBaseIndex
);

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
/** \brief Send Sync Measurement Data to user
 **
 ** This function sends available sync measurement data to user.
 */
STATIC FUNC(void, STBM_CODE) StbM_SendSyncMeasurementData
(
  void
);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
/** \brief Send Offset Measurement Data to user
 **
 ** This function sends available offset measurement data to user.
 */
STATIC FUNC(void, STBM_CODE) StbM_SendOffsetMeasurementData
(
  void
);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


/** \brief Send Measurement Data to user
 **
 ** This function sends available measurement data to user.
 */
STATIC FUNC(void, STBM_CODE) StbM_SendMeasurementData
(
  void
);

#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */



#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)


#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON))

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyCanTSynMasterTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_CanTimeMasterMeasurementType, AUTOMATIC, STBM_VAR) cantsynMasterTimingDataBlocks
);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyCanTSynSlaveTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_CanTimeSlaveMeasurementType, AUTOMATIC, STBM_VAR) cantsynSlaveTimingDataBlocks
);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */

#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)) */



#if ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON))

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyFrTSynMasterTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_FrTimeMasterMeasurementType, AUTOMATIC, STBM_VAR) frtsynMasterTimingDataBlocks
);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyFrTSynSlaveTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_FrTimeSlaveMeasurementType, AUTOMATIC, STBM_VAR) frtsynSlaveTimingDataBlocks
);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */

#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)) */



#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynMasterTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_EthTimeMasterMeasurementType, AUTOMATIC, STBM_VAR) ethtsynMasterTimingDataBlocks
);

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynSlaveTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_EthTimeSlaveMeasurementType, AUTOMATIC, STBM_VAR) ethtsynSlaveTimingDataBlocks
);

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynPdelayResponderTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_PdelayResponderMeasurementType, AUTOMATIC, STBM_VAR) ethtsynPdelayResponderTimingDataBlocks
);

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynPdelayInitiatorTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_PdelayInitiatorMeasurementType, AUTOMATIC, STBM_VAR) ethtsynPdelayInitiatorTimingDataBlocks
);

#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */




#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON))

STATIC FUNC(void, STBM_CODE) StbM_SendCanTSynTimingData(void);

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
/** \brief Send CANTSYN MASTER Timing Data
 **
 ** This function sends CanTSyn master timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendCanTSynMasterTimingData
(
  uint8 timeBaseIndex
);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
/** \brief Send CANTSYN SLAVE Timing Data
 **
 ** This function sends CanTSyn slave timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendCanTSynSlaveTimingData
(
  uint8 timeBaseIndex
);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */

#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)) */



#if ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON))
/** \brief Send FRTSYN Timing Data
 **
 ** This function sends FrTSyn timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendFrTSynTimingData(void);

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
/** \brief Send FRTSYN MASTER Timing Data
 **
 ** This function sends FrTSyn master timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendFrTSynMasterTimingData
(
  uint8 timeBaseIndex
);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
/** \brief Send FRTSYN SLAVE Timing Data
 **
 ** This function sends FrTSyn slave timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendFrTSynSlaveTimingData
(
  uint8 timeBaseIndex
);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */

#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)) */




#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)

STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynTimingData(void);

/** \brief Send ETHTSYN MASTER Timing Data
 **
 ** This function sends EthTSyn master timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynMasterTimingData
(
  uint8 timeBaseIndex
);

/** \brief Send ETHTSYN SLAVE Timing Data
 **
 ** This function sends EthTSyn slave timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynSlaveTimingData
(
  uint8 timeBaseIndex
);


STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynPdelayTimingData(void);

/** \brief Send ETHTSYN MASTER PDELAY Timing Data
 **
 ** This function sends EthTSyn master pdelay timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynMasterPdelayTimingData
(
  uint8 timeBaseIndex
);

/** \brief Send ETHTSYN SLAVE PDELAY Timing Data
 **
 ** This function sends EthTSyn slave pdelay timing data to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynSlavePdelayTimingData
(
  uint8 timeBaseIndex
);

#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */


#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */



#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

/** \brief Send Notification to customer
 **
 ** This function sends available notification to customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendNotificationToCustomer
(
  StbM_SynchronizedTimeBaseType timebaseId,
  StbM_CustomerIdType customerId,
  P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_VAR) devTime
);


/** \brief Send Notification to customer when Gpt Timer expires
 **
 ** This function notifies the customer when StbM Timer and also Gpt Timer has expired for a certain Notification Customer
 */
STATIC FUNC(void, STBM_CODE) StbM_SendNotificationForExpiryPointsWithGptTimerAlreadyExpired(void);


/** \brief Tries to call Gpt_StartTimer()
 **
 ** This function tries to start the Gpt timer for a specific node
 */
STATIC FUNC(void, STBM_CODE) StbM_TryToCallGptStartTimer
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) gptExpireTimeStamp,
  P2VAR(StbM_CustomerTimerExpireTimeNodeDataType, AUTOMATIC, STBM_VAR) currentNode
);

/** \brief Tries to call Gpt_StartTimer()
 **
 ** This function tries to start the Gpt timer for a specific array index
 */
STATIC FUNC(void, STBM_CODE) StbM_TryToCallGptStartTimerByArrayIndex
(
  StbM_TimeStampType gptExpireTimeStamp,
  uint32 arrayIndex
);



/** \brief Calculates the time deviation
 **
 ** This function calculate the time deviation which need to be sent through an immediate customer notification
 */
STATIC FUNC(sint32, STBM_CODE) StbM_CalculateTimeDeviationForImmediateNotification
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) localTimeStamp,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) customerExpireTime
);

/** \brief Handles expiry points which couldn't call Gpt_StartTimer() when it was the case
 **
 ** This function checks for expiry points which have Gpt_StartTimer() pending,
 ** if Customer should be notified or Gpt_StartTimer() should be called
 */
STATIC FUNC(void, STBM_CODE) StbM_HandleExpiryPointsWithPendingStartGptTimer
(
  P2VAR(StbM_LocalTimeCallType, AUTOMATIC, STBM_VAR) localTimes
);


/** \brief Calculates the difference between 'customerTimerExpireTime' and 'currentTimeBaseTime' and compares it with StartThreshold
 **
 ** This function handles expiry points for with the difference mentioned above, elapsed StartThreshold
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_DifferencePassedOverStartThreshold
(
  P2VAR(StbM_LocalTimeCallType, AUTOMATIC, STBM_VAR) localTimes
);

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */



/** \brief Calculates the difference between minuend and subtrahend
 **
 ** This function calculates and returns the difference of two timestamps.
 ** The Minuend must be greater or equal the Subtrahend.
 **
 ** \param[in] timeStampMinuendPtr - Points to the first timestamp (Minuend parameter)
 ** \param[in] timeStampSubtrahendPtr - Points to the second timestamp (Subtrahend parameter)
 ** \param[out] timeStampDifferencePtr - Points to the memory location where the difference
 **                                      of the timestamps shall be stored
 **
 ** \return Status of subtract operation
 ** \retval E_OK Subtraction successful
 ** \retval E_NOT_OK operation failed - Result is negative
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SubtractTimeStamps
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampMinuendPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampSubtrahendPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampDifferencePtr
);

/** \brief Calculates diff of Virtual Local Times
 **
 ** This function calculates and returns the difference of two virtual local times.
 ** The Minuend must be greater or equal the Subtrahend. Result will be a time stamp.
 **
 ** \param[in] virtualLocalTimeMinuendPtr - Points to the first VLT (Minuend parameter)
 ** \param[in] virtualLocalTimeSubtrahendPtr - Points to the second VLT (Subtrahend parameter)
 ** \param[out] timeStampDifferencePtr - Points to the memory location where the difference
 **                                      of the VLTs shall be stored
 **
 ** \return Status of subtract operation
 ** \retval E_OK Subtraction successful
 */
STATIC FUNC(void, STBM_CODE) StbM_SubtractVirtualLocalTimesToTimeStamp
(
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeMinuendPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSubtrahendPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampDifferencePtr
);

/** \brief Calculates diff of Virtual Local Times
 **
 ** This function calculates and returns the difference of two virtual local times.
 ** The Minuend must be greater or equal the Subtrahend. Result will be a Virtual Local Time.
 **
 ** \param[in] virtualLocalTimeMinuendPtr - Points to the first VLT (Minuend parameter)
 ** \param[in] virtualLocalTimeSubtrahendPtr - Points to the second VLT (Subtrahend parameter)
 ** \param[out] virtualLocalTimeDiff - Points to the memory location where the difference
 **                                    of the VLTs shall be stored
 **
 ** \return Status of subtract operation
 */
STATIC FUNC(void, STBM_CODE) StbM_SubtractVirtualLocalTimes
(
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeMinuendPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSubtrahendPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeDiff
);

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
/** \brief Calculate new Time Tuple
 **
 ** This calculates a new time tuple after the adaption interval is exceeded.
 ** (used only when Offset Correction is used).
 **
 ** \param[in] commonIndex - common index of the synchronized time base
 ** \param[in] operationSign - sign to know if subtraction/addition will be made
 ** \param[in] rate - current calculated rate (rrc + roc)
 ** \param[in] adaptationIntervalPtr - configured adaption interval
 ** \param[in/out] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[in/out] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_CalculateNewTimeTuple
(
  uint8 commonIndex,
  uint8 operationSign,
  uint32 rate,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) adaptationIntervalPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr
);

/** \brief Reset Offset Correction values
 **
 ** This function resets the variable used for Offset Correction.
 **
 ** \param[in] rcDataIndex - index in slave rate correction array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_ResetOffsetCorrectionValues
(
  uint8 rcDataIndex
);

/**  \brief Calculate Rate Correction
**
**  This function calculates rate correction
**
** \param[in] commonIndex common index of the synchronized time base
** \param[in/out] rocPtr rate adaptation with all calculated decimals
** \param[in/out] operationSignPtr sign to know if subtraction/addition will be made
** \param[in/out] virtualLocalTimeDiffPtr  Points to the memory location where the difference
**                                      of the VLTs shall be stored
** \param[in/out] currentTimeTupleGlobalPtr - Current stored Global Time value.
** \param[in/out] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
** \param[in] localTimePtr - current local time
*/
STATIC FUNC(void, STBM_CODE)StbM_CalculateRateCorrection
(
  uint8 commonIndex,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rocPtr,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) ratePtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) operationSignPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) VirtualLocalTimeDiffPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
);
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */

#if ((STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON) || (STBM_OFFSET_CORRECTION_USED == STD_ON))
/** \brief Calculates sum of Virtual Local Times
 **
 ** This function calculates and returns the sum of two virtual local times.
 **
 ** \param[in] virtualLocalTimeMinuendPtr - Points to the first VLT (Minuend parameter)
 ** \param[in] virtualLocalTimeSubtrahendPtr - Points to the second VLT (Subtrahend parameter)
 ** \param[out] virtualLocalTimeSumPtr - Points to the memory location where the sum
 **                                      of the VLTs shall be stored
 **
 ** \return Status of subtract operation
 ** \retval E_OK Subtraction successful
 */
STATIC FUNC(void, STBM_CODE) StbM_SumVirtualLocalTimes
(
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeMinuendPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSubtrahendPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSumPtr
);
#endif /* (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON) || (STBM_OFFSET_CORRECTION_USED == STD_ON) */

/** \brief Calculates if one timestamp is greater of equal than another timestamp
 **
 ** This function checks if timestamp A is greater or equal than timestamp B
 **
 ** \param[in] timeStampAPtr - timestamp A
 ** \param[in] timeStampBPtr - timestamp B
 **
 ** \return Status of comparsion
 ** \retval TRUE Timestamp A is greater or equal than timestamp B
 ** \retval FALSE timestamp A is smaller than timestamp B
 */
STATIC FUNC(boolean, STBM_CODE) StbM_TimeStampIsGreaterEqual
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampAPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampBPtr
);

#if (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON)
/** \brief Synchronize schedule table
 **
 ** This function synchronizes a schedule table given by triggeredCustomerIndex by:
 ** a) first updating the global time
 ** b) synchronizing the schedule table
 **
 ** \param[in] triggeredCustomerIndex - configuration index of the triggered customer
 ** \param[in] timeBaseId - time base Id
 */
STATIC FUNC(void, STBM_CODE) StbM_SyncTriggeredCustomer
(
  uint8 triggeredCustomerIndex,
  StbM_SynchronizedTimeBaseType timeBaseId
);
#endif /* STBM_TRIGGERED_CUSTOMERS_USED == STD_ON */

/** \brief Detects time leaps
 **
 ** Handles time leap feature.
 **
 ** Note: Function must be called from within an exclusive area.
 **
 ** \param[in] timeBaseId - timeBaseId of the synchronized time base
 ** \param[in] currentTimeBaseTime - current local time of the time base
 **                                  (before Global Time is applied)
 ** \param[in] timeStampPtr - actual timestamp used to calculate the difference value
 ** \param[out] flagsOutPtr - output variable for the status flags
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_HandleTimeLeap
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr
);

/** \brief Detects time leaps
 **
 ** This function checks if the difference value between the given timestamp
 ** and the previous stored timestamp exceeds the threshold value for a given
 ** sync time base Id.
 **
 ** Note: Function must be called from within an exclusive area.
 **
 ** \param[in] syncTimeBaseIndex - Id (=index) of the synchronized time base
 ** \param[in] currentTimeBaseTime - current local time of the time base
 **                                  (before Global Time is applied)
 ** \param[in] timeStampPtr - actual timestamp used to calculate the difference value
 ** \param[out] flagsOutPtr - output variable for the time leap status flags
 **
 ** \return Indicates result of time leap detection
 ** \retval TRUE time leap detected
 ** \retval FALSE no time leap detected
 */
STATIC FUNC(boolean, STBM_CODE) StbM_TimeLeapDetection
(
  uint8 commonIndex,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTime,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr
);

#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
/** \brief Handles the clear timeleap counter
 **
 ** This function checks if a timeleap counter(for future or past)
 ** needs to be decremented, or it reached zero and the timeleap
 ** can be cleared.
 **
 ** Note: Function must be called from within an exclusive area.
 **
 ** \param[in] timeLeapCounterPtr - pointer to the clear timeleap counter
 ** \param[out] flagsOutPtr - output variable for the time leap status flags
 ** \param[in] timeLeapFlag - evaluated timeleap flag
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_HandleTimeLeapCounter
(
  P2VAR(uint16, AUTOMATIC, STBM_VAR) timeLeapCounterPtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  uint8 timeLeapFlag
);
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */



#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)

/** \brief Update Time Base offset and status in shared memory
 **
 ** This function updates the offset time with respect to the HwCounter, and the
 ** status of the time base, in the shared memory
 **
 ** \param[in] timeBaseId - current time base Id
 ** \param[in] currentTimeBaseStatus - current status of the time base
 ** \param[in] currentTimeBseTimePtr - current time of the time base
 ** \param[in] currentHwCounter - current Eth Hardware counter
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateSharedDataInMemory
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_TimeBaseStatusType currentTimeBaseStatus,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) currentHwCounter
);

/** \brief Update Time Base offset in shared memory
 **
 ** This function updates the status of the time base in the
 ** shared memory
 **
 ** \param[in] sharedMemoryIndex - index in the Shared Memory location
 ** \param[in] currentTimeBaseStatuss - current status of the time base
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateSharedStatusInMemory
(
  uint16 sharedMemoryIndex,
  StbM_TimeBaseStatusType currentTimeBaseStatus
);

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Update Rate Deviation in shared memory
 **
 ** This function updates the rate deviation of the time base in the
 ** shared memory
 **
 ** \param[in] sharedMemoryIndex - index in the Shared Memory location
 ** \param[in] rcDataIndex - index in slave rate correction array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateSharedRateDeviationInMemory
(
  uint16 sharedMemoryIndex,
  uint8 rcDataIndex
);
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */


#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */

#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)

/** \brief Update global time in the shared memory - version 2
 **
 ** This function updates the global time in the shared memory - version 2
 **
 ** \param[in] commonIndex - common index
 ** \param[in] timeBaseStartIndex - start index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateGlobalTimeInSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
);

/** \brief Update virtual local time in the shared memory - version 2
 **
 ** This function updates the virtual local time in the shared memory - version 2
 **
 ** \param[in] commonIndex - common index
 ** \param[in] timeBaseStartIndex - start index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateVirtualLocalTimeInSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
);


/** \brief Update timeTuple and timeBaseStatus in the shared memory - version 2
 **
 ** This function updates the timeTuple and timeBaseStatus in the shared memory - version 2
 **
 ** \param[in] commonIndex - common index
 ** \param[in] timeBaseStartIndex - start index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateTimeTupleInSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
);

#if ((STBM_MASTER_RATE_CORRECTION_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON))
/** \brief Update Rate Deviation and Rate Correction in shared memory - version 2
 **
 ** This function updates the rate deviation and rate correction of the time base in the
 ** shared memory - version 2
 **
 ** \param[in] rateCorrection - pointer to calculated rate correction
 ** \param[in] rateDeviation - pointer to calculated rate deviation
 ** \param[in] timeBaseStartIndex - index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateRateDevAndRateCorrInSharedMemory
(
  P2CONST(uint32, AUTOMATIC, STBM_VAR) rateCorrection,
  P2CONST(StbM_RateDeviationType, AUTOMATIC, STBM_VAR) rateDeviation,
  uint16 timeBaseStartIndex
);
#endif /* ((STBM_MASTER_RATE_CORRECTION_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)) */

#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */


#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)

/** \brief Read TG from shared memory - version 2
 **
 ** This function reads the TG from the shared memory - version 2
 **
 ** \param[in] commonIndex - current time base Id
 ** \param[in] timeBaseStartIndex - start index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_ReadGlobalTimeFromSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
);

/** \brief Read VLT from shared memory - version 2
 **
 ** This function reads the VLT from the shared memory - version 2
 **
 ** \param[in] commonIndex - current time base Id
 ** \param[in] timeBaseStartIndex - start index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_ReadVirtualLocalTimeFromSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
);

/** \brief Read timeTuple, timeBaseStatus, rateDeviation and rateCorrection (if supported) from shared memory - version 2
 **
 ** This function reads the timeTuple, timeBaseStatus, rateDeviation and rateCorrection (if supported) from the shared memory - version 2
 **
 ** \param[in] commonIndex - current time base Id
 ** \param[in] timeBaseStartIndex - start index in shared data array
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_ReadDataFromSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
);
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */


#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
/** \brief Sets the flags in NotificationEvents according to the configured
 ** StbMStatusNotificationMask
 **
 ** \param[in] timeBaseId - Id (=index) of the time base
 ** \param[in] StbM_NotificationEvents - variable containing the events that happend
 ** in the function calling StbM_StatusEventDetection().
 */
STATIC FUNC(void, STBM_CODE) StbM_StatusEventDetection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_TimeBaseNotificationType StbM_NotificationEvents
);

/** \brief Sets the flags in StatusNotification according to global status flags
 **
 ** \param[in] flags - global status flags
 ** \param[in] currentTimeStamp - global time
 ** \param[out] statusNotificationPtr - Notification Status
 */
STATIC FUNC(void, STBM_CODE) StbM_UpdateNotificationStatus
(
  uint8 flags,
  StbM_TimeStampType currentTimeStamp,
  P2VAR(StbM_TimeBaseNotificationType, AUTOMATIC, STBM_APPL_DATA) statusNotificationPtr
);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#if (STBM_RATE_CORRECTION_USED)
/** \brief Initialize all the Rate Correction data
 **
 ** Initialize all the Rate Correction data
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_RateCorrectionDataInit
(
  void
);
#endif /* (STBM_RATE_CORRECTION_USED) */


#if (STBM_TIME_VALIDATION_SUPPORT)


/** \brief Initialize all the Time Validation info data
 **
 ** Initialize all the Time Validation info data (counter and wrappedCounter)
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_InitTimeValidationInfo
(
  uint32 idx,
  P2VAR(StbM_TimeValidationInfoType, AUTOMATIC, STBM_VAR) timeValidationInfo,
  boolean isMaster,
  boolean isPdelay
);


/** \brief Initialize all the Time Validation info data for all blocks
 **
 ** Initialize all the Time Validation info data for all blocks
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_InitTimeValidationInfoBlocks
(
  void
);


/** \brief Initialize all the Time Validation data
 **
 ** Initialize all the Time Validation data
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_TimeValidationDataInit
(
  void
);


#endif /* (STBM_TIME_VALIDATION_SUPPORT) */

#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED)
/** \brief Initialize all data related to time notification
 **
 ** Initialize all data related to time notification
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_TimeNotificationDataInit
(
  uint32 timeNotificationDataIndex
);
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED) */


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Initialize variables to config values
 **
 ** Initialize the Rate Correction data to the config values,
 ** in order to skip the first Rate Correction calculations
 ** that don't have start values, or start with the correct
 ** offset in the array for the intervalCounter.
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_SlaveDataInit
(
  uint8 rcDataIndex,
  uint8 startValuesIndex,
  uint8 stopValuesIndex
);

/** \brief Initialize variables to config values
 **
 ** ReInitialize the Rate Correction measurement data to the,
 ** config valuesin order to skip the first Rate Correction
 ** calculations that don't have start values, or start with
 ** the correct offset in the array for the intervalCounter.
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_SlaveDataReinitMeasurements
(
  uint8 rcDataIndex,
  uint8 startValuesIndex,
  uint8 stopValuesIndex
);
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Detects time leaps
 **
 ** This function checks if enough time has passed since the last
 ** "start "StbM_BusSetGlobalTime() call to be able to calculate
 ** a new Rate Correction value.
 **
 ** Note: Function must be called from within an exclusive area.
 **
 ** \param[in] timeBaseId - time base id
 ** \param[in] intervalCounter - value of the counter for current time base
 **
 ** \return Indicates result of interval check
 ** \retval TRUE perform Rate Correction
 ** \retval FALSE do not perform Rate Correction
 */
STATIC FUNC(boolean, STBM_CODE) StbM_CheckIntervalTiming
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint8 intervalCounter
);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Computes the quotient of two unsigned Q4.28 fixed-point
 ** numbers
 **
 ** This function computes the quotient of two unsigned Q4.28
 ** fixed-point numbers
 **
 ** \param[in] a - first member of the division
 ** \param[in] b - second member of the division
 **
 ** \return Quotient
 */
STATIC FUNC(uint32, STBM_CODE) StbM_Div_Q
(
  uint32 a,
  uint32 b
);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_RATE_CORRECTION_USED)
/** \brief Computes the high part of a product
 **
 ** This function computes the high part of the product a*b number (bits <63:32>)
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 ** \param[out] rhi - bits <63:32> of the product a * b
 **
 */
STATIC FUNC(uint32, STBM_CODE) StbM_Umul32_hi
(
  uint32 a,
  uint32 b
);

/** \brief Computes product of two unsigned 32-bit integers
 **
 ** This function computes the full 64-bit product of two unsigned 32-bit integers
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 ** \param[out] rhi - bits <63:32> of the product a * b
 ** \param[out] rlo - bits <31:0> of the product a * b
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Umul32_Wide
(
  uint32 a,
  uint32 b,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rhi,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rlo
);

/** \brief Computes the product of two numbers
 **
 ** This function computes the product of two numbers
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 **
 ** \return Product result
 */
STATIC FUNC(uint64, STBM_CODE) StbM_Umul32_64
(
  uint32 a,
  uint32 b
);

/** \brief Computes the division of two numbers
 **
 ** This function computes the division of two numbers
 **
 ** \param[in] a - first member of the division
 ** \param[in] b - second member of the division
 **
 ** \return Division result
 */
STATIC FUNC(uint64, STBM_CODE) StbM_Udiv64_32
(
  uint64 n,
  uint32 base
);

/** \brief Computes the product of two unsigned Q4.28 fixed-point
 ** numbers
 **
 ** This function computes the product of two unsigned Q4.28
 ** fixed-point numbers
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 **
 ** \return Product result
 */
STATIC FUNC(uint32, STBM_CODE) StbM_Mul_Q
(
  uint32 a,
  uint32 b
);

/** \brief Converts the timestamp to a Q number
 ** numbers
 **
 ** This function converts the timestamp to a Q number
 **
 ** \param[in] timeStampPtr - timestamp to convert
 **
 ** \return Converted timestamp
 */
STATIC FUNC(uint32, STBM_CODE) StbM_Timestamp_To_Q
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
);

/** \brief Converts the Q number to a timestamp
 ** numbers
 **
 ** This function converts the Q number to a timestamp
 **
 ** \param[in] q_timestamp - number to convert
 ** \param[out] timeStampPtr - resulted timestamp
 **
 ** \return Converted timestamp
 */
STATIC FUNC(void, STBM_CODE) StbM_Q_To_Timestamp
(
  uint32 q_timestamp,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
);

/** \brief Calculates local time of a time base using the Rate
 ** Correction formula or the Offset Correction one
 **
 ** This function calculates local time of a time base using the Rate
 ** Correction formula or the Offset Correction one
 **
 ** \param[in] timebaseId - time base id
 ** \param[out] timeStampLocalTimePtr - calculated local time timestamp
 ** \param[out] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[out] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 ** \param[out] localTimePtr - Current Virtual Local Time value.
 **
 ** \return the success/failure of the function call
 ** \retval E_OK In case of successful call of the function.
 ** \retval E_NOT_OK In case of unsuccessful call of the function.
 */
STATIC FUNC(void, STBM_CODE) StbM_CalculateLocalTimeWithRate
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampLocalTimePtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
);

/** \brief Obtain max limit for calculation with rate
 **
 ** This function calculates the maximum value StbM can handle
 ** when using rate correction/offset correction
 **
 ** \param[in] rcDataIndex - index to the rate correction data
 ** \param[in] masterRateCorrectionDisabled - master/slave rate correction
 ** \param[out] maxAllowedValuePtr - value of the limit
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_GetMaxAllowedLimit
(
  uint8 rcDataIndex,
  boolean masterRateCorrectionDisabled,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) maxAllowedValuePtr
);
#endif /* (STBM_RATE_CORRECTION_USED) */

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
/** \brief Perform Offset Correction
 **
 ** This function calculates and updates all variables
 ** needed for offset correction
 **
 ** \param[in] syncTimeBaseIndex - sync time base id
 ** \param[in] currentTimeBaseTimePtr - current time base local time
 ** \param[in] currentGlobalTimePtr - current global time
 **
 ** \return the success/failure of the function call
 ** \retval E_OK In case of successful call of the function.
 ** \retval E_NOT_OK In case of unsuccessful call of the function.
 */
STATIC FUNC(void, STBM_CODE) StbM_PerformOffsetCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentGlobalTimePtr,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) performJumpPtr
);
#endif /* STBM_OFFSET_CORRECTION_USED == STD_ON */


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Perform Slave Rate Correction
 **
 ** This function calculates and updates all variables
 ** needed for a slaves rate correction
 **
 ** \param[in] timeBaseId - time base id
 **
 ** \return the success/failure of the function call
 ** \retval E_OK In case of successful call of the function.
 ** \retval E_NOT_OK In case of unsuccessful call of the function.
 */
STATIC FUNC(void, STBM_CODE) StbM_PerformSlaveRateCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId
);


/** \brief Perform Calculation of Rate Correction
 **
 ** This function calculates the rate correction
 **
 ** \param[in] rcDataIndex - index in StbM_SlaveRateCorrectionData[] array
 ** \param[in] commonIndex - common index
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_CalculateSlaveRateCorrection
(
  uint8 rcDataIndex,
  uint8 commonIndex
);

/** \brief Check status of flags
 **
 ** This function checks the status of flags in order
 ** to determine if the rate correction is performed with
 ** valid data
 **
 ** \param[in] rcDataIndex - time base rate correction index
 **
 ** \return Rate correction can/can not be performed
 ** \retval TRUE Rate correction can be performed.
 ** \retval FALSE Rate correction can not be performed.
 */
STATIC FUNC(boolean, STBM_CODE) StbM_CheckFlagChanges
(
  uint8 rcDataIndex
);

/** \brief Validate rate correction interval
 **
 ** This function checks if the rate correction interval
 ** has overlapped with another interval
 **
 ** \param[in] commonIndex - time base common index
 ** \param[in] rcDataIndex - time base rate correction index
 ** \param[in] intervalCounter - current rate correction interval
 **
 ** \return Intervals have/have not overlapped
 ** \retval TRUE Intervals have overlapped.
 ** \retval FALSE Intervals have not overlapped.
 */
STATIC FUNC(boolean, STBM_CODE) StbM_ValidateRateCorrectionInterval
(
  uint8 commonIndex,
  uint8 rcDataIndex,
  uint8 intervalCounter
);

/** \brief Check if restart of measurement is needed
 **
 ** This function checks if we need to restart the rate
 ** correction measurements or not
 **
 ** \param[in] rcDataIndex - time base rate correction index
 ** \param[in] startValuesIndex - rate correction start data index
 ** \param[in] stopValuesIndex - rate correction stop data index
 ** \param[in] extendDiscard - flags problem detected
 ** \param[in] rateIntervalOverlapped - interval overlap problem detected
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_CheckIfMeasurementRestartIsNeeded
(
  uint8 rcDataIndex,
  uint8 startValuesIndex,
  uint8 stopValuesIndex,
  boolean extendDiscard,
  boolean rateIntervalOverlapped
);
#endif /* STBM_RATE_CORRECTION_USED == STD_ON */

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
 /** \brief Update Local Time of the Time Base
 **
 ** This function update the local time of the time base
 ** if also checks for time leaps, or does the offset
 ** correction if necessary
 **
 ** \param[in] timeBaseId - time base id
 ** \param[out] flagsOutPtr - current flags variable
 ** \param[in] currentGlobalTimePtr - current global time
 ** \param[in] currentTimeBaseTimePtr - current local time
 ** \param[in] measureDataPtr - current measurement data
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_PerformTimeRecording
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentGlobalTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */

#if (STBM_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime_DetChecks
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);
#endif /* STBM_DEV_ERROR_DETECT == STD_ON */



#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Stores new time values needed for Slave Rate Correction
 **
 ** \param[in]  timeBaseId - ID of the synchronized time-base.
 ** \param[in]  flagsPtr - set flags
 ** \param[in]  currentGlobalTimeStampPtr - Current GlobalTime value
 ** \param[in]  currentLocalTimePtr - Current Local Time value.
 */
STATIC FUNC(void, STBM_CODE) StbM_StoreNewTimeValuesForSlaveRateCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(uint8, AUTOMATIC, STBM_VAR) flagsPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentGlobalTimeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) currentLocalTimePtr
);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

/** \brief Update Local Time of the Time Base
 **        and handle OffsetCorrection, TimeRecording, Timeleap, if local time was successfully retrieved
 **        and also store the values of the Main Time Tuple needed for TimeValidation.
 **
 ** This function handles:
 ** - Offset Correction
 ** - Time Recording
 ** - Time Leap
 ** - Stores the values of the Main Time Tuple
 **
 ** \param[in]  timeBaseId - ID of the synchronized time-base.
 ** \param[in]  flagsOutPtr - set flags
 ** \param[out] performJumpPtr - Use GlobalTime/SyncLocalTime
 ** \param[in]  receivedGlobalTimePtr - received GlobalTime
 ** \param[in]  currentTimeBaseTimePtr - Current Local Time value.
 ** \param[in]  measureDataPtr - PDelay related data
 ** \param[in]  localTimePtr - User data of the time base.
 */
STATIC FUNC(void, STBM_CODE) StbM_HandleOffsetCorrectionTimeRecordingTimeleap
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) performJumpPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) receivedGlobalTimePtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
/** \brief Handles Offset Correction
 **
 ** This function handles:
 ** - Offset Correction
 **
 ** \param[in] timeBaseId - ID of the synchronized time-base.
 ** \param[in] currentTimeBaseTimePtr - Time stamp containing the current time.
 ** \param[in] receivedGlobalTimePtr - Received GlobalTime value
 ** \param[out] performJumpPtr -flag to check if jump shall be performed or not
 */
STATIC FUNC(void, STBM_CODE) StbM_HandleOffsetCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) receivedGlobalTimePtr,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) performJumpPtr
);
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */


#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_HandleTimeRecording
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) receivedGlobalTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_StoreTimeTuple
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)) */
#endif /* STBM_TIME_VALIDATION_SUPPORT == STD_ON */



/** \brief Set UserData bytes, based on userDataLength
**
** This function sets the new user data bytes, based on userDataLength
** This function shall be called inside an exclusive area
**
** \param[in] userDataCommonIndex - common ID for StbM_UserData[] array
** \param[in] userData - user data bytes which need to be set
**
*/
STATIC FUNC(void, STBM_CODE) StbM_SetUserDataBytes
(
  uint8 userDataCommonIndex,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
);


#if (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON)
/** \brief Update Local Time of the Time Base
**
** This function allows the caller to set the new global time that has to be valid for the
** system, which will be sent to the busses and modify HW registers behind the
** providers, if supported. This function will be used if a Time Master is present in
** this ECU.
**
** \param[in] timeBaseId - ID of the synchronized time-base.
** \param[in] timeStampPtr - Time stamp containing the current time.
** \param[out] currentTimeTupleGlobalPtr - Current stored Global Time value.
** \param[out] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
** \param[in] userDataPtr - User data of the time base.
**
** \return the success/failure of the function call
** \retval E_OK In case of successful call of the function.
** \retval E_NOT_OK In case of unsuccessful call of the function.
**
*/
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SetTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
);
#endif /* (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON) */

/** \brief Service to convert Virtual Local Time to Time Stamp
 **
 ** Returns the Time Stamp converted from Virtual Local Time.
 **
 ** \param[in] virtualLocalTimePtr - Virtual Local Time to be converted
 ** \param[out] timeStampPtr - Converted Time Stamp.
 **
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_VirtualLocalTimeToTimeStamp
(
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimePtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
);

#if (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED)
/** \brief Service to convert Time Stamp to Virtual Local Time
 **
 ** Returns the Virtual Local Time converted from Time Stamp.
 **
 ** \param[in] virtualLocalTimePtr - Virtual Local Time to be converted
 ** \param[out] timeStampPtr - Converted Time Stamp.
 **
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_TimeStampToVirtualLocalTime
(
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimePtr
);
#endif /* STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED */

/** \brief Service to return the Virtual Local Time with det checks
 **
 ** Returns the Virtual Local Time of the referenced Time Base.
 **
 ** \param[in] timeBaseId - ID of the synchronized time-base.
 ** \param[out] detectedDET - Check if a possible DET was detected.
 ** \param[out] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[out] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 ** \param[out] localTimePtr - Current Virtual Local Time value.
 **
 ** \return the success/failure of the function call
 ** \retval E_OK In case of successful call of the function.
 ** \retval E_NOT_OK In case of unsuccessful call of the function.
 **
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTimeNoDet
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint8* detectedDET,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);

/** \brief Service to return the Virtual Local Time no det checks
 **
 ** Returns the Virtual Local Time of the referenced Time Base.
 **
 ** \param[in] timeBaseId - ID of the synchronized time-base.
 ** \param[out] localTimePtr - Current Virtual Local Time value.
 **
 ** \return the success/failure of the function call
 ** \retval E_OK In case of successful call of the function.
 ** \retval E_NOT_OK In case of unsuccessful call of the function.
 **
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTimeNoChecks
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
);

#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
/** \brief Service to return the current time of an offset time base
 **
 ** Returns the current time of the referenced Offset Time Base.
 **
 ** \param[in] timeBaseId - ID of the synchronized time-base.
 ** \param[out] timeStampPtr - pointer where to store time value.
 ** \param[out] syncTimeStampPtr - current local time of the sync time base.
 ** \param[out] currentTimeTupleGlobalPtr - Current stored Global Time value.
 ** \param[out] currentTimeTupleVLTPtr - Current stored Virtual Local Time value.
 ** \param[out] localTimePtr - Current Virtual Local Time value.
 **
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeBaseTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) syncTimeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
);

/** \brief CheckCalculateOffsetTime function
 **
 ** Check if it is needed to calculate offsettime or not.
 **
 ** \param[in] syncIndex - the underlying synchronized time base.
 ** \param[in] checkGlobalTimeBit - this parameter will be TRUE for calls comming
 ** from StbM_SetGlobalTime() and StbM_UpdateGlobalTime so the check for the
 ** GLOBAL_TIME_BIT for offset can be done. And it will be FALSE for calls
 ** comming from StbM_BusSetGlobalTime() because the check should not be
 ** performed for slave time bases.
 ** \param[out] calculateOffsetTimePtr - TRUE if it is needed to calculate offset time.
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_CheckCalculateOffsetTime
(
  uint8 syncIndex,
  boolean checkGlobalTimeBit,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) calculateOffsetTimePtr
);
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */

#if ((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) && (STBM_SYNC_TIME_RECORDING_USED == STD_ON))
/** \brief Service to return the current Block Index
 **
 ** Returns the current block index
 **
 ** \param[in] commonIndex - common index of the time-base.
 **
 ** \return the current block index
 */
STATIC FUNC(uint32, STBM_CODE) StbM_FindCurrentBlockIndex
(
  uint8 commonIndex
);
#endif /* ((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) && (STBM_SYNC_TIME_RECORDING_USED == STD_ON)) */


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief Service to calculate and record Rate Correction
 **
 ** \param[in] commonIndex - common index of the time-base.
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_HandleSlaveRateCorrection
(
  uint8 commonIndex
);

/** \brief Service to calculate and record Rate Correction
 **
 ** \param[in] commonIndex - common index of the time-base.
 ** \param[out] notificationEventsPtr - event notification
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_CalculateAndRecordRateCorrection
(
  uint8 commonIndex
);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

/** \brief Get the first free array index
 **
 ** Get the first free array index, where the new expiry point needs to be inserted
 **
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetInsertionIndex
(
  P2VAR(uint32, AUTOMATIC, STBM_VAR) insertIdx
);

/** \brief Get the length of the list
 **
 ** Get the length of the list
 **
 */
STATIC FUNC(uint32, STBM_CODE) StbM_GetListLength
(
  void
);

/** \brief Check if timeBaseId and customerId are already in the list
 **
 ** Check if timeBaseId and customerId are already in the list
 ** If so, they will not be inserted
 **
 */
STATIC FUNC(boolean, STBM_CODE) StbM_IsTimeBaseIdCustomerIdInList
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CustomerIdType customerId
);

/** \brief Insert an element after a specific expiry point
 **
 ** Insert an element after a specific expiry point
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_InsertAfter
(
  uint32 expireTimeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) expiryPointAfterWhichToInsert,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
);

/** \brief Insert an element at the beginning of the list
 **
 ** Insert an element at the beginning of the list
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_InsertAtTheBeginning
(
  uint32 expireTimeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
);

/** \brief Insert an element in the list
 **
 ** Insert an element in a list
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_InsertInList
(
  uint32 timeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeNodeDataType, AUTOMATIC, STBM_VAR) newExpiryPointNode,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
);


/** \brief Seach for the right position for inserting a new expity point in the list
 **
 ** Seach for the right position for inserting a new expity point in the list
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_InsertAtTheRightPosition
(
  uint32 expireTimeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
);


/** \brief Delete a specific expiry point from the list
 **
 ** Delete a specific expiry point from the list, when its timer has expired
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_DeleteFromPosition
(
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) expiryPointToBeDeleted
);



#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */



#if (STBM_FRESHNESS_USED == STD_ON)
#if (STBM_DEV_ERROR_DETECT == STD_ON)
/** \brief Check if freshnessValueId is configured
 **
 ** Check if freshnessValueId is already in the list of freshness value ids
 **
 */
STATIC FUNC(boolean, STBM_CODE) StbM_IsFreshnessValueIdConfigured
(
  uint16 freshnessValueId
);
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */
#endif /* (STBM_FRESHNESS_USED == STD_ON) */


/** \brief Service to return the Updated Rx Time Tuple
 **
 ** Returns the resulting Time Tuple.
 **
 ** \param[in] timeBaseId - ID of the synchronized or offset time-base.
 ** \param[in/out] globalStampPtr - Updated Rx global time.
 ** \param[in/out] virtualTimePtr - Updated Rx virtual time.
 **
 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateRxTimeTuple
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) globalStampPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) virtualTimePtr
);



#if  (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_LocalTimeCallType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_LocalTimeCallType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_LocalTimeCall
(
  P2VAR(StbM_LocalTimeCallType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */


#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_SyncRecordTableBlockType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_SyncRecordTableBlockType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_SyncRecordTableBlock
(
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_OffsetRecordTableBlockType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_OffsetRecordTableBlockType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_OffsetRecordTableBlock
(
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_CanTimeMasterMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_CanTimeMasterMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_CanTimeMasterMeasurement
(
  P2VAR(StbM_CanTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_CanTimeSlaveMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_CanTimeSlaveMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_CanTimeSlaveMeasurement
(
  P2VAR(StbM_CanTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_FrTimeMasterMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_FrTimeMasterMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_FrTimeMasterMeasurement
(
  P2VAR(StbM_FrTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_FrTimeSlaveMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_FrTimeSlaveMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_FrTimeSlaveMeasurement
(
  P2VAR(StbM_FrTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_EthTimeMasterMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_EthTimeMasterMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_EthTimeMasterMeasurement
(
  P2VAR(StbM_EthTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);

/** \brief Initialize all the elements of the array of type StbM_EthTimeSlaveMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_EthTimeSlaveMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_EthTimeSlaveMeasurement
(
  P2VAR(StbM_EthTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);

/** \brief Initialize all the elements of the array of type StbM_PdelayResponderMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_PdelayResponderMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_PdelayResponderMeasurement
(
  P2VAR(StbM_PdelayResponderMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);

/** \brief Initialize all the elements of the array of type StbM_PdelayInitiatorMeasurementType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_PdelayInitiatorMeasurementType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_PdelayInitiatorMeasurement
(
  P2VAR(StbM_PdelayInitiatorMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */

#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
/** \brief Initialize all the elements of the array of type StbM_SendCustomerNotificationType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_SendCustomerNotificationType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_SendCustomerNotification
(
  P2VAR(StbM_SendCustomerNotificationType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);

/** \brief Initialize all the elements of the array of type StbM_GptCallPairType
 **
 ** This function initializes with 0 all the elements of the array of type StbM_GptCallPairType.
 **
 ** \param[in] arrayToBeInitialized - array which needs to be initialized
 **
 */
STATIC FUNC(void, STBM_CODE) StbM_Init_GptCallPair
(
  P2VAR(StbM_GptCallPairType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
);
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */






#define STBM_STOP_SEC_CODE
#include <StbM_MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/



#define STBM_START_SEC_VAR_INIT_8
#include <StbM_MemMap.h>

/** \brief Variable used to store the initialization state of the StbM.*/
STATIC VAR(uint8,STBM_VAR) StbM_InitStatus = STBM_NOINIT;

#define STBM_STOP_SEC_VAR_INIT_8
#include <StbM_MemMap.h>


#define STBM_START_SEC_VAR_CLEARED_32
#include <StbM_MemMap.h>

#if (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON)
/** \brief Variable used to store the initialization state of the StbM.*/
STATIC VAR(uint32,STBM_VAR) StbM_TriggeredCustomerThreshold[STBM_NUMBER_OF_TRIGGERED_CUSTOMERS];
#endif /* STBM_TRIGGERED_CUSTOMERS_USED == STD_ON */

#if (STBM_TIMEOUTS_USED == STD_ON)
/** \brief Actual timeout value of all synchronized and offset time bases
 **
 ** Value of 0: Timeout disabled per configuration or timeout not active now.
 ** Value of 1+: Remaining time (in MainFunction invocation) until timeout occurs */
STATIC VAR(uint32, STBM_VAR) StbM_TimeBaseTimeout[STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES];
#endif /* STBM_TIMEOUTS_USED == STD_ON */



#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)

/** \brief Actual timeout value of all synchronized, offset and pure time bases
 **
 ** Value of 0: Timeout disabled per configuration or timeout not active now.
 ** Value of 1+: Remaining time (in MainFunction invocation) until timeout occurs */
STATIC VAR(uint32, STBM_VAR) StbM_SharedDataTimeout[STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];

#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


/** \brief Actual time since the Time Tuple was updated
 **/
STATIC VAR(uint32, STBM_VAR) StbM_UpdateTimeTupleCounter
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
/** \brief Holds the notification bits for the different Time Base related events
 **/
/* !LINKSTO StbM.SWS_StbM_00278.NotificationEvents,1 */
STATIC VAR(Atomic_t, STBM_VAR) StbM_TimeBaseNotificationEvents
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#define STBM_STOP_SEC_VAR_CLEARED_32
#include <StbM_MemMap.h>

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <StbM_MemMap.h>



#if ( STBM_SOURCE_TIMEBASES_USED == STD_ON)
  /** \brief Variable that holds the clone data and  Src Time base for the destination Time Bases */
STATIC VAR(StbM_CloneDataType, STBM_VAR) StbM_CloneDataArr[STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES+ STBM_NUMBER_OF_PURE_TIMEBASES];
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */


/* !LINKSTO StbM.EB.StbM_TimeStamps,1 */
#if (STBM_NVM_USED == STD_ON)
/** \brief Actual time tuple of all synchronized and offset time bases */
VAR(StbM_TimeTupleType, STBM_VAR) StbM_TimeStamps
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];
#else
/** \brief Actual time tuple of all synchronized and offset time bases */
STATIC VAR(StbM_TimeTupleType, STBM_VAR) StbM_TimeStamps
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];
#endif /* STBM_NVM_USED == STD_ON */

#if ((STBM_OS_COUNTER_USED == STD_ON) || (STBM_GPT_USED == STD_ON) || (STBM_OSGETTIMESTAMP_USED == STD_ON))
/** \brief Variable that holds the Virtual Local Time sources of a synchronized timebase */
STATIC VAR(StbM_VirtualLocalTimeSourcesType, STBM_VAR) StbM_VirtualLocalTimeSources;
#endif /* ((STBM_OS_COUNTER_USED == STD_ON) || (STBM_GPT_USED == STD_ON) || (STBM_OSGETTIMESTAMP_USED == STD_ON)) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON))

/** \brief The last Time Tuple which was received through StbM_BusSetGlobalTime, for synchronized and offset time bases */
STATIC VAR(StbM_TimeValidationTimeTupleType, STBM_VAR) StbM_LastReceivedTimeTuple
        [STBM_NUMBER_OF_SYNC_TIMEBASES];

#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)) */
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
/** \brief All Master Rate Correction related timers */
STATIC VAR(StbM_MasterRateCorrectionDataType, STBM_VAR) StbM_MasterRateCorrectionData
        [STBM_NUMBER_OF_MASTER_RATE_CORRECTION_TIMEBASES];
#endif /* STBM_MASTER_RATE_CORRECTION_USED == STD_ON */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

/** \brief expireTimes for all Notification Customers */
STATIC VAR(StbM_CustomerTimerExpireTimeNodeDataType, STBM_VAR) StbM_ExpireTimeData[STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS];

/** \brief this pointer always points to the FIRST element from the sorted doubly linked list */
STATIC P2VAR(StbM_CustomerTimerExpireTimeNodeDataType, AUTOMATIC, STBM_VAR) Head;

/** \brief this pointer always points to the LAST element from the sorted doubly linked list */
STATIC P2VAR(StbM_CustomerTimerExpireTimeNodeDataType, AUTOMATIC, STBM_VAR) Last;

#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
/** \brief All Slave Rate Correction related timers */
STATIC VAR(StbM_SlaveRateCorrectionDataType, STBM_VAR) StbM_SlaveRateCorrectionData
        [STBM_NUMBER_OF_SLAVE_RATE_CORRECTION_TIMEBASES];

/** \brief All Start Values necessary for Slave Rate Correction Calculation */
STATIC VAR(StbM_SlaveRateCorrectionStartValuesCfgType, STBM_VAR) StbM_SlaveRateCorrectionStartValues
        [STBM_NUMBER_OF_RATE_CORRECTION_INTERVALS];
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */

#if (STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
/** \brief Variable that holds the time leap informations */
STATIC VAR(StbM_TimeLeapType, STBM_VAR) StbM_TimeLeapInfo
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES];
#endif /* (STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON) */

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00308.Blocks,1 */
/** \brief Variable that holds the Time Recording for all sync time bases */
STATIC VAR(StbM_SyncRecordTableBlockType, STBM_VAR) StbM_SyncRecordTableBlocks[STBM_NUMBER_OF_SYNC_TIME_RECORD_BLOCKS];
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00311.Blocks,1 */
/** \brief Variable that holds the Time Recording for all offset time bases */
STATIC VAR(StbM_OffsetRecordTableBlockType, STBM_VAR) StbM_OffsetRecordTableBlocks[STBM_NUMBER_OF_OFFSET_TIME_RECORD_BLOCKS];
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
/** \brief Variable that holds the block counter for all time bases */
STATIC VAR(StbM_TimeRecordingInfoType, STBM_VAR) StbM_RecordTableBlocksInfo
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES];
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */



#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00468.MasterPort.CAN,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Master CANTSYN Time Domain */
STATIC VAR(StbM_CanTimeMasterMeasurementType, STBM_VAR) StbM_CanMasterTimingData[STBM_NUMBER_OF_SYNC_CANTSYN_MASTER_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Master CANTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_CanMasterTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00468.MasterPort.FR,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Master FRTSYN Time Domain */
STATIC VAR(StbM_FrTimeMasterMeasurementType, STBM_VAR) StbM_FrMasterTimingData[STBM_NUMBER_OF_SYNC_FRTSYN_MASTER_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Master FRTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_FrMasterTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00468.ETH.MappedToEthTSynTimeDomain,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Master ETHTSYN Time Domain */
STATIC VAR(StbM_EthTimeMasterMeasurementType, STBM_VAR) StbM_EthMasterTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Master ETHTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_EthMasterTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];

/* !LINKSTO StbM.SWS_StbM_00523.MappedToEthTSynTimeDomain,1 */
/* !LINKSTO StbM.SWS_StbM_00480,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Master Pdelay ETHTSYN Time Domain */
STATIC VAR(StbM_PdelayResponderMeasurementType, STBM_VAR) StbM_EthPdelayResponderTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Master Pdelay ETHTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */



#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00466.SlavePort.CAN,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Slave CANTSYN Time Domain */
STATIC VAR(StbM_CanTimeSlaveMeasurementType, STBM_VAR) StbM_CanSlaveTimingData[STBM_NUMBER_OF_SYNC_CANTSYN_SLAVE_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Slave CANTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_CanSlaveTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00466.SlavePort.FR,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Slave FRTSYN Time Domain */
STATIC VAR(StbM_FrTimeSlaveMeasurementType, STBM_VAR) StbM_FrSlaveTimingData[STBM_NUMBER_OF_SYNC_FRTSYN_SLAVE_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Slave FRTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_FrSlaveTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00466.ETH.MappedToEthTSynTimeDomain,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Slave ETHTSYN Time Domain */
STATIC VAR(StbM_EthTimeSlaveMeasurementType, STBM_VAR) StbM_EthSlaveTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Slave ETHTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_EthSlaveTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];

/* !LINKSTO StbM.SWS_StbM_00522.MappedToEthTSynTimeDomain,1 */
/* !LINKSTO StbM.SWS_StbM_00478,1 */
/** \brief Variable that holds the Time Recording for all SYNC StbM Time Bases, linked to a Slave Pdelay ETHTSYN Time Domain */
STATIC VAR(StbM_PdelayInitiatorMeasurementType, STBM_VAR) StbM_EthPdelayInitiatorTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];

/** \brief Variable that holds the Time Validation block counter for StbM Time Bases linked to a Slave Pdelay ETHTSYN Time Domain */
STATIC VAR(StbM_TimeValidationInfoType, STBM_VAR) StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[STBM_NUMBER_OF_SYNC_TIMEBASES];
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */


#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


/** \brief User data set by StbM_SetUserData */
STATIC VAR(StbM_UserDataType, STBM_VAR) StbM_UserData
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <StbM_MemMap.h>


#define STBM_START_SEC_CONST_UNSPECIFIED
#include <StbM_MemMap.h>

#if (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON)
/** \brief time stamp to Virtual Local Time Array conversion table
 *
 *  This table contains the converted value in nanosecondsHi and nanosecondsLo of:
 *  Index 0: 2^0s
 *  Index 1: 2^1s
 *  ...
 *  Index 15: 2^15s
 *
 *  Type sorted by nanosecondsHi, nanosecondsLo.
 */
 /* Deviation MISRAC2012-2 */
STATIC CONST(StbM_VirtualLocalTimeType, STBM_CONST) StbM_TimeStampToVRTConversionTable[32U] =
{
  {1000000000U, 0U},
  {2000000000U, 0U},
  {4000000000U, 0U},
  {3705032704U, 1U},
  {3115098112U, 3U},
  {1935228928U, 7U},
  {3870457856U, 14U},
  {3445948416U, 29U},
  {2596929536U, 59U},
  {898891776U, 119U},
  {1797783552U, 238U},
  {3595567104U, 476U},
  {2896166912U, 953U},
  {1497366528U, 1907U},
  {2994733056U, 3814U},
  {1694498816U, 7629U},
  {3388997632U, 15258U},
  {2483027968U, 30517U},
  {671088640U, 61035U},
  {1342177280U, 122070U},
  {2684354560U, 244140U},
  {1073741824U, 488281U},
  {2147483648U, 976562U},
  {0U, 1953125U},
  {0U, 3906250U},
  {0U, 7812500U},
  {0U, 15625000U},
  {0U, 31250000U},
  {0U, 62500000U},
  {0U, 125000000U},
  {0U, 250000000U},
  {0U, 500000000U}
};
#endif /* STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON */

/** \brief Virtual Local Time to time stamp Array conversion table
 *
 *  This table contains the converted value in nanoseconds, seconds, and secondsHi of:
 *  Index 0: 2^0s
 *  Index 1: 2^1s
 *  ...
 *  Index 15: 2^29s
 *
 *  Type sorted by nanoseconds, seconds, secondsHi.
 */
 /* Deviation MISRAC2012-2 */
STATIC CONST(StbM_TimeStampType, STBM_CONST) StbM_VRTtoTimeStampConversionTable[30U] =
{
  {0U, 294967296U, 4U, 0U},
  {0U, 589934592U, 8U, 0U},
  {0U, 179869184U, 17U, 0U},
  {0U, 359738368U, 34U, 0U},
  {0U, 719476736U, 68U, 0U},
  {0U, 438953472U, 137U, 0U},
  {0U, 877906944U, 274U, 0U},
  {0U, 755813888U, 549U, 0U},
  {0U, 511627776U, 1099U, 0U},
  {0U, 23255552U, 2199U, 0U},
  {0U, 46511104U, 4398U, 0U},
  {0U, 93022208U, 8796U, 0U},
  {0U, 186044416U, 17592U, 0U},
  {0U, 372088832U, 35184U, 0U},
  {0U, 744177664U, 70368U, 0U},
  {0U, 488355328U, 140737U, 0U},
  {0U, 976710656U, 281474U, 0U},
  {0U, 953421312U, 562949U, 0U},
  {0U, 906842624U, 1125899U, 0U},
  {0U, 813685248U, 2251799U, 0U},
  {0U, 627370496U, 4503599U, 0U},
  {0U, 254740992U, 9007199U, 0U},
  {0U, 509481984U, 18014398U, 0U},
  {0U, 18963968U, 36028797U, 0U},
  {0U, 37927936U, 72057594U, 0U},
  {0U, 75855872U, 144115188U, 0U},
  {0U, 151711744U, 288230376U, 0U},
  {0U, 303423488U, 576460752U, 0U},
  {0U, 606846976U, 1152921504U, 0U},
  {0U, 213693952U, 2305843009U, 0U}
};

#define STBM_STOP_SEC_CONST_UNSPECIFIED
#include <StbM_MemMap.h>


#define STBM_START_SEC_VAR_CLEARED_8
#include <StbM_MemMap.h>

#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
/** \brief The time base update counter of a time base */
/* !LINKSTO StbM.dsn.StbM_TimeBaseUpdateCounter.Range,1 */
/* !LINKSTO StbM.SWS_StbM_00351,1 */
STATIC VAR(uint8, STBM_VAR) StbM_TimeBaseUpdateCounter
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES];
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */


#if((STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) || (STBM_NUMBER_OF_PURE_TIMEBASES > 0U))
#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
/** \brief Variable used to monitor if new values for TimeTuple have been received for sync, offset and pure time bases */
STATIC VAR(uint8, STBM_VAR) StbM_NewTimeTupleValue
        [STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */
#endif /* ((STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) || (STBM_NUMBER_OF_PURE_TIMEBASES > 0U)) */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
STATIC VAR(boolean, STBM_VAR) StbM_IsGptTimeRunning;
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */

#define STBM_STOP_SEC_VAR_CLEARED_8
#include <StbM_MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define STBM_START_SEC_CODE
#include <StbM_MemMap.h>


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)

#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)

STATIC FUNC(void, STBM_CODE) StbM_UpdateSharedDataInMemory
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_TimeBaseStatusType currentTimeBaseStatus,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) currentHwCounter
)
{
  uint8 commonIdx = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIdx);

  /* Local variable use for storing the currentHwCounter */
  StbM_VirtualLocalTimeType lclCurrentHwCounter = {0U, 0U};

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(currentTimeBaseTimePtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentHwCounter != NULL_PTR,DET_INTERNAL_API_ID);

  /* The currentHwCounter is stored here in a local variable,
     in order to get rid of "discarded CONST qualifier" warning.
     Warning appeared because currentHwCounter has P2CONST and it's passed
     to StbM_VirtualLocalTimeToTimeStamp() which shall receive a P2VAR.
  */
  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(lclCurrentHwCounter, *currentHwCounter);


  /* check if time base needs to share data to memory */
  if (sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA)
  {
    StbM_TimeStampType currentOffset = {0U, 0U, 0U, 0U};
    StbM_TimeStampType currentHwCounterToTimeStamp = {0U, 0U, 0U, 0U};

#if (STBM_RATE_CORRECTION_USED)
    uint8 rcDataIndex;
    StbM_RateDeviationType rateDeviation = STBM_RATE_DEVIATION_DEFAULT_VALUE;
#endif /*  STBM_RATE_CORRECTION_USED */
#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
    /* check if rate correction is calculated for a master timebase */
    boolean masterRateCorrectionDisabled = STBM_MASTER_RATE_CORRECTION_DISABLED(commonIdx);
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
    /* check if the time base is an offset time base */
    if(!(STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId)))
    {
#endif /*  STBM_OFFSET_TIMEBASES_USED */

      /* convert currentHwCounter of type StbM_VirtualLocalTimeType to StbM_TimeStampType */
      StbM_VirtualLocalTimeToTimeStamp(&lclCurrentHwCounter, &currentHwCounterToTimeStamp);

      /* check if the Global Time is behind/after that the local Hw Time */
      if(StbM_TimeStampIsGreaterEqual(currentTimeBaseTimePtr, &currentHwCounterToTimeStamp))
      {
        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.SyncAndPure.Offset.Positive,2 */
        /* Global Time has a greater value, we need to subtract GlobalTime - HwTime */
        (void)StbM_SubtractTimeStamps
            (
                currentTimeBaseTimePtr,
                &currentHwCounterToTimeStamp,
                &currentOffset
            );

        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.Sign,2 */
        /* set the sign as positive, so the users that read from the shared memory location
             know that they should add the offset to the HwTime */
        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].OffsetSign = STBM_SIGN_IS_POSITIVE;
      }
      else
      {
        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.SyncAndPure.Offset.Negative,2 */
        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.Sign,2 */
        /* Global Time has a smaller value, we need to subtract HwTime - GlobalTime */
        (void)StbM_SubtractTimeStamps
            (
                &currentHwCounterToTimeStamp,
                currentTimeBaseTimePtr,
                &currentOffset
            );

        /* set the sign as negative, so the users that read from the shared memory location
             know that they should subtract the offset from the HwTime */
        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].OffsetSign = STBM_SIGN_IS_NEGATIVE;
      }

#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
    }
    else
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.Offset,2 */
       /* time base is an offset time base */
       /* we need to add the current Offset Time Base values, there is no need to have
          the HwTime as reference */
       STBM_ASSIGN_TIMESTAMP(currentOffset, StbM_TimeStamps[commonIdx].globalTime);
       currentTimeBaseStatus = StbM_TimeStamps[commonIdx].globalTime.timeBaseStatus;
    }
#endif /*  STBM_OFFSET_TIMEBASES_USED */

      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.WriteBegin,2 */
      /* increment the 'begin' counter, this will signal the user that
         data is currently being written */
      Atomics_ThreadFence();
      StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].WriteBeginCnt++;
      Atomics_ThreadFence();

      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.SyncAndPure.Offset.Positive,2 */
      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.SyncAndPure.Offset.Negative,2 */
      /* assign offset */
      STBM_ASSIGN_TIMESTAMP(StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].OffsetTime, currentOffset);

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
      if(masterRateCorrectionDisabled == FALSE)
      {
        /* get index for the StbM_MasterRateCorrectionData[] array */
        rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonIdx);
        /* update rate deviation */
        rateDeviation = StbM_MasterRateCorrectionData[rcDataIndex].rateDev;
      }
      /* it shall be done for a slave */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
      else
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
      {
        /* get index for the StbM_SlaveRateCorrectionData[] array */
        rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIdx);
        /* update rate deviation */
        rateDeviation = StbM_SlaveRateCorrectionData[rcDataIndex].rateDev;
      }
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_RATE_CORRECTION_USED)
      /* if the rate deviation has an invalid values/ has not been calculated yet,
         set a value of "0", which is equivalent to a rate correction of 1, since the
         user might use the value all the time in the calculation */
      if(rateDeviation == STBM_RATE_DEVIATION_INVALID_VALUE)
      {
        rateDeviation = STBM_RATE_DEVIATION_DEFAULT_VALUE;
      }

      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.RateDeviation,2 */
      /* update rate deviation */
      StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].RateDeviation = rateDeviation;
#endif /*  STBM_RATE_CORRECTION_USED */

      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.TimeBaseStatus,2 */
      /* update the status of the current time base */
      StbM_UpdateSharedStatusInMemory(sharedMemoryIndex, currentTimeBaseStatus);

      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.WriteEnd,2 */
      /* increment the 'end' counter, this will signal the user that
         data has been written */
      Atomics_ThreadFence();
      StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].WriteEndCnt++;
      Atomics_ThreadFence();


  }

}


STATIC FUNC(void, STBM_CODE) StbM_UpdateSharedStatusInMemory
(
  uint16 sharedMemoryIndex,
  StbM_TimeBaseStatusType currentTimeBaseStatus
)
{


  /* check if time base needs to share data to memory */
  if (sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA)
  {
    /* update current status */
    StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].OffsetTime.timeBaseStatus = currentTimeBaseStatus;
  }

}


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_UpdateSharedRateDeviationInMemory
(
  uint16 sharedMemoryIndex,
  uint8 rcDataIndex
)
{

  /* check if time base needs to share data to memory */
  if (sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA)
  {
    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.WriteBegin,2 */
    /* increment the 'begin' counter, this will signal the user that
       data is currently being written */
    Atomics_ThreadFence();
    StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].WriteBeginCnt++;
    Atomics_ThreadFence();

    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.RateDeviation,2 */
    /* update rate deviation */
    StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].RateDeviation = StbM_SlaveRateCorrectionData[rcDataIndex].rateDev;

    /* increment the 'end' counter, this will signal the user that
       data has been written */
    Atomics_ThreadFence();
    StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].WriteEndCnt++;
    Atomics_ThreadFence();
  }

}
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */



#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)

STATIC FUNC(void, STBM_CODE) StbM_UpdateGlobalTimeInSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
)
{

  /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.TimeBaseStatus,1 */
  /* update the status */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX] = StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus;
  /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.TimeTuple,1 */
  /* update TG */
  /* TG - nanoseconds */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 1U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].globalTime.nanoseconds & STBM_32BIT_MASK3_MSB) >> 24U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 2U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].globalTime.nanoseconds & STBM_32BIT_MASK2) >> 16U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 3U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].globalTime.nanoseconds & STBM_32BIT_MASK1) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 4U] = (uint8)(StbM_TimeStamps[commonIndex].globalTime.nanoseconds & STBM_32BIT_MASK0_LSB);
  /* TG - seconds */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 5U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].globalTime.seconds & STBM_32BIT_MASK3_MSB) >> 24U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 6U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].globalTime.seconds & STBM_32BIT_MASK2) >> 16U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 7U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].globalTime.seconds & STBM_32BIT_MASK1) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 8U] = (uint8)(StbM_TimeStamps[commonIndex].globalTime.seconds & STBM_32BIT_MASK0_LSB);
  /* TG - secondsHi */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 9U] = (uint8)((uint16)(StbM_TimeStamps[commonIndex].globalTime.secondsHi & STBM_16BIT_MASK1_MSB) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 10U] = (uint8)(StbM_TimeStamps[commonIndex].globalTime.secondsHi & STBM_16BIT_MASK0_LSB);

}

STATIC FUNC(void, STBM_CODE) StbM_UpdateVirtualLocalTimeInSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
)
{

  /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.TimeTuple,1 */
  /* update VLT */
  /* VLT - nanosecondsLo */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsLo & STBM_32BIT_MASK3_MSB) >> 24U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 1U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsLo & STBM_32BIT_MASK2) >> 16U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 2U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsLo & STBM_32BIT_MASK1) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 3U] = (uint8)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsLo & STBM_32BIT_MASK0_LSB);
  /* VLT - nanosecondsHi */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 4U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsHi & STBM_32BIT_MASK3_MSB) >> 24U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 5U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsHi & STBM_32BIT_MASK2) >> 16U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 6U] = (uint8)((uint32)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsHi & STBM_32BIT_MASK1) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 7U] = (uint8)(StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsHi & STBM_32BIT_MASK0_LSB);

}

STATIC FUNC(void, STBM_CODE) StbM_UpdateTimeTupleInSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
)
{

  /* update global time */
  StbM_UpdateGlobalTimeInSharedMemory(commonIndex, timeBaseStartIndex);
  /* update virtual local time */
  StbM_UpdateVirtualLocalTimeInSharedMemory(commonIndex, timeBaseStartIndex);

}

#if ((STBM_MASTER_RATE_CORRECTION_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_UpdateRateDevAndRateCorrInSharedMemory
(
  P2CONST(uint32, AUTOMATIC, STBM_VAR) rateCorrection,
  P2CONST(StbM_RateDeviationType, AUTOMATIC, STBM_VAR) rateDeviation,
  uint16 timeBaseStartIndex
)
{
  uint16 tempRateDev = 0U;


  tempRateDev = (uint16) *rateDeviation;

  /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.RateDeviation,1 */
  /* update rate deviation */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATEDEVIATION_STARTINDEX] = (uint8)((uint16)(tempRateDev & STBM_16BIT_MASK1_MSB) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATEDEVIATION_STARTINDEX + 1U] = (uint8)((uint16)(tempRateDev & STBM_16BIT_MASK0_LSB));

  /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.RateCorrection,1 */
  /* update rate correction */
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX] = (uint8)((uint32)(*rateCorrection & STBM_32BIT_MASK3_MSB) >> 24U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 1U] = (uint8)((uint32)(*rateCorrection & STBM_32BIT_MASK2) >> 16U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 2U] = (uint8)((uint32)(*rateCorrection & STBM_32BIT_MASK1) >> 8U);
  StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 3U] = (uint8)(*rateCorrection & STBM_32BIT_MASK0_LSB);

}
#endif /* ((STBM_MASTER_RATE_CORRECTION_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)) */

#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */


#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_ReadGlobalTimeFromSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
)
{

   /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.UseSharedVariable.CurrentTimeBaseData.TimeBaseStatus,1 */
   /* save time base status */
   StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus = StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX];

  /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.UseSharedVariable.CurrentTimeBaseData.TimeTuple,1 */
   /* save current TG values for the SYNC time base */
   StbM_TimeStamps[commonIndex].globalTime.nanoseconds = (uint32)(((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 1U]) << 24) | \
                                                                  ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 2U]) << 16) | \
                                                                  ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 3U]) << 8) | \
                                                                   (uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 4U]));
   StbM_TimeStamps[commonIndex].globalTime.seconds = (uint32)(((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 5U]) << 24) | \
                                                              ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 6U]) << 16) | \
                                                              ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 7U]) << 8) | \
                                                               (uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 8U]));
   StbM_TimeStamps[commonIndex].globalTime.secondsHi = (uint16)(((uint16)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 9U]) << 8) | \
                                                                 (uint16)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 10U]));

}

STATIC FUNC(void, STBM_CODE) StbM_ReadVirtualLocalTimeFromSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
)
{

   /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.UseSharedVariable.CurrentTimeBaseData.TimeTuple,1 */
   /* save current VLT values for the SYNC time base */
   StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsLo = (uint32)(((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX]) << 24) | \
                                                                          ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 1U]) << 16) | \
                                                                          ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 2U]) << 8) | \
                                                                           (uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 3U]));
   StbM_TimeStamps[commonIndex].virtualLocalTime.nanosecondsHi = (uint32)(((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 4U]) << 24) | \
                                                                          ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 5U]) << 16) | \
                                                                          ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 6U]) << 8) | \
                                                                           (uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 7U]));

}


STATIC FUNC(void, STBM_CODE) StbM_ReadDataFromSharedMemory
(
  uint8 commonIndex,
  uint16 timeBaseStartIndex
)
{
#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
   uint8 rcDataIndex = 0U;
  StbM_RateDeviationType lclMasterRateDeviation = 0U;
#endif /* (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */


   /* read TG from shared memory */
   StbM_ReadGlobalTimeFromSharedMemory(commonIndex, timeBaseStartIndex);
   /* read VLT from shared memory */
   StbM_ReadVirtualLocalTimeFromSharedMemory(commonIndex, timeBaseStartIndex);

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
   /* check if time base has master rate correction activated */
   if(STBM_MASTER_RATE_CORRECTION_DISABLED(commonIndex) == FALSE)
   {
     StbM_RateDeviationType tempMasterRateDev = 0U;
     /* get index for the StbM_MasterRateCorrectionData[] array */
     rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonIndex);

     /* read master rate reviation from shared memory */
     lclMasterRateDeviation = (uint16)(((uint16)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATEDEVIATION_STARTINDEX]) << 8) | \
                                        (uint16)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATEDEVIATION_STARTINDEX + 1U]));

     tempMasterRateDev = (StbM_RateDeviationType) lclMasterRateDeviation;

     /* copy master rate deviation from shared memory and use it, only if it has a valid value */
     if(tempMasterRateDev != STBM_RATE_DEVIATION_INVALID_VALUE)
     {
       /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.UseSharedVariable.CurrentTimeBaseData.RateDeviation,1 */
       /* update rate deviation */
       StbM_MasterRateCorrectionData[rcDataIndex].rateDev = tempMasterRateDev;

       /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.UseSharedVariable.CurrentTimeBaseData.RateCorrection,1 */
       /* update rate correction */
       StbM_MasterRateCorrectionData[rcDataIndex].rrc = (uint32)(((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX]) << 24) | \
                                                                 ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 1U]) << 16) | \
                                                                 ((uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 2U]) << 8) | \
                                                                  (uint32)(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 3U]));
     }
   }
#endif /* (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */

}
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */


#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


/* !LINKSTO StbM.SWS_StbM_91006,1 */
/* !LINKSTO StbM.dsn.ExclusiveArea_VirtualLocalTimeOs,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETCURRENTVIRTUALLOCALTIME_ENTRY(timeBaseId, localTimePtr);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetCurrentVirtualLocalTime,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTVIRTUALLOCALTIME, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00445,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTVIRTUALLOCALTIME, STBM_E_PARAM);
  }
  else if (localTimePtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00444,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTVIRTUALLOCALTIME, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* !LINKSTO StbM.SWS_StbM_00437.Sync.ReturnVLT,1 */
    /* !LINKSTO StbM.SWS_StbM_00437.Pure.ReturnVLT,1 */
    /* !LINKSTO StbM.SWS_StbM_00437.Offset.ReturnVLT,1 */
    /* !LINKSTO StbM.SWS_StbM_00437.Sync.E_NOT_OK,1 */
    /* !LINKSTO StbM.SWS_StbM_00437.Pure.E_NOT_OK,1 */
    /* !LINKSTO StbM.SWS_StbM_00437.Offset.E_NOT_OK,1 */
    retval = StbM_GetCurrentVirtualLocalTimeNoChecks(timeBaseId, localTimePtr);
  }

  DBG_STBM_GETCURRENTVIRTUALLOCALTIME_EXIT(retval, timeBaseId, localTimePtr);

  return retval;
}

/* !LINKSTO StbM.dsn.ExclusiveArea_VirtualLocalTimeOs,1 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTimeNoChecks
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  uint8 commonIndex;
  /* get underlaying sync or pure */
  timeBaseId = STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX(timeBaseId);
  /* get the common index underlying synchronized time base (timeBaseId might be an offset), or pure common index */
  /* Deviation TASKING-1 */
  commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

  /* obtain our time. */
  retval = StbM_SyncTimeBaseCfg[commonIndex].virtualLocalTimeGetterFctPtr
  (
    timeBaseId,
    localTimePtr
  );


  return retval;
}

/* !LINKSTO StbM.dsn.ExclusiveArea_VirtualLocalTimeOs,1 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTimeNoDet
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint8* detectedDET,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(localTimePtr != NULL_PTR,DET_INTERNAL_API_ID);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    *detectedDET = STBM_E_UNINIT;
  }
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00435.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00446.NotConfigured,1 */
    *detectedDET = STBM_E_PARAM;
  }
  else
#else
  TS_PARAM_UNUSED(detectedDET);
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* get common index */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* store current Time Tuple values */
    STBM_ASSIGN_TIMESTAMP(*currentTimeTupleGlobalPtr, StbM_TimeStamps[commonIndex].globalTime);

    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*currentTimeTupleVLTPtr, StbM_TimeStamps[commonIndex].virtualLocalTime);

    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    retval = StbM_GetCurrentVirtualLocalTimeNoChecks(timeBaseId, localTimePtr);

    /* Defensive programming */
    STBM_POSTCONDITION_ASSERT(localTimePtr != NULL_PTR,DET_INTERNAL_API_ID);
  }


  return retval;
}

/* !LINKSTO StbM.SWS_StbM_91005,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_BusGetCurrentTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) globalTimePtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
  uint8 detectedDET = 0U;

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  uint8 commonIdx = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIdx);
  uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  DBG_STBM_BUSGETCURRENTTIME_ENTRY(timeBaseId, localTimePtr, timeStampPtr, userDataPtr);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  /* check if time base needs to share data to memory */
  if((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[commonIdx].timeBaseRoleSharedData == STBM_TIME_BASE_CONSUMER_SHARED_DATA))
  {
    /* get array start index for this timebase */
    timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

    /* enter critical section */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* before using time base data from shared memory, check that it was succesfully written */
    if(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX] == StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX])
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.When.StbM_BusGetCurrentTime,1 */
      /* read data from shared memory */
      StbM_ReadDataFromSharedMemory(commonIdx, timeBaseStartIndex);

      /* reload the update counter */
      StbM_UpdateTimeTupleCounter[commonIdx] = STBM_UPDATE_COUNTER_VALUE;
    }

    if(STBM_FLAG_IS_SET(StbM_TimeStamps[commonIdx].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG))
    {
      /* if data is ready to be read, read it, or if data is not ready to be read, read the last time base data which was written in the shared memory */
      retval = E_OK;
    }
    else
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.IfNotSuccessfullyUpdated.StbM_BusGetCurrentTime,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.If_GTSBit_NotSet.StbM_BusGetCurrentTime,1 */
      /* no time base data was written in the shared memory - return E_NOT_OK */
    }

    /* exit critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }
  else
  {
    /* if timebase has no shared data activated, return E_OK */
    retval = E_OK;
  }

  /* check if data was successfully read from shared memory */
  if(E_OK == retval)
  {
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    /* Get current Virtual Local Time */
    /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Os,1 */
    /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Ethernet,1 */
    /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Gpt,1 */
    retval = StbM_GetCurrentVirtualLocalTimeNoDet(timeBaseId, &detectedDET, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
    if(detectedDET == STBM_E_UNINIT)
    {
      retval = E_NOT_OK;
      /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_BusGetCurrentTime,1 */
      STBM_DET_REPORTERROR(STBM_API_BUSGETCURRENTTIME, STBM_E_UNINIT);
    }
    else if (detectedDET == STBM_E_PARAM)
    {
      retval = E_NOT_OK;
      /* !LINKSTO StbM.SWS_StbM_00435.TimeBaseId,1 */
      /* !LINKSTO StbM.SWS_StbM_00446.NotConfigured,1 */
      STBM_DET_REPORTERROR(STBM_API_BUSGETCURRENTTIME, STBM_E_PARAM);
    }
    else if ((STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId)) || (STBM_IS_PURE_TIMEBASE_ID(timeBaseId)))
    {
      retval = E_NOT_OK;
      /* !LINKSTO StbM.SWS_StbM_00446.OffsetTimeBaseId,1 */
      /* !LINKSTO StbM.SWS_StbM_00446.PureTimeBaseId,1 */
      STBM_DET_REPORTERROR(STBM_API_BUSGETCURRENTTIME, STBM_E_PARAM);
    }
    else if (globalTimePtr == NULL_PTR)
    {
      retval = E_NOT_OK;
      /* !LINKSTO StbM.SWS_StbM_00447.globalTimePtr,1 */
      STBM_DET_REPORTERROR(STBM_API_BUSGETCURRENTTIME, STBM_E_PARAM_POINTER);
    }
    else if (localTimePtr == NULL_PTR)
    {
      retval = E_NOT_OK;
      /* !LINKSTO StbM.SWS_StbM_00447.localTimePtr,1 */
      STBM_DET_REPORTERROR(STBM_API_BUSGETCURRENTTIME, STBM_E_PARAM_POINTER);
    }
    else if (userData == NULL_PTR)
    {
      retval = E_NOT_OK;
      /* !LINKSTO StbM.SWS_StbM_00447.userData,1 */
      STBM_DET_REPORTERROR(STBM_API_BUSGETCURRENTTIME, STBM_E_PARAM_POINTER);
    }
    else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* !LINKSTO StbM.SWS_StbM_00434.VLT.NotRetrieved.StbM_BusGetCurrentTime.E_NOT_OK,1 */
      if(E_OK == retval)
      {
        StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};
        /* First step: update synchronized time base with the actual time. */
        retval = StbM_GetTime(timeBaseId, &timeStampLocalTime, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

        /* return time information.
         * In case of requesting a synchronized time base: write the data immediately to
         * the out parameter.
         */
        /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Os,1 */
        /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Ethernet,1 */
        /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Gpt,1 */
        /* !LINKSTO StbM.EB.BusGetCurrentTime.E_NOT_OK,1 */
        /*
         * Check if the time was successfully retrieved:
         * - EthIf_GetCurrentTime returned E_OK
         * - TimeQual had a value different from ETH_UNCERTAIN and ETH_INVALID
         */
        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.EthIf_GetCurrentTime.E_NOT_OK,2 */
        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.EthIf_GetCurrentTime.ETH_UNCERTAIN,2 */
        if (retval == E_OK)
        {
          uint8 index = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

          /* enter critical section */
          /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeStamps,1 */
          /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_UserData,1 */
          /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
          SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

          /* assign Virtual Local Time part of the Main Tuple */
          STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*localTimePtr, localTime);
          /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Os,1 */
          /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Ethernet,1 */
          /* !LINKSTO StbM.SWS_StbM_00435.TimeTuple.VLT.DerivedFrom.Gpt,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_SetGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_UpdateGlobalTime,1 */
          STBM_ASSIGN_TIMESTAMP(*globalTimePtr, timeStampLocalTime);

          /* !LINKSTO StbM.SWS_StbM_00435.TimeBaseStatus,1 */
          /* copy timeBaseStatus member */
          globalTimePtr->timeBaseStatus = StbM_TimeStamps[index].globalTime.timeBaseStatus;

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
          /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_BusGetCurrentTime,2 */
          StbM_UpdateSharedDataInMemory(timeBaseId, StbM_TimeStamps[index].globalTime.timeBaseStatus, &timeStampLocalTime, &localTime);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

          /* !LINKSTO StbM.SWS_StbM_00435.UserData,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_SetGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_UpdateGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_SetUserData,1 */
          /* initialize the user data address with the user data of this time base */
          userData->userDataLength = StbM_UserData[index].userDataLength;
          userData->userByte0      = StbM_UserData[index].userByte0;
          userData->userByte1      = StbM_UserData[index].userByte1;
          userData->userByte2      = StbM_UserData[index].userByte2;

          /* leave critical section */
          SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
        }
      }
    }

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  }
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  DBG_STBM_BUSGETCURRENTTIME_EXIT(retval, timeBaseId, localTimePtr, timeStampPtr, userDataPtr);

  return retval;
} /* StbM_BusGetCurrentTime */




STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeCommon
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;

  StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobalSync = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLTSync = {0U, 0U};
#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
  StbM_TimeStampType currentTimeTupleGlobalOffset = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLTOffset = {0U, 0U};
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */

  /* get the underlying synchronized time base (timeBaseId might be an offset) */
  uint8 underlyingTimeBaseId = STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX(timeBaseId);
  /* get common index */
  /* Deviation TASKING-1 */
  uint8 commonIndexSync = STBM_TIMEBASE_ID_TO_COMMON_INDEX(underlyingTimeBaseId);
  /* get common index sync/offset */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIndex);
  uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)

  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* check if time base needs to share data to memory */
  if((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[commonIndex].timeBaseRoleSharedData == STBM_TIME_BASE_CONSUMER_SHARED_DATA))
  {
    /* get array start index for this timebase */
    timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

    /* before using time base data from shared memory, check that it was succesfully written */
    if(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX] == StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX])
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.When.StbM_GetCurrentTime,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.When.StbM_GetCurrentTimeExtended,1 */
      /* read data from shared memory */
      StbM_ReadDataFromSharedMemory(commonIndex, timeBaseStartIndex);

      /* reload the update counter */
      StbM_UpdateTimeTupleCounter[commonIndex] = STBM_UPDATE_COUNTER_VALUE;
    }

    if(STBM_FLAG_IS_SET(StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG))
    {
      /* if data is ready to be read, read it, or if data is not ready to be read, read the last time base data which was written in the shared memory */
      retval = E_OK;
    }
    else
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.IfNotSuccessfullyUpdated.StbM_GetCurrentTime,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.If_GTSBit_NotSet.StbM_GetCurrentTime,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.IfNotSuccessfullyUpdated.StbM_GetCurrentTimeExtended,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.If_GTSBit_NotSet.StbM_GetCurrentTimeExtended,1 */
      /* no time base data was written in the shared memory - return E_NOT_OK */
    }
  }
  else
  {
    /* if timebase has no shared data activated, return E_OK */
    retval = E_OK;
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* check if data was successfully read from shared memory */
  if(E_OK == retval)
  {
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* store current Time Tuple values for the SYNC time base */
    STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobalSync, StbM_TimeStamps[commonIndexSync].globalTime);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLTSync, StbM_TimeStamps[commonIndexSync].virtualLocalTime);
#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
    /* store current Time Tuple values for the OFFSET time base */
    STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobalOffset, StbM_TimeStamps[commonIndex].globalTime);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLTOffset, StbM_TimeStamps[commonIndex].virtualLocalTime);
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */

    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* Get current Virtual Local Time */
    retval = StbM_GetCurrentVirtualLocalTimeNoChecks(timeBaseId, &localTime);

    /* open another exclusive are since obtaining the virtual local time
       needs to be done with highest priority, and as fast as possible */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedData,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
    /* !LINKSTO StbM.EB.RateCorrectionCalcualtion.OutsideOfBusSetGlobalTime,1 */
    StbM_HandleSlaveRateCorrection(commonIndex);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* !LINKSTO StbM.SWS_StbM_00434.VLT.NotRetrieved.StbM_GetCurrentTime.E_NOT_OK,1 */
    /* !LINKSTO StbM.SWS_StbM_00434.VLT.NotRetrieved.StbM_GetCurrentTimeExtended.E_NOT_OK,1 */
    if(E_OK == retval)
    {
      /* First step: update synchronized time base with the actual time. */
      retval = StbM_GetTime(underlyingTimeBaseId, &timeStampLocalTime, &currentTimeTupleGlobalSync, &currentTimeTupleVLTSync, &localTime);

      /* Second step: return time information.
       * In case of requesting a synchronized time base: write the data immediately to
       * the out parameter.
       * In case of requesting an offset time base: Calculate the sum of the requested
       * offset time base and the underlying sync time base.
       */
      /* !LINKSTO StbM.EB.GetCurrentTime.E_NOT_OK.Sync,1 */
      /* !LINKSTO StbM.EB.GetCurrentTimeExtended.E_NOT_OK.Sync,1 */
      if (E_OK == retval)
      {

#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
        if (STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
        {
          retval = StbM_GetOffsetTimeBaseTime(timeBaseId, timeStamp, &timeStampLocalTime, &currentTimeTupleGlobalOffset, &currentTimeTupleVLTOffset, &localTime);
        }
        else
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */
        {
          /* enter critical section */
          /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
          SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

          /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.timeOfTheTimeBase.derivedFromOs,1 */
          /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.timeOfTheTimeBase.derivedFromEthTSyn,1 */
          /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.timeOfTheTimeBase.derivedFromGpt,1 */
          STBM_ASSIGN_TIMESTAMP(*timeStamp, timeStampLocalTime);

          /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.TimeBaseStatus,1 */
          /* copy timeBaseStatus member */
          timeStamp->timeBaseStatus = StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus;

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
          /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_GetCurrentTime,2 */
          StbM_UpdateSharedDataInMemory(timeBaseId, StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, &timeStampLocalTime, &localTime);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

          /* leave critical section */
          SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
        }

#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
      if(E_OK == retval)
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */
        {
          /* enter critical section */
          SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

          /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.UserData,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_SetGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_UpdateGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTime.UserData.setBy.StbM_SetUserData,1 */
          /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.UserData,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTimeExtended.UserData.setBy.StbM_SetGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTimeExtended.UserData.setBy.StbM_UpdateGlobalTime,1 */
          /* !LINKSTO StbM.SWS_StbM_00398.StbM_GetCurrentTimeExtended.UserData.setBy.StbM_SetUserData,1 */
          /* initialize the user data address with the user data of this time base */
          userData->userDataLength = StbM_UserData[commonIndex].userDataLength;
          userData->userByte0      = StbM_UserData[commonIndex].userByte0;
          userData->userByte1      = StbM_UserData[commonIndex].userByte1;
          userData->userByte2      = StbM_UserData[commonIndex].userByte2;

          /* leave critical section */
          SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
        }
      }
    }

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  }
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  return retval;
} /* StbM_GetCurrentTimeCommon */



/* !LINKSTO StbM.SWS_StbM_00195,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETCURRENTTIME_ENTRY(timeBaseId, timeStamp, userData);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetCurrentTime,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIME, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00196,1 */
    /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00177.StbM_GetCurrentTime.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTime.PureTimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIME, STBM_E_PARAM);
  }
  else if (timeStamp == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00197,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIME, STBM_E_PARAM_POINTER);
  }
  else if (userData == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00197,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIME, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* get normal current time stamp */
    retval = StbM_GetCurrentTimeCommon(timeBaseId, timeStamp, userData);
  }

  DBG_STBM_GETCURRENTTIME_EXIT(retval, timeBaseId, timeStamp, userData);
  return retval;
} /* StbM_GetCurrentTime */





#if (STBM_GETCURRENTTIMEEXTENDED_USED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00200,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeExtended
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampExtendedType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETCURRENTTIMEEXTENDED_ENTRY(timeBaseId, timeStamp, userData);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetCurrentTimeExtended,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIMEEXTENDED, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.PureTimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00177.StbM_GetCurrentTimeExtended.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00201.NotConfigured,1 */
    /* !LINKSTO StbM.SWS_StbM_00201.WithinReservedRange,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIMEEXTENDED, STBM_E_PARAM);
  }
  else if (timeStamp == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00202.Invalid.timeStamp,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIMEEXTENDED, STBM_E_PARAM_POINTER);
  }
  else if (userData == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00202.userData,1 */
    STBM_DET_REPORTERROR(STBM_API_GETCURRENTTIMEEXTENDED, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    StbM_TimeStampType normalTimeStamp = {0U, 0U, 0U, 0U};

    /* get normal current time stamp */
    retval = StbM_GetCurrentTimeCommon(timeBaseId, &normalTimeStamp, userData);

    if(E_OK == retval)
    {
      /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.timeOfTheTimeBase.derivedFromOs,1 */
      /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.timeOfTheTimeBase.derivedFromEthTSyn,1 */
      /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.timeOfTheTimeBase.derivedFromGpt,1 */
      /* convert normal timeStamp of type StbM_TimeStampType into extended timeStamp of type StbM_TimeStampExtendedType */
      STBM_ASSIGN_TIMESTAMP_TO_EXTENDEDTIMESTAMP(*timeStamp, normalTimeStamp);

      /* !LINKSTO StbM.SWS_StbM_00173.StbM_GetCurrentTimeExtended.TimeBaseStatus,1 */
      /* GLOBAL_TIME_BIT shall only be set if it is set in both sync and offset */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.GLOBAL_TIME_BASE.NoSync,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.GLOBAL_TIME_BASE.Sync,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.TIMEOUT.NoTimeout,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.TIMEOUT.TimeoutOccured,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.SYNC_TO_GATEWAY.NotBasedOnGateway,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.SYNC_TO_GATEWAY.BasedOnGateway,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.TIMELEAP_FUTURE.NoTimeleap,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.TIMELEAP_FUTURE.Timeleap,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.TIMELEAP_PAST.NoTimeleap,1 */
      /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTimeExtended.TIMELEAP_PAST.Timeleap,1 */
      /* copy timeBaseStatus member and set TIMEOUT, SYNC_TO_GATEWAY, TIMELEAP_PAST and TIMELEAP_FUTURE bits if any of sync or offset has the bits set */
      TS_AtomicAssign8(timeStamp->timeBaseStatus, normalTimeStamp.timeBaseStatus);

    }
  }

  DBG_STBM_GETCURRENTTIMEEXTENDED_EXIT(retval, timeBaseId, timeStamp, userData);
  return retval;
} /* StbM_GetCurrentTimeExtended */
#endif /* (STBM_GETCURRENTTIMEEXTENDED_USED == STD_ON) */



#if (STBM_FRESHNESS_USED == STD_ON)

#if (STBM_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(boolean, STBM_CODE) StbM_IsFreshnessValueIdConfigured(uint16 freshnessValueId)
{
  boolean freshnessValueIdFound = FALSE;
  uint8 idx;


  /* Deviation TASKING-4 */
  for(idx = 0U; idx < STBM_NUMBER_OF_FRESHNESSVALUES; idx++)
  {
    if(StbM_FreshnessValueIdsCfg[idx].freshnessValueId == freshnessValueId)
    {
      freshnessValueIdFound = TRUE;
      break;
    }
  }


  return freshnessValueIdFound;
}
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */



#if (STBM_MASTER_FRESHNESS_USED == STD_ON)

/* !LINKSTO StbM.R22-11.SWS_StbM_00541,1 */
/* !LINKSTO StbM.R22-11.SWS_StbM_91018,1 */
#if (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_TXFRESHNESS_USED == STD_ON)) || (STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON))
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTxFreshness
(
  uint16 StbMFreshnessValueId,
  P2VAR(uint32, AUTOMATIC, STBM_APPL_DATA) StbMFreshnessValueLength,
  P2VAR(uint8, AUTOMATIC, STBM_APPL_DATA) StbMFreshnessValue
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETTXFRESHNESS_ENTRY(StbMFreshnessValueId, StbMFreshnessValue, StbMFreshnessValueLength);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.EB.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetTxFreshness,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESS, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if(FALSE == StbM_IsFreshnessValueIdConfigured(StbMFreshnessValueId))
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00544,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESS, STBM_E_PARAM);
  }
  else if(StbMFreshnessValue == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00545.StbMFreshnessValue.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESS, STBM_E_PARAM_POINTER);
  }
  else if(StbMFreshnessValueLength == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00545.StbMFreshnessValueLength.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESS, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    retval = StbM_GetTxFreshnessLcl(StbMFreshnessValueId, StbMFreshnessValueLength, StbMFreshnessValue);
  }

  DBG_STBM_GETTXFRESHNESS_EXIT(retval, StbMFreshnessValueId, StbMFreshnessValue, StbMFreshnessValueLength);
  return retval;
} /* StbM_GetTxFreshness */
#endif /* (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_TXFRESHNESS_USED == STD_ON)) || (STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON)) */


/* !LINKSTO StbM.R22-11.SWS_StbM_00541,1 */
/* !LINKSTO StbM.R22-11.SWS_StbM_91014,1 */
#if (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_TXFRESHNESSTRUNC_USED == STD_ON)) || ((STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON) && (STBM_TXFRESHNESSTRUNC_CSINTERFACE_USED == STD_ON)))
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTxFreshnessTruncData
(
  uint16 StbMFreshnessValueId,
  P2VAR(uint32, AUTOMATIC, STBM_APPL_DATA) StbMFreshnessValueLength,
  P2VAR(uint32, AUTOMATIC, STBM_APPL_DATA) StbMTruncatedFreshnessValueLength,
  P2VAR(uint8, AUTOMATIC, STBM_APPL_DATA) StbMFreshnessValue,
  P2VAR(uint8, AUTOMATIC, STBM_APPL_DATA) StbMTruncatedFreshnessValue
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETTXFRESHNESSTRUNCDATA_ENTRY(StbMFreshnessValueId, StbMFreshnessValue, StbMFreshnessValueLength, StbMTruncatedFreshnessValue, StbMTruncatedFreshnessValueLength);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.EB.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetTxFreshnessTruncData,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESSTRUNCDATA, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if(FALSE == StbM_IsFreshnessValueIdConfigured(StbMFreshnessValueId))
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00546,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESSTRUNCDATA, STBM_E_PARAM);
  }
  else if(StbMFreshnessValue == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00547.StbMFreshnessValue.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESSTRUNCDATA, STBM_E_PARAM_POINTER);
  }
  else if (StbMFreshnessValueLength == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00547.StbMFreshnessValueLength.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESSTRUNCDATA, STBM_E_PARAM_POINTER);
  }
  else if(StbMTruncatedFreshnessValue == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00547.StbMTruncatedFreshnessValue.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESSTRUNCDATA, STBM_E_PARAM_POINTER);
  }
  else if(StbMTruncatedFreshnessValueLength == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00547.StbMTruncatedFreshnessValueLength.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTXFRESHNESSTRUNCDATA, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    retval =  StbM_GetTxFreshnessTruncDataLcl(StbMFreshnessValueId, StbMFreshnessValueLength, StbMTruncatedFreshnessValueLength, StbMFreshnessValue, StbMTruncatedFreshnessValue);
  }

  DBG_STBM_GETTXFRESHNESSTRUNCDATA_EXIT(retval, StbMFreshnessValueId, StbMFreshnessValue, StbMFreshnessValueLength, StbMTruncatedFreshnessValue, StbMTruncatedFreshnessValueLength);
  return retval;
} /* StbM_GetTxFreshnessTruncData */
#endif /* (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_TXFRESHNESSTRUNC_USED == STD_ON)) || ((STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON) && (STBM_TXFRESHNESSTRUNC_CSINTERFACE_USED == STD_ON))) */


/* !LINKSTO StbM.R22-11.SWS_StbM_00541,1 */
/* !LINKSTO StbM.R22-11.SWS_StbM_91015,1 */
#if (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_TXCONFFRESHNESS_USED == STD_ON)) || (STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON))
FUNC(void, STBM_CODE) StbM_SPduTxConfirmation
(
  uint16 StbMFreshnessValueId
)
{
  DBG_STBM_SPDUTXCONFIRMATION_ENTRY(StbMFreshnessValueId);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.EB.SWS_StbM_00041.STBM_E_UNINIT.StbM_SPduTxConfirmation,1 */
    STBM_DET_REPORTERROR(STBM_API_SPDUTXCONFIRMATION, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if(FALSE == StbM_IsFreshnessValueIdConfigured(StbMFreshnessValueId))
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00548,1 */
    STBM_DET_REPORTERROR(STBM_API_SPDUTXCONFIRMATION, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    StbM_SPduTxConfirmationLcl(StbMFreshnessValueId);
  }

  DBG_STBM_SPDUTXCONFIRMATION_EXIT(StbMFreshnessValueId);
} /* StbM_SPduTxConfirmation */
#endif /* (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_TXCONFFRESHNESS_USED == STD_ON)) || (STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON)) */

#endif /* (STBM_MASTER_FRESHNESS_USED == STD_ON) */



#if (STBM_SLAVE_FRESHNESS_USED == STD_ON)

/* !LINKSTO StbM.R22-11.SWS_StbM_00541,1 */
/* !LINKSTO StbM.R22-11.SWS_StbM_91016,1 */
#if (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_RXFRESHNESS_USED == STD_ON)) || (STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON))
FUNC(Std_ReturnType, STBM_CODE) StbM_GetRxFreshness
(
  uint16 StbMFreshnessValueId,
  P2CONST(uint8, AUTOMATIC, STBM_APPL_DATA) StbMTruncatedFreshnessValue,
  uint32 StbMTruncatedFreshnessValueLength,
  uint16 StbMAuthVerifyAttempts,
  P2VAR(uint32, AUTOMATIC, STBM_APPL_DATA) StbMFreshnessValueLength,
  P2VAR(uint8, AUTOMATIC, STBM_APPL_DATA) StbMFreshnessValue
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETRXFRESHNESS_ENTRY(StbMFreshnessValueId, StbMTruncatedFreshnessValue, StbMTruncatedFreshnessValueLength, StbMAuthVerifyAttempts, StbMFreshnessValueLength, StbMFreshnessValue);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.EB.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetRxFreshness,1 */
    STBM_DET_REPORTERROR(STBM_API_GETRXFRESHNESS, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if(FALSE == StbM_IsFreshnessValueIdConfigured(StbMFreshnessValueId))
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00549,1 */
    STBM_DET_REPORTERROR(STBM_API_GETRXFRESHNESS, STBM_E_PARAM);
  }
  else if(StbMFreshnessValue == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00550.StbMFreshnessValue.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETRXFRESHNESS, STBM_E_PARAM_POINTER);
  }
  else if(StbMFreshnessValueLength == NULL_PTR)
  {
    /* !LINKSTO StbM.R22-11.SWS_StbM_00550.StbMFreshnessValueLength.NULL_PTR,1 */
    STBM_DET_REPORTERROR(STBM_API_GETRXFRESHNESS, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    retval = StbM_GetRxFreshnessLcl(StbMFreshnessValueId, StbMTruncatedFreshnessValue, StbMTruncatedFreshnessValueLength, StbMAuthVerifyAttempts, StbMFreshnessValueLength, StbMFreshnessValue);
  }

  DBG_STBM_GETRXFRESHNESS_EXIT(retval, StbMFreshnessValueId, StbMTruncatedFreshnessValue, StbMTruncatedFreshnessValueLength, StbMAuthVerifyAttempts, StbMFreshnessValueLength, StbMFreshnessValue);
  return retval;
} /* StbM_GetRxFreshness */
#endif /* (((STBM_FRESHNESS_CALLBACK_USED == STD_ON) && (STBM_RXFRESHNESS_USED == STD_ON)) || (STBM_FRESHNESS_RTEINTERFACE_USED == STD_ON)) */

#endif /* (STBM_SLAVE_FRESHNESS_USED == STD_ON) */


#endif /* (STBM_FRESHNESS_USED == STD_ON) */




#if (STBM_GET_MASTERCONFIG_SUPPORTED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00408,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetMasterConfig
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_MasterConfigType, AUTOMATIC, STBM_APPL_DATA) masterConfig
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETMASTERCONFIG_ENTRY(timeBaseId, masterConfig);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetMasterConfig,1 */
    STBM_DET_REPORTERROR(STBM_API_GETMASTERCONFIG, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00415.NotConfigured.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00415.Reserved.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETMASTERCONFIG, STBM_E_PARAM);
  }
  else if (masterConfig == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00416,1 */
    STBM_DET_REPORTERROR(STBM_API_GETMASTERCONFIG, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-4 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* !LINKSTO StbM.EB.StbM_GetMasterConfig.CalledWith.Slave.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETMASTERCONFIG, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* is this time base acting as a system-wide source of time */
    /* Deviation TASKING-1 */
    *masterConfig = StbM_CommonTimeBaseCfg[STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId)].systemWideMaster;
    retval = E_OK;
  }

  DBG_STBM_GETMASTERCONFIG_EXIT(retval, timeBaseId, masterConfig);
  return retval;
} /* StbM_GetMasterConfig */
#endif /* (STBM_GET_MASTERCONFIG_SUPPORTED == STD_ON) */



#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeBaseTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) syncTimeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  /* offset common index */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* get the underlying synchronized time base */
  uint8 syncIndex = STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET(timeBaseId);
  /* !LINKSTO StbM.SWS_StbM_00177.StbM_GetCurrentTime.AbsoluteTimeValue,1 */
  /* !LINKSTO StbM.SWS_StbM_00177.StbM_GetCurrentTimeExtended.AbsoluteTimeValue,1 */
  StbM_TimeStampType timeStampLocalTimeOffset = {0U, 0U, 0U, 0U};

  /* First step: update offset time base with the actual time. */
  /* no retval, only internal getters for offset time bases */
  (void)StbM_GetTime(timeBaseId, &timeStampLocalTimeOffset, currentTimeTupleGlobalPtr, currentTimeTupleVLTPtr, localTimePtr);

  retval = StbM_SumTimeStamps
    (
      syncTimeStampPtr,
      &timeStampLocalTimeOffset,
      timeStampPtr
    );

  /* enter critical section */
  /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.TIMEOUT.NoTimeout,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.TIMEOUT.TimeoutOccured,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.SYNC_TO_GATEWAY.NotBasedOnGateway,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.SYNC_TO_GATEWAY.BasedOnGateway,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.TIMELEAP_FUTURE.NoTimeleap,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.TIMELEAP_FUTURE.Timeleap,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.TIMELEAP_PAST.NoTimeleap,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.TIMELEAP_PAST.Timeleap,1 */
  /* set TIMEOUT, SYNC_TO_GATEWAY, TIMELEAP_PAST and TIMELEAP_FUTURE bits if any of sync or offset has the bits set
     (individually) */
  timeStampPtr->timeBaseStatus = StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus | StbM_TimeStamps[syncIndex].globalTime.timeBaseStatus;

  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.GLOBAL_TIME_BASE.NoSync,1 */
  /* !LINKSTO StbM.SWS_StbM_00261.StbM_GetCurrentTime.GLOBAL_TIME_BASE.Sync,1 */
  /* GLOBAL_TIME_BIT shall only be set if it is set in both sync and offset */
  if(STBM_FLAG_IS_SET((StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus & StbM_TimeStamps[syncIndex].globalTime.timeBaseStatus), STBM_GLOBAL_TIME_BASE_FLAG))
  {
    STBM_FLAG_SET(timeStampPtr->timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG);
  }
  else
  {
    STBM_FLAG_DELETE(timeStampPtr->timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG);
  }


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
  /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_GetCurrentTime,2 */
  StbM_UpdateSharedDataInMemory(timeBaseId, timeStampPtr->timeBaseStatus, &timeStampLocalTimeOffset, localTimePtr);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


  return retval;

} /* StbM_GetOffsetTimeBaseTime */

STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_CheckCalculateOffsetTime
(
  uint8 syncIndex,
  boolean checkGlobalTimeBit,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) calculateOffsetTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  /* enter critical section */
  /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeStamps,1 */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* check if STBM_GLOBAL_TIME_BASE_FLAG has been set for underlying sync time base */
  /* master side */
  if(TRUE == checkGlobalTimeBit)
  {
    if(STBM_FLAG_IS_SET(StbM_TimeStamps[syncIndex].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG))
    {
      *calculateOffsetTimePtr = TRUE;
    }
    else
    {
      /* !LINKSTO StbM.SWS_StbM_00304.StbM_SetGlobalTime.GLOBAL_TIME_BASE.NotSet,1 */
      /* !LINKSTO StbM.SWS_StbM_00304.StbM_UpdateGlobalTime.GLOBAL_TIME_BASE.NotSet,1 */
      retval = E_NOT_OK;
    }
  }
  /* slave side */
  else
  {
    /* !LINKSTO StbM.SWS_StbM_00393,1 */
    /* no need to calculate offset for slave */
    *calculateOffsetTimePtr = FALSE;

    retval = E_OK;
  }

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  return retval;
} /* StbM_CheckCalculateOffsetTime */
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */


#if (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00385,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateGlobalTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
  uint8 detectedDET = 0U;

  /* get the underlying synchronized time base (timeBaseId might be an offset) */
  uint8 underlyingTimeBaseId = STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX(timeBaseId);

  DBG_STBM_UPDATEGLOBALTIME_ENTRY(timeBaseId, timeStamp, userData);

  /* Get current Virtual Local Time */
  /* !LINKSTO StbM.SWS_StbM_00342.StbM_UpdateGlobalTime.GetVirtualLocalTime,1 */
  retval = StbM_GetCurrentVirtualLocalTimeNoDet(underlyingTimeBaseId, &detectedDET, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (detectedDET == STBM_E_UNINIT)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_UpdateGlobalTime,1 */
    STBM_DET_REPORTERROR(STBM_API_UPDATEGLOBALTIME, STBM_E_UNINIT);
  }
  else if (detectedDET == STBM_E_PARAM)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00340,1 */
    STBM_DET_REPORTERROR(STBM_API_UPDATEGLOBALTIME, STBM_E_PARAM);
  }
  else if (timeStamp == NULL_PTR)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00341,1 */
    STBM_DET_REPORTERROR(STBM_API_UPDATEGLOBALTIME, STBM_E_PARAM_POINTER);
  }
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    retval = E_NOT_OK;
    STBM_DET_REPORTERROR(STBM_API_UPDATEGLOBALTIME, STBM_E_PARAM);
  }
  else if (timeStamp->nanoseconds > STBM_NANOSEC_MAX_VALID_VALUE)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00451,1 */
    STBM_DET_REPORTERROR(STBM_API_UPDATEGLOBALTIME, STBM_E_PARAM_TIMESTAMP);
  }
  else if ((userData != NULL_PTR) && (userData->userDataLength > STBM_MAX_USER_DATA_LENGTH))
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00452,1 */
    STBM_DET_REPORTERROR(STBM_API_UPDATEGLOBALTIME, STBM_E_PARAM_USERDATA);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    if(E_OK == retval)
    {
      /* !LINKSTO StbM.SWS_StbM_00342.StbM_UpdateGlobalTime.UpdateTimeTuple,1 */
     retval = StbM_SetTime(timeBaseId, timeStamp, userData, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);
   }
  }

  DBG_STBM_UPDATEGLOBALTIME_EXIT(retval, timeBaseId, timeStamp, userData);

  return retval;
}
#endif /* (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON) */


#if (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00213,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
  uint8 detectedDET = 0U;


  /* get the underlying synchronized time base (timeBaseId might be an offset) */
  uint8 underlyingTimeBaseId = STBM_GET_UNDERLYING_SYNC_TIMEBASE_INDEX(timeBaseId);

  DBG_STBM_SETGLOBALTIME_ENTRY(timeBaseId, timeStamp, userData);

  /* Get current Virtual Local Time */
  /* !LINKSTO StbM.SWS_StbM_00342.StbM_SetGlobalTime.GetVirtualLocalTime,1 */
  retval = StbM_GetCurrentVirtualLocalTimeNoDet(underlyingTimeBaseId, &detectedDET, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (detectedDET == STBM_E_UNINIT)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_SetGlobalTime,1 */
    STBM_DET_REPORTERROR(STBM_API_SETGLOBALTIME, STBM_E_UNINIT);
  }
  else if (detectedDET == STBM_E_PARAM)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00214,1 */
    STBM_DET_REPORTERROR(STBM_API_SETGLOBALTIME, STBM_E_PARAM);
  }
  else if (timeStamp == NULL_PTR)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00215,1 */
    STBM_DET_REPORTERROR(STBM_API_SETGLOBALTIME, STBM_E_PARAM_POINTER);
  }
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    retval = E_NOT_OK;
    STBM_DET_REPORTERROR(STBM_API_SETGLOBALTIME, STBM_E_PARAM);
  }
  else if (timeStamp->nanoseconds > STBM_NANOSEC_MAX_VALID_VALUE)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00448,1 */
    STBM_DET_REPORTERROR(STBM_API_SETGLOBALTIME, STBM_E_PARAM_TIMESTAMP);
  }
  else if ((userData != NULL_PTR) && (userData->userDataLength > STBM_MAX_USER_DATA_LENGTH))
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00449,1 */
    STBM_DET_REPORTERROR(STBM_API_SETGLOBALTIME, STBM_E_PARAM_USERDATA);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    if(E_OK == retval)
    {
      /* !LINKSTO StbM.SWS_StbM_00342.StbM_SetGlobalTime.UpdateTimeTuple,1 */
      retval = StbM_SetTime(timeBaseId, timeStamp, userData, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
#if (STBM_PURE_TIMEBASES_USED == STD_ON)
      /* Increase timeBaseUpdateCounter only for SYNC and OFFSET timebase Ids */
      if(!(STBM_IS_PURE_TIMEBASE_ID(timeBaseId)))
#endif /* (STBM_PURE_TIMEBASES_USED == STD_ON) */
      {
        /* !LINKSTO StbM.EB.SetGlobalTime.E_NOT_OK.Offset,1 */
        if(E_OK == retval)
        {
          /* Get the timebaseid into the zero-based dense configuration existing for all time bases. */
          uint8 Index = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

          /* Enter critical section */
          /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseUpdateCounter,1 */
          SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

          /* Increment the time base update counter, this is the defined and intended overflow */
          /* !LINKSTO StbM.SWS_StbM_00350.StbM_SetGlobalTime.Sync,1 */
          /* !LINKSTO StbM.SWS_StbM_00350.StbM_SetGlobalTime.Offset,1 */
          StbM_TimeBaseUpdateCounter[Index]++;

          /* Leave critical section */
          SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
        }
      }
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */
    }
  }

  DBG_STBM_SETGLOBALTIME_EXIT(retval, timeBaseId, timeStamp, userData);
  return retval;
} /* StbM_SetGlobalTime */
#endif /* (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON) */




#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)



/* !LINKSTO StbM.SWS_StbM_00272,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_StartTimer
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CustomerIdType customerId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_STARTTIMER_ENTRY(timeBaseId, customerId, expireTime);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_StartTimer,1 */
    STBM_DET_REPORTERROR(STBM_API_STARTTIMER, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00296.CalledWith.NotConfigured.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00296.CalledWith.Reserved.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_STARTTIMER, STBM_E_PARAM);
  }
  else if (STBM_CUSTOMER_ID_NOT_CONFIGURED(STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId), customerId))
  {
    /* !LINKSTO StbM.SWS_StbM_00406,1 */
    STBM_DET_REPORTERROR(STBM_API_STARTTIMER, STBM_E_PARAM);
  }
  else if (expireTime == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00298,1 */
    STBM_DET_REPORTERROR(STBM_API_STARTTIMER, STBM_E_PARAM_POINTER);
  }
  else if (STBM_EXPIRE_TIME_IS_ZERO(expireTime))
  {
    /* !LINKSTO StbM.SWS_StbM_00298.ExpireTime.Zero,1 */
    STBM_DET_REPORTERROR(STBM_API_STARTTIMER, STBM_E_PARAM);
  }
  else
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    StbM_CustomerTimerExpireTimeNodeDataType newExpiryPoint = {NULL_PTR, {65535U, 255U, {0U, 0U, 0U, 0U}, 0U, FALSE, FALSE, FALSE, TRUE, 0}, NULL_PTR};
    StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};

    /* !LINKSTO StbM.SWS_StbM_00270,1 */
    if(StbM_IsTimeBaseIdCustomerIdInList(timeBaseId, customerId) == FALSE)
    {
      StbM_TimeStampType configuredStartTimerThreshold = {0U, 0U, 0U, 0U};
      StbM_TimeStampType newCalculatedExpireTime = {0U, 0U, 0U, 0U};
      uint32 expireTimeDataArrayIndex = 0U;

      configuredStartTimerThreshold.nanoseconds = STBM_TIMERSTARTTHRESHOLD_NANOSEC_PART;
      configuredStartTimerThreshold.seconds = STBM_TIMERSTARTTHRESHOLD_SEC_PART;

      /* Get StbM local time */
      if(StbM_CalculateLocalTime(timeBaseId, &timeStampLocalTime) == E_OK)
      {
        /* add expire time to the local StbM time */
        timeStampLocalTime.nanoseconds += expireTime->nanoseconds;
        timeStampLocalTime.seconds += expireTime->seconds;
        timeStampLocalTime.secondsHi += expireTime->secondsHi;

        /* calculate the new expire time which needs to be inserted in the list */
        /* !LINKSTO StbM.SWS_StbM_00270,1 */
        STBM_ASSIGN_TIMESTAMP(newCalculatedExpireTime, timeStampLocalTime);

        newExpiryPoint.previous = NULL_PTR;
        newExpiryPoint.Data.timeBaseId = timeBaseId;
        newExpiryPoint.Data.customerId = customerId;
        STBM_ASSIGN_TIMESTAMP(newExpiryPoint.Data.customerTimerExpireTime, newCalculatedExpireTime);
        newExpiryPoint.Data.isGptTimerRunning = FALSE;
        newExpiryPoint.Data.pendingStartGptTimer = FALSE;
        newExpiryPoint.Data.isTimerExpiredInGpt = FALSE;
        newExpiryPoint.Data.arrayCellIndex = 0U;
        newExpiryPoint.Data.isArrayCellEmpty = TRUE;
        newExpiryPoint.Data.calculatedTimeDeviation = 0U;
        newExpiryPoint.next = NULL_PTR;

        /* expireTime smaller than StbMStartTimerThreshold */
        if(StbM_TimeStampIsGreaterEqual(&configuredStartTimerThreshold, expireTime) == TRUE)
        {
          /* Try to call Gpt_StartTimer() when expireTime is smaller than threshold */
          StbM_TryToCallGptStartTimer(expireTime, &newExpiryPoint);
        }

        SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

        /* set the expireTimeDataArray index */
        /* !LINKSTO StbM.SWS_StbM_00337.SameExpiryPoints,1 */
        /* !LINKSTO StbM.SWS_StbM_00337.DifferentExpiryPoints,1 */
        /* !LINKSTO StbM.SWS_StbM_00270.MaxNrOf.StbM_StartTimer.Calls,1 */
        retval = StbM_GetInsertionIndex(&expireTimeDataArrayIndex);

        if(retval == E_OK)
        {
          /* if empty list */
          if(STBM_ISLISTEMPTY())
          {
            /* !LINKSTO StbM.SWS_StbM_00337.SameExpiryPoints,1 */
            /* !LINKSTO StbM.SWS_StbM_00337.DifferentExpiryPoints,1 */
            StbM_InsertAtTheBeginning(expireTimeDataArrayIndex, &newExpiryPoint.Data);
          }
          else /* there is still place in the list for a new insertion */
          {
            /* !LINKSTO StbM.SWS_StbM_00337.SameExpiryPoints,1 */
            /* !LINKSTO StbM.SWS_StbM_00337.DifferentExpiryPoints,1 */
            StbM_InsertAtTheRightPosition(expireTimeDataArrayIndex, &newExpiryPoint.Data);
          }
        }

        SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
      }
    }
  }

  DBG_STBM_STARTTIMER_EXIT(retval, timeBaseId, customerId, expireTime);
  return retval;
} /* StbM_StartTimer */




 /* Deviation MISRAC2012-3 */
 /* !LINKSTO StbM.SWS_StbM_00336.GPTTimerExpired.Call.StbM_TimerCallback,1 */
FUNC(void, STBM_CODE) StbM_TimerCallback
(
  void
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;
  StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};
  StbM_TimeStampType customerExpireTime = {0U, 0U, 0U, 0U};

  StbM_TimeStampType timeStampA = {0U, 0U, 0U, 0U};
  StbM_TimeStampType timeStampB = {0U, 0U, 0U, 0U};

  /* variables used for handling time deviation */
  StbM_TimeStampType calculatedDeviationTimeStamp = {0U, 0U, 0U, 0U};
  /* max Gpt value */
  StbM_TimeStampType maxGptValueInTicks = {0U, 147483647U, 2U, 0U};

  StbM_SynchronizedTimeBaseType lclTimeBaseId = 0U;

  uint32 nanosecondsCalcDev = 0U;
  uint32 secondsCalcDev = 0U;
  uint32 nanosecondsPartFromsecondsCalcDev = 0U;
  sint32 totalCalcDevNanoseconds = 0U;
  uint8 signOfTheDifference = 0U;
  uint32 cellIndex = 0U;

  boolean found = FALSE;

  DBG_STBM_TIMERCALLBACK_ENTRY();

  /* calculate the difference between CustomerTimerExpireTime and timeStampLocalTime */

  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* search for the first expiry point from the list, for which isGptTimerRunning flag was set */
  for(current = Head; current != NULL_PTR; current = current->next)
  {
    /* first expiry point for which a Gpt Timer was started */
    if(current->Data.isGptTimerRunning == TRUE)
    {
      /* get customer timer expire time */
      customerExpireTime = current->Data.customerTimerExpireTime;

      /* get timebaseId */
      lclTimeBaseId = current->Data.timeBaseId;

      /* save array index */
      cellIndex = current->Data.arrayCellIndex;

      found = TRUE;
      break;
    }
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  if(found)
  {
    /* calculate local time */
    (void) StbM_CalculateLocalTime(lclTimeBaseId, &timeStampLocalTime);

    /* compare customerExpireTime with timeStampLocalTime in order to find the sign */
    if(StbM_TimeStampIsGreaterEqual(&customerExpireTime, &timeStampLocalTime))
    {
      STBM_ASSIGN_TIMESTAMP(timeStampA, customerExpireTime);
      STBM_ASSIGN_TIMESTAMP(timeStampB, timeStampLocalTime);
      /* store sign calculation */
      signOfTheDifference = STBM_SIGN_IS_POSITIVE;
    }
    else
    {
      STBM_ASSIGN_TIMESTAMP(timeStampB, customerExpireTime);
      STBM_ASSIGN_TIMESTAMP(timeStampA, timeStampLocalTime);
      /* store sign calculation */
      signOfTheDifference = STBM_SIGN_IS_NEGATIVE;
    }

    /* calculate the difference between CustomerTimerExpireTime and timeStampLocalTime */
    /* !LINKSTO StbM.SWS_StbM_00271.CalculateTimeDifference,1 */
    (void)StbM_SubtractTimeStamps
    (
      &timeStampA,
      &timeStampB,
      &calculatedDeviationTimeStamp
    );

    /* get the nanoseconds part from the deviationTimeStamp */
    nanosecondsCalcDev = calculatedDeviationTimeStamp.nanoseconds;
    /* get the seconds part from the deviationTimeStamp */
    secondsCalcDev = calculatedDeviationTimeStamp.seconds;


    /* check if range is elapsed */
    if (StbM_TimeStampIsGreaterEqual(&maxGptValueInTicks, &calculatedDeviationTimeStamp) == TRUE)
    {
      /* calculate how many nanoseconds are contained in secondsCalcDev */
      nanosecondsPartFromsecondsCalcDev = secondsCalcDev * STBM_NS_PER_SEC;

      /* calculate the sum of nanoseconds from calculatedDeviationTimeStamp */
      /* Deviation MISRAC2012-1 */
      totalCalcDevNanoseconds =  (sint32)(nanosecondsCalcDev + nanosecondsPartFromsecondsCalcDev);

      if(signOfTheDifference == STBM_SIGN_IS_NEGATIVE)
      {
        totalCalcDevNanoseconds =  (-1) * totalCalcDevNanoseconds;
      }

    }
    else /* range elapsed */
    {
      /* possitive sign */
      if(signOfTheDifference == STBM_SIGN_IS_POSITIVE)
      {
        totalCalcDevNanoseconds = STBM_MAX_POSITIVE_SINT32_VALUE;
      }
      else /* negative sign */
      {
        totalCalcDevNanoseconds = STBM_MAX_NEGATIVE_SINT32_VALUE;
      }
    }

    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    StbM_ExpireTimeData[cellIndex].Data.isTimerExpiredInGpt = TRUE;
    StbM_ExpireTimeData[cellIndex].Data.calculatedTimeDeviation = totalCalcDevNanoseconds;
    StbM_IsGptTimeRunning = FALSE;

    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }
  /* unexpected StbM_TimerCallback => nothing happens */
  /* !LINKSTO StbM.SWS_StbM_00271.Unexpected.StbM_TimerCallback,1 */

  DBG_STBM_TIMERCALLBACK_EXIT();

}
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */



#if (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00218,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_SetUserData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_SETUSERDATA_ENTRY(timeBaseId, userData);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_SetUserData,1 */
    STBM_DET_REPORTERROR(STBM_API_SETUSERDATA, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00219,1 */
    STBM_DET_REPORTERROR(STBM_API_SETUSERDATA, STBM_E_PARAM);
  }
  else if (userData == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00220,1 */
    STBM_DET_REPORTERROR(STBM_API_SETUSERDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-4 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* Calling SetUserData for a slave time base shall throw a DET error */
    /* !LINKSTO StbM.EB.StbM_SetUserData.timeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_SETUSERDATA, STBM_E_PARAM);
  }
  else if (userData->userDataLength > STBM_MAX_USER_DATA_LENGTH)
  {
    /* !LINKSTO StbM.SWS_StbM_00457,1 */
    STBM_DET_REPORTERROR(STBM_API_SETUSERDATA, STBM_E_PARAM_USERDATA);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* get the offset into the zero-based dense configuration existing for all time bases. */
    /* Deviation TASKING-1 */
    uint8 Index = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

    /* enter critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_UserData,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* Store the userData bytes for the MASTER time base, based on userDataLength */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_SetUserData,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_SetUserData,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_SetUserData,1 */
    StbM_SetUserDataBytes(Index, userData);

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* Return if successful */
    retval = E_OK;
  }

  DBG_STBM_SETUSERDATA_EXIT(retval, timeBaseId, userData);
  return retval;
} /* StbM_SetUserData */
#endif /* (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON) */


#if (STBM_SETOFFSET_SUPPORTED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00223,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_SetOffset
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
  uint8 detectedDET = 0U;

  DBG_STBM_SETOFFSET_ENTRY(timeBaseId, timeStamp, userData);

  /* Get current Virtual Local Time */
  /* !LINKSTO StbM.EB.SetOffset.E_NOT_OK,1 */
  /* currentTimeTupleGlobal, currentTimeTupleVLT not used in StbM_SetOffset,
     but are required by StbM_GetCurrentVirtualLocalTimeNoDet */
  retval = StbM_GetCurrentVirtualLocalTimeNoDet(timeBaseId, &detectedDET, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (detectedDET == STBM_E_UNINIT)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_SetOffset,1 */
    STBM_DET_REPORTERROR(STBM_API_SETOFFSET, STBM_E_UNINIT);
  }
  else if (detectedDET == STBM_E_PARAM)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00224.TimeBaseId.NotConfigured,1 */
    /* !LINKSTO StbM.SWS_StbM_00224.WithinReservedValueRange,1 */
    STBM_DET_REPORTERROR(STBM_API_SETOFFSET, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00191,1 */
  else if (!STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00224.Synchronized.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00224.Pure.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_SETOFFSET, STBM_E_PARAM);
  }
  else if (timeStamp == NULL_PTR)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00225,1 */
    STBM_DET_REPORTERROR(STBM_API_SETOFFSET, STBM_E_PARAM_POINTER);
  }
  else if (timeStamp->nanoseconds > STBM_NANOSEC_MAX_VALID_VALUE)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00453,1 */
    STBM_DET_REPORTERROR(STBM_API_SETOFFSET, STBM_E_PARAM_TIMESTAMP);
  }
  else if ((userData != NULL_PTR) && (userData->userDataLength > STBM_MAX_USER_DATA_LENGTH))
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00454,1 */
    STBM_DET_REPORTERROR(STBM_API_SETOFFSET, STBM_E_PARAM_USERDATA);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    if(E_OK == retval)
    {
     uint8 index = STBM_OFFSET_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(index);
      uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


      /* enter critical section */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeStamps,1 */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_UserData,1 */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedData,1 */
      SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* store the given offset(Global Time) of the Main Tuple */
      /* !LINKSTO StbM.SWS_StbM_00190,1 */
      STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[index].globalTime, *timeStamp);
      /* store the Virtual Local Time of the Main Tuple */
      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[index].virtualLocalTime, localTime);

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
      /* set EV_RESYNC notification event after time was updated */
      /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
      STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[index], STBM_EV_RESYNC);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

      /* reload the update counter */
      StbM_UpdateTimeTupleCounter[index] = STBM_UPDATE_COUNTER_VALUE;

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
      if(!(STBM_FLAG_IS_SET(StbM_TimeStamps[index].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG)))
      {
        STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[index], STBM_EV_GLOBAL_TIME);
      }
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

        /* For an offset time base the status shall have the following behavior:
         * 1.) The offset value is set:
         * - GetCurrentTime shall return the timestamp of the underlying sync time base
         *   plus the offset value.
         * - GetCurrentTime shall return the timeBaseStatus of the underlying sync time base
         * 2.) The offset value was never set:
         * - GetCurrentTime shall return the timestamp of the underlying sync time base only
         * - The timeBase status shall be set to 0.
         *
         * The time base status of an offset time base is therefore unused.
         * This implementation uses the time base status to memorize if the value of
         * an offset time base is set (instead of having a status derived from some SYNC condition).
         */
        /* !LINKSTO StbM.SWS_StbM_00181.SetOffset,1 */
        StbM_TimeStamps[index].globalTime.timeBaseStatus = STBM_GLOBAL_TIME_BASE_FLAG;


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_SetOffset,2 */
      StbM_UpdateSharedDataInMemory(timeBaseId, STBM_GLOBAL_TIME_BASE_FLAG, timeStamp, &localTime);
#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      /* check if time base needs to share data to memory */
      if ((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[index].timeBaseRoleSharedData == STBM_TIME_BASE_PROVIDER_SHARED_DATA))
      {
        /* get array start index for this timebase */
        timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteBegin,1 */
        /* increment the 'begin' counter, this will signal the user that
           data is currently being written */
        Atomics_ThreadFence();
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX]++;
        Atomics_ThreadFence();

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_SetOffset,1 */
        StbM_UpdateTimeTupleInSharedMemory(index, timeBaseStartIndex);

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteEnd,1 */
        /* increment the 'end' counter, this will signal the user that
           data has been written */
        Atomics_ThreadFence();
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX]++;
        Atomics_ThreadFence();
      }
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

      /* Store the userData bytes for the MASTER time base, based on userDataLength */
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_SetOffset,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_SetOffset,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_SetOffset,1 */
      StbM_SetUserDataBytes(index, userData);

#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
      /* Increment the time base update counter, this is the defined and intended overflow */
      /* !LINKSTO StbM.SWS_StbM_00350.StbM_SetOffset,1 */
      StbM_TimeBaseUpdateCounter[index]++;
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */

      /* leave critical section */
      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
    }
  }

  DBG_STBM_SETOFFSET_EXIT(retval, timeBaseId, timeStamp, userData);
  return retval;
}
#endif /* (STBM_SETOFFSET_SUPPORTED == STD_ON) */



/* !LINKSTO StbM.SWS_StbM_00228,1 */
/* !LINKSTO StbM.SWS_StbM_00192,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffset
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETOFFSET_ENTRY(timeBaseId, timeStamp, userData);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetOffset,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSET, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  /* Deviation MISRAC2012-4 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00229.NotConfigured.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00229.WithinReservedRange.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSET, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00191,1 */
  /* Deviation TASKING-4 */
  /* Deviation MISRAC2012-4 */
  else if (!STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00229.Synchronized.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00229.Pure.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSET, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00230.timeStamp,1 */
  else if (timeStamp == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETOFFSET, STBM_E_PARAM_POINTER);
  }
  /* !LINKSTO StbM.SWS_StbM_00230.userData,1 */
  else if (userData == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETOFFSET, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};
    StbM_VirtualLocalTimeType localTime = {0U, 0U};
    StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
    StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};

    /* This function is used only for offset time bases so only the offset ID to common
     * index is used for user data */
    uint8 index = STBM_OFFSET_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(index);
  uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    /* get the underlying synchronized time base (timeBaseId might be an offset) */
    uint8 underlyingTimeBaseId = STBM_GET_SYNC_TIMEBASE_INDEX_FROM_OFFSET(timeBaseId);

    /* get common index */
    /* Deviation TASKING-1 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
  /* check if time base needs to share data to memory */
  if((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[index].timeBaseRoleSharedData == STBM_TIME_BASE_CONSUMER_SHARED_DATA))
  {
    /* get array start index for this timebase */
    timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

    /* enter critical section */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* before using time base data from shared memory, check that it was succesfully written */
    if(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX] == StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX])
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.When.StbM_GetOffset,1 */
      /* read data from shared memory */
      StbM_ReadDataFromSharedMemory(index, timeBaseStartIndex);

      /* reload the update counter */
      StbM_UpdateTimeTupleCounter[commonIndex] = STBM_UPDATE_COUNTER_VALUE;
    }

    if(STBM_FLAG_IS_SET(StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG))
    {
      /* if data is ready to be read, read it, or if data is not ready to be read, read the last time base data which was written in the shared memory */
      retval = E_OK;
    }
    else
    {
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.IfNotSuccessfullyUpdated.StbM_GetOffset,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.DoNotUseSharedVariable.If_GTSBit_NotSet.StbM_GetOffset,1 */
      /* no time base data was written in the shared memory - return E_NOT_OK */
    }

    /* exit critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }
  else
  {
    /* if timebase has no shared data activated, return E_OK */
    retval = E_OK;
  }

  /* check if data was successfully read from shared memory */
  if(E_OK == retval)
  {
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* store current Time Tuple values */
    STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobal, StbM_TimeStamps[commonIndex].globalTime);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLT, StbM_TimeStamps[commonIndex].virtualLocalTime);

    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* Get current Virtual Local Time */
      retval = StbM_GetCurrentVirtualLocalTimeNoChecks(underlyingTimeBaseId, &localTime);

      if(E_OK == retval)
      {
        /* First step: update synchronized time base with the actual time. */
        /* no retval, only intrnal usage for offset time bases */
        /* !LINKSTO  StbM.SWS_StbM_00192,1 */
        (void) StbM_GetTime(timeBaseId, &timeStampLocalTime, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

        /* enter critical section */
        /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
        SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_GetOffset,2 */
        StbM_UpdateSharedDataInMemory(timeBaseId, StbM_TimeStamps[index].globalTime.timeBaseStatus, &timeStampLocalTime, &localTime);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

        STBM_ASSIGN_TIMESTAMP(*timeStamp, timeStampLocalTime);

        /* copy timeBaseStatus member */
        timeStamp->timeBaseStatus = StbM_TimeStamps[index].globalTime.timeBaseStatus;

        /* initialize the user data address with the user data of this time base */
        userData->userDataLength = StbM_UserData[index].userDataLength;
        userData->userByte0      = StbM_UserData[index].userByte0;
        userData->userByte1      = StbM_UserData[index].userByte1;
        userData->userByte2      = StbM_UserData[index].userByte2;

        /* leave critical section */
        SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
      }

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
    }
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  }

  DBG_STBM_GETOFFSET_EXIT(retval, timeBaseId, timeStamp, userData);
  return retval;
}



#if (STBM_TRIGGERTIMETRANSMISSION_SUPPORTED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00346,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_TriggerTimeTransmission
(
  StbM_SynchronizedTimeBaseType timeBaseId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_STBM_TRIGGERTIMETRANSMISSION_ENTRY(timeBaseId);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_TriggerTimeTransmission,1 */
    STBM_DET_REPORTERROR(STBM_API_TRIGGERTIMETRANSMISSION, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00349.TimeBaseId.NotConfigured.Or.WithinReservedRange,1 */
    /* !LINKSTO StbM.SWS_StbM_00349.Pure.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_TRIGGERTIMETRANSMISSION, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* enter critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseUpdateCounter,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* Increment the time base update counter, this is the defined and intended overflow */
    /* !LINKSTO StbM.SWS_StbM_00350.StbM_TriggerTimeTransmission.Sync,1 */
    /* !LINKSTO StbM.SWS_StbM_00350.StbM_TriggerTimeTransmission.Offset,1 */
    /* Deviation TASKING-1 */
    /* Deviation TASKING-2 */
    StbM_TimeBaseUpdateCounter[STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId)]++;

    /* exit critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    RetVal = E_OK;
  }

  DBG_STBM_TRIGGERTIMETRANSMISSION_EXIT(RetVal, timeBaseId);
  return RetVal;
}
#endif /* (STBM_TRIGGERTIMETRANSMISSION_SUPPORTED == STD_ON) */


/* !LINKSTO StbM.SWS_StbM_00263,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeBaseStatus
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_DATA) syncTimeBaseStatus,
  P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_DATA) offsetTimeBaseStatus
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_STBM_GETTIMEBASESTATUS_ENTRY(timeBaseId, syncTimeBaseStatus, offsetTimeBaseStatus);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetTimeBaseStatus,1 */
  if (StbM_InitStatus == STBM_NOINIT)
  {
    STBM_DET_REPORTERROR(STBM_API_GETTIMEBASESTATUS, STBM_E_UNINIT);
  }
  /* !LINKSTO StbM.SWS_StbM_00264,1 */
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    STBM_DET_REPORTERROR(STBM_API_GETTIMEBASESTATUS, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00386,1 */
  else if (syncTimeBaseStatus == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETTIMEBASESTATUS, STBM_E_PARAM_POINTER);
  }
  /* !LINKSTO StbM.SWS_StbM_00386,1 */
  else if (offsetTimeBaseStatus == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETTIMEBASESTATUS, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {

    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* If this is a synchronized or a pure time base set syncTimeBaseStatus to the status of the
     * corresponding synchronized time base and if this is an offset time base set
     * syncTimeBaseStatus to the status of the related synchronized time base. */
    /* !LINKSTO StbM.SWS_StbM_00262.GetTimeBaseStatus.Sync,1 */
    /* !LINKSTO StbM.SWS_StbM_00262.GetTimeBaseStatus.Pure,1 */
    /* Deviation TASKING-4 */
    *syncTimeBaseStatus = StbM_TimeStamps[STBM_GET_SYNC_TIMEBASE_INDEX(timeBaseId)].globalTime.timeBaseStatus;

    /* If this is a synchronized or pure time base set offsetTimeBaseStatus to 0 and if this is an
     * offset time base set offsetTimeBaseStatus to the status of the corresponding offset
     * time base. */
    /* !LINKSTO StbM.SWS_StbM_00262.GetTimeBaseStatus.Offset,1 */
    /* !LINKSTO StbM.SWS_StbM_00262.GetTimeBaseStatus.Pure,1 */
    /* Deviation MISRAC2012-4 */
    if(STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
    {
      *offsetTimeBaseStatus = StbM_TimeStamps[STBM_OFFSET_ID_TO_COMMON_INDEX(timeBaseId)].globalTime.timeBaseStatus;
    }
    else
    {
      *offsetTimeBaseStatus = 0U;
    }

    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    RetVal = E_OK;
  }

  DBG_STBM_GETTIMEBASESTATUS_EXIT
    (RetVal, timeBaseId, syncTimeBaseStatus, offsetTimeBaseStatus);

  return RetVal;
}


/* !LINKSTO StbM.SWS_StbM_00378,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetRateDeviation
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_DATA) rateDeviation
)
{
  Std_ReturnType retval = E_NOT_OK;
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_OFF)
  TS_PARAM_UNUSED(timeBaseId);
  TS_PARAM_UNUSED(rateDeviation);
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

  DBG_STBM_GETRATEDEVIATION_ENTRY(timeBaseId, rateDeviation);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetRateDeviation,1 */
    STBM_DET_REPORTERROR(STBM_API_GETRATEDEVIATION, STBM_E_UNINIT);
  }
  /* !LINKSTO StbM.SWS_StbM_00379,1 */
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    STBM_DET_REPORTERROR(STBM_API_GETRATEDEVIATION, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00380,1 */
  else if (rateDeviation == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETRATEDEVIATION, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    StbM_RateDeviationType rateDev = STBM_RATE_DEVIATION_INVALID_VALUE;
#if (STBM_RATE_CORRECTION_USED)
    uint8 rcDataIndex = 0U;
    /* Deviation TASKING-1 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
#endif /* STBM_RATE_CORRECTION_USED */

    /* enter critical section */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
    /* check if the time base has Master Rate Correction activated and also
       if time base is a SystemWideGlobalTimeMaster, in order to be sure that rate deviation will be calculated on StbM_SetRateCorrection() if it's called */
    if(STBM_MASTER_IS_SYSTEM_WIDE_MASTER(commonIndex) == TRUE)
    {
      /* get index for the StbM_MasterRateCorrectionData[] array */
      rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonIndex);
      rateDev = StbM_MasterRateCorrectionData[rcDataIndex].rateDev;
    }
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
    else
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
    {
      /* get index for the StbM_SlaveRateCorrectionData[] array */
      rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);
      rateDev = StbM_SlaveRateCorrectionData[rcDataIndex].rateDev;
    }
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

    /* if calculated rate deviation is invalid, or no rate deviation has been calculated,
     * return E_NOT_OK */
    /* !LINKSTO StbM.SWS_StbM_00397.Slave.E_NOT_OK,1 */
    /* !LINKSTO StbM.SWS_StbM_00422.NoRateDeviation.Set,1 */
#if ((STBM_MASTER_RATE_CORRECTION_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON))
    if(rateDev != STBM_RATE_DEVIATION_INVALID_VALUE)
    {
      /* !LINKSTO StbM.SWS_StbM_00527.Slave.Sync,1 */
      /* !LINKSTO StbM.SWS_StbM_00527.Slave.Offset,1 */
      /* !LINKSTO StbM.SWS_StbM_00422.RateDeviation.Set,1 */
      /* obtain rate deviation */
      *rateDeviation = rateDev;
      /* !LINKSTO StbM.SWS_StbM_00397.Slave.E_OK,1 */
      retval = E_OK;
    }
#else
    *rateDeviation = rateDev;
#endif /* ((STBM_MASTER_RATE_CORRECTION_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)) */

    /* exit critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }

  DBG_STBM_GETRATEDEVIATION_EXIT(retval, timeBaseId, rateDeviation);

  return retval;
} /* StbM_GetRateDeviation */

#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00267,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeLeap
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_APPL_DATA) timeJump
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETTIMELEAP_ENTRY(timeBaseId, timeJump);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetTimeLeap,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTIMELEAP, STBM_E_UNINIT);
  }
  /* !LINKSTO StbM.SWS_StbM_00268.NotConfiguredId,1 */
  /* !LINKSTO StbM.SWS_StbM_00268.PureTimeBaseId,1 */
  /* !LINKSTO StbM.SWS_StbM_00268.ReservedId,1 */
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    STBM_DET_REPORTERROR(STBM_API_GETTIMELEAP, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00269,1 */
  else if (timeJump == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETTIMELEAP, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  else if(STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_GetTimeLeap for a MASTER time base shall throw a DET error */
    /* !LINKSTO StbM.GetTimeLeap.MASTERTimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTIMELEAP, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-1 */
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    /* !LINKSTO StbM.SWS_StbM_00425.FirstValidInvocationOfBusSetGlobalTime.StbM_GetTimeLeap.Returns.E_NOT_OK,1 */
    /* The timeleap is handled only after the second valid invocation of StbM_BusSetGlobalTime() for the corresponding Time Base,
       If timeleaptype is set, it means that at least once the timeleap was handled */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
    if (StbM_TimeLeapInfo[commonIndex].timeJumpCalculated != FALSE)
    {
      /* !LINKSTO StbM.GetTimeLeap.TimeLeapFeatureDisabled,1 */
      /* !LINKSTO StbM.SWS_StbM_00425.Calculate.TimeDifference,1 */
      *timeJump = StbM_TimeLeapInfo[commonIndex].timejump;
      retval = E_OK;
    }
    else
    {
      /* StbM_GetTimeLeap() shall return the Global Time difference between the Received Time and the Synclocal Time
       * which is calculated upon each, except the very first, valid invocation of StbM_BusSetGlobalTime()
       *  for the corresponding Time Base.*/
      /* Nothing to do */
      /* !LINKSTO StbM.SWS_StbM_00425.FirstValidInvocationOfBusSetGlobalTime.StbM_GetTimeLeap.Returns.E_NOT_OK,1 */
    }
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }
  DBG_STBM_GETTIMELEAP_EXIT(retval, timeBaseId, timeJump);

  return retval;
} /* StbM_GetTimeLeap */
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */

/* !LINKSTO StbM.SWS_StbM_00390,1 */
/* !LINKSTO StbM.EB.StbM_SetRateCorrection.API.Availability,1 */
#if(STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
FUNC(Std_ReturnType, STBM_CODE) StbM_SetRateCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_RateDeviationType rateDeviation
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
  uint8 detectedDET = 0U;

  /* Get current Virtual Local Time */
  retval = StbM_GetCurrentVirtualLocalTimeNoDet(timeBaseId, &detectedDET,  &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

  DBG_STBM_SETRATECORRECTION_ENTRY(timeBaseId, rateDeviation);

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_SetRateCorrection,1 */
  if(detectedDET == STBM_E_UNINIT)
  {
    retval = E_NOT_OK;
    STBM_DET_REPORTERROR(STBM_API_SETRATECORRECTION, STBM_E_UNINIT);
  }
  /* !LINKSTO StbM.SWS_StbM_00391,1 */
  else if (detectedDET == STBM_E_PARAM)
  {
    retval = E_NOT_OK;
    STBM_DET_REPORTERROR(STBM_API_SETRATECORRECTION, STBM_E_PARAM);
  }
  /* !LINKSTO StbM.SWS_StbM_00392,1 */
  /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_SERVICE_DISABLED.StbM_SetRateCorrection,1 */
  else if(STBM_MASTER_RATE_CORRECTION_TO_COMMON_DISABLED(timeBaseId) == TRUE)
  {
    retval = E_NOT_OK;
    STBM_DET_REPORTERROR(STBM_API_SETRATECORRECTION, STBM_E_SERVICE_DISABLED);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    if(E_OK == retval)
    {
      StbM_TimeStampType currentLocalTime = {0U, 0U, 0U, 0U};
      uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIndex);
      uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

      /* get index for the StbM_MasterRateCorrectionData[] array */
      uint8 rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonIndex);
      uint32 maxRateDeviation = STBM_GET_MASTER_RATE_DEVIATION_MAX(commonIndex);
      /* rccMax = rdMax + 1 */
      uint32 maxRateCorrection = maxRateDeviation + STBM_FACTOR_PPM;
      /* rccMin = (-)rdMin + 1 = 1 - rdMin */
      uint32 minRateCorrection = STBM_FACTOR_PPM - maxRateDeviation;
      /* calculate current rate correction */
      sint32 currentRateCorrectionTemp = rateDeviation + (sint32)STBM_FACTOR_PPM;
      uint32 currentRateCorrection = (uint32)currentRateCorrectionTemp;
      /* rrc in PPM in Q format */
      uint64 rrc_in_ppm_to_q = 0U;
      /* rrc in PPM in Q format */
      uint32 rrc_to_q = 0U;

      /* !LINKSTO StbM.SWS_StbM_00395,1 */
      /* !LINKSTO StbM.SWS_StbM_00396,1 */
      /* check limits of rate correction */
      if(currentRateCorrection >= maxRateCorrection)
      {
        currentRateCorrection = maxRateCorrection;
      }
      else if(currentRateCorrection <= minRateCorrection)
      {
        currentRateCorrection = minRateCorrection;
      }
      else
      {
        /* nothing to do */
      }

      /* transform rrc to Q format */
      rrc_in_ppm_to_q = STBM_UINT64_TO_Q(currentRateCorrection);
      /* divide by the ppm part, to get the actual number */
      rrc_to_q = (uint32)(STBM_NR_FROM_PPM(rrc_in_ppm_to_q));

      /* obtain time */
      (void)StbM_GetTime(timeBaseId, &currentLocalTime, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

      /* enter critical section */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedData,1 */
      SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* assign rrc to be used with next GetCurrentTime */
      /* !LINKSTO StbM.SWS_StbM_00411,1 */
      StbM_MasterRateCorrectionData[rcDataIndex].rrc = rrc_to_q;
      /* assign rate deviation, in case it is requested */
      /* !LINKSTO StbM.SWS_StbM_00422.RateDeviation.Set,1 */
      /* Deviation MISRAC2012-1 */
      StbM_MasterRateCorrectionData[rcDataIndex].rateDev = (StbM_RateDeviationType)(currentRateCorrection - STBM_FACTOR_PPM);

      /* !LINKSTO StbM.SWS_StbM_00433.UpdateMainTimeTuple.AfterSetting.NewRateCorrection,1 */
      /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTime.ReplaceMainTimeTuple.AfterSetting.NewRateCorrection.ByApplication,1 */
      /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTimeExtended.ReplaceMainTimeTuple.AfterSetting.NewRateCorrection.ByApplication,1 */
      /* !LINKSTO StbM.SWS_StbM_00436.StbM_BusGetCurrentTime.ReplaceMainTimeTuple.AfterSetting.NewRateCorrection.ByApplication,1 */

      /* !LINKSTO StbM.SWS_StbM_00442,1 */
      /* !LINKSTO StbM.SWS_StbM_00443,1 */
      /* Update Time Tuple */
      STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[commonIndex].globalTime, currentLocalTime);
      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[commonIndex].virtualLocalTime, localTime);


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_SetRateCorrection,2 */
      StbM_UpdateSharedDataInMemory(timeBaseId, StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, &currentLocalTime, &localTime);
#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
      /* check if time base needs to share data to memory */
      if (sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA)
      {
        /* get array start index for this timebase */
        timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteBegin,1 */
        /* increment the 'begin' counter, this will signal the user that
           data is currently being written */
        Atomics_ThreadFence();
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX]++;
        Atomics_ThreadFence();

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_SetRateCorrection,1 */
        /* update time tuple */
        StbM_UpdateTimeTupleInSharedMemory(commonIndex, timeBaseStartIndex);

        /* update rate correction */
        StbM_UpdateRateDevAndRateCorrInSharedMemory(&StbM_MasterRateCorrectionData[rcDataIndex].rrc, &StbM_MasterRateCorrectionData[rcDataIndex].rateDev, timeBaseStartIndex);

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteEnd,1 */
        /* increment the 'end' counter, this will signal the user that
           data has been written */
        Atomics_ThreadFence();
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX]++;
        Atomics_ThreadFence();
      }
#endif /* (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


      /* reload the update counter */
      StbM_UpdateTimeTupleCounter[commonIndex] = STBM_UPDATE_COUNTER_VALUE;

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
      /* set EV_RESYNC notification event after time was updated */
      /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
      STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_RESYNC);

      /* set EV_RATECORRECTION notification event after Master Rate Correction was calculated and it value was not beyond limits */
      /* !LINKSTO StbM.SWS_StbM_00284.EV_RATECORRECTION.Master,1 */
      STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_RATECORRECTION);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

      /* exit critical section */
      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    }
  }

  DBG_STBM_SETRATECORRECTION_EXIT(retval, timeBaseId, rateDeviation);

  return retval;
} /* StbM_SetRateCorrection */
#endif /*( STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */


#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00319,1 */
/* !LINKSTO StbM.SWS_StbM_00320,1 */
/* !LINKSTO StbM.SWS_StbM_00326,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetSyncTimeRecordHead
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_SyncRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA) syncRecordTableHead
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETSYNCTIMERECORDHEAD_ENTRY(timeBaseId, syncRecordTableHead);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetSyncTimeRecordHead,1 */
    STBM_DET_REPORTERROR(STBM_API_GETSYNCTIMERECORDHEAD, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00394.InvalidId,1 */
    /* !LINKSTO StbM.SWS_StbM_00394.PureLocalTimeBase,1 */
    STBM_DET_REPORTERROR(STBM_API_GETSYNCTIMERECORDHEAD, STBM_E_PARAM);
  }
  /* Deviation TASKING-4 */
  /* Deviation MISRAC2012-4 */
  else if (STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00394.OffsetId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETSYNCTIMERECORDHEAD, STBM_E_PARAM);
  }
  else if (syncRecordTableHead == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00405,1 */
    STBM_DET_REPORTERROR(STBM_API_GETSYNCTIMERECORDHEAD, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* !LINKSTO StbM.SWS_StbM_00315,1 */
    syncRecordTableHead->SynchronizedTimeDomain =
      StbM_SyncRecordTableHeads[timeBaseId].SynchronizedTimeDomain;
    syncRecordTableHead->HWfrequency = StbM_SyncRecordTableHeads[timeBaseId].HWfrequency;
    syncRecordTableHead->HWprescaler = StbM_SyncRecordTableHeads[timeBaseId].HWprescaler;

    retval = E_OK;
  }

  DBG_STBM_GETSYNCTIMERECORDHEAD_EXIT(retval, timeBaseId, syncRecordTableHead);

  return retval;
}
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00325,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeRecordHead
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_OffsetRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA) offsetRecordTableHead
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETOFFSETTIMERECORDHEAD_ENTRY(timeBaseId, offsetRecordTableHead);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetOffsetTimeRecordHead,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSETTIMERECORDHEAD, STBM_E_UNINIT);
  }
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00327.InvalidId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSETTIMERECORDHEAD, STBM_E_PARAM);
  }
  /* Deviation TASKING-4 */
  else if (!STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00327.SyncId,1 */
    /* !LINKSTO StbM.SWS_StbM_00327.PureId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSETTIMERECORDHEAD, STBM_E_PARAM);
  }
  else if (offsetRecordTableHead == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00404,1 */
    STBM_DET_REPORTERROR(STBM_API_GETOFFSETTIMERECORDHEAD, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
#if(STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
    /* !LINKSTO StbM.SWS_StbM_00316,1 */
    offsetRecordTableHead->OffsetTimeDomain =
      StbM_OffsetRecordTableHeads[STBM_OFFSET_ID_TO_0BASED_INDEX(timeBaseId)].OffsetTimeDomain;

    retval = E_OK;
#endif /* #if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
  }

  DBG_STBM_GETOFFSETTIMERECORDHEAD_EXIT(retval, timeBaseId, offsetRecordTableHead);

  return retval;
}
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */


FUNC(void, STBM_CODE) StbM_Init(P2CONST(StbM_ConfigType, AUTOMATIC, STBM_APPL_DATA)ConfigPtr)
{
  uint8 i;
#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
  uint32 k;
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
  uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
  uint16 sharedMemoryIndex;
  uint8 timeBaseId;
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  DBG_STBM_INIT_ENTRY(ConfigPtr);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_INIT_FAILED,1 */
  /* current implementation supports only Precompile variant */
  if(NULL_PTR != ConfigPtr)
  {
    STBM_DET_REPORTERROR(STBM_API_INIT, STBM_E_INIT_FAILED);
  }
  else
#else
  TS_PARAM_UNUSED(ConfigPtr);
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */
  {

#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON))
    /* Deviation TASKING-1 */
    for (i = 0; i<STBM_NUMBER_OF_SYNC_TIMEBASES; i++)
    {
      /*initialize the last Time Tuple which was received through StbM_BusSetGlobalTime*/
      StbM_LastReceivedTimeTuple[i].timeValidationGlobalTime.nanoseconds = 0;
      StbM_LastReceivedTimeTuple[i].timeValidationGlobalTime.seconds = 0;
      StbM_LastReceivedTimeTuple[i].timeValidationVirtualLocalTime.nanosecondsHi = 0;
      StbM_LastReceivedTimeTuple[i].timeValidationVirtualLocalTime.nanosecondsLo = 0;
    }
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)) */
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */

#if ((STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) || (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U))
    /* initialize all informations for SYNC time bases */
    /* !LINKSTO StbM.SWS_StbM_00170,1 */
    /* Deviation TASKING-1 */
    for (i = 0U; i < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES); i++)
    {
#if (STBM_TIMEOUTS_USED == STD_ON)
      /* timeout not active after initialization */
      StbM_TimeBaseTimeout[i] = 0U;
#endif /* STBM_TIMEOUTS_USED == STD_ON */

      /* initialize the time base update counter */
      /* !LINKSTO StbM.dsn.StbM_TimeBaseUpdateCounter.Init,1 */
      /* !LINKSTO StbM.SWS_StbM_00344,1 */
      StbM_TimeBaseUpdateCounter[i]   = 0U;

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
      StbM_RecordTableBlocksInfo[i].counter = StbM_CommonTimeBaseCfg[i].startIndexTrBlocks;
      StbM_RecordTableBlocksInfo[i].wasCounterWrapped = FALSE;
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */
#if (STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
      /* !LINKSTO StbM.SWS_StbM_00170,1 */
      /* Initialize the timeJumpCalculated and the timejump */
      StbM_TimeLeapInfo[i].timeJumpCalculated = FALSE;
      StbM_TimeLeapInfo[i].timejump = 0;
      /* Initialize time leap counter for the clearing of the time leap bits */
#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
      StbM_TimeLeapInfo[i].future = 0U;
      StbM_TimeLeapInfo[i].past = 0U;
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */
    }
#endif /* ((STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) || (STBM_NUMBER_OF_OFFSET_TIMEBASES > 0U)) */

    /* Deviation TASKING-1 */
    for (i = 0U; i < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); i++)
    {
#if (STBM_NVM_USED == STD_ON)
      if(STBM_STORE_AND_LOAD_TIME_NVM_DISABLED(i))
      {
        /* initialize all time information with 0 */
        STBM_INIT_TIMETUPLE_0(StbM_TimeStamps[i]);
      }
      else /* store and load TimeStamp in NvM */
      {
        NvM_RequestResultType result = NVM_REQ_NOT_OK;
        /* !LINKSTO StbM.SWS_StbM_00171,1 */
        /* !LINKSTO StbM.SWS_StbM_00172,1 */
        /* Call NvM_GetErrorStatus API to check if the time was successfully read */
        if((E_OK == NvM_GetErrorStatus(STBM_GET_NVM_BLOCK_ID(i), &result)) && (result == NVM_REQ_OK))
        {
          /* Call Nvm_SetRamBlockStatus API in order to notify NvM that each time when
           * TimeStamp is changed, it shall be stored in NvM at SHUTDOWN phase
           * and loaded from NvM at INIT phase*/
          STBM_TIMESTAMP_MODIFIED(i);
          /* Init timeBaseStatus to 0U */
          /* !LINKSTO StbM.EB.NvM.timeBaseStatus,1 */
          StbM_TimeStamps[i].globalTime.timeBaseStatus = 0U;

          /* initialize the virtual local time */
          STBM_INIT_VIRTUAL_LOCAL_TIME_0(StbM_TimeStamps[i].virtualLocalTime);
        }
        else /* an error occured while loading the time from NvM */
        {
          /* initialize all time information with 0 */
          STBM_INIT_TIMETUPLE_0(StbM_TimeStamps[i]);
        }
      }
#else /* No NvM used */
      /* initialize all time information */
      STBM_INIT_TIMETUPLE_0(StbM_TimeStamps[i]);
#endif /* (STBM_NVM_USED == STD_ON) */

/* Init the clone structure*/
#if ( STBM_SOURCE_TIMEBASES_USED == STD_ON)
      StbM_CloneDataArr[i].srcTimeBaseId = STBM_NO_SOURCE_TIME_BASE;
      StbM_CloneDataArr[i].cloneCfg = 0U;
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */
      /* initialize the user data */
      /* !LINKSTO StbM.SWS_StbM_00427,1 */
      StbM_UserData[i].userDataLength = 0U;
      StbM_UserData[i].userByte0      = 0U;
      StbM_UserData[i].userByte1      = 0U;
      StbM_UserData[i].userByte2      = 0U;

      /* initialize update counter with 3 sec */
      StbM_UpdateTimeTupleCounter[i] = STBM_UPDATE_COUNTER_VALUE;

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
      /* load StbM_SharedDataTimeout */
      STBM_RESTART_SHAREDDATA_TIMEOUT(i);
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */

#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      /* initialize StbM_NewTimeTupleValue with zero */
      StbM_NewTimeTupleValue[i] = FALSE;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */

#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

      /* initialize shared data */
#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
      sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(i);

      if(sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA)
      {
        timeBaseId = STBM_COMMON_INDEX_TO_TIMEBASEID(i);

        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].WriteBeginCnt = 0U;

        /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.TimeBaseId,2 */
        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].TimeBaseId = timeBaseId;

        STBM_INIT_TIMESTAMP_0(StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].OffsetTime);

        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].OffsetSign = 0U;

        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].RateDeviation = STBM_RATE_DEVIATION_DEFAULT_VALUE;

        StbM_SharedEthOffsetData.Offset[sharedMemoryIndex].WriteEndCnt = 0U;
      }
#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
      sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(i);

      if(sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA)
      {
        timeBaseId = STBM_COMMON_INDEX_TO_TIMEBASEID(i);

        /* get array start index for this timebase */
        timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

        /* beginCounter */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX] = 0U;

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.TimeBaseId,1 */
        /* timeBaseId */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_TIMEBASEID_STARTINDEX] = timeBaseId;

        /* TG - timeBaseStatus */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX] = 0x00U;
        /* TG - nanoseconds */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 1U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 2U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 3U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 4U] = 0x00U;
        /* TG- seconds */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 5U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 6U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 7U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 8U] = 0x00U;
        /* TG - secondsHi */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 9U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_GLOBALTIME_STARTINDEX + 10U] = 0x00U;
        /*  VLT - nanosecondsLo */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 1U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 2U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 3U] = 0x00U;
        /*  VLT - nanosecondsHi */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 4U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 5U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 6U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_VIRTUALLOCALTIME_STARTINDEX + 7U] = 0x00U;

        /* STBM_RATE_DEVIATION_INVALID_VALUE rateDeviation */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATEDEVIATION_STARTINDEX] = 0x7DU;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATEDEVIATION_STARTINDEX + 1U] = 0x01U;

        /* STBM_RATE_CORRECTION_DEFAULT_VALUE rateCorrection  */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX] = 0x10U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 1U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 2U] = 0x00U;
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_RATECORRECTION_STARTINDEX + 3U] = 0x00U;

        /* endCounter */
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX] = 0U;
      }

#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
       /* !LINKSTO StbM.SWS_StbM_00345,1 */
       StbM_TimeBaseNotificationEvents[i] = 0U;
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */
    }

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.Version,2 */
    StbM_SharedEthOffsetData.Version = 1U;
    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.NrOfTimeBases,2 */
    StbM_SharedEthOffsetData.TimeBasesNumber = STBM_NUMBER_TIME_BASES_THAT_SHARE_DATA_MODULES;
#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
    /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.Version,1 */
    StbM_SharedData[STBM_SHAREDDATA_VERSION_STARTINDEX] = 0x02U;
    /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.NrOfTimeBases,1 */
    StbM_SharedData[STBM_SHAREDDATA_TIMEBASENUMBER_STARTINDEX] = (uint8)((uint32)(STBM_NUMBER_TIME_BASES_THAT_SHARE_DATA_MODULES & STBM_32BIT_MASK1) >> 8U);
    StbM_SharedData[STBM_SHAREDDATA_TIMEBASENUMBER_STARTINDEX + 1U] = (uint8)(STBM_NUMBER_TIME_BASES_THAT_SHARE_DATA_MODULES & STBM_32BIT_MASK0_LSB);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


#if (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON)
    /* Deviation TASKING-1 */
    for (i = 0U; i < STBM_NUMBER_OF_TRIGGERED_CUSTOMERS; i++)
    {
      StbM_TriggeredCustomerThreshold[i] = StbM_TriggerCustomerCfg[i].invocationNumber;
    }
#endif /* STBM_TRIGGERED_CUSTOMERS_USED == STD_ON */

#if (STBM_RATE_CORRECTION_USED)
    StbM_RateCorrectionDataInit();
#endif /* (STBM_RATE_CORRECTION_USED) */

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    /* !LINKSTO StbM.SWS_StbM_00306,1 */
    /* !LINKSTO StbM.SWS_StbM_00314,1 */
    StbM_Init_SyncRecordTableBlock(&StbM_SyncRecordTableBlocks[0U]);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
    /* !LINKSTO StbM.SWS_StbM_00306,1 */
    StbM_Init_OffsetRecordTableBlock(&StbM_OffsetRecordTableBlocks[0U]);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
    StbM_TimeValidationDataInit();
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


#if (STBM_OS_COUNTER_USED == STD_ON)
    {
      /* call counter function to equal the previous value to the current value
         to create a "zero-point" during initialization. */
      TickType osTicksBasedOn_OsCounter = 0U;    /* use default value if call fails */
      (void) StbM_Os_GetCounterValue(STBM_OS_COUNTER_ID, &osTicksBasedOn_OsCounter);
      StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter = osTicksBasedOn_OsCounter;

      /* initialize all time information regarding Virtual Local Time */
      STBM_INIT_VIRTUAL_LOCAL_TIME_0(StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OsCounter);
    }
#endif /* STBM_OS_COUNTER_USED == STD_ON */


#if (STBM_OSGETTIMESTAMP_USED == STD_ON)
    {
      /* call OS_GetTimeStamp function to equal the previous value to the current value
         to create a "zero-point" during initialization. */
      /* intentionally uninitialized since os_timestamp_t can also be a structure */
      os_timestamp_t osTicks_OSGetTimeStamp;    /* use default value if call fails */
      OS_GetTimeStamp(&osTicks_OSGetTimeStamp);
      StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OSGetTimeStamp = osTicks_OSGetTimeStamp;

      /* initialize all time information regarding Virtual Local Time */
      STBM_INIT_VIRTUAL_LOCAL_TIME_0(StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OSGetTimeStamp);
    }
#endif /* STBM_OSGETTIMESTAMP_USED == STD_ON */



#if (STBM_GPT_USED == STD_ON)
    /* Deviation TASKING-1 */
    for(i = 0U; i < STBM_NUMBER_OF_GPT_TIMEBASES; i++)
    {
      /* call counter function to equal the previous value to the current value
         to create a "zero-point" during initialization. */
      /* !LINKSTO StbM.dsn.GptTimeSource,1 */
      Gpt_StartTimer(StbM_GptTimeBases[i].gptChannelId, StbM_GptTimeBases[i].gptMaxChannelTickValue);
      StbM_VirtualLocalTimeSources.StbM_PreviousGptTicks[i] = 0U;

      /* initialize all time information regarding Virtual Local Time */
      STBM_INIT_VIRTUAL_LOCAL_TIME_0(StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_Gpt[i]);
    }
#endif /* STBM_GPT_USED == STD_ON */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)

    Head = NULL_PTR;
    Last = NULL_PTR;
    StbM_IsGptTimeRunning = FALSE;

    /* initialize all time notification related data */
    /* Deviation TASKING-1 */
    for(k = 0U; k < STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS; k++)
    {
      StbM_TimeNotificationDataInit(k);
    }

    /* When Gpt_EnableNotification() is called, STBM_GPT_CHANNEL_USED_FOR_STARTING_GPTTIMER Gpt timer channel
     * will be able to call a notification function when target time is reached */
    /* !LINKSTO StbM.EB.StbM_Init.Calls.Gpt_EnableNotification,1 */
    Gpt_EnableNotification(STBM_GPT_CHANNEL_USED_FOR_STARTING_GPTTIMER);

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */



    /* StbM changes state to initialized. */
    StbM_InitStatus = STBM_INIT;

  }

  DBG_STBM_INIT_EXIT(ConfigPtr);
} /* StbM_Init */



#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED)

STATIC FUNC(void, STBM_CODE) StbM_TimeNotificationDataInit
(
  uint32 timeNotificationDataIndex
)
{


  StbM_ExpireTimeData[timeNotificationDataIndex].previous = NULL_PTR;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.timeBaseId = 0xFFFFU;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.customerId = 0xFFU;
  STBM_INIT_TIMESTAMP_0(StbM_ExpireTimeData[timeNotificationDataIndex].Data.customerTimerExpireTime);
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.isGptTimerRunning = FALSE;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.pendingStartGptTimer = FALSE;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.isTimerExpiredInGpt = FALSE;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.arrayCellIndex = 0U;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.isArrayCellEmpty = TRUE;
  StbM_ExpireTimeData[timeNotificationDataIndex].Data.calculatedTimeDeviation = 0U;
  StbM_ExpireTimeData[timeNotificationDataIndex].next = NULL_PTR;

}

#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED) */



#if (STBM_RATE_CORRECTION_USED)
STATIC FUNC(void, STBM_CODE) StbM_RateCorrectionDataInit
(
  void
)
{
  uint8 i;
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  uint8 stopValuesIndex = 0U;
  uint8 startValuesIndex = 0U;
  uint8 rcDataIndex = 0U;
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  /* Deviation TASKING-1 */
  for (i = 0U; i < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES); i++)
  {
    stopValuesIndex = StbM_CommonTimeBaseCfg[i].stopIndexRcIntervals;

    /* This implies that if the value is not 0, Rate Correction is used */
    if((StbM_CommonTimeBaseCfg[i].rateCorrectionIntervalNs != 0U) || (StbM_CommonTimeBaseCfg[i].rateCorrectionIntervalSec != 0U))
    {
      rcDataIndex = StbM_CommonTimeBaseCfg[i].intervalArrayIndex;
      startValuesIndex = StbM_CommonTimeBaseCfg[i].startIndexRcIntervals;
      /* Initialize data */
      StbM_SlaveDataInit(rcDataIndex, startValuesIndex, stopValuesIndex);
    }
  }
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */

/* !LINKSTO StbM.SWS_StbM_00424.AllowRate,1 */
#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
  /* Deviation TASKING-1 */
  for (i = 0U; i < STBM_NUMBER_OF_SLAVE_RATE_CORRECTION_TIMEBASES; i++)
  {
    StbM_SlaveRateCorrectionData[i].roc = STBM_RATE_DEVIATION_DEFAULT_VALUE;
    StbM_SlaveRateCorrectionData[i].rocSign = STBM_SIGN_IS_POSITIVE;
    StbM_SlaveRateCorrectionData[i].beforeAdaptionInterval = FALSE;
  }
#endif /* STBM_OFFSET_CORRECTION_USED == STD_ON */

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
  /* Deviation TASKING-1 */
  for (i = 0U; i < STBM_NUMBER_OF_MASTER_RATE_CORRECTION_TIMEBASES; i++)
  {
    /* !LINKSTO StbM.SWS_StbM_00431.MasterRateCorrection.Sync,1 */
    /* !LINKSTO StbM.SWS_StbM_00431.MasterRateCorrection.Offset,1 */
    /* !LINKSTO StbM.EB.SWS_StbM_00431.MasterRateCorrection.Pure,1 */
    StbM_MasterRateCorrectionData[i].rrc = STBM_RATE_CORRECTION_DEFAULT_VALUE;
    StbM_MasterRateCorrectionData[i].rateDev = STBM_RATE_DEVIATION_INVALID_VALUE;
  }
#endif /* (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */

}
#endif /* STBM_RATE_CORRECTION_USED */




#if (STBM_TIME_VALIDATION_SUPPORT)

STATIC FUNC(void, STBM_CODE) StbM_InitTimeValidationInfo
(
  uint32 idx,
  P2VAR(StbM_TimeValidationInfoType, AUTOMATIC, STBM_VAR) timeValidationInfo,
  boolean isMaster,
  boolean isPdelay
)
{

  /* pdelay is used */
  if(isPdelay == FALSE)
  {
    /* master */
    if(isMaster == TRUE)
    {
      /* counter starts from startIndexTrBlocksTimeValidationMASTERPart */
      (*timeValidationInfo).counter = StbM_CommonTimeBaseCfg[idx].startIndexTrBlocksTimeValidationMASTERPart;
    }
    else /* slave */
    {
      /* counter starts from startIndexTrBlocksTimeValidationSLAVEPart */
      (*timeValidationInfo).counter = StbM_CommonTimeBaseCfg[idx].startIndexTrBlocksTimeValidationSLAVEPart;
    }
  }
  else /* pdelay is not used */
  {
    /* master */
    if(isMaster == TRUE)
    {
      /* counter starts from startIndexTrBlocksTimeValidationMASTERPdelayPart */
      (*timeValidationInfo).counter = StbM_CommonTimeBaseCfg[idx].startIndexTrBlocksTimeValidationMASTERPdelayPart;
    }
    else /* slave */
    {
      /* counter starts from startIndexTrBlocksTimeValidationSLAVEPdelayPart */
      (*timeValidationInfo).counter = StbM_CommonTimeBaseCfg[idx].startIndexTrBlocksTimeValidationSLAVEPdelayPart;
    }
  }

  (*timeValidationInfo).wasCounterWrapped = FALSE;

}


STATIC FUNC(void, STBM_CODE) StbM_InitTimeValidationInfoBlocks
(
  void
)
{
  uint32 j;


  /* Deviation TASKING-1 */
  for (j = 0U; j < STBM_NUMBER_OF_SYNC_TIMEBASES; j++)
  {

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[j].canTSynMasterTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_CanMasterTimingDataRecordTableBlocksInfo[j], TRUE, FALSE);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[j].frTSynMasterTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_FrMasterTimingDataRecordTableBlocksInfo[j], TRUE, FALSE);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[j].canTSynSlaveTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_CanSlaveTimingDataRecordTableBlocksInfo[j], FALSE, FALSE);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[j].frTSynSlaveTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_FrSlaveTimingDataRecordTableBlocksInfo[j], FALSE, FALSE);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
    if(StbM_CallbacksPtrList[j].ethTSynMasterTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_EthMasterTimingDataRecordTableBlocksInfo[j], TRUE, FALSE);
    }
    if(StbM_CallbacksPtrList[j].ethTSynPdelayResponderTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[j], TRUE, TRUE);
    }
    if(StbM_CallbacksPtrList[j].ethTSynSlaveTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_EthSlaveTimingDataRecordTableBlocksInfo[j], FALSE, FALSE);
    }
    if(StbM_CallbacksPtrList[j].ethTSynPdelayInitiatorTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_InitTimeValidationInfo(j, &StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[j], FALSE, TRUE);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */
  }

}


STATIC FUNC(void, STBM_CODE) StbM_TimeValidationDataInit
(
  void
)
{

  /* initialize all informations for SYNC time bases which have time validation activated */
  /* !LINKSTO StbM.SWS_StbM_00170,1 */
  StbM_InitTimeValidationInfoBlocks();


  /* initialize all [Bus][Master/Slave]TimingData blocks */
  /* !LINKSTO StbM.SWS_StbM_00170,1 */

  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_CanMasterTimingData.InitializedWith0,1 */
#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
  StbM_Init_CanTimeMasterMeasurement(&StbM_CanMasterTimingData[0U]);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */

  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_FrMasterTimingData.InitializedWith0,1 */
#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
  StbM_Init_FrTimeMasterMeasurement(&StbM_FrMasterTimingData[0U]);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */

  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_CanSlaveTimingData.InitializedWith0,1 */
#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
  StbM_Init_CanTimeSlaveMeasurement(&StbM_CanSlaveTimingData[0U]);
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */

  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_FrSlaveTimingData.InitializedWith0,1 */
#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
  StbM_Init_FrTimeSlaveMeasurement(&StbM_FrSlaveTimingData[0U]);
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */

  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_EthMasterTimingData.InitializedWith0,1 */
  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_EthPdelayResponderTimingData.InitializedWith0,1 */
  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_EthSlaveTimingData.InitializedWith0,1 */
  /* !LINKSTO StbM.EB.SWS_StbM_00306.StbM_EthPdelayInitiatorTimingData.InitializedWith0,1 */
#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
  StbM_Init_EthTimeMasterMeasurement(&StbM_EthMasterTimingData[0U]);
  StbM_Init_PdelayResponderMeasurement(&StbM_EthPdelayResponderTimingData[0U]);
  StbM_Init_EthTimeSlaveMeasurement(&StbM_EthSlaveTimingData[0U]);
  StbM_Init_PdelayInitiatorMeasurement(&StbM_EthPdelayInitiatorTimingData[0U]);
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */

}


#endif /* STBM_TIME_VALIDATION_SUPPORT */





#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SlaveDataInit
(
  uint8 rcDataIndex,
  uint8 startValuesIndex,
  uint8 stopValuesIndex
)
{

  StbM_SlaveDataReinitMeasurements(rcDataIndex, startValuesIndex, stopValuesIndex);

  STBM_INIT_TIMETUPLE_0( StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData);
  StbM_SlaveRateCorrectionData[rcDataIndex].initialFlags = 0U;
  StbM_SlaveRateCorrectionData[rcDataIndex].updatedFlags = 0U;
  StbM_SlaveRateCorrectionData[rcDataIndex].newValues = FALSE;
  StbM_SlaveRateCorrectionData[rcDataIndex].syncToGateway = STBM_SYNC_TO_GATEWAY_FLAG;
  /* !LINKSTO StbM.SWS_StbM_00412.SlaveRateCorrection.Sync,1 */
  /* !LINKSTO StbM.SWS_StbM_00412.SlaveRateCorrection.Offset,1 */
  StbM_SlaveRateCorrectionData[rcDataIndex].rrc = STBM_RATE_CORRECTION_DEFAULT_VALUE;
  StbM_SlaveRateCorrectionData[rcDataIndex].rateDev = STBM_RATE_DEVIATION_INVALID_VALUE;

} /* StbM_SlaveDataInit */

STATIC FUNC(void, STBM_CODE) StbM_SlaveDataReinitMeasurements
(
  uint8 rcDataIndex,
  uint8 startValuesIndex,
  uint8 stopValuesIndex
)
{
  uint8 j;


  STBM_INIT_TIMESTAMP_0(StbM_SlaveRateCorrectionStartValues[startValuesIndex].startGlobalTime);
  STBM_INIT_VIRTUAL_LOCAL_TIME_0(StbM_SlaveRateCorrectionStartValues[startValuesIndex].startVirtualLocalTime);

  for (j = (startValuesIndex + 1U); j <= stopValuesIndex; j++)
  {
    STBM_INIT_TIMESTAMP_0(StbM_SlaveRateCorrectionStartValues[j].startGlobalTime);
    STBM_INIT_VIRTUAL_LOCAL_TIME_1(StbM_SlaveRateCorrectionStartValues[j].startVirtualLocalTime);
  }

  StbM_SlaveRateCorrectionData[rcDataIndex].intervalCounter = startValuesIndex;
  StbM_SlaveRateCorrectionData[rcDataIndex].discardMeasurementCounter = (stopValuesIndex - startValuesIndex) + 1U;

} /* StbM_SlaveDataReinitMeasurements */
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */

#if (STBM_VERSION_INFO_API == STD_ON)
FUNC(void,STBM_CODE) StbM_GetVersionInfo
(
  P2VAR(Std_VersionInfoType,AUTOMATIC,STBM_APPL_DATA) versioninfo
)
{
  DBG_STBM_GETVERSIONINFO_ENTRY(versioninfo);

  /* !LINKSTO StbM.SWS_StbM_00094,1 */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if (versioninfo == NULL_PTR)
  {
    STBM_DET_REPORTERROR(STBM_API_GETVERSIONINFO, STBM_E_PARAM_POINTER);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    versioninfo->vendorID         = STBM_VENDOR_ID;
    versioninfo->moduleID         = STBM_MODULE_ID;
    versioninfo->sw_major_version = STBM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = STBM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = STBM_SW_PATCH_VERSION;
  }

  DBG_STBM_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* #if (STBM_VERSION_INFO_API == STD_ON) */



#if ( (STBM_SOURCE_TIMEBASES_USED == STD_ON) && (STBM_TIMEOUTS_USED == STD_ON) )
STATIC FUNC(void, STBM_CODE)  StbM_Check_Pending_Clone_When_Timeout(uint8 srcIndex)
{
  uint8 destIndex;
  StbM_SynchronizedTimeBaseType srcTimeIndex;
  /* for SynC Time bases IDs only as (srcIndex <= STBM_NUMBER_OF_SYNC_TIMEBASES)*/
  for( destIndex = 0; destIndex<(STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES) ; destIndex++ )
  {
      srcTimeIndex = StbM_CloneDataArr[destIndex].srcTimeBaseId;
      if(srcTimeIndex == srcIndex)
      {
          /* !LINKSTO StbM.SWS_StbM_00531.AR-117132,1 */
          /* remove any pending deferred clone request as Timeout happens */
          StbM_CloneDataArr[destIndex].srcTimeBaseId = STBM_NO_SOURCE_TIME_BASE;
      }
  }
}
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */

/* !LINKSTO StbM.SWS_StbM_00057,1 */
/* !LINKSTO StbM.SWS_StbM_00407,1 */
FUNC(void, STBM_CODE) StbM_MainFunction(void)
{
#if  (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
  boolean listEmpty = TRUE;
  StbM_LocalTimeCallType localTimes[STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES];
#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
  StbM_TimeBaseNotificationType TBNotification = 0U;
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if ((STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) || ((STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) && (STBM_TIMEOUTS_USED == STD_ON)))
  uint16 sharedMemoryIndex = 0U;
#endif /* ((STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) || ((STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) && (STBM_TIMEOUTS_USED == STD_ON))) */
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
  uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */
  DBG_STBM_MAINFUNCTION_ENTRY();

  /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_MainFunction,1 */
  if (StbM_InitStatus == STBM_INIT)
  {
    uint8 idx;

#if  (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
    StbM_Init_LocalTimeCall(&localTimes[0U]);
#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON)
    /* Deviation TASKING-1 */
    for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); idx++)
    {
      /* get shared memory index */
      sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(idx);

      /* update shared data in memory */
      /* check if time base needs to share data to memory */
      if ((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[idx].timeBaseRoleSharedData == STBM_TIME_BASE_CONSUMER_SHARED_DATA))
      {
        /* Defensive programming */
        STBM_PRECONDITION_ASSERT(StbM_SharedDataTimeout[idx] != 0U,DET_INTERNAL_API_ID);

        /* counter value is given in Mainfunction invocations */
        -- StbM_SharedDataTimeout[idx];

        /* update shared data when SharedDataTimeout has expired */
        if (StbM_SharedDataTimeout[idx] == 0U)
        {
          /* get array start index for this timebase */
          timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

          /* enter critical section */
          SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

          /* before using time base data from shared memory, check that it was succesfully written */
          if(StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX] == StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX])
          {
            /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeConsumer.When.StbM_MainFunction.StbMSharedDataTimeout_Expired,1 */
            /* read data from shared memory */
            StbM_ReadDataFromSharedMemory(idx, timeBaseStartIndex);

            /* reload the update counter */
            StbM_UpdateTimeTupleCounter[idx] = STBM_UPDATE_COUNTER_VALUE;
          }

          /* exit critical section */
          SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

          /* reload shared data timeout */
          STBM_RESTART_SHAREDDATA_TIMEOUT(idx);
        }

      }
    }
#endif /* (STBM_SHAREDDATA_CONSUMER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


    /* Deviation TASKING-1 */
    for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); idx++)
    {
      boolean updateTimeTuple = FALSE;

      SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      if(0U == StbM_UpdateTimeTupleCounter[idx])
      {
        /* Update Time Tuple because 3 seconds have passed with no update */
        updateTimeTuple = TRUE;
      }
      else
      {
        StbM_UpdateTimeTupleCounter[idx]--;
      }

      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      if(updateTimeTuple)
      {
        StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};
        uint8 timeBaseId = STBM_COMMON_INDEX_TO_TIMEBASEID(idx);
        /* Calculate and update local time and also set EV_RESYNC event notification if status notification is enabled */
        /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
        /* Update time tuple if there was no update for 3 seconds */
        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_MainFunction.NoUpdateFor3Seconds,1 */
        (void) StbM_CalculateLocalTimeAndUpdate(timeBaseId, &timeStampLocalTime);
      }
    }


  /* !LINKSTO StbM.SWS_StbM_00084,1 */
#if (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON)
    /* Deviation TASKING-1 */
    for (idx = 0U; idx < STBM_NUMBER_OF_TRIGGERED_CUSTOMERS; idx++)
    {
      /* count the number of elapsed MainFunction invocations
       * The configuration ensures that the threshold value is at least 1.
       * Therefore no underflow happens here. */
      -- StbM_TriggeredCustomerThreshold[idx];

      /* check if the threshold is reached */
      if (StbM_TriggeredCustomerThreshold[idx] == 0U)
      {
        /* reload value from configuration */
        StbM_TriggeredCustomerThreshold[idx] = StbM_TriggerCustomerCfg[idx].invocationNumber;
        /* synchronize schedule table */
        /* !LINKSTO StbM.SWS_StbM_00107,1 */
        StbM_SyncTriggeredCustomer(idx, StbM_TriggerCustomerCfg[idx].syncTimeBaseIndex);
      }
      else
      {
        /* do nothing */
      }
    }
#endif /* STBM_TRIGGERED_CUSTOMERS_USED == STD_ON */


#if ((STBM_TIMEOUTS_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON))
    /* enter critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseTimeout,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeStamps,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
    /* !LINKSTO StbM.SWS_StbM_00317.DataIntegrity,1 */
    /* !LINKSTO StbM.SWS_StbM_00318.DataIntegrity,1 */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.PassingBlockToAplication.TimeMaster,1 */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.PassingBlockToAplication.TimeSlave,1 */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.PassingBlockToAplication.PdelayResponder,1 */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.PassingBlockToAplication.PdelayInitiator,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
#endif /* ((STBM_TIMEOUTS_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)) */


#if ((STBM_TIMEOUTS_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) || ((STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) && (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)))
#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
    /* Deviation TASKING-1 */
    for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES); idx++)
    {

#if (STBM_TIMEOUTS_USED == STD_ON)
      /* do timeout handling if counter is running (= if not zero) */
      if (StbM_TimeBaseTimeout[idx] != 0U)
      {
        /* counter value is given in Mainfunction invocations */
        -- StbM_TimeBaseTimeout[idx];

        /* !LINKSTO StbM.SWS_StbM_00187.SET_SYNC_TO_GATEWAY_BIT,1 */
        if (StbM_TimeBaseTimeout[idx] == 0U)
        {
          uint8 syncIndex = 0U;
          uint8 flags = 0U;
          /* offset time base case */
#if(STBM_NUMBER_OF_OFFSET_TIMEBASES != 0U)
          if(idx >= STBM_NUMBER_OF_SYNC_TIMEBASES)
          {
            /* get underlying sync index */
            syncIndex = STBM_GET_SYNC_TIMEBASE_INDEX_FROM_ZERO_BASED_OFFSET((idx - STBM_NUMBER_OF_SYNC_TIMEBASES));
          }
          else
#endif /* (STBM_NUMBER_OF_OFFSET_TIMEBASES != 0U) */
          {
            /* get underlying sync index */
             syncIndex = idx;


#if ( STBM_SOURCE_TIMEBASES_USED == STD_ON)
             StbM_Check_Pending_Clone_When_Timeout(syncIndex);
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */
          }

          /* A timeout occurring for a time base acting as gateway means that the time master
           * has failed sending periodic time updates. In this case the gateway shall set
           * the SYNC_TO_GATEWAY_FLAG to signalize the time slave (to which the gateway forwards
           * the time) that the gateway overtook the role as time provider. */
          if(StbM_SyncTimeBaseCfg[syncIndex].role == STBM_ROLE_GATEWAY)
          {
#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
            if(!(STBM_FLAG_IS_SET(StbM_TimeStamps[idx].globalTime.timeBaseStatus, STBM_SYNC_TO_GATEWAY_FLAG)))
            {
              /* Transition from 0 to 1. */
              /* !LINKSTO StbM.SWS_StbM_00284.EV_SYNC_TO_SUBDOMAIN,1 */
              STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[idx], STBM_EV_SYNC_TO_SUBDOMAIN);
            }
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */
            flags = STBM_SYNC_TO_GATEWAY_FLAG;
          }
          else
          {
            flags = 0U;
          }

          /* timeout occurred */
          /* !LINKSTO StbM.SWS_StbM_00183.SET_TIMEOUT_BIT,1 */
          /* !LINKSTO StbM.SWS_StbM_00187.SET_TIMEOUT_BIT,1 */
          STBM_FLAG_SET(flags, STBM_TIMEOUT_FLAG);

          /* write flags to global timestamp */
          STBM_FLAG_SET(StbM_TimeStamps[idx].globalTime.timeBaseStatus, flags);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
          /* get shared memory index */
          sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(idx);
          /* update SharedData_V1 in shared memory */
          StbM_UpdateSharedStatusInMemory(sharedMemoryIndex, StbM_TimeStamps[idx].globalTime.timeBaseStatus);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
          STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[idx], STBM_EV_TIMEOUT_OCCURRED);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

        }
      }
#endif /* (STBM_TIMEOUTS_USED == STD_ON) */


#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
      /* !LINKSTO StbM.EB.RateCorrectionCalcualtion.OutsideOfBusSetGlobalTime,1 */
      StbM_HandleSlaveRateCorrection(idx);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

    }
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */
#endif /* (STBM_TIMEOUTS_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) || ((STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) && (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1))) */


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
    /* Deviation TASKING-1 */
    for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); idx++)
    {
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
      /* get rate correction array index */
      uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(idx);
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
      /* check if there were new values received for time tuple */
      if((StbM_NewTimeTupleValue[idx] == TRUE) && (STBM_OFFSET_CORRECTION_DISABLED(idx) == TRUE))
#else /* (STBM_OFFSET_CORRECTION_USED == STD_OFF) */
       /* check if there were new values received for time tuple */
      if(StbM_NewTimeTupleValue[idx] == TRUE)
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */
      {
        /* get shared memory index */
        sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(idx);

        /* update shared data in memory */
        /* check if time base needs to share data to memory */
        if((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[idx].timeBaseRoleSharedData == STBM_TIME_BASE_PROVIDER_SHARED_DATA))
        {
          /* get array start index for this timebase */
          timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));


          /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteBegin,1 */
          /* increment the 'begin' counter, this will signal the user that
             data is currently being written */
          Atomics_ThreadFence();
          StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX]++;
          Atomics_ThreadFence();

          /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_MainFunction.AfterRateCorrectionCalculation,1 */
          /* update time tuple */
          StbM_UpdateTimeTupleInSharedMemory(idx, timeBaseStartIndex);
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
          if(STBM_SLAVE_RATE_CORRECTION_DISABLED(idx) == FALSE)
          {
            /* update rate correction */
            StbM_UpdateRateDevAndRateCorrInSharedMemory(&StbM_SlaveRateCorrectionData[rcDataIndex].rrc, &StbM_SlaveRateCorrectionData[rcDataIndex].rateDev, timeBaseStartIndex);
          }
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

          /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteEnd,1 */
          /* increment the 'end' counter, this will signal the user that
             data has been written */
          Atomics_ThreadFence();
          StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX]++;
          Atomics_ThreadFence();

          /* reset StbM_NewTimeTupleValue variable */
          StbM_NewTimeTupleValue[idx] = FALSE;
        }
      }
    }
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
    listEmpty = STBM_ISLISTEMPTY();
#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */


#if ((STBM_TIMEOUTS_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON))
    /* leave critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
#endif /* ((STBM_TIMEOUTS_USED == STD_ON) || (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON))
    StbM_SendCanTSynTimingData();
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)) */

#if ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON))
    StbM_SendFrTSynTimingData();
#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)) */

#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
    StbM_SendEthTSynTimingData();
    StbM_SendEthTSynPdelayTimingData();
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
    /* send the record table blocks */
    StbM_SendMeasurementData();
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */


#if(STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
    if(listEmpty == FALSE)
    {
      uint8 jdx;

      /* Deviation TASKING-1 */
      for(jdx = 0U; jdx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); jdx++)
      {
        uint8 timeBaseId = STBM_COMMON_INDEX_TO_TIMEBASEID(jdx);
        /* calculate local time of time bases */
        localTimes[jdx].retVal = StbM_CalculateLocalTime(timeBaseId, &localTimes[jdx].localTime);
      }

      /* First handle expiry points for which Gpt Timer has expired */
      StbM_SendNotificationForExpiryPointsWithGptTimerAlreadyExpired();

      /* Second handle expiry points for which Gpt_StartTimer() chouldn't be called when it was the case */
      StbM_HandleExpiryPointsWithPendingStartGptTimer(localTimes);

      /* Third calculate the difference between customer timer expire time and the current time base time
       * and check if passed over start threshold */
      StbM_DifferencePassedOverStartThreshold(localTimes);
    }
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */


#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
    for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); idx++)
    {
      /* local variable used in order to avoid compiler warning */
      /* Clear the buffer for notification events if the callback was called at least for one time */
      /* !LINKSTO StbM.SWS_StbM_00280,1 */
      TBNotification = (StbM_TimeBaseNotificationType) (Atomics_Exchange(&StbM_TimeBaseNotificationEvents[idx], (Atomic_value_t)0U));
      if(TBNotification != 0U)
      {
        uint8 timeBaseId = STBM_COMMON_INDEX_TO_TIMEBASEID(idx);
        /* Report EV_RESYNC, STBM_EV_SYNC_TO_SUBDOMAIN, STBM_EV_TIMEOUT_OCCURRED and STBM_EV_RATECORRECTION notification events */
        /* !LINKSTO StbM.SWS_StbM_00282.Callback_CalledOneTime,1 */
        /* !LINKSTO StbM.SWS_StbM_00282.SRInterface_CalledOneTime,1 */
        /* !LINKSTO StbM.SWS_StbM_00526,1 */
        StbM_StatusEventDetection(timeBaseId, TBNotification);
      }
    }
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */



  } /* StbM_InitStatus == STBM_INIT */

  DBG_STBM_MAINFUNCTION_EXIT();
}



#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopySyncMeasurementDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_VAR) syncRecordTableBlocks
)
{
  uint32 idx = 0U;

  /* copy sync blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_SyncRecordTableBlocks[] into a local variable */
    STBM_ASSIGN_SYNC_RECORDTABLEBLOCK(syncRecordTableBlocks[idx], StbM_SyncRecordTableBlocks[idx]);
  }

}
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyOffsetMeasurementDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_VAR) offsetRecordTableBlocks
)
{
  uint32 idx = 0U;

  /* copy offset blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_OffsetRecordTableBlocks[] into a local variable */
    STBM_ASSIGN_OFFSET_RECORDTABLEBLOCK(offsetRecordTableBlocks[idx], StbM_OffsetRecordTableBlocks[idx]);
  }

}
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */




#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendSyncMeasurementDataBlockByBlock
(
  uint8 timeBaseIdx,
  boolean isCallbackConfigured,
  uint32 blockStartIdx,
  uint32 blockStopIdx,
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_VAR) syncRecordTableBlocks
)
{
  uint32 jdx = 0U;


  /* send blocks consecutively, starting from  startIndex to stopIndex  */
  for (jdx = blockStartIdx; jdx <= blockStopIdx; jdx++)
  {
    if(isCallbackConfigured == TRUE)
    {
      (void)StbM_CallbacksPtrList[timeBaseIdx].syncTimeRecordBlockCbkFctPtr(&syncRecordTableBlocks[jdx]);
    }
#if (STBM_RTE_USED == STD_ON)
    else
    {
      (void)StbM_CallbacksPtrList[timeBaseIdx].syncTimeRecordBlockRteCbkFctPtr(&syncRecordTableBlocks[jdx]);
    }
#endif /* STBM_RTE_USED == STD_ON */
  }

}
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendOffsetMeasurementDataBlockByBlock
(
  uint8 timeBaseIdx,
  boolean isCallbackConfigured,
  uint32 blockStartIdx,
  uint32 blockStopIdx,
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_VAR) offsetRecordTableBlocks
)
{
  uint32 jdx = 0U;


  /* send blocks consecutively, starting from  startIndex to stopIndex  */
  for (jdx = blockStartIdx; jdx <= blockStopIdx; jdx++)
  {
    if(isCallbackConfigured == TRUE)
    {
      (void)StbM_CallbacksPtrList[timeBaseIdx].offsetTimeRecordBlockCbkFctPtr(&offsetRecordTableBlocks[jdx]);
    }
#if (STBM_RTE_USED == STD_ON)
    else
    {
      (void)StbM_CallbacksPtrList[timeBaseIdx].offsetTimeRecordBlockRteCbkFctPtr(&offsetRecordTableBlocks[jdx]);
    }
#endif /* STBM_RTE_USED == STD_ON */
  }

}
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */




STATIC FUNC(void, STBM_CODE) StbM_CheckIfNewMeasurementDataIsAvailableAndSend
(
  boolean isSyncTimeBase,
  uint8 timeBaseIndex
)
{
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;
  boolean isCallbackActive = FALSE;
  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewSyncBlocks = FALSE;
  boolean sendSyncBlocksWrapping = FALSE;
  boolean sendAllSyncBlocks = FALSE;

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  StbM_SyncRecordTableBlockType lcl_StbM_SyncRecordTableBlocks[STBM_NUMBER_OF_SYNC_TIME_RECORD_BLOCKS];
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
  StbM_OffsetRecordTableBlockType lcl_StbM_OffsetRecordTableBlocks[STBM_NUMBER_OF_OFFSET_TIME_RECORD_BLOCKS];
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  StbM_Init_SyncRecordTableBlock(&lcl_StbM_SyncRecordTableBlocks[0U]);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
  StbM_Init_OffsetRecordTableBlock(&lcl_StbM_OffsetRecordTableBlocks[0U]);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocks;
  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocks;


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* if number of configured sync blocks is different from 0 and
        there are new sync blocks in the table or the table is fully filled with blocks
     => send sync blocks */
  if(numberOfBlocks != 0U)
  {
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
    if(isSyncTimeBase == TRUE)
#else
    TS_PARAM_UNUSED(isSyncTimeBase);
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    {
      if(StbM_CallbacksPtrList[timeBaseIndex].syncTimeRecordBlockCbkFctPtr != NULL_PTR)
      {
        isCallbackActive = TRUE;
      }
    }
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    else
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
    {
      if(StbM_CallbacksPtrList[timeBaseIndex].offsetTimeRecordBlockCbkFctPtr != NULL_PTR)
      {
        isCallbackActive = TRUE;
      }
    }
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

    /* only a few blocks recorded without wrapping  or wrapping occured */
    if((StbM_RecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex))
    {
      /* only a few blocks were filled */
      if(StbM_RecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
      {
        blockStopIndex = (StbM_RecordTableBlocksInfo[timeBaseIndex].counter - 1U);
        sendOnlyFewSyncBlocks = TRUE;
      }
      else /* wrapping occurred */
      {
        blockStopIndex = (blockStartIndex + numberOfBlocks) - 1U;
        blockStartIndex = StbM_RecordTableBlocksInfo[timeBaseIndex].counter;
        blockStopIndexNewestBlocks = (StbM_RecordTableBlocksInfo[timeBaseIndex].counter - 1U);
        blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocks;
        sendSyncBlocksWrapping = TRUE;
      }
    }
    else /* the exact same number of configured blocks were recorded */
    {
      /* exact number of configured blocks were recored and wrapping occured */
      if(StbM_RecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
      {
        blockStopIndex = (blockStartIndex + numberOfBlocks) - 1U;
        sendAllSyncBlocks = TRUE;
      }
    }

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
    if(isSyncTimeBase == TRUE)
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
    {
      /* copy sync blocks from the global variable to a local variable, starting from  startIndex to stopIndex */
      StbM_CopySyncMeasurementDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_SyncRecordTableBlocks);
    }
#endif /* STBM_SYNC_TIME_RECORDING_USED == STD_ON */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    else
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
    {
      /* copy offset blocks from the global variable to a local variable, starting from  startIndex to stopIndex */
      StbM_CopyOffsetMeasurementDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_OffsetRecordTableBlocks);
    }
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

    if(sendSyncBlocksWrapping == TRUE)
    {
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
      if(isSyncTimeBase == TRUE)
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
      {
        /* copy sync blocks from the global variable to a local variable, starting from  startIndex to stopIndex */
        StbM_CopySyncMeasurementDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_SyncRecordTableBlocks);
      }
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    else
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
      {
        /* copy offset blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
        StbM_CopyOffsetMeasurementDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_OffsetRecordTableBlocks);
      }
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
    }

    /* reset counter and also set wasCounterWrapped to FALSE */
    StbM_RecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
    StbM_RecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;
  }

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();


  if((sendOnlyFewSyncBlocks == TRUE) || (sendSyncBlocksWrapping == TRUE) || (sendAllSyncBlocks == TRUE))
  {
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
    if(isSyncTimeBase == TRUE)
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
    {
      StbM_SendSyncMeasurementDataBlockByBlock(timeBaseIndex, isCallbackActive, blockStartIndex, blockStopIndex, lcl_StbM_SyncRecordTableBlocks);
    }
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    else
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
    {
      StbM_SendOffsetMeasurementDataBlockByBlock(timeBaseIndex, isCallbackActive, blockStartIndex, blockStopIndex, lcl_StbM_OffsetRecordTableBlocks);
    }
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */

    if(sendSyncBlocksWrapping == TRUE)
    {
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
      if(isSyncTimeBase == TRUE)
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
      {
        StbM_SendSyncMeasurementDataBlockByBlock(timeBaseIndex, isCallbackActive, blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_SyncRecordTableBlocks);
      }
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
    else
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */
      {
        StbM_SendOffsetMeasurementDataBlockByBlock(timeBaseIndex, isCallbackActive, blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_OffsetRecordTableBlocks);
      }
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
    }
  }

}


#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendSyncMeasurementData(void)
{
  uint8 idx;


  /* !LINKSTO StbM.SWS_StbM_00317.NotifyApp,1 */
  /* Deviation TASKING-1 */
  for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES); idx++)
  {
    /* check if sync time base has time recording enabled and if new measurement data was written in the time recording table */
    StbM_CheckIfNewMeasurementDataIsAvailableAndSend(TRUE, idx);
  }

}
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendOffsetMeasurementData(void)
{

  uint8 idx;


  /* !LINKSTO StbM.SWS_StbM_00318.NotifyApp,1 */
  for (idx = STBM_NUMBER_OF_SYNC_TIMEBASES; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES); idx++)
  {
    /* check if offset time base has time recording enabled and if new measurement data was written in the time recording table */
    StbM_CheckIfNewMeasurementDataIsAvailableAndSend(FALSE, idx);
  }

}
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


STATIC FUNC(void, STBM_CODE) StbM_SendMeasurementData(void)
{


#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  StbM_SendSyncMeasurementData();
#endif /* STBM_SYNC_TIME_RECORDING_USED == STD_ON */


#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
  StbM_SendOffsetMeasurementData();
#endif /* STBM_OFFSET_TIME_RECORDING_USED == STD_ON */

}

#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */




#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)


#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON))
#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyCanTSynMasterTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_CanTimeMasterMeasurementType, AUTOMATIC, STBM_VAR) cantsynMasterTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy cantsyn master timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_CanMasterTimingData[] into a local variable */
    cantsynMasterTimingDataBlocks[idx].sequenceCounter = StbM_CanMasterTimingData[idx].sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(cantsynMasterTimingDataBlocks[idx].syncEgressTimestamp, StbM_CanMasterTimingData[idx].syncEgressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(cantsynMasterTimingDataBlocks[idx].preciseOriginTimestamp, StbM_CanMasterTimingData[idx].preciseOriginTimestamp);
    cantsynMasterTimingDataBlocks[idx].segmentId = StbM_CanMasterTimingData[idx].segmentId;
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyCanTSynSlaveTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_CanTimeSlaveMeasurementType, AUTOMATIC, STBM_VAR) cantsynSlaveTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy cantsyn slave timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_CanMasterTimingData[] into a local variable */
    cantsynSlaveTimingDataBlocks[idx].sequenceCounter = StbM_CanSlaveTimingData[idx].sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(cantsynSlaveTimingDataBlocks[idx].syncIngressTimestamp, StbM_CanSlaveTimingData[idx].syncIngressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(cantsynSlaveTimingDataBlocks[idx].preciseOriginTimestamp, StbM_CanSlaveTimingData[idx].preciseOriginTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(cantsynSlaveTimingDataBlocks[idx].referenceLocalTimestamp, StbM_CanSlaveTimingData[idx].referenceLocalTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(cantsynSlaveTimingDataBlocks[idx].referenceGlobalTimestamp, StbM_CanSlaveTimingData[idx].referenceGlobalTimestamp);
    cantsynSlaveTimingDataBlocks[idx].segmentId = StbM_CanSlaveTimingData[idx].segmentId;
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)) */



#if ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON))
#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyFrTSynMasterTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_FrTimeMasterMeasurementType, AUTOMATIC, STBM_VAR) frtsynMasterTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy frtsyn master timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_FrMasterTimingData[] into a local variable */
    frtsynMasterTimingDataBlocks[idx].sequenceCounter = StbM_FrMasterTimingData[idx].sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(frtsynMasterTimingDataBlocks[idx].referenceTimestamp, StbM_FrMasterTimingData[idx].referenceTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(frtsynMasterTimingDataBlocks[idx].preciseOriginTimestamp, StbM_FrMasterTimingData[idx].preciseOriginTimestamp);
    frtsynMasterTimingDataBlocks[idx].segmentId         = StbM_FrMasterTimingData[idx].segmentId;
    frtsynMasterTimingDataBlocks[idx].currentCycle      = StbM_FrMasterTimingData[idx].currentCycle;
    frtsynMasterTimingDataBlocks[idx].currentMacroticks = StbM_FrMasterTimingData[idx].currentMacroticks;
    frtsynMasterTimingDataBlocks[idx].macrotickDuration = StbM_FrMasterTimingData[idx].macrotickDuration;
    frtsynMasterTimingDataBlocks[idx].cycleLength       = StbM_FrMasterTimingData[idx].cycleLength;
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyFrTSynSlaveTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_FrTimeSlaveMeasurementType, AUTOMATIC, STBM_VAR) frtsynSlaveTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy frtsyn slave timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_FrSlaveTimingData[] into a local variable */
    frtsynSlaveTimingDataBlocks[idx].sequenceCounter = StbM_FrSlaveTimingData[idx].sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(frtsynSlaveTimingDataBlocks[idx].syncIngressTimestamp, StbM_FrSlaveTimingData[idx].syncIngressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(frtsynSlaveTimingDataBlocks[idx].preciseOriginTimestampSec, StbM_FrSlaveTimingData[idx].preciseOriginTimestampSec);
    frtsynSlaveTimingDataBlocks[idx].currentCycle = StbM_FrSlaveTimingData[idx].currentCycle;
    frtsynSlaveTimingDataBlocks[idx].CurrentMacroticks = StbM_FrSlaveTimingData[idx].CurrentMacroticks;
    frtsynSlaveTimingDataBlocks[idx].FCNT = StbM_FrSlaveTimingData[idx].FCNT;
    frtsynSlaveTimingDataBlocks[idx].macrotickDuration = StbM_FrSlaveTimingData[idx].macrotickDuration;
    frtsynSlaveTimingDataBlocks[idx].cycleLength = StbM_FrSlaveTimingData[idx].cycleLength;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(frtsynSlaveTimingDataBlocks[idx].referenceLocalTimestamp, StbM_FrSlaveTimingData[idx].referenceLocalTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(frtsynSlaveTimingDataBlocks[idx].referenceGlobalTimestampSec, StbM_FrSlaveTimingData[idx].referenceGlobalTimestampSec);
    frtsynSlaveTimingDataBlocks[idx].segmentId = StbM_FrSlaveTimingData[idx].segmentId;
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */
#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)) */





#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynMasterTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_EthTimeMasterMeasurementType, AUTOMATIC, STBM_VAR) ethtsynMasterTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy ethtsyn master timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_EthMasterTimingData[] into a local variable */
    ethtsynMasterTimingDataBlocks[idx].sequenceId = StbM_EthMasterTimingData[idx].sequenceId;
    STBM_ASSIGN_PORT_ID(ethtsynMasterTimingDataBlocks[idx].sourcePortId, StbM_EthMasterTimingData[idx].sourcePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynMasterTimingDataBlocks[idx].syncEgressTimestamp, StbM_EthMasterTimingData[idx].syncEgressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynMasterTimingDataBlocks[idx].preciseOriginTimestamp, StbM_EthMasterTimingData[idx].preciseOriginTimestamp);
    ethtsynMasterTimingDataBlocks[idx].correctionField = StbM_EthMasterTimingData[idx].correctionField;
  }

}

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynSlaveTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_EthTimeSlaveMeasurementType, AUTOMATIC, STBM_VAR) ethtsynSlaveTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy ethtsyn slave timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_FrSlaveTimingData[] into a local variable */
    ethtsynSlaveTimingDataBlocks[idx].sequenceId = StbM_EthSlaveTimingData[idx].sequenceId;
    STBM_ASSIGN_PORT_ID(ethtsynSlaveTimingDataBlocks[idx].sourcePortId, StbM_EthSlaveTimingData[idx].sourcePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynSlaveTimingDataBlocks[idx].syncIngressTimestamp, StbM_EthSlaveTimingData[idx].syncIngressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynSlaveTimingDataBlocks[idx].preciseOriginTimestamp, StbM_EthSlaveTimingData[idx].preciseOriginTimestamp);
    ethtsynSlaveTimingDataBlocks[idx].correctionField = StbM_EthSlaveTimingData[idx].correctionField;
    ethtsynSlaveTimingDataBlocks[idx].pDelay = StbM_EthSlaveTimingData[idx].pDelay;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynSlaveTimingDataBlocks[idx].referenceLocalTimestamp, StbM_EthSlaveTimingData[idx].referenceLocalTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynSlaveTimingDataBlocks[idx].referenceGlobalTimestamp, StbM_EthSlaveTimingData[idx].referenceGlobalTimestamp);

  }

}

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynPdelayResponderTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_PdelayResponderMeasurementType, AUTOMATIC, STBM_VAR) ethtsynPdelayResponderTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy ethtsyn pdelay responder timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_EthPdelayResponderTimingData[] into a local variable */
    ethtsynPdelayResponderTimingDataBlocks[idx].sequenceId = StbM_EthPdelayResponderTimingData[idx].sequenceId;
    STBM_ASSIGN_PORT_ID(ethtsynPdelayResponderTimingDataBlocks[idx].requestPortId, StbM_EthPdelayResponderTimingData[idx].requestPortId);
    STBM_ASSIGN_PORT_ID(ethtsynPdelayResponderTimingDataBlocks[idx].responsePortId, StbM_EthPdelayResponderTimingData[idx].responsePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynPdelayResponderTimingDataBlocks[idx].requestReceiptTimestamp, StbM_EthPdelayResponderTimingData[idx].requestReceiptTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynPdelayResponderTimingDataBlocks[idx].responseOriginTimestamp, StbM_EthPdelayResponderTimingData[idx].responseOriginTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynPdelayResponderTimingDataBlocks[idx].referenceLocalTimestamp, StbM_EthPdelayResponderTimingData[idx].referenceLocalTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynPdelayResponderTimingDataBlocks[idx].referenceGlobalTimestamp, StbM_EthPdelayResponderTimingData[idx].referenceGlobalTimestamp);

  }

}

STATIC FUNC(void, STBM_CODE) StbM_CopyEthTSynPdelayInitiatorTimingDataBlockByBlock
(
  uint32 blockStartIndex,
  uint32 blockStopIndex,
  P2VAR(StbM_PdelayInitiatorMeasurementType, AUTOMATIC, STBM_VAR) ethtsynPdelayInitiatorTimingDataBlocks
)
{
  uint32 idx = 0U;

  /* copy ethtsyn pdelay initiator timing data blocks from the global variable to a local variable, starting from  startIndex to stopIndex  */
  for (idx = blockStartIndex; idx <= blockStopIndex; idx++)
  {
    /* save StbM_EthPdelayInitiatorTimingData[] into a local variable */
    ethtsynPdelayInitiatorTimingDataBlocks[idx].sequenceId = StbM_EthPdelayInitiatorTimingData[idx].sequenceId;
    STBM_ASSIGN_PORT_ID(ethtsynPdelayInitiatorTimingDataBlocks[idx].requestPortId, StbM_EthPdelayInitiatorTimingData[idx].requestPortId);
    STBM_ASSIGN_PORT_ID(ethtsynPdelayInitiatorTimingDataBlocks[idx].responsePortId, StbM_EthPdelayInitiatorTimingData[idx].responsePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynPdelayInitiatorTimingDataBlocks[idx].requestOriginTimestamp, StbM_EthPdelayInitiatorTimingData[idx].requestOriginTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynPdelayInitiatorTimingDataBlocks[idx].responseReceiptTimestamp, StbM_EthPdelayInitiatorTimingData[idx].responseReceiptTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynPdelayInitiatorTimingDataBlocks[idx].requestReceiptTimestamp, StbM_EthPdelayInitiatorTimingData[idx].requestReceiptTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynPdelayInitiatorTimingDataBlocks[idx].responseOriginTimestamp, StbM_EthPdelayInitiatorTimingData[idx].responseOriginTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(ethtsynPdelayInitiatorTimingDataBlocks[idx].referenceLocalTimestamp, StbM_EthPdelayInitiatorTimingData[idx].referenceLocalTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(ethtsynPdelayInitiatorTimingDataBlocks[idx].referenceGlobalTimestamp, StbM_EthPdelayInitiatorTimingData[idx].referenceGlobalTimestamp);
    ethtsynPdelayInitiatorTimingDataBlocks[idx].pdelay = StbM_EthPdelayInitiatorTimingData[idx].pdelay;

  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */




#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendCanTSynMasterTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_CanTimeMasterMeasurementType lcl_StbM_CanMasterTimingData[STBM_NUMBER_OF_SYNC_CANTSYN_MASTER_TIME_RECORD_BLOCKS];


  StbM_Init_CanTimeMasterMeasurement(&lcl_StbM_CanMasterTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart;


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00476.TimeMaster.SetMasterTimingData.CAN,1 */
  /* !LINKSTO StbM.SWS_StbM_00476.TimeGateway.SetMasterTimingData.CAN,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart;
      blockStopIndexNewestBlocks = (StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact number of configured blocks were filled */
  {
    /* wraping occured */
    if(StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy CanTSyn master timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyCanTSynMasterTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_CanMasterTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy CanTSyn master timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyCanTSynMasterTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_CanMasterTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_CanMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].canTSynMasterTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_CanMasterTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].canTSynMasterTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_CanMasterTimingData[jdx]);
      }
    }
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */



#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendCanTSynSlaveTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_CanTimeSlaveMeasurementType lcl_StbM_CanSlaveTimingData[STBM_NUMBER_OF_SYNC_CANTSYN_SLAVE_TIME_RECORD_BLOCKS];


  StbM_Init_CanTimeSlaveMeasurement(&lcl_StbM_CanSlaveTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart;

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00475.TimeSlave.SetSlaveTimingData.CAN,1 */
  /* !LINKSTO StbM.SWS_StbM_00475.TimeGateway.SetSlaveTimingData.CAN,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart;
      blockStopIndexNewestBlocks = (StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occured */
    if(StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy CanTSyn slave timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyCanTSynSlaveTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_CanSlaveTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy CanTSyn slave timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyCanTSynSlaveTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_CanSlaveTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_CanSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;


  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].canTSynSlaveTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_CanSlaveTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].canTSynSlaveTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_CanSlaveTimingData[jdx]);
      }
    }
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */



#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_SendCanTSynTimingData(void)
{
  uint8 idx;


  /* !LINKSTO StbM.SWS_StbM_00317.NotifyApp,1 */
  /* Deviation TASKING-1 */
  for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES); idx++)
  {

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[idx].canTSynMasterTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendCanTSynMasterTimingData(idx);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[idx].canTSynSlaveTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendCanTSynSlaveTimingData(idx);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */
  }

}
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)) */




#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendFrTSynMasterTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_FrTimeMasterMeasurementType lcl_StbM_FrMasterTimingData[STBM_NUMBER_OF_SYNC_FRTSYN_MASTER_TIME_RECORD_BLOCKS];


  StbM_Init_FrTimeMasterMeasurement(&lcl_StbM_FrMasterTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart;


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00476.TimeMaster.SetMasterTimingData.FR,1 */
  /* !LINKSTO StbM.SWS_StbM_00476.TimeGateway.SetMasterTimingData.FR,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart;
      blockStopIndexNewestBlocks = (StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occured */
    if(StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy FrTSyn master timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyFrTSynMasterTimingDataBlockByBlock(blockStartIndex, blockStopIndex, &lcl_StbM_FrMasterTimingData[0U]);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy FrTSyn master timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyFrTSynMasterTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, &lcl_StbM_FrMasterTimingData[0U]);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_FrMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].frTSynMasterTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_FrMasterTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].frTSynMasterTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_FrMasterTimingData[jdx]);
      }
    }
  }

}
#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendFrTSynSlaveTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_FrTimeSlaveMeasurementType lcl_StbM_FrSlaveTimingData[STBM_NUMBER_OF_SYNC_FRTSYN_SLAVE_TIME_RECORD_BLOCKS];


  StbM_Init_FrTimeSlaveMeasurement(&lcl_StbM_FrSlaveTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart;

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00475.TimeSlave.SetSlaveTimingData.FR,1 */
  /* !LINKSTO StbM.SWS_StbM_00475.TimeGateway.SetSlaveTimingData.FR,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart;
      blockStopIndexNewestBlocks = (StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occured */
    if(StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy FrTSyn slave timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyFrTSynSlaveTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_FrSlaveTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy FrTSyn slave timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyFrTSynSlaveTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_FrSlaveTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_FrSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].frTSynSlaveTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_FrSlaveTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].frTSynSlaveTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_FrSlaveTimingData[jdx]);
      }
    }
  }

}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */


#if ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_SendFrTSynTimingData(void)
{
  uint8 idx;


  /* !LINKSTO StbM.SWS_StbM_00317.NotifyApp,1 */
  /* Deviation TASKING-1 */
  for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES); idx++)
  {
#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[idx].frTSynMasterTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendFrTSynMasterTimingData(idx);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */

#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
    if(StbM_CallbacksPtrList[idx].frTSynSlaveTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendFrTSynSlaveTimingData(idx);
    }
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */
  }

}
#endif /* ((STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)) */



#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynMasterTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_EthTimeMasterMeasurementType lcl_StbM_EthMasterTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];


  StbM_Init_EthTimeMasterMeasurement(&lcl_StbM_EthMasterTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart;

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00476.TimeMaster.SetMasterTimingData.ETH,1 */
  /* !LINKSTO StbM.SWS_StbM_00476.TimeGateway.SetMasterTimingData.ETH,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPart;
      blockStopIndexNewestBlocks = (StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occured */
    if(StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy EthTSyn master timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyEthTSynMasterTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_EthMasterTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy EthTSyn master timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyEthTSynMasterTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_EthMasterTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_EthMasterTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynMasterTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthMasterTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynMasterTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthMasterTimingData[jdx]);
      }
    }
  }

}


STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynSlaveTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_EthTimeSlaveMeasurementType lcl_StbM_EthSlaveTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];


  StbM_Init_EthTimeSlaveMeasurement(&lcl_StbM_EthSlaveTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart;

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00475.TimeSlave.SetSlaveTimingData.ETH,1 */
  /* !LINKSTO StbM.SWS_StbM_00475.TimeGateway.SetSlaveTimingData.ETH,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPart;
      blockStopIndexNewestBlocks = (StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occured */
    if(StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy EthTSyn slave timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyEthTSynSlaveTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_EthSlaveTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy EthTSyn slave timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyEthTSynSlaveTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_EthSlaveTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_EthSlaveTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynSlaveTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthSlaveTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynSlaveTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthSlaveTimingData[jdx]);
      }
    }
  }

}


STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynTimingData(void)
{
  uint8 idx;


  /* !LINKSTO StbM.SWS_StbM_00317.NotifyApp,1 */
  /* Deviation TASKING-1 */
  for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES); idx++)
  {
    if(StbM_CallbacksPtrList[idx].ethTSynMasterTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendEthTSynMasterTimingData(idx);
    }
    if(StbM_CallbacksPtrList[idx].ethTSynSlaveTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendEthTSynSlaveTimingData(idx);
    }
  }

}




STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynMasterPdelayTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_PdelayResponderMeasurementType lcl_StbM_EthPdelayResponderTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];


  StbM_Init_PdelayResponderMeasurement(&lcl_StbM_EthPdelayResponderTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPdelayPart;

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00481,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPdelayPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationMASTERPdelayPart;
      blockStopIndexNewestBlocks = (StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occurred */
    if(StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy EthTSyn pdelay responder timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyEthTSynPdelayResponderTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_EthPdelayResponderTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy EthTSyn pdelay responder timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyEthTSynPdelayResponderTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_EthPdelayResponderTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynPdelayResponderTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthPdelayResponderTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynPdelayResponderTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthPdelayResponderTimingData[jdx]);
      }
    }
  }

}


STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynSlavePdelayTimingData
(
  uint8 timeBaseIndex
)
{
  uint32 jdx;
  uint32 blockStartIndex = 0U;
  uint16 numberOfBlocks = 0U;

  uint32 blockStopIndex = 0U;

  uint32 blockStartIndexNewestBlocks = 0U;
  uint32 blockStopIndexNewestBlocks = 0U;

  boolean sendOnlyFewBlocks = FALSE;
  boolean sendBlocksWrapping = FALSE;
  boolean sendAllBlocks = FALSE;
  StbM_PdelayInitiatorMeasurementType lcl_StbM_EthPdelayInitiatorTimingData[STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS];


  StbM_Init_PdelayInitiatorMeasurement(&lcl_StbM_EthPdelayInitiatorTimingData[0U]);

  numberOfBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].numberOfBlocksTimeValidation;
  blockStartIndex = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPdelayPart;

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* !LINKSTO StbM.SWS_StbM_00479,1 */
  /* only a few blocks were recorded without wrapping or wrapping occured */
  if(StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].counter > blockStartIndex)
  {
    /* only a few blocks were filled */
    if(StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == FALSE)
    {
      blockStopIndex = (StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendOnlyFewBlocks = TRUE;
    }
    else /* wrapping occured */
    {
      blockStartIndex = StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].counter;
      blockStopIndex = ((StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPdelayPart + numberOfBlocks) - 1U);
      blockStartIndexNewestBlocks = StbM_CommonTimeBaseCfg[timeBaseIndex].startIndexTrBlocksTimeValidationSLAVEPdelayPart;
      blockStopIndexNewestBlocks = (StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].counter - 1U);
      sendBlocksWrapping = TRUE;
    }
  }
  else /* the exact same number of configured blocks were filled */
  {
    /* wrapping occurred */
    if(StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped == TRUE)
    {
      blockStopIndex = ((blockStartIndex + numberOfBlocks) - 1U);
      sendAllBlocks = TRUE;
    }
  }

  /* copy EthTSyn pdelay initiator timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
  StbM_CopyEthTSynPdelayInitiatorTimingDataBlockByBlock(blockStartIndex, blockStopIndex, lcl_StbM_EthPdelayInitiatorTimingData);

  if(sendBlocksWrapping == TRUE)
  {
    /* copy EthTSyn pdelay initiator timing data from the global variable to a local variable, starting from  startIndex to stopIndex */
    StbM_CopyEthTSynPdelayInitiatorTimingDataBlockByBlock(blockStartIndexNewestBlocks, blockStopIndexNewestBlocks, lcl_StbM_EthPdelayInitiatorTimingData);
  }

  /* reset counter and also set wasCounterWrapped to FALSE */
  StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].counter = blockStartIndex;
  StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[timeBaseIndex].wasCounterWrapped = FALSE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  /* send timing data */
  if((sendOnlyFewBlocks == TRUE) || (sendBlocksWrapping == TRUE) || (sendAllBlocks == TRUE))
  {
    /* send blocks consecutively */
    for (jdx = blockStartIndex; jdx <= blockStopIndex; jdx++)
    {
      (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynPdelayInitiatorTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthPdelayInitiatorTimingData[jdx]);
    }

    if(sendBlocksWrapping == TRUE)
    {
      /* the newest blocks (blocks which were overwritten after the wrapping occurred) are the last to be sent */
      for (jdx = blockStartIndexNewestBlocks; jdx <= blockStopIndexNewestBlocks; jdx++)
      {
        (void)StbM_CallbacksPtrList[timeBaseIndex].ethTSynPdelayInitiatorTimeValidationRecordBlockRteCbkFctPtr(&lcl_StbM_EthPdelayInitiatorTimingData[jdx]);
      }
    }
  }

}


STATIC FUNC(void, STBM_CODE) StbM_SendEthTSynPdelayTimingData(void)
{
  uint8 idx;


  /* !LINKSTO StbM.SWS_StbM_00317.NotifyApp,1 */
  /* Deviation TASKING-1 */
  for (idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES); idx++)
  {
    if(StbM_CallbacksPtrList[idx].ethTSynPdelayResponderTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendEthTSynMasterPdelayTimingData(idx);
    }
    if(StbM_CallbacksPtrList[idx].ethTSynPdelayInitiatorTimeValidationRecordBlockRteCbkFctPtr != NULL_PTR)
    {
      StbM_SendEthTSynSlavePdelayTimingData(idx);
    }
  }

}

#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */


#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */



#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)


STATIC FUNC(void, STBM_CODE) StbM_SendNotificationToCustomer
(
  StbM_SynchronizedTimeBaseType timebaseId,
  StbM_CustomerIdType customerId,
  P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_VAR) devTime
)
{
  uint8 customerNotifIdx;
  StbM_SynchronizedTimeBaseType currentTimeBaseId = 0U;
  StbM_CustomerIdType currentCustomerId = 0U;


  /* Defensive programming */
  /* Deviation TASKING-1 */
  STBM_PRECONDITION_ASSERT(currentCustomerId < STBM_NUMBER_OF_NOTIFICATION_CUSTOMERS,DET_INTERNAL_API_ID);

  /* For condition would've been FALSE in the following situation:
   1. customerNotifIdx whould have been above the maximum number of Notification Customers
   Situation 1 -> FOR loop will never reach FALSE condition since we accept only configured customers and we will break before the FOR loop ends */

  /* CHECK: NOPARSE */
  /* iterate through each notification customer */
  /* Deviation TASKING-1 */
  for(customerNotifIdx = 0U; customerNotifIdx < STBM_NUMBER_OF_NOTIFICATION_CUSTOMERS; customerNotifIdx++)
  {
    currentTimeBaseId = StbM_CustomerNotificationCfg[customerNotifIdx].timeBaseId;
    currentCustomerId = StbM_CustomerNotificationCfg[customerNotifIdx].customerId;

    /* search for timeBaseId and customerId in the StbM_CustomerNotificationCfg list */
    if((currentTimeBaseId == timebaseId) && (currentCustomerId == customerId))
    {
      /* customer found, send notification through callback or C-S Interface */
      /* !LINKSTO StbM.SWS_StbM_00271.NotifyCustomer,1 */
      (void)StbM_CustomerNotificationCfg[customerNotifIdx].customerNotificationCbkFctPtr(*devTime);
      break;
    }
  }
  /* CHECK: PARSE */

}



STATIC FUNC(sint32, STBM_CODE) StbM_CalculateTimeDeviationForImmediateNotification
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) localTimeStamp,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) customerExpireTime
)
{
  StbM_TimeStampType timeStampA = {0U, 0U, 0U, 0U};
  StbM_TimeStampType timeStampB = {0U, 0U, 0U, 0U};

  uint32 nanosecondsCalcDev = 0U;
  uint32 secondsCalcDev = 0U;
  uint32 nanosecondsPartFromsecondsCalcDev = 0U;
  sint32 totalCalcDevNanoseconds = 0U;
  /* variables used for handling time deviation */
  StbM_TimeStampType calculatedDeviationTimeStamp = {0U, 0U, 0U, 0U};
  /* max Gpt value */
  StbM_TimeStampType maxGptValueInTicks = {0U, 147483647U, 2U, 0U};

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(localTimeStamp != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(customerExpireTime != NULL_PTR,DET_INTERNAL_API_ID);


  /* make sure that timeStampA is greater than timeStampB */
  STBM_ASSIGN_TIMESTAMP(timeStampB, *customerExpireTime);
  STBM_ASSIGN_TIMESTAMP(timeStampA, *localTimeStamp);
  /* sign calculation will always result in a negative sign */

  /* calculate the difference between CustomerTimerExpireTime and timeStampLocalTime */
  (void)StbM_SubtractTimeStamps
      (
          &timeStampA,
          &timeStampB,
          &calculatedDeviationTimeStamp
      );

  /* get the nanoseconds part from the deviationTimeStamp */
  nanosecondsCalcDev = calculatedDeviationTimeStamp.nanoseconds;
  /* get the seconds part from the deviationTimeStamp */
  secondsCalcDev = calculatedDeviationTimeStamp.seconds;


  /* check if range is elapsed */
  if (StbM_TimeStampIsGreaterEqual(&maxGptValueInTicks, &calculatedDeviationTimeStamp) == TRUE)
  {
    /* calculate how many nanoseconds are contained in secondsCalcDev */
    nanosecondsPartFromsecondsCalcDev = secondsCalcDev * STBM_NS_PER_SEC;

    /* calculate the sum of nanoseconds from calculatedDeviationTimeStamp */
    /* Deviation MISRAC2012-1 */
    totalCalcDevNanoseconds =  (-1) * ((sint32)(nanosecondsCalcDev + nanosecondsPartFromsecondsCalcDev));
  }
  else /* range elapsed */
  {
    /* negative sign */
    totalCalcDevNanoseconds = STBM_MAX_NEGATIVE_SINT32_VALUE;
  }


  return totalCalcDevNanoseconds;
}





STATIC FUNC(void, STBM_CODE) StbM_TryToCallGptStartTimer
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) gptExpireTimeStamp,
  P2VAR(StbM_CustomerTimerExpireTimeNodeDataType, AUTOMATIC, STBM_VAR) currentNode
)
{
  Gpt_ValueType gptExpireTimeTicks = 0U;
  uint32 gptExpireTimeTicksFromSeconds = 0U;
  uint32 gptExpireTimeTicksFromNanoseconds = 0U;
  boolean callGpt = FALSE;


  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* Call Gtp_StartTimer() and start Gpt timer if it is not running */
  if(StbM_IsGptTimeRunning == FALSE)
  {
    /* convert total number of seconds into gpt ticks */
    gptExpireTimeTicksFromSeconds = gptExpireTimeStamp->seconds * STBM_SEC_PER_MICROSEC;

    /* convert total number of nanoseconds into gpt ticks */
    gptExpireTimeTicksFromNanoseconds = gptExpireTimeStamp->nanoseconds / STBM_NS_PER_MICROSEC;

    /* calculate the sum of ticks (ticks from ns + ticks from sec) */
    gptExpireTimeTicks = (Gpt_ValueType)(gptExpireTimeTicksFromSeconds + gptExpireTimeTicksFromNanoseconds);

    /* Gpt timer is in state "RUNNING" */
    StbM_IsGptTimeRunning = TRUE;

    /* Gpt Timer is running for this expiry point */
    currentNode->Data.isGptTimerRunning = TRUE;

    callGpt = TRUE;
  }
  else
  {
    /* Gpt Timer is busy now and it will be called when it will be FREE */
    currentNode->Data.pendingStartGptTimer = TRUE;
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  if(callGpt == TRUE)
  {
    /* !LINKSTO StbM.SWS_StbM_00336.DifferenceElapsedStbMTimerStartThreshold.Call.Gpt_StartTimer,1 */
    Gpt_StartTimer(STBM_GPT_CHANNEL_USED_FOR_STARTING_GPTTIMER, gptExpireTimeTicks);
  }

}


STATIC FUNC(void, STBM_CODE) StbM_TryToCallGptStartTimerByArrayIndex
(
  StbM_TimeStampType gptExpireTimeStamp,
  uint32 arrayIndex
)
{
  Gpt_ValueType gptExpireTimeTicks = 0U;
  uint32 gptExpireTimeTicksFromSeconds = 0U;
  uint32 gptExpireTimeTicksFromNanoseconds = 0U;
  boolean callGpt = FALSE;


  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* Call Gtp_StartTimer() and start Gpt timer if it is not running */
  if(StbM_IsGptTimeRunning == FALSE)
  {
    /* convert total number of seconds into gpt ticks */
    gptExpireTimeTicksFromSeconds = gptExpireTimeStamp.seconds * STBM_SEC_PER_MICROSEC;

    /* convert total number of nanoseconds into gpt ticks */
    gptExpireTimeTicksFromNanoseconds = gptExpireTimeStamp.nanoseconds / STBM_NS_PER_MICROSEC;

    /* calculate the sum of ticks (ticks from ns + ticks from sec) */
    gptExpireTimeTicks = (Gpt_ValueType)(gptExpireTimeTicksFromSeconds + gptExpireTimeTicksFromNanoseconds);

    /* Gpt timer is in state "RUNNING" */
    StbM_IsGptTimeRunning = TRUE;

    /* Gpt Timer is running for this expiry point */
    StbM_ExpireTimeData[arrayIndex].Data.isGptTimerRunning = TRUE;

    callGpt = TRUE;
  }
  else
  {
    /* Gpt Timer is busy now and it will be called when it will be FREE */
    StbM_ExpireTimeData[arrayIndex].Data.pendingStartGptTimer = TRUE;
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  if(callGpt == TRUE)
  {
    /* !LINKSTO StbM.SWS_StbM_00336.DifferenceElapsedStbMTimerStartThreshold.Call.Gpt_StartTimer,1 */
    Gpt_StartTimer(STBM_GPT_CHANNEL_USED_FOR_STARTING_GPTTIMER, gptExpireTimeTicks);
  }

}


STATIC FUNC(void, STBM_CODE) StbM_SendNotificationForExpiryPointsWithGptTimerAlreadyExpired(void)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;
  uint32 idx;
  uint32 nrOfCustomersToCall = 0U;
  StbM_SendCustomerNotificationType sendNotificationArray[STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS];


  StbM_Init_SendCustomerNotification(&sendNotificationArray[0U]);

  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* search if there is an expiry point for which StbM_TimerCallback() was called */
  for(current = Head; current != NULL_PTR; current = current->next)
  {
    /* StbM_TimerCallback already called for this node */
    if(current->Data.isTimerExpiredInGpt == TRUE)
    {
      StbM_SynchronizedTimeBaseType lclTimeBaseId = 0U;
      StbM_CustomerIdType lclCustomerId = 0U;
      StbM_TimeDiffType calcDeviationTime = 0;
      StbM_CustomerTimerExpireTimeDataType nodeToBeDeleted = {0U, 0U, {0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U, 0U, 0U};


      lclTimeBaseId = current->Data.timeBaseId;
      lclCustomerId = current->Data.customerId;
      calcDeviationTime = current->Data.calculatedTimeDeviation;

      nodeToBeDeleted.timeBaseId = lclTimeBaseId;
      nodeToBeDeleted.customerId = lclCustomerId;
      STBM_ASSIGN_TIMESTAMP(nodeToBeDeleted.customerTimerExpireTime, current->Data.customerTimerExpireTime);

      /* delete the node from the list */
      StbM_DeleteFromPosition(&nodeToBeDeleted);

      /* save the customer data to be sent */
      sendNotificationArray[nrOfCustomersToCall].timeBaseId = lclTimeBaseId;
      sendNotificationArray[nrOfCustomersToCall].customerId = lclCustomerId;
      sendNotificationArray[nrOfCustomersToCall].calcDeviation = calcDeviationTime;
      nrOfCustomersToCall++;

    }
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  for(idx = 0U; idx < nrOfCustomersToCall; idx++)
  {
    /* send notification */
    /* !LINKSTO StbM.SWS_StbM_00271.NotifyCustomer,1 */
    StbM_SendNotificationToCustomer(sendNotificationArray[idx].timeBaseId, sendNotificationArray[idx].customerId, &(sendNotificationArray[idx].calcDeviation));
  }

}



STATIC FUNC(void, STBM_CODE) StbM_HandleExpiryPointsWithPendingStartGptTimer
(
  P2VAR(StbM_LocalTimeCallType, AUTOMATIC, STBM_VAR) localTimes
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;
  StbM_TimeStampType customerExpireTime = {0U, 0U, 0U, 0U};

  uint32 idx;
  uint32 nrOfCustomersToCall = 0U;
  uint32 nrOfGptCalls = 0U;
  StbM_SendCustomerNotificationType sendNotificationArray[STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS];
  StbM_GptCallPairType gptPair[STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS];


  StbM_Init_SendCustomerNotification(&sendNotificationArray[0U]);
  StbM_Init_GptCallPair(&gptPair[0U]);

  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* search if there are pending calls to Gpt_StartTimer() and handle them first */
  for(current = Head; current != NULL_PTR; current = current->next)
  {
    customerExpireTime = current->Data.customerTimerExpireTime;

    /* check if there are Gpt_StartTimer() which should have been called,
       but they were not called because Gpt timer was already running */
    if(current->Data.pendingStartGptTimer == TRUE)
    {
      uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(current->Data.timeBaseId);
      /* calculate and record rate correction, if it is the case */
      if(localTimes[commonIndex].retVal == E_OK)
      {
        /* 'customerTimerExpireTime' already expired
           (current Time Base time is in future compared with 'customerTimerExpireTime', due to an invocation of StbM_BusSetGlobalTime API)*/
        /* !LINKSTO StbM.SWS_StbM_00432,1 */
        /* !LINKSTO StbM.SWS_StbM_00335,1 */
        if(StbM_TimeStampIsGreaterEqual(&localTimes[commonIndex].localTime, &customerExpireTime))
        {
          StbM_CustomerTimerExpireTimeDataType nodeToBeDeleted = {0U, 0U, {0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U, 0U, 0U};
          StbM_SynchronizedTimeBaseType timeBaseId = 0U;
          StbM_CustomerIdType customerId = 0U;
          sint32 calculatedTimeDeviation = 0;

          timeBaseId = current->Data.timeBaseId;
          customerId = current->Data.customerId;

          /* get calculated Time Deviation which needs to be sent to customer */
          calculatedTimeDeviation = StbM_CalculateTimeDeviationForImmediateNotification(&localTimes[commonIndex].localTime, &customerExpireTime);

          nodeToBeDeleted.timeBaseId = timeBaseId;
          nodeToBeDeleted.customerId = customerId;
          STBM_ASSIGN_TIMESTAMP(nodeToBeDeleted.customerTimerExpireTime, current->Data.customerTimerExpireTime);

          /* delete the node from the list */
          StbM_DeleteFromPosition(&nodeToBeDeleted);

          /* save the customer data to be sent */
          sendNotificationArray[nrOfCustomersToCall].timeBaseId = timeBaseId;
          sendNotificationArray[nrOfCustomersToCall].customerId = customerId;
          sendNotificationArray[nrOfCustomersToCall].calcDeviation = calculatedTimeDeviation;
          nrOfCustomersToCall++;

        }
        else /* calculate gptExpireTime and try to call Gpt_StartTimer if not running */
        {
          StbM_TimeStampType expireTimeStampDifference = {0U, 0U, 0U, 0U};

          /* expire time is still greater than current TimeBase time, we need to subtract customerExpireTime - localTimes[commonIndex].localTime */
          /* !LINKSTO StbM.SWS_StbM_00335,1 */
          (void)StbM_SubtractTimeStamps
              (
                  &customerExpireTime,
                  &localTimes[commonIndex].localTime,
                  &expireTimeStampDifference
              );

          STBM_ASSIGN_TIMESTAMP(gptPair[nrOfGptCalls].expireTimeDiff, expireTimeStampDifference);
          gptPair[nrOfGptCalls].arrayIndex = current->Data.arrayCellIndex;
          nrOfGptCalls++;
        }
      }
    }
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  for(idx = 0U; idx < nrOfCustomersToCall; idx++)
  {
    /* send notification */
    /* !LINKSTO StbM.SWS_StbM_00271.NotifyCustomer,1 */
    StbM_SendNotificationToCustomer(sendNotificationArray[idx].timeBaseId, sendNotificationArray[idx].customerId, &(sendNotificationArray[idx].calcDeviation));
  }

  for(idx = 0U; idx < nrOfGptCalls; idx++)
  {
    /* Try to call Gpt_StartTimer(), for those nodes which couldn't call Gpt_StartTimer() when it was the case */
    StbM_TryToCallGptStartTimerByArrayIndex(gptPair[idx].expireTimeDiff, gptPair[idx].arrayIndex);
  }


}



STATIC FUNC(void, STBM_CODE) StbM_DifferencePassedOverStartThreshold
(
  P2VAR(StbM_LocalTimeCallType, AUTOMATIC, STBM_VAR) localTimes
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;
  StbM_TimeStampType customerExpireTime;

  uint32 idx;
  uint32 nrOfCustomersToCall = 0U;
  uint32 nrOfGptCalls = 0U;
  StbM_SendCustomerNotificationType sendNotificationArray[STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS];
  StbM_GptCallPairType gptPair[STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS];


  StbM_Init_SendCustomerNotification(&sendNotificationArray[0U]);
  StbM_Init_GptCallPair(&gptPair[0U]);

  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* iterate through all nodes from the list */
  for(current = Head; current != NULL_PTR; current = current->next)
  {

    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(current->Data.timeBaseId);

    if(current->Data.pendingStartGptTimer == TRUE)
    {
      continue;
    }

    customerExpireTime = current->Data.customerTimerExpireTime;

    /* calculate and record rate correction, if it is the case */
    if(localTimes[commonIndex].retVal == E_OK)
    {
      /* the expiration time was elapsed due to an invocation of StbM_BusSetGlobalTime()  */
      /* !LINKSTO StbM.SWS_StbM_00335,1 */
      if(StbM_TimeStampIsGreaterEqual(&localTimes[commonIndex].localTime, &customerExpireTime))
      {
        StbM_CustomerTimerExpireTimeDataType nodeToBeDeleted = {0U, 0U, {0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U, 0U, 0U};
        StbM_SynchronizedTimeBaseType timeBaseId = 0U;
        StbM_CustomerIdType customerId = 0U;
        sint32 calculatedTimeDeviation = 0;

        timeBaseId = current->Data.timeBaseId;
        customerId = current->Data.customerId;
        calculatedTimeDeviation = StbM_CalculateTimeDeviationForImmediateNotification(&localTimes[commonIndex].localTime, &customerExpireTime);

        nodeToBeDeleted.timeBaseId = timeBaseId;
        nodeToBeDeleted.customerId = customerId;
        STBM_ASSIGN_TIMESTAMP(nodeToBeDeleted.customerTimerExpireTime, current->Data.customerTimerExpireTime);

        /* delete the node from the list */
        StbM_DeleteFromPosition(&nodeToBeDeleted);

        /* save the customer data to be sent */
        sendNotificationArray[nrOfCustomersToCall].timeBaseId = timeBaseId;
        sendNotificationArray[nrOfCustomersToCall].customerId = customerId;
        sendNotificationArray[nrOfCustomersToCall].calcDeviation = calculatedTimeDeviation;
        nrOfCustomersToCall++;

      }
      else /* calculate gptExpireTime and try to call Gpt_StartTimer if not running */
      {
        StbM_TimeStampType gptExpireTimeStamp = {0U, 0U, 0U, 0U};
        StbM_TimeStampType ConfiguredStartThresholdValue  = {0U, 0U, 0U, 0U};


        /* expire time is still greater than current TimeBase time, we need to subtract customerExpireTime - localTimes[commonIndex].localTime */
        /* !LINKSTO StbM.SWS_StbM_00335,1 */
        (void)StbM_SubtractTimeStamps
            (
                &customerExpireTime,
                &localTimes[commonIndex].localTime,
                &gptExpireTimeStamp
            );

        ConfiguredStartThresholdValue.nanoseconds = STBM_TIMERSTARTTHRESHOLD_NANOSEC_PART;
        ConfiguredStartThresholdValue.seconds = STBM_TIMERSTARTTHRESHOLD_SEC_PART;

        /* check if the difference between  customerTimerExpireTime and LocalTime passed over the threshold
           ((customerTimerExpireTime - LocalTime) < threshold) */
        /* !LINKSTO StbM.SWS_StbM_00336.Difference.HasNotElapsed.StbMTimerStartThreshold.Gpt_StartTimer.NotCalled,1 */
        if(StbM_TimeStampIsGreaterEqual(&ConfiguredStartThresholdValue, &gptExpireTimeStamp) == TRUE)
        {
          STBM_ASSIGN_TIMESTAMP(gptPair[nrOfGptCalls].expireTimeDiff, gptExpireTimeStamp);
          gptPair[nrOfGptCalls].arrayIndex = current->Data.arrayCellIndex;
          nrOfGptCalls++;
        }

      }
    }
  }

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  for(idx = 0U; idx < nrOfCustomersToCall; idx++)
  {
    /* send notification */
    /* !LINKSTO StbM.SWS_StbM_00271.NotifyCustomer,1 */
    StbM_SendNotificationToCustomer(sendNotificationArray[idx].timeBaseId, sendNotificationArray[idx].customerId, &(sendNotificationArray[idx].calcDeviation));
  }

  for(idx = 0U; idx < nrOfGptCalls; idx++)
  {
    /* Try to call Gpt_StartTimer(), for those nodes which couldn't call Gpt_StartTimer() when it was the case */
    StbM_TryToCallGptStartTimerByArrayIndex(gptPair[idx].expireTimeDiff, gptPair[idx].arrayIndex);
  }



}
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */



#if (STBM_SOURCE_TIMEBASES_USED == STD_ON)
STATIC FUNC(void, STBM_CODE)  StbM_Check_Pending_Clone_Request(uint8 srcIndex)
{
  uint8 destIndex;
  uint8 srcTimeIndex;
  StbM_CloneConfigType srcCloneCfg ;
  for( destIndex = 0; destIndex < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES) ; destIndex++ )
  {
     /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_CloneDataPtr,1 */
     SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
     srcTimeIndex = StbM_CloneDataArr[destIndex].srcTimeBaseId;
     srcCloneCfg = StbM_CloneDataArr[destIndex].cloneCfg ;
     SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
     if(srcTimeIndex == srcIndex)
     {
         Atomic_t srcTimeBaseIdLcl = StbM_CloneDataArr[destIndex].srcTimeBaseId;
         /* !LINKSTO StbM.SWS_StbM_00532.AR-117132,1 */
         /* Do the clone between srcIndex  & destIndex */
         (void)StbM_CloneTimeBase_Internal( srcIndex ,destIndex, srcCloneCfg );
         /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_CloneDataPtr,1 */
         /* remove the pending deferred clone request as the clone happens */
         Atomics_Store(&srcTimeBaseIdLcl, (Atomic_value_t)STBM_NO_SOURCE_TIME_BASE);
     }
  }

}
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */

/* !LINKSTO StbM.SWS_StbM_00233,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) globalTimePtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  DBG_STBM_BUSSETGLOBALTIME_ENTRY(timeBaseId, globalTimePtr, userDataPtr, measureDataPtr, localTimePtr);

#if ((STBM_TIME_RECORDING_USED == STD_OFF) && (STBM_DEV_ERROR_DETECT == STD_OFF))
  TS_PARAM_UNUSED(measureDataPtr);
#endif /* (STBM_TIME_RECORDING_USED == STD_OFF) && (STBM_DEV_ERROR_DETECT == STD_OFF) */

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_BusSetGlobalTime_DetChecks(timeBaseId, globalTimePtr, userDataPtr, measureDataPtr, localTimePtr) == E_OK)
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Copy global time to local variable. This allows to update the status flags
     * before forwarding the timestamp to possible connected master domains */
    StbM_TimeStampType currentTimeStamp = *globalTimePtr;
    StbM_VirtualLocalTimeType receivedTimeTupleVLT = *localTimePtr;

    if(E_OK == StbM_UpdateRxTimeTuple(timeBaseId, &currentTimeStamp, &receivedTimeTupleVLT))
    {
      StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
      StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
      StbM_TimeStampType currentTimeBaseTime = {0U, 0U, 0U, 0U};
      boolean performJump = FALSE;
      /* get the offset into the zero-based dense configuration existing for all time bases. */
      uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
#if ((STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED == STD_ON))
      uint8 oldTimeleapFlags = 0U;
#endif /* (STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED == STD_ON) */


      uint8 flags;
#if(STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
      StbM_TimeBaseNotificationType tmpStatusNotification = 0U;
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */


      SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* Always:
       * - Read the global status flags
       * - Only keep the TIME_LEAP flags, reset the TIMEOUT flag
       * - Set the GLOBAL_TIME_BASE flag
       *
       * Read the global status flags in the local variable in order to prevent
       * a possible data loss for 8 bits variables */
      flags = StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus;

      /* store current Time Tuple values */
      STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobal, StbM_TimeStamps[commonIndex].globalTime);

      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLT, StbM_TimeStamps[commonIndex].virtualLocalTime);

      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
      StbM_UpdateNotificationStatus
      (
        flags,
        currentTimeStamp,
        &tmpStatusNotification
      );
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

      /* Keep the value of the TIME_LEAP status flags between successive calls of this function */
      flags &= STBM_ALL_TIME_LEAP_FLAGS_MASK;
#if ((STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED ==STD_ON))
      oldTimeleapFlags = flags;
#endif /* (STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED ==STD_ON) */
      /* Add the global time base flag. Do supervision only if setting the internal time base
       * was successful */

      /* !LINKSTO StbM.SWS_StbM_00183.CLEAR_TIMEOUT_BIT,1 */
      /* !LINKSTO StbM.SWS_StbM_00185,1 */
      /* !LINKSTO StbM.SWS_StbM_00187.CLEAR_TIMEOUT_BIT,1 */
      STBM_FLAG_SET(flags, STBM_GLOBAL_TIME_BASE_FLAG);

      /* !LINKSTO StbM.SWS_StbM_00184,1 */
      if ((currentTimeStamp.timeBaseStatus & STBM_SYNC_TO_GATEWAY_FLAG) == STBM_SYNC_TO_GATEWAY_FLAG)
      {
        /* The syncToTimeBase signalizes if updates are based on a time gateway below
         * the global time master. */
        STBM_FLAG_SET(flags, STBM_SYNC_TO_GATEWAY_FLAG);
      }

      /* !LINKSTO StbM.SWS_StbM_00438,1 */
      /* !LINKSTO StbM.SWS_StbM_00439,1 */
      /* !LINKSTO StbM.EB.BusSetGlobalTime.E_NOT_OK,1 */
      if(E_OK == StbM_GetTime(timeBaseId, &currentTimeBaseTime, &currentTimeTupleGlobal, &currentTimeTupleVLT, &receivedTimeTupleVLT))
      {
        /* Handle Offset Correction, Time Recording, Timeleap
           and also store the values of the Main Time Tuple needed afterwards for Time Validation */
        StbM_HandleOffsetCorrectionTimeRecordingTimeleap(timeBaseId, &flags, &performJump, &currentTimeStamp, &currentTimeBaseTime, measureDataPtr, &receivedTimeTupleVLT);
      }
      else
      {
        /* a jump to the received time shall be done */
        performJump = TRUE;
      }
#if ((STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED ==STD_ON))
      STBM_CHECK_TIMELEAP_FOR_NOTIFICATION(
                                              STBM_TIME_LEAP_FUTURE_FLAG,
                                              STBM_EV_TIMELEAP_FUTURE,
                                              STBM_EV_TIMELEAP_FUTURE_REMOVED
                                            );
      STBM_CHECK_TIMELEAP_FOR_NOTIFICATION(
                                              STBM_TIME_LEAP_PAST_FLAG,
                                              STBM_EV_TIMELEAP_PAST,
                                              STBM_EV_TIMELEAP_PAST_REMOVED
                                            );
#endif /* (STBM_TIMELEAP_DETECTION_USED == STD_ON) && (STBM_STATUS_NOTIFICATIONS_USED ==STD_ON) */

#if (STBM_TIMEOUTS_USED == STD_ON)
      /* enter critical section */
      /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseTimeout,1 */
      SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* measure time until the next call to StbM_BusSetGlobalTime() */
      STBM_RESTART_TIMEOUT(commonIndex);

      /* leave critical section */
      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
#endif /* STBM_TIMEOUTS_USED == STD_ON */

      /* !LINKSTO StbM.SWS_StbM_00179,1 */
      /* store flags in local variable before forwarding the timestamp */
      currentTimeStamp.timeBaseStatus = flags;

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
      /* check id the Time Tuple shall be replaced by the Global Time Tuple,
         or by the Sync Time Tuple */
      if(TRUE == performJump)
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */
      {
        retval = StbM_SetGlobalTimeInternal(timeBaseId, &currentTimeStamp, &currentTimeTupleGlobal, &currentTimeTupleVLT, &receivedTimeTupleVLT, FALSE);
      }
#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
      else
      {
        retval = StbM_SetGlobalTimeInternal(timeBaseId, &currentTimeBaseTime, &currentTimeTupleGlobal, &currentTimeTupleVLT, &receivedTimeTupleVLT, FALSE);
      }
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */

      if (retval == E_OK)
      {
#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
        /* set EV_RESYNC notification event after time was updated */
        /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
        STBM_FLAG_SET(tmpStatusNotification, STBM_EV_RESYNC);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

        /* enter critical section */
        /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_UserData,1 */
        /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseUpdateCounter,1 */
        /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
        /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
        /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedData,1 */
        SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

        /* !LINKSTO StbM.SWS_StbM_00372,1 */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
        StbM_StoreNewTimeValuesForSlaveRateCorrection(timeBaseId, &flags, &currentTimeStamp, &receivedTimeTupleVLT);
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      StbM_NewTimeTupleValue[commonIndex] = TRUE;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
        if(!(STBM_FLAG_IS_SET(StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG)))
        {
          STBM_FLAG_SET(tmpStatusNotification, STBM_EV_GLOBAL_TIME);
        }
        StbM_TimeBaseNotificationEvents[commonIndex] |= tmpStatusNotification;
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

        /* Store status only if global time could be distributed successful. */
        StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus = flags;

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
      /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_BusSetGlobalTime,2 */
      StbM_UpdateSharedDataInMemory(timeBaseId, flags, &currentTimeStamp, &receivedTimeTupleVLT);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

        /* Store the userData bytes for the SLAVE time base, based on userDataLength */
        /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_BusSetGlobalTime,1 */
        /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_BusSetGlobalTime,1 */
        /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_BusSetGlobalTime,1 */
        StbM_SetUserDataBytes(commonIndex, userDataPtr);

#if (STBM_NUMBER_OF_SYNC_TIMEBASES  > 0U)
        /* Increment the time base update counter, this is the defined and intended overflow */
        /* !LINKSTO StbM.SWS_StbM_00350.StbM_BusSetGlobalTime.Sync,1 */
        /* !LINKSTO StbM.SWS_StbM_00350.StbM_BusSetGlobalTime.Offset,1 */
        StbM_TimeBaseUpdateCounter[commonIndex]++;
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES  > 0U) */

        /* leave critical section */
        SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
#if ( STBM_SOURCE_TIMEBASES_USED == STD_ON)
        StbM_Check_Pending_Clone_Request(commonIndex);
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */
      }
    }
    else
    {
      /* Nothing to do */
      /* !LINKSTO StbM.EB.SWS_StbM_00529.SyncRxTimeTuple.E_NOT_OK,1 */
    }
  }
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Nothing to do */
  }
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */

  DBG_STBM_BUSSETGLOBALTIME_EXIT(retval, timeBaseId, globalTimePtr, userDataPtr, measureDataPtr, localTimePtr);
  return retval;
} /* StbM_BusSetGlobalTime */




#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_StoreNewTimeValuesForSlaveRateCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(uint8, AUTOMATIC, STBM_VAR) flagsPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentGlobalTimeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) currentLocalTimePtr
)
{
  /* get the offset into the zero-based dense configuration existing for all time bases. */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  /* check if rate correction is activated for this time base */
  if(!STBM_SLAVE_RATE_CORRECTION_DISABLED(commonIndex))
  {
    uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);

    STBM_ASSIGN_TIMESTAMP(StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.globalTime, *currentGlobalTimeStampPtr);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_SlaveRateCorrectionData[rcDataIndex].syncVirtualLocalTime,StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.virtualLocalTime);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.virtualLocalTime, *currentLocalTimePtr);
    StbM_SlaveRateCorrectionData[rcDataIndex].updatedFlags = *flagsPtr;
    StbM_SlaveRateCorrectionData[rcDataIndex].initialFlags = StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus;
    StbM_SlaveRateCorrectionData[rcDataIndex].newValues = TRUE;
  }


}
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

STATIC FUNC(void, STBM_CODE) StbM_HandleOffsetCorrectionTimeRecordingTimeleap
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) performJumpPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) receivedGlobalTimePtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_TIME_RECORDING_USED == STD_OFF))
  TS_PARAM_UNUSED(measureDataPtr);
  TS_PARAM_UNUSED(flagsOutPtr);
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_TIME_RECORDING_USED == STD_OFF)) */

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_CORRECTION_USED == STD_OFF) \
      && (STBM_TIMELEAP_DETECTION_USED == STD_OFF))
  TS_PARAM_UNUSED(receivedGlobalTimePtr);
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_CORRECTION_USED == STD_OFF)
          && (STBM_TIMELEAP_DETECTION_USED == STD_OFF) */

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_OFF) && (STBM_OFFSET_TIME_RECORDING_USED == STD_OFF) && (STBM_TIME_VALIDATION_SUPPORT == STD_OFF))
  TS_PARAM_UNUSED(localTimePtr);
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_OFF) */

#if (STBM_OFFSET_CORRECTION_USED == STD_OFF)
  TS_PARAM_UNUSED(performJumpPtr);
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_OFF) */


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
  StbM_HandleOffsetCorrection(timeBaseId, currentTimeBaseTimePtr, receivedGlobalTimePtr, performJumpPtr);
#endif /* STBM_OFFSET_CORRECTION_USED == STD_ON */

  StbM_HandleTimeLeap(timeBaseId, currentTimeBaseTimePtr, receivedGlobalTimePtr, flagsOutPtr);

#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON))
  StbM_StoreTimeTuple(timeBaseId, currentTimeBaseTimePtr, localTimePtr);
#else
  TS_PARAM_UNUSED(timeBaseId);
  TS_PARAM_UNUSED(currentTimeBaseTimePtr);
  TS_PARAM_UNUSED(localTimePtr);
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)) */
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();

  StbM_HandleTimeRecording(timeBaseId, flagsOutPtr, receivedGlobalTimePtr, currentTimeBaseTimePtr, measureDataPtr, localTimePtr);

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_2();
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */


}


#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_HandleOffsetCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) receivedGlobalTimePtr,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) performJumpPtr
)
{
  /* get the offset into the zero-based dense configuration existing for all time bases. */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  /* check if current time base supports offset correction */
  /* !LINKSTO StbM.SWS_StbM_00400,1 */
  if(!STBM_OFFSET_CORRECTION_DISABLED(commonIndex))
  {
    /* Perform offset correction */
    StbM_PerformOffsetCorrection(timeBaseId, currentTimeBaseTimePtr, receivedGlobalTimePtr, performJumpPtr);
  }
  else
  {
    /* a jump to the received time shall be done */
    *performJumpPtr = TRUE;
  }


}
#endif /* STBM_OFFSET_CORRECTION_USED == STD_ON */




#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_HandleTimeRecording
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) receivedGlobalTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  /* get the offset into the zero-based dense configuration existing for all time bases. */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  /* check if time recording is activated for this time base */
  if(!STBM_TIME_RECORDING_DISABLED(commonIndex))
  {
    /* !LINKSTO StbM.SWS_StbM_00312,1 */
    StbM_PerformTimeRecording(timeBaseId, flagsOutPtr, receivedGlobalTimePtr, currentTimeBaseTimePtr, measureDataPtr, localTimePtr);
   }


}
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */



#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
#if ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_StoreTimeTuple
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{

  /* !LINKSTO StbM.SWS_StbM_00471.Copy.Slave.MeasureDataPtr.ReceivedFrom.CAN.ToTable,1 */
  /* !LINKSTO StbM.SWS_StbM_00471.Copy.Slave.MeasureDataPtr.ReceivedFrom.FR.ToTable,1 */
  /* !LINKSTO StbM.SWS_StbM_00471.Copy.Slave.MeasureDataPtr.ReceivedFrom.ETH.ToTable,1 */

  /* StbM_LastReceivedTimeTuple[] array doesn't need to be initialized for offset time bases */
  /* Deviation MISRAC2012-4 */
  if(!(STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId)))
  {
    /* store Virtual Local Time of the Main Tuple, which was received through a call to StbM_BusSetGlobalTime()  */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_LastReceivedTimeTuple[timeBaseId].timeValidationVirtualLocalTime, *localTimePtr);
    /* store Global Time of the Main Tuple, which was received through a call to StbM_BusSetGlobalTime() */
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_LastReceivedTimeTuple[timeBaseId].timeValidationGlobalTime, *timeStampPtr);
  }


}
#endif /* ((STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) || (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)) */
#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


STATIC FUNC(void, STBM_CODE) StbM_SetUserDataBytes
(
  uint8 userDataCommonIndex,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData
)
{
  /* variable to count the number of changed UserData bytes */
  uint8 userDataBytesChanged = 0U;


  /* !LINKSTO StbM.EB.SetterFunction.userDataNullPtr,1 */
  if(userData != NULL_PTR)
  {
    /* set userDataLength */
    StbM_UserData[userDataCommonIndex].userDataLength = userData->userDataLength;

    /* set only userDataLength UserData bytes */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_BusSetGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_UpdateGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_SetGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_SetUserData,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_SetOffset,1 */
    for(userDataBytesChanged = 0U; userDataBytesChanged < userData->userDataLength; userDataBytesChanged++)
    {
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_BusSetGlobalTime,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_BusSetGlobalTime,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_UpdateGlobalTime,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_UpdateGlobalTime,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_SetGlobalTime,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_SetGlobalTime,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_SetUserData,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_SetUserData,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_SetOffset,1 */
      /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_SetOffset,1 */
      if(userDataBytesChanged == 0U)
      {
        /* set UserByte 0 */
        StbM_UserData[userDataCommonIndex].userByte0 = userData->userByte0;
      }
      else if(userDataBytesChanged == 1U)
      {
        /* set UserByte 0 and UserByte 1 */
        StbM_UserData[userDataCommonIndex].userByte0 = userData->userByte0;
        StbM_UserData[userDataCommonIndex].userByte1 = userData->userByte1;
      }
      else
      {
        /* set UserByte 0, UserByte 1 and UserByte 2 */
        StbM_UserData[userDataCommonIndex].userByte0 = userData->userByte0;
        StbM_UserData[userDataCommonIndex].userByte1 = userData->userByte1;
        StbM_UserData[userDataCommonIndex].userByte2 = userData->userByte2;
      }
    }
  }


}


#if (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON)
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SetTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  /* Copy global time to local variable. This allows to update the status flags
   * before forwarding the time stamp to possible connected master domains */
  StbM_TimeStampType currentTimeStamp = *timeStampPtr;


  /* time base synchronized with global time - clear all other bits.
   * Set status of pure time base, offset time base AND underlying synchronized time base. */
  /* !LINKSTO StbM.SWS_StbM_00181.SetGlobalTime,1 */
  /* !LINKSTO StbM.SWS_StbM_00181.UpdateGlobalTime,1 */
  /* !LINKSTO StbM.SWS_StbM_00399.GLOBAL_TIME_BASE.setBy.StbM_SetGlobalTime,1 */
  /* !LINKSTO StbM.SWS_StbM_00399.GLOBAL_TIME_BASE.setBy.StbM_UpdateGlobalTime,1 */
  currentTimeStamp.timeBaseStatus = STBM_GLOBAL_TIME_BASE_FLAG;

  retval = StbM_SetGlobalTimeInternal(timeBaseId, &currentTimeStamp, currentTimeTupleGlobalPtr, currentTimeTupleVLTPtr, localTimePtr, TRUE);

  if (retval == E_OK)
  {
    /* Get the offset into the zero-based dense configuration existing for all time bases. */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIndex);
      uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    /* Enter critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_UserData,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseUpdateCounter,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedData,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
    if(!(STBM_FLAG_IS_SET(StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG)))
    {
      STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_GLOBAL_TIME);
    }
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

    /* Store status only if global time could be distributed successfully. */
    StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus = STBM_GLOBAL_TIME_BASE_FLAG;




#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
    /* set EV_RESYNC notification event after time was updated */
    /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
    STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_RESYNC);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_SetGlobalTime,2 */
    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_UpdateGlobalTime,2 */
    StbM_UpdateSharedDataInMemory(timeBaseId, STBM_GLOBAL_TIME_BASE_FLAG, &currentTimeStamp, localTimePtr);
#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
    /* check if time base needs to share data to memory */
    if ((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[commonIndex].timeBaseRoleSharedData == STBM_TIME_BASE_PROVIDER_SHARED_DATA))
    {
      /* get array start index for this timebase */
      timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteBegin,1 */
      /* increment the 'begin' counter, this will signal the user that
         data is currently being written */
      Atomics_ThreadFence();
      StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX]++;
      Atomics_ThreadFence();

      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_SetGlobalTime,1 */
      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_UpdateGlobalTime,1 */
      StbM_UpdateTimeTupleInSharedMemory(commonIndex, timeBaseStartIndex);

      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteEnd,1 */
      /* increment the 'end' counter, this will signal the user that
         data has been written */
      Atomics_ThreadFence();
      StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX]++;
      Atomics_ThreadFence();
    }
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    /* Store the userData bytes for the MASTER time base, based on userDataLength */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_SetGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_SetGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_SetGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.NotEquals.Zero.StbM_UpdateGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.userDataLength.Equals.Zero.StbM_UpdateGlobalTime,1 */
    /* !LINKSTO StbM.SWS_StbM_00381.NotSetUserData.PreviousValueKept.StbM_UpdateGlobalTime,1 */
    StbM_SetUserDataBytes(commonIndex, userDataPtr);

    /* Leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }

  return retval;
} /* StbM_SetTime */
#endif /* (STBM_MASTER_OR_GATEWAY_TIME_BASE_CONFIGURED == STD_ON) */


FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeInternal
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
  Std_ReturnType retval =  E_OK;
  StbM_TimeStampType virtualLocalTimeDiff = {0U, 0U, 0U, 0U};

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(localTimePtr != NULL_PTR,DET_INTERNAL_API_ID);

#if ((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_MASTER_RATE_CORRECTION_USED == STD_ON))
  if(STBM_SLAVE_OR_MASTER_RATE_CORRECTION_DISABLED(timeBaseId) == TRUE)
  {
    /* calculate local time using rate correction */
    StbM_CalculateLocalTimeWithRate(timeBaseId, timeStampPtr, currentTimeTupleGlobalPtr, currentTimeTupleVLTPtr, localTimePtr);
  }
  else
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) || (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
  {

#if (STBM_OFFSET_TIMEBASES_USED == STD_OFF)
    TS_PARAM_UNUSED(timeBaseId);
#endif /* STBM_OFFSET_TIMEBASES_USED == STD_OFF */

    /* offset time bases do not progress in time if rate corection is not used */
    /* Deviation MISRAC2012-4 */
    if(!STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
    {
      /* perform the difference time calculation between the current Virtual Local Time
        * and the stored Virtual Local Time of the Main Time Tuple */
      /* will never return E_NOT_OK since the time progresses */
      StbM_SubtractVirtualLocalTimesToTimeStamp
      (
        localTimePtr,
        currentTimeTupleVLTPtr,
        &virtualLocalTimeDiff
      );
    }

    /* don't consider retval(overflow of the global time could happen in thousands of years) */
    /* calculate the local time and assign it (TL = TG + virtualLocalTimeDiff) */
    (void)StbM_SumTimeStamps
    (
      currentTimeTupleGlobalPtr,
      &virtualLocalTimeDiff,
      timeStampPtr
    );

  }

  return retval;
}


FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTimeOffset
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  /* no reason not to return E_ok */
  /* this shall be kept with Std_ReturnType, because the setter could be a user
     defined module */
  Std_ReturnType retval = E_OK;
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* !LINKSTO StbM.SWS_StbM_00433.UpdateMainTimeTuple.AfterSetting.NewGlobalTime,1 */
  /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTime.ReplaceMainTimeTuple.AfterSetting.NewGlobalTime.ByApplication,1 */
  /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTimeExtended.ReplaceMainTimeTuple.AfterSetting.NewGlobalTime.ByApplication,1 */
  /* !LINKSTO StbM.SWS_StbM_00436.StbM_BusGetCurrentTime.ReplaceMainTimeTuple.AfterSetting.NewGlobalTime.ByApplication,1 */
  /* !LINKSTO StbM.SWS_StbM_00433.UpdateMainTimeTuple.AfterReceivingTimeTuple.FromTimeSyncModule,1 */
  /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTime.ReplaceMainTimeTuple.AfterReceiving.NewTimeTuple.FromTSynModule,1 */
  /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTimeExtended.ReplaceMainTimeTuple.AfterReceiving.NewTimeTuple.FromTSynModule,1 */
  /* !LINKSTO StbM.SWS_StbM_00436.StbM_BusGetCurrentTime.ReplaceMainTimeTuple.AfterReceiving.NewTimeTuple.FromTSynModule,1 */
  /* store Virtual Local Time of the Main Tuple */
  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[commonIndex].virtualLocalTime, *localTimePtr);
  /* store Global Time of the Main Tuple */
  STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[commonIndex].globalTime, *timeStampPtr);

  /* reload the update counter */
  StbM_UpdateTimeTupleCounter[commonIndex] = STBM_UPDATE_COUNTER_VALUE;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


  return retval;
}

/* !LINKSTO StbM.SWS_StbM_00347,1 */
FUNC(uint8, STBM_CODE) StbM_GetTimeBaseUpdateCounter
(
  StbM_SynchronizedTimeBaseType timeBaseId
)
{
  /* Value of the time base update counter to be returned */
  uint8 RetVal = 0U;

  DBG_STBM_GETTIMEBASEUPDATECOUNTER_ENTRY(timeBaseId);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    RetVal = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetTimeBaseUpdateCounter,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTIMEBASEUPDATECOUNTER, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  /* Deviation TASKING-5 */
  /* Deviation MISRAC2012-4 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00348.TimeBaseId.NotConfigured.Or.WithinResevedRange,1 */
    /* !LINKSTO StbM.SWS_StbM_00348.Pure.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_GETTIMEBASEUPDATECOUNTER, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
    /* enter critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseUpdateCounter,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* The current time base update counter will be returned */
    /* !LINKSTO StbM.SWS_StbM_00414,1 */
    /* Deviation TASKING-1 */
    /* Deviation TASKING-2 */
    RetVal = StbM_TimeBaseUpdateCounter[STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId)];

    /* exit critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */
  }

#if (STBM_NUMBER_OF_SYNC_TIMEBASES == 0U)
  TS_PARAM_UNUSED(timeBaseId);
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES == 0U) */

  DBG_STBM_GETTIMEBASEUPDATECOUNTER_EXIT(RetVal, timeBaseId);

  return RetVal;
}


/*==[Definition of functions with internal linkage]===========================*/
#if (STBM_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime_DetChecks
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_BusSetGlobalTime,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_UNINIT);
  }
  /* Deviation MISRAC2012-4 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE_NO_PURE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00234.TimeBaseId.Invalid.TimeBaseId,1 */
    /* !LINKSTO StbM.SWS_StbM_00234.Pure.TimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM);
  }
  else if (timeStampPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00235.globalTimePtr,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM_POINTER);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00235.measureDataPtr,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM_POINTER);
  }
  else if (localTimePtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00235.localTimePtr,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM_POINTER);
  }
  else if (STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling BusSetGlobalTime for a master time base shall throw a DET error */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM);
  }
  else if (timeStampPtr->nanoseconds > STBM_NANOSEC_MAX_VALID_VALUE)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00455,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM_TIMESTAMP);
  }
  else if ((userDataPtr != NULL_PTR) && (userDataPtr->userDataLength > STBM_MAX_USER_DATA_LENGTH))
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00456,1 */
    STBM_DET_REPORTERROR(STBM_API_BUSSETGLOBALTIME, STBM_E_PARAM_USERDATA);
  }
  else
  {
    /* Defensive programming */
    STBM_PRECONDITION_ASSERT(!(STBM_TIME_STAMP_AND_VIRTUAL_LOCAL_TIME_IS_ZERO(timeStampPtr,localTimePtr)), DET_INTERNAL_API_ID);

    retval = E_OK;
  }


  return retval;
}
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */

/* !LINKSTO StbM.SWS_StbM_00180,1 */
/* !LINKSTO StbM.SWS_StbM_00413,1 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTimeInternal
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr,
  boolean checkGlobalTimeBit
)
{
  Std_ReturnType retval = E_NOT_OK;


  /* defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentTimeTupleGlobalPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentTimeTupleVLTPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(localTimePtr != NULL_PTR,DET_INTERNAL_API_ID);

#if (STBM_OFFSET_TIMEBASES_USED == STD_ON)
  if (STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
  {
    boolean calculateOffsetTime = FALSE;
    /* get the underlying synchronized time base (timeBaseId might be an offset Id or a pure Id) */
    uint8 syncIndex = STBM_GET_SYNC_TIMEBASE_INDEX(timeBaseId);

    retval = StbM_CheckCalculateOffsetTime(syncIndex,checkGlobalTimeBit,&calculateOffsetTime);

    /* Deviation TASKING-5 */
    if(TRUE == calculateOffsetTime)
    {
      /* If the timeBaseId is a Id pointing to an offset time base, the underlying
       * synchronized time base is not overwritten (avoid time jumps).
       * Instead the difference between the timestamp given and the current time
       * of the synchronized time base is stored for this offset time base.  */

      StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};

      /* get actual time for difference time calculation */
      retval = StbM_GetTime(syncIndex, &timeStampLocalTime, currentTimeTupleGlobalPtr, currentTimeTupleVLTPtr, localTimePtr);

      if (retval == E_OK)
      {

        /* perform the difference time calculation and store the difference time as
         * an offset time base. */
        /* !LINKSTO StbM.SWS_StbM_00304.StbM_SetGlobalTime.GLOBAL_TIME_BASE.Set.CalculateOffsetTime,1 */
        /* !LINKSTO StbM.SWS_StbM_00304.StbM_UpdateGlobalTime.GLOBAL_TIME_BASE.Set.CalculateOffsetTime,1 */
        retval = StbM_SubtractTimeStamps
          (
            timeStampPtr,
            &timeStampLocalTime,
            timeStampPtr
          );
      }
    }

    /* Deviation TASKING-4 */
    if (retval == E_OK)
    {
      /* if the difference between the minuend and the subtrahend was greater or equal to zero,
         the offset time shall be updated */
      /* !LINKSTO StbM.SWS_StbM_00304.StbM_SetGlobalTime.GLOBAL_TIME_BASE.Set.UpdateOffsetTime.GreaterOrEqualThan0,1 */
      /* !LINKSTO StbM.SWS_StbM_00304.StbM_UpdateGlobalTime.GLOBAL_TIME_BASE.Set.UpdateOffsetTime.GreaterOrEqualThan0,1 */
      retval = StbM_SetGlobalTimeBase(timeBaseId, timeStampPtr, localTimePtr);
    }

    /* if the difference between the minuend and the subtrahend was less than zero,
       the offset time will not be updated */
    /* !LINKSTO StbM.SWS_StbM_00304.StbM_SetGlobalTime.GLOBAL_TIME_BASE.Set.UpdateOffsetTime.LessThan0,1 */
    /* !LINKSTO StbM.SWS_StbM_00304.StbM_UpdateGlobalTime.GLOBAL_TIME_BASE.Set.UpdateOffsetTime.LessThan0,1 */
  }
  else
#else /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */
  TS_PARAM_UNUSED(checkGlobalTimeBit);
  TS_PARAM_UNUSED(currentTimeTupleGlobalPtr);
  TS_PARAM_UNUSED(currentTimeTupleVLTPtr);
#endif /* (STBM_OFFSET_TIMEBASES_USED == STD_ON) */
  {
    retval = StbM_SetGlobalTimeBase(timeBaseId, timeStampPtr, localTimePtr);
  }

  return retval;
}


STATIC FUNC(void, STBM_CODE) StbM_CalculateLocalTimeAndUpdate
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
)
{
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};

  /* get common index */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIndex);
      uint16 timeBaseStartIndex = 0U;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* store current Time Tuple values */
  STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobal, StbM_TimeStamps[commonIndex].globalTime);

  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLT, StbM_TimeStamps[commonIndex].virtualLocalTime);

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* Get current Virtual Local Time and check if it returned E_OK */
  if(E_OK == StbM_GetCurrentVirtualLocalTimeNoChecks(timeBaseId, &localTime))
  {
    /* obtain time */
    (void)StbM_GetTime(timeBaseId, timeStampPtr, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);

    /* Enter critical section */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeBaseNotificationEvents,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedEthOffsetData,1 */
    /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_SharedData,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    /* !LINKSTO StbM.SWS_StbM_00433.UpdateMainTimeTuple.AfterSetting.UpdateAfter3sec,1 */
    /* Update Time Tuple */
    STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[commonIndex].globalTime, *timeStampPtr);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[commonIndex].virtualLocalTime, localTime);

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
    /* set EV_RESYNC notification event after time was updated (because there was no update for 3 seconds) */
    /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
    STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_RESYNC);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
    /* !LINKSTO StbM.EB.SharedMemorySupport.UpdateSharedVariable.When.StbM_MainFunction,2 */
    StbM_UpdateSharedDataInMemory(timeBaseId, StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus, timeStampPtr, &localTime);
#else /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
    /* check if time base needs to share data to memory */
    if ((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[commonIndex].timeBaseRoleSharedData == STBM_TIME_BASE_PROVIDER_SHARED_DATA))
    {
      /* get array start index for this timebase */
      timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));

      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteBegin,1 */
      /* increment the 'begin' counter, this will signal the user that
         data is currently being written */
      Atomics_ThreadFence();
      StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX]++;
      Atomics_ThreadFence();

      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_MainFunction.NoUpdateFor3Seconds,1 */
      StbM_UpdateTimeTupleInSharedMemory(commonIndex, timeBaseStartIndex);

      /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteEnd,1 */
      /* increment the 'end' counter, this will signal the user that
         data has been written */
      Atomics_ThreadFence();
      StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX]++;
      Atomics_ThreadFence();
    }
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

    /* reload update counter */
    StbM_UpdateTimeTupleCounter[commonIndex] = STBM_UPDATE_COUNTER_VALUE;

    /* Leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }

}

#if ((STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) || (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON))
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateLocalTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
)
{
  Std_ReturnType retval;
  StbM_VirtualLocalTimeType localTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};

  /* get common index */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* store current Time Tuple values */
  STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobal, StbM_TimeStamps[commonIndex].globalTime);
  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLT, StbM_TimeStamps[commonIndex].virtualLocalTime);

  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* Get current Virtual Local Time */
  retval = StbM_GetCurrentVirtualLocalTimeNoChecks(timeBaseId, &localTime);

  if(E_OK == retval)
  {
    /* obtain time */
    retval = StbM_GetTime(timeBaseId, timeStampPtr, &currentTimeTupleGlobal, &currentTimeTupleVLT, &localTime);
  }

  return retval;
}
#endif /* ((STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) || (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON)) */



STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetTime
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
  Std_ReturnType retval;
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  retval = StbM_GetTimeSub
  (
    timeBaseId,
    timeStampPtr,
    currentTimeTupleGlobalPtr,
    currentTimeTupleVLTPtr,
    localTimePtr
  );

  /* Defensive programming */
  STBM_POSTCONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* !LINKSTO StbM.EB.GetTime.NoCheck.Timestamp,1 */
  if(StbM_SyncTimeBaseCfg[commonIndex].timeGetterFctPtr != (&StbM_GetCurrentTimeInternal))
  {
    if(timeStampPtr->nanoseconds > STBM_NANOSEC_MAX_VALID_VALUE)
    {
      /* !LINKSTO StbM.EB.GetTime.Invalid.Timestamp,1 */
      /* The returned value of the nanosecond is invalid */
      retval = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO StbM.EB.GetTime.Valid.Timestamp,1 */
      /* If the returned timestamp is valid don't change the retval */
    }
  }
  else
  {
    /* Defensive programming */
    STBM_POSTCONDITION_ASSERT(timeStampPtr->nanoseconds <= STBM_NANOSEC_MAX_VALID_VALUE,DET_INTERNAL_API_ID);
  }

  return retval;
}

STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeSub
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
  Std_ReturnType retval;
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentTimeTupleGlobalPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentTimeTupleVLTPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(localTimePtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* obtain our time. */
  retval = StbM_SyncTimeBaseCfg[commonIndex].timeGetterFctPtr
    (
      timeBaseId,
      timeStampPtr,
      currentTimeTupleGlobalPtr,
      currentTimeTupleVLTPtr,
      localTimePtr
    );
  return retval;
} /* StbM_GetTimeSub() */

STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTimeBase
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  uint8 cnt;
  Std_ReturnType retval = E_NOT_OK;  /* default value */
  boolean settingTimeFailed = FALSE;

  /* get the common index */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* obtain pointer to a list of index variables used to jump into
   * the function pointer table for the connected modules */
  CONSTP2CONST(uint8, AUTOMATIC, STBM_APPL_CONST) indexListPtr =
    StbM_SyncTimeBaseCfg[commonIndex].timeSetterIndexPtr;
  /* obtain size of list containing the index variables */
  uint8 numberOfTimeSetter = StbM_SyncTimeBaseCfg[commonIndex].numberOfTimeSetter;


  /* defensive programming */
  /* The config generator shall ensure that the pointer numberOfTimeSetter is consistent
     to the variable numberOfTimeSetter.
     Following variations are possible:
     1) ptr == NULL_PTR  &&  number == 0   --> valid, no master exists
     2) ptr != NULL_PTR  &&  number == 0   --> not valid, Pointer shows to something but
                                               numberOfTimeSetter indicates that there is no master
     3) ptr == NULL_PTR  &&  number >= 0   --> not valid, numberOfTimeSetter indicates that
                                               masters exist, but pointer is invalid
     4) ptr != NULL_PTR  &&  number >= 0   --> valid, master exists and pointer is valid
   */
  STBM_PRECONDITION_ASSERT( (indexListPtr == NULL_PTR) != (numberOfTimeSetter > 0U),
                            DET_INTERNAL_API_ID
                          );

  /* loop over all connected layer */
  for (cnt = 0U; cnt < numberOfTimeSetter; cnt++)
  {
    /* get index for function pointer table */
    uint8 bswIndex = indexListPtr[cnt];

#if (STBM_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    /* Bellow condition would've been TRUE in the following situation:
       1. numberOfTimeSetter > 0 && SetterFctPtrList[bswIndex] == NULL_PTR
       Situation 1 -> Will never happen, because the "NewMasterListEntry" list (which is filled in StbM_TimeBase.m file),
                      only contains the BswModulePos (adjacent BswModule position in the BswModuleList),
                      of adjacent BswModules which have SetGlobalTime API supported (see where "SetModule" variable is set to 'true')
                      and also the TimeSetter is increased based on that
       Please check "5.3.1.6. StbM_TimeSetterFctPtrList" from StbM_Design.pdf for more details */
    /* CHECK: NOPARSE */
    if (StbM_TimeSetterFctPtrList[bswIndex] == NULL_PTR)
    {
      /* unreachable code */
      STBM_UNREACHABLE_CODE_ASSERT(DET_INTERNAL_API_ID);
    }
    else
    /* CHECK: PARSE */
#endif
    {
      /* call the function to set global time */
      if (StbM_TimeSetterFctPtrList[bswIndex](timeBaseId, timeStampPtr, localTimePtr) != E_OK)
      {
        /* this function fails if at least one connected layer fails */
        settingTimeFailed = TRUE;
      }
    }
  }

  if (settingTimeFailed == FALSE)
  {
    /* setting time for all connected layer successful */
    retval = E_OK;
  }


  return retval;
}

/* !LINKSTO StbM.dsn.SummarizeTimestamps,1 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SumTimeStamps
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampAugendPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampAddendPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampSumPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  /* ignore overflow, since each nanosecond element should not reach 10^9 */
  uint32 NsSum = timeStampAugendPtr->nanoseconds + timeStampAddendPtr->nanoseconds;
  /* calculate seconds sum, overflow detection happens later */
  uint32 SecSum = timeStampAugendPtr->seconds + timeStampAddendPtr->seconds;
  /* store carry to add it to the seconds later */
  uint8 NsCarry = ((NsSum / STBM_NS_PER_SEC) > 0U) ? 1U : 0U;
  /* carry to add it to the high parts of seconds */
  uint8 SecCarry = 0U;


  /* defensive programming */
  /* Deviation TASKING-3 */
  STBM_PRECONDITION_ASSERT(timeStampAugendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampAddendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampSumPtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* Some important information for this algorithm:
   * If the sum of our (low-)seconds reaches the maximum value but we have a nanoseconds
   * carry we have also an overflow for the seconds.
   * The maximum carry value for the (low-)seconds is always 1.
   * Consider the worst case:
   * Augend: 0xffffffff, Addend: 0xffffffff, Nanoseconds overflow.
   * The sum of Augend and Addend is: 0xfffffffe, so the Nanoseconds can not cause
   * an additional overflow! */

  /* detect if sum of seconds causes an overflow */
  if ((0xffffffffU - timeStampAugendPtr->seconds) < timeStampAddendPtr->seconds)
  {
    SecCarry = 1U;
  }

  /* detect if nanoseconds overflow causes an overflow of the seconds */
  if ((SecSum == 0xffffffffU) && (NsCarry == 1U))
  {
    SecCarry = 1U;
  }

  /* check for overflow */
  /* !LINKSTO StbM.EB.GetCurrentTime.OffsetTimeBase,1 */
  if ((  (uint32)timeStampAugendPtr->secondsHi
       + (uint32)timeStampAddendPtr->secondsHi
       + (uint32)SecCarry
      ) <= (uint32)0xffffU
     )
  {
    /* write back nanosecond part */
    timeStampSumPtr->nanoseconds = NsSum % STBM_NS_PER_SEC;
    /* write back (low-)second part considering the Nanosecond carry */
    timeStampSumPtr->seconds = SecSum + NsCarry;
    /* write back (high-)second part
     * Don't consider overflows, this might happen in thousand of years. */
    timeStampSumPtr->secondsHi =
        timeStampAugendPtr->secondsHi
      + timeStampAddendPtr->secondsHi
      + SecCarry;
    /* no overflow */
    retval = E_OK;
  }

  return retval;
}

/* !LINKSTO StbM.dsn.SubtractTimestamps,1 */
STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_SubtractTimeStamps
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampMinuendPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampSubtrahendPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampDifferencePtr
)
{
  Std_ReturnType retval = E_NOT_OK;

  /* Difference between the nanoseconds part of Minuend and Subtrahend */
  uint32 NsDiff;
  /* Difference between the seconds part of Minuend and Subtrahend */
  uint32 SecDiff;
  /* Helper variable to take carry value into account for seconds part */
  uint32 SecSubtrahend;
  /* Helper variable to take carry value into account for seconds High part */
  uint32 SecHiSubtrahend;
  /* store seconds carry to subtract it to the seconds (high) later */
  uint8 SecCarry;
  /* store nanoseconds carry to subtract it to the seconds later */
  uint8 NsCarry;


  /* defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampMinuendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampSubtrahendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampDifferencePtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* Part 1: calculation for nanoseconds part of timestamp */

  /* We need some special arithmetic. Normal underflow is not sufficient.
   * If the subtrahend is bigger than the minuend, calculate from a base value of 10^9 */
  if (timeStampSubtrahendPtr->nanoseconds > timeStampMinuendPtr->nanoseconds)
  {
    /* Subtrahend bigger - calculate with underflow */
    NsDiff = (STBM_NS_PER_SEC + timeStampMinuendPtr->nanoseconds)
      - timeStampSubtrahendPtr->nanoseconds;
    NsCarry = 1U;
  }
  else
  {
    NsDiff = timeStampMinuendPtr->nanoseconds - timeStampSubtrahendPtr->nanoseconds;
    NsCarry = 0U;
  }

  /* Part 2: calculation for seconds (low) part of timestamp */

  /* Take carry value into account */
  SecSubtrahend = timeStampSubtrahendPtr->seconds + NsCarry;
  /* underflow of unsigned variables is defined in C */
  SecDiff = timeStampMinuendPtr->seconds - SecSubtrahend;
  /* check if we had an underflow */
  SecCarry = ((SecSubtrahend > timeStampMinuendPtr->seconds) || ((timeStampSubtrahendPtr->seconds == 0xffffffffU) && (NsCarry == 1U))) ? 1U : 0U;

  /* Part 3: calculation for seconds (high) part of timestamp (including error check) */

  /* check for "total" underflow (to avoid negative results) */
  SecHiSubtrahend = (uint32)timeStampSubtrahendPtr->secondsHi + (uint32)SecCarry;

  if (SecHiSubtrahend <= timeStampMinuendPtr->secondsHi)
  {
    /* calculation valid - store difference result to OUT parameter */
    timeStampDifferencePtr->nanoseconds = NsDiff;
    timeStampDifferencePtr->seconds = SecDiff;
    timeStampDifferencePtr->secondsHi = timeStampMinuendPtr->secondsHi - (uint16)SecHiSubtrahend;
    /* no underflow */
    retval = E_OK;
  }

  return retval;
}

STATIC FUNC(void, STBM_CODE) StbM_SubtractVirtualLocalTimesToTimeStamp
(
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeMinuendPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSubtrahendPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampDifferencePtr
)
{
  /* temp value for adding remaining values */
  StbM_VirtualLocalTimeType virtualLocalTimeDiff = {0U, 0U};


  /* defensive programming */
  STBM_PRECONDITION_ASSERT(virtualLocalTimeMinuendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(virtualLocalTimeSubtrahendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampDifferencePtr != NULL_PTR,DET_INTERNAL_API_ID);

  StbM_SubtractVirtualLocalTimes(virtualLocalTimeMinuendPtr, virtualLocalTimeSubtrahendPtr, &virtualLocalTimeDiff);

  StbM_VirtualLocalTimeToTimeStamp(&virtualLocalTimeDiff, timeStampDifferencePtr);

}

STATIC FUNC(void, STBM_CODE) StbM_SubtractVirtualLocalTimes
(
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeMinuendPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSubtrahendPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeDiff
)
{
  /* Difference between the nanosecondsLo part of Minuend and Subtrahend */
  uint32 NsLoDiff;
  /* Difference between the nanosecondsHi part of Minuend and Subtrahend */
  uint32 NsHiDiff;
  /* Helper variable to take carry value into account for nanosecondsHi part */
  uint32 NsHiSubtrahend;
  /* store nanosecondsHi carry to subtract it to the seconds later */
  uint8 nanosecondsHiCarry = 0U;


  /* defensive programming */
  STBM_PRECONDITION_ASSERT(virtualLocalTimeMinuendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(virtualLocalTimeSubtrahendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(virtualLocalTimeDiff != NULL_PTR,DET_INTERNAL_API_ID);

  /* Part 1: calculation for nanosecondsLo part of Virtual Local Time */

  /* If the subtrahend is bigger than the minuend, a unit needs to be subtracted from nanonseondsHi */
  if (virtualLocalTimeSubtrahendPtr->nanosecondsLo > virtualLocalTimeMinuendPtr->nanosecondsLo)
  {
    nanosecondsHiCarry = 1U;
  }

  /* Normal underflow is used. */
  NsLoDiff = virtualLocalTimeMinuendPtr->nanosecondsLo - virtualLocalTimeSubtrahendPtr->nanosecondsLo;

  /* Part 2: calculation for nanosecondsHi (low) part of Virtual Local Time */

  /* Take carry value into account */
  NsHiSubtrahend = virtualLocalTimeSubtrahendPtr->nanosecondsHi + nanosecondsHiCarry;
  /* calculate difference between nanosecondsHi parts, will always be zero or more */
  NsHiDiff = virtualLocalTimeMinuendPtr->nanosecondsHi - NsHiSubtrahend;

  virtualLocalTimeDiff->nanosecondsLo = NsLoDiff;
  virtualLocalTimeDiff->nanosecondsHi = NsHiDiff;

}

STATIC FUNC(void, STBM_CODE) StbM_VirtualLocalTimeToTimeStamp
(
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimePtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
)
{
  uint8 Idx;
  StbM_TimeStampType temp = {0U, 0U, 0U, 0U};


  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(virtualLocalTimePtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* make sure there is no garbage in this variable */
  STBM_INIT_TIMESTAMP_0(*timeStampPtr);

  /* Convert the 30 bits of the nanosecondsHi in the Virtual Local Time to time stamp. */
  for(Idx = 0U; Idx < 30U; Idx++)
  {
    if(virtualLocalTimePtr->nanosecondsHi == 0U)
    {
      /* Calculation finished for the seconds in the Virtual Local Time */
      break;
    }
    if((virtualLocalTimePtr->nanosecondsHi & 0x00000001U) == 1U)
    {
      (void)StbM_SumTimeStamps
      (
        timeStampPtr,
        &StbM_VRTtoTimeStampConversionTable[Idx],
        timeStampPtr
      );
    }

    virtualLocalTimePtr->nanosecondsHi >>= 1U;
  }

  /* add remianing seconds from nanosecondsLo */
  temp.seconds += virtualLocalTimePtr->nanosecondsLo / STBM_NS_PER_SEC;
  temp.nanoseconds += virtualLocalTimePtr->nanosecondsLo % STBM_NS_PER_SEC;

  (void)StbM_SumTimeStamps
  (
    timeStampPtr,
    &temp,
    timeStampPtr
  );


}

#if ((STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON) || (STBM_OFFSET_CORRECTION_USED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_SumVirtualLocalTimes
(
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeMinuendPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSubtrahendPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimeSumPtr
)
{
  /* store nanosecondsHi carry to subtract it to the seconds later */
  uint8 nanosecondsLoCarry = 0U;


  /* defensive programming */
  STBM_PRECONDITION_ASSERT(virtualLocalTimeMinuendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(virtualLocalTimeSubtrahendPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(virtualLocalTimeSumPtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* Part 1: calculation for nanosecondsLo part of Vitual Local Time */

  /* check vor overflow of nanosecondsLo */
  if ((0xffffffffU - virtualLocalTimeMinuendPtr->nanosecondsLo) < virtualLocalTimeSubtrahendPtr->nanosecondsLo)
  {
    nanosecondsLoCarry = 1U;
  }

  virtualLocalTimeSumPtr->nanosecondsLo = virtualLocalTimeMinuendPtr->nanosecondsLo + virtualLocalTimeSubtrahendPtr->nanosecondsLo;
  virtualLocalTimeSumPtr->nanosecondsHi = virtualLocalTimeMinuendPtr->nanosecondsHi + virtualLocalTimeSubtrahendPtr->nanosecondsHi + nanosecondsLoCarry;

}
#endif /* (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON) || (STBM_OFFSET_CORRECTION_USED == STD_ON) */

STATIC FUNC(boolean, STBM_CODE) StbM_TimeStampIsGreaterEqual
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampAPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampBPtr
)
{
  boolean retval = FALSE;


  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampAPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(timeStampBPtr != NULL_PTR,DET_INTERNAL_API_ID);

  if (timeStampAPtr->secondsHi > timeStampBPtr->secondsHi)
  {
    retval = TRUE;
  }
  else if (timeStampAPtr->secondsHi == timeStampBPtr->secondsHi)
  {
    if (timeStampAPtr->seconds > timeStampBPtr->seconds)
    {
      retval = TRUE;
    }
    else if (timeStampAPtr->seconds == timeStampBPtr->seconds)
    {
      if (timeStampAPtr->nanoseconds > timeStampBPtr->nanoseconds)
      {
        retval = TRUE;
      }
      else if (timeStampAPtr->nanoseconds == timeStampBPtr->nanoseconds)
      {
        retval = TRUE;
      }
      else
      {
        /* TimeStamp B(nanoseconds) > TimeStamp A(nanoseconds) */
        /* retval is set to FALSE */
      }
    }
    else
    {
      /* TimeStamp B(seconds) > TimeStamp A(seconds) */
      /* retval is set to FALSE */
    }
  }
  else
  {
    /* TimeStamp B(secondsHi) > TimeStamp A(secondsHi) */
    /* retval is set to FALSE */
  }

  return retval;
}

#if (STBM_TRIGGERED_CUSTOMERS_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_SyncTriggeredCustomer
(
  uint8 triggeredCustomerIndex,
  StbM_SynchronizedTimeBaseType timeBaseId
)
{
  StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};

  uint8 syncIndex = STBM_GET_SYNC_TIMEBASE_INDEX_FROM_SYNC_OR_PURE(timeBaseId);
  ScheduleTableStatusType scheduleTblStatus = SCHEDULETABLE_STOPPED;   /* use init value */
  ScheduleTableType scheduleTblIdx = StbM_TriggerCustomerCfg[triggeredCustomerIndex].scheduleTblIndex;


  /* !LINKSTO StbM.SWS_StbM_00020,1 */
  if (StbM_Os_GetScheduleTableStatus(scheduleTblIdx, &scheduleTblStatus) == E_OK)
  {
    /* schedule table shall be synchronized only in specific states */
    /* !LINKSTO StbM.SWS_StbM_00092,1 */
    if ((scheduleTblStatus == SCHEDULETABLE_WAITING) ||
        (scheduleTblStatus == SCHEDULETABLE_RUNNING) ||
        (scheduleTblStatus == SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS)
       )
    {
        StbM_TimeBaseStatusType tempTimeBaseStatus;

        TS_AtomicAssign8(tempTimeBaseStatus, StbM_TimeStamps[syncIndex].globalTime.timeBaseStatus);

        /* to synchronize a schedule table, a global time must be available*/
        /* !LINKSTO StbM.SWS_StbM_00077.GlobalTimeBase,1 */
        /* !LINKSTO StbM.SWS_StbM_00077.Timeout,1 */
        /* !LINKSTO StbM.SWS_StbM_00077.SyncToGateway,1 */
        /* !LINKSTO StbM.SWS_StbM_00077.TimeleapFuture,1 */
        /* !LINKSTO StbM.SWS_StbM_00077.TimeleapPast,1 */
        if(tempTimeBaseStatus == STBM_GLOBAL_TIME_BASE_FLAG)
        {
          /* enter critical section */
          /* !LINKSTO StbM.dsn.SyncOsScheduleTable,1 */
          SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_1();

          if (StbM_CalculateLocalTime(timeBaseId, &timeStampLocalTime) == E_OK)
          {
              uint32 schdlTblDur = StbM_TriggerCustomerCfg[triggeredCustomerIndex].scheduleTblDuration;
              uint32 nanoseconds;
              uint32 currentTimeTicks;
              uint32 currentSchdlTblTicks;

              nanoseconds = timeStampLocalTime.nanoseconds;

              /* convert StbM local time (nanoseconds) to ticks */
              /* calculate how many ticks have passed in Os, based on the StbM local time (also converted in ticks) */
              /* !LINKSTO StbM.SWS_StbM_00303.AllCalculations.DoneIn.Nanoseconds,1 */
              /* !LINKSTO StbM.dsn.TriggeredCustomers.ClockFreq.EnabledAndConfigured.FoundInList.UseTheMorePrecise.OsMacro,1 */
              /* !LINKSTO StbM.dsn.TriggeredCustomers.ClockFreq.EnabledAndConfigured.NotFoundInList.UseTheLessPrecise.Macro,1 */
              /* !LINKSTO StbM.dsn.TriggeredCustomers.ClockFreq.Disabled.UseTheLessPrecise.Macro,1 */
              currentTimeTicks = StbM_ConvNsToTicks(triggeredCustomerIndex, nanoseconds);

              currentSchdlTblTicks = currentTimeTicks % schdlTblDur;

              /* synchronizing the OS ScheduleTable customer. Dealing with errors
               * during the interaction with customers are out of StbM module scope.
               * (see chapter '4.1.5 Out of scope' from StbM's 4.4.0 SWS document.) */
              /* !LINKSTO StbM.SWS_StbM_00020,1 */
              /* !LINKSTO StbM.SWS_StbM_00302,1 */
              (void) StbM_Os_SyncScheduleTable(scheduleTblIdx, (TickType)currentSchdlTblTicks );
          }

          /* leave critical section */
          SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_1();

        }
    }
  }

}
#endif /* STBM_TRIGGERED_CUSTOMERS_USED == STD_ON */

STATIC FUNC(void, STBM_CODE) StbM_HandleTimeLeap
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr
)
{
  /* Store the result of the time leap status detection */
  uint8 TimeLeapStatusFlagsOut = 0U;
  /* get the offset into the zero-based dense configuration existing for all time bases. */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);


  /* In case the threshold is exceeded the StbM shall set the TIMELEAP bit.
   * If the next update is within the threshold the StbM shall clear the TIMELEAP bit. */
  if (StbM_TimeLeapDetection(commonIndex, currentTimeBaseTimePtr, timeStampPtr, &TimeLeapStatusFlagsOut) == TRUE)
  {
#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
    /* !LINKSTO StbM.SWS_StbM_00182.SET_TIMELEAP_FUTURE_BIT,1 */
    /* !LINKSTO StbM.SWS_StbM_00305.SET_TIMELEAP_PAST_BIT,1 */
    STBM_FLAG_SET(*flagsOutPtr, TimeLeapStatusFlagsOut);

    /* !LINKSTO StbM.ECUC_StbM_00037_Conf,1 */
    /* Get the configured value of the clear time leap counter */
    if (TimeLeapStatusFlagsOut == STBM_TIME_LEAP_FUTURE_FLAG)
    {
      StbM_TimeLeapInfo[commonIndex].future = StbM_CommonTimeBaseCfg[commonIndex].clearTimeleapCount;
    }
    else
    {
      StbM_TimeLeapInfo[commonIndex].past = StbM_CommonTimeBaseCfg[commonIndex].clearTimeleapCount;
    }
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */
  }
#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
  StbM_HandleTimeLeapCounter(&StbM_TimeLeapInfo[commonIndex].future, flagsOutPtr, STBM_TIME_LEAP_FUTURE_FLAG);

  StbM_HandleTimeLeapCounter(&StbM_TimeLeapInfo[commonIndex].past, flagsOutPtr, STBM_TIME_LEAP_PAST_FLAG);
#else
  TS_PARAM_UNUSED(flagsOutPtr);
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */

}


STATIC FUNC(boolean, STBM_CODE) StbM_TimeLeapDetection
(
  uint8 commonIndex,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTime,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr
)
{
  StbM_TimeStampType TimeStampDiffValue       = {0U, 0U, 0U, 0U}; /* Use initial values */
#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
  StbM_TimeStampType ConfiguredTimeLeapValue  = {0U, 0U, 0U, 0U};
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */
  StbM_TimeStampType TimeStampA               = {0U, 0U, 0U, 0U};
  StbM_TimeStampType TimeStampB               = {0U, 0U, 0U, 0U};
#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
  uint8 TmpJumpType = 0U;
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */
  /* Max positive value that can be represented on sint32 */
  StbM_TimeStampType maxAllowedValue = {0U, 147483647U, 2U, 0U};
  /* The initial value is "time leap not detected".
   * If no errors occur and a time leap is detected, then this flag is set to TRUE. */
  boolean timeLeapDetected = FALSE;

#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
  /* Variable to store the direction of the time leap */
  uint8 CurrentTimeLeapStatusFlag = 0U;
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */

  /* defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* When the function StbM_BusSetGlobalTime() is initially called, time leap detection
   * shall not be performed.
   * In this case the timeBaseStatus of the synchronized slave time base is not set.
   * The timeBaseStatus gets updated at the end of StbM_BusSetGlobalTime() after time
   * leap detection is performed. */
  if (STBM_FLAG_IS_SET(StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus,
                       STBM_GLOBAL_TIME_BASE_FLAG
                      )
     )
  {
    if (StbM_TimeStampIsGreaterEqual(timeStampPtr, currentTimeBaseTime))
    {
#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
      /* !LINKSTO StbM.SWS_StbM_00182.ZERO_THRESHOLD,1 */
      /* A threshold of 0 shall deactivate this check. */
      if(STBM_TIME_LEAP_FUTURE_THRESHOLD_DISABLED(commonIndex) == FALSE)
      {
        CurrentTimeLeapStatusFlag = STBM_TIME_LEAP_FUTURE_FLAG;
        /* load threshold value from configuration */
        /* !LINKSTO StbM.ECUC_StbM_00041_Conf,1 */
        ConfiguredTimeLeapValue.nanoseconds =
          StbM_CommonTimeBaseCfg[commonIndex].timeleapFutureValueNs;
        ConfiguredTimeLeapValue.seconds     =
          StbM_CommonTimeBaseCfg[commonIndex].timeleapFutureValueSec;
      }
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */
        /* current time stamp > previous time stamp, TimeStampA always holds the higher value */
        STBM_ASSIGN_TIMESTAMP(TimeStampA, *timeStampPtr);
        STBM_ASSIGN_TIMESTAMP(TimeStampB, *currentTimeBaseTime);
#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
        TmpJumpType = STBM_TIME_LEAP_FUTURE_FLAG;
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */
    }
    else
    {
#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
      /* !LINKSTO StbM.SWS_StbM_00305.ZERO_THRESHOLD,1 */
      /* A threshold of 0 shall deactivate this check. */
      if (STBM_TIME_LEAP_PAST_THRESHOLD_DISABLED(commonIndex) == FALSE)
      {
        CurrentTimeLeapStatusFlag = STBM_TIME_LEAP_PAST_FLAG;
        /* load threshold value from configuration */
        /* !LINKSTO StbM.ECUC_StbM_00042_Conf,1 */
        ConfiguredTimeLeapValue.nanoseconds =
          StbM_CommonTimeBaseCfg[commonIndex].timeleapPastValueNs;
        ConfiguredTimeLeapValue.seconds     =
          StbM_CommonTimeBaseCfg[commonIndex].timeleapPastValueSec;
      }
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */
        /* previous time stamp > current time stamp, TimeStampA always holds the higher value */
        STBM_ASSIGN_TIMESTAMP(TimeStampB, *timeStampPtr);
        STBM_ASSIGN_TIMESTAMP(TimeStampA, *currentTimeBaseTime);
#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
        TmpJumpType = STBM_TIME_LEAP_PAST_FLAG;
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */
    }

      /* Cast to void for the returned value because TimeStampA is always higher then TimeStampB */
      (void)StbM_SubtractTimeStamps(&TimeStampA, &TimeStampB, &TimeStampDiffValue);
      if(TRUE == StbM_TimeStampIsGreaterEqual(&TimeStampDiffValue, &maxAllowedValue))
      {
#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
        /* If the calculated time difference exceeds the value range of the timeJump parameter,
         * the returned time difference shall be limited to either the maximum negative or the
         *  maximum positive value of the type of timeJump */
        if(TmpJumpType == STBM_TIME_LEAP_PAST_FLAG)
        {
          /* !LINKSTO StbM.SWS_StbM_00425.DifferenceExceeds.MaximumNegative.Range,1 */
          StbM_TimeLeapInfo[commonIndex].timejump = STBM_MAX_NEGATIVE_SINT32_VALUE;
        }
        else
        {
          /* !LINKSTO StbM.SWS_StbM_00425.DifferenceExceeds.MaximumPositive.Range,1 */
          StbM_TimeLeapInfo[commonIndex].timejump = STBM_MAX_POSITIVE_SINT32_VALUE;
        }
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */
      }
      else
      {
#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
        uint32 tmpTimeLeap = (TimeStampDiffValue.seconds * STBM_NS_PER_SEC) + TimeStampDiffValue.nanoseconds;
        /* If the calculated time difference exceeds the value range of the timeJump parameter,
         * the returned time difference shall be limited to either the maximum negative or the
         *  maximum positive value of the type of timeJump */
        /* !LINKSTO StbM.SWS_StbM_00425.Calculate.TimeDifference,1 */
        if(TmpJumpType == STBM_TIME_LEAP_PAST_FLAG)
        {
          StbM_TimeLeapInfo[commonIndex].timejump = (-1) * ((sint32)tmpTimeLeap);
        }
        else
        {
          StbM_TimeLeapInfo[commonIndex].timejump = (sint32)tmpTimeLeap;
        }
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */
      }
#if(STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON)
      /* Timejump was calculated */
      StbM_TimeLeapInfo[commonIndex].timeJumpCalculated = TRUE;
#endif /* STBM_SYNC_SLAVE_TIMEBASES_CONFIGURED == STD_ON */

#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
    if (CurrentTimeLeapStatusFlag != 0U)
    {
      /* !LINKSTO StbM.SWS_StbM_00182.THRESHOLD,1 */
      /* !LINKSTO StbM.SWS_StbM_00305.THRESHOLD,1 */
      if (StbM_TimeStampIsGreaterEqual(&TimeStampDiffValue, &ConfiguredTimeLeapValue))
      {
        /* Time leap detected, timeLeapDetected is TRUE for
         * TimeStampDiffValue > ConfiguredTimeLeapValue */
        *flagsOutPtr = CurrentTimeLeapStatusFlag;
        timeLeapDetected = TRUE;
      }
    }
#else
    TS_PARAM_UNUSED(flagsOutPtr);
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */
  }


  return timeLeapDetected;
}

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_StatusEventDetection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_TimeBaseNotificationType StbM_NotificationEvents
)
{
  uint8 commonIdx = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* Get the notification mask for synchronized or offset time bases */
  uint32 NotificationMask = STBM_GET_NOTIFICATION_MASK(commonIdx);


  /* Check if any of the bits has been set, and the callback and SR interface exists for the current time base */
  /* !LINKSTO StbM.SWS_StbM_00278.NotificationMask,1 */
  /* !LINKSTO StbM.SWS_StbM_00278.NotificationEvents,1 */
  /* !LINKSTO StbM.SWS_StbM_00282.ReportedThrough_Callback_SRInterface,1 */
  if((NotificationMask & StbM_NotificationEvents) != 0U)
  {
      StbM_NotificationEvents &= NotificationMask;

      /* CDD is notified */
      /* !LINKSTO StbM.SWS_StbM_00277.NoNotification,1 */
      if(StbM_CallbacksPtrList[commonIdx].statusNotificationCbkFctPtr != NULL_PTR)
      {
        /* !LINKSTO StbM.SWS_StbM_00282.SetEventNotificationParameter,1 */
        /* Notify the CDD through Callback */
        (void)StbM_CallbacksPtrList[commonIdx].statusNotificationCbkFctPtr(StbM_NotificationEvents);
        /* Clear the buffer for notification events if the callback was called at least for one time */
        /* !LINKSTO StbM.SWS_StbM_00280,1 */
      }

#if (STBM_RTE_USED == STD_ON)
      /* Application is notified */
      /* !LINKSTO StbM.SWS_StbM_00277.NoNotification,1 */
      if(StbM_CallbacksPtrList[commonIdx].statusNotificationRteCbkFctPtr != NULL_PTR)
      {
        /* !LINKSTO StbM.SWS_StbM_00282.SetEventNotificationParameter,1 */
        /* Notify the application through SR Interface */
        (void)StbM_CallbacksPtrList[commonIdx].statusNotificationRteCbkFctPtr(StbM_NotificationEvents);
        /* Clear the buffer for notification events if the callback was called at least for one time */
        /* !LINKSTO StbM.SWS_StbM_00280,1 */
      }
#endif /* (STBM_RTE_USED == STD_ON) */

  }
  /* Clear the notification events if the callback was called at least for one time */
  /* !LINKSTO StbM.SWS_StbM_00280,1 */

}

STATIC FUNC(void, STBM_CODE) StbM_UpdateNotificationStatus
(
  uint8 flags,
  StbM_TimeStampType currentTimeStamp,
  P2VAR(StbM_TimeBaseNotificationType, AUTOMATIC, STBM_APPL_DATA) statusNotificationPtr
)
{
 if(STBM_FLAG_IS_SET(flags, STBM_TIMEOUT_FLAG))
 {
   STBM_FLAG_SET(*statusNotificationPtr, STBM_EV_TIMEOUT_REMOVED);
 }
 if((STBM_FLAG_IS_SET(flags, STBM_SYNC_TO_GATEWAY_FLAG)) && (STBM_SYNC_TO_GATEWAY_FLAG !=(currentTimeStamp.timeBaseStatus & STBM_SYNC_TO_GATEWAY_FLAG)))
 {
    /* Transition from 1 to 0. */
    /* !LINKSTO StbM.SWS_StbM_00284.EV_SYNC_TO_GLOBAL_MASTER,1 */
    STBM_FLAG_SET(*statusNotificationPtr, STBM_EV_SYNC_TO_GLOBAL_MASTER);
 }
 if((STBM_FLAG_IS_SET(currentTimeStamp.timeBaseStatus, STBM_SYNC_TO_GATEWAY_FLAG)) && (STBM_SYNC_TO_GATEWAY_FLAG !=(flags & STBM_SYNC_TO_GATEWAY_FLAG)))
 {
   /* Transition from 0 to 1. */
   /* !LINKSTO StbM.SWS_StbM_00284.EV_SYNC_TO_SUBDOMAIN,1 */
   STBM_FLAG_SET(*statusNotificationPtr, STBM_EV_SYNC_TO_SUBDOMAIN);
 }
} /* StbM_UpdateNotificationStatus */
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#if (STBM_OS_COUNTER_USED == STD_ON)
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTime_BasedOn_OsCounter
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR( StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  TickType osTicks = 0U;
  TickType tempOsTicks = 0U;
  uint32 nanoseconds = 0U;
  uint8 carry = 0U;


  /* not needed for Os, there is only one counter */
  TS_PARAM_UNUSED(timeBaseId);


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* save previous ticks in a local variable;
     this is necessary since we could be interrupted by another
     call of this function and could rewrite this variable */
  tempOsTicks = StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter;

  /* exit critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


  /* get the actual counter value */
  if (StbM_Os_GetCounterValue(STBM_OS_COUNTER_ID, &osTicks) == E_OK)
  {
    TickType tempElaspsedValue = 0U;

    /* enter critical section */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


    /* check if a preemption has occurred */
    if(tempOsTicks == StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter)
    {
      /* handle Os counter */
      if(StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter <= osTicks)
      {
        tempElaspsedValue = osTicks - StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter;
      }
      /* counter wrap-around */
      else
      {
        tempElaspsedValue = (STBM_MAX_OS_COUNTER_VALUE_IN_TICKS - StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter) + (osTicks + 1U);
      }

      StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OsCounter = osTicks;

      /* convert this ticks to a nanoseconds value */
      nanoseconds = (uint32)STBM_OS_COUNTER_CONV_TICKS_TO_NS(tempElaspsedValue);

      /* Add elapsed time to the Virtual Local Time */
      /* check for overflow */
      /* !LINKSTO StbM.SWS_StbM_00515,1 */
      if((STBM_NANOSECONDS_LO_MAX - nanoseconds) < StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OsCounter.nanosecondsLo)
      {
        carry = 1U;
      }

      StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OsCounter.nanosecondsLo += nanoseconds;
      StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OsCounter.nanosecondsHi += carry;
    }

    /* even if the function was preempted by itself or not,
       localTimePtr shall be updated with the most recent value of the OsCounter */
    /* !LINKSTO StbM.EB.StbM_GetCurrentVirtualLocalTime.Os.PreemptedByItself,1 */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*localTimePtr, StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OsCounter);

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  }


  return retval;
}
#endif /* STBM_OS_COUNTER_USED == STD_ON */




#if (STBM_OSGETTIMESTAMP_USED == STD_ON)
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTime_Using_OSGetTimeStamp
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR( StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_OK;

  /* intentionally uninitialized since os_timestamp_t can also be a structure */
  os_timestamp_t currentOsTicksTakenThroughGetTimeStamp;
  os_timestamp_t previousOsTicksTakenThroughGetTimeStamp;
  os_tick_t tempElaspsedValue = 0U;
  uint32 nanoseconds = 0U;
  uint8 carry = 0U;


  /* not needed for Os, there is only one counter */
  TS_PARAM_UNUSED(timeBaseId);


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  previousOsTicksTakenThroughGetTimeStamp = StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OSGetTimeStamp;

  /* !LINKSTO StbM.dsn.Taking.VirtualLocalTime.From.OS.Through.OS_GetTimeStamp.API,1 */
  /* get the current time, through OS_GetTimeStamp API */
  OS_GetTimeStamp(&currentOsTicksTakenThroughGetTimeStamp);

  /* !LINKSTO StbM.dsn.Calculate.Elapsed.Time.When.StbMUseOSGetTimeStamp.Enabled,1 */
  /* calculate the difference between the current and the previous saved time stamp */
  tempElaspsedValue = OS_DiffTime32(&currentOsTicksTakenThroughGetTimeStamp, &previousOsTicksTakenThroughGetTimeStamp);

  /* the current time stamp, becomes now the previous time stamp */
  StbM_VirtualLocalTimeSources.StbM_PreviousOsTicks_OSGetTimeStamp = currentOsTicksTakenThroughGetTimeStamp;

  /* !LINKSTO StbM.dsn.OSGetTimeStamp.API.Used.OSTicks.To.Ns.Conversion,1 */
  /* convert this ticks to a nanoseconds value, using OS_TimestampTicksToNs function/macro */
  nanoseconds = (uint32)OS_TimestampTicksToNs(tempElaspsedValue);

  /* !LINKSTO StbM.SWS_StbM_00515,1 */
  /* Add elapsed time to the Virtual Local Time */
  /* check for overflow */
  if((STBM_NANOSECONDS_LO_MAX - nanoseconds) < StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OSGetTimeStamp.nanosecondsLo)
  {
    carry = 1U;
  }

  StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OSGetTimeStamp.nanosecondsLo += nanoseconds;
  StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OSGetTimeStamp.nanosecondsHi += carry;

  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*localTimePtr, StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_OSGetTimeStamp);

  /* exit critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();



  return retval;
}
#endif /* STBM_OSGETTIMESTAMP_USED == STD_ON */




#if (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON)
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTimeEthTSyn
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_TimeStampType hwLocalTime = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentVirtualLocalTime = {0U, 0U};
  Eth_TimeStampQualType TimeQuality = ETH_UNCERTAIN;
  Eth_TimeStampType EthTimeStamp = {0U, 0U, 0U};

  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* get the Ethernet controller index associated to this time base */
  uint8 ethIfControllerIdx = StbM_SyncTimeBaseCfg[commonIndex].timeBaseLocalTimeIdx;


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* get the current value of the free running HW counter
     from the corresponding Ethernet Controller via EthIf_GetCurrentTime() */
  retval = EthIf_GetCurrentTime(
      ethIfControllerIdx,
      &TimeQuality,
      &EthTimeStamp
  );

  /* !LINKSTO StbM.SWS_StbM_00515,1 */
  /* !LINKSTO StbM.EB.SWS_StbM_00178.EthIf_GetCurrentTime.E_OK.timeQualPtr.ETH_VALID.DoNotIgnoreTimeValue, 1 */
  /* !LINKSTO StbM.EB.SWS_StbM_00178.EthIf_GetCurrentTime.E_OK.timeQualPtr.ETH_VALID.StbM_GetCurrentVirtualLocalTimeEthTSyn.returns.E_OK, 1 */
  if((E_OK == retval) && (TimeQuality == ETH_VALID) && (EthTimeStamp.nanoseconds <= STBM_NANOSEC_MAX_VALID_VALUE))
  {
    /* save EthTimeStamp of type Eth_TimeStampType to hwLocalTime of type StbM_TimeStampType */
    hwLocalTime.nanoseconds = EthTimeStamp.nanoseconds;
    hwLocalTime.seconds = EthTimeStamp.seconds;
    hwLocalTime.secondsHi = EthTimeStamp.secondsHi;

    /* convert current time from EthTSyn of type StbM_TimeStampType to StbM_VirtualLocalTimeType */
    StbM_TimeStampToVirtualLocalTime(&hwLocalTime, &currentVirtualLocalTime);

    /* assign the time taken from EthTSyn to localTimePtr */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*localTimePtr, currentVirtualLocalTime);
  }
  else
  {
    /* !LINKSTO StbM.EB.SWS_StbM_00178.EthIf_GetCurrentTime.E_NOT_OK.IgnoreTimeValue, 1 */
    /* !LINKSTO StbM.EB.SWS_StbM_00178.EthIf_GetCurrentTime.E_NOT_OK.StbM_GetCurrentVirtualLocalTimeEthTSyn.returns.E_NOT_OK, 1 */
    /* !LINKSTO StbM.SWS_StbM_00178.EthIf_GetCurrentTime.ETH_UNCERTAIN, 1 */
    /* !LINKSTO StbM.SWS_StbM_00178.EthIf_GetCurrentTime.ETH_INVALID, 1 */
    /* !LINKSTO StbM.EB.SWS_StbM_00178.EthIf_GetCurrentTime.InvalidNsTimeStamp.IgnoreTimeValue, 1 */
    /* !LINKSTO StbM.EB.SWS_StbM_00178.EthIf_GetCurrentTime.InvalidNsTimeStamp.StbM_GetCurrentVirtualLocalTimeEthTSyn.returns.E_NOT_OK, 1 */
    retval = E_NOT_OK;
  }


  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


  return retval;
}
#endif /* STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON */



#if (STBM_GPT_USED == STD_ON)
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTimeGpt
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR( StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  Gpt_ValueType currentGptTicks = 0U;
  uint8 carry = 0U;
  uint32 nanoseconds = 0U;

  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  uint8 idxGpt = StbM_SyncTimeBaseCfg[commonIndex].timeBaseLocalTimeIdx;

  Gpt_ChannelType gptChannelId = StbM_GptTimeBases[idxGpt].gptChannelId;
  uint32 maxChannelTickValue = StbM_GptTimeBases[idxGpt].gptMaxChannelTickValue;

  /* get the actual counter value */
  Gpt_ValueType tempElaspsedValue = 0U;


  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* !LINKSTO StbM.dsn.GptTimeSource,1 */
  /* !LINKSTO StbM.SWS_StbM_00512,1 */
  currentGptTicks = Gpt_GetTimeElapsed(gptChannelId);

  /* handle Gpt ticks */
  if(StbM_VirtualLocalTimeSources.StbM_PreviousGptTicks[idxGpt] <= currentGptTicks)
  {
    tempElaspsedValue = currentGptTicks - StbM_VirtualLocalTimeSources.StbM_PreviousGptTicks[idxGpt];
  }
  /* counter wrap-around */
  else
  {
    tempElaspsedValue = (maxChannelTickValue - StbM_VirtualLocalTimeSources.StbM_PreviousGptTicks[idxGpt]) + currentGptTicks + 1U;
  }

  /* save the current Gpt ticks as previous, which will be used
   * when another value for ticks is taken from GPT */
  StbM_VirtualLocalTimeSources.StbM_PreviousGptTicks[idxGpt] = currentGptTicks;

  /* !LINKSTO StbM.dsn.Conversion.When.TimeSource.Is.GPT.MacrosFrom.StbM_TimeConversionMacros.Used,1 */
  /* !LINKSTO StbM.dsn.Conversion.When.TimeSource.Is.GPT.Macro.STBM_GPT_CONV_TICKS_TO_NS.Used,1 */
  /* !LINKSTO StbM.SWS_StbM_00352.VLT_DerivedFrom_GPT,1 */
  /* Convert ticks into nanoseconds, when the time is taken from it's local hardware clock */
  nanoseconds = StbM_ConvGptTicksToNs(timeBaseId, tempElaspsedValue);

  /* !LINKSTO StbM.SWS_StbM_00515,1 */
  /* Add elapsed time to the Virtual Local Time */
  /* check for overflow */
  if((STBM_NANOSECONDS_LO_MAX - nanoseconds) < StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_Gpt[idxGpt].nanosecondsLo)
  {
    carry = 1U;
  }

  StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_Gpt[idxGpt].nanosecondsLo += nanoseconds;
  StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_Gpt[idxGpt].nanosecondsHi += carry;

  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*localTimePtr, StbM_VirtualLocalTimeSources.StbM_VirtualLocalTime_Gpt[idxGpt]);

  retval = E_OK;

  /* leave critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();


  return retval;
}
#endif /* STBM_GPT_USED == STD_ON */



#if (STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_TimeStampToVirtualLocalTime
(
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) virtualLocalTimePtr
)
{
  uint8 Idx;
  StbM_VirtualLocalTimeType temp = {0U, 0U};


  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(virtualLocalTimePtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* !LINKSTO StbM.EB.StbM_GetCurrentVirtualLocalTimeEthTSyn.MAX,1 */
  /* Convert the 32 bits of the seconds in the time stamp to Virtual Local Time. */
  for(Idx = 0U; Idx < 32U; Idx++)
  {
    if(timeStampPtr->seconds == 0U)
    {
      /* Calculation finished for the seconds in the time stamp */
      break;
    }
    if((timeStampPtr->seconds & 0x00000001U) == 1U)
    {
      StbM_SumVirtualLocalTimes
      (
        virtualLocalTimePtr,
        &StbM_TimeStampToVRTConversionTable[Idx],
        virtualLocalTimePtr
      );
    }

    timeStampPtr->seconds >>= 1U;
  }

  temp.nanosecondsLo = timeStampPtr->nanoseconds;

  /* don't forget the nanoseconds, seconds and secondsHi will be 0 here */
  StbM_SumVirtualLocalTimes
  (
    virtualLocalTimePtr,
    &temp,
    virtualLocalTimePtr
  );

}
#endif /* STBM_VIRTUAL_LOCALTIME_ETHTSYN_USED == STD_ON */

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(boolean, STBM_CODE) StbM_CheckIntervalTiming
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint8 intervalCounter
)
{
  StbM_TimeStampType intervalTimeDiff = {0U, 0U, 0U, 0U};
  StbM_TimeStampType rateCorrectionInterval = {0U, 0U, 0U, 0U};
  boolean calculateRate = FALSE;
  uint8 intervalCounterMin = 0U;
  uint8 intervalCounterMax = 0U;

  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* get index for the StbM_SlaveRateCorrectionData[] array */
  uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);

  intervalCounterMin = StbM_CommonTimeBaseCfg[commonIndex].startIndexRcIntervals;
  intervalCounterMax = StbM_CommonTimeBaseCfg[commonIndex].stopIndexRcIntervals;
  rateCorrectionInterval.nanoseconds = StbM_CommonTimeBaseCfg[commonIndex].rateCorrectionIntervalNs;
  rateCorrectionInterval.seconds = StbM_CommonTimeBaseCfg[commonIndex].rateCorrectionIntervalSec;


  if(!STBM_VIRTUAL_LOCAL_TIME_IS_ZERO(StbM_SlaveRateCorrectionStartValues[intervalCounter].startVirtualLocalTime))
  {
    /* decrease interval counter, since we need to use the previous value of Virtual Local Time */
    if(intervalCounter == intervalCounterMin)
    {
      /* counter wrap around */
      intervalCounter = intervalCounterMax;
    }
    else
    {
      intervalCounter--;
    }

    /* perform the difference time calculation between the current Virtual Local Time(stop)
     * and the stored (start) Virtual Local Time */
    StbM_SubtractVirtualLocalTimesToTimeStamp
    (
      &StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.virtualLocalTime,
      &StbM_SlaveRateCorrectionStartValues[intervalCounter].startVirtualLocalTime,
      &intervalTimeDiff
    );

    /* check if the time interval that was configured has been exceeded */
    if (StbM_TimeStampIsGreaterEqual(&intervalTimeDiff, &rateCorrectionInterval))
    {
      calculateRate = TRUE;
    }
  }
  else
  {
    /* check if this is the fisrt call to StbM_BusSetGlobalTime() */
    if((StbM_SlaveRateCorrectionData[rcDataIndex].initialFlags & STBM_GLOBAL_TIME_BASE_FLAG) != STBM_GLOBAL_TIME_BASE_FLAG)
    {
      /* This is the first call for StbM_BusSetGlobalTime()
         allow storing the initial values, even though in this case
         Rate Correction will not be calculated because of the
         other counters */
      /* also the value of the SYNC_TO_GATEWAY flag will be saved */
      if(STBM_FLAG_IS_SET(StbM_SlaveRateCorrectionData[rcDataIndex].updatedFlags, STBM_SYNC_TO_GATEWAY_FLAG))
      {
        StbM_SlaveRateCorrectionData[rcDataIndex].syncToGateway = STBM_SYNC_TO_GATEWAY_FLAG;
      }
      else
      {
        StbM_SlaveRateCorrectionData[rcDataIndex].syncToGateway = 0U;
      }
    }

    calculateRate = TRUE;
  }


  return calculateRate;
}
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(uint32, STBM_CODE) StbM_Div_Q
(
  uint32 a,
  uint32 b
)
{
  uint32 aux = 0U;
  uint32 lo = a << STBM_Q_FRACTION;
  uint32 hi = a >> STBM_Q_INTEGRAL;

  uint64 temp = ((uint64) hi << 32U) | lo;


  aux = b / 2U;
  temp = temp + ((uint64)aux);

  temp = StbM_Udiv64_32(temp, b);


  return (uint32)temp;
}
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_RATE_CORRECTION_USED)
STATIC FUNC(uint32, STBM_CODE) StbM_Umul32_hi
(
  uint32 a,
  uint32 b
)
{
  /* split operands into halves */
  uint32 al = (uint16)a;
  uint32 ah = a >> 16;
  uint32 bl = (uint16)b;
  uint32 bh = b >> 16;
  /* compute partial products */
  uint32 p0 = al * bl;
  uint32 p1 = al * bh;
  uint32 p2 = ah * bl;
  uint32 p3 = ah * bh;
  /* sum partial products */
  uint32 cy = ((p0 >> 16) + (uint16)p1 + (uint16)p2) >> 16;
  uint32 rhi = p3 + (p2 >> 16) + (p1 >> 16) + cy;

  return rhi;
}

STATIC FUNC(void, STBM_CODE) StbM_Umul32_Wide
(
  uint32 a,
  uint32 b,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rhi,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rlo
)
{

  /* bits <31:0> of the product a * b */
  *rlo = a * b;
  /* bits <63:32> of the product a * b */
  *rhi = StbM_Umul32_hi (a, b);

}

STATIC FUNC(uint64, STBM_CODE) StbM_Umul32_64
(
  uint32 a,
  uint32 b
)
{
  uint32 hi, lo;
  uint64 product;


  StbM_Umul32_Wide(a, b, &hi, &lo);

  product = (uint64)(((uint64)hi << 32) | lo);


  return product;
}

STATIC FUNC(uint64, STBM_CODE) StbM_Udiv64_32
(
  uint64 n,
  uint32 base
)
{
  uint64 rem = n;
  uint64 b = base;
  uint64 res = 0U;
  uint64 d = 1U;
  uint32 high = (uint32)(rem >> 32U);
  uint32 aux = 0U;


  /* defensive programming */
  /* CHECK: NOPARSE */
  if ((high >= base) && (base != 0U))
  {
    high /= base;
    res = (uint64) high << 32U;
    aux = (high*base);
    rem -= (uint64) aux << 32U;
  }
  /* CHECK: PARSE */

  while (((sint64)b > (sint64)0) && (b < rem))
  {
    b = b+b;
    d = d+d;
  }

  do
  {
    if (rem >= b)
    {
      rem -= b;
      res += d;
    }
    b >>= 1U;
    d >>= 1U;
  } while (d != 0U);


  return res;
}

STATIC FUNC(uint32, STBM_CODE) StbM_Mul_Q
(
  uint32 a,
  uint32 b
)
{
  uint32 hi, lo;
  uint32 result;


  StbM_Umul32_Wide (a, b, &hi, &lo);

  /* Q4.28 is scaled by 2**28, trim out scale factor */
  result = (uint32)(((uint32)hi << STBM_Q_INTEGRAL) | ((uint32)lo >> STBM_Q_FRACTION));


  return result;
}

STATIC FUNC(uint32, STBM_CODE) StbM_Timestamp_To_Q
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
)
{
  uint64 q_timestamp = 0U;
  uint64 q_nanoseconds = 0U;
  uint32 q_seconds = 0U;


  /* convert seconds to Q */
  q_seconds = STBM_UINT32_TO_Q(timeStampPtr->seconds);

  /* convert nanoseconds to Q */
  q_nanoseconds = STBM_UINT64_TO_Q(timeStampPtr->nanoseconds);
  q_nanoseconds = STBM_NSECS_TO_SECS(q_nanoseconds);

  /* calculate the whole timestamp to Q */
  q_timestamp = q_seconds + q_nanoseconds;


  return (uint32)q_timestamp;
}

STATIC FUNC(void, STBM_CODE) StbM_Q_To_Timestamp
(
  uint32 q_timestamp,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampPtr
)
{
  uint64 temp = 0U;
  uint32 q_nanoseconds = 0U;


  /* extract seconds part */
  timeStampPtr->seconds = STBM_Q_TO_UINT32(q_timestamp);

  q_nanoseconds = q_timestamp - (timeStampPtr->seconds * STBM_FACTOR_Q);
  /* extract nanoseconds part */
  temp = STBM_SECS_TO_NSECS(q_nanoseconds);
  timeStampPtr->nanoseconds = (uint32)(STBM_Q_TO_UINT64(temp));

}

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_ResetOffsetCorrectionValues
(
  uint8 rcDataIndex
)
{

  StbM_SlaveRateCorrectionData[rcDataIndex].beforeAdaptionInterval = FALSE;

  StbM_SlaveRateCorrectionData[rcDataIndex].roc = 0U;

  StbM_SlaveRateCorrectionData[rcDataIndex].rocSign = STBM_SIGN_IS_POSITIVE;

}

STATIC FUNC(void, STBM_CODE)StbM_CalculateRateCorrection
(
  uint8 commonIndex,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rocPtr,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) ratePtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) operationSignPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) VirtualLocalTimeDiffPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
#if (STBM_RATE_CORRECTION_USED)
#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
  /* check if rate correction is calculated for a master timebase */
  boolean masterRateCorrectionDisabled = STBM_MASTER_RATE_CORRECTION_DISABLED(commonIndex);
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#endif /* #if (STBM_RATE_CORRECTION_USED) */
  uint8 rcDataIndex = 0U;
  uint32 rrc = 0U;
  StbM_TimeStampType coorInterval = {0U, 0U, 0U, 0U};

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
  /* !LINKSTO StbM.SWS_StbM_00424.Calculation,1 */
  /* check if rate correction shall be calculated for a master time base */
  if(masterRateCorrectionDisabled == FALSE)
  {
    /* get index for the StbM_MasterRateCorrectionData[] array */
    rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonIndex);
    rrc = StbM_MasterRateCorrectionData[rcDataIndex].rrc;
  }
  /* it shall be done for a slave */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  else
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  {
    /* get index for the StbM_SlaveRateCorrectionData[] array */
    rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);
    rrc = StbM_SlaveRateCorrectionData[rcDataIndex].rrc;
#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
    *rocPtr = StbM_SlaveRateCorrectionData[rcDataIndex].roc;
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */
  }
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

  if(STBM_OFFSET_CORRECTION_DISABLED(commonIndex) == FALSE)
    {
      /* check if Adaption interval was exceed */
      if(TRUE == StbM_SlaveRateCorrectionData[rcDataIndex].beforeAdaptionInterval)
      {
        /* load adaptation interval */
        coorInterval.nanoseconds = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionAdaptIntervalNs;
        coorInterval.seconds = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionAdaptIntervalSec;
        coorInterval.secondsHi = 0U;

        /* check to see if the threshold for the adaptation interval is exceeded
         * (from the last resync)*/
        /* also check if *rocPtr is 0, the time is calculated only with rrc */
        /* !LINKSTO StbM.SWS_StbM_00355,1 */
        /* !LINKSTO StbM.SWS_StbM_00353,1 */

        /* calculate local time with additional rate */
        /* !LINKSTO StbM.SWS_StbM_00356,1 */
        if(StbM_SlaveRateCorrectionData[rcDataIndex].rocSign == STBM_SIGN_IS_NEGATIVE)
        {
          if(rrc > *rocPtr)
          {
            /* ((TV - TVSync) * (rrc - *rocPtr) */
            *ratePtr = rrc - *rocPtr;
          }
          else
          {
            /* -((TV - TVSync) * (*rocPtr - rrc) */
            *ratePtr = *rocPtr - rrc;
            *operationSignPtr = STBM_SIGN_IS_NEGATIVE;
          }
        }
        else
        {
          *ratePtr = rrc + *rocPtr;
        }

        if(StbM_TimeStampIsGreaterEqual(&coorInterval, VirtualLocalTimeDiffPtr))
        {
          /* calculate with *ratePtr = rrc + *rocPtr */
        }
        else
        {
          /* rate adaptation interval has expired, update time tuple */
          /* !LINKSTO StbM.SWS_StbM_00433.UpdateMainTimeTuple.AfterOffsetCorrection,1 */
          /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTime.ReplaceMainTimeTuple.After.OffsetCorrection.ByRateAdaptionInterval,1 */
          /* !LINKSTO StbM.SWS_StbM_00436.StbM_GetCurrentTimeExtended.ReplaceMainTimeTuple.After.OffsetCorrection.ByRateAdaptionInterval,1 */
          /* !LINKSTO StbM.SWS_StbM_00436.StbM_BusGetCurrentTime.ReplaceMainTimeTuple.After.OffsetCorrection.ByRateAdaptionInterval,1 */
          StbM_CalculateNewTimeTuple(commonIndex, *operationSignPtr, *ratePtr, &coorInterval, currentTimeTupleGlobalPtr, currentTimeTupleVLTPtr);

          /* calculate with only rrc, reset Offset Correction */
          StbM_ResetOffsetCorrectionValues(rcDataIndex);

          *rocPtr = 0U;

          /* update the virtual local time difference, so that it is based on
             the new time tuple */
          StbM_SubtractVirtualLocalTimesToTimeStamp
          (
            localTimePtr,
            currentTimeTupleVLTPtr,
            VirtualLocalTimeDiffPtr
          );
        }
      }
      else
      {
        /* calculate rate correction normally */
        *ratePtr = rrc;
      }
    }
    else
    {
      /* calculate rate correction normally */
      *ratePtr = rrc;
    }
}/* StbM_CalculateRateCorrection */
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */


STATIC FUNC(void, STBM_CODE) StbM_GetMaxAllowedLimit
(
  uint8 rcDataIndex,
  boolean masterRateCorrectionDisabled,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) maxAllowedValuePtr
)
{

  /* check if this is a master time base */
  if(masterRateCorrectionDisabled == TRUE)
  {
    /* not a master time base, check for slave */
#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
    /* check if we need to calculate with roc or not */
    if(TRUE == StbM_SlaveRateCorrectionData[rcDataIndex].beforeAdaptionInterval)
    {
      /* if yes, limit is 5s */
      /* !LINKSTO StbM.EB.TimeCalculationWithRateLimit.SlaveTimeBase.WithOffsetCorrection,1 */
      maxAllowedValuePtr->seconds = 5U;
    }
    else
#else
    TS_PARAM_UNUSED(rcDataIndex);
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */
    {
      /* if no, limit is 15s */
      /* !LINKSTO StbM.EB.TimeCalculationWithRateLimit.SlaveTimeBase.NoOffsetCorrection,1 */
      maxAllowedValuePtr->seconds = 15U;
    }
  }
  else
  {
    /* if yes, limit is 15s */
    /* !LINKSTO StbM.EB.TimeCalculationWithRateLimit.MasterTimeBase,1 */
    maxAllowedValuePtr->seconds = 15U;
  }

}


STATIC FUNC(void, STBM_CODE) StbM_CalculateLocalTimeWithRate
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) timeStampLocalTimePtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) localTimePtr
)
{
  /* check for time bases that have rate correction activated but do not have
   * offset correction activated */
  StbM_TimeStampType virtualLocalTimeDiff = {0U, 0U, 0U, 0U};
  StbM_TimeStampType productTimeStamp = {0U, 0U, 0U, 0U};
  StbM_TimeStampType maxAllowedValue = {0U, 0U, 0U, 0U};

  uint8 rcDataIndex = 0U;

#if (STBM_RATE_CORRECTION_USED)
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
  /* check if rate correction is calculated for a master timebase */
  boolean masterRateCorrectionDisabled = STBM_MASTER_RATE_CORRECTION_DISABLED(commonIndex);
#else
  boolean masterRateCorrectionDisabled = TRUE;
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#endif /* #if (STBM_RATE_CORRECTION_USED) */
#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
  uint8 operationSign = STBM_SIGN_IS_POSITIVE;
  uint32 roc = 0U;
#else
  uint32 rrc = 0U;
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */
  uint32 virtualLocalTimeDiff_Q = 0U;
  uint32 rate = 0U;
  uint32 product_Q = 0U;


  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(timeStampLocalTimePtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentTimeTupleGlobalPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(currentTimeTupleVLTPtr != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(localTimePtr != NULL_PTR,DET_INTERNAL_API_ID);

  /* calculate the local time as: TL = TG + (TV - TVSync) * rrc */

  /* enter critical section */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
  /* !LINKSTO StbM.SWS_StbM_00424.Calculation,1 */
  /* check if rate correction shall be calculated for a master time base */
  if(masterRateCorrectionDisabled == FALSE)
  {
    /* get index for the StbM_MasterRateCorrectionData[] array */
    rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(commonIndex);
#if (STBM_OFFSET_CORRECTION_USED == STD_OFF)
    rrc = StbM_MasterRateCorrectionData[rcDataIndex].rrc;
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_OFF) */
  }
  /* it shall be done for a slave */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  else
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  {
    /* get index for the StbM_SlaveRateCorrectionData[] array */
    rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);
#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
    roc = StbM_SlaveRateCorrectionData[rcDataIndex].roc;
#else
    rrc = StbM_SlaveRateCorrectionData[rcDataIndex].rrc;
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */
  }
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

  /* calculate how much time has passed from the last resync (TV-TVsync) */
  /* don't expect return, since the current Virtual time should be ahead of the past one */
  StbM_SubtractVirtualLocalTimesToTimeStamp
  (
    localTimePtr,
    currentTimeTupleVLTPtr,
    &virtualLocalTimeDiff
  );

  /* obtain the limit for witch the calculation can be made */
  StbM_GetMaxAllowedLimit(rcDataIndex, masterRateCorrectionDisabled, &maxAllowedValue);

  /* check if allowed calculation bound is correct */
  if(FALSE == StbM_TimeStampIsGreaterEqual(&virtualLocalTimeDiff, &maxAllowedValue))
  {

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
    StbM_CalculateRateCorrection
    (
      commonIndex,
      &roc,
      &rate,
      &operationSign,
      &virtualLocalTimeDiff,
      currentTimeTupleGlobalPtr,
      currentTimeTupleVLTPtr,
      localTimePtr
    );
#else

    /* calculate rate correction normally */
    rate = rrc;

#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */

    /* convert the virtualLocalTimeDiff to Q */
    virtualLocalTimeDiff_Q = StbM_Timestamp_To_Q(&virtualLocalTimeDiff);
    /* !LINKSTO StbM.SWS_StbM_00355,1 */
    /* calculate the multiplication: ((TV - TVSync) * rrc) or ((TV - TVSync) * (rrc + roc) )*/
    product_Q = StbM_Mul_Q(virtualLocalTimeDiff_Q, rate);
    StbM_Q_To_Timestamp(product_Q, &productTimeStamp);
  }
  else
  {
    /* use the virtual time difference without applying the rate, since
       it will be outside bounds */
    STBM_ASSIGN_TIMESTAMP(productTimeStamp, virtualLocalTimeDiff);
  }

  /* enter critical section */
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
  if(roc != 0U)
  {
    if(operationSign == STBM_SIGN_IS_POSITIVE)
    {
      /* don't consider retval(overflow of the global time could happen in thousands of years) */
      /* calculate the local time and assign it (TL = TG + product) */
     (void)StbM_SumTimeStamps
      (
        currentTimeTupleGlobalPtr,
        &productTimeStamp,
        timeStampLocalTimePtr
      );
    }
    else
    {
      /* don't consider retval(globalTime shall always be larger) */
      /* calculate the local time and assign it (TL = TG - product) */
     (void)StbM_SubtractTimeStamps
      (
        currentTimeTupleGlobalPtr,
        &productTimeStamp,
        timeStampLocalTimePtr
      );
    }
  }
  else
  {
    /* don't consider retval(overflow of the global time could happen in thousands of years) */
    /* calculate the local time and assign it (TL = TG(TO for offset) + product) */
    (void)StbM_SumTimeStamps
    (
      currentTimeTupleGlobalPtr,
      &productTimeStamp,
      timeStampLocalTimePtr
    );
  }
#else
  /* don't consider retval(overflow of the global time could happen in thousands of years) */
  /* calculate the local time and assign it (TL = TG + product) */
 (void)StbM_SumTimeStamps
  (
    currentTimeTupleGlobalPtr,
    &productTimeStamp,
    timeStampLocalTimePtr
  );
#endif /* #if (STBM_OFFSET_CORRECTION_USED == STD_ON) */

}
#endif /* (STBM_RATE_CORRECTION_USED) */

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_CalculateNewTimeTuple
(
  uint8 commonIndex,
  uint8 operationSign,
  uint32 rate,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) adaptationIntervalPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeTupleGlobalPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_VAR) currentTimeTupleVLTPtr
)
{
  uint32 adaptationInterval_Q = 0U;
  uint32 product_Q = 0U;
  StbM_TimeStampType productTimeStamp = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType adaptationIntervalVirtual = {0U, 0U};

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
      uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIndex);
      uint16 timeBaseStartIndex = 0U;
      uint8 rcDataIndex = 0U;
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


  /* convert the adaptation interval to Q */
  adaptationInterval_Q = StbM_Timestamp_To_Q(adaptationIntervalPtr);

  /* calculate AdaptationInterval * (rate) */
  product_Q = StbM_Mul_Q(adaptationInterval_Q, rate);
  StbM_Q_To_Timestamp(product_Q, &productTimeStamp);

  /* copy value of adaption interval from config */
  adaptationIntervalVirtual.nanosecondsLo = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionAdaptIntervalNsLo;
  adaptationIntervalVirtual.nanosecondsHi = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionAdaptIntervalNsHi;

  /* don't consider retval (overflow of the virtual local time could happen in thousands of years) */
  /* calculate TVtemp, and update Virtual Local Time part of Time Tuple */
  (void)StbM_SumVirtualLocalTimes
  (
    currentTimeTupleVLTPtr,
    &adaptationIntervalVirtual,
    currentTimeTupleVLTPtr
  );

  /* calculate TLtemp and update Time Tuple */
  if(operationSign == STBM_SIGN_IS_POSITIVE)
  {
    /* calculate TLtemp, and update Global Time part of Time Tuple */
    (void)StbM_SumTimeStamps
    (
      currentTimeTupleGlobalPtr,
      &productTimeStamp,
      currentTimeTupleGlobalPtr
    );
  }
  else
  {
    /* calculate TLtemp, and update Global Time part of Time Tuple */
    (void)StbM_SubtractTimeStamps
    (
      currentTimeTupleGlobalPtr,
      &productTimeStamp,
      currentTimeTupleGlobalPtr
    );
  }

  STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[commonIndex].globalTime, *currentTimeTupleGlobalPtr);

  STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[commonIndex].virtualLocalTime, *currentTimeTupleVLTPtr);

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
  /* set EV_RESYNC notification event after rate adaptation interval has expired and time has been updated */
  /* !LINKSTO StbM.SWS_StbM_00284.EV_RESYNC,1 */
  STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_RESYNC);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */


#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)
#if (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON)
  /* check if time base needs to share data to memory */
    if ((sharedMemoryIndex != STBM_TIME_BASE_DOES_NOT_USE_SHARED_DATA) && (StbM_CommonTimeBaseCfg[commonIndex].timeBaseRoleSharedData == STBM_TIME_BASE_PROVIDER_SHARED_DATA))
    {
        /* get array start index for this timebase */
        timeBaseStartIndex = (uint16)(STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (sharedMemoryIndex * STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE));
        /* get index for the StbM_SlaveRateCorrectionData[] array */
        rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteBegin,1 */
        /* increment the 'begin' counter, this will signal the user that
           data is currently being written */
        Atomics_ThreadFence();
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_BEGINCOUNTER_STARTINDEX]++;
        Atomics_ThreadFence();

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.When.StbM_CalculateNewTimeTuple,1 */
        /* update time tuple */
        StbM_UpdateTimeTupleInSharedMemory(commonIndex, timeBaseStartIndex);
        /* update rate correction and rate deviation */
        StbM_UpdateRateDevAndRateCorrInSharedMemory(&StbM_SlaveRateCorrectionData[rcDataIndex].rrc, &StbM_SlaveRateCorrectionData[rcDataIndex].rateDev, timeBaseStartIndex);

        /* !LINKSTO StbM.EB.SharedMemorySupport_V2.TimeProvider.UpdateSharedVariable.CurrentTimeBaseData.WriteEnd,1 */
        /* increment the 'end' counter, this will signal the user that
           data has been written */
        Atomics_ThreadFence();
        StbM_SharedData[timeBaseStartIndex + STBM_SHAREDDATA_ENDCOUNTER_STARTINDEX]++;
        Atomics_ThreadFence();
    }
#endif /* (STBM_SHAREDDATA_PROVIDER_TIMEBASES_USED == STD_ON) */
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */


}
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */

#if (STBM_OFFSET_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_PerformOffsetCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentGlobalTimePtr,
  P2VAR(boolean, AUTOMATIC, STBM_VAR) performJumpPtr
)
{

  StbM_TimeStampType timeStampA = {0U, 0U, 0U, 0U};
  StbM_TimeStampType timeStampB = {0U, 0U, 0U, 0U};
  StbM_TimeStampType currentTimeOffset = {0U, 0U, 0U, 0U};
  StbM_TimeStampType offsetJumpThreshold = {0U, 0U, 0U, 0U};
   /* get the underlying synchronized time base (timeBaseId might be an offset Id) */
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* get index for the StbM_SlaveRateCorrectionData[] array */
  uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TO_COMMON_TIMEBASE_INDEX(timeBaseId);


  /* When the function StbM_BusSetGlobalTime() is initially called, offset correction
   * shall not be performed.
   * In this case the timeBaseStatus of the synchronized slave time base is not set.
   * The timeBaseStatus gets updated at the end of StbM_BusSetGlobalTime() after time
   * offset correction is performed. */
  /* !LINKSTO StbM.SWS_StbM_00359,1 */
  if (STBM_FLAG_IS_SET(StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus,
                       STBM_GLOBAL_TIME_BASE_FLAG
                      )
     )
  {

    /* !LINKSTO StbM.SWS_StbM_00359,1 */
    /* !LINKSTO StbM.SWS_StbM_00440,1 */
    /* !LINKSTO StbM.SWS_StbM_00441,1 */
    /* calculate the difference between the global time and the local time, abs(TG-TLsync) */
    if(StbM_TimeStampIsGreaterEqual(currentGlobalTimePtr, currentTimeBaseTimePtr))
    {
      STBM_ASSIGN_TIMESTAMP(timeStampA, *currentGlobalTimePtr);
      STBM_ASSIGN_TIMESTAMP(timeStampB, *currentTimeBaseTimePtr);
      /* store sign for the roc calculation */
      StbM_SlaveRateCorrectionData[rcDataIndex].rocSign = STBM_SIGN_IS_POSITIVE;
    }
    else
    {
      STBM_ASSIGN_TIMESTAMP(timeStampB, *currentGlobalTimePtr);
      STBM_ASSIGN_TIMESTAMP(timeStampA, *currentTimeBaseTimePtr);
      /* store sign for the roc calculation */
      StbM_SlaveRateCorrectionData[rcDataIndex].rocSign = STBM_SIGN_IS_NEGATIVE;
    }

    /* cast to void because we know that the first time stamp is greater */
    (void)StbM_SubtractTimeStamps
    (
      &timeStampA,
      &timeStampB,
      &currentTimeOffset
    );

    /* obtain config data */
    offsetJumpThreshold.nanoseconds = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionJumpThresholdNs;
    offsetJumpThreshold.seconds = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionJumpThresholdSec;
    offsetJumpThreshold.secondsHi = 0U;

    /* !LINKSTO StbM.SWS_StbM_00355,1 */
    /* !LINKSTO StbM.SWS_StbM_00353,1 */
    /* check to see if the threshold is exceeded */
    if(FALSE == StbM_TimeStampIsGreaterEqual(&currentTimeOffset, &offsetJumpThreshold))
    {
      StbM_TimeStampType coorInterval = {0U, 0U, 0U, 0U};
      uint32 currentTimeOffsetQ = 0U;
      uint32 coorIntervalQ = 0U;
      uint32 q_roc = 0U;

      /* obtain the StbMOffsetCorrectionAdaptionInterval from config */
      coorInterval.nanoseconds = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionAdaptIntervalNs;
      coorInterval.seconds = StbM_CommonTimeBaseCfg[commonIndex].offsetCorrectionAdaptIntervalSec;
      coorInterval.secondsHi = 0U;

      /* threshold is not exceeded, local time shall be calculated with an additional rate,
       * besides rate correction */

      /* calculate additional rate ( roc = (TG - TLSync)/Tcorrint ) */
      /* convert timestamps to Q format */
      currentTimeOffsetQ = StbM_Timestamp_To_Q(&currentTimeOffset);
      coorIntervalQ = StbM_Timestamp_To_Q(&coorInterval);
      /* perform division between the two timestamps and store roc in Q format */
      q_roc = StbM_Div_Q(currentTimeOffsetQ, coorIntervalQ);

      /* store calculated value */
      StbM_SlaveRateCorrectionData[rcDataIndex].roc = q_roc;

      /* we are before adaption interval is exceeded */
      StbM_SlaveRateCorrectionData[rcDataIndex].beforeAdaptionInterval = TRUE;
    }
    else
    {
      /* threshold is exceeded, local time shall be calculated only with rate correction */
      StbM_ResetOffsetCorrectionValues(rcDataIndex);
      /* a jump to the received time shall be done */
      *performJumpPtr = TRUE;
    }
  }
  else
  {
  /* threshold is exceeded, local time shall be calculated only with rate correction */
    StbM_ResetOffsetCorrectionValues(rcDataIndex);
    /* a jump to the received time shall be done */
    *performJumpPtr = TRUE;
  }


}
#endif /* (STBM_OFFSET_CORRECTION_USED == STD_ON) */

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_PerformSlaveRateCorrection
(
  StbM_SynchronizedTimeBaseType timeBaseId
)
{
  uint8 startValuesIndex = 0U;
  uint8 stopValuesIndex = 0U;
  uint8 intervalCounter = 0U;
  boolean extendDiscard = FALSE;
  boolean rateIntervalOverlapped = FALSE;

  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  /* get index for the StbM_SlaveRateCorrectionData[] array */
  uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);


  startValuesIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexRcIntervals;
  stopValuesIndex = StbM_CommonTimeBaseCfg[commonIndex].stopIndexRcIntervals;

  /* !LINKSTO StbM.SWS_StbM_00368,1 */
  /* !LINKSTO StbM.SWS_StbM_00367.ParalellMeasurements,1 */
  intervalCounter = StbM_SlaveRateCorrectionData[rcDataIndex].intervalCounter;

  extendDiscard = StbM_CheckFlagChanges(rcDataIndex);

  /* !LINKSTO StbM.SWS_StbM_00367.MeasurementOverlap,1 */
  rateIntervalOverlapped = StbM_ValidateRateCorrectionInterval(commonIndex, rcDataIndex, intervalCounter);

  StbM_CheckIfMeasurementRestartIsNeeded(rcDataIndex, startValuesIndex, stopValuesIndex, extendDiscard, rateIntervalOverlapped);

  /* !LINKSTO StbM.SWS_StbM_00371.Sync,1 */
  /* !LINKSTO StbM.SWS_StbM_00371.Offset,1 */
  /* !LINKSTO StbM.SWS_StbM_00370,1 */
  if(StbM_CheckIntervalTiming(timeBaseId, intervalCounter) == TRUE)
  {

    if(StbM_SlaveRateCorrectionData[rcDataIndex].discardMeasurementCounter == 0U)
    {
      /* Calculate slave rate correction */
      StbM_CalculateSlaveRateCorrection(rcDataIndex, commonIndex);
    }
    else
    {
      /* !LINKSTO StbM.SWS_StbM_00412.SlaveRateCorrection.Sync,1 */
      /* !LINKSTO StbM.SWS_StbM_00412.SlaveRateCorrection.Offset,1 */
      /* No Rate Correction calculated */
      StbM_SlaveRateCorrectionData[rcDataIndex].discardMeasurementCounter--;
    }

    /* !LINKSTO StbM.SWS_StbM_00364,1 */
    /* store values for next Rate Correction calculation */
    STBM_ASSIGN_TIMESTAMP(StbM_SlaveRateCorrectionStartValues[intervalCounter].startGlobalTime, StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.globalTime);

    /* !LINKSTO StbM.SWS_StbM_00366,1 */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_SlaveRateCorrectionStartValues[intervalCounter].startVirtualLocalTime, StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.virtualLocalTime);

    /* !LINKSTO StbM.SWS_StbM_00368,1 */
    /* !LINKSTO StbM.SWS_StbM_00367.ParalellMeasurements,1 */
    if(intervalCounter == stopValuesIndex)
    {
      StbM_SlaveRateCorrectionData[rcDataIndex].intervalCounter = startValuesIndex;
    }
    else
    {
      StbM_SlaveRateCorrectionData[rcDataIndex].intervalCounter++;
    }
  }
  {
    /* No Rate Correction performed at this time */
  }


}



STATIC FUNC(void, STBM_CODE) StbM_CalculateSlaveRateCorrection
(
  uint8 rcDataIndex,
  uint8 commonIndex
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_TimeStampType globalTimeDiff = {0U, 0U, 0U, 0U};
  StbM_TimeStampType virtualLocalTimeDiff = {0U, 0U, 0U, 0U};
  /* this is the max allowed difference for Q format calculations */
  StbM_TimeStampType maxAllowedValue = {0U, 999999999U, 15U, 0U};
  /* store current Global Time Value, or current Offset Value */
  StbM_TimeStampType tempTimeStamp = {0U, 0U, 0U, 0U};
  uint8 intervalCounter = 0U;

#if (((STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) && (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)) || (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_OFF))
  TS_PARAM_UNUSED(commonIndex);
#endif /* (((STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) && (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V2)) || (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_OFF)) */


  intervalCounter = StbM_SlaveRateCorrectionData[rcDataIndex].intervalCounter;

  /* !LINKSTO StbM.SWS_StbM_00366,1 */
  STBM_ASSIGN_TIMESTAMP(tempTimeStamp, StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.globalTime);

  /* perform difference between the start and stop Virtual Local Times */
  StbM_SubtractVirtualLocalTimesToTimeStamp
  (
    &StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.virtualLocalTime,
    &StbM_SlaveRateCorrectionStartValues[intervalCounter].startVirtualLocalTime,
    &virtualLocalTimeDiff
  );

  /* !LINKSTO StbM.EB.RateCorrectionCalcualtionLimit.VirtualLocalTime,1 */
  /* check that the difference fits the accepted interval */
  if(FALSE == StbM_TimeStampIsGreaterEqual(&virtualLocalTimeDiff, &maxAllowedValue))
  {

    /* perform the difference time calculation between the current received Global Time(stop)
     * and the stored (start) Global Time (or Global Time Offset for offset time bases) */
    /* this could return E_NOT_OK for offset time bases, or if the difference is not in the
       accepted interval */
    retval = StbM_SubtractTimeStamps
    (
      &tempTimeStamp,
      &StbM_SlaveRateCorrectionStartValues[intervalCounter].startGlobalTime,
      &globalTimeDiff
    );

    /* !LINKSTO StbM.SWS_StbM_00360,1 */
    /* !LINKSTO StbM.EB.RateCorrectionCalcualtionLimit.GlobalTime,1 */
    if((FALSE == StbM_TimeStampIsGreaterEqual(&globalTimeDiff, &maxAllowedValue)) && (retval == E_OK))
    {
      /* calculate rc = globalTimeDiff / virtualLocalTimeDiff */
      /* convert timestamps to Q format */
      uint32 globalTime = StbM_Timestamp_To_Q(&globalTimeDiff);
      uint32 virtualLocalTime = StbM_Timestamp_To_Q(&virtualLocalTimeDiff);
      /* perform division between the two timestamps and store rc in Q format */
      uint32 q_rc = StbM_Div_Q(globalTime, virtualLocalTime);
      /* calculate rate correction in ppm(still in Q format) */
      uint64 q_rc_ppm = STBM_UINT64_TO_PPM(q_rc);
      /* convert from Q to uint64 */
      uint64 rc_ppm_64 = STBM_Q_TO_UINT64(q_rc_ppm);
      /* should fit into uint32 */
      uint32 rc_ppm = (uint32) rc_ppm_64;
      /* convert if rate correction can be converted to a valid rate deviation(rrc-1) */
      uint32 rc_ppm_verified = STBM_RATE_DEVIATION_UNSIGNED(rc_ppm);
      /* check it the rate deviation is within limits */
      if(rc_ppm_verified <= STBM_RATE_DEVIATION_MAX_VALUE)
      {

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
        uint16 sharedMemoryIndex = STBM_GET_SHARED_MEMORY_INDEX(commonIndex);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

        /* store the signed calculation */
        /* Deviation MISRAC2012-1 */
        StbM_SlaveRateCorrectionData[rcDataIndex].rateDev = (StbM_RateDeviationType)(rc_ppm - STBM_FACTOR_PPM);
        /* !LINKSTO StbM.SWS_StbM_00361,1 */
        /* !LINKSTO StbM.SWS_StbM_00362,1 */
        /* store calculated value for rate correction */
        StbM_SlaveRateCorrectionData[rcDataIndex].rrc = q_rc;

#if (STBM_STATUS_NOTIFICATIONS_USED == STD_ON)
        /* set EV_RATECORRECTION notification event after Slave Rate Correction was calculated and it value was not beyond limits */
        /* !LINKSTO StbM.SWS_StbM_00284.EV_RATECORRECTION.Master,1 */
        STBM_FLAG_SET(StbM_TimeBaseNotificationEvents[commonIndex], STBM_EV_RATECORRECTION);
#endif /* STBM_STATUS_NOTIFICATIONS_USED == STD_ON */

#if (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON)
#if (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1)
      StbM_UpdateSharedRateDeviationInMemory(sharedMemoryIndex, rcDataIndex);
#endif /* (STBM_SHARED_DATA_VERSION == STBM_SHARED_DATA_V1) */
#endif /* (STBM_TIME_BASES_THAT_SHARE_DATA_USED == STD_ON) */

      }
      else
      {
        /* No Rate Correction calculated */
        /* !LINKSTO StbM.SWS_StbM_00362,1 */
      }
    }
    /* set rate correction to default values */
    else
    {
      /* !LINKSTO StbM.SWS_StbM_00412.SlaveRateCorrection.Sync,1 */
      /* !LINKSTO StbM.SWS_StbM_00412.SlaveRateCorrection.Offset,1 */
      /* !LINKSTO StbM.SWS_StbM_00362,1 */
      /* No Rate Correction calculated */
    }
  }
  else
  {
    /* !LINKSTO StbM.SWS_StbM_00362,1 */
    /* No Rate Correction calculated */
  }

}

STATIC FUNC(void, STBM_CODE) StbM_CheckIfMeasurementRestartIsNeeded
(
  uint8 rcDataIndex,
  uint8 startValuesIndex,
  uint8 stopValuesIndex,
  boolean extendDiscard,
  boolean rateIntervalOverlapped
)
{

  if((extendDiscard == TRUE) || (rateIntervalOverlapped == TRUE))
  {
    StbM_SlaveRateCorrectionData[rcDataIndex].discardMeasurementCounter = (stopValuesIndex - startValuesIndex) + 1U;
  }

}

STATIC FUNC(boolean, STBM_CODE) StbM_ValidateRateCorrectionInterval
(
  uint8 commonIndex,
  uint8 rcDataIndex,
  uint8 intervalCounter
)
{
  boolean rateIntervalOverlapped = FALSE;
  StbM_TimeStampType intervalTimeDiff = {0U, 0U, 0U, 0U};
  StbM_TimeStampType doubleTheRateCorrectionInterval = {0U, 0U, 0U, 0U};


  doubleTheRateCorrectionInterval.nanoseconds = StbM_CommonTimeBaseCfg[commonIndex].doubleTheRateCorrectionIntervalNs;
  doubleTheRateCorrectionInterval.seconds = StbM_CommonTimeBaseCfg[commonIndex].doubleTheRateCorrectionIntervalSec;

  if(!STBM_VIRTUAL_LOCAL_TIME_IS_ZERO(StbM_SlaveRateCorrectionStartValues[intervalCounter].startVirtualLocalTime))
  {
    /* perform the difference time calculation between the current Virtual Local Time(stop)
       * and the stored (start) Virtual Local Time */
    StbM_SubtractVirtualLocalTimesToTimeStamp
    (
      &StbM_SlaveRateCorrectionData[rcDataIndex].newGlobalTimeData.virtualLocalTime,
      &StbM_SlaveRateCorrectionData[rcDataIndex].syncVirtualLocalTime,
      &intervalTimeDiff
    );

    /* check if the time interval that was configured has been exceeded */
    if (StbM_TimeStampIsGreaterEqual(&intervalTimeDiff, &doubleTheRateCorrectionInterval))
    {
      rateIntervalOverlapped = TRUE;
    }
  }


  return rateIntervalOverlapped;
}

STATIC FUNC(boolean, STBM_CODE) StbM_CheckFlagChanges
(
  uint8 rcDataIndex
)
{
  boolean extendDiscard = FALSE;
  uint8 allowedFlags = 0U;
  uint8 flags = StbM_SlaveRateCorrectionData[rcDataIndex].updatedFlags;


#if (STBM_TIMEOUTS_USED == STD_ON)
  /* check for TIMEOUT */
  if(STBM_FLAG_IS_SET(StbM_SlaveRateCorrectionData[rcDataIndex].initialFlags, STBM_TIMEOUT_FLAG))
  {
    STBM_FLAG_SET(flags, STBM_TIMEOUT_FLAG);
  }
#endif /* STBM_TIMEOUTS_USED == STD_ON */

  /* check if this is the first call to StbM_BusSetGlobalTime() */
  if((StbM_SlaveRateCorrectionData[rcDataIndex].initialFlags & STBM_GLOBAL_TIME_BASE_FLAG) == STBM_GLOBAL_TIME_BASE_FLAG)
  {
    allowedFlags = STBM_GLOBAL_TIME_BASE_FLAG | StbM_SlaveRateCorrectionData[rcDataIndex].syncToGateway;
  }
  else
  {
    /* first SYNC_TO_GATEWAY bit will be accepted and the one used from now on for comparison */
    allowedFlags = STBM_GLOBAL_TIME_BASE_FLAG | (flags & STBM_SYNC_TO_GATEWAY_MASK);
  }

  /* !LINKSTO StbM.SWS_StbM_00376,1 */
  /* !LINKSTO StbM.SWS_StbM_00375,1 */
  /* !LINKSTO StbM.SWS_StbM_00374,1 */
  /* !LINKSTO StbM.SWS_StbM_00373,1 */
  if(flags != allowedFlags)
  {
    extendDiscard = TRUE;

    /* re-store the syncToGateway flag */
    if(STBM_FLAG_IS_SET(flags, STBM_SYNC_TO_GATEWAY_FLAG))
    {
      StbM_SlaveRateCorrectionData[rcDataIndex].syncToGateway = STBM_SYNC_TO_GATEWAY_FLAG;
    }
    else
    {
      StbM_SlaveRateCorrectionData[rcDataIndex].syncToGateway = 0U;
    }

  }


  return extendDiscard;
}
#endif /* (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_TIMELEAP_DETECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_HandleTimeLeapCounter
(
  P2VAR(uint16, AUTOMATIC, STBM_VAR) timeLeapCounterPtr,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  uint8 timeLeapFlag
)
{

  if (*timeLeapCounterPtr > 0U)
  {
    /* !LINKSTO StbM.ECUC_StbM_00037_Conf,1 */
    /* Decrement the clear time leap counter */
    (*timeLeapCounterPtr)--;
  }

  if (*timeLeapCounterPtr == 0U)
  {
    /* !LINKSTO StbM.SWS_StbM_00182.CLEAR_TIMELEAP_FUTURE_BIT,1 */
    /* !LINKSTO StbM.SWS_StbM_00305.CLEAR_TIMELEAP_PAST_BIT,1 */
    /* Clear the time leap bits after the clear time leap counter has expired */
    STBM_FLAG_DELETE(*flagsOutPtr, timeLeapFlag);
  }

}
#endif /* STBM_TIMELEAP_DETECTION_USED == STD_ON */

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
STATIC FUNC(void, STBM_CODE) StbM_PerformTimeRecording
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(uint8, AUTOMATIC, STBM_VAR) flagsOutPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentGlobalTimePtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_VAR) currentTimeBaseTimePtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr
)
{
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  uint32 blockStartIndex = 0U;
  uint32 blockEndIndex = 0U;
  uint32 currentBlockIndex = 0U;
  uint16 numberOfBlocks = 0U;



  blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocks;
  numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocks;

  blockEndIndex = blockStartIndex + numberOfBlocks;

  currentBlockIndex = StbM_RecordTableBlocksInfo[commonIndex].counter;

#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) && (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
  /* fill time block */
  if(STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId))
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) && (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
  {
    /* !LINKSTO StbM.SWS_StbM_00388,1 */
    /* !LINKSTO StbM.SWS_StbM_00428,1 */
    StbM_OffsetRecordTableBlocks[currentBlockIndex].TimeBaseStatus = *flagsOutPtr;
    StbM_OffsetRecordTableBlocks[currentBlockIndex].GlbSeconds = currentGlobalTimePtr->seconds;
    StbM_OffsetRecordTableBlocks[currentBlockIndex].GlbNanoSeconds = currentGlobalTimePtr->nanoseconds;
  }
#endif /* STBM_OFFSET_TIME_RECORDING_USED == STD_ON */
#if ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) && (STBM_OFFSET_TIME_RECORDING_USED == STD_ON))
  else
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) && (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  {
    /* !LINKSTO StbM.SWS_StbM_00428,1 */
    /* !LINKSTO StbM.SWS_StbM_00314,1 */
    StbM_SyncRecordTableBlocks[currentBlockIndex].TimeBaseStatus = *flagsOutPtr;
    StbM_SyncRecordTableBlocks[currentBlockIndex].GlbSeconds = currentGlobalTimePtr->seconds;
    StbM_SyncRecordTableBlocks[currentBlockIndex].GlbNanoSeconds = currentGlobalTimePtr->nanoseconds;
    StbM_SyncRecordTableBlocks[currentBlockIndex].VirtualLocalTimeLow = localTimePtr->nanosecondsLo;
    /* !LINKSTO StbM.SWS_StbM_00313,1 */
    StbM_SyncRecordTableBlocks[currentBlockIndex].LocSeconds = currentTimeBaseTimePtr->seconds;
    StbM_SyncRecordTableBlocks[currentBlockIndex].LocNanoSeconds = currentTimeBaseTimePtr->nanoseconds;
    StbM_SyncRecordTableBlocks[currentBlockIndex].PathDelay = measureDataPtr->pathDelay;
  }
#else /* STBM_SYNC_TIME_RECORDING_USED == STD_OFF */
  TS_PARAM_UNUSED(currentTimeBaseTimePtr);
  TS_PARAM_UNUSED(measureDataPtr);
  TS_PARAM_UNUSED(localTimePtr);
#endif /* STBM_SYNC_TIME_RECORDING_USED == STD_ON */

  /* increase counter */
  ++StbM_RecordTableBlocksInfo[commonIndex].counter;

  /* check if all blocks have been filled for this time base */
  if (StbM_RecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
  {
    /* let the MainFunction know that block counter was wrapped */
    StbM_RecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

    /* wraparound the counter */
    StbM_RecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
  }

}
#endif /* ((STBM_SYNC_TIME_RECORDING_USED == STD_ON) || (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)) */


#if ((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) && (STBM_SYNC_TIME_RECORDING_USED == STD_ON))
STATIC FUNC(uint32, STBM_CODE) StbM_FindCurrentBlockIndex
(
  uint8 commonIndex
)
{
  uint16 numberOfBlocks = 0U;
  uint32 blockStartIndex = 0U;
  uint32 blockEndIndex = 0U;
  uint32 currentBlockCounter = 0U;
  uint32 lclcurrentBlockIndex = 0U;


  blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocks;
  numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocks;
  blockEndIndex = blockStartIndex + numberOfBlocks;
  currentBlockCounter = StbM_RecordTableBlocksInfo[commonIndex].counter;

  /* the TimeBase is the first one in the list of TimeBases which support TimeRecording
     and one recording block configured */
  if((blockStartIndex == 0U) && (numberOfBlocks == 1U))
  {
    lclcurrentBlockIndex = 0U;
  }
  else
  {
    /* counter was not reseted */
      if(currentBlockCounter != blockStartIndex)
      {
        /* decrease the current block index by 1, if it was not reseted */
        lclcurrentBlockIndex = (currentBlockCounter - 1U);
      }
      else
      {
        /* if counter was reseted, take the blockEndIndex-1 as current block index */
        lclcurrentBlockIndex = blockEndIndex - 1U;
      }
  }


  return lclcurrentBlockIndex;
}
#endif /* ((STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) && (STBM_SYNC_TIME_RECORDING_USED == STD_ON)) */



#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_HandleSlaveRateCorrection
(
  uint8 commonIndex
)
{
  uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);


  /* check if rate correction is activated for this time base, and we have new values */
  if((!STBM_SLAVE_RATE_CORRECTION_DISABLED(commonIndex)) && (StbM_SlaveRateCorrectionData[rcDataIndex].newValues == TRUE))
  {
    /* calculate and record rate correction, if it is the case
       and also set EV_RATECORRECTION event notification if a valid slave rate correction was calculated */
    /* !LINKSTO StbM.SWS_StbM_00284.EV_RATECORRECTION.Normal.SlaveRateCorrection,1 */
    StbM_CalculateAndRecordRateCorrection(commonIndex);
  }

}


STATIC FUNC(void, STBM_CODE) StbM_CalculateAndRecordRateCorrection
(
  uint8 commonIndex
)
{
#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  /* variable for the current block index*/
  uint32 currentBlockIndex = 0U;
  /* variable for the current time base status */
  uint8 currentTimeBaseStatus = 0U;
  /* variable to check if StbM_BusSetGlobalTime() was called */
  boolean isGlobalTimeBaseSet = FALSE;
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

  uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);
  uint8 currentTimeBaseId = 0U;


#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  /* get the current TimeBase Status only for SYNC time bases */
  if(commonIndex < STBM_NUMBER_OF_SYNC_TIMEBASES)
  {
    currentTimeBaseStatus = StbM_TimeStamps[commonIndex].globalTime.timeBaseStatus;
    /* check if GLOBAL_TIME_BASE bit was set for this SYNC time base */
    isGlobalTimeBaseSet = (STBM_FLAG_IS_SET(currentTimeBaseStatus, STBM_GLOBAL_TIME_BASE_FLAG));
  }

  /* find current block index */
  if((!STBM_TIME_RECORDING_DISABLED(commonIndex)) && (commonIndex < STBM_NUMBER_OF_SYNC_TIMEBASES) && (isGlobalTimeBaseSet == TRUE))
  {
    currentBlockIndex = StbM_FindCurrentBlockIndex(commonIndex);
  }
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

  StbM_SlaveRateCorrectionData[rcDataIndex].newValues = FALSE;

  /* Calculate timeBaseID from commonIdx */
  currentTimeBaseId = STBM_COMMON_INDEX_TO_TIMEBASEID(commonIndex);

  /* Calculate Slave Rate Correction */
  StbM_PerformSlaveRateCorrection(currentTimeBaseId);

#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
  /* SYNC TimeBaseId with TimeRecording active */
  if(!(STBM_TIME_RECORDING_DISABLED(commonIndex)) && (commonIndex < STBM_NUMBER_OF_SYNC_TIMEBASES) && (isGlobalTimeBaseSet == TRUE))
  {
    /* write RateDeviation value in StbM_SyncRecordTableBlocks[currentBlockIndex - 1U]
     * (currentBlockIndex was decreased by one, because it was increased before in StbM_PerformeTimeRecording()) */
    if(StbM_SlaveRateCorrectionData[rcDataIndex].rateDev == STBM_RATE_DEVIATION_INVALID_VALUE)
    {
      /* if rateDev has an invalid value => record 0 value for it, as SWS_StbM_00306 says (ASCSTBM-445) */
      StbM_SyncRecordTableBlocks[currentBlockIndex].RateDeviation = 0U;
    }
    else
    {
      /* if rateDev has an valid value => record it */
      StbM_SyncRecordTableBlocks[currentBlockIndex].RateDeviation = StbM_SlaveRateCorrectionData[rcDataIndex].rateDev;
    }
  }
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */

}
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */





#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00465,1 */

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00493.CAN.StbM_CanSetMasterTimingData,1 */
/* !LINKSTO StbM.SWS_StbM_00490,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_CanSetMasterTimingData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_CanTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_CanSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETMASTERTIMINGDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00494.TimeBaseId.StbM_CanSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETMASTERTIMINGDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00495.Null.MeasureDataPtr.StbM_CanSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETMASTERTIMINGDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_CanSetMasterTimingData for a SLAVE time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00494.SLAVETimeBaseId.StbM_CanSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETMASTERTIMINGDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_CANSETMASTERTIMINGDATA_ENTRY(timeBaseId, measureDataPtr);


    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.TimeMaster,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationMASTERPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00474.Master.NoNotification.OverwriteBlock.CAN,1 */
    currentBlockIndex = StbM_CanMasterTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00468.MasterPort.CAN,1 */
    /* !LINKSTO StbM.SWS_StbM_00469.Master.CanTSyn_Provider,1 */
    /* !LINKSTO StbM.SWS_StbM_00473.Copy.Master.MeasureDataPtr.ReceivedFrom.CAN.ToTable,1 */
    StbM_CanMasterTimingData[currentBlockIndex].sequenceCounter = measureDataPtr->sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_CanMasterTimingData[currentBlockIndex].syncEgressTimestamp, measureDataPtr->syncEgressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_CanMasterTimingData[currentBlockIndex].preciseOriginTimestamp, measureDataPtr->preciseOriginTimestamp);
    StbM_CanMasterTimingData[currentBlockIndex].segmentId = measureDataPtr->segmentId;

    /* increase block counter */
    ++StbM_CanMasterTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.Master.ValidationRecordTable,1 */
    if (StbM_CanMasterTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_CanMasterTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_CanSetMasterTimingData() is called */
      StbM_CanMasterTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }


    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }

  DBG_STBM_CANSETMASTERTIMINGDATA_EXIT(timeBaseId, measureDataPtr, retval);
  return retval;
}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */



#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00493.FR.StbM_FrSetMasterTimingData,1 */
/* !LINKSTO StbM.SWS_StbM_00491,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_FrSetMasterTimingData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_FrTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_FrSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETMASTERTIMINGDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00494.TimeBaseId.StbM_FrSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETMASTERTIMINGDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00495.Null.MeasureDataPtr.StbM_FrSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETMASTERTIMINGDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_FrSetMasterTimingData for a SLAVE time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00494.SLAVETimeBaseId.StbM_FrSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETMASTERTIMINGDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_FRSETMASTERTIMINGDATA_ENTRY(timeBaseId, measureDataPtr);

    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.TimeMaster,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationMASTERPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00474.Master.NoNotification.OverwriteBlock.FR,1 */
    currentBlockIndex = StbM_FrMasterTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00468.MasterPort.FR,1 */
    /* !LINKSTO StbM.SWS_StbM_00469.Master.FrTSyn_Provider,1 */
    /* !LINKSTO StbM.SWS_StbM_00473.Copy.Master.MeasureDataPtr.ReceivedFrom.FR.ToTable,1 */
    StbM_FrMasterTimingData[currentBlockIndex].sequenceCounter = measureDataPtr->sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_FrMasterTimingData[currentBlockIndex].referenceTimestamp, measureDataPtr->referenceTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_FrMasterTimingData[currentBlockIndex].preciseOriginTimestamp, measureDataPtr->preciseOriginTimestamp);
    StbM_FrMasterTimingData[currentBlockIndex].segmentId = measureDataPtr->segmentId;
    StbM_FrMasterTimingData[currentBlockIndex].currentCycle = measureDataPtr->currentCycle;
    StbM_FrMasterTimingData[currentBlockIndex].currentMacroticks = measureDataPtr->currentMacroticks;
    StbM_FrMasterTimingData[currentBlockIndex].macrotickDuration = measureDataPtr->macrotickDuration;
    StbM_FrMasterTimingData[currentBlockIndex].cycleLength = measureDataPtr->cycleLength;

    /* increase block counter */
    ++StbM_FrMasterTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.Master.ValidationRecordTable,1 */
    if (StbM_FrMasterTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_FrMasterTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_FrSetMasterTimingData() is called */
      StbM_FrMasterTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }


    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  }

  DBG_STBM_FRSETMASTERTIMINGDATA_EXIT(timeBaseId, measureDataPtr, retval);
  return retval;
}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */




#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00493.ETH,1 */
/* !LINKSTO StbM.SWS_StbM_00492,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetMasterTimingData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_EthTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_EthSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETMASTERTIMINGDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00494.TimeBaseId.StbM_EthSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETMASTERTIMINGDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00495.Null.MeasureDataPtr.StbM_EthSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETMASTERTIMINGDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_EthSetMasterTimingData for a SLAVE time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00494.SLAVETimeBaseId.StbM_EthSetMasterTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETMASTERTIMINGDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_ETHSETMASTERTIMINGDATA_ENTRY(timeBaseId, measureDataPtr);

    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.TimeMaster,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationMASTERPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00474.Master.NoNotification.OverwriteBlock.ETH,1 */
    currentBlockIndex = StbM_EthMasterTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00468.ETH.MappedToEthTSynTimeDomain,1 */
    /* !LINKSTO StbM.SWS_StbM_00469.Master.EthTSyn_Provider,1 */
    /* !LINKSTO StbM.SWS_StbM_00473.Copy.Master.MeasureDataPtr.ReceivedFrom.ETH.ToTable,1 */
    StbM_EthMasterTimingData[currentBlockIndex].sequenceId = measureDataPtr->sequenceId;
    STBM_ASSIGN_PORT_ID(StbM_EthMasterTimingData[currentBlockIndex].sourcePortId, measureDataPtr->sourcePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthMasterTimingData[currentBlockIndex].syncEgressTimestamp, measureDataPtr->syncEgressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthMasterTimingData[currentBlockIndex].preciseOriginTimestamp, measureDataPtr->preciseOriginTimestamp);
    StbM_EthMasterTimingData[currentBlockIndex].correctionField = measureDataPtr->correctionField;

    /* increase block counter */
    ++StbM_EthMasterTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.Master.ValidationRecordTable,1 */
    if (StbM_EthMasterTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_EthMasterTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_EthSetMasterTimingData() is called */
      StbM_EthMasterTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  }

  DBG_STBM_ETHSETMASTERTIMINGDATA_EXIT(timeBaseId, measureDataPtr, retval);
  return retval;
}



/* !LINKSTO StbM.SWS_StbM_00501,1 */
/* !LINKSTO StbM.SWS_StbM_00500,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetPdelayResponderData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_PdelayResponderMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_EthSetPdelayResponderData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYRESPONDERDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00502,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYRESPONDERDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00503,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYRESPONDERDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_EthSetPdelayResponderData for a SLAVE time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00494.SLAVETimeBaseId.StbM_EthSetPdelayResponderData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYRESPONDERDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_ETHSETPDELAYRESPONDERDATA_ENTRY(timeBaseId, measureDataPtr);

    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.PdelayResponder,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationMASTERPdelayPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00525,1 */
    currentBlockIndex = StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00523.MappedToEthTSynTimeDomain,1 */
    /* !LINKSTO StbM.SWS_StbM_00480,1 */
    StbM_EthPdelayResponderTimingData[currentBlockIndex].sequenceId = measureDataPtr->sequenceId;
    STBM_ASSIGN_PORT_ID(StbM_EthPdelayResponderTimingData[currentBlockIndex].requestPortId, measureDataPtr->requestPortId);
    STBM_ASSIGN_PORT_ID(StbM_EthPdelayResponderTimingData[currentBlockIndex].responsePortId, measureDataPtr->responsePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthPdelayResponderTimingData[currentBlockIndex].requestReceiptTimestamp, measureDataPtr->requestReceiptTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthPdelayResponderTimingData[currentBlockIndex].responseOriginTimestamp, measureDataPtr->responseOriginTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthPdelayResponderTimingData[currentBlockIndex].referenceLocalTimestamp, measureDataPtr->referenceLocalTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthPdelayResponderTimingData[currentBlockIndex].referenceGlobalTimestamp, measureDataPtr->referenceGlobalTimestamp);

    /* increase block counter */
    ++StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.PdelayResponder.ValidationRecordTable,1 */
    if (StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_EthSetPdelayResponderData() is called */
      StbM_EthPdelayResponderTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  }

  DBG_STBM_ETHSETPDELAYRESPONDERDATA_EXIT(timeBaseId, measureDataPtr, retval);
  return retval;
}
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */







#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00487.CAN.StbM_CanSetSlaveTimingData,1 */
/* !LINKSTO StbM.SWS_StbM_00484,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_CanSetSlaveTimingData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_CanTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_CanSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETSLAVETIMINGDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00488.TimeBaseId.StbM_CanSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETSLAVETIMINGDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00489.Null.MeasureDataPtr.StbM_CanSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETSLAVETIMINGDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_CanSetSlaveTimingData for a MASTER time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00488.MASTERTimeBaseId.StbM_CanSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_CANSETSLAVETIMINGDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_CANSETSLAVETIMINGDATA_ENTRY(timeBaseId, measureDataPtr);

    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.TimeSlave,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationSLAVEPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00472.Slave.NoNotification.OverwriteBlock.CAN,1 */
    currentBlockIndex = StbM_CanSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00466.SlavePort.CAN,1 */
    /* !LINKSTO StbM.SWS_StbM_00467.Slave.CanTSyn_Provider,1 */
    /* !LINKSTO StbM.SWS_StbM_00471.Copy.Slave.MeasureDataPtr.ReceivedFrom.CAN.ToTable,1 */
    StbM_CanSlaveTimingData[currentBlockIndex].sequenceCounter = measureDataPtr->sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_CanSlaveTimingData[currentBlockIndex].syncIngressTimestamp, measureDataPtr->syncIngressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_CanSlaveTimingData[currentBlockIndex].preciseOriginTimestamp, measureDataPtr->preciseOriginTimestamp);

    /* Set referenceLocalTimestamp and referenceGlobalTimestamp to the time tuple value received in the previous StbM_BusSetGlobalTime() function call */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_CanSlaveTimingData[currentBlockIndex].referenceLocalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationVirtualLocalTime);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_CanSlaveTimingData[currentBlockIndex].referenceGlobalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationGlobalTime);

    StbM_CanSlaveTimingData[currentBlockIndex].segmentId = measureDataPtr->segmentId;

    /* increase block counter */
    ++StbM_CanSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.Slave.ValidationRecordTable,1 */
    if (StbM_CanSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_CanSlaveTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_CanSetSlaveTimingData() is called */
      StbM_CanSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  }

  DBG_STBM_CANSETSLAVETIMINGDATA_EXIT(timeBaseId, measureDataPtr, retval);

  return retval;
}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00487.FR.StbM_FrSetSlaveTimingData,1 */
/* !LINKSTO StbM.SWS_StbM_00485,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_FrSetSlaveTimingData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_FrTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_FrSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETSLAVETIMINGDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00488.TimeBaseId.StbM_FrSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETSLAVETIMINGDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00489.Null.MeasureDataPtr.StbM_FrSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETSLAVETIMINGDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_FrSetSlaveTimingData for a MASTER time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00488.MASTERTimeBaseId.StbM_FrSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_FRSETSLAVETIMINGDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_FRSETSLAVETIMINGDATA_ENTRY(timeBaseId, measureDataPtr);


    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.TimeSlave,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationSLAVEPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00472.Slave.NoNotification.OverwriteBlock.FR,1 */
    currentBlockIndex = StbM_FrSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00466.SlavePort.FR,1 */
    /* !LINKSTO StbM.SWS_StbM_00467.Slave.FrTSyn_Provider,1 */
    /* !LINKSTO StbM.SWS_StbM_00471.Copy.Slave.MeasureDataPtr.ReceivedFrom.FR.ToTable,1 */
    StbM_FrSlaveTimingData[currentBlockIndex].sequenceCounter = measureDataPtr->sequenceCounter;
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_FrSlaveTimingData[currentBlockIndex].syncIngressTimestamp, measureDataPtr->syncIngressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_FrSlaveTimingData[currentBlockIndex].preciseOriginTimestampSec, measureDataPtr->preciseOriginTimestampSec);

    StbM_FrSlaveTimingData[currentBlockIndex].currentCycle = measureDataPtr->currentCycle;
    StbM_FrSlaveTimingData[currentBlockIndex].CurrentMacroticks = measureDataPtr->CurrentMacroticks;
    StbM_FrSlaveTimingData[currentBlockIndex].FCNT = measureDataPtr->FCNT;
    StbM_FrSlaveTimingData[currentBlockIndex].macrotickDuration = measureDataPtr->macrotickDuration;
    StbM_FrSlaveTimingData[currentBlockIndex].cycleLength = measureDataPtr->cycleLength;

    /* Set referenceLocalTimestamp and referenceGlobalTimestamp to the time tuple value received in the previous StbM_BusSetGlobalTime() function call */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_FrSlaveTimingData[currentBlockIndex].referenceLocalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationVirtualLocalTime);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_FrSlaveTimingData[currentBlockIndex].referenceGlobalTimestampSec, StbM_LastReceivedTimeTuple[commonIndex].timeValidationGlobalTime);

    StbM_FrSlaveTimingData[currentBlockIndex].segmentId = measureDataPtr->segmentId;


    /* increase block counter */
    ++StbM_FrSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.Slave.ValidationRecordTable,1 */
    if (StbM_FrSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_FrSlaveTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_FrSetSlaveTimingData() is called */
      StbM_FrSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }

  DBG_STBM_FRSETSLAVETIMINGDATA_EXIT(timeBaseId, measureDataPtr, retval);

  return retval;
}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
/* !LINKSTO StbM.SWS_StbM_00487.ETH,1 */
/* !LINKSTO StbM.SWS_StbM_00486,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetSlaveTimingData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_EthTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_EthSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETSLAVETIMINGDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00488.TimeBaseId.StbM_EthSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETSLAVETIMINGDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00489.Null.MeasureDataPtr.StbM_EthSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETSLAVETIMINGDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_EthSetSlaveTimingData for a MASTER time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00488.MASTERTimeBaseId.StbM_EthSetSlaveTimingData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETSLAVETIMINGDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_ETHSETSLAVETIMINGDATA_ENTRY(timeBaseId, measureDataPtr);

    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.TimeSlave,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationSLAVEPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00472.Slave.NoNotification.OverwriteBlock.ETH,1 */
    currentBlockIndex = StbM_EthSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00466.ETH.MappedToEthTSynTimeDomain,1 */
    /* !LINKSTO StbM.SWS_StbM_00467.Slave.EthTSyn_Provider,1 */
    /* !LINKSTO StbM.SWS_StbM_00471.Copy.Slave.MeasureDataPtr.ReceivedFrom.ETH.ToTable,1 */
    StbM_EthSlaveTimingData[currentBlockIndex].sequenceId = measureDataPtr->sequenceId;
    STBM_ASSIGN_PORT_ID(StbM_EthSlaveTimingData[currentBlockIndex].sourcePortId, measureDataPtr->sourcePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthSlaveTimingData[currentBlockIndex].syncIngressTimestamp, measureDataPtr->syncIngressTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthSlaveTimingData[currentBlockIndex].preciseOriginTimestamp, measureDataPtr->preciseOriginTimestamp);
    StbM_EthSlaveTimingData[currentBlockIndex].correctionField = measureDataPtr->correctionField;
    StbM_EthSlaveTimingData[currentBlockIndex].pDelay = measureDataPtr->pDelay;
    /* Set referenceLocalTimestamp and referenceGlobalTimestamp to the time tuple value received in the previous StbM_BusSetGlobalTime() function call */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthSlaveTimingData[currentBlockIndex].referenceLocalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationVirtualLocalTime);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthSlaveTimingData[currentBlockIndex].referenceGlobalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationGlobalTime);

    /* increase block counter */
    ++StbM_EthSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.Slave.ValidationRecordTable,1 */
    if (StbM_EthSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_EthSlaveTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_EthSetSlaveTimingData() is called */
      StbM_EthSlaveTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  }

  DBG_STBM_ETHSETSLAVETIMINGDATA_EXIT(timeBaseId, measureDataPtr, retval);

  return retval;
}



/* !LINKSTO StbM.SWS_StbM_00497,1 */
/* !LINKSTO StbM.SWS_StbM_00496,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetPdelayInitiatorData
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_PdelayInitiatorMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr
)
{
  Std_ReturnType retval = E_NOT_OK;

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    retval = E_NOT_OK;
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_EthSetPdelayInitiatorData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYINITIATORDATA, STBM_E_UNINIT);
  }
  else if (!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00498,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYINITIATORDATA, STBM_E_PARAM);
  }
  else if (measureDataPtr == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00499,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYINITIATORDATA, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_EthSetPdelayInitiatorData for a MASTER time base shall throw a DET error */
    /* !LINKSTO StbM.SWS_StbM_00498.MASTERTimeBaseId.StbM_EthSetPdelayInitiatorData,1 */
    STBM_DET_REPORTERROR(STBM_API_ETHSETPDELAYINITIATORDATA, STBM_E_PARAM);
  }
  else
#endif /* #if (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Deviation TASKING-2 */
    uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
    uint32 blockStartIndex = 0U;
    uint32 blockEndIndex = 0U;
    uint32 currentBlockIndex = 0U;
    uint16 numberOfBlocks = 0U;

    DBG_STBM_ETHSETPDELAYINITIATORDATA_ENTRY(timeBaseId, measureDataPtr);

    /* enter critical section */
    /* !LINKSTO StbM.SWS_StbM_00477.NoInterrupt.When.Overwritting.PdelayInitiator,1 */
    SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

    blockStartIndex = StbM_CommonTimeBaseCfg[commonIndex].startIndexTrBlocksTimeValidationSLAVEPdelayPart;
    numberOfBlocks = StbM_CommonTimeBaseCfg[commonIndex].numberOfBlocksTimeValidation;

    blockEndIndex = blockStartIndex + numberOfBlocks;

    /* set current block index */
    /* !LINKSTO StbM.SWS_StbM_00524,1 */
    currentBlockIndex = StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* !LINKSTO StbM.SWS_StbM_00522.MappedToEthTSynTimeDomain,1 */
    /* !LINKSTO StbM.SWS_StbM_00478,1 */
    StbM_EthPdelayInitiatorTimingData[currentBlockIndex].sequenceId = measureDataPtr->sequenceId;
    STBM_ASSIGN_PORT_ID(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].requestPortId, measureDataPtr->requestPortId);
    STBM_ASSIGN_PORT_ID(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].responsePortId, measureDataPtr->responsePortId);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].requestOriginTimestamp, measureDataPtr->requestOriginTimestamp);
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].responseReceiptTimestamp, measureDataPtr->responseReceiptTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].requestReceiptTimestamp, measureDataPtr->requestReceiptTimestamp);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].responseOriginTimestamp, measureDataPtr->responseOriginTimestamp);

    /* Set referenceLocalTimestamp and referenceGlobalTimestamp to the time tuple value received in the previous StbM_BusSetGlobalTime() function call */
    STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].referenceLocalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationVirtualLocalTime);
    STBM_ASSIGN_SHORTTIMESTAMP(StbM_EthPdelayInitiatorTimingData[currentBlockIndex].referenceGlobalTimestamp, StbM_LastReceivedTimeTuple[commonIndex].timeValidationGlobalTime);

    StbM_EthPdelayInitiatorTimingData[currentBlockIndex].pdelay = measureDataPtr->pdelay;

    /* increase block counter */
    ++StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[commonIndex].counter;

    /* check if block counter has reached the blockEndIndex */
    /* !LINKSTO StbM.SWS_StbM_00470.PdelayInitiator.ValidationRecordTable,1 */
    if (StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[commonIndex].counter == blockEndIndex)
    {
      /* let the MainFunction know that block counter was wrapped */
      StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[commonIndex].wasCounterWrapped = TRUE;

      /* wrapping counter will start from blockStartIndex position, when the next StbM_EthSetPdelayInitiatorData() is called */
      StbM_EthPdelayInitiatorTimingDataRecordTableBlocksInfo[commonIndex].counter = blockStartIndex;
    }

    retval = E_OK;

    /* leave critical section */
    SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  }

  DBG_STBM_ETHSETPDELAYINITIATORDATA_EXIT(timeBaseId, measureDataPtr, retval);

  return retval;
}
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */

#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */



#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)


STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_GetInsertionIndex
(
  P2VAR(uint32, AUTOMATIC, STBM_VAR) insertIdx
)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32 idx = 0U;


  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS; idx++)
  {
    if(StbM_ExpireTimeData[idx].Data.isArrayCellEmpty == TRUE)
    {
      retVal = E_OK;
      *insertIdx = idx;
      break;
    }
  }


  return retVal;
}


STATIC FUNC(uint32, STBM_CODE) StbM_GetListLength(void)
{
  uint32 listLength = 0U;
  StbM_CustomerTimerExpireTimeNodeDataType *lclCurrent;


  for(lclCurrent = Head; lclCurrent != NULL_PTR; lclCurrent = lclCurrent->next){
    listLength++;
  }


  return listLength;
}


STATIC FUNC(boolean, STBM_CODE) StbM_IsTimeBaseIdCustomerIdInList(StbM_SynchronizedTimeBaseType timeBaseId, StbM_CustomerIdType customerId)
{
  boolean timeBaseIdCustomerIdFound = FALSE;
  StbM_CustomerTimerExpireTimeNodeDataType *lclCurrent;


  for(lclCurrent = Head; lclCurrent != NULL_PTR; lclCurrent = lclCurrent->next)
  {
    if((lclCurrent->Data.timeBaseId == timeBaseId) && (lclCurrent->Data.customerId == customerId))
    {
      timeBaseIdCustomerIdFound = TRUE;
      break;
    }
  }

  return timeBaseIdCustomerIdFound;
}


STATIC FUNC(void, STBM_CODE) StbM_InsertInList
(
  uint32 timeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeNodeDataType, AUTOMATIC, STBM_VAR) newExpiryPointNode,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
)
{


  newExpiryPointNode->Data.timeBaseId = calculatedExpiryPoint->timeBaseId;
  newExpiryPointNode->Data.customerId = calculatedExpiryPoint->customerId;
  newExpiryPointNode->Data.customerTimerExpireTime = calculatedExpiryPoint->customerTimerExpireTime;
  newExpiryPointNode->Data.isGptTimerRunning = calculatedExpiryPoint->isGptTimerRunning;
  newExpiryPointNode->Data.pendingStartGptTimer = calculatedExpiryPoint->pendingStartGptTimer;
  newExpiryPointNode->Data.isTimerExpiredInGpt = calculatedExpiryPoint->isTimerExpiredInGpt;
  newExpiryPointNode->Data.arrayCellIndex = timeDataArrayIdx;
  newExpiryPointNode->Data.isArrayCellEmpty = FALSE;

}

/* !LINKSTO StbM.SWS_StbM_00337.SameExpiryPoints,1 */
/* !LINKSTO StbM.SWS_StbM_00337.DifferentExpiryPoints,1 */
STATIC FUNC(void, STBM_CODE) StbM_InsertAtTheBeginning
(
  uint32 expireTimeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *newlink = &StbM_ExpireTimeData[expireTimeDataArrayIdx];


  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(calculatedExpiryPoint != NULL_PTR,DET_INTERNAL_API_ID);

  /* insert in the list, the newly calculated expiry point */
  StbM_InsertInList(expireTimeDataArrayIdx, newlink, calculatedExpiryPoint);

  if(STBM_ISLISTEMPTY())
  {
     /* make it the last link */
     Last = newlink;
  }
  else
  {
     /* update first prev link */
     Head->previous = newlink;
  }

  /* point it to old first link */
  newlink->next = Head;

  /* point first to new first link */
  Head = newlink;

}

/* !LINKSTO StbM.SWS_StbM_00337.SameExpiryPoints,1 */
/* !LINKSTO StbM.SWS_StbM_00337.DifferentExpiryPoints,1 */
STATIC FUNC(void, STBM_CODE) StbM_InsertAfter
(
  uint32 expireTimeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) expiryPointAfterWhichToInsert,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;
  /* prepare expiry point to be inserted */
  StbM_CustomerTimerExpireTimeNodeDataType *newExpiryPoint = &StbM_ExpireTimeData[expireTimeDataArrayIdx];

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(expiryPointAfterWhichToInsert != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(calculatedExpiryPoint != NULL_PTR,DET_INTERNAL_API_ID);
  STBM_PRECONDITION_ASSERT(Head != NULL_PTR,DET_INTERNAL_API_ID);

  current = Head;

  /* navigate through list of expiry points, until 'pos' is reached */
  while((current->next != NULL_PTR) && (STBM_IS_DATA_FROM_NODES_EQUAL(expiryPointAfterWhichToInsert, (current->Data)) == FALSE))
  {
    /* move to the next expiry point */
    current = current->next;
  }

  /* insert in the list, the newly calculated expiry point */
  StbM_InsertInList(expireTimeDataArrayIdx, newExpiryPoint, calculatedExpiryPoint);

  if(current == Last)
  {
    newExpiryPoint->next = NULL_PTR;
    Last = newExpiryPoint;
  }
  else
  {
    newExpiryPoint->next = current->next;
    current->next->previous = newExpiryPoint;
  }

  newExpiryPoint->previous = current;
  current->next = newExpiryPoint;

}


/* !LINKSTO StbM.SWS_StbM_00337.SameExpiryPoints,1 */
/* !LINKSTO StbM.SWS_StbM_00337.DifferentExpiryPoints,1 */
STATIC FUNC(void, STBM_CODE) StbM_InsertAtTheRightPosition
(
  uint32 expireTimeDataArrayIdx,
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) calculatedExpiryPoint
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;
  uint32 listLength = 0U;
  StbM_TimeStampType newlyCalculatedExpiryPoint = {0U, 0U, 0U, 0U};


  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(calculatedExpiryPoint != NULL_PTR,DET_INTERNAL_API_ID);

  STBM_ASSIGN_TIMESTAMP(newlyCalculatedExpiryPoint, calculatedExpiryPoint->customerTimerExpireTime);

  listLength = StbM_GetListLength();

  /* if the list has only 1 element */
  if(listLength == 1U)
  {
    StbM_CustomerTimerExpireTimeDataType alreadyContainedInListExpiryPoint = {0U, 0U, {0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U, 0U, 0U};

    STBM_ASSIGN_CUSTOMERID_TIMEBASEID_EXPIRETIME(alreadyContainedInListExpiryPoint, StbM_ExpireTimeData[0].Data);

    /* newly calculated 'customerTimerExpireTime' is greater than the 'customerTimerExpireTime' of the first element, insert it after the first element */
    if(StbM_TimeStampIsGreaterEqual(&newlyCalculatedExpiryPoint, &alreadyContainedInListExpiryPoint.customerTimerExpireTime))
    {
      StbM_InsertAfter(expireTimeDataArrayIdx, &alreadyContainedInListExpiryPoint, calculatedExpiryPoint);
    }
    else /* newly calculated 'customerTimerExpireTime' is less than the 'customerTimerExpireTime' of the first element, insert it at the beginning */
    {
      StbM_InsertAtTheBeginning(expireTimeDataArrayIdx, calculatedExpiryPoint);
    }
  }
  else /* the list has more than 1 element */
  {

    for(current = Last; current != NULL_PTR; current = current->previous)
    {
      StbM_CustomerTimerExpireTimeDataType currentExpiryPoint = {0U, 0U, {0U, 0U, 0U, 0U}, 0U, 0U, 0U, 0U, 0U, 0U};

      STBM_ASSIGN_CUSTOMERID_TIMEBASEID_EXPIRETIME(currentExpiryPoint, current->Data);

      /* newlyCalculatedExpiryPoint is greater or equal than currentExpiryPoint => insert after position */
      if((StbM_TimeStampIsGreaterEqual(&newlyCalculatedExpiryPoint, &currentExpiryPoint.customerTimerExpireTime) == TRUE))
      {
        StbM_InsertAfter(expireTimeDataArrayIdx, &currentExpiryPoint, calculatedExpiryPoint);
        break;
      }
    }

    /* the element is smaller than all elements from the list */
    if(current == NULL_PTR)
    {
      /* the element should be inserted at the beginning */
      StbM_InsertAtTheBeginning(expireTimeDataArrayIdx, calculatedExpiryPoint);
    }

  }

}




STATIC FUNC(void, STBM_CODE) StbM_DeleteFromPosition
(
  P2VAR(StbM_CustomerTimerExpireTimeDataType, AUTOMATIC, STBM_VAR) expiryPointToBeDeleted
)
{
  StbM_CustomerTimerExpireTimeNodeDataType *current = NULL_PTR;

  /* Defensive programming */
  STBM_PRECONDITION_ASSERT(Head != NULL_PTR,DET_INTERNAL_API_ID);

  /* start from the first link */
  current = Head;


  /* navigate through list */
  while(STBM_IS_DATA_FROM_NODES_EQUAL(expiryPointToBeDeleted, (current->Data)) == FALSE)
  {
    /* move to next link */
    current = current->next;
  }

  /* if element is the first in list */
  if(current == Head)
  {
    /* change first to point to next link */
    Head = Head->next;

    if(current->next != NULL_PTR)
    {
      /* change previous of the new Head to point to NULL_PTR */
      current->next->previous = NULL_PTR;
    }
  }
  else if(current == Last) /* if element is the last in list */
  {
    /* change last to point to prev link */
    Last = current->previous;

    /* Defensive programming */
    /* Branch would've been reached in the following situation:
       1. current->previous would have been NULL_PTR
       Situation 1 -> Will never happen, because the Last node will always have a previous node.
                      If it is not the Last node, it will be the Head of an Intermediate node and it will enter on the other branches */

    /* CHECK: NOPARSE */
    if(current->previous != NULL_PTR)
    {
      current->previous->next = NULL_PTR;
    }
    else
    {
      /* unreachable code */
      STBM_UNREACHABLE_CODE_ASSERT(DET_INTERNAL_API_ID);
    }
    /* CHECK: PARSE */

    if(current->previous->previous != NULL_PTR)
    {
      /* change last to point to prev link */
      current->previous->previous->next = current->previous;
    }
  }
  else /* element is an intermediate one */
  {
    /* set the current node to be the next, after previous element
     * (link the left side)*/
    current->previous->next = current->next;

    /* set the current node to be the next, after previous element
     * (link the left side)*/
    current->next->previous = current->previous;
  }

  /* free array cell */
  StbM_TimeNotificationDataInit(current->Data.arrayCellIndex);

}


#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */

STATIC FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateRxTimeTuple
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) globalStampPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) virtualTimePtr
)
{
  Std_ReturnType retval = E_NOT_OK;
  StbM_VirtualLocalTimeType receivedTimeTupleVLT = {0U, 0U};
  StbM_TimeStampType tFrd = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTvSync = {0U, 0U};
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  StbM_TimeStampType maxAllowedValue = {0U, 0U, 0U, 0U};
  StbM_TimeStampType productTimeStamp = {0U, 0U, 0U, 0U};
  uint32 virtualLocalTimeDiff_Q = 0U;
  uint32 product_Q = 0U;
  Atomic_t rate = STBM_RATE_CORRECTION_DEFAULT_VALUE;
  uint8 commonIndex = STBM_TIMEBASE_ID_TO_COMMON_INDEX(timeBaseId);
  uint8 rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(commonIndex);
#endif /* STBM_SLAVE_RATE_CORRECTION_USED == STD_ON */

  /* Deviation MISRAC2012-4 */
  if(!(STBM_TIMEBASE_ID_IS_OFFSET(timeBaseId)))
  {
    retval = StbM_GetCurrentVirtualLocalTimeNoChecks(timeBaseId, &currentTvSync);
    if(retval == E_OK)
    {
      /* !LINKSTO StbM.SWS_StbM_00529.SyncRxTimeTuple.GetTvsync,1 */
      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(receivedTimeTupleVLT, *virtualTimePtr);
      /* update the Tvsync with new value */
      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(*virtualTimePtr, currentTvSync);
      /* !LINKSTO StbM.SWS_StbM_00529.SyncRxTimeTuple.CalcTfrd.AR-116407,2 */
      StbM_SubtractVirtualLocalTimesToTimeStamp
      (
        &currentTvSync,
        &receivedTimeTupleVLT,
        &tFrd
      );
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
      if(!STBM_SLAVE_RATE_CORRECTION_DISABLED(commonIndex))
      {
        /* !LINKSTO StbM.SWS_StbM_00529.SyncRxTimeTuple.ApplyRrc,1 */
        Atomics_Store(&rate, (Atomic_value_t)StbM_SlaveRateCorrectionData[rcDataIndex].rrc);
        /* obtain the limit for witch the calculation can be made */
        StbM_GetMaxAllowedLimit(rcDataIndex, TRUE, &maxAllowedValue);

        /* check if allowed calculation bound is correct */
        if(FALSE == StbM_TimeStampIsGreaterEqual(&tFrd, &maxAllowedValue))
        {
          /* convert the frdT to Q */
          virtualLocalTimeDiff_Q = StbM_Timestamp_To_Q(&tFrd);
          /* calculate the multiplication: ((TVSync - TVRx) * rrc) or ((TVSync - TVRx) * (roc - 1) )*/
          product_Q = StbM_Mul_Q(virtualLocalTimeDiff_Q, (uint32)rate);
          StbM_Q_To_Timestamp(product_Q, &productTimeStamp);
          STBM_ASSIGN_TIMESTAMP(tFrd, productTimeStamp);
        }
      }
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */
      /* !LINKSTO StbM.SWS_StbM_00529.SyncRxTimeTuple.AddRate,1 */
      (void)StbM_SumTimeStamps
      (
        globalStampPtr,
        &tFrd,
        globalStampPtr
      );
    }
  }
  else
  {
    /* Offset time base is used. */
    retval = E_OK;
  }


  return retval;
}




#if (STBM_SETBUSPROTOCOLPARAM_ACTIVE == STD_ON)
/* !LINKSTO StbM.SWS_StbM_91008,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_SetBusProtocolParam
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_ProtocolParamType, AUTOMATIC, STBM_APPL_DATA) protocolParam
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_SETBUSPROTOCOLPARAM_ENTRY(timeBaseId, protocolParam);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_SetBusProtocolParam,1 */
    STBM_DET_REPORTERROR(STBM_API_SETBUSPROTOCOLPARAM, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  else if ((!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId))) || (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00520,1 */
    /* !LINKSTO StbM.EB.StbM_SetBusProtocolParam.SyncTimeBaseNotConfigured.Return.E_NOT_OK,1 */
    STBM_DET_REPORTERROR(STBM_API_SETBUSPROTOCOLPARAM, STBM_E_PARAM);
  }
  else if (protocolParam == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00521,1 */
    STBM_DET_REPORTERROR(STBM_API_SETBUSPROTOCOLPARAM, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_SLAVE_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_SetBusProtocolParam for a slave time base shall throw a DET error */
    /* !LINKSTO StbM.EB.StbM_SetBusProtocolParam.Slave.Return.E_NOT_OK,1 */
    STBM_DET_REPORTERROR(STBM_API_SETBUSPROTOCOLPARAM, STBM_E_PARAM);
  }
  else
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* !LINKSTO StbM.SWS_StbM_00516.TimeBaseMappedToEthernet.And.protocolType.SetTo.STBM_TIMESYNC_ETHERNET.ForwardValuesToEthTSyn,1 */
    if((STBM_IS_TIMEBASE_CONNECTED_TO_ETHTSYN_TIMEDOMAIN(timeBaseId) == TRUE) && (protocolParam->protocolType == STBM_TIMESYNC_ETHERNET))
    {
      /* Forward the values provided in protocolParam to EthTSyn */
      retval = EthTSyn_SetProtocolParam(timeBaseId, protocolParam);
    }
    /* !LINKSTO StbM.SWS_StbM_00516.TimeBase.NotMappedTo.Ethernet.Return.E_NOT_OK,1 */
    /* !LINKSTO StbM.SWS_StbM_00516.protocolType.NotSetTo.STBM_TIMESYNC_ETHERNET.Return.E_NOT_OK,1 */
  }

  DBG_STBM_SETBUSPROTOCOLPARAM_EXIT(retval, timeBaseId, protocolParam);
  return retval;
} /* StbM_SetBusProtocolParam */
#endif /* (STBM_SETBUSPROTOCOLPARAM_ACTIVE == STD_ON) */




#if (STBM_GETBUSPROTOCOLPARAM_ACTIVE == STD_ON)
/* !LINKSTO StbM.SWS_StbM_91007,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetBusProtocolParam
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_ProtocolParamType, AUTOMATIC, STBM_APPL_DATA) protocolParam
)
{
  Std_ReturnType retval = E_NOT_OK;

  DBG_STBM_GETBUSPROTOCOLPARAM_ENTRY(timeBaseId, protocolParam);

#if(STBM_DEV_ERROR_DETECT == STD_ON)
  if (StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_GetBusProtocolParam,1 */
    STBM_DET_REPORTERROR(STBM_API_GETBUSPROTOCOLPARAM, STBM_E_UNINIT);
  }
  /* Deviation TASKING-4 */
  else if ((!(STBM_IS_SYNC_TIMEBASE_ID(timeBaseId))) || (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId)))
  {
    /* !LINKSTO StbM.SWS_StbM_00518,1 */
    /* !LINKSTO StbM.EB.StbM_GetBusProtocolParam.SyncTimeBaseNotConfigured.Return.E_NOT_OK,1 */
    STBM_DET_REPORTERROR(STBM_API_GETBUSPROTOCOLPARAM, STBM_E_PARAM);
  }
  else if (protocolParam == NULL_PTR)
  {
    /* !LINKSTO StbM.SWS_StbM_00519,1 */
    STBM_DET_REPORTERROR(STBM_API_GETBUSPROTOCOLPARAM, STBM_E_PARAM_POINTER);
  }
  /* Deviation TASKING-5 */
  else if (STBM_ONLY_MASTER_PORT_CONNECTED(timeBaseId))
  {
    /* Calling StbM_GetBusProtocolParam for a Master time base shall throw a DET error */
    /* !LINKSTO StbM.EB.StbM_GetBusProtocolParam.Master.Return.E_NOT_OK,1 */
    STBM_DET_REPORTERROR(STBM_API_GETBUSPROTOCOLPARAM, STBM_E_PARAM);
  }
  else
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* !LINKSTO StbM.SWS_StbM_00517.protocolType.SetTo.STBM_TIMESYNC_ETHERNET.ReadValuesFromEthTSyn,1 */
    if((STBM_IS_TIMEBASE_CONNECTED_TO_ETHTSYN_TIMEDOMAIN(timeBaseId) == TRUE) && (protocolParam->protocolType == STBM_TIMESYNC_ETHERNET))
    {
      /* Get the protocolParam from EthTSyn */
      retval = EthTSyn_GetProtocolParam(timeBaseId, protocolParam);
    }
    /* !LINKSTO StbM.SWS_StbM_00517.TimeBase.NotMappedTo.Ethernet.Return.E_NOT_OK,1 */
    /* !LINKSTO StbM.SWS_StbM_00517.protocolType.NotSetTo.STBM_TIMESYNC_ETHERNET.Return.E_NOT_OK,1 */
  }

  DBG_STBM_GETBUSPROTOCOLPARAM_EXIT(retval, timeBaseId, protocolParam);
  return retval;
} /* StbM_GetBusProtocolParam */
#endif /* (STBM_GETBUSPROTOCOLPARAM_ACTIVE == STD_ON) */

#if ( STBM_SOURCE_TIMEBASES_USED == STD_ON)

/* !LINKSTO StbM.SWS_StbM_91012,1 */
FUNC(Std_ReturnType, STBM_CODE) StbM_CloneTimeBase
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CloneConfigType cloneCfg,
  StbM_TimeBaseStatusType statusMask,
  StbM_TimeBaseStatusType statusValue
)
{
  Std_ReturnType retval = E_NOT_OK;
  uint8 destIndex;
  uint8 srcIndex;
  StbM_SynchronizedTimeBaseType srcTimeBaseId;
  Atomic_t srcTimeBaseStatus = 0U;
  DBG_STBM_CLONETIMEBASE_ENTRY(timeBaseId, cloneCfg, statusMask ,statusValue);
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  if(StbM_InitStatus == STBM_NOINIT)
  {
    /* !LINKSTO StbM.SWS_StbM_00041.STBM_E_UNINIT.StbM_CloneTimeBase,1 */
    STBM_DET_REPORTERROR(STBM_API_CLONETIMEBASE, STBM_E_UNINIT);
  }
  /* Deviation TASKING-1 */
  /* Deviation TASKING-2 */
  else if (STBM_TIMEBASE_ID_NOT_CONFIGURED_OR_WITHIN_RESERVED_RANGE(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00537.DET.NotConfigured,1 */
    STBM_DET_REPORTERROR(STBM_API_CLONETIMEBASE, STBM_E_PARAM);
  }
  else if (STBM_IS_OFFSET_TIMEBASE_ID(timeBaseId))
  {
    /* !LINKSTO StbM.SWS_StbM_00537.DET.OffsetTimeBaseId,1 */
    STBM_DET_REPORTERROR(STBM_API_CLONETIMEBASE, STBM_E_PARAM);
  }
  else
#endif /* (STBM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* !LINKSTO  StbM.SWS_StbM_00530.CloneTimeBase.First,1 */
    /* Deviation TASKING-1 */
    destIndex = STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX(timeBaseId);
    srcTimeBaseId = StbM_SourceTimeBaseCfg[destIndex].syncTimeBaseIndex;
    if(srcTimeBaseId != STBM_NO_SOURCE_TIME_BASE)
    {
        srcIndex  = STBM_SYNC_OR_PURE_ID_TO_COMMON_INDEX(srcTimeBaseId);
        /* store StbM_TimeStamps[srcIndex].globalTime.timeBaseStatus) into srcTimeBaseStatus atomically */
        Atomics_Store(&srcTimeBaseStatus, (Atomic_value_t)StbM_TimeStamps[srcIndex].globalTime.timeBaseStatus);
        if( ( srcTimeBaseStatus & statusMask) == statusValue)
        {
            /* !LINKSTO StbM.SWS_StbM_00533.CloneMask.E_OK,1 */
    #if (STBM_TIMEOUTS_USED == STD_ON)
            /*if( StbM_CommonTimeBaseCfg[srcIndex].timeoutValue > 0 && StbM_TimeBaseTimeout[srcIndex] == 0U )*/
            if(STBM_FLAG_IS_SET(srcTimeBaseStatus, STBM_TIMEOUT_FLAG))
            {
               Atomic_t srcTimeBaseIdLcl = StbM_CloneDataArr[destIndex].srcTimeBaseId;
               /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_CloneDataPtr,1 */
               /* !LINKSTO StbM.SWS_StbM_00531.AR-117132,1 */
               /* Timeout happens for Src time base and should reject the clone request*/
               /* Remove any pending deferred clone request of the same [Source;Destination] tuple */
               Atomics_Store(&srcTimeBaseIdLcl, (Atomic_value_t)STBM_NO_SOURCE_TIME_BASE);
            }
            else
    #endif /*(STBM_TIMEOUTS_USED == STD_ON)*/
            {
               if( (cloneCfg & STBM_CLONE_DEFERRED_COPY) != 0U)
               {
                  /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_CloneDataPtr,1 */
                  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
                  /* Deffered the clone until Source Time base is updated next time by <bus>TSyn module */
                  /* !LINKSTO StbM.SWS_StbM_00530.CloneTimeBase.DEFERRED_COPY_flag.Set,1 */
                  StbM_CloneDataArr[destIndex].srcTimeBaseId = srcIndex;
                  StbM_CloneDataArr[destIndex].cloneCfg = cloneCfg;
                  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
                  retval = E_OK;
               }
               else
               {
                  Atomic_t srcTimeBaseIdLcl = StbM_CloneDataArr[destIndex].srcTimeBaseId;
                  /* No deffered, Time information to be copied immediately to Destination Time Base */
                  /* !LINKSTO StbM.SWS_StbM_00530.CloneTimeBase.DEFERRED_COPY_flag.Not_Set.ProcessCloneRequest_Successful,1 */
                  retval = StbM_CloneTimeBase_Internal( srcIndex ,destIndex, cloneCfg );
                  /*remove any pending deferred clone request of the same [Source;Destination] tuple*/
                  /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_CloneDataPtr,1 */
                  Atomics_Store(&srcTimeBaseIdLcl, (Atomic_value_t)STBM_NO_SOURCE_TIME_BASE);
               }
            }
        }
        else
        {
            /* !LINKSTO StbM.SWS_StbM_00533.CloneMask.E_NOT_OK,1 */
            /* Reject the clone request */
        }
    }
    else
    {
      /* Reject the clone request as no source time  based configured*/
    }

  }

  DBG_STBM_CLONETIMEBASE_EXIT(timeBaseId, cloneCfg, statusMask ,statusValue);
  return retval;
}


STATIC FUNC(Std_ReturnType, STBM_CODE)  StbM_CloneTimeBase_Internal(uint8 srcIndex, uint8 destIndex, StbM_CloneConfigType cloneCfg )
{
  Std_ReturnType retval = E_NOT_OK;
  Std_ReturnType retvalDest = E_NOT_OK;
  StbM_VirtualLocalTimeType srcLocalTime = {0U, 0U};
  StbM_VirtualLocalTimeType destLocalTime = {0U, 0U};
  StbM_TimeStampType currentTimeTupleGlobal = {0U, 0U, 0U, 0U};
  StbM_VirtualLocalTimeType currentTimeTupleVLT = {0U, 0U};
  StbM_TimeStampType timeStampLocalTime = {0U, 0U, 0U, 0U};
  uint8 u8srcTimeeId;
  uint8 u8destTimeeId;
  StbM_SynchronizedTimeBaseType srcTimeBaseId;
  StbM_SynchronizedTimeBaseType destTimeBaseId;

  if( StbM_SourceTimeBaseCfg[destIndex].haveSameVirtualSources == 1U)
  {
      /*  they have same Virtual Local Time Sources */
      /* !LINKSTO StbM.SWS_StbM_00534.Same.Virtual_Local_Time_Source,1 */
     SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* Clone Time Tuple values for the Src time base to Destination*/
      STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[destIndex].globalTime, StbM_TimeStamps[srcIndex].globalTime);

      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[destIndex].virtualLocalTime, StbM_TimeStamps[srcIndex].virtualLocalTime);
      /* Clone the user data */
      StbM_UserData[destIndex].userDataLength = StbM_UserData[srcIndex].userDataLength;
      StbM_UserData[destIndex].userByte0      = StbM_UserData[srcIndex].userByte0;
      StbM_UserData[destIndex].userByte1      = StbM_UserData[srcIndex].userByte1;
      StbM_UserData[destIndex].userByte2      = StbM_UserData[srcIndex].userByte2;
      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
      retval = E_OK;
  }
  else
  {
      /* if they don't have same Virtual Local Time Sources */
      /* !LINKSTO StbM.SWS_StbM_00534.Different.Virtual_Local_Time_Source,1 */
      u8srcTimeeId =  STBM_COMMON_INDEX_TO_TIMEBASEID(srcIndex);
      u8destTimeeId = STBM_COMMON_INDEX_TO_TIMEBASEID(destIndex);
      srcTimeBaseId =  (StbM_SynchronizedTimeBaseType) u8srcTimeeId;
      destTimeBaseId = (StbM_SynchronizedTimeBaseType) u8destTimeeId;

      SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      /* Get current Time Tuple values */
      STBM_ASSIGN_TIMESTAMP(currentTimeTupleGlobal, StbM_TimeStamps[srcIndex].globalTime);

      STBM_ASSIGN_VIRTUAL_LOCAL_TIME(currentTimeTupleVLT, StbM_TimeStamps[srcIndex].virtualLocalTime);
      retval     = StbM_GetCurrentVirtualLocalTimeNoChecks( srcTimeBaseId, &srcLocalTime);
      retvalDest = StbM_GetCurrentVirtualLocalTimeNoChecks( destTimeBaseId , &destLocalTime);

      SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

      if( (E_OK ==  retval) && (E_OK == retvalDest))
      {
          retval = StbM_GetTime(srcTimeBaseId, &timeStampLocalTime, &currentTimeTupleGlobal, &currentTimeTupleVLT, &srcLocalTime);
          if (retval == E_OK)
          {
              /* Clone the Local Time */
              /* enter critical section */
              /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_TimeStamps,1 */
              /* !LINKSTO StbM.dsn.ExclusiveArea_StbM_UserData,1 */
              SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
              STBM_ASSIGN_VIRTUAL_LOCAL_TIME(StbM_TimeStamps[destIndex].virtualLocalTime, destLocalTime);
              STBM_ASSIGN_TIMESTAMP(StbM_TimeStamps[destIndex].globalTime, timeStampLocalTime);
              /* Clone the user data */
              StbM_UserData[destIndex].userDataLength = StbM_UserData[srcIndex].userDataLength;
              StbM_UserData[destIndex].userByte0      = StbM_UserData[srcIndex].userByte0;
              StbM_UserData[destIndex].userByte1      = StbM_UserData[srcIndex].userByte1;
              StbM_UserData[destIndex].userByte2      = StbM_UserData[srcIndex].userByte2;
              SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
          }
          else
          {
            /* retVal = E_NOT_OK when src TL could not be retrieved */
            /* !LINKSTO StbM.SWS_StbM_00530.CloneTimeBase.DEFERRED_COPY_flag.Not_Set.ProcessCloneRequest_NotSuccessful.srcTLNotRetrieved,1 */
          }
      }
      else
      {
        /* retVal = E_NOT_OK when src VLT or dest VLT could not be retrieved */
        /* !LINKSTO StbM.SWS_StbM_00530.CloneTimeBase.DEFERRED_COPY_flag.Not_Set.ProcessCloneRequest_NotSuccessful.srcVLTdestVLTNotRetrieved,1 */
      }
  }

  if(retval == E_OK)
  {
     retval = StbM_Clone_Internal_Update_Counter_Rate(srcIndex, destIndex, cloneCfg );
  }

  return retval;

}


STATIC FUNC(Std_ReturnType, STBM_CODE)  StbM_Clone_Internal_Update_Counter_Rate(uint8 srcIndex, uint8 destIndex, StbM_CloneConfigType cloneCfg )
{
  Std_ReturnType retval = E_NOT_OK;

#if (STBM_RATE_CORRECTION_USED)
  uint8 rcDataIndex;
  StbM_RateDeviationType rateDeviation = STBM_RATE_DEVIATION_DEFAULT_VALUE;
  uint32 rrc = STBM_RATE_CORRECTION_DEFAULT_VALUE;
#endif /* #if (STBM_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
  boolean  srcMasterRateCorrectionDisabled;
  boolean  destMasterRateCorrectionDisabled;
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
  boolean  srcSlaveRateCorrectionDisabled;
#endif /*  STBM_SLAVE_RATE_CORRECTION_USED */

#if !(STBM_RATE_CORRECTION_USED)
  TS_PARAM_UNUSED(srcIndex);
#endif /* #if (STBM_RATE_CORRECTION_USED == STD_ON) */
  SchM_Enter_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();

  /* !LINKSTO StbM.SWS_StbM_00536,1 */
  /* If the flag IMMEDIATE_TX is set, StbM shall increment the timeBaseUpdateCounter of the Destination Time Base */
#if(STBM_NUMBER_OF_SYNC_TIMEBASES > 0U)
  if( (STBM_FLAG_IS_SET(cloneCfg, STBM_CLONE_IMMEDIATE_TX)) && (destIndex < STBM_NUMBER_OF_SYNC_TIMEBASES) )
  {
      /* Increment the Destination time base update counter, this is the defined and intended overflow */
      StbM_TimeBaseUpdateCounter[destIndex]++;
  }
#endif /* (STBM_NUMBER_OF_SYNC_TIMEBASES > 0U) */

  /* If the flag APPLY_RATE is set, the StbM shall copy the Rate Correction value of the Source Time Base to the Destination Time Base.  */
  if(STBM_FLAG_IS_SET(cloneCfg, STBM_CLONE_APPLY_RATE))
  {
#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
     /* check if rate correction is calculated for a master timebase */
     srcMasterRateCorrectionDisabled = STBM_MASTER_RATE_CORRECTION_DISABLED(srcIndex);
     destMasterRateCorrectionDisabled = STBM_MASTER_RATE_CORRECTION_DISABLED(destIndex);
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
     srcSlaveRateCorrectionDisabled = STBM_SLAVE_RATE_CORRECTION_DISABLED(srcIndex);
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
     if(srcMasterRateCorrectionDisabled == FALSE)
     {
        /* get index for the StbM_MasterRateCorrectionData[] array */
        rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(srcIndex);
        /* update rate deviation */
        /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_Set.SrcRateCorrection_DestRateCorrection_ApplySrcRateValueToDest,1 */
        rateDeviation = StbM_MasterRateCorrectionData[rcDataIndex].rateDev;
        rrc = StbM_MasterRateCorrectionData[rcDataIndex].rrc;
     }
     /* it shall be checked for a slave */
     else
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
#if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON)
     if (srcSlaveRateCorrectionDisabled == FALSE)
     {
        /* get index for the StbM_SlaveRateCorrectionData[] array */
        rcDataIndex = STBM_GET_SLAVE_RATEDATA_TIMEBASE_INDEX(srcIndex);
        /* update rate deviation */
        /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_Set.SrcRateCorrection_DestRateCorrection_ApplySrcRateValueToDest,1 */
        rateDeviation = StbM_SlaveRateCorrectionData[rcDataIndex].rateDev;
        rrc = StbM_SlaveRateCorrectionData[rcDataIndex].rrc;
     }
     else
#endif /* #if (STBM_SLAVE_RATE_CORRECTION_USED == STD_ON) */
     {
        /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_Set.SrcNoRateCorrection_DestRateCorrection_ApplySrcDefaultRateValueToDest,1 */
        /* even if src's Rate Correction is not enabled, cloning will take place
           and src's rateDeviation and rrc will be set to their DEFAULT values */
     }

#if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON)
      if(destMasterRateCorrectionDisabled == FALSE)
      {
         /* get index for the StbM_MasterRateCorrectionData[] array */
         rcDataIndex = STBM_GET_MASTER_RATEDATA_TIMEBASE_INDEX(destIndex);
         /* update rate deviation */
         /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_Set.SrcRateCorrection_DestRateCorrection_ApplySrcRateValueToDest,1 */
         StbM_MasterRateCorrectionData[rcDataIndex].rateDev = rateDeviation;
         StbM_MasterRateCorrectionData[rcDataIndex].rrc = rrc;
         /* cloning will take place - src's Rate Correction (beeing it the DEFAULT one or the computed one) is applied to dest */
         retval = E_OK;
      }
      else
#endif /* #if (STBM_MASTER_RATE_CORRECTION_USED == STD_ON) */
      {
        /* retVal = E_NOT_OK when src RateCorrection could not be applied to dest */
        /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_Set.SrcRateCorrection_DestNoRateCorrection_NotApplySrcRateValueToDest,1 */
        /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_Set.SrcNoRateCorrection_DestNoRateCorrection_NotApplySrcRateValueToDest,1 */
      }
  }
  else
  {
    /* cloning will take place, even if APPLY_RATE is not set */
    /* !LINKSTO StbM.SWS_StbM_00535.APPLY_RATE_NotSet,1 */
    retval = E_OK;
  }
  SchM_Exit_StbM_SCHM_STBM_EXCLUSIVE_AREA_0();
  return retval;
}
#endif /* (STBM_SOURCE_TIMEBASES_USED == STD_ON) */





#if  (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_LocalTimeCall
(
  P2VAR(StbM_LocalTimeCallType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint16 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < (STBM_NUMBER_OF_SYNC_TIMEBASES + STBM_NUMBER_OF_OFFSET_TIMEBASES + STBM_NUMBER_OF_PURE_TIMEBASES); idx++)
  {
    /* initialize array */
    STBM_INIT_LOCALTIMECALL_0(arrayToBeInitialized[idx]);
  }
}
#endif /* STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON */



#if (STBM_SYNC_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_SyncRecordTableBlock
(
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_SYNCRECORDTABLEBLOCK_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_SYNC_TIME_RECORDING_USED == STD_ON) */



#if (STBM_OFFSET_TIME_RECORDING_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_OffsetRecordTableBlock
(
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_NUMBER_OF_OFFSET_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_OFFSETRECORDTABLEBLOCK_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_OFFSET_TIME_RECORDING_USED == STD_ON) */


#if (STBM_TIME_VALIDATION_SUPPORT == STD_ON)

#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_CanTimeMasterMeasurement
(
  P2VAR(StbM_CanTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_CANTSYN_MASTER_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_CANTIMEMASTERMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_CanTimeSlaveMeasurement
(
  P2VAR(StbM_CanTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_CANTSYN_SLAVE_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_CANTIMESLAVEMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_HAS_AT_LEAST_ONE_CANTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_FrTimeMasterMeasurement
(
  P2VAR(StbM_FrTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_FRTSYN_MASTER_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_FRTIMEMASTERMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_MASTER_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_FrTimeSlaveMeasurement
(
  P2VAR(StbM_FrTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_FRTSYN_SLAVE_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_FRTIMESLAVEMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_HAS_AT_LEAST_ONE_FRTSYN_SLAVE_LINKED == STD_ON) */


#if (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_EthTimeMasterMeasurement
(
  P2VAR(StbM_EthTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_ETHTIMEMASTERMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}

STATIC FUNC(void, STBM_CODE) StbM_Init_EthTimeSlaveMeasurement
(
  P2VAR(StbM_EthTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_ETHTIMESLAVEMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}

STATIC FUNC(void, STBM_CODE) StbM_Init_PdelayResponderMeasurement
(
  P2VAR(StbM_PdelayResponderMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_PDELAYRESPONDERMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}

STATIC FUNC(void, STBM_CODE) StbM_Init_PdelayInitiatorMeasurement
(
  P2VAR(StbM_PdelayInitiatorMeasurementType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  for(idx = 0U; idx < STBM_NUMBER_OF_SYNC_ETHTSYN_MASTER_OR_SLAVE_TIME_RECORD_BLOCKS; idx++)
  {
    /* initialize array */
    STBM_INIT_PDELAYINITIATORMEASUREMENT_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_HAS_AT_LEAST_ONE_ETHTSYN_LINKED_TO_A_TIMEBASE_WHICH_HAS_TIMEVALIDATION_ENABLED == STD_ON) */

#endif /* (STBM_TIME_VALIDATION_SUPPORT == STD_ON) */


#if (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON)
STATIC FUNC(void, STBM_CODE) StbM_Init_SendCustomerNotification
(
  P2VAR(StbM_SendCustomerNotificationType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS; idx++)
  {
    /* initialize array */
    STBM_INIT_SENDCUSTOMERNOTIFICATION_0(arrayToBeInitialized[idx]);
  }
}

STATIC FUNC(void, STBM_CODE) StbM_Init_GptCallPair
(
  P2VAR(StbM_GptCallPairType, AUTOMATIC, STBM_APPL_DATA) arrayToBeInitialized
)
{
  uint32 idx;

  /* Deviation TASKING-1 */
  for(idx = 0U; idx < STBM_MAX_NUMBER_OF_STBM_STARTTIMER_CALLS; idx++)
  {
    /* initialize array */
    STBM_INIT_GPTCALLPAIR_0(arrayToBeInitialized[idx]);
  }
}
#endif /* (STBM_NOTIFICATION_OF_CUSTOMERS_USED == STD_ON) */









#define STBM_STOP_SEC_CODE
#include <StbM_MemMap.h>

/*==================[end of file]===========================================*/

