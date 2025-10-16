/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 PROG configuration                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cfg_IMPL90.h              */
/*%%  |                             |  %%  \brief PROG layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3              */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]
#ifndef PROG_CFG_IMPL90_H
#define PROG_CFG_IMPL90_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgFord')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
#define PROG_ACTIVE_SBL_RESPONSE_SIZE                   5U
#define PROG_VAL_MEMORY_RESPONSE_SIZE                   6U
#define PROG_ECU_RESET_RESPONSE_SIZE                    2U
#define PROG_DSC_RESPONSE_SIZE                          2U
#define PROG_TD_RESPONSE_SIZE                           2U
#define PROG_RTE_RESPONSE_SIZE                          3U
#define PROG_COMPARE_KEY_RESPONSE_SIZE                  2U
#define PROG_ERASE_POS_RESPONSE_SIZE                    5U
#define PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE             7U
#define PROG_ERASE_REQUEST_DATA                         4U
#define PROG_TD_MIN_SIZE                                2U
#define PROG_TD_MIN_SIZE_RD                             3U
#define PROG_NRC_SIZE                                   3U
#define PROG_RTE_SIZE                                   1U
#define PROG_RTE_RESPONSE_BASE_INDEX                    1U
#define PROG_RC_VAL_MEMORY_STATUS_INDEX                 4U
#define PROG_RC_VAL_MEMORY_RESULT_INDEX                 5U
#define PROG_ERASE_ADDR_LEN                             4U
#define PROG_ERASE_SIZE_LEN                             4U

#define PROG_EXPECTED_VS_VERSION            [!"num:inttohex(VerificationStructure/Verification_Structure_Version)"!]U
#define PROG_SIGNATURE_PASSED               0x00U
#define PROG_WRONG_SIGNATURE                0x01U
#define PROG_INVALID_VS_VERSION             0x02U
#define PROG_INVALID_VS_BLKNBR              0x03U
#define PROG_WRONG_HASH                     0x04U
#define PROG_VS_MEMORY_READERROR            0x05U
#define PROG_VS_BLOCK_MISMATCH              0x06U
#define PROG_VALIDITY_ROUTINE_NOTEXEC       0xFFU


#define PROG_SBL_VALIDITY_FLAG_OFF                      120U
#define PROG_SBL_VALIDITY_FLAG                          0xAF5A50A5U

#define PROG_SBL_SOFTWARE_VERSION                       0x00000004U

#define PROG_ERASE_TYPE                                 PROG_ERASE_BY_ADDR
/* Data verification */
#define PROG_VERIFICATION_METHOD                        PROG_VERIFICATION_HASH
#define PROG_CRC_CALCULATION                            PROG_TD_CRC16
#define PROG_SIGNATURE_CALCULATION                      STD_ON
#define PROG_HASH_CALCULATION                           STD_ON
#define PROG_RANGE_CKS                                  STD_OFF
#define PROG_SEG_LIST_CKS                               STD_ON
#define PROG_VERIFICATION_ON_THE_FLY                    STD_ON
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA     STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_ON
#define PROG_DOWNLOAD_TYPE                              PROG_DOWNLOAD_BY_ADDR
#define PROG_MAX_RD_ADDRESS_LENGTH                      4U
#define PROG_CVN_CHECK                                  STD_OFF


/* !!!! To Be Generated once Csm stub will be available !!!!*/
#define PROG_CRY_PRESENT                                STD_ON
#define PROG_CAL_PRESENT                                STD_OFF
#define PROG_CRYSHE_PRESENT                             STD_OFF

#define PROG_KEY_LENGTH                                 256U
#define PROG_MOD_LENGTH                                 4U
#define PROG_SIGNATURE_LENGTH                           256U
#define PROG_CRY_EXPONENT_ENABLED                       STD_ON
/*Length of Asymmetric Key in DER Format*/
#define PROG_KEY_DER_LENGTH                            (PROG_KEY_LENGTH + PROG_MOD_LENGTH + 8U)                     
/* Routine type defines */
#define PROG_ROUTINE_TYPE_1                             0x10U
#define PROG_ROUTINE_TYPE_2                             0x20U
#define PROG_ROUTINE_TYPE_3                             0x30U

/* Routine status defines */
#define PROG_ROUTINE_FINISHED_OK                        0x00U
#define PROG_ROUTINE_FINISHED_NOK                       0x01U
#define PROG_ROUTINE_IN_PROGRESS                        0x02U

/* Return value for a valid application  (0 means ok)*/
#define PROG_APPL_VALID                                 0x00000000U
/* Return value if the compare and compatible block is not coherent */
#define PROG_APPL_INVALID                               0x00000005U

#define PROG_AUTOCONTROL_POS_RESPONSE_SIZE              9U

