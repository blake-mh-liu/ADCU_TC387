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
/*%%   _____________________________   %%  \file BM_Cbk.h                        */
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



#ifndef BM_CBK_H
#define BM_CBK_H
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/* - Public Callback Prototypes                                                  */

[!IF "as:modconf('BM')/General/Dual_Memory_Bank_Used = 'true'"!]
/** \brief Initialize the Dual Memory Bank
 **
 ** This function is called when Bootloader starts
 ** to prepare the usage of the dual memory banks.
 **
 **/
extern void BM_CustomDualBankInit(void);

[!IF "as:modconf('BM')/General/Trial_period = 'true'"!]
/** \brief trigger the rollback function
 **
 ** This function is called to perform a roolback followed by reset
 **
 **/
extern void BM_CustomPerformRollBack(void);

/** \brief get the trial peirod flag status
 **
 ** This function is called to check if trial period is active
 **
 **/
extern tBMBoolean BM_CustomTrialPeriodCheck(void);
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager""!]
/** \brief API that check if a programming request has been received by the application
 **
 ** Callback is called: at Initial Boot startup to know if a programming request has
 **                     been received in Application
 **
 ** Callback shall implement: get information from application if a programming
 **                          request has been received (e.g: read a flag from
 **                          noinit RAM shared between Bootloader and
 **                           Application)
 **
 ** \return Result of check
 ** \retval TRUE Reprogramming request has been received
 ** \retval FALSE No reprogramming request received
 **/
extern tBMBoolean BM_CheckProgRequest(void);

/** \brief Callback checking if the application is valid or not
 **
 ** Callback is called: at Initial Boot startup.
 **
 ** Callback shall implement: It shall verify that the application
 ** with all its dependencies are correctly flashed
 ** and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid or not present
 **/
extern tBMBoolean BM_CustomCheckValidAppl(void);

/** \brief Callback checking if the Bootloader Updater Programm is valid or not
 **
 ** Callback is called: at Initial Boot startup.
 **
 ** Callback shall implement: It shall verify that the Bootloader Updater Programm
 ** is correctly flashed and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE BLU Updater Programm is valid
 ** \retval FALSE BLU is not valid or not present
 **/
extern tBMBoolean BM_CustomCheckValidBLU(void);

/** \brief Callback checking if the Bootloader is valid or not
 **
 ** Callback is called: at Initial Boot startup.
 **
 ** Callback shall implement: It shall verify that the Bootloader
 ** is correctly flashed and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE Bootloader is valid
 ** \retval FALSE Bootloader is not valid or not present
 **/
extern tBMBoolean BM_CustomCheckValidBL(void);

/** \brief Callback performing jump to application software
 **
 ** Callback is called: at Initial Boot startup if application is valid and shall
 **                    be executed
 **
 ** Callback shall implement: jump to application start address
 **
 **/
extern void BM_JumpToApplication(void);

/** \brief Callback performing jump to Bootloader Updater Programm
 **
 ** Callback is called: at Initial Boot startup if Bootloader Updater Programm is 
 ** valid and shall be executed
 **
 ** Callback shall implement: jump to BLU start address
 **
 **/
extern void BM_JumpToBLU(void);

/** \brief Callback performing jump to Bootloader
 **
 ** Callback is called: at Initial Boot startup if Bootloader is valid and shall
 **                    be executed
 **
 ** Callback shall implement: jump to Bootloader start address
 **
 **/
extern void BM_JumpToBL(void);
[!IF "General/Test_Application = 'true'"!]
 /** \brief Notify the Integration-code to check and allow Test-Application execution
  **
  ** This function is called at the startup to notify the Integration code to verify and
  ** execute the Test-Application if allowed to be executed.
  ** If the execution of the Test-Application is not allowed, callback shall return
  ** the control to BM.
  **/
extern void BM_CustomAllowTestApplExe(void);
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]
 /** \brief Notification that Application is invalid
  **
  ** This function is called when BLUpdater checksum
  ** verification failed and that BLUpdater cannot be started.
  ** This information shall be store in non-volatile memory.
  **
  **/
extern void BM_CustomSetInvalidBlu(void);
[!ENDIF!]
[!ENDIF!]
/** \brief Callback that shall disable ECC if needed
 ** Callback is called: When Bootloader perform read access on Flash that can be
 **                     unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, disabling of ECC check
 **                           Hardware specific)
 **/
extern void BM_DisableECCCheck(void);

/** \brief Callback that shall enable ECC if needed
 ** Callback is called: After Bootloader has performed a read access on Flash
 **                    that can be unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, enabling of ECC check
 **                          (Hardware specific)
 **/
