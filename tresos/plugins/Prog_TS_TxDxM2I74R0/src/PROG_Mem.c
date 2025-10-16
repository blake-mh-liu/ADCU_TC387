/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Mem.c                      */
/*%%  |                             |  %%  \brief PROG Memory                    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/* NOCOV List
 *
 * NOCOV-FEATURE_NOT_USED:
 *   certain features are implemented but not yet used.
 *
 * Reason:
 * We assume that they are not tested for the moment (will be done later).
 * In order to not impact the coverage, the NOCOV is used.
 *
 *
 * NOCOV-EMPTYDEFAULT:
 *   defensive code.
 *
 * Reason:
 * Defensive case which shall never happen.
 *
 *
 * NOCOV-UNITARYTEST
 *   pieces of code cannot be tested by Unitary Tests.
 *
 * Reason:
 *  Coverage should not be check on code bounded by NCS_UNITARY_TEST checking.
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
#include <Dcm_Types.h>
#endif
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
NCS_PRI_VAR u8 m_ubDisableSkipPage;
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_2 */
/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

#if (PROG_FLASH_MEMORY_USE == PROG_TRUE)

/** \brief Perform Flash memory access
 **
 ** This function is called to perform an access (write, read, erase)
 ** in the flash memory
 **
 ** \param[in] eAccessType type of the memory access (write, read, erase)
 ** \param[in] uMemAddress address to access
 ** \param[in] ulLength Data length
 ** \param[in,out] paubDataBuffer pointer to buffer where data shall be set/get
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  memory access is successfull
 ** \retval PROG_E_NOT_OK  memory access failed
 ** \retval PROG_E_BUSY  memory access is in progress
 **
 **/
NCS_PRI_FCT tProgStatus PROG_MemFlash (
        tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
);
#endif

#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
/** \brief Perform external Flash memory access
 **
 ** This function is called to perform an access (write, read, erase)
 ** in the external flash memory
 **
 ** \param[in] eAccessType type of the memory access (write, read, erase)
 ** \param[in] uMemAddress address to access
 ** \param[in] ulLength Data length
 ** \param[in,out] paubDataBuffer pointer to buffer where data shall be set/get
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  memory access is successfull
 ** \retval PROG_E_NOT_OK  memory access failed
 ** \retval PROG_E_BUSY  memory access is in progress
 **
 **/
NCS_PRI_FCT tProgStatus PROG_MemFlashExt
(
        tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
);
#endif

#if (PROG_RAM_MEMORY_USE == PROG_TRUE)
/** \brief Perform RAM memory access
 **
 ** This function is called to perform an access (write, read, erase)
 ** in the RAM memory
 **
 ** \param[in] eAccessType type of the memory access (write, read, erase)
 ** \param[in] uMemAddress address to access
 ** \param[in] ulLength Data length
 ** \param[in,out] paubDataBuffer pointer to buffer where data shall be set/get
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  memory access is successfull
 ** \retval PROG_E_NOT_OK  memory access failed
 ** \retval PROG_E_BUSY  memory access is in progress
 **
 **/
NCS_PRI_FCT tProgStatus PROG_MemRam
(
        tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
);
#endif

#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
/** \brief Perform Custom memory access
 **
 ** This function is called to perform an access (write, read, erase)
 ** in the custom memory
 **
 ** \param[in] eAccessType type of the memory access (write, read, erase)
 ** \param[in] uMemAddress address to access
 ** \param[in] ulLength Data length
 ** \param[in,out] paubDataBuffer pointer to buffer where data shall be set/get
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  memory access is successfull
 ** \retval PROG_E_NOT_OK  memory access failed
 ** \retval PROG_E_BUSY  memory access is in progress
 **
 **/
NCS_PRI_FCT tProgStatus PROG_MemCustom
(
        tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
);
#endif

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------{PROG_MemInit}-------------------------------------*/
void PROG_MemInit(void)
{
    DBG_PROG_MEMINIT_ENTRY();
#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
    m_ubDisableSkipPage = FALSE;
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_2 */
    DBG_PROG_MEMINIT_EXIT();
}
/*---------------------------{End PROG_MemInit}----------------------------------*/