#define PROG_GET_PROG_CNTR_ENABLE                       1U
#define PROG_GET_PROG_CNTR_DISABLE                      0U
#define PROG_CNTR_GET_TYPE                              PROG_GET_PROG_CNTR_DISABLE
 
#define PROG_REPROG_TYPE                                PROG_NO_REPROG_TYPE

[!IF "General/Network_Management = 'true'"!]
#define PROG_FR_NS_INIT                                 0x0000U
#define PROG_FR_NS_NORMAL                               0x0001U
#define PROG_FR_NS_BOOT                                 0x1000U
#define PROG_FR_NS_UNDEFINED                            0x2000U
[!ENDIF!]

#define PROG_GET_EXPECTED_CRC_ENABLED                   STD_OFF
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                 STD_OFF

/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                     STD_OFF

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                     STD_OFF

#define PROG_DECOMP_FLASH_ROUTINES                      STD_OFF

#define PROG_SIGNATURE_CALCULATION_OVER_HASH            STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                 STD_OFF
#define PROG_RESUM_REPROG                               STD_OFF

#define PROG_P2_PROG_SESSION_VAL                           [!WS "27"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2"!]U
#define PROG_P2STAR_PROG_SESSION_VAL                       [!WS "23"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2STAR"!]U
#define PROG_P2_DEFAULT_SESSION_VAL                        [!WS "24"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2"!]U
#define PROG_P2STAR_DEFAULT_SESSION_VAL                    [!WS "20"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2STAR"!]U

#define PROG_2_SUCCESSIVE_CHECKMEMORY_ALLOWED           STD_OFF

