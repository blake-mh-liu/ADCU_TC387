/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Prg.c                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 *
 * MISRAC2012-2) Deviated Rule: 8.4 (required)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined
 *
 *   Reason:
 * This variable need to be used in test environment
 */
/* NOCOV List
 *
 * NOCOV-NOCOV-BMTIMEOUTCHECKONNOTSUPPORTED:
 *
 * Reason:
 * BM_TIMEOUT_CHECK_ON not yet supported
 */
/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: INT.36
 * Converting a pointer to integer or integer to pointer
 *
 * Reason:
 * this variable contains a flash memory address that will not be subject to pointer arithmetics no risk of alignment issues.
 */



/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: Variable Types                                                */


/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */

#include "EB_Prj.h"
#include "BM_Priv.h"
#include <BM_Trace.h>

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if (BM_NETWORK_FLEXRAY_SUPPORTED == STD_ON)
#include <FrSM.h>
#endif

#if ((BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_OFF) || (BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
#include "board.h"
#if (BM_CSM_PRESENT == STD_ON)
#include "Csm.h"
#endif
#endif
#endif /* (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER) */

/*                                                                               */
/*===============================================================================*/




/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

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
/* - Private Variables                                                           */

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if ((BM_NETWORK_FLEXRAY_SUPPORTED == STD_ON) && (BM_NETWORK_MANAGEMENT_ENABLE == STD_ON))
tBMFRStatus m_ubBMFRStatus;
tBMNetworkStatus m_ubBMNetworkStatus;
tBMCycleCount m_ubBMFRCycleOrigin;
#endif

#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)
tBMTimeout m_ubBMTimeoutCount;
#endif

#if (((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON)) && (BM_BOOT_CHECKSUM_VERIFICATION == STD_ON))
#define BM_BOOT_CKS_START_SEC_VAR
#include <MemMap.h>
/* Bootloader checksum, shall be stored at specific address in order to be set at build time */
const uint8 m_aubExpectedBootloaderChecksum[BM_CHECKSUM_SIZE_IN_BYTES] = {0U};
#define BM_BOOT_CKS_STOP_SEC_VAR
#include <MemMap.h>
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
#if ((BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF) && (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_OFF))
INLINE void BM_BootStartUp(tBMBoolean eBootFromAppl);
#elif ((BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF) && (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON))
INLINE void BM_BootStartUp(tBMBoolean eBootFromAppl, tBMBoolean eNormalStartup);
#else
INLINE void BM_BootStartUp(void);
#endif
#endif /* (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/
/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

#if (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER)
/*----------------------------------{BM_InitialBootStartUp}--------------------------------*/
void BM_InitialBootStartUp(void)
{
    tBMBoolean eBootFromAppl;
    tBMBoolean eBLUValid;
    tBMBoolean eBLValid;
#if (BM_INITIAL_BOOT_APPLICATION_VALIDITY_CHECK == STD_ON)
    tBMBoolean eApplValid;
#endif
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON))
    tBMBoolean IsTrialPeriodActive;
#endif
#if (BM_SECURE_BOOT_ENABLE == STD_ON)
    tBMBoolean ubSoftExecutionAllowed = BM_FALSE;
#endif

    DBG_BM_INITIALBOOTSTARTUP_ENTRY();
#if (BM_OTA_DUALBANK_USED == STD_ON)
    /*Activate Dual Bank*/
    BM_CustomDualBankInit();
#endif /*(BM_OTA_DUALBANK_USED == STD_ON)*/
#if(BM_EXECUTE_TESTAPPL == STD_ON)
    /* Notify Callback to check and execute TestApplication if allowed*/
    BM_CustomAllowTestApplExe();
#endif
    eBLUValid = BM_FALSE;
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON))
    IsTrialPeriodActive = BM_CustomTrialPeriodCheck();
    if(IsTrialPeriodActive == BM_TRUE)
    {
        BM_CustomPerformRollBack();
    }