/*----------------------------{PROG_FlashPage}-----------------------------------*/
#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
#define PROG_START_SEC_CODE_FLASH_PAGE
#include "MemMap.h"
u8 PROG_FlashPage(u32 ulAddress, u8 ubPages, u32* pulDataBuffer, u16 uwDataBufferLenght)
{
    u8 ubReturnValue;
    u8 ubLocalPageNumber;
    tFlashStatus eProgFlashStatus = FLASH_ACCESS_ERROR;
    u32 ulMinValueToWrite = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ulMinValueToWrite;

    DBG_PROG_FLASHPAGE_ENTRY(ulAddress, ubPages,pulDataBuffer, uwDataBufferLenght);

    /*Disable call to skippage*/
    m_ubDisableSkipPage = TRUE;

    /* Check the number of pages is matching buffer length */
    ubLocalPageNumber = (u8)((u8)((((u32)((u32)uwDataBufferLenght & 0x0000FFFFU) - 1U) / ulMinValueToWrite) + 1U) & 0xFFU);

    if (ubLocalPageNumber > ubPages)
    {
        /* Buffer Length shall be limited to the provided number of page */
        eProgFlashStatus = FLASH_WriteBuffer(ulAddress, (u16)(((u32)ubLocalPageNumber*ulMinValueToWrite) & 0xFFFFU), (u8*)pulDataBuffer);
    }
    else if (ubLocalPageNumber == ubPages)
    {
        /* Buffer Length shall be used to call Flash driver */
        eProgFlashStatus = FLASH_WriteBuffer(ulAddress, uwDataBufferLenght, (u8*)pulDataBuffer);
    }
    else
    {
        /* Too many pages write is requested */
        /* Return value has already been set to NOT OK */
    }

    if (FLASH_NO_ERROR == eProgFlashStatus)
    {
        ubReturnValue = PROG_FLASH_PAGE_E_OK;
    }
    else
    {
        ubReturnValue = PROG_FLASH_PAGE_E_NOT_OK;
    }

    /*Enable call to skippage*/
    m_ubDisableSkipPage = FALSE;

    DBG_PROG_FLASHPAGE_EXIT(ubReturnValue);
    return ubReturnValue;
}
#define PROG_STOP_SEC_CODE_FLASH_PAGE
#include "MemMap.h"
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_2 */
/*---------------------------{End PROG_FlashPage}--------------------------------*/

/*----------------------------{PROG_SkipPage}------------------------------------*/
/* Wrap skipPage function to address pointer */
#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
u8 PROG_SkipPage(u32* uAddr)
{
    u8 ubRetVal;
#ifndef NCS_UNITARY_TEST
    tpulskipPage pulskipPage = (tpulskipPage)pulProgFramework_Api_Array_Ptr[12]; /*Address of skipPage Api*/
#endif

    DBG_PROG_SKIPPAGE_ENTRY(uAddr);

    /*check if SkipPage shall be called*/
    if (FALSE == m_ubDisableSkipPage)
    {
#ifndef NCS_UNITARY_TEST
        ubRetVal = pulskipPage(uAddr);
#else
        ubRetVal = skipPage(uAddr);
#endif
    }
    else
    {
        /*No call, page shall not be skipped*/
        ubRetVal = PROG_NO_SKIP_PAGE;
    }
    DBG_PROG_SKIPPAGE_EXIT(ubRetVal);
    return ubRetVal;
}
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_2 */
/*---------------------------{End PROG_SkipPage}---------------------------------*/

