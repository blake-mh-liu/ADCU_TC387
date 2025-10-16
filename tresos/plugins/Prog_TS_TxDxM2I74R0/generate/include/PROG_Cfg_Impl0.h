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
/*%%   _____________________________   %%  \file PROG_Cfg_Impl0.h                */
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
#ifndef PROG_CFG_IMPL0_H
#define PROG_CFG_IMPL0_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgJLR')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!IF "node:exists(as:modconf('ProgJLR'))"!]
#define PROG_ACTIVE_SBL_RESPONSE_SIZE                   5U
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
#define PROG_BLK_APP                                    0U
#define PROG_BLK_CAL                                    1U
#define PROG_BLK_APP1                                   2U
#define PROG_BLK_CAL1                                   3U
#define PROG_BLK_RAM                                    4U
#define POSTSOFTWAREDOWNLOAD_DEFAULTSTATUS                0xFFU
#define POSTSOFTWAREDOWNLOAD_PROG_ERASE_STATUS_FAILED     0x01U
#define POSTSOFTWAREDOWNLOAD_ERASE_STATUS_SUCCESS         0x16U
#define POSTSOFTWAREDOWNLOAD_PROG_STATUS_SUCCESS          0x04U
#define POSTSOFTWAREDOWNLOAD_BLOCKVALIDATION_FAILED       0x02U
#define POSTSOFTWAREDOWNLOAD_CHECKVALIDAPLLI_FAILED       0X1BU
#define POSTSOFTWAREDOWNLOAD_CHECKVALIDAPLLI_PASSED       0X1AU

#define PROG_ERASE_ADDR_LEN                             4U
#define PROG_ERASE_SIZE_LEN                             4U

#define PROG_RESPONSE_PARAMETERS_OFFSET                 (u8) (1U)/* This define is used because the tables in C starts from 0 and not 1
                                                                    and the indexes in the specifications starts sometimes from 1 */

#define PROG_RTE_RESPONSE_BASE_INDEX                    PROG_MSG_BYTE_INDEX(2U)
#define PROG_RC_ROUTINE_STATUS_BASE_INDEX               PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_BASE_INDEX  PROG_RC_ROUTINE_STATUS_BASE_INDEX
 
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIZE        6U
 
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_OK          1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_NOT_OK      2U

#define PROG_SBL_VALIDITY_FLAG_OFF                      120U
#define PROG_SBL_VALIDITY_FLAG                          0xAF5A50A5U

#define PROG_SBL_SOFTWARE_VERSION                       0x00000004U

#define PROG_ERASE_TYPE                                 PROG_ERASE_BY_ADDR
/* Data verification */
#define PROG_RANGE_CKS                                  STD_OFF
#define PROG_SEG_LIST_CKS                               STD_OFF
#define PROG_GET_EXPECTED_CRC_ENABLED                   STD_OFF
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                 STD_OFF
#define PROG_VERIFICATION_ON_THE_FLY                    STD_ON
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA     STD_ON
#define PROG_CVN_CHECK                                  STD_OFF

#define PROG_DOWNLOAD_TYPE                              PROG_DOWNLOAD_BY_ADDR
#define PROG_MAX_RD_ADDRESS_LENGTH                      4U
/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                1U

 [!IF "node:exists(as:modconf('Csm'))"!]
/* !!!! To Be Generated once Csm stub will be available !!!!*/
#define PROG_CRY_PRESENT                                STD_ON
  [!ELSE!]
#define PROG_CRY_PRESENT                                STD_OFF
  [!ENDIF!]
 [!IF "node:exists(as:modconf('CryShe'))"!]
#define PROG_CRYSHE_PRESENT                                STD_ON
  [!ELSE!]
#define PROG_CRYSHE_PRESENT                                STD_OFF
  [!ENDIF!]
[!IF "node:exists(as:modconf('Cal'))"!]
#define PROG_CAL_PRESENT                                   STD_ON
[!ELSE!]
#define PROG_CAL_PRESENT                                   STD_OFF
[!ENDIF!]

/* specific routine result value */
#define PROG_ROUTINE_ACTIVE                             0x01U
#define PROG_ROUTINE_RESAVAILABLE                       0x02U
#define PROG_ROUTINE_PREDIF                             0x08U
#define PROG_ROUTINE_STOP_SUBFUNC                       0x10U
#define PROG_ROUTINE_RES_SUBFUNC                        0x20U
#define PROG_ROUTINE_SELFTERM                           0x40U
#define PROG_ROUTINE_AUTONOMOUS                         0x80U