#endif
    /* Verify if a downloading request have been made in application */
    eBootFromAppl = BM_CheckProgRequest();

    /* if reset didn't came for reprogramming */
    if (BM_FALSE == eBootFromAppl)
    {
#if (BM_INITIAL_BOOT_APPLICATION_VALIDITY_CHECK == STD_ON)
        eApplValid = BM_CustomCheckValidAppl();
        if (BM_TRUE == eApplValid)
        {
            /* Switch to Application (no return) */
            BM_JumpToApplication();
        }
        else
#endif
        {
            eBLUValid = BM_CustomCheckValidBLU();
            if (BM_TRUE == eBLUValid)
            {
#if (BM_SECURE_BOOT_ENABLE == STD_ON)
                ubSoftExecutionAllowed = BM_VerifySoftwareIntegrity();
                /* BLUpdater is started only if checksum is ok */
                if (BM_TRUE == ubSoftExecutionAllowed)
#endif
                {
                    /* Switch to BLU (no return) */
                    BM_JumpToBLU();
                }
            }
        }
    }

    if ((BM_FALSE != eBootFromAppl) || (BM_TRUE != eBLUValid))
    {
        eBLValid = BM_CustomCheckValidBL();
        if (BM_TRUE == eBLValid)
        {
            /* Switch to BL (no return) */
            BM_JumpToBL();
        }
    }

    DBG_BM_INITIALBOOTSTARTUP_EXIT();
}
/*----------------------------------{end BM_InitialBootStartUp}----------------------------*/
#else /* (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER) */