/*----------------------------{PROG_MemDataAccess}-------------------------------*/
tProgStatus PROG_MemDataAccess
(
    tProgMemType eMemType,
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    tProgStatus eProgStatus;

    DBG_PROG_MEMDATAACCESS_ENTRY(eMemType, eOperationType,uMemAddress, ulLength,paubDataBuffer);

    eProgStatus = PROG_E_NOT_OK;

    switch(eMemType)
    {
#if (PROG_FLASH_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_FLASH:
            /* redirect function according to access wanted (read, write, erase) */
            eProgStatus = PROG_MemFlash( eOperationType,
                    uMemAddress,
                    ulLength,
                    paubDataBuffer);
            break;
#endif
#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_FLASH_EXT:
            eProgStatus = PROG_MemFlashExt( eOperationType,
                    uMemAddress,
                    ulLength,
                    paubDataBuffer);
            break;
#endif
#if (PROG_RAM_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_RAM:
            eProgStatus = PROG_MemRam( eOperationType,
                    uMemAddress,
                    ulLength,
                    paubDataBuffer);
            break;
#endif
#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_CUSTOM:
            eProgStatus = PROG_MemCustom( eOperationType,
                    uMemAddress,
                    ulLength,
                    paubDataBuffer);
            break;
#endif
        /* unknown memory type */
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            /* Nothing to do, NOK status already set */
            break;
/* CHECK: PARSE */
    }

    if(PROG_E_OK == eProgStatus)
    {
        eProgStatus = PROG_CustomMemoryAccessNotification(eMemType, eOperationType, uMemAddress, ulLength, paubDataBuffer);
    }

    DBG_PROG_MEMDATAACCESS_EXIT(eProgStatus);
    return (eProgStatus);
}
/*-----------------------{End PROG_MemDataAccess}-----------------------------*/

#if (PROG_FLASH_MEMORY_USE == PROG_TRUE)
/*-----------------------------{PROG_MemFlash}--------------------------------*/
NCS_PRI_FCT tProgStatus PROG_MemFlash
(
        tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    tProgStatus eProgStatus;
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
      Std_ReturnType RetVal;
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
      tProgStatus eProgFlashStatus;
#endif
    tProgAddressType ulLocalMemAddress;

    ulLocalMemAddress = (u32)(uMemAddress + PROG_FLASH_ADDR_OFFSET);

    eProgStatus = PROG_E_NOT_OK;

    /* redirect function according to access wanted (read, write, erase) */
    switch (eOperationType)
    {
#if ((PROG_FLASH_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_FLASH_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_WRITE))
        /* PROG_MemErase */
        case PROG_MEM_OPERATION_TYPE_ERASE:
#if (PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON)
            if(PROG_FALSE == PROG_DrvDown_IsFlashRoutinesPresent())
            {

#if (PROG_REPROGMEMM_ENABLED == STD_ON)
                 RetVal = E_NOT_OK;
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
                 eProgFlashStatus = FLASH_ACCESS_ERROR;
#endif
            }
            else
#endif
            {

#if (PROG_REPROGMEMM_ENABLED == STD_ON)
                 /* here, for erasing case, length unit is one sector */
                 RetVal = ReProgMemM_Erase(uMemAddress,ulLength);
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
                /* Request erasing to flash driver */
                eProgFlashStatus = FLASH_EraseSector(ulLocalMemAddress);
#else
                /* here, for erasing case, length unit is one sector */
                eProgFlashStatus = FLASH_Erase(uMemAddress, ulLength);
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */
#endif
            }
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
      if(E_OK == RetVal)
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
       if(FLASH_NO_ERROR == eProgFlashStatus)
#endif
            {
                eProgStatus = PROG_E_OK;
            }
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
      else if(REPROGMEMM_STATUS_PENDING == RetVal)
      {
          eProgStatus = PROG_E_BUSY;
      }
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
#if (PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS)
      else if(FLASH_BUSY == eProgFlashStatus)

            {
                eProgStatus = PROG_E_BUSY;
            }
#endif
#endif

            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;

        /* PROG_MemWriteBuffer */
        case PROG_MEM_OPERATION_TYPE_WRITE:
#if (PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON)
            if(PROG_FALSE == PROG_DrvDown_IsFlashRoutinesPresent())
            {
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
                 RetVal = E_NOT_OK;
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
                 eProgFlashStatus = FLASH_ACCESS_ERROR;
#endif
            }
            else
#endif
            {
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
                RetVal = ReProgMemM_Write(ulLocalMemAddress, (u32)((u32)ulLength & 0xFFFFFFFFU), paubDataBuffer);
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
                eProgFlashStatus = FLASH_WriteBuffer(ulLocalMemAddress, (u32)((u32)ulLength & 0xFFFFFFFFU), paubDataBuffer);
#endif
        }
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
      if(E_OK == RetVal)
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
       if(FLASH_NO_ERROR == eProgFlashStatus)
#endif
            {
                eProgStatus = PROG_E_OK;
            }
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
      else if(REPROGMEMM_STATUS_PENDING == RetVal)
      {
          eProgStatus = PROG_E_BUSY;
      }
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
#if (PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS)
      else if(FLASH_BUSY == eProgFlashStatus)

            {
                eProgStatus = PROG_E_BUSY;
            }
#endif
#endif


            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;
#endif
#if ((PROG_FLASH_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_FLASH_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ))
        case PROG_MEM_OPERATION_TYPE_READ:
            /* disable ECC */
            PROG_DisableECCCheck();
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
            RetVal = ReProgMemM_Read(ulLocalMemAddress, (u32)((u32)ulLength & 0xFFFFFFFFU), paubDataBuffer, ReProgMemM_UbActiveBank);
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
            eProgFlashStatus = FLASH_Read(ulLocalMemAddress, (u32)((u32)ulLength & 0xFFFFFFFFU), paubDataBuffer);
#endif
            /* enable ECC */
            PROG_EnableECCCheck();
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
            if(E_OK == RetVal)
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
            if(FLASH_NO_ERROR == eProgFlashStatus)
#endif
            {
                eProgStatus = PROG_E_OK;
            }
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
            else if(REPROGMEMM_STATUS_PENDING == RetVal)
            {
                /* loop is to call ReProgMemM_MainFunction until it returns PROG_E_OK */
                while(RetVal == REPROGMEMM_STATUS_PENDING)
                {
                    ReProgMemM_MainFunction();
                    RetVal = ReProgMemM_GetJobStatus();
                }
                if (E_OK == RetVal)
                {
                    eProgStatus = PROG_E_OK;
                }
                else
                {
                    eProgStatus = PROG_E_NOT_OK;
                }
            }
#endif
            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;
#endif
        /* this case must never happen */
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            /* Nothing to do, NOK status already set */
            break;
/* CHECK: PARSE */
    }

    return (eProgStatus);
}
/*---------------------------{End PROG_MemFlash}-------------------------------*/
#endif /* if (PROG_FLASH_MEMORY_USE == PROG_TRUE) */

