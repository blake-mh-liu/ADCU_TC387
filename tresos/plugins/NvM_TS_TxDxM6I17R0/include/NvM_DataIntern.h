/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
 *
 * \version 6.17.36
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef NVM_DATA_INTERN_H
#define NVM_DATA_INTERN_H
/*==================[inclusions]============================================*/
#include <TSAutosar.h>            /* AUTOSAR standard types                 */
#include <NvM_Int_Types.h>        /* NvM specific internal types            */
#include <NvM_Cfg.h>              /* Contains generated configuration       */
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
#include <Os.h>                   /* Os Application related                 */
#endif
#include <NvM_UsrHdr.h>
                                  /* data.                                  */

/*==================[macros]================================================*/

/*------------------[the NvM Instance Id]---------------------------------*/

#if(defined NVM_INSTANCE_ID)
#error NVM_INSTANCE_ID is already defined
#endif
/** \brief Defines the instance number of this NVRAM manager.
 **        Since multiple instances of a NVRAM manager are not supported
 **        the Instance Id is always zero.
 **/
#define NVM_INSTANCE_ID     0x00U





/*------------------------[Defensive programming]----------------------------*/

#if (defined NVM_PRECONDITION_ASSERT)
#error NVM_PRECONDITION_ASSERT is already defined
#endif

#if (defined NVM_PRECONDITION_ASSERT_NO_EVAL)
#error NVM_PRECONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (NVM_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define NVM_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define NVM_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_PRECONDITION_ASSERT_NO_EVAL((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_PRECONDITION_ASSERT(Condition, ApiId)
#define NVM_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined NVM_POSTCONDITION_ASSERT)
#error NVM_POSTCONDITION_ASSERT is already defined
#endif

#if (defined NVM_POSTCONDITION_ASSERT_NO_EVAL)
#error NVM_POSTCONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (NVM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define NVM_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define NVM_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT_NO_EVAL((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_POSTCONDITION_ASSERT(Condition, ApiId)
#define NVM_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined NVM_INVARIANT_ASSERT)
#error NVM_INVARIANT_ASSERT is already defined
#endif

#if (defined NVM_INVARIANT_ASSERT_NO_EVAL)
#error NVM_INVARIANT_ASSERT_NO_EVAL is already defined
#endif

#if (NVM_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define NVM_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define NVM_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_INVARIANT_ASSERT_NO_EVAL((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_INVARIANT_ASSERT(Condition, ApiId)
#define NVM_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined NVM_STATIC_ASSERT)
# error NVM_STATIC_ASSERT is already defined
#endif
#if (NVM_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define NVM_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define NVM_STATIC_ASSERT(expr)
#endif

#if (defined NVM_UNREACHABLE_CODE_ASSERT)
#error NVM_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (NVM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **

 ** \param[in] ApiId Service ID of the API function */
#define NVM_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined NVM_INTERNAL_API_ID)
#error NVM_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define NVM_INTERNAL_API_ID DET_INTERNAL_API_ID


#if (defined NVM_GET_BLOCK_INDEX)
#error NVM_GET_BLOCK_INDEX is already defined
#endif

/** \brief Macro function to validate block id and return the index in block descriptor if valid if
 * Det is ON, otherwise just return the index in the block descriptor array for the given block id
 **/
#if ( NVM_DEV_ERROR_DETECT == STD_ON )
#define NVM_GET_BLOCK_INDEX(BlockId)    NvM_GetBlockIndexForValidId(BlockId)
#else /* ( NVM_DEV_ERROR_DETECT == STD_ON ) */
#if ( NVM_USE_REDIR_BLOCK_ARRAY == STD_ON )
#define NVM_GET_BLOCK_INDEX(BlockId)    NvM_RedirBlockId[BlockId]
#else /* ( NVM_USE_REDIR_BLOCK_ARRAY == STD_ON ) */
#if ( NVM_BLOCK_INDEX_SEARCH == STD_ON )
#define NVM_GET_BLOCK_INDEX(BlockId)    NvM_SearchConfigTable(BlockId)
#else /* ( NVM_BLOCK_INDEX_SEARCH == STD_ON ) */
#define NVM_GET_BLOCK_INDEX(BlockId)    (uint16)BlockId
#endif /* ( NVM_BLOCK_INDEX_SEARCH == STD_ON ) */
#endif /* ( NVM_USE_REDIR_BLOCK_ARRAY == STD_ON ) */
#endif /* ( NVM_DEV_ERROR_DETECT == STD_ON ) */

/** \brief Report development error if DET is enabled
 **/

#if ( NVM_DEV_ERROR_DETECT == STD_ON )

#if (defined NVM_DET_REPORT_ERROR)
#error NVM_DET_REPORT_ERROR is already defined
#endif

#define NVM_DET_REPORT_ERROR( ApiId,ErrorId )    \
    (void)Det_ReportError( NVM_MODULE_ID, NVM_INSTANCE_ID, ( ApiId ), ( ErrorId ) )
#else
#define NVM_DET_REPORT_ERROR( ApiId,ErrorId )
#endif

#if (defined NVM_DEM_REPORT_ERROR)
#error NVM_DEM_REPORT_ERROR is already defined
#endif
/** \brief Reports production error for a configured Dem event Id
 **
 ** \param[in] Dem Event Id
 ** \param[in] Dem Event Status
 **/
#define NVM_DEM_REPORT_ERROR(EventId, EventStatus) \
  (void)Dem_ReportErrorStatus((EventId), (EventStatus))

#if (defined NVM_GET_BLOCKREQUEST)
#error NVM_GET_BLOCKREQUEST is already defined
#endif
/** \brief Converts the SeviceId/API Id into NvM_BlockRequestType values used for single block callback
 **
 ** \param[in] SeviceId to report the job result for
 **/
#define NVM_GET_BLOCKREQUEST(ServiceId) ((((ServiceId) == NVM_READ_BLOCK_API_ID) || ((ServiceId) == NVM_READ_PRAM_BLOCK_API_ID)) ? (NVM_READ_BLOCK) : \
                                          ((((ServiceId) == NVM_WRITE_BLOCK_API_ID) || ((ServiceId) == NVM_WRITE_PRAM_BLOCK_API_ID)) ? (NVM_WRITE_BLOCK) : \
                                            ((((ServiceId) == NVM_RESTORE_BLOCK_DEFAULTS_API_ID) ||((ServiceId) == NVM_RESTORE_PRAM_BLOCK_DEFAULTS_API_ID)) ? (NVM_RESTORE_BLOCK_DEFAULTS) : \
                                              (((ServiceId) == NVM_ERASE_NV_BLOCK_API_ID) ? (NVM_ERASE_NV_BLOCK) : \
                                                (((ServiceId) == NVM_INVALIDATE_NV_BLOCK_API_ID) ? (NVM_INVALIDATE_NV_BLOCK) : \
                                                  (NVM_READ_ALL_BLOCK))))))
#if (defined NVM_INVERT_DATAINDEX)
#error NVM_INVERT_DATAINDEX is already defined
#endif
/** \brief Inverts the current used data index for redundant blocks
 **
 ** \param[in] Index Current data index of a redundant block
 **/
#define NVM_INVERT_DATAINDEX(Index) (((Index) == 0U) ? (1U) : (0U))

#if (defined NVM_BD_CRCTYPE_OFFSET)
#error NVM_BD_CRCTYPE_OFFSET is already defined
#endif
/** \brief offset of CRC bits in the bit pattern */
#define NVM_BD_CRCTYPE_OFFSET        0U

#if (defined NVM_BD_CRCTYPE)
#error NVM_BD_CRCTYPE is already defined
#endif
/** \brief NVM_BD_CRCTYPE: extracts the CRC type from the given
 **                              bit pattern
 ** \param[in]   value : bit pattern from which the CRC type has
 **                         to be extracated
 **/
#define NVM_BD_CRCTYPE(value) (((uint8)((value) >> NVM_BD_CRCTYPE_OFFSET)) & 0x07U)

#if (defined NVM_BD_CRCTYPE_NONE)
#error NVM_BD_CRCTYPE_NONE is already defined
#endif
/** \brief No CRC */
#define NVM_BD_CRCTYPE_NONE          0U

#if (defined NVM_BD_CRCTYPE_CRC8)
#error NVM_BD_CRCTYPE_CRC8 is already defined
#endif
/** \brief 8 bit CRC */
#define NVM_BD_CRCTYPE_CRC8          1U

#if (defined NVM_BD_CRCTYPE_CRC16)
#error NVM_BD_CRCTYPE_CRC16 is already defined
#endif
/** \brief 16 bit CRC */
#define NVM_BD_CRCTYPE_CRC16         2U

#if (defined NVM_BD_CRCTYPE_CRC32)
#error NVM_BD_CRCTYPE_CRC32 is already defined
#endif
/** \brief 32 bit CRC */
#define NVM_BD_CRCTYPE_CRC32         3U

#if (defined NVM_BD_CALCRAMBLOCKCRC_BIT)
#error NVM_BD_CALCRAMBLOCKCRC_BIT is already defined
#endif
/** \brief mask for RAM block CRC bit */
#define NVM_BD_CALCRAMBLOCKCRC_BIT 0x08U

#if (defined NVM_BD_CALCRAMBLOCKCRC)
#error NVM_BD_CALCRAMBLOCKCRC is already defined
#endif
/** \brief NVM_BD_CALCRAMBLOCKCRC: Check whether the RAM block CRC is present.
 **
 ** \param[in]  value : bit pattern from which the RAM block CRC
 **                         is present status is extracted
 **/
#define NVM_BD_CALCRAMBLOCKCRC(value) (((value) & NVM_BD_CALCRAMBLOCKCRC_BIT) != 0U)

#if (defined NVM_BD_WRITEBLOCKPROTECTION_BIT)
#error NVM_BD_WRITEBLOCKPROTECTION_BIT is already defined
#endif
/** \brief mask for Write block protection bit */
#define NVM_BD_WRITEBLOCKPROTECTION_BIT 0x10U

#if (defined NVM_BD_WRITEBLOCKPROTECTION)
#error NVM_BD_WRITEBLOCKPROTECTION is already defined
#endif
/** \brief NVM_BD_WRITEBLOCKPROTECTION: Check whether the write block protection is enabled
 **
 ** \param[in]  value : bit pattern from which the write block protection
 **                         status is extracted
 **/
#define NVM_BD_WRITEBLOCKPROTECTION(value) (((value) & NVM_BD_WRITEBLOCKPROTECTION_BIT) != 0U)

#if (defined NVM_BD_WRITEONCE_BIT)
#error NVM_BD_WRITEONCE_BIT is already defined
#endif
/** \brief mask for Write once bit */
#define NVM_BD_WRITEONCE_BIT 0x20U

#if (defined NVM_BD_WRITEONCE)
#error NVM_BD_WRITEONCE is already defined
#endif
/** \brief NVM_BD_WRITEONCE: Check whether the write block once is enabled
 **
 ** \param[in]  value : bit pattern from which the write block once
 **                         status is extracted
 **/
#define NVM_BD_WRITEONCE(value) (((value) & NVM_BD_WRITEONCE_BIT) != 0U)

#if (defined NVM_BD_RESISTANTTOCHANGE_BIT)
#error NVM_BD_RESISTANTTOCHANGE_BIT is already defined
#endif
/** \brief mask for Resistant to change bit */
#define NVM_BD_RESISTANTTOCHANGE_BIT 0x40U