#if ((BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF) && (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_OFF))
INLINE void BM_BootStartUp(tBMBoolean eBootFromAppl)
#elif ((BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF) && (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON))
INLINE void BM_BootStartUp(tBMBoolean eBootFromAppl, tBMBoolean eNormalStartup)
#else
INLINE void BM_BootStartUp(void)
#endif
{
#if (BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF)
#if (BM_SOURCE_ADDRESS_CHECK == STD_ON)
    u16 ubTesterAddress;
#endif
#endif

#if (BM_BOOT_CHECKSUM_VERIFICATION == STD_ON)

    tBMBoolean eOperationSuccess = BM_TRUE;
    tBMBoolean ubCheckOk = BM_TRUE;

#if (BM_CSM_HASH_USED == STD_ON)
    u8 aubComputedBootloaderChecksum[BM_CHECKSUM_SIZE_IN_BYTES];
    u16 uwLoopIndex;

#if (BM_AUTHENTICATED_BOOT_ENABLE == STD_ON)
    tProgStatus eProgStatus;
#endif

#endif

#endif

#if (BM_BOOT_CHECKSUM_VERIFICATION == STD_ON)
#if (BM_AUTHENTICATED_BOOT_ENABLE == STD_ON)
#if (BM_CSM_HASH_USED == STD_ON)
    /* Bootloader checksum shall be verified before starting it */
    eProgStatus = PROG_GetComputedBootloaderChecksum(&aubComputedBootloaderChecksum[0U]);

    if (PROG_E_OK != eProgStatus)
    {
        /* Checksum is not valid and shall be computed */
        /* Deviation MISRAC2012-1 */
       /* Deviation CERTC-1 */
        eOperationSuccess = BM_ComputeHash((u8 const *)BM_BOOT_START_ADDR, BM_BOOT_LENGTH, &aubComputedBootloaderChecksum[0U]);
    }
#elif (BM_CSM_MAC_USED == STD_ON)
    /* Computation of the MAC for the current block */
    /* Comparison to the MAC saved for the same block */
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    eOperationSuccess = BM_VerifyMac(   &m_aubExpectedBootloaderChecksum[0U],
                                        (u8 const *)BM_BOOT_START_ADDR,
                                        BM_BOOT_LENGTH);
#endif
#elif (BM_SECURE_BOOT_ENABLE == STD_ON)
#if (BM_CSM_HASH_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    eOperationSuccess = BM_ComputeHash((u8 const *)BM_BOOT_START_ADDR, BM_BOOT_LENGTH, &aubComputedBootloaderChecksum[0U]);
#elif (BM_CSM_MAC_USED == STD_ON)
    /* Computation of the MAC for the current block */
    /* Comparison to the MAC saved for the same block */
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    eOperationSuccess = BM_VerifyMac(   &m_aubExpectedBootloaderChecksum[0U],
                                        (u8 const *)BM_BOOT_START_ADDR,
                                        BM_BOOT_LENGTH);
#endif
#endif

    if (BM_TRUE == eOperationSuccess)
    {
        ubCheckOk = BM_TRUE;
#if (BM_CSM_HASH_USED == STD_ON)
        for (uwLoopIndex = 0U; ((uwLoopIndex < BM_CHECKSUM_SIZE_IN_BYTES) && (BM_TRUE == ubCheckOk)); uwLoopIndex++)
        {
            if (aubComputedBootloaderChecksum[uwLoopIndex] != m_aubExpectedBootloaderChecksum[uwLoopIndex])
            {
                ubCheckOk = BM_FALSE;
            }
        }
#endif
    }
    else
    {
        ubCheckOk = BM_FALSE;
    }

    /* Bootloader is started only if checksum is ok, else reset is performed */
    if (BM_FALSE == ubCheckOk)
    {
        /* Inform application that Bootloader is not valid */
        BM_CustomSetInvalidBoot();
        BoardPerformSwReset();
        /* Function will not return */
    }
#endif /* (BM_BOOT_CHECKSUM_VERIFICATION == STD_ON) */

    /* Initialization of APP layer */
    APP_Init();

    /* Initialization of all layer */
    EB_Init();


#if (BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF)
    /* Send back the programming session request */
    if (BM_TRUE == eBootFromAppl)
    {
#if (BM_SOURCE_ADDRESS_CHECK == STD_ON)
        /* Get source address of the tester */
        BM_GetTesterAddress(&ubTesterAddress);
        EB_SetTesterAddress(ubTesterAddress);
#endif
        PROG_SimulateOpenProgSession();
#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)
        m_ubBMTimeoutCount = 0U;
#endif
    }
    else
    {
#if (BM_SOURCE_ADDRESS_CHECK == STD_ON)
        EB_SetTesterAddress(EB_ALL_TESTER_ADDRESS);
#endif
#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)
    if (BM_FALSE == eNormalStartup)
    {
        m_ubBMTimeoutCount = ((BM_TIMEOUT_VALUE / BM_CALL_CYCLE)+1U);
    }
#endif
    }

#endif

}

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{BM_StartUp}--------------------------------*/



void BM_StartUp(void)
{

#if (BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF)
    tBMBoolean eBootFromAppl;
#endif

#if (BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF)
    tBMBoolean eApplValid;
#endif
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON)&&(BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF))
    tBMBoolean IsTrialPeriodActive;
#endif
#if ((BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON) && (BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF))
    tBMBoolean eNormalStartup;
#endif

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
    tBMBoolean ubSoftExecutionAllowed = BM_FALSE;
#endif

    DBG_BM_STARTUP_ENTRY();

    /* Hardware initialization */
    BM_HardwareInit();

    /* initialize RAM if required (stack init, copy functions from flash to ram if required) */
    BM_SoftwareInit();

#if (BM_CSM_PRESENT == STD_ON)
    /* Initialize crypto libraries */
    Csm_Init();
#endif

#if ((BM_NETWORK_FLEXRAY_SUPPORTED == STD_ON) && (BM_NETWORK_MANAGEMENT_ENABLE == STD_ON))
    /* Number of FR cycle duration  without FR synchronization before Application check */
    m_ubBMTimeoutCount = (BM_TIMEOUT_VALUE * BM_FR_CYCLE_LENGTH) / BM_CALL_CYCLE;

    /* Initialization of Network Status variable */
    m_ubBMNetworkStatus = BM_FR_NS_INIT;

    /* Initialization of FlexRay Status variable */
    m_ubBMFRStatus = BM_FR_NOTHING_REQUESTED;