#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
/*----------------------------{PROG_MemFlashExt}-------------------------------*/
NCS_PRI_FCT tProgStatus PROG_MemFlashExt
(
    tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    tProgStatus eProgStatus;
    tProgStatus eProgFlashStatus;
    tProgAddressType uLocalMemAddress;

    eProgStatus = PROG_E_NOT_OK;

    uLocalMemAddress = (uMemAddress - PROG_FLASH_EXT_ADDR_OFFSET);

    /* redirect function according to access wanted (read, write, erase) */
    switch (eOperationType)
    {
#if ((PROG_FLASH_EXT_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_FLASH_EXT_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_WRITE))
        /* PROG_MemErase */
        case PROG_MEM_OPERATION_TYPE_ERASE:
#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
            /* here, for erasing case, length unit is one sector */
            eProgFlashStatus = FLASH_Ext_EraseSector(uLocalMemAddress);
#else
            eProgFlashStatus = FLASH_Ext_Erase(uLocalMemAddress,ulLength);
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */
            if(FLASH_EXT_NO_ERROR == eProgFlashStatus)
            {
                eProgStatus = PROG_E_OK;
            }
#if (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS)
            else if(FLASH_EXT_BUSY == eProgFlashStatus)
            {
                eProgStatus = PROG_E_BUSY;
            }
#endif
            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;

        /* PROG_MemWriteBuffer */
        case PROG_MEM_OPERATION_TYPE_WRITE:
            eProgFlashStatus = FLASH_Ext_WriteBuffer(uLocalMemAddress, (u16)((u16)ulLength & 0xFFFFU), paubDataBuffer);
            if(FLASH_EXT_NO_ERROR == eProgFlashStatus)
            {
                eProgStatus = PROG_E_OK;
            }
#if (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS)
            else if(FLASH_EXT_BUSY == eProgFlashStatus)
            {
                eProgStatus = PROG_E_BUSY;
            }
#endif
            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;
#endif
#if ((PROG_FLASH_EXT_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_FLASH_EXT_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ))
        /* PROG_MemReaduffer */
        case PROG_MEM_OPERATION_TYPE_READ:
            eProgFlashStatus = FLASH_Ext_Read(uLocalMemAddress, (u16)((u16)ulLength & 0xFFFFU), paubDataBuffer);

            if(FLASH_EXT_NO_ERROR == eProgFlashStatus)
            {
                eProgStatus = PROG_E_OK;
            }
            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;
#endif
        /* this case must never happen */
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            /* Nothing to do, NOK status already set */
            break;
/* CHECK: PARSE */
    }

    return (eProgStatus);
}
/*------------------------{End PROG_MemFlashExt}-----------------------------*/
#endif /* if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE) */