#if (defined NVM_BD_RESISTANTTOCHANGE_BIT_FALSE)
#error NVM_BD_RESISTANTTOCHANGE_BIT_FALSE is already defined
#endif
/** \brief NVM_BD_RESISTANTTOCHANGE_BIT_FALSE: Check whether the write block once is disabled
 **
 ** \param[in]  value : bit pattern from which the resistant to change
 **                         status is extracted
 **/
#define NVM_BD_RESISTANTTOCHANGE_BIT_FALSE(value) (((value) & NVM_BD_RESISTANTTOCHANGE_BIT) == 0U)

#if (defined NVM_BD_BLOCKMNGTTYPE_OFFSET)
#error NVM_BD_BLOCKMNGTTYPE_OFFSET is already defined
#endif
/** \brief offset of block management type bits in the bit pattern */
#define NVM_BD_BLOCKMNGTTYPE_OFFSET 7U

#if (defined NVM_BD_BLOCKMNGTTYPE)
#error NVM_BD_BLOCKMNGTTYPE is already defined
#endif
/** \brief NVM_BD_BLOCKMNGTTYPE: extracts the block management type from the given
 **                              bit pattern
 ** \param[in]  value : bit pattern from which the block management type has
 **                         to be extracated
 **/
#define NVM_BD_BLOCKMNGTTYPE(value) (((uint8)((value) >> NVM_BD_BLOCKMNGTTYPE_OFFSET)) & 0x03U)

#if (defined NVM_BD_BLOCKMNGTTYPE_NATIVE)
#error NVM_BD_BLOCKMNGTTYPE_NATIVE is already defined
#endif
/**  \brief Native Block */
#define NVM_BD_BLOCKMNGTTYPE_NATIVE    0U

#if (defined NVM_BD_BLOCKMNGTTYPE_REDUNDANT)
#error NVM_BD_BLOCKMNGTTYPE_REDUNDANT is already defined
#endif
/**  \brief Redundant Block */
#define NVM_BD_BLOCKMNGTTYPE_REDUNDANT 1U

#if (defined NVM_BD_BLOCKMNGTTYPE_DATASET)
#error NVM_BD_BLOCKMNGTTYPE_DATASET is already defined
#endif
/**  \brief Dataset Block */
#define NVM_BD_BLOCKMNGTTYPE_DATASET   2U

#if (defined NVM_BD_READALL_BIT)
#error NVM_BD_READALL_BIT is already defined
#endif
/** \brief mask for Read all bit */
#define NVM_BD_READALL_BIT 0x0200U

#if (defined NVM_BD_READALL)
#error NVM_BD_READALL is already defined
#endif
/** \brief NVM_BD_READALL: Check whether the read all is enabled
 **
 ** \param[in]  value : bit pattern from which the read all
 **                         status is extracted
 **/
#define NVM_BD_READALL(value) (((value) & NVM_BD_READALL_BIT) != 0U)

#if (defined NVM_BD_DEVICEID_OFFSET)
#error NVM_BD_DEVICEID_OFFSET is already defined
#endif
/** \brief offset of block management type bits in the bit pattern */
#define NVM_BD_DEVICEID_OFFSET 10U

#if (defined NVM_BD_DEVICEID)
#error NVM_BD_DEVICEID is already defined
#endif
/** \brief NVM_BD_BLOCKMNGTTYPE: extracts the device ID from the given
 **                              bit pattern
 ** \param[in]  value : bit pattern from which the device ID has
 **                         to be extracated
 **/
#define NVM_BD_DEVICEID(value) (((uint8)((value) >> NVM_BD_DEVICEID_OFFSET)) & 0x07U)

#if (defined NVM_BD_USEINTERNALBUFFER_BIT)
#error NVM_BD_USEINTERNALBUFFER_BIT is already defined
#endif
/** \brief mask for 'Use internal buffer' bit */
#define NVM_BD_USEINTERNALBUFFER_BIT 0x2000U

#if (defined NVM_BD_USEINTERNALBUFFER)
#error NVM_BD_USEINTERNALBUFFER is already defined
#endif
/** \brief NVM_BD_USEINTERNALBUFFER: Check whether the usage of internal buffer is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Use internal buffer'
 **                         status is extracted
 **/
#define NVM_BD_USEINTERNALBUFFER(value) (((value) & NVM_BD_USEINTERNALBUFFER_BIT) != 0U)

#if (defined NVM_BD_ADVANCED_RECOVERY_BIT)
#error NVM_BD_ADVANCED_RECOVERY_BIT is already defined
#endif
/** \brief mask for 'Nvm Advanced Recovery' bit */
#define NVM_BD_ADVANCED_RECOVERY_BIT 0x4000U

#if (defined NVM_BD_ADVANCED_RECOVERY)
#error NVM_BD_ADVANCED_RECOVERY is already defined
#endif
/** \brief NVM_BD_ADVANCED_RECOVERY: Check whether 'Advanced Recovery' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Advanced Recovery'
 **                     status is extracted
 **/
#define NVM_BD_ADVANCED_RECOVERY(value) (((value) & NVM_BD_ADVANCED_RECOVERY_BIT) != 0U)

#if (defined NVM_BD_WRITE_VERIFICATION_BIT)
#error NVM_BD_WRITE_VERIFICATION_BIT is already defined
#endif
/** \brief mask for 'NvM Write Verification' bit */
#define NVM_BD_WRITE_VERIFICATION_BIT 0x8000U

#if (defined NVM_BD_WRITE_VERIFICATION)
#error NVM_BD_WRITE_VERIFICATION is already defined
#endif
/** \brief NVM_BD_WRITE_VERIFICATION: Check whether 'Write Verification' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Write Verification'
 **                     status is extracted
 **/
#define NVM_BD_WRITE_VERIFICATION(value) (((value) & NVM_BD_WRITE_VERIFICATION_BIT) != 0U)

#if (defined NVM_BD_STATICBLOCKID_BIT)
#error NVM_BD_STATICBLOCKID_BIT is already defined
#endif
/** \brief mask for 'Static Block Id' bit */
#define NVM_BD_STATICBLOCKID_BIT 0x10000U

#if (defined NVM_BD_USESTATICBLOCKID)
#error NVM_BD_USESTATICBLOCKID is already defined
#endif
/** \brief NVM_BD_USESTATICBLOCKID: Check whether 'Static Block Id' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Static Block Id'
 **                     status is extracted
 **/
#define NVM_BD_USESTATICBLOCKID(value) (((value) & NVM_BD_STATICBLOCKID_BIT) != 0U)

#if (defined NVM_BD_USEMIRROR_BIT)
#error NVM_BD_USEMIRROR_BIT is already defined
#endif
/** \brief mask for 'Use Mirror' bit */
#define NVM_BD_USEMIRROR_BIT 0x20000U

#if (defined NVM_BD_USEMIRROR)
#error NVM_BD_USEMIRROR is already defined
#endif
/** \brief NVM_BD_USEMIRROR: Check whether 'Use Mirror' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Use Mirror'
 **                     status is extracted
 **/
#define NVM_BD_USEMIRROR(value) (((value) & NVM_BD_USEMIRROR_BIT) != 0U)

#if (defined NVM_BD_WRITEALL_BIT)
#error NVM_BD_WRITEALL_BIT is already defined
#endif
/** \brief mask for 'WriteAll enabled' bit */
#define NVM_BD_WRITEALL_BIT 0x40000U

#if (defined NVM_BD_WRITEALL)
#error NVM_BD_WRITEALL is already defined
#endif
/** \brief NVM_BD_WRITEALL: Check whether 'WriteAll' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'WriteAll enable'
 **                     status is extracted
 **/
#define NVM_BD_WRITEALL(value) (((value) & NVM_BD_WRITEALL_BIT) != 0U)

#if (defined NVM_BD_BLOCKSTATUSINFO_BIT)
#error NVM_BD_BLOCKSTATUSINFO_BIT is already defined
#endif
/** \brief mask for 'BlockStatusInfo' enabled bit */
#define NVM_BD_BLOCKSTATUSINFO_BIT  0x80000U

#if (defined NVM_BD_BLOCKSTATUSINFO)
#error NVM_BD_BLOCKSTATUSINFO is already defined
#endif
/** \brief NVM_BD_BLOCKSTATUSINFO: Check whether 'BlockStatusInfo' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'BlockStatusInfo'
 **                     status is extracted
 **/
#define NVM_BD_BLOCKSTATUSINFO(value) (((value) & NVM_BD_BLOCKSTATUSINFO_BIT) != 0U)

#if (defined NVM_BD_USERPROVIDESSPACEFORCRC_BIT)
#error NVM_BD_USERPROVIDESSPACEFORCRC_BIT is already defined
#endif
/** \brief mask for 'UserProvidesSpaceForBlockAndCrc' enabled bit */
#define NVM_BD_USERPROVIDESSPACEFORCRC_BIT  0x100000U

#if (defined NVM_BD_USERPROVIDESSPACEFORCRC)
#error NVM_BD_USERPROVIDESSPACEFORCRC is already defined
#endif
/** \brief NVM_BD_USERPROVIDESSPACEFORCRC: Check whether 'NvMUserProvidesSpaceForBlockAndCrc'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMUserProvidesSpaceForBlockAndCrc'
 **                     status is extracted
 **/
#define NVM_BD_USERPROVIDESSPACEFORCRC(value) (((value) & NVM_BD_USERPROVIDESSPACEFORCRC_BIT) != 0U)

#if (defined NVM_BD_VALIDATEALL_BIT)
#error NVM_BD_VALIDATEALL_BIT is already defined
#endif
/** \brief mask for 'ValidateAll enabled' bit */
#define NVM_BD_VALIDATEALL_BIT 0x200000U

#if (defined NVM_BD_VALIDATEALL)
#error NVM_BD_VALIDATEALL is already defined
#endif
/** \brief NVM_BD_VALIDATEALL: Check whether 'ValidateAll' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'ValidateAll enable'
 **                     status is extracted
 **/
#define NVM_BD_VALIDATEALL(value) (((value) & NVM_BD_VALIDATEALL_BIT) != 0U)

#if (defined NVM_BD_USERAMBLOCKSTATUS_BIT)
#error NVM_BD_USERAMBLOCKSTATUS_BIT is already defined
#endif
/** \brief mask for 'NvMBlockUseSetRamBlockStatus' enabled bit */
#define NVM_BD_USERAMBLOCKSTATUS_BIT  0x400000U

#if (defined NVM_BD_USERAMBLOCKSTATUS)
#error NVM_BD_USERAMBLOCKSTATUS is already defined
#endif
/** \brief NVM_BD_USERAMBLOCKSTATUS: Check whether 'NvMBlockUseSetRamBlockStatus'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMBlockUseSetRamBlockStatus'
 **                     status is extracted
 **/
#define NVM_BD_USERAMBLOCKSTATUS(value) (((value) & NVM_BD_USERAMBLOCKSTATUS_BIT) != 0U)

#if (defined NVM_BD_PRE_WRITE_DATA_COMP_BIT)
#error NVM_BD_PRE_WRITE_DATA_COMP_BIT is already defined
#endif
/** \brief mask for 'NvMPreWriteDataComp' enabled bit */
#define NVM_BD_PRE_WRITE_DATA_COMP_BIT  0x800000U