#endif
#if (BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF)

    /* Verify if a downloading request have been made in application */
    eBootFromAppl = PROG_CheckProgrammingRequest();

#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)
    /* Identify if normal or abnormal startup is done */
    eNormalStartup = BM_CustomIsNormalStartup();
    if (BM_TRUE == eNormalStartup)
#endif
    {
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON))
    IsTrialPeriodActive = BM_CustomTrialPeriodCheck();
    if(IsTrialPeriodActive == BM_TRUE)
    {
        BM_CustomPerformRollBack();
    }
#endif
        /* if reset didn't came for reprogramming */
        if (BM_FALSE == eBootFromAppl)
        {
            eApplValid = PROG_CheckValidAppl();

            if (BM_TRUE == eApplValid)
            {
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
                 ubSoftExecutionAllowed = BM_VerifySoftwareIntegrity();
                /* Application is started only if checksum is ok */
                if (BM_TRUE == ubSoftExecutionAllowed)
#endif /* ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON)) */

                /* Switch to application (no return)*/
                {
                    PROG_SwitchApplicationMode();
                }
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
                else
                {
                    /* Shutdown ECU */
                    BoardSetSleepState();
                }
#endif
            }
        }
    }
#endif

    /* Bootloader shall be started */
#if (BM_OTA_DUALBANK_USED == STD_ON)
    /*Activate Dual Bank*/
    BM_CustomDualBankInit();
#endif /*(BM_OTA_DUALBANK_USED == STD_ON)*/

#if ((BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF) && (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_OFF))
    BM_BootStartUp(eBootFromAppl);
#elif ((BM_NETWORK_MANAGEMENT_ENABLE == STD_OFF) && (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON))
    BM_BootStartUp(eBootFromAppl,eNormalStartup);
#else
    BM_BootStartUp();
#endif

    DBG_BM_STARTUP_EXIT();
}
/*----------------------------------{end BM_StartUp}----------------------------*/

/*-------------------------------------------------------------------------------*/

#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)

/*----------------------------------{BM_Manage}--------------------------------*/
void BM_Manage (void)
{
    tBMBoolean eApplValid;
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON))
    tBMBoolean IsTrialPeriodActive;
#endif
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
    tBMBoolean ubSoftExecutionAllowed = BM_FALSE;
