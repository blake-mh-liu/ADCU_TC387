/**
 * \file
 *
 * \brief AUTOSAR Fee
 *
 * This file contains the implementation of the AUTOSAR
 * module Fee.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* This file contains function prototypes for jobs operations */

#ifndef FEE_JOBS_H
#define FEE_JOBS_H

/*==================[inclusions]============================================*/
/* !LINKSTO Fee.SWS_Fee_00084,2, Fee.ASR40.SWS_Fee_00002,1 */
#include <Std_Types.h>        /* AUTOSAR Standard type header*/
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/** \brief State entry function to initiate the flash write of block info
 *         to invalidate a block.
 */
extern FUNC(void, FEE_CODE) Fee_SfOnEntryInvalidate(void);

/** \brief State entry function to initiate the flash write of block info
 *          to erase an immediate block.
 */
extern FUNC(void, FEE_CODE) Fee_SfOnEntryEraseImmediateBlock(void);

/** \brief State entry function to initiate writing the block info
 *         at the next location in flash memory.
 */
extern FUNC(void, FEE_CODE) Fee_SfOnEntryWriteBlockInfo(void);

/** \brief State function to check if writing the block info was successful
 *         for either an invalidation or an erase immediate job or, in case of a write job
 *         trigger the transition to write block data or update the block data address
 *         if write job was canceled.
 */
extern FUNC(void, FEE_CODE) Fee_SfWriteBlockInfo(void);

/** \brief State entry function to initiate writing the block data
 *         at the next location in flash memory.
 */
extern FUNC(void, FEE_CODE) Fee_SfOnEntryWriteBlockData(void);

/** \brief State function to check if writing of block data was successful.
 **
 **        If the usage of consistency patterns is disabled, the state function resumes
 **        a pending switch section or erase operation. If no operation is pending,
 **        state is set to idle.
 **
 **        If the usage of consistency patterns is enabled, the transition to write the block
 **        data end pattern is triggered.
 */
extern FUNC(void, FEE_CODE) Fee_SfWriteBlockData(void);

/** \brief State entry function to initiate writing the written marker
 *         after BlockInfo.
 */
extern FUNC(void, FEE_CODE) Fee_SfOnEntryWriteWrittenMarker(void);

/** \brief State function to check if writing of written marker was successful.
 **
 **        If the usage of consistency patterns is disabled, the state function resumes
 **        a pending switch section or erase operation. If no operation is pending,
 **        state is set to idle.
 **
 **        If the usage of consistency patterns is enabled, the transition to write the block
 **        data end pattern is triggered.
 */
extern FUNC(void, FEE_CODE) Fee_SfWriteWrittenMarker(void);

/** \brief State entry function to initiate the flash read for the block data using
 *         the address in cache.
 */
extern FUNC(void, FEE_CODE) Fee_SfOnEntryReadBlockData(void);

/** \brief State function to check if reading the block data from flash was
 *         successful. If successful, the block result is set as
 *         MEMIF_JOB_OK and Nvm job end notification is called if configured.
 */
extern FUNC(void, FEE_CODE) Fee_SfReadBlockData(void);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /* ifndef FEE_JOBS_H */