#if (defined NVM_BD_PRE_WRITE_DATA_COMP)
#error NVM_BD_PRE_WRITE_DATA_COMP is already defined
#endif
/** \brief NVM_BD_PRE_WRITE_DATA_COMP: Check whether 'NvMPreWriteDataComp'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMPreWriteDataComp'
 **                     status is extracted
 **/
#define NVM_BD_PRE_WRITE_DATA_COMP(value) (((value) & NVM_BD_PRE_WRITE_DATA_COMP_BIT) != 0U)

#if (defined NVM_BD_ENCRCCOMP_BIT)
#error NVM_BD_ENCRCCOMP_BIT is already defined
#endif
/** \brief mask for 'NvMBlockUseCRCCompMechanism' enabled bit */
#define NVM_BD_ENCRCCOMP_BIT  0x1000000U

#if (defined NVM_BD_ENCRCCOMP)
#error NVM_BD_ENCRCCOMP is already defined
#endif
/** \brief NVM_BD_ENCRCCOMP: Check whether 'NvMBlockUseCRCCompMechanism'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMBlockUseCRCCompMechanism'
 **                     status is extracted
 **/
#define NVM_BD_ENCRCCOMP(value) (((value) & NVM_BD_ENCRCCOMP_BIT) != 0U)

#if (defined NVM_BD_FIRSTINITALL_BIT)
#error NVM_BD_FIRSTINITALL_BIT is already defined
#endif
/** \brief mask for 'NvMSelectBlockForFirstInitAll' enabled bit */
#define NVM_BD_FIRSTINITALL_BIT  0x2000000U

#if (defined NVM_BD_FIRSTINITALL)
#error NVM_BD_FIRSTINITALL is already defined
#endif
/** \brief NVM_BD_FIRSTINITALL: Check whether 'NvMSelectBlockForFirstInitAll'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMSelectBlockForFirstInitAll'
 **                     status is extracted
 **/
#define NVM_BD_FIRSTINITALL(value) (((value) & NVM_BD_FIRSTINITALL_BIT) != 0U)

#if (defined NVM_BD_AR2011CBK_BIT)
#error NVM_BD_AR2011CBK_BIT is already defined
#endif
/** \brief mask for 'AR2011CBK' enabled bit */
#define NVM_BD_AR2011CBK_BIT  0x4000000U

#if (defined NVM_BD_AR2011CBK)
#error NVM_BD_AR2011CBK is already defined
#endif
/** \brief NVM_BD_AR2011CBK: Check whether 'AR2011CBK'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'AR2011CBK'
 **                     status is extracted
 **/
#define NVM_BD_AR2011CBK(value) (((value) & NVM_BD_AR2011CBK_BIT) != 0U)

#if (defined NVM_BD_CRYPTOHOOKS_BIT)
#error NVM_BD_CRYPTOHOOKS_BIT is already defined
#endif
/** \brief mask for 'NvMEnableBlockCryptoSecurityHandling' enabled bit */
#define NVM_BD_CRYPTOHOOKS_BIT  0x8000000U

#if (defined NVM_BD_CRYPTOHOOKS)
#error NVM_BD_CRYPTOHOOKS is already defined
#endif
/** \brief NVM_BD_CRYPTOHOOKS: Check whether 'NvMEnableBlockCryptoSecurityHandling'
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMEnableBlockCryptoSecurityHandling'
 **                     status is extracted
 **/
#define NVM_BD_CRYPTOHOOKS(value) (((value) & NVM_BD_CRYPTOHOOKS_BIT) != 0U)


/** \brief ************ Bit definitions of the dynamic status variable  *************/

#if (defined NVM_DYN_CHANGE_MASK)
#error NVM_DYN_CHANGE_MASK is already defined
#endif
/** \brief Macro to extract the ChangeFlag flag
 **        from bit 0 of NvM_DynamicStatusType
 **
 **        value 0: RAM data has not been changed during read
 **        value 1: RAM data has been changed during read
 **/
#define NVM_DYN_CHANGE_MASK                0x0001U

#if (defined NVM_DYN_WPF_MASK)
#error NVM_DYN_WPF_MASK is already defined
#endif
/** \brief Macro to extract the WriteProtectionFlag
 **        from bit 1 of NvM_DynamicStatusType
 **
 **        value 0: block is not write protected
 **        value 1: block is write protected
 **/
#define NVM_DYN_WPF_MASK                   0x0002U

#if (defined NVM_DYN_BRVE_MASK)
#error NVM_DYN_BRVE_MASK is already defined
#endif
/** \brief Macro to extract the BlockReadValidErrorFlag
 **        from bit 2 of NvM_DynamicStatusType
 **
 **        value 0: The NVM Block is valid
 **        value 1: The NVM Block is invalidated
 **/
#define NVM_DYN_BRVE_MASK                  0x0004U

#if (defined NVM_DYN_LOCK_MASK)
#error NVM_DYN_LOCK_MASK is already defined
#endif
/** \brief Macro to extract the 'Block Locked' Flag
 **        from bit 3 of NvM_DynamicStatusType
 **
 **        value 0: The RAM block is marked as unlocked.
 **        value 1: The RAM block is marked as locked.
 **/
#define NVM_DYN_LOCK_MASK                  0x0008U

#if (defined NVM_DYN_RDL_MASK)
#error NVM_DYN_RDL_MASK is already defined
#endif
/** \brief Macro to extract the RomDataLoadedFlag
 **        from bit 4 of NvM_DynamicStatusType
 **
 **        value 0: ROM data was not loaded by NvM_RestorBlockDefaults.
 **        value 1: ROM data loaded by NvM_RestorBlockDefaults.
 **/
#define NVM_DYN_RDL_MASK                   0x0010U

#if (defined NVM_DYN_WPPF_MASK)
#error NVM_DYN_WPPF_MASK is already defined
#endif
/** \brief Macro to extract the WriteProtectionPermanentFlag
 **        from bit 5 of NvM_DynamicStatusType
 **
 **        value 0: permanent write protection disabled.
 **        value 1: permanent write protection enabled.
 **/
#define NVM_DYN_WPPF_MASK                  0x0020U

#if (defined NVM_ERBF_MASK)
#error NVM_ERBF_MASK is already defined
#endif
/** \brief Macro to extract the ExtentedRuntimeBlockFlag
 **        from bit 6 of NvM_DynamicStatusType
 **
 **        value 0: block address not changed in case Dynamic Configuration is enabled
 **        value 1: block address is changed in case Dynamic Configuration is enabled
 **/
#define NVM_ERBF_MASK                      0x0040U

#if (defined NVM_DYN_REDUNDANCY_MASK)
#error NVM_DYN_REDUNDANCY_MASK is already defined
#endif
/** \brief Macro to extract the 'Loss of Redundancy' Flag
 **        from bit 7 of NvM_DynamicStatusType
 **
 **        value 0: Loss of Redundancy.
 **        value 1: No Loss of Redundancy.
 **/
#define NVM_DYN_REDUNDANCY_MASK                 0x0080U

#if (defined NVM_DYN_CCU_MASK)
#error NVM_DYN_CCU_MASK is already defined
#endif
/** \brief Macro to extract the CrcCheckedUnequalFlag
 **        from bit 8 of NvM_DynamicStatusType
 **
 **        value 0: CRC match
 **        value 1: CRC mismatch
 **/
#define NVM_DYN_CCU_MASK                   0x0100U

#if (defined NVM_DYN_UPRB_MASK)
#error NVM_DYN_UPRB_MASK is already defined
#endif
/** \brief Macro to extract the UsePermanentRamBlock
 **        from bit 9 of NvM_DynamicStatusType
 **
 **        value 0: Current service uses the Permanent RAM Block
 **        value 1: Current service uses the Temporary RAM Block.
 **/
#define NVM_DYN_UPRB_MASK                  0x0200U

#if (defined NVM_DYN_BRBI_MASK)
#error NVM_DYN_BRBI_MASK is already defined
#endif
/** \brief Macro to extract the BlockReadBlockInconsistentFlag
 **        from bit 10 of NvM_DynamicStatusType
 **
 **        value 0: MemIf job result is unequal to MEMIF_BLOCK_INCONSISTENT
 **        value 1: MemIf job result is equal to MEMIF_BLOCK_INCONSISTENT
 **/
#define NVM_DYN_BRBI_MASK                  0x0400U

#if (defined NVM_DYN_WBID_MASK)
#error NVM_DYN_WBID_MASK is already defined
#endif
/** \brief Macro to extract the WrongBlockIdFlag
 **        from bit 11 of NvM_DynamicStatusType
 **
 **        value 0: Static Block Id check has been successful
 **        value 1: Static Block Id check has failed
 **/
#define NVM_DYN_WBID_MASK                  0x0800U

#if (defined NVM_DYN_MIRROR_MASK)
#error NVM_DYN_MIRROR_MASK is already defined
#endif
/** \brief Macro to extract the 'Use Mirror' Flag
 **        from bit 12 of NvM_DynamicStatusType
 **
 **        value 0: User RAM block or Internal buffer shall be used.
 **        value 1: NvM Mirror shall be used to read and write data.
 **/
#define NVM_DYN_MIRROR_MASK                0x1000U

#if (defined NVM_DYN_SRBSC_MASK)
#error NVM_DYN_SRBSC_MASK is already defined
#endif
/** \brief Macro to extract the SetRamBlockStatusChangedFlag
 **        from bit 13 of NvM_DynamicStatusType
 **
 **        value 0: SetRamBlockStatus was not called or it was called with
 **                 BlockChanged=FALSE
 **        value 1: SetRamBlockStatus was called with BlockChanged=TRUE
 **
 ** Note: SetRamBlockStatusChangedFlag is merely set and cleared.
 ** The value of this flag is not evaluated within the code.
 ** This status information might be useful for integration and debugging.
 **/
#define NVM_DYN_SRBSC_MASK            0x2000U

#if (defined NVM_DYN_LLRF_MASK)
#error NVM_DYN_LLRF_MASK is already defined
#endif
/** \brief Macro to extract failure in the lower layer
 **        from bit 14 of NvM_DynamicStatusType
 **
 **        value 0: Lower layer did not report failure
 **        value 1: Lower layer reported failure
 **/
#define NVM_DYN_LLRF_MASK                  0x4000U

#if (defined NVM_DYN_WBORF_MASK)
#error NVM_DYN_WBORF_MASK is already defined
#endif
/** \brief Macro to tell if a WriteBlockOnce Block is read or not
 **        from bit 15 of NvM_DynamicStatusType
 **
 **        value 0: Block is not read yet
 **        value 1: A Read request for this block is finished whether it succeeded or failed
 **/
#define NVM_DYN_WBORF_MASK                  0x8000U


/** \brief ************ Bit definitions of NvMExtendedStatus *************************/

#if (defined NVM_ES_ADVANCED_RECOVERY_MASK)
#error NVM_ES_ADVANCED_RECOVERY_MASK is already defined
#endif
/** \brief Macro to extract bit 0 of NvMExtendedStatus which indicates whether
 **        block data could be recovered from redundant block or ROM block.
 **        value 0: Block could not be recovered
 **        value 1: Block could be recovered from redundant or ROM block.
 **/