#endif
#if ((BM_NETWORK_FLEXRAY_SUPPORTED == STD_ON) && (BM_NETWORK_MANAGEMENT_ENABLE == STD_ON))
    u8 ubfrCycle = 0U;
    static u8 m_ubBMValidTime = BM_FALSE;

    DBG_BM_MANAGE_ENTRY();

    if (BM_FR_BOOT_REQUESTED != m_ubBMFRStatus)
    {
        if(EB_TRUE == EB_IsNetworkSynchronized(&ubfrCycle))
        {
            if (m_ubBMValidTime != BM_TRUE)
            {
                /*Save first synchronized cycle without NetworkStatus received*/
                m_ubBMFRCycleOrigin = ubfrCycle;
                /* FlexRay is synchronized therefore, cycle data are correct*/
                m_ubBMValidTime = BM_TRUE;
            }
        }
        else
        {
            if (m_ubBMTimeoutCount > 0U)
            {
                if (m_ubBMTimeoutCount > 1U)
                {
                    m_ubBMTimeoutCount--;
                }
                else
                {
                    m_ubBMTimeoutCount = 0U;
                    m_ubBMFRStatus = BM_FR_APPLI_REQUESTED;
                }
            }
        }

        if (BM_TRUE == m_ubBMValidTime)
        {
            /* The ECU read the NetworkStatus sent by the coordinator */
            m_ubBMNetworkStatus = PROG_GetNetworkStatus();

            /* Check NetworkStatus value */
            switch (m_ubBMNetworkStatus)
            {
                case BM_FR_NS_BOOT:
                    /* Bootloader requested */
                    m_ubBMFRStatus = BM_FR_BOOT_REQUESTED;
                    /* Leave Single Slot mode to authorize Transmission */
                    (void)EB_AllSlots();
                    /*Switch to programming session*/
                    PROG_SimulateOpenProgSession();

                    /* Initialize specific bootloader layers*/
                    /* Initialization of the rest of the bootloader stack */
                    EB_Init2();
                    break;

                case BM_FR_NS_NORMAL:
                case BM_FR_NS_UNDEFINED:
                    /* Application requested */
                    m_ubBMFRStatus = BM_FR_APPLI_REQUESTED;
                    break;

                default:
                    /* Check if the timeout is reached */
                    if(EB_TRUE == EB_IsNetworkSynchronized(&ubfrCycle))
                    {
                        if(ubfrCycle == ((m_ubBMFRCycleOrigin + BM_TIMEOUT_VALUE) % 64U))
                        {
                            /* Application requested */
                            m_ubBMFRStatus = BM_FR_APPLI_REQUESTED;
                        }
                    }
                    break;
            }
        }
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON))
        IsTrialPeriodActive = BM_CustomTrialPeriodCheck();
        if(IsTrialPeriodActive == BM_TRUE)
        {
            BM_CustomPerformRollBack();
        }
#endif
        if(BM_FR_APPLI_REQUESTED == m_ubBMFRStatus)
        {
            eApplValid = PROG_CheckValidAppl();

            if (BM_TRUE == eApplValid)
            {
                /* Switch to application (no return)*/
                PROG_SwitchApplicationMode();
            }
            else
            {
                /* Reset the cycle origin value and counter*/
                m_ubBMFRCycleOrigin = ubfrCycle;
                m_ubBMTimeoutCount = (BM_TIMEOUT_VALUE * BM_FR_CYCLE_LENGTH)/BM_CALL_CYCLE;

                /* Initialization of FlexRay Status variable */
                m_ubBMFRStatus = BM_FR_NOTHING_REQUESTED;
            }
        }
    }
    else
    {
        /* Set all slot mode in case of the bootloader is required */
        /* to make sure diagnostic communication is allowed */
        EB_AllSlots();
    }
#else
    if (UDS_GetCurrentSession() == UDS_SESSION_PROGRAMMING)
    {
        m_ubBMTimeoutCount = 0U;
    }

    if(0U != m_ubBMTimeoutCount)
    {
        if(1U == m_ubBMTimeoutCount)
        {
#if((BM_TRIAL_PERIOD==STD_ON)&&(BM_OTA_DUALBANK_USED == STD_ON))
            IsTrialPeriodActive = BM_CustomTrialPeriodCheck();
            if(IsTrialPeriodActive == BM_TRUE)
            {
                BM_CustomPerformRollBack();
            }
#endif
            eApplValid = PROG_CheckValidAppl();

            if (BM_TRUE == eApplValid)
            {
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
                 ubSoftExecutionAllowed = BM_VerifySoftwareIntegrity();

                /* Application is started only if checksum is ok */
                if (BM_TRUE == ubSoftExecutionAllowed)
#endif /* ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON)) */
                {
                    /* Switch to application (no return)*/
                    PROG_SwitchApplicationMode();
                }
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
                else
                {
                    /* Shutdown ECU */
                    BoardSetSleepState();
                }
#endif
            }
            /* Deactivate the timeout check */
            m_ubBMTimeoutCount = 0U;

            /* No valid application => stay in boot */
        }
        else
        {
            m_ubBMTimeoutCount--;
        }
    }
#endif

    DBG_BM_MANAGE_EXIT();
}
/*----------------------------------{end BM_Manage}----------------------------*/
#endif
#endif /* (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER) */