#if (PROG_RAM_MEMORY_USE == PROG_TRUE)
/*-----------------------------{PROG_MemRam}---------------------------------*/
NCS_PRI_FCT tProgStatus PROG_MemRam
(
    tOperationType eOperationType,
        tProgAddressType uMemAddress,
        tDataLength ulLength,
        tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    tProgStatus eProgStatus;
#ifndef NCS_UNITARY_TEST
    u8 *pubAddrToWrite;
    u32 ulIdxByte;
#endif

    /* redirect function according to access wanted (read, write, erase) */
    switch (eOperationType)
    {
#if ((PROG_RAM_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_RAM_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_WRITE))
        /* PROG_MemWriteBuffer */
        case PROG_MEM_OPERATION_TYPE_WRITE:
#ifndef NCS_UNITARY_TEST
/* CHECK: NOPARSE */
/* NOCOV-UNITARYTEST */
            /* Get the address to write */
            pubAddrToWrite = (u8*)uMemAddress;
            for (ulIdxByte = 0U; ulIdxByte < ulLength; ulIdxByte++)
            {
                pubAddrToWrite[ulIdxByte] = paubDataBuffer[ulIdxByte];
            }
#else
/* CHECK: PARSE */
            /* In EB UT an API is used to simulate specific write value */
            PROG_RamWrite(uMemAddress, ulLength, paubDataBuffer);
#endif
            eProgStatus = PROG_E_OK;
            break;
        case PROG_MEM_OPERATION_TYPE_ERASE:
#ifndef NCS_UNITARY_TEST
/* CHECK: NOPARSE */
/* NOCOV-UNITARYTEST */
            /* Get the address to erase */
            pubAddrToWrite = (u8*)uMemAddress;
            /* erase all the required memory to 0 */
            for (ulIdxByte = 0U; ulIdxByte < ulLength; ulIdxByte++)
            {
                pubAddrToWrite[ulIdxByte] = 0U;
            }
/* CHECK: PARSE */
#else
            OSC_PARAM_UNUSED(uMemAddress);
            OSC_PARAM_UNUSED(ulLength);
            OSC_PARAM_UNUSED(paubDataBuffer);
#endif
            eProgStatus = PROG_E_OK;
            break;

#endif
#if ((PROG_RAM_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_RAM_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ))

        case PROG_MEM_OPERATION_TYPE_READ:
#ifndef NCS_UNITARY_TEST
/* CHECK: NOPARSE */
/* NOCOV-UNITARYTEST */
            /* Get the address to read */
            pubAddrToWrite = (u8*)uMemAddress;
            for (ulIdxByte = 0U; ulIdxByte < ulLength; ulIdxByte++)
            {
                paubDataBuffer[ulIdxByte] = pubAddrToWrite[ulIdxByte];
            }
#else
/* CHECK: PARSE */
            /* In EB UT an API is used to simulate specific read value */
            PROG_RamRead(uMemAddress, ulLength, paubDataBuffer);
#endif
            eProgStatus = PROG_E_OK;
            break;
#endif
        /* this case must never happen */
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            eProgStatus = PROG_E_NOT_OK;
            break;
/* CHECK: PARSE */
    }

    return (eProgStatus);
}
/*---------------------------{End PROG_MemRam}--------------------------------*/
#endif /* if (PROG_RAM_MEMORY_USE == PROG_TRUE) */