#define NVM_ES_ADVANCED_RECOVERY_MASK        0x01U

#if (defined NVM_ES_RAM_BLOCK_CRC_CALC_MASK)
#error NVM_ES_RAM_BLOCK_CRC_CALC_MASK is already defined
#endif
/** \brief Macro to extract bit 1 of NvMExtendedStatus which indicates whether
 **        RAM block CRC shall be calculated.
 **        value 0: RAM Block CRC could not be calculated
 **        value 1: RAM Block CRC could be calculated.
 **/
#define NVM_ES_RAM_BLOCK_CRC_CALC_MASK        0x02U

#if (defined NVM_ES_REDUNDANT_ERROR_MASK)
#error NVM_ES_REDUNDANT_ERROR_MASK is already defined
#endif
/** \brief Macro to extract bit 2 of NvMExtendedStatus which indicates whether
 **        Native block or redundant block contains invalid data.
 **        value 0: Native block is corrupt
 **        value 1: Redundant block is corrupt
 **/
#define NVM_ES_REDUNDANT_ERROR_MASK          0x04U

#if (defined NVM_ES_REDUNDANT_CRC_ERROR_MASK)
#error NVM_ES_REDUNDANT_CRC_ERROR_MASK is already defined
#endif
/** \brief Macro to extract bit 3 of NvMExtendedStatus which indicates whether
 **        both copies of a redundant block were read but with different CRCs.
 **        value 0: CRC comparison OK
 **        value 1: CRC comparison failed
 **/
#define NVM_ES_REDUNDANT_CRC_ERROR_MASK      0x08U

#if (defined NVM_ES_READ_REDUNDANT_MASK)
#error NVM_ES_READ_REDUNDANT_MASK is already defined
#endif
/** \brief Macro to extract bit 4 of NvMExtendedStatus which indicates if a
 **        read operation has been started while writing a redundant block.
 **        value 0: No read operation started for writing redundant block
 **        value 1: A read operation started for writing redundant block
 **/
#define NVM_ES_READ_REDUNDANT_MASK           0x10U

#if (defined NVM_ES_WRITE_VERIFICATION_MASK)
#error NVM_ES_WRITE_VERIFICATION_MASK is already defined
#endif
/** \brief Macro to extract bit 5 of NvMExtendedStatus which indicates if a
 **        read operation for write verify has been started.
 **        value 0: No read operation started for write verification
 **        value 1: A read operation started for write verification
 **/
#define NVM_ES_WRITE_VERIFICATION_MASK      0x20U

#if (defined NVM_ES_PRE_WRITE_DATA_COMP_MASK)
#error NVM_ES_PRE_WRITE_DATA_COMP_MASK is already defined
#endif
/** \brief Macro to extract bit 6 of NvMExtendedStatus which indicates if a
 **        read operation for pre write verify has been started.
 **        value 0: No read operation started for pre write data comparison
 **        value 1: A read operation started for pre write data comparison
 **/
#define NVM_ES_PRE_WRITE_DATA_COMP_MASK      0x40U

#if (defined NVM_ES_MULTICORE_LOCK_MASK)
#error NVM_ES_MULTICORE_LOCK_MASK is already defined
#endif
/** \brief Macro to extract bit 7 of NvMExtendedStatus which indicates if a
 **        multicore operation is ongoing.
 **/
#define NVM_ES_MULTICORE_LOCK_MASK      0x80U

/**  \brief ************ Bit definitions of the global generic status byte ***********/

#if (defined NVM_GENERIC_INIT_FLAG_MASK)
#error NVM_GENERIC_INIT_FLAG_MASK is already defined
#endif
/** \brief Init flag
 **        Macro to extract bit 0 of NvM_GlobalGenericStatus
 **        Indicates whether NvM module has been initialized
 **        value 0: NvM not initialized
 **        value 1: NvM initialized
 **/
#define NVM_GENERIC_INIT_FLAG_MASK           0x0001U

#if (defined NVM_GENERIC_CWA_MASK)
#error NVM_GENERIC_CWA_MASK is already defined
#endif
/** \brief Cancel Write All flag
 **        Macro to extract bit 1 of NvM_GlobalGenericStatus
 **        Indicates whether NvM_CancelWriteAll was called
 **        value 0: NvM_WriteAll() must NOT be cancelled
 **        value 1: NvM_WriteAll() must be cancelled
 **/
#define NVM_GENERIC_CWA_MASK                 0x0002U

#if (defined NVM_GENERIC_MFP_MASK)
#error NVM_GENERIC_MFP_MASK is already defined
#endif
/** \brief Main Function Processing flag
 **        Macro to extract bit 2 of NvM_GlobalGenericStatus
 **        Indicates whether main function is being processed
 **        value 0: NvM_Mainfunction is currently not running
 **        value 1: NvM_Mainfunction is currently running
 **/
#define NVM_GENERIC_MFP_MASK                 0x0004U

#if (defined NVM_GENERIC_DPM_MASK)
#error NVM_GENERIC_DPM_MASK is already defined
#endif
/** \brief Polling Mode Ignore flag
 **        Macro to extract bit 3 of NvM_GlobalGenericStatus
 **        Indicates whether polling mode is enabled
 **        value 0: Polling Mode enabled  --> not ignored
 **        value 1: Polling Mode disabled --> ignore
 **/
#define NVM_GENERIC_DPM_MASK                 0x0008U

#if (defined NVM_GENERIC_DC_MASK)
#error NVM_GENERIC_DC_MASK is already defined
#endif
/** \brief Dynamic Cofiguration flag
 **        Macro to extract bit 4 of NvM_GlobalGenericStatus
 **        Indicates whether dynamic configuration must be applied
 **        value 0: Dynamic Configuration must NOT be applied by ReadAll
 **        value 1: Dynamic Configuration must be applied by ReadAll
 **/
#define NVM_GENERIC_DC_MASK                  0x0010U

#if (defined NVM_GENERIC_MRKJP_MASK)
#error NVM_GENERIC_MRKJP_MASK is already defined
#endif
/** \brief Multi Request Keep Job Pending flag
 **        Macro to extract bit 5 of NvM_GlobalGenericStatus
 **        Indicates whether the single block request must be kept pending
 **        value 0: A multi block request must set the ErrorStatus to
 **                 NvM_GlobalErrorStatus after a single block
 **                 was processed.
 **        value 1: A multi block request must keep the value of ErrorStatus
 **                 by NVM_REQ_PENDING after a single block was processed.
 **                 was processed. This happens in case a single block
 **                 request was inserted into the queue while a multi block
 **                 request is processing.
 **/
#define NVM_GENERIC_MRKJP_MASK               0x0020U

#if (defined NVM_GENERIC_CANCEL_MASK)
#error NVM_GENERIC_CANCEL_MASK is already defined
#endif
/** \brief Block request Canceled Flag
 **        Macro to extract bit 6 of NvM_GlobalGenericStatus
 **        Indicates that during a multi-block request, a single block request
 **        for the same block is present in the queue, but it must be canceled.
 **        Therefore, after the block was processed by NvM_WriteAll() or NvM_ReadAll()
 **        the ErrorStatus must remain NVM_REQ_CANCELED.
 **/
#define NVM_GENERIC_CANCEL_MASK              0x0040U

#if (defined NVM_WRITE_ALL_PREVENTED_MASK)
#error NVM_WRITE_ALL_PREVENTED_MASK is already defined
#endif
/** \brief Block request Canceled Flag
 **        Macro to extract bit 7 of NvM_GlobalGenericStatus
 **        Indicates that during a NvM_WriteAll request, a NvM_CancelWriteAll
 **        was received, and this block was prevented from being written.
 **        Restore status in case a new NvM_WriteAll later.
 **/
#define NVM_WRITE_ALL_PREVENTED_MASK              0x0080U

#if (defined NVM_WRITE_REDUNDANT_MASK)
#error NVM_WRITE_REDUNDANT_MASK is already defined
#endif
/** \brief Block request Canceled Flag
 **        Macro to extract bit 8 of NvM_GlobalGenericStatus
 **        Indicates that current write is first of redundant blocks
 **/
#define NVM_WRITE_REDUNDANT_MASK              0x0100U

/**  \brief ****************  Miscellaneous macros  **********************************/

#if (defined NVM_REQUEST_INTERIM_RESULT)
#error NVM_REQUEST_INTERIM_RESULT is already defined
#endif
/** \brief Defines the variable which is used to store the interim result of
 **        a multi block request. The location
 **        NvM_AdminBlockTable[0].NvMDatasetBlockIndex can be used for this
 **        purpose because for block the block type is obsolete and not used.
 **/
#define NVM_REQUEST_INTERIM_RESULT \
        NvM_AdminBlockTable[0].NvMDatasetBlockIndex

#if (defined NVM_REDUNDANT_ERROR_COUNTER)
#error NVM_REDUNDANT_ERROR_COUNTER is already defined
#endif
/** \brief Defines the variable which is used to store
 **        the interim result of a redundant block request.
 **        The location NvM_AdminBlockTable[0].NvMValid can be used for this
 **        purpose because for block 0 the block validattion is obsolete and
 **        not used.
 **/
#define NVM_REDUNDANT_ERROR_COUNTER \
        NvM_AdminBlockTable[NVM_BLOCK_MULTI].NvMValid

#if (defined NVM_BLOCK_USE_32BITCRC_MASK)
#error NVM_BLOCK_USE_32BITCRC_MASK is already defined
#endif
/** \brief Masks the 32Bit CRC type used by a block.
 **/
#define NVM_BLOCK_USE_32BITCRC_MASK          0x05U

#if (defined NVM_BLOCK_USE_16BITCRC_MASK)
#error NVM_BLOCK_USE_16BITCRC_MASK is already defined
#endif
/** \brief Masks the 16Bit CRC type used by a block.
 **/
#define NVM_BLOCK_USE_16BITCRC_MASK          0x01U

#if (defined NVM_BLOCKID_LENGTH)
#error NVM_BLOCKID_LENGTH is already defined
#endif
/** \brief Defines the length of the Static Block Id.
 **/
#define NVM_BLOCKID_LENGTH                   0x02U

#if (defined NVM_NO_API_ID)
#error NVM_NO_API_ID is already defined
#endif
/** \brief Defines API ID in case no service is currently being processed.
 **/
#define NVM_NO_API_ID                        0xFFU

#if (defined NVM_NUMBER_OF_ASYNC_FUNCTIONS)
#error NVM_NUMBER_OF_ASYNC_FUNCTIONS is already defined
#endif
/** \brief Defines the total number of implemented asynchronous API
 **        functions.
 **/
#define NVM_NUMBER_OF_ASYNC_FUNCTIONS        6U

#if (defined NVM_NUMBER_OF_FUNCTIONS)
#error NVM_NUMBER_OF_FUNCTIONS is already defined
#endif
/** \brief Defines the total number of NvM API functions.
 **/
#define NVM_NUMBER_OF_FUNCTIONS             15U

/** \brief **********************  Block 0, Block 1 and Block 2 IDs *****************/

#if (defined NVM_MULTI_REQUEST_BLOCK_0_ID)
#error NVM_MULTI_REQUEST_BLOCK_0_ID is already defined
#endif
/** \brief Defines the block ID of block 0 used to manage multi block
 **        requests.
 **/
#define NVM_MULTI_REQUEST_BLOCK_0_ID   0U