#define PROG_APPL_VALID                                 0x00000002U
#define PROG_APPL_INVALID                               0x00000001U

#define PROG_AUTOCONTROL_POS_RESPONSE_SIZE              6U

/* Routine status defines */
#define PROG_ROUTINE_FINISHED_OK                        0x00U

/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                     STD_OFF

#define PROG_GET_PROG_CNTR_ENABLE                       1U
#define PROG_GET_PROG_CNTR_DISABLE                      0U
#define PROG_CNTR_GET_TYPE                              PROG_GET_PROG_CNTR_DISABLE

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                     STD_OFF

#define PROG_DECOMP_FLASH_ROUTINES                      STD_OFF

#define PROG_SIGNATURE_CALCULATION_OVER_HASH            STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                 STD_OFF
#define PROG_RESUM_REPROG                               STD_OFF

#define PROG_REPROG_TYPE                                PROG_NO_REPROG_TYPE

#define PROG_CHECKVALIDATEAPPLICATION_POS_RESPONSE_SIZE 6U

 [!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false')) and
   (not(node:exists(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm)) or (as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false')) "!]
 #define PROG_SECURE_CHECKSUM_SIZE_IN_BITS               [!"num:dectoint((as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH) * 8)"!]U
 #define PROG_SECURE_CHECKSUM_SIZE_IN_BYTES              [!"num:dectoint(as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH)"!]U

 [!IF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmHash/') =  'true')) or
     ((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmHash)) )"!]
/* Secure Boot Algorithm used */
 #define PROG_CSM_SECURE_HASH_ID                         CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
 #define PROG_CSM_HASH_USED                              STD_ON
 #define PROG_CSM_MAC_USED                               STD_OFF
 [!ELSEIF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmMacGenerate/') =  'true')) or
     ((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
/* Secure Boot Algorithm used */
#define PROG_CSM_SECURE_MAC_ID                          CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
 #define PROG_CSM_HASH_USED                              STD_OFF
 #define PROG_CSM_MAC_USED                               STD_ON
 [!ELSE!]
 #define PROG_CSM_HASH_USED                              STD_OFF
 #define PROG_CSM_MAC_USED                               STD_OFF
 [!ENDIF!]
 [!ELSE!]
 #define PROG_CSM_HASH_USED                              STD_OFF
 #define PROG_CSM_MAC_USED                               STD_OFF
 [!ENDIF!]
  [!ELSE!]
#define PROG_CSM_HASH_USED                              STD_OFF
#define PROG_CSM_MAC_USED                               STD_OFF
[!ENDIF!]
 [!IF "(as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or 
       (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL') "!]
/* Macros to indicate operation type for the VDS table callback operations */
#define PROG_VDSUPDATE_CLEAR                            0U
#define PROG_VDSUPDATE_STORE                            1U
#define PROG_VDSUPDATE_GETSEGID_BYADR                   2U
#define PROG_VDSUPDATE_READVDS                          3U
  [!ENDIF!]
[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL_WITH_EB_FRAMEWORK'"!]
[!/********************* Feature configuration for JLR PBL with framework ************************/!]

#define PROG_IMPL_VARIANT           PROG_IMPL_1

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
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE    STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE     STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE      STD_ON
#define PROG_NETWORK_MANAGEMENT_ENABLE                  STD_OFF
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_PEC_ENABLE                                 STD_OFF
#define PROG_MULTIPLE_BUFFERS_ENABLE                    [!WS "20"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BYPASS_SA_COMPARE_KEY                      [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_SBL_HEADER_DEFINE                          STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE             STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE           STD_ON
#define PROG_CAL_CRC_ENABLE                             STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                 STD_OFF
#define PROG_PRE_INIT_ENABLE                            STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                   STD_OFF
#define PROG_ERASE_ALL                                  STD_OFF

#define PROG_ENABLE_DOWNGRADE_PROTECTION                STD_OFF

#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_OFF

#define PROG_HASH_CALCULATION                           STD_OFF
#define PROG_SIGNATURE_CALCULATION                      STD_OFF

#define PROG_VERIFICATION_METHOD                        PROG_VERIFICATION_CRC
#define PROG_CRC_CALCULATION                            PROG_TD_CRC16

#define PROG_SLEEP_MANAGEMENT_TYPE [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT   [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
#define PROG_CURRENT_DIAG_APP        1U

#define PROG_FRAMEWORK_PARTID_1                         0xA5F0BBBBU
#define PROG_FRAMEWORK_PARTID_2                         0xA0F5CCCCU

#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

#define PROG_CheckProgRequest()                         checkProgrammingRequest()
#define PROG_JumpToApplication()                        jumpToApplication()

[!ELSEIF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
[!/********************* Feature configuration for JLR SBL with framework ************************/!]
#define PROG_IMPL_VARIANT           PROG_IMPL_2

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
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_PEC_ENABLE                                 STD_OFF
#define PROG_MULTIPLE_BUFFERS_ENABLE                    [!WS "20"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BYPASS_SA_COMPARE_KEY                      [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_SBL_HEADER_DEFINE                          STD_ON

#define PROG_SWITCH_APPLICATION_MODE_ENABLE             STD_OFF
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE           STD_OFF
#define PROG_CAL_CRC_ENABLE                             STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                 STD_ON
#define PROG_PRE_INIT_ENABLE                            STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                   STD_OFF
#define PROG_ERASE_ALL                                  STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_OFF

#define PROG_ENABLE_DOWNGRADE_PROTECTION                STD_OFF

#define PROG_HASH_CALCULATION                           STD_OFF
#define PROG_SIGNATURE_CALCULATION                      STD_OFF

#define PROG_VERIFICATION_METHOD                        PROG_VERIFICATION_CRC
#define PROG_CRC_CALCULATION                            PROG_TD_CRC16

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
#define PROG_CURRENT_DIAG_APP                           2U

#define PROG_FRAMEWORK_PARTID_1                         0xA5F0BBBBU
#define PROG_FRAMEWORK_PARTID_2                         0xA0F5CCCCU
#define PROG_FLASH_PAGE_E_NOT_OK                        0U
#define PROG_FLASH_PAGE_E_OK                            1U
#define PROG_NO_SKIP_PAGE                               0U
#define PROG_SKIP_PAGE                                  1U

[!ELSEIF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'"!]
[!/********************* Feature configuration for JLR PBL ************************/!]

#define PROG_IMPL_VARIANT                               PROG_IMPL_3

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
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE    STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE     STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE      STD_ON
#define PROG_NETWORK_MANAGEMENT_ENABLE                  STD_OFF
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
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
#define PROG_ERASE_ALL                                  STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
[!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
 [!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
 [!ENDIF!]
[!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
[!ENDIF!]
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                 STD_ON

#define PROG_HASH_CALCULATION                            STD_ON
#define PROG_SIGNATURE_CALCULATION                       STD_ON

#define PROG_VERIFICATION_METHOD                         0xFFU

/* !!!! To Be Generated once Csm stub will be available !!!!*/
[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "node:exists(as:modconf('CryIf'))"!]
	[!VAR "AlgoMode" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyAlgorithmMode)"!]
	[!VAR "Key_Length" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyKeyLength)"!]
	[!VAR "Signature_Length" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyCompareLength)"!]

/* Key Length shall be configured based on the value provided in the Csm job conf paramater- CsmSignatureVerifyKeyLength */
#define PROG_KEY_LENGTH                                    [!WS "34"!][!"$Key_Length"!]U /* In bytes */
/* Signature Length shall be configured based on the value provided in the Csm job conf paramater- CsmSignatureVerifyCompareLength */
#define PROG_SIGNATURE_LENGTH                              [!WS "28"!][!"$Signature_Length"!]U
    [!IF "$AlgoMode = 'CRYPTO_ALGOMODE_RSASSA_PSS'"!]
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
    [!ELSE!]
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
    [!ENDIF!]
[!ELSE!]
    [!IF "((as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))/CsmSignatureVerifyPrimitiveName) = 'EdDSAVrfy'"!]
#define PROG_KEY_LENGTH                                    32U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              64U
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
	[!ELSEIF "((as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))/CsmSignatureVerifyPrimitiveName) = 'RsaSsaPssVerify'"!]
#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
	 [!ELSE!]
/* Default Config for all the unsupported algorithms configured */
#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
	[!ENDIF!]
[!ENDIF!]
[!ENDIF!]

#define PROG_CRC_CALCULATION                            PROG_NO_CRC
 
#define PROG_RC_OPTION_RECORD_SIGNATURE_BASE_INDEX      PROG_MSG_BYTE_INDEX(5U)

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
#define PROG_CURRENT_DIAG_APP                           1U

#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

#define PROG_FRAMEWORK_PARTID_1                         0xA5F0BBBBU
#define PROG_FRAMEWORK_PARTID_2                         0xA0F5CCCCU
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
  extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[[!"num:dectoint(count(Segments/*))"!]];
 [!ENDIF!]
[!ELSEIF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'"!]
[!/********************* Feature configuration for JLR SBL ************************/!]
#define PROG_IMPL_VARIANT                               PROG_IMPL_4

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
#define PROG_SET_CRC_COMPARE_RESULT_ENABLE              STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE    STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE     STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE      STD_ON
#define PROG_NETWORK_MANAGEMENT_ENABLE                  STD_OFF
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
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

#define PROG_ERASE_ALL                                  STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
 [!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
 [!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
 [!ENDIF!]
[!ELSEIF "(not(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true'))"!]
 #define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
 [!ELSE!]
  #define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
 [!ENDIF!]
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_ON
[!IF "(as:modconf('Prog')/Security/Submit_signature_request='With Address')"!]
#define PROG_SUBMITSIGNATURE_WITH_ADDRESS               STD_ON
#define PROG_RC_OPTION_RECORD_HASH_TAB_ADD_BASE_INDEX   PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_OPTION_RECORD_SIGNATURE_BASE_INDEX      PROG_MSG_BYTE_INDEX(9U)
[!ELSE!]
#define PROG_SUBMITSIGNATURE_WITH_ADDRESS               STD_OFF
#define PROG_RC_OPTION_RECORD_SIGNATURE_BASE_INDEX      PROG_MSG_BYTE_INDEX(5U)
[!ENDIF!]

#define PROG_HASH_CALCULATION                           STD_ON
#define PROG_SIGNATURE_CALCULATION                      STD_ON

#define PROG_VERIFICATION_METHOD                        0xFFU

/* !!!! To Be Generated once Csm stub will be available !!!!*/
[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "node:exists(as:modconf('CryIf'))"!]
	[!VAR "AlgoMode" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyAlgorithmMode)"!]
	[!VAR "Key_Length" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyKeyLength)"!]
	[!VAR "Signature_Length" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyCompareLength)"!]


/* Key Length shall be configured based on the value provided in the Csm job conf paramater- CsmSignatureVerifyKeyLength */
#define PROG_KEY_LENGTH                                    [!WS "34"!][!"$Key_Length"!]U /* In bytes */
/* Signature Length shall be configured based on the value provided in the Csm job conf paramater- CsmSignatureVerifyCompareLength */
#define PROG_SIGNATURE_LENGTH                              [!WS "28"!][!"$Signature_Length"!]U

    [!IF "$AlgoMode = 'CRYPTO_ALGOMODE_RSASSA_PSS'"!]
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
    [!ELSE!]
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
    [!ENDIF!]
[!ELSE!]
    [!IF "((as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))/CsmSignatureVerifyPrimitiveName) = 'EdDSAVrfy'"!]
#define PROG_KEY_LENGTH                                    32U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              64U
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
	[!ELSEIF "((as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))/CsmSignatureVerifyPrimitiveName) = 'RsaSsaPssVerify'"!]
#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
	 [!ELSE!]
/* Default Config for all the unsupported algorithms configured */
#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
	[!ENDIF!]
[!ENDIF!]
[!ENDIF!]

#define PROG_CRC_CALCULATION                            PROG_NO_CRC

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
#define PROG_CURRENT_DIAG_APP                           2U

#define PROG_FRAMEWORK_PARTID_1                         0xA5F0BBBBU
#define PROG_FRAMEWORK_PARTID_2                         0xA0F5CCCCU

[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[[!"num:dectoint(count(Segments/*))"!]];
 [!ENDIF!]
[!ELSEIF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'"!]
/* One Level Bootloader Architecture selected */
#define PROG_IMPL_VARIANT                               PROG_IMPL_5
[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
[!VAR "CRCVERIFCATIONENABLED"="'false'"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]
 [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
 [!VAR "SEGMENT_IDX"="$SEGMENT_MAX"!]
[!ELSE!]
 [!VAR "CRCVERIFCATIONENABLED"="'true'"!]  
[!ENDIF!]
[!ENDFOR!]

[!IF "$SIGNATUREVERIFCATIONENABLED = 'true'"!]
#define PROG_HASH_CALCULATION                            STD_ON
#define PROG_SIGNATURE_CALCULATION                       STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                 STD_ON
[!IF "$CRCVERIFCATIONENABLED = 'true'"!]
#define PROG_CRC_CALCULATION                             PROG_TD_CRC16
[!ELSE!]
#define PROG_CRC_CALCULATION                             PROG_NO_CRC
[!ENDIF!]
[!ELSE!]
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                 STD_OFF
#define PROG_HASH_CALCULATION                            STD_OFF
#define PROG_SIGNATURE_CALCULATION                       STD_OFF
#define PROG_CRC_CALCULATION                             PROG_TD_CRC16
[!ENDIF!]

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
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
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
#define PROG_ERASE_ALL                                  STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
[!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
 [!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
 [!ENDIF!]
[!ELSEIF "(not(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true'))"!]
 #define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
[!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
[!ENDIF!]

#define PROG_VERIFICATION_METHOD                         0xFFU

/* !!!! To Be Generated once Csm stub will be available !!!!*/
[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "node:exists(as:modconf('CryIf'))"!]
	[!VAR "AlgoMode" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyAlgorithmMode)"!]
	[!VAR "Key_Length" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyKeyLength)"!]
	[!VAR "Signature_Length" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobPrimitiveRef)/CsmSignatureVerify/*/CsmSignatureVerifyCompareLength)"!]

/* Key Length shall be configured based on the value provided in the Csm job conf paramater- CsmSignatureVerifyKeyLength */
#define PROG_KEY_LENGTH                                    [!WS "34"!][!"$Key_Length"!]U /* In bytes */
/* Signature Length shall be configured based on the value provided in the Csm job conf paramater- CsmSignatureVerifyCompareLength */
#define PROG_SIGNATURE_LENGTH                              [!WS "28"!][!"$Signature_Length"!]U
    [!IF "$AlgoMode = 'CRYPTO_ALGOMODE_RSASSA_PSS'"!]
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
    [!ELSE!]
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
    [!ENDIF!]
[!ELSE!]
    [!IF "((as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))/CsmSignatureVerifyPrimitiveName) = 'EdDSAVrfy'"!]
#define PROG_KEY_LENGTH                                    32U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              64U
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
	[!ELSEIF "((as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))/CsmSignatureVerifyPrimitiveName) = 'RsaSsaPssVerify'"!]
#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
	 [!ELSE!]
/* Default Config for all the unsupported algorithms configured */
#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_CRY_EXPONENT_ENABLED                          STD_OFF
	[!ENDIF!]
[!ENDIF!]
[!ENDIF!]

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
#define PROG_CURRENT_DIAG_APP                           1U

#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

#define PROG_FRAMEWORK_PARTID_1                         0xA5F0BBBBU
#define PROG_FRAMEWORK_PARTID_2                         0xA0F5CCCCU
 [!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[[!"num:dectoint(count(Segments/*))"!]];
 [!ENDIF!]
[!IF "(as:modconf('Prog')/Security/Submit_signature_request='With Address')"!]
#define PROG_SUBMITSIGNATURE_WITH_ADDRESS               STD_ON
#define PROG_RC_OPTION_RECORD_HASH_TAB_ADD_BASE_INDEX   PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_OPTION_RECORD_SIGNATURE_BASE_INDEX      PROG_MSG_BYTE_INDEX(9U)
[!ELSE!]
#define PROG_SUBMITSIGNATURE_WITH_ADDRESS               STD_OFF
#define PROG_RC_OPTION_RECORD_SIGNATURE_BASE_INDEX      PROG_MSG_BYTE_INDEX(5U)
[!ENDIF!]
[!ELSE!]
[!ERROR "The JLR variant configured in ProgJLR is unknown"!]
[!ENDIF!][!/* as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL_WITH_EB_FRAMEWORK'' */!]

/* Security access limit request seed */
[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_ON
[!ELSE!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_OFF
[!ENDIF!]

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

/*Enable the response after reset in function of reset cause*/
#define PROG_RESET_CAUSE_ENABLE                         STD_OFF
/* Programming pre-conditions check */
#define PROG_PRECOND_CHECK_ENABLE                       STD_OFF

/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                     STD_OFF

/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                    STD_OFF

/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                         STD_OFF

#define PROG_USE_ECUID_CALLBACK                         STD_OFF

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                         STD_OFF

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

[!VAR "JLR_BLOCK_NBR"="num:dectoint(0)"!]
    [!VAR "SEGMENT_NBR_CAL"="num:inttohex(count(text:grep(as:modconf('Prog')/Segments/*/Partition_Type, 'PROG_CALIBRATION_PARTITION')))"!]
[!IF "$SEGMENT_NBR_CAL != num:inttohex(0)"!]
        [!VAR "JLR_BLOCK_NBR" = "num:dectoint($JLR_BLOCK_NBR + 1)"!]
[!ENDIF!]
    [!VAR "SEGMENT_NBR_APP"="num:inttohex(count(text:grep(as:modconf('Prog')/Segments/*/Partition_Type, 'PROG_APPLICATION_PARTITION')))"!]
[!IF "$SEGMENT_NBR_APP != num:inttohex(0)"!]
        [!VAR "JLR_BLOCK_NBR" = "num:dectoint($JLR_BLOCK_NBR + 1)"!]
[!ENDIF!]
    [!VAR "SEGMENT_NBR_APP1"="num:inttohex(count(text:grep(as:modconf('Prog')/Segments/*/Partition_Type, 'PROG_APP1_PARTITION')))"!]
[!IF "$SEGMENT_NBR_APP1 != num:inttohex(0)"!]
        [!VAR "JLR_BLOCK_NBR" = "num:dectoint($JLR_BLOCK_NBR + 1)"!]
[!ENDIF!]
    [!VAR "SEGMENT_NBR_CAL1"="num:inttohex(count(text:grep(as:modconf('Prog')/Segments/*/Partition_Type, 'PROG_CAL1_PARTITION')))"!]
[!IF "$SEGMENT_NBR_CAL1 != num:inttohex(0)"!]
        [!VAR "JLR_BLOCK_NBR" = "num:dectoint($JLR_BLOCK_NBR + 1)"!]
[!ENDIF!]
    [!VAR "SEGMENT_NBR_RAM"="num:inttohex(count(text:grep(as:modconf('Prog')/Segments/*/Partition_Type, 'PROG_RAM_PARTITION')))"!]
[!IF "$SEGMENT_NBR_RAM != num:inttohex(0)"!]
        [!VAR "JLR_BLOCK_NBR" = "num:dectoint($JLR_BLOCK_NBR + 1)"!]
[!ENDIF!]
#define PROG_APP_SEG_NB                                   [!WS "34"!][!"$SEGMENT_NBR_APP"!]U /* In bytes */
#define PROG_CAL_SEG_NB                                    [!WS "34"!][!"$SEGMENT_NBR_CAL"!]U /* In bytes */
#define PROG_APP1_SEG_NB                                    [!WS "34"!][!"$SEGMENT_NBR_APP1"!]U /* In bytes */
#define PROG_CAL1_SEG_NB                                    [!WS "34"!][!"$SEGMENT_NBR_CAL1"!]U /* In bytes */
#define PROG_RAM_SEG_NB                                    [!WS "34"!][!"$SEGMENT_NBR_RAM"!]U /* In bytes */
#define PROG_BLOCK_NB                                    5U /* Number of Partition type */

/*Introduced below the compiler switch to support Fingerprint for the Segments in RAM*/
#ifndef PROG_RAMSEG_FINGERPRINT_SUPPORT
#define PROG_RAMSEG_FINGERPRINT_SUPPORT                 STD_OFF
#endif

#ifndef PROG_SUBMITSIGNATURE_WITH_ADDRESS
#define PROG_SUBMITSIGNATURE_WITH_ADDRESS               STD_OFF
#endif

#endif /* PROG_CFG_IMPL0_H */