#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
/*----------------------------{PROG_MemCustom}-------------------------------*/
NCS_PRI_FCT tProgStatus PROG_MemCustom
(
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    tProgStatus eProgStatus;
    tProgAddressType uLocalMemAddress;

    eProgStatus = PROG_E_NOT_OK;

    uLocalMemAddress = (uMemAddress - PROG_CUSTOM_MEMORY_ADDR_OFFSET);

    /* redirect function according to access wanted (read, write, erase) */
    switch (eOperationType)
    {
#if ((PROG_CUSTOM_MEMORY_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_CUSTOM_MEMORY_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_WRITE))
        /* PROG_MemErase */
        case PROG_MEM_OPERATION_TYPE_ERASE:
            eProgStatus = PROG_CustomMemoryErase(uLocalMemAddress,ulLength);

            break;
        /* PROG_MemWriteBuffer */
        case PROG_MEM_OPERATION_TYPE_WRITE:
            eProgStatus = PROG_CustomMemoryWrite(uLocalMemAddress, (u16)((u16)ulLength & 0xFFFFU), paubDataBuffer);

            break;
#endif
#if ((PROG_CUSTOM_MEMORY_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ_WRITE) || (PROG_CUSTOM_MEMORY_ACCESS_TYPE == PROG_MEM_ACCESS_TYPE_READ))
        /* PROG_MemReaduffer */
        case PROG_MEM_OPERATION_TYPE_READ:
            eProgStatus = PROG_CustomMemoryRead(uLocalMemAddress, (u16)((u16)ulLength & 0xFFFFU), paubDataBuffer);

            break;
#endif
        /* this case must never happen */
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            /* Nothing to do, NOK status already set */
            break;
/* CHECK: PARSE */
    }

    return (eProgStatus);
}
/*------------------------{End PROG_MemCustom}-----------------------------*/
#endif /* if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE) */

#if ( (PROG_REPROGMEMM_ENABLED == STD_ON) \
      ||((PROG_FLASHWRAPPER_ENABLED == STD_ON) &&((PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS) || (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS) || (PROG_CUSTOM_MEMORY_MODE == PROG_MEMORY_ASYNCHRONOUS))))