#if (defined NVM_BLOCK_CONFIG_ID)
#error NVM_BLOCK_CONFIG_ID is already defined
#endif
/** \brief Defines the block ID of the block 1 used to store the
 **        configuration ID.
 **/
#define NVM_BLOCK_CONFIG_ID            1U

#if (defined NVM_FIRST_USER_BLOCK_2_ID)
#error NVM_FIRST_USER_BLOCK_2_ID is already defined
#endif
/** \brief Defines the block ID of the first user block. The blocks 0 and 1
 **        are reserved for NvM internal management.
 **/
#define NVM_FIRST_USER_BLOCK_2_ID      2U

#if (defined NvM_WriteState)
#error NvM_WriteState is already defined
#endif
/** \brief Define which marks that the next post crypto state will be a write operation.
 **/
#define NvM_WriteState      1U

#if (defined NvM_ReadState)
#error NvM_ReadState is already defined
#endif
/** \brief Define which marks that the next post crypto state will be a read operation.
 **/
#define NvM_ReadState      2U

#if (defined NVM_BLOCK_IMMEDIATE_PRIORITY)
#error NVM_BLOCK_IMMEDIATE_PRIORITY is already defined
#endif
/** \brief Defines "immediate priority" of blocks. blocks with priority "0"
 **        are considered "immediate priority" blocks and are given
 **        precedence compared to blocks with "standard prioriry" ( priority > 0 )
 **        while proessing requests.
 **/
#define NVM_BLOCK_IMMEDIATE_PRIORITY   0U

#if (defined NVM_QUEUE_INDEX_RESET)
#error NVM_QUEUE_INDEX_RESET is already defined
#endif
/** \brief Defines "Queue Empty" condition of standard and immediate queues.
 **        Queue index is initialized to this value.
 **        When the first request is inserted into the queue, this value is reset to 0
 **        and is incremented thereafter for each enqueued requests.
 **/
#define NVM_QUEUE_INDEX_RESET   0xFFFFU

#if (NVM_INTERNAL_BUFFER_SIZE != 0U)

#if (defined NVM_GET_INTERNAL_BUFFER)
#error NVM_GET_INTERNAL_BUFFER is already defined
#endif
/** \brief Returns address of NVM internal buffer for temporary block data/crc storage.
 ** \return Starting address of NVM internal buffer
 **/
#define NVM_GET_INTERNAL_BUFFER() ((NvM_PtrToApplDataType)NvM_InternalBuffer)

#endif /* #if (NVM_INTERNAL_BUFFER_SIZE != 0U) */

#if (NVM_MIRROR_SIZE != 0U)

#if (defined NVM_GET_MIRROR_ADDR)
#error NVM_GET_MIRROR_ADDR is already defined
#endif
/** \brief Returns address of NVM Mirror when explicit synchronization is enabled.
 ** \return Starting address of NVM Mirror
 **/
#define NVM_GET_MIRROR_ADDR() NVM_GET_INTERNAL_BUFFER()

#endif /* #if (NVM_MIRROR_SIZE != 0U) */

#if (defined NVM_STATIC_BLOCKID)
#error NVM_STATIC_BLOCKID is already defined
#endif
/** \brief Returns the address of the static block id for the current block.
 ** \return Address of the static block id for the current block.
 **/
#define NVM_STATIC_BLOCKID()  ((NvM_PtrToConstType)&NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockIdentifier)

#if (defined NVM_STD_QUEUE_EMPTY)
#error NVM_STD_QUEUE_EMPTY is already defined
#endif
/** \brief Checks if the standard job processing queue is empty.
 ** \return Empty status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_EMPTY() \
  ( NvM_Queue_IndexStandard == NVM_QUEUE_INDEX_RESET )

#if (defined NVM_IMMEDIATE_QUEUE_EMPTY)
#error NVM_IMMEDIATE_QUEUE_EMPTY is already defined
#endif
/** \brief Checks if the immediate job processing queue is empty.
 ** \return Empty status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_EMPTY() \
  ( NvM_Queue_CountImmediate == 0U )

#if (defined NVM_STD_QUEUE_NOT_EMPTY)
#error NVM_STD_QUEUE_NOT_EMPTY is already defined
#endif
/** \brief Checks if the standard job processing queue is NOT empty.
 ** \return Not-empty status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_NOT_EMPTY() \
  ( NvM_Queue_IndexStandard != NVM_QUEUE_INDEX_RESET )

#if (defined NVM_IMMEDIATE_QUEUE_NOT_EMPTY)
#error NVM_IMMEDIATE_QUEUE_NOT_EMPTY is already defined
#endif
/** \brief Checks if the immediate job processing queue is NOT empty.
 ** \return Not-empty status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_NOT_EMPTY() \
  ( NvM_Queue_CountImmediate != 0U )

#if (defined NVM_STD_QUEUE_NOT_FULL)
#error NVM_STD_QUEUE_NOT_FULL is already defined
#endif
/** \brief Checks if the standard job processing queue is NOT full.
 **        (not including the reserved entry for for multiblock requests).
 ** \return Not-full status of the standard job processing queue
 **/
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
#define NVM_STD_QUEUE_NOT_FULL() \
  ( NvM_Queue_IndexStandard + NvM_Std_Initiated_On_Satellite < ( NVM_SIZE_STANDARD_JOB_QUEUE - 2U ) )
#else
#define NVM_STD_QUEUE_NOT_FULL() \
  ( NvM_Queue_IndexStandard < ( NVM_SIZE_STANDARD_JOB_QUEUE - 2U ) )
#endif /* (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON) */

#if (defined NVM_STD_QUEUE_NOT_FULL_MULTI)
#error NVM_STD_QUEUE_NOT_FULL_MULTI is already defined
#endif
/** \brief Checks if the standard job processing queue is NOT full
 **        (including the reserved entry for for multiblock requests).
 ** \return Not-full status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_NOT_FULL_MULTI() \
  ( NvM_Queue_IndexStandard < ( NVM_SIZE_STANDARD_JOB_QUEUE - 1U ) )

#if ( ( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) )
#if (defined NVM_IMMEDIATE_QUEUE_NOT_FULL)
#error NVM_IMMEDIATE_QUEUE_NOT_FULL is already defined
#endif
/** \brief Checks if the immediate job processing queue is NOT full.
 ** \return Not-full status of the immediate job processing queue
 **/
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
#define NVM_IMMEDIATE_QUEUE_NOT_FULL() \
  ( NvM_Queue_CountImmediate + NvM_Imm_Initiated_On_Satellite < NVM_SIZE_IMMEDIATE_JOB_QUEUE )
#else
#define NVM_IMMEDIATE_QUEUE_NOT_FULL() \
  ( NvM_Queue_CountImmediate < NVM_SIZE_IMMEDIATE_JOB_QUEUE )
#endif /* (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON) */
#endif /* ( ( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) ) */

#if (defined NVM_IMMEDIATE_QUEUE_MULTIPLE_JOBS)
#error NVM_IMMEDIATE_QUEUE_MULTIPLE_JOBS is already defined
#endif
/** \brief Checks if the immediate job processing queue contains
 **        more than one request.
 ** \return Multiple-requests status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_MULTIPLE_JOBS() (NvM_Queue_CountImmediate > 1U)

#if (defined NVM_STD_QUEUE_MULTIPLE_JOBS)
#error NVM_STD_QUEUE_MULTIPLE_JOBS is already defined
#endif
/** \brief Checks if the standard job processing queue contains
 **        more than one request.
 ** \return Multiple-requests status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_MULTIPLE_JOBS() (NVM_STD_QUEUE_NOT_EMPTY() && (NvM_Queue_IndexStandard > 0U))

#if (defined NVM_IMMEDIATE_QUEUE_BLOCKID)
#error NVM_IMMEDIATE_QUEUE_BLOCKID is already defined
#endif
/** \brief Represents the Block Identifier of the immediate request
 **        to be or currently being processed.
 **/
#define NVM_IMMEDIATE_QUEUE_BLOCKID \
  ( NvM_Queue_Immediate[NvM_Queue_IndexImmediate].NvMBlockDescriptorIndex )

#if (defined NVM_STD_QUEUE_BLOCKID)
#error NVM_STD_QUEUE_BLOCKID is already defined
#endif
/** \brief Represents the Block Identifier of the standard request
 **        to be or currently being processed.
 **/
#define NVM_STD_QUEUE_BLOCKID \
  (NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockDescriptorIndex)

#if (defined NVM_IMMEDIATE_QUEUE_UP)
#error NVM_IMMEDIATE_QUEUE_UP is already defined
#endif
/** \brief Advance the Immediate Queue by one after inserting a new element
 **
 **        The macro increments the value of Immediate Queue Count by 1
 **        after a new job request is queued in the Queue.
 **/
#define NVM_IMMEDIATE_QUEUE_UP()                                         \
  do                                                                     \
  {                                                                      \
    NvM_Queue_CountImmediate++;                                          \
  } while (0)

#if (defined NVM_IMMEDIATE_QUEUE_DOWN)
#error NVM_IMMEDIATE_QUEUE_DOWN is already defined
#endif
/** \brief Remove an element from the Immediate Queue
 **
 **        The macro circularly increments the value of Immediate Queue Front by 1
 **        and decreases Immediate Queue Count by 1 so that the job request
 **        at Immediate Queue Front is removed from the queue.
 **/
#define NVM_IMMEDIATE_QUEUE_DOWN()                                                              \
  do                                                                                            \
  {                                                                                             \
    NvM_Queue_IndexImmediate = (NvM_Queue_IndexImmediate + 1U) % NVM_SIZE_IMMEDIATE_JOB_QUEUE;  \
    NvM_Queue_CountImmediate--;                                                                 \
  } while (0)

#if (defined NVM_IMMEDIATE_QUEUE_GET_INDEX_MOD_SIZE)
#error NVM_IMMEDIATE_QUEUE_GET_INDEX_MOD_SIZE is already defined
#endif
/** \brief Returns the index of the element passed as argument (x)
 **        from the immediate queue, wrapped around the queue size
 **/
#define NVM_IMMEDIATE_QUEUE_GET_INDEX_MOD_SIZE(x)  ((x) % NVM_SIZE_IMMEDIATE_JOB_QUEUE)

#if (defined NVM_STANDARD_QUEUE_UP)
#error NVM_STANDARD_QUEUE_UP is already defined
#endif
/** \brief Advance the Standard Queue by one position
 **
 **        The macro increments the value of Standard Queue Index by 1
 **        so that a new job request can be queued in the Index position.
 **        In case of Index is uninitialized(0xFF), it is set to 0.
 **/
#define NVM_STANDARD_QUEUE_UP()                                          \
  do                                                                     \
  {                                                                      \
    NvM_Queue_IndexStandard = (uint16)( NvM_Queue_IndexStandard + 1U );   \
  } while (0)

#if (defined NVM_STANDARD_QUEUE_DOWN)
#error NVM_STANDARD_QUEUE_DOWN is already defined
#endif
/** \brief Reduce the Standard Queue Index by 1
 **
 **        The macro decrements the value of Standard Queue Index by 1
 **        so that the job request at Index position is removed from the queue.
 **        When all elements are removed, Index is set to uninitialized(0xFF).
 **/