extern void BM_EnableECCCheck(void);

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or
    (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))"!]

/** \brief Allow customer operation during long operation
 **
 ** This function is called during long operation (e.g. cryptography)
 ** allowing customer performing actions that cannot be stopped during
 ** a long time (e.g watchdog triggering).
 **
 **/
extern void BM_CustomBckOperation (void);


[!IF "as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true'"!]
/** \brief Verify the Mac with HSM
 ** This function is called to trigger a Mac verification for corresponding block
 **
 ** \param[in] uwBlockId Block Identifier
 **
 ** \return Result of check
 ** \retval BM_HSM_JOB_OK Mac verification succeed
 ** \retval BM_HSM_JOB_FAILED Mac verification failed
 ** \retval BM_HSM_JOB_PENDING Mac verification is pending
 **
 **/
extern tBMHsmJobResult BM_CustomHsmVerifyMac(u16 uwBlockId);
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Boot Manager""!]
/** \brief Software RAM initialization
 **
 ** This function is called at the very beginning of the Boot manager.
 ** It allows the application to do the minimum software initialization
 ** before the Boot manager start to check the application validity.
 **
 **/
extern void BM_SoftwareInit(void);

/** \brief Hardware initialization
 **
 ** This function is called at the very beginning of the Boot manager.
 ** It allows the application to do the minimum hardware initialization
 ** before the Boot manager start to check the application validity.
 **
 **/
extern void BM_HardwareInit (void);

/** \brief Get the diagnostic tester source address
 **
 ** This function is called when programming is requested by
 ** application (eBootFromAppli = BM_TRUE) and BM_SOURCE_ADDRESS_CHECK is set.
 ** This is a callback that get the tester address
 **
 ** \param[in,out] ubTesterAddress pointer on tester address
 **
 **/
#if (BM_SOURCE_ADDRESS_CHECK == STD_ON)
extern void BM_GetTesterAddress (u16 *ubTesterAddress);
#endif

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]
/** \brief Get the last computed application checksum
 **
 ** This function is called at Bootloader startup to
 ** verify the application checksum before allowing
 ** the start of application. This checksum shall have been
 ** computed by application on configured application data range.
 **
 ** \param[out] pubChecksum address where the computed checksum shall be copied
 ** \param[in] uwBlockIdentifier Block Identifier
 **
 **/
extern void BM_CustomGetComputedApplicationChecksum (u8 *pubChecksum, u16 uwBlockIdentifier);
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or
    (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))"!]
  [!IF "Security/SecureBoot/BMSecureBootWithHsm = 'false'"!]
/** \brief Get the expected application checksum
 **
 ** This function is called at Bootloader startup to
 ** verify the application checksum before allowing
 ** the start of application. It gets from non-volatile
 ** memory the checksum that had been computed during
 ** the last application download.
 **
 ** \param[out] pubChecksum address where the checksum shall be copied
 ** \param[in] uwBlockIdentifier Block Identifier
 **
 **/
extern void BM_CustomGetExpectedApplicationChecksum (u8 *pubChecksum, u16 uwBlockIdentifier);
  [!ENDIF!]
/** \brief Notification that Application is invalid
 **
 ** This function is called when Application checksum
 ** verification failed and that Application cannot be started.
 ** This information shall be store in non-volatile memory.
 **
 ** \param[in] uwBlockIdentifier Identifier of invalid Block
 **
 **/
extern void BM_CustomSetInvalidAppli (u16 uwBlockIdentifier);
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))
and (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]
/** \brief Notification that Bootloader is invalid
 **
 ** This function is called when Bootloader checksum
 ** verification failed and that Bootloader cannot be started.
 ** By this callback application shall be informed that Bootloader
 ** cannot be executed anymore.
 **
 **/
extern void BM_CustomSetInvalidBoot (void);
[!ENDIF!]

#if (BM_CSM_MAC_USED == STD_ON)
/** \brief Get the mac key used in Mac verification (should be the same key used in the generation)
 **
 ** This function is called at the beginning of the Mac verification to get the key yo be used in the process
 **
 **/
extern void BM_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength);
#endif
/*                                                                               */
/*===============================================================================*/


[!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
/** \brief Request if ECU has started normally or not
 **
 ** This function is called at startup to know if normal or abnormal startup has been done.
 ** In case of abnormal startup ECU stay in Bootloader mode during a configured time
 ** before jumping to application (if valid).
 ** This time window allow the tester to send a programming session request to force the Boot mode
 **
 **/
extern tBMBoolean BM_CustomIsNormalStartup(void);
[!ENDIF!]
[!ENDIF!]
#endif      /* BM_CBK_H */