[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[[!"num:dectoint(count(Segments/*))"!]];
 [!ENDIF!]

[!IF "as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL'"!]
[!/********************* Feature configuration for Ford PBL ************************/!]

#define PROG_IMPL_VARIANT                               PROG_IMPL_90

#define PROG_WATCHDOG_ENABLE                            STD_ON
#define PROG_REQUEST_DOWNLOAD_ENABLE                    STD_ON
#define PROG_SECURITY_ENABLE                            STD_ON
#define PROG_SA_SEED_ENABLE                             STD_ON
#define PROG_SA_KEY_ENABLE                              STD_ON
#define PROG_ERASE_MEMORY_ENABLE                        STD_OFF
#define PROG_TRANSFER_DATA_ENABLE                       STD_ON
#define PROG_REQUEST_TRANSFER_EXIT_ENABLE               STD_ON
#define PROG_ECU_RESET_ENABLE                           STD_ON
#define PROG_ACTIVE_SBL_ENABLE                          STD_ON
#define PROG_UPDATE_PSI_ENABLE                          STD_OFF
#define PROG_CONTROL_DTC_SETTING_ENABLE                 STD_OFF
#define PROG_COMMUNICATION_CONTROL_ENABLE               STD_OFF
#define PROG_CHECK_MEMORY_ENABLE                        STD_OFF
#define PROG_SET_CRC_COMPARE_RESULT_ENABLE              STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE    STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE     STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE      STD_ON
#define PROG_NETWORK_MANAGEMENT_ENABLE                  STD_OFF
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_PEC_ENABLE                                 STD_OFF
#define PROG_MULTIPLE_BUFFERS_ENABLE                    [!WS "20"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BYPASS_SA_COMPARE_KEY                      [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_SBL_HEADER_DEFINE                          STD_OFF
#define PROG_ENABLE_DOWNGRADE_PROTECTION                STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE             STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE           STD_ON
#define PROG_CAL_CRC_ENABLE                             STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                 STD_OFF
#define PROG_PRE_INIT_ENABLE                            STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                   STD_OFF

#define PROG_SLEEP_MANAGEMENT_TYPE [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT   [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
#define PROG_ERASE_ALL                                  STD_OFF

#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_SECURE_BOOT_ENABLE                         [!WS "25"!][!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BOOT_VERIFICATION                          [!WS "26"!][!IF "(as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF

#define PROG_CSM_MAC_USED                               STD_OFF
#define PROG_CSM_HASH_USED                              STD_OFF

#define PROG_SBL_VS_START_ADDRESS                      [!"num:inttohex(SBLVerificationStructure/Verification_Structure_Start_Address)"!]U
#define PROG_SBL_VS_LENGTH                             [!"num:inttohex(SBLVerificationStructure/Verification_Structure_Length)"!]U
#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

[!ELSEIF "as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'"!]
[!/********************* Feature configuration for Ford SBL ************************/!]
#define PROG_IMPL_VARIANT                               PROG_IMPL_91

#define PROG_WATCHDOG_ENABLE                            STD_ON
#define PROG_REQUEST_DOWNLOAD_ENABLE                    STD_ON
#define PROG_SECURITY_ENABLE                            STD_ON
#define PROG_SA_SEED_ENABLE                             STD_ON
#define PROG_SA_KEY_ENABLE                              STD_ON
#define PROG_ERASE_MEMORY_ENABLE                        STD_ON
#define PROG_TRANSFER_DATA_ENABLE                       STD_ON
#define PROG_REQUEST_TRANSFER_EXIT_ENABLE               STD_ON
#define PROG_ECU_RESET_ENABLE                           STD_ON
#define PROG_ACTIVE_SBL_ENABLE                          STD_OFF
#define PROG_UPDATE_PSI_ENABLE                          STD_OFF
#define PROG_CONTROL_DTC_SETTING_ENABLE                 STD_OFF
#define PROG_COMMUNICATION_CONTROL_ENABLE               STD_OFF
#define PROG_CHECK_MEMORY_ENABLE                        STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE    STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE     STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE      STD_ON
#define PROG_NETWORK_MANAGEMENT_ENABLE                  STD_OFF
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_PEC_ENABLE                                 STD_OFF
#define PROG_MULTIPLE_BUFFERS_ENABLE                    [!WS "20"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BYPASS_SA_COMPARE_KEY                      [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_SBL_HEADER_DEFINE                          STD_ON
#define PROG_ENABLE_DOWNGRADE_PROTECTION                STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE             STD_OFF
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE           STD_OFF
#define PROG_CAL_CRC_ENABLE                             STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                 STD_ON
#define PROG_PRE_INIT_ENABLE                            STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                   STD_OFF

#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_SECURE_BOOT_ENABLE                         STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
[!IF "(as:modconf('Prog')/Security/Secure_Checksum_computation = 'true') or
 ((node:exists(as:modconf('BM'))) and (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))"!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
[!IF "(node:exists(as:modconf('BM'))) and (node:exists(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm))
         and (as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true')"!]
#define PROG_CSM_MAC_USED                               STD_OFF
[!ELSE!]
#define PROG_CSM_MAC_USED                               STD_ON
#define PROG_CSM_SECURE_MAC_ID                          CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
#define PROG_SECURE_CHECKSUM_SIZE_IN_BITS               [!"num:dectoint((as:modconf('Prog')/Security/CHECKSUM_LENGTH) * 8)"!]U
#define PROG_SECURE_CHECKSUM_SIZE_IN_BYTES              [!"num:dectoint(as:modconf('Prog')/Security/CHECKSUM_LENGTH)"!]U
 [!ENDIF!]
[!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
#define PROG_CSM_MAC_USED                               STD_OFF
[!ENDIF!]
#define PROG_CSM_HASH_USED                              STD_OFF

#define PROG_SLEEP_MANAGEMENT_TYPE [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT   [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]

#define PROG_ERASE_ALL                                  STD_OFF

[!ELSE!]
[!ERROR "The Ford variant configured in ProgFord is unknown"!]
[!ENDIF!] [!/* as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' */!]

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                    STD_OFF
/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE              STD_OFF
/*Security access antiscanning*/
[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define PROG_ANTISCANNING_ENABLED                       STD_ON
[!ELSE!]
#define PROG_ANTISCANNING_ENABLED                       STD_OFF
[!ENDIF!]
/* Security access limit request seed */
[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_ON
[!ELSE!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_OFF
[!ENDIF!]
/*Enable the response after reset in function of reset cause*/
#define PROG_RESET_CAUSE_ENABLE                         STD_OFF
/* Programming pre-conditions check */
#define PROG_PRECOND_CHECK_ENABLE                       STD_OFF
/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                     STD_OFF
#define PROG_USE_ECUID_CALLBACK                         STD_OFF

/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                    STD_OFF

/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                         STD_OFF

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                         STD_OFF

#define PROG_BLOCK_NB   1U
extern const tProg_Block     stCfgBlock[PROG_BLOCK_NB];
[!ENDIF!]

/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE             STD_OFF

/* Downloading Pseudo Flash driver feature activation */
#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_ENABLE      STD_OFF

#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_OFF

/*Securiy access request seed delay timer*/
[!IF "as:modconf('SA')/General/Security_Access_Rs_Delay_Timer != '0'"!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_ON
[!ELSE!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_OFF
[!ENDIF!]

/*Introduced below the compiler switch to support Fingerprint for the Segments in RAM*/
#ifndef PROG_RAMSEG_FINGERPRINT_SUPPORT
#define PROG_RAMSEG_FINGERPRINT_SUPPORT STD_OFF
#endif
[!VAR "SECUREDKEYS_READ"="0"!]

/*SecuredKeys Read Programming status using DID*/

#define PROG_SA_SECUREDKEYS_STATUSREAD                  STD_OFF

#endif /* PROG_CFG_IMPL90_H */