#define NVM_STANDARD_QUEUE_DOWN()                                        \
  do                                                                     \
  {                                                                      \
    NvM_Queue_IndexStandard = (uint16)( NvM_Queue_IndexStandard - 1U );   \
  } while (0)

/*==================[type definitions]======================================*/

#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
/** \brief User configuration information for NvM blocks
 **
 ** Each configured block has assigned one realization of this type. */
typedef struct
{
#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a eraseNvBlock job */
  NvM_SchMJobEraseNvBlockFctPtr eraseNvBlock;

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a invalidateNvBlock job */
  NvM_SchMJobInvalidateNvBlockFctPtr invalidateNvBlock;
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a readBlock job */
  NvM_SchMJobReadBlockFctPtr readBlock;

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a readPRAMBlock job */
  NvM_SchMJobReadPRAMBlockFctPtr readPRAMBlock;

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a restoreBlockDefaults job */
  NvM_SchMJobRestoreBlockDefaultsFctPtr restoreBlockDefaults;

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a restorePRAMBlockDefaults job */
  NvM_SchMJobRestorePRAMBlockDefaultsFctPtr restorePRAMBlockDefaults;

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a writeBlock job */
  NvM_SchMJobWriteBlockFctPtr writeBlock;

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a writePRAMBlock job */
  NvM_SchMJobWritePRAMBlockFctPtr writePRAMBlock;
#endif /* (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

  /** \brief pointer to the SchM call that a certain NvM satellite has to execute in order to
   * tell the NvM master to queue a cancelJobs job */
  NvM_SchMJobCancelJobsFctPtr cancelJobs;
} NvM_SchMJobCallsType;

/** \brief User configuration information for NvM-SchM-NvM communication
 **
 ** Each partition that a NvM satellite is mapped to has assigned one realization of this type. */
typedef struct
{
  /** \brief Gives the SchM job calls from a particular Satellite to Master*/
  CONSTP2CONST(NvM_SchMJobCallsType, TYPEDEF, NVM_APPL_CONST) schMJobCallsToMaster;

  /** \brief It is called by Master to let Satellite know that the job is finished and it can call the single block callback. */
  NvM_SchMJobEndCallbackFctPtr satelliteJobEndNotification;

  /** \brief Os application identifier helps the mapping to the corresponding satellite SchM calls */
  os_applicationid_t NvM_OsApplicationId;

} NvM_SchMInterPartitionCallsType;

#endif /* (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON) */
/** \brief User configuration information for NvM blocks
 **
 ** Each configured block has assigned one realization of this type. */
typedef struct
{
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  /** \brief pointer to initialization function. Can be used alternatively to copy
   ** default data into the RAM block. */
  CONSTP2CONST(NvM_CallbackFctPtr, TYPEDEF, NVM_APPL_CONST) initBlockCallback;


  /** \brief error status call back function. Called after an asynchronous request has
   ** finished. */
  CONSTP2CONST(NvM_CallbackFctPtr, TYPEDEF, NVM_APPL_CONST) singleBlockCallback;

#if (NVM_SYNC_MECHANISM == STD_ON)

  /**  \brief Pointer to NvM to RAM copy callback function. Called by NvM in order to let
   **         the application copy data from NvM module's mirror to RAM block.
   **/
  CONSTP2CONST(NvM_NvToRamCopyCallbackType, TYPEDEF, NVM_APPL_CONST) readRamFromNvCallback;

  /**  \brief Pointer to RAM to NvM copy callback function. Called by NvM in order to let
   **         the application copy data from RAM block to NvM module's mirror.
   **/
  CONSTP2CONST(NvM_RamToNvCopyCallbackType, TYPEDEF, NVM_APPL_CONST) writeRamToNvCallback;

#endif

#else
  /** \brief pointer to initialization function. Can be used alternatively to copy
   ** default data into the RAM block. */
  NvM_CallbackFctPtr initBlockCallback;


  /** \brief error status call back function. Called after an asynchronous request has
   ** finished. */
  NvM_CallbackFctPtr singleBlockCallback;

#if (NVM_SYNC_MECHANISM == STD_ON)

  /**  \brief Pointer to NvM to RAM copy callback function. Called by NvM in order to let
   **         the application copy data from NvM module's mirror to RAM block.
   **/
  NvM_NvToRamCopyCallbackType readRamFromNvCallback;

  /**  \brief Pointer to RAM to NvM copy callback function. Called by NvM in order to let
   **         the application copy data from RAM block to NvM module's mirror.
   **/
  NvM_RamToNvCopyCallbackType writeRamToNvCallback;
#endif

#endif /* (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON) */

  /** \brief start address of the user data ROM block which contains the default
   ** data */
  P2CONST(void, TYPEDEF, NVM_APPL_CONST) romBlockDataAddress;

  /** \brief  start address of the permanent user data RAM block. */
  P2VAR(void, TYPEDEF, NVM_APPL_DATA) ramBlockDataAddress;

  /** \brief Bit encoded NV block description
   *
   * Bit pattern: xxxx xxxx tpuk qwsd vebi iiam msow rccc
   * - c: crcType, enum: no crc, CRC8, CRC16, CRC32
   * - r: RAM block CRC, boolean
   * - w: write protection, boolean
   * - o: write once, boolean
   * - s: resistant to changed SW, boolean
   * - m: management type, enum: native, redundant, dataset
   * - a: read all, boolean
   * - i: deviceId, 0-7
   * - b: use internal buffer, boolean
   * - e: enable advanced error recovery, boolean
   * - v: enable write verification, boolean
   *
   * - d: enable static block id check, boolean
   * - s: use mirror for explicit synchronization, boolean
   * - w: write all enabled, boolean
   * - q: block status info enabled, boolean
   * - k: user space for block crc, boolean
   * - u: crc comparison mechanism, boolean
   * - p: enable ram block status, boolean
   * - t: pre write data comparison mechanism, boolean
   *
   * Only use NVM_BD_*() macros to access contents.
   */
  uint32 blockDesc;

  /** \brief length of the user data in bytes. */
  uint16 nvBlockLength;

  /** \brief block base number. */
  uint16 nvBlockBaseNum;
   /** \brief block Identifier. */
  uint16 nvBlockIdentifier;

  /** \brief Index of the stored CRC(for the RAM data) for the block. */
  uint16 ramBlockCrcIndex;

#if (NVM_CRC_COMP_MECH == STD_ON)
  /** \brief Index of the stored CRC(for the NV data) for the block. */
  uint16 nvBlockCrcIndex;
#endif

#if (NVM_WRITE_VERIFICATION == STD_ON)
  /** \brief NV block verification data size */
  uint16 verifyDataSize;
#endif

#if (NVM_PRE_WRITE_DATA_COMP == STD_ON)
  /** \brief Pre Write NV block data comparison data size */
  uint16 preWriteDataComparisonDataSize;
#endif

#if (NVM_BLOCK_CHECK_ENABLED == STD_ON)
  /** \brief Index of the corresponding block index in the Block Check admin data array */
  uintBC bcBlockIdx;
#endif

  /** \brief number of user data areas. 1 for native blocks, 2 for redundant blocks, n
   ** for dataset blocks */
  uint8 nvBlockNum;

  /** \brief number of user ROM Blocks */
  uint8 romBlockNum;
#if ( NVM_JOB_PRIORITIZATION == STD_ON )
  /* Priority of the NvM blocks. Priority is classified into "immediate
   * priority" and "standard priority". Immediate priority jobs have priority
   * over standard priority jobs. All standard priority jobs are processed in
   * first-come-first-served manner. i.e. no prioritisation is done for
   * several standard priority jobs which are in the queue at a time */
  uint8 blockJobPriority;
#endif

#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
  /** \brief Maximum number of block write retry */
  uint8 writeRetryLimit;
#endif

#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
  /** \brief Maximum number of times the read operation is retried */
  uint8 readRetryLimit;
#endif
#if (NVM_CRYPTO_HOOKS == STD_ON)
  /** \brief Crypto Extra Info Size */
  uint8 CryptoExtraInfoSize;
#endif
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  /** \brief Id of the Os Application that references partition */
  os_applicationid_t OsAppId;
#endif
} NvM_BlockDescriptorType;

#if (NVM_BLOCK_CHECK_ENABLED == STD_ON)
/**  \brief Defines the elements of the Block Check configuration.
 **/
typedef struct
{
  /** \brief Block index in Block Descriptor Table of the BC element**/
  uint16 BlockIndex;
  /** \brief Minimum delay between 2 BC **/
  uint8 BcDelayCounter;
  /** \brief BC descriptor
   **        bit0  - StartAfterReset
   **        bit1  - BcCrcCompare
   **        bit2  - BcRamCompare
   **        bit3  - BcCopiesCompare
   **        bit4  - EnAutoRepair
   **        bit5  - EnableAPIisON
   **/
  uint8 BcBlkDescriptor;
}NvM_BcCfgDataType;
#endif
/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/
/* To be moved somewere else in this file */
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)

/* General MultiPartition flags */
#define NVM_QUEUES_PROTECT_MASK                    ((NvM_Atomic_value_t)0x00000001)
#define NVM_CRC_QUEUE_PROTECT_MASK                 ((NvM_Atomic_value_t)0x00000002)
#define NVM_SATELLITE_MULTIBLOCK_FINALIZING_MASK   ((NvM_Atomic_value_t)0x00000002)

/* Bsw distribution flags used for direct NvM inter-partition/inter-core communication,
 * between NvM partition distributed instances. */

/* Parallel accessing protection flags */
#define NVM_ASYNC_ASYNC_PROTECT_MASK       ((NvM_Atomic_value_t)0x00000100)
#define NVM_SYNC_ASYNC_PROTECT_MASK        ((NvM_Atomic_value_t)0x00000200)
#define NVM_SYNC_SYNC_PROTECT_MASK         ((NvM_Atomic_value_t)0x00000400)
#define NVM_BLOCK_CANCEL_LOCK_MASK         ((NvM_Atomic_value_t)0x00000800)

/* Satellite job related flags */
#define NVM_SATELLITE_JOB_ACCEPTED_MASK             ((NvM_Atomic_value_t)0x00000001)
#define NVM_SATELLITE_BGND_CRC_QUEUED_MASK          ((NvM_Atomic_value_t)0x00000002)
#define NVM_SATELLITE_JOB_TO_BE_CANCELLED_MASK      ((NvM_Atomic_value_t)0x00000004)
#define NVM_SATELLITE_JOB_ONGOING_MASK              ((NvM_Atomic_value_t)0x00000008)
#define NVM_SATELLITE_JOB_FINALIZING_MASK           ((NvM_Atomic_value_t)0x00000010)

/* Handling the satellite job flags */
#define NVM_SET_SATELLITE_JOB_ACCEPTED_FLAG(BlockIndex) (void)Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_ACCEPTED_MASK)
#define NVM_GET_SATELLITE_JOB_ACCEPTED_FLAG(BlockIndex) (boolean)((Atomics_Load(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo) & NVM_SATELLITE_JOB_ACCEPTED_MASK) != 0U ? TRUE : FALSE)
#define NVM_CLEAR_SATELLITE_JOB_ACCEPTED_FLAG(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_ACCEPTED_MASK)