/*---------------------------{PROG_MemJobResult}------------------------------*/
tProgStatus PROG_MemJobResult(tProgMemType eMemType)
{
    tProgStatus eProgStatus;

#if ((PROG_FLASH_MEMORY_USE == PROG_TRUE) || (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE))
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
    Std_ReturnType RetVal;
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
    tProgStatus eProgFlashStatus;
#endif
#endif

    DBG_PROG_MEMJOBRESULT_ENTRY(eMemType);

    eProgStatus = PROG_E_NOT_OK;

    switch (eMemType)
    {
#if (PROG_FLASH_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_FLASH:
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
            RetVal = ReProgMemM_GetJobStatus();
        if (E_OK == RetVal)
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
            eProgFlashStatus = FLASH_GetJobStatus();
        if (FLASH_NO_ERROR == eProgFlashStatus)
#endif
            {
                eProgStatus = PROG_E_OK;
            }
#if (PROG_REPROGMEMM_ENABLED == STD_ON)
            else if(REPROGMEMM_STATUS_PENDING == RetVal)
#elif (PROG_FLASHWRAPPER_ENABLED == STD_ON)
            else if (FLASH_BUSY == eProgFlashStatus)
#endif
            {
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;
#endif
#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_FLASH_EXT:
            eProgFlashStatus = FLASH_Ext_GetJobStatus();
            if (FLASH_EXT_NO_ERROR == eProgFlashStatus)
            {
                eProgStatus = PROG_E_OK;
            }
            else if (FLASH_EXT_BUSY == eProgFlashStatus)
            {
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                /* Nothing to do, NOK status already set */
            }
            break;
#endif
#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_CUSTOM:
            eProgStatus = PROG_CustomMemGetJobStatus();

            break;
#endif
#if (PROG_RAM_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_RAM:
            eProgStatus = PROG_E_OK;
            break;
#endif
        /* unknown memory type */
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            /* Nothing to do, NOK status already set */
            break;
/* CHECK: PARSE */
    }

    DBG_PROG_MEMJOBRESULT_EXIT(eProgStatus);

    return eProgStatus;
}
/*--------------------------{End PROG_MemJobResult}----------------------------*/
#endif /* if ( (PROG_REPROGMEMM_ENABLED == STD_ON)||((PROG_FLASHWRAPPER_ENABLED == STD_ON) &&((PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS) || (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS) || (PROG_CUSTOM_MEMORY_MODE == PROG_MEMORY_ASYNCHRONOUS)))) */

#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
/*---------------------------{PROG_MemGetNextSectorAddr}------------------------------*/
tProgAddressType PROG_MemGetNextSectorAddr(tProgMemType eMemType, tProgAddressType uCurrentSectorAddr)
{
    tProgAddressType ulNextSectorAddr = 0x00;
#if ((PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE) || (PROG_CUSTOM_MEMORY_USE == PROG_TRUE))
    tProgAddressType uLocalCurrentSectorAddr;
#endif

    DBG_PROG_MEMGETNEXTSECTORADDR_ENTRY(eMemType, uCurrentSectorAddr);

    switch (eMemType)
    {
#if (PROG_FLASH_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_FLASH:
            ulNextSectorAddr = FLASH_GetNextSectorAddr(uCurrentSectorAddr);
            break;
#endif
#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_FLASH_EXT:
            /* retrieve the physical external flash address */
            uLocalCurrentSectorAddr = uCurrentSectorAddr - PROG_FLASH_EXT_ADDR_OFFSET;

            ulNextSectorAddr = FLASH_Ext_GetNextSectorAddr(uLocalCurrentSectorAddr);

            /* Set back the functional next address */
            ulNextSectorAddr += PROG_FLASH_EXT_ADDR_OFFSET;
            break;
#endif
#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
        case PROG_MEM_TYPE_CUSTOM:
            /* retrieve the physical Custom Memory address */
            uLocalCurrentSectorAddr = uCurrentSectorAddr - PROG_CUSTOM_MEMORY_ADDR_OFFSET;

            ulNextSectorAddr = PROG_CustomGetNextSectorAddr(uLocalCurrentSectorAddr);

            /* Set back the functional next address */
            ulNextSectorAddr += PROG_CUSTOM_MEMORY_ADDR_OFFSET;
            break;
#endif
/* CHECK: NOPARSE */
/* NOCOV-UNITARYTEST */
        default:
            /* Nothing to do */
            break;
/* CHECK: PARSE */
    }
    DBG_PROG_MEMGETNEXTSECTORADDR_EXIT(ulNextSectorAddr);
    return ulNextSectorAddr;
}
/*--------------------------{End PROG_MemGetNextSectorAddr}----------------------------*/
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */

/*----------------------------{PROG_MemCheckPageErasing}-----------------------*/
#if ((PROG_IMPL_VARIANT == PROG_IMPL_20) ||  (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_11) || (PROG_IMPL_VARIANT == PROG_IMPL_91) )
tProgStatus PROG_MemCheckPageErasing(tProgMemType eMemType, tProgAddressType uMemAddress)
{
    tProgStatus eProgStatus = PROG_E_OK;
    u8  ubEraseValue = PROG_MEM_TYPE_INIT;
    u16  uwLoopIndex;
    u8 aubData[PROG_MIN_VAL_TO_WRITE] = {0};
    u32 ulMinValueToWrite = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ulMinValueToWrite;

    DBG_PROG_MEMCHECKPAGEERASING_ENTRY(eMemType, uMemAddress);

    if(eMemType != PROG_MEM_TYPE_RAM)
    {
#if (PROG_FLASH_MEMORY_USE == PROG_TRUE)
        if(eMemType == PROG_MEM_TYPE_FLASH)
        {
            ubEraseValue = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ubEraseValue;
        }
#endif
#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
        if(eMemType == PROG_MEM_TYPE_FLASH_EXT)
        {
            ubEraseValue = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ubEraseValue;
        }
#endif
#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
        if(eMemType == PROG_MEM_TYPE_CUSTOM)
        {
            ubEraseValue = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ubEraseValue;
        }
#endif

        (void)PROG_MemDataAccess( eMemType, PROG_MEM_OPERATION_TYPE_READ,
                uMemAddress, PROG_MIN_VAL_TO_WRITE, aubData);


        /* check if memory was well erased */
        for(uwLoopIndex = 0; (uwLoopIndex < ulMinValueToWrite) && (eProgStatus != PROG_E_NOT_OK); uwLoopIndex++)
        {
            /* if memory not empty */
            if(aubData[uwLoopIndex] != ubEraseValue)
            {
                eProgStatus = PROG_E_NOT_OK;
            }
        }
    }
    DBG_PROG_MEMCHECKPAGEERASING_EXIT(eProgStatus);
    return eProgStatus;
}
#endif
/*--------------------{end PROG_MemCheckPageErasing}-----------------------------*/