#define NVM_SET_SATELLITE_BGND_CRC_QUEUED_FLAG(BlockIndex) (void)Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_BGND_CRC_QUEUED_MASK)
#define NVM_GET_SATELLITE_BGND_CRC_QUEUED_FLAG(BlockIndex) (boolean)((Atomics_Load(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo) & NVM_SATELLITE_BGND_CRC_QUEUED_MASK) != 0U ? TRUE : FALSE)
#define NVM_CLEAR_SATELLITE_BGND_CRC_QUEUED_FLAG(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_BGND_CRC_QUEUED_MASK)

#define NVM_SET_SATELLITE_JOB_TO_BE_CANCELLED_FLAG(BlockIndex) (void)Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_TO_BE_CANCELLED_MASK)
#define NVM_GET_SATELLITE_JOB_TO_BE_CANCELLED_FLAG(BlockIndex) (boolean)((Atomics_Load(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo) & NVM_SATELLITE_JOB_TO_BE_CANCELLED_MASK) != 0U ? TRUE : FALSE)
#define NVM_CLEAR_SATELLITE_JOB_TO_BE_CANCELLED_FLAG(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_TO_BE_CANCELLED_MASK)

#define NVM_SET_SATELLITE_JOB_ONGOING_FLAG(BlockIndex) (void)Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_ONGOING_MASK)
#define NVM_GET_SATELLITE_JOB_ONGOING_FLAG(BlockIndex) (boolean)((Atomics_Load(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo) & NVM_SATELLITE_JOB_ONGOING_MASK) != 0U ? TRUE : FALSE)
#define NVM_CLEAR_SATELLITE_JOB_ONGOING_FLAG(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_ONGOING_MASK)

#define NVM_SET_SATELLITE_JOB_FINALIZING_FLAG(BlockIndex) (void)Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_FINALIZING_MASK)
#define NVM_GET_SATELLITE_JOB_FINALIZING_FLAG(BlockIndex) (boolean)((Atomics_Load(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo) & NVM_SATELLITE_JOB_FINALIZING_MASK) != 0U ? TRUE : FALSE)
#define NVM_CLEAR_SATELLITE_JOB_FINALIZING_FLAG(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SATELLITE_JOB_FINALIZING_MASK)

#define NVM_CLEAR_SATELLITE_JOB_FLAGS(BlockIndex) (NVM_ATOMIC_STORE(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo & (NvM_Atomic_value_t)0xFFFFFF00U))

/* Master uses these to know the type of the current job given to Satellite. */
#define NVM_SATELLITE_NO_JOB        0U
#define NVM_SATELLITE_DO_STD_JOB    1U
#define NVM_SATELLITE_DO_IMM_JOB    2U
#define NVM_SATELLITE_DO_CRC_JOB    3U

/* Master sets this token to signal Satellite that it needs the token back */
#define NVM_NOBODY_S_TOKEN     255U

/* Macro function to access the inter-partition token */
#define NVM_GET_TOKEN_PARTITION() ((uint8)NvM_MultiPartitionToken)
#define NVM_SET_TOKEN_PARTITION(PartitionNumber) ((NvM_MultiPartitionToken & 0xFFFFFF00) | (uint32)PartitionNumber)

/* Handling inter-partition protections */
#define NVM_CANCEL_OPERATION_LOCK(BlockIndex) (!Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_BLOCK_CANCEL_LOCK_MASK))
#define NVM_CANCEL_OPERATION_LOCK_RELEASE(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_BLOCK_CANCEL_LOCK_MASK)

#define NVM_ASYNC_ASYNC_TRY_LOCK(BlockIndex) (!Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_ASYNC_ASYNC_PROTECT_MASK))
#define NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_ASYNC_ASYNC_PROTECT_MASK)
#define NVM_ASYNC_SYNC_TRY_LOCK(BlockIndex) (!Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SYNC_ASYNC_PROTECT_MASK))
#define NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SYNC_ASYNC_PROTECT_MASK)

/* Handling inter-Partition exclusive area. This waiting point is acceptable due to short execution time of a synchronous API */
#define NVM_ASYNC_SYNC_WAIT_TO_LOCK(BlockIndex) while(Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SYNC_ASYNC_PROTECT_MASK)){}
#define NVM_SYNC_SYNC_WAIT_TO_LOCK(BlockIndex) while(Atomics_TestAndSetFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SYNC_SYNC_PROTECT_MASK)){}
#define NVM_SYNC_SYNC_LOCK_RELEASE(BlockIndex) Atomics_ClearFlag(&NvM_AdminBlockTable[BlockIndex].MultiPartitionInfo, NVM_SYNC_SYNC_PROTECT_MASK)

#define NVM_QUEUE_WAIT_TO_LOCK() while(Atomics_TestAndSetFlag(&NvM_MultiPartitionGeneral, NVM_QUEUES_PROTECT_MASK)){}
#define NVM_QUEUE_LOCK_RELEASE() Atomics_ClearFlag(&NvM_MultiPartitionGeneral, NVM_QUEUES_PROTECT_MASK)

#define NVM_CRC_QUEUE_WAIT_TO_LOCK() while(Atomics_TestAndSetFlag(&NvM_MultiPartitionGeneral, NVM_CRC_QUEUE_PROTECT_MASK)){}
#define NVM_CRC_QUEUE_LOCK_RELEASE() Atomics_ClearFlag(&NvM_MultiPartitionGeneral, NVM_CRC_QUEUE_PROTECT_MASK)

/* Handling the satellite multi-block job flags */
#define NVM_SET_SATELLITE_MULTIBLOCK_FINALIZING_FLAG() (void)Atomics_TestAndSetFlag(&NvM_MultiPartitionGeneral, NVM_SATELLITE_MULTIBLOCK_FINALIZING_MASK)
#define NVM_GET_SATELLITE_MULTIBLOCK_FINALIZING_FLAG() (boolean)((Atomics_Load(&NvM_MultiPartitionGeneral) & NVM_SATELLITE_MULTIBLOCK_FINALIZING_MASK) != 0U ? TRUE : FALSE)
#define NVM_CLEAR_SATELLITE_MULTIBLOCK_FINALIZING_FLAG() Atomics_ClearFlag(&NvM_MultiPartitionGeneral, NVM_SATELLITE_MULTIBLOCK_FINALIZING_MASK)

/* These redefinitions are needed to switch between EB AtomicLibrary and the standard BSWMulticoreLibrary */
#define NVM_ATOMIC_INIT(object, value) Atomics_Init(object, value)
#define NVM_ATOMIC_STORE(object, value) Atomics_Store(object, value)
#define NVM_ATOMIC_LOAD(object) Atomics_Load(object)
#define NVM_ATOMIC_CHECK_SET_FLAG(object, flag) Atomics_TestAndSetFlag(object, flag)
#define NVM_ATOMIC_CLEAR_FLAG(object, flag) Atomics_ClearFlag(object, flag)

#else

#define NVM_ASYNC_ASYNC_TRY_LOCK(BlockIndex) ( NvM_AdminBlockTable[BlockIndex].NvMResult != NVM_REQ_PENDING )
#define NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex)
#define NVM_ASYNC_SYNC_TRY_LOCK(BlockIndex) ( NvM_AdminBlockTable[BlockIndex].NvMResult != NVM_REQ_PENDING )
#define NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex)

#define NVM_ASYNC_SYNC_WAIT_TO_LOCK(BlockIndex) /* No need to do something in case of BSW distribution is OFF */
#define NVM_SYNC_SYNC_WAIT_TO_LOCK(BlockIndex) SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0()
#define NVM_SYNC_SYNC_LOCK_RELEASE(BlockIndex) SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0()

#define NVM_QUEUE_WAIT_TO_LOCK()
#define NVM_QUEUE_LOCK_RELEASE()

#define NVM_CRC_QUEUE_WAIT_TO_LOCK()
#define NVM_CRC_QUEUE_LOCK_RELEASE()

#define NVM_SET_SATELLITE_MULTIBLOCK_FINALIZING_FLAG()
#define NVM_GET_SATELLITE_MULTIBLOCK_FINALIZING_FLAG()
#define NVM_CLEAR_SATELLITE_MULTIBLOCK_FINALIZING_FLAG()

#endif /* #if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON) */
/*==================[external data]==========================================*/

#if (NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS > 0U)
#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#if (NVM_CLEAR_RAMBLOCK_AFTER_RESET == STD_ON)
#define NVM_START_SEC_VAR_CLEARED_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief Stores the status of the NvM blocks.
 **/
extern VAR (NvM_AdminBlockType, NVM_VAR_CLEARED) NvM_AdminBlockTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#else
#define NVM_START_SEC_VAR_POWER_ON_CLEARED_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief Stores the status of the NvM blocks.
 **/
extern VAR (NvM_AdminBlockType, NVM_VAR_POWER_ON_CLEARED) NvM_AdminBlockTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#endif
#else /*MC CALLOUTS ENABLED*/
#if (NVM_CLEAR_RAMBLOCK_AFTER_RESET == STD_ON)
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief Stores the status of the NvM blocks.
 **/
extern VAR (NvM_AdminBlockType, NVM_VAR_CLEARED) NvM_AdminBlockTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#else
#define NVM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief Stores the status of the NvM blocks.
 **/
extern VAR (NvM_AdminBlockType, NVM_VAR_POWER_ON_CLEARED) NvM_AdminBlockTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#endif
#endif /*MC CALLOUTS ENABLED*/

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#if (NVM_CLEAR_RAMBLOCK_AFTER_RESET == STD_ON)
#define NVM_STOP_SEC_VAR_CLEARED_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_VAR_POWER_ON_CLEARED_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
#endif
#else /*MC CALLOUTS ENABLED*/
#if (NVM_CLEAR_RAMBLOCK_AFTER_RESET == STD_ON)
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include <NvM_MemMap.h>
#endif
#endif /*MC CALLOUTS ENABLED*/
#endif

/** \brief *************************  variables init uint8 section ****************/

#define NVM_START_SEC_VAR_INIT_8
#include <NvM_MemMap.h>
/** \brief used to store the interim value of the error status of a single
 ** block API function while this function is processed. */
extern VAR( uint8,NVM_VAR ) NvM_GlobalErrorStatus;

#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
extern VAR( NvM_Atomic_t,NVM_VAR ) NvM_MultiPartitionToken;
extern VAR( uint8,NVM_VAR ) NvM_SatelliteJobType;
#endif /* #if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON) */

#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
/** \brief counts the number of write retries. If the value reaches
 ** 'NvMMaxNumOfWriteRetries' NvM_WriteBlock() terminates with an error. */
extern VAR( uint8,NVM_VAR ) NvM_WriteRetryCount;
#endif

#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
/** \brief counts the number of read retries. If the value reaches
 ** 'NvMaxNumOfReadRetries' NvM_ReadBlock() starts copy redundant/ROM block . */
extern VAR( uint8,NVM_VAR ) NvM_ReadRetryCount;
#endif

#define NVM_STOP_SEC_VAR_INIT_8
#include <NvM_MemMap.h>

/** \brief *************************  variables init uint16 section ****************/
#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_START_SEC_VAR_INIT_MC_SHARED_16
#include <NvM_MemMap.h>
#else
#define NVM_START_SEC_VAR_INIT_16
#include <NvM_MemMap.h>
#endif

/** \brief stores status information concerning all blocks. */
extern VAR( uint16,NVM_VAR ) NvM_GlobalGenericStatus;

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U))
extern VAR (uint16,NVM_VAR) NvM_CrcQueue[NVM_NUMBER_OF_CRC_BLOCKS];
#endif

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_STOP_SEC_VAR_INIT_MC_SHARED_16
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_VAR_INIT_16
#include <NvM_MemMap.h>
#endif /*MC CALLOUTS ENABLED*/

/** \brief *************************  uninitialized variables uint8 section ****************/
#define NVM_START_SEC_VAR_CLEARED_8
#include <NvM_MemMap.h>

/** \brief used as index ( 'stack pointer' ) for array NvM_CurrentFunctionPtr to
 ** store the call level of the currently processed state machine. */
extern VAR( uint8,NVM_VAR ) NvM_GlobalCallLevel;

/** \brief holds the ID of the currently executed service. It is used to
 ** determine the currently running operation and to pass it as parameter
 ** to the callback function if the currently executed service has finished.
 **/
extern VAR( uint8,NVM_VAR_CLEARED ) NvM_CurrentServiceId;

#if (NVM_SYNC_MECHANISM == STD_ON)
/** \brief Counts the number of retries to let the application copy data
 **        between the RAM block and NvM module's mirror before postponing
 **        the current job.
 **/
extern VAR(uint8, NVM_VAR_CLEARED) NvM_MirrorRetryCount;
#endif

#if (NVM_CRYPTO_HOOKS == STD_ON)
/** \brief Stores the state that should be executed after the crypto operation is finished.
 **/
extern VAR( uint8,NVM_VAR_CLEARED ) NvM_PostCryptoState;
#endif
#define NVM_STOP_SEC_VAR_CLEARED_8
#include <NvM_MemMap.h>

/** \brief *************************  uninitialized variables uint16 section ****************/
#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_START_SEC_VAR_CLEARED_MC_SHARED_16
#include <NvM_MemMap.h>
#else
#define NVM_START_SEC_VAR_CLEARED_16
#include <NvM_MemMap.h>
#endif

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U))
/**  \brief The number of RAM block CRC Calculation pending request.
 **/
extern VAR( uint16, NVM_VAR_CLEARED ) NvM_RamBlockCrcCalcCount;
#endif /*SETRAMBLOCKSTATUS ENABLED*/

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_STOP_SEC_VAR_CLEARED_MC_SHARED_16
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_VAR_CLEARED_16
#include <NvM_MemMap.h>
#endif /*MC CALLOUTS ENABLED*/

/** \brief *************************  uninitialized variables unspecified section ****************/
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <NvM_MemMap.h>

#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
/**  \brief Stores the general locking flags used to protect parallel access.
 **/
extern VAR( NvM_Atomic_t,NVM_VAR_CLEARED ) NvM_MultiPartitionGeneral;
#endif

/** \brief Stores the current status of the currently processed
 **        NvM Block.
 **/
extern VAR( NvM_DynamicStatusType,NVM_VAR_CLEARED )  NvM_GlobalWorkingStatus;

#if (NVM_BUFFER_ALIGNMENT_BITS != 8)
extern VAR( boolean,NVM_VAR_CLEARED )  NvM_UseInternalBufferAlignment;
#endif

#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <NvM_MemMap.h>

/** \brief *************************  initialized variables unspecified allignment section ****************/
#define NVM_START_SEC_VAR_CLEARED_APPL_DATA_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief Stores the address of the temporary RAM block to be used
 **        while a request with a temporary RAM block is in progress.
 **        This value is initialized when the request is fetched from
 **        the queue and processing is started.
 **/
extern P2VAR(uint8, NVM_VAR_CLEARED, NVM_APPL_DATA) NvM_TempRamBlockAddress;

#define NVM_STOP_SEC_VAR_CLEARED_APPL_DATA_UNSPECIFIED
#include <NvM_MemMap.h>

/** \brief *************************  configuration dependent alignment section **********/

/* !LINKSTO NvM.ECUC_NvM_00573,1 */
#if (NVM_BUFFER_ALIGNMENT_BITS == 8)
#define NVM_START_SEC_VAR_CLEARED_8
#include <NvM_MemMap.h>
#elif (NVM_BUFFER_ALIGNMENT_BITS == 16)
#define NVM_START_SEC_VAR_CLEARED_16
#include <NvM_MemMap.h>
#elif (NVM_BUFFER_ALIGNMENT_BITS == 32)
#define NVM_START_SEC_VAR_CLEARED_32
#include <NvM_MemMap.h>
#else
#define NVM_START_SEC_VAR_CLEARED_64
#include <NvM_MemMap.h>
#endif

#if (NVM_INTERNAL_BUFFER_SIZE != 0U)
/** \brief NVM internal buffer for temporary data storage.
 ** This buffer is used for blocks with CRC for storing block data and CRC
 ** while reading from and writing to NV memory. */
extern VAR(uint8, NVM_VAR_CLEARED) NvM_InternalBuffer[NVM_INTERNAL_BUFFER_SIZE];
#endif

#if ((NVM_WRITE_VERIFICATION == STD_ON) ||(NVM_PRE_WRITE_DATA_COMP == STD_ON) || (NVM_BLOCK_CHECK_ENABLED == STD_ON))
/**  \brief Internal buffer used for intermediate read operations for pre and post write to NV memory.
 **         Internal buffer will be used in case of BlockCheck RedCopies compare to hold the data
 **         from the second redundant copy.
 **/
extern VAR(uint8, NVM_VAR_CLEARED) NvM_IntermediateReadBuffer[NVM_WRITE_VERIFICATION_BUFFER_SIZE];
#endif/*(NVM_WRITE_VERIFICATION == STD_ON) ||(NVM_PRE_WRITE_DATA_COMP == STD_ON) || (NVM_BLOCK_CHECK_ENABLED == STD_ON)*/

#if (NVM_BUFFER_ALIGNMENT_BITS == 8)
#define NVM_STOP_SEC_VAR_CLEARED_8
#include <NvM_MemMap.h>
#elif (NVM_BUFFER_ALIGNMENT_BITS == 16)
#define NVM_STOP_SEC_VAR_CLEARED_16
#include <NvM_MemMap.h>
#elif (NVM_BUFFER_ALIGNMENT_BITS == 32)
#define NVM_STOP_SEC_VAR_CLEARED_32
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_VAR_CLEARED_64
#include <NvM_MemMap.h>
#endif

/** \brief *****************  variables user application data section ***********/
#define NVM_START_SEC_VAR_INIT_8
#include <NvM_MemMap.h>

/** \brief The RAM data buffer for the configuration ID (Block 1).
 **/
extern VAR( uint8,NVM_APPL_DATA ) NvM_ConfigurationId[NVM_CONFIGURATIONID_PLUSCRC_SIZE];

#define NVM_STOP_SEC_VAR_INIT_8
#include <NvM_MemMap.h>
/** \brief ****************** end of variables user application data section ***********
 **************************  variables cleared uin16 section ********************/
#define NVM_START_SEC_VAR_CLEARED_16
#include <NvM_MemMap.h>

/** \brief Stores the number of the currently processed NvM block.
 **/
extern VAR( uint16,NVM_VAR )        NvM_GlobalBlockNumber;

#define NVM_STOP_SEC_VAR_CLEARED_16
#include <NvM_MemMap.h>
/** \brief ************************  end of variables cleared uin16 section ***********
 **************************  variables init unspecified section ***********/
#define NVM_START_SEC_VAR_INIT_UNSPECIFIED
#include <NvM_MemMap.h>

/** \brief Stores the function pointers to the currently processed
 **        state of the state machine of an asynchronous function.
 **/
extern VAR( NvM_CurrentFunctionPtrType,NVM_VAR ) NvM_CurrentFunctionPtr[6U];

/** \brief Pointer to the block descriptor of currently processed NvM block.
 **/
extern P2CONST( NvM_BlockDescriptorType,NVM_VAR,NVM_CONST ) NvM_CurrentBlockDescriptorPtr;

#define NVM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief ************************  end of variables init unspecified section ****
 ***************** configurated constants uint8 section *********************
 ***************************  end of constants uint8 section ****************
 **************************  constants uint8 section ************************
 **************************  end of constants uint8 section *****************
 ***********************  constants user application section ****************
 ********************* end of constants user application section ************
 ***************************  constants unspecified section *****************/

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_START_SEC_CONFIG_DATA_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
#else
#define NVM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <NvM_MemMap.h>
#endif

/** \brief Array storing the block configuration for each block.
 **/
extern CONST( NvM_BlockDescriptorType,NVM_CONST )
          NvM_BlockDescriptorTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
/** \brief Array storing the SchM inter-partition calls for Master-Satellite communication
 **/
extern CONST(NvM_SchMInterPartitionCallsType,NVM_CONST)
          NvM_SchMInterPartitionCalls[NVM_NUMBER_OF_SATELLITE_PARTITIONS];
#endif

#if (NVM_BLOCK_CHECK_ENABLED == STD_ON)
/** \brief Array storing the block configuration for each block configured with block check.
 **/
extern CONST( NvM_BcCfgDataType,NVM_CONST )
          NvM_BcCfgData[NVM_BC_NR_OF_BLOCKS];
#endif

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_STOP_SEC_CONFIG_DATA_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <NvM_MemMap.h>
#endif /*MC CALLOUTS ENABLED*/

#define NVM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <NvM_MemMap.h>

#if (NVM_CANCEL_INTERNAL_JOB == STD_ON)
/** \brief Array storing the IDs of the configured memory devices.
 **/
extern CONST( uint8,NVM_CONST )
          NvM_UsedDeviceIds[NVM_NUM_USED_DEVICES];
#endif /*NVM_CANCEL_INTERNAL_JOB == STD_ON*/

#define NVM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <NvM_MemMap.h>
/** \brief *************************  end of constants unspecified section **********
 ***************************  constants unspecified section *****************
 ***************************  end of constants unspecified section **********
 ***************************  constants unspecified section *****************
 ***************************  end of constants unspecified section **********
 ***************************  constants uint8 section ***********************
 ***************************  end of constants uint8 section ****************/
/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function declarations]========================*/
#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/** \brief Function to search for block with the given id in the configuration table
 *         and return the index of the block.
 *
 *  \param[in] BlockId requested block number
 *  \param[out] The index in configuration table where the block id was found.
 */
#if ( NVM_BLOCK_INDEX_SEARCH == STD_ON )
extern FUNC(uint16, NVM_CODE) NvM_SearchConfigTable(const NvM_BlockIdType BlockId);
#endif

/** \brief Function to get block index from configuration table.
 *
 *  \param[in] BlockId requested block number
 *  \param[out] The index in configuration table where the block id was found.
 */
#if ( NVM_DEV_ERROR_DETECT == STD_ON )
extern FUNC(uint16, NVM_CODE) NvM_GetBlockIndexForValidId(const NvM_BlockIdType BlockId);
#endif

#if ( ( NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFO == STD_OFF ) || ( NVM_NUMBER_OF_SINGLE_BLOCK_CALLBACK > 0U ) )

/** \brief NvM_ProcessBlockCallback processes single block or multi block
 **        callbacks */
extern FUNC(void, NVM_CODE) NvM_ProcessBlockCallback(void);

#endif

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/*==================[internal function definitions]=========================*/
#endif /* NVM_DATA_INTERN_H */

/*======================[end of file NvM_DataIntern.h]======================*/
