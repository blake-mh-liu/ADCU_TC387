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
/*%%   _____________________________   %%  \file PROG_Cfg_Impl30.h               */
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
#ifndef PROG_CFG_IMPL30_H
#define PROG_CFG_IMPL30_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgFCA')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]


[!IF "node:exists(as:modconf('ProgFCA'))"!]

#define PROG_ENABLE_DOWNGRADE_PROTECTION                STD_OFF

[!IF "as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid'"!]
[!/********** Feature configuration for FCA Atlantis_Mid **********/!]

#define PROG_SIGNATURE_CALCULATION_OVER_HASH            STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                 STD_OFF
#define PROG_RESUM_REPROG                               STD_OFF

 [!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
 #define PROG_SECURE_CHECKSUM_SIZE_IN_BITS               [!"num:dectoint((as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH) * 8)"!]U
 #define PROG_SECURE_CHECKSUM_SIZE_IN_BYTES              [!"num:dectoint(as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH)"!]U

 /* Secure Boot Algorithm used */
 [!IF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmHash/') =  'true')) or
     ((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmHash)) )"!]
 #define PROG_CSM_SECURE_HASH_ID                         CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
 #define PROG_CSM_HASH_USED                              STD_ON
 #define PROG_CSM_MAC_USED                               STD_OFF
 [!ELSEIF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmMacGenerate/') =  'true')) or
     ((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
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

#define PROG_ECU_RESET_RESPONSE_SIZE                    2U
#define PROG_DSC_RESPONSE_SIZE                          2U
#define PROG_TD_RESPONSE_SIZE                           2U
#define PROG_RTE_RESPONSE_SIZE                          1U
#define PROG_COMPARE_KEY_RESPONSE_SIZE                  2U
#define PROG_ERASE_POS_RESPONSE_SIZE                    4U
#define PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE             4U
#define PROG_ERASE_REQUEST_DATA                         4U
#define PROG_TD_MIN_SIZE                                2U
#define PROG_TD_MIN_SIZE_RD                             3U
#define PROG_WF_RESPONSE_SIZE                           3U
#define PROG_NRC_SIZE                                   3U
#define PROG_RTE_SIZE                                   1U

#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

/* Programming status Mask bitfield value */
#define PROG_BOOT_BLOCK                                 0x00000001U /* Valid Bootloader block */
#define PROG_APPLI_BLOCK                                0x00000002U /* Valid Application block */
#define PROG_DATA_BLOCK                                 0x00000004U /* Valid Data block */
#define PROG_TD_SEQUENCE                                0x00000100U /* Data transfer error (Wrong total length) */
#define PROG_TD_BLOCK_SIZE                              0x00000200U /* Data transfer length to long */
#define PROG_RC_ERASE_SIZE                              0x00000800U /* Wrong erase size requested */
#define PROG_RC_ERASE_ADDRESS                           0x00001000U /* Wrong erase address requested */
#define PROG_RC_CHECKSUM_ADDRESS                        0x00002000U /* Wrong checksum address requested */
#define PROG_RC_CHECKSUM_SIZE                           0x00004000U /* Wrong checksum size requested */
#define PROG_RC_CHECKSUM_VERIFY                         0x00008000U /* Wrong checksum result */
#define PROG_SEQUENCE_WDBI                              0x00010000U /* WDBI not done before erasing request */
#define PROG_SEQUENCE_ERASE                             0x00020000U /* Wrong erasing sequence */
#define PROG_SEQUENCE_BLOCK_TRANSFFER                   0x00040000U /* Wrong BlockSequenceCounter received */
#define PROG_SEQUENCE_CHECKSUM                          0x00080000U /* Wrong CheckSum sequence */
#define PROG_SA_VERIFY                                  0x00100000U /* Incorrect key received */
#define PROG_RD_AREA                                    0x00200000U /* Wrong address range */
#define PROG_RD_TYPE                                    0x00400000U /* addressAndLengthFormatIdentifier not compatible */
#define PROG_RD_SIZE                                    0x00800000U /* Address size not coherent */
#define PROG_HW_COMPATIBLE                              0x01000000U /* BIN not compatible with HW */
#define PROG_APP_DATA_COMPATIBLE                        0x02000000U /* SW or Calib BIN not compatible*/

#define PROG_ERASE_ADDR_LEN                             4U
#define PROG_ERASE_SIZE_LEN                             4U

#define PROG_GET_PROG_CNTR_ENABLE                       1U
#define PROG_GET_PROG_CNTR_DISABLE                      0U
#define PROG_CNTR_GET_TYPE                              PROG_GET_PROG_CNTR_DISABLE

#define PROG_ERASE_TYPE                                 PROG_ERASE_BY_ADDR

#define PROG_VERIFICATION_METHOD                        PROG_VERIFICATION_CRC
#define PROG_CRC_CALCULATION                            PROG_TD_CRC_CUST
#define PROG_HASH_CALCULATION                           STD_OFF
#define PROG_RANGE_CKS                                  STD_ON
#define PROG_SEG_LIST_CKS                               STD_OFF
#define PROG_VERIFICATION_ON_THE_FLY                    STD_OFF
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA     STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_OFF
#define PROG_DOWNLOAD_TYPE                              PROG_DOWNLOAD_BY_ADDR
#define PROG_CVN_CHECK                                  STD_OFF

#define PROG_MAX_RD_ADDRESS_LENGTH                      4U
/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                1U

/* Routine type defines */
#define PROG_ROUTINE_TYPE_1                             0x10U
#define PROG_ROUTINE_TYPE_2                             0x20U
#define PROG_ROUTINE_TYPE_3                             0x30U

/* Routine status defines */
#define PROG_ROUTINE_FINISHED_OK                        0x00U
#define PROG_ROUTINE_FINISHED_NOK                       0x01U
#define PROG_ROUTINE_IN_PROGRESS                        0x02U

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

#define PROG_IMPL_VARIANT                               PROG_IMPL_30

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
#define PROG_CONTROL_DTC_SETTING_ENABLE                 STD_ON
#define PROG_COMMUNICATION_CONTROL_ENABLE               STD_ON
#define PROG_CHECK_MEMORY_ENABLE                        STD_OFF
#define PROG_GET_EXPECTED_CRC_ENABLED                   STD_OFF
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                 STD_OFF
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
#define PROG_SBL_HEADER_DEFINE                          STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE             STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE           STD_ON
#define PROG_CAL_CRC_ENABLE                             STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                 STD_OFF
#define PROG_PRE_INIT_ENABLE                            STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                   STD_ON

#define PROG_ERASE_ALL                                  STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
 #define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
[!ELSE!]
 #define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
[!ENDIF!]

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]


[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define PROG_ANTISCANNING_ENABLED                       STD_ON
[!ELSE!]
#define PROG_ANTISCANNING_ENABLED                       STD_OFF
[!ENDIF!]

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                         [!WS "5"!][!IF "NRC78_Transmission/Transmit_Nrc78_On_SecurityAccess = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define for the fingerprint writing */
#define PROG_WF_DID_1ST_BYTE                            0xF1U
#define PROG_WF_DID_2ND_BYTE_APP                        0x84U
#define PROG_WF_DID_2ND_BYTE_CALIB                      0x85U

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                    STD_ON

/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE              STD_ON

/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                         STD_OFF

[!IF "node:exists(as:modconf('Csm'))"!]
/* !!!! To Be Generated once Csm/ Csm stub will be available !!!!*/
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
#define PROG_CAL_PRESENT                                STD_ON
[!ELSE!]
#define PROG_CAL_PRESENT                                STD_OFF
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


/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                     STD_OFF


/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE             STD_OFF

/* Downloading Pseudo Flash driver feature activation */
#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_ENABLE      STD_OFF

#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_OFF

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                     STD_OFF

#define PROG_DECOMP_FLASH_ROUTINES                      STD_OFF

#define PROG_CRC_COMP_RESPONSE_SIZE                     5U
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
 [!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]
 [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
 [!VAR "SEGMENT_IDX"="$SEGMENT_MAX"!]
[!ENDIF!]
[!ENDFOR!]
[!ENDIF!]
[!IF "$SIGNATUREVERIFCATIONENABLED = 'true'"!]
#define PROG_SIGNATURE_CALCULATION                      STD_ON
#define PROG_SIGNATURE_LENGTH                           256U
#define PROG_KEY_LENGTH                                 256U
#define PROG_CRY_EXPONENT_ENABLED                       STD_ON
#define PROG_DIGEST_LENGTH                              32U
[!ELSE!]
#define PROG_SIGNATURE_CALCULATION                      STD_OFF
[!ENDIF!]
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[[!"num:dectoint(count(Segments/*))"!]];
[!ENDIF!]

#define PROG_CPD_ENDADDR_OFFSET 						0x08u
#define PROG_CPD_STARTADDR_OFFSET 						0x04u

#define PROG_REPROG_TYPE                                PROG_NO_REPROG_TYPE

[!ELSEIF "as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'"!]
[!/********** Feature configuration for FCA Atlantis_High **********/!]

#define PROG_SIGNATURE_CALCULATION_OVER_HASH            STD_OFF
#define PROG_RESUM_REPROG                               STD_OFF

#define PROG_ECU_RESET_RESPONSE_SIZE                    2U
#define PROG_DSC_RESPONSE_SIZE                          2U
#define PROG_TD_RESPONSE_SIZE                           2U
#define PROG_RTE_RESPONSE_SIZE                          1U
#define PROG_COMPARE_KEY_RESPONSE_SIZE                  2U
#define PROG_ERASE_POS_RESPONSE_SIZE                    4U
#define PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE             4U
#define PROG_ERASE_REQUEST_DATA                         0U
#define PROG_TD_MIN_SIZE                                2U
#define PROG_TD_MIN_SIZE_RD                             3U
#define PROG_WF_RESPONSE_SIZE                           3U
#define PROG_NRC_SIZE                                   3U
#define PROG_RTE_SIZE                                   1U
#define PROG_CRC_COMP_RESPONSE_SIZE                     5U
#define PROG_COH_CHK_RESP_SIZE                          5U
#define PROG_CHK_PROG_PRECOND_SIZE                      5U

#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

/* Programming status Mask bitfield value */
#define PROG_BOOT_BLOCK                                 0x00000001U /* Valid Bootloader block */
#define PROG_APPLI_BLOCK                                0x00000002U /* Valid Application block */
#define PROG_DATA_BLOCK                                 0x00000004U /* Valid Data block */
#define PROG_TD_SEQUENCE                                0x00000100U /* Data transfer error (Wrong total length) */
#define PROG_TD_BLOCK_SIZE                              0x00000200U /* Data transfer length to long */
#define PROG_RC_ERASE_SIZE                              0x00000800U /* Wrong erase size requested */
#define PROG_RC_ERASE_ADDRESS                           0x00001000U /* Wrong erase address requested */
#define PROG_RC_CHECKSUM_ADDRESS                        0x00002000U /* Wrong checksum address requested */
#define PROG_RC_CHECKSUM_SIZE                           0x00004000U /* Wrong checksum size requested */
#define PROG_RC_CHECKSUM_VERIFY                         0x00008000U /* Wrong checksum result */
#define PROG_SEQUENCE_WDBI                              0x00010000U /* WDBI not done before erasing request */
#define PROG_SEQUENCE_ERASE                             0x00020000U /* Wrong erasing sequence */
#define PROG_SEQUENCE_BLOCK_TRANSFFER                   0x00040000U /* Wrong BlockSequenceCounter received */
#define PROG_SEQUENCE_CHECKSUM                          0x00080000U /* Wrong CheckSum sequence */
#define PROG_SA_VERIFY                                  0x00100000U /* Incorrect key received */
#define PROG_RD_AREA                                    0x00200000U /* Wrong address range */
#define PROG_RD_TYPE                                    0x00400000U /* addressAndLengthFormatIdentifier not compatible */
#define PROG_RD_SIZE                                    0x00800000U /* Address size not coherent */
#define PROG_HW_COMPATIBLE                              0x01000000U /* BIN not compatible with HW */
#define PROG_APP_DATA_COMPATIBLE                        0x02000000U /* SW or Calib BIN not compatible*/

#define PROG_ERASE_ADDR_LEN                             4U
#define PROG_ERASE_SIZE_LEN                             4U

#define PROG_GET_PROG_CNTR_ENABLE                       1U
#define PROG_GET_PROG_CNTR_DISABLE                      0U
#define PROG_CNTR_GET_TYPE                              PROG_GET_PROG_CNTR_DISABLE

#define PROG_ERASE_TYPE                                 PROG_ERASE_BY_BLOCK_ID

[!IF "(as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Standard')"!]
#define PROG_REPROG_TYPE                                PROG_STANDARD_REPROG
#define PROG_VERIFICATION_METHOD                        PROG_VERIFICATION_CRC
#define PROG_CRC_CALCULATION                            PROG_TD_CRC16
#define PROG_SIGNATURE_CALCULATION                      STD_OFF
#define PROG_HASH_CALCULATION                           STD_OFF
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_OFF
 /* Size of the CRC which bytes wich is included in data */
#define PROG_CRC_BYTE_LENGTH                            2U

#define PROG_SEG_LIST_CKS                               STD_ON
#define PROG_RC_LOGICAL_BLOCK_NUMBER_INDEX              4U
#define PROG_LOGICAL_BLOCK_HASH_RESP_SIZE               36U

/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                         STD_ON

#define PROG_COMPUTE_HASH_WITH_PHYS_ADDR                [!WS "16"!][!IF "DownloadVerification/SignatureVerificationWithPhyAddr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                 [!WS "17"!][!IF "DownloadVerification/SignatureVerificationWithAddrLen = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!ELSEIF "(as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Authenticated')"!]
#define PROG_REPROG_TYPE                                PROG_AUTHENTICATED_REPROG
#define PROG_VERIFICATION_METHOD                        PROG_VERIFICATION_HASH
#define PROG_CRC_CALCULATION                            PROG_NO_CRC
#define PROG_SIGNATURE_CALCULATION                      STD_ON
#define PROG_HASH_CALCULATION                           STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                STD_ON

#define PROG_SEG_LIST_CKS                               STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                 STD_OFF
 
/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                         STD_OFF
[!ENDIF!]
#define PROG_RANGE_CKS                                  STD_OFF
#define PROG_VERIFICATION_ON_THE_FLY                    STD_ON
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA     STD_ON
#define PROG_DOWNLOAD_TYPE                              PROG_DOWNLOAD_BY_ADDR
#define PROG_CVN_CHECK                                  STD_OFF

#define PROG_MAX_RD_ADDRESS_LENGTH                      4U
/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                1U

/* Security access limit request seed */
[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_ON
[!ELSE!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_OFF
[!ENDIF!]

/* Routine type defines */
#define PROG_ROUTINE_TYPE_1                             0x10U
#define PROG_ROUTINE_TYPE_2                             0x20U
#define PROG_ROUTINE_TYPE_3                             0x30U

/* Routine status defines */
#define PROG_ROUTINE_FINISHED_OK                        0x00U
#define PROG_ROUTINE_FINISHED_NOK                       0x01U
#define PROG_ROUTINE_IN_PROGRESS                        0x02U

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

#define PROG_IMPL_VARIANT                               PROG_IMPL_31

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
#define PROG_CONTROL_DTC_SETTING_ENABLE                 STD_ON
#define PROG_COMMUNICATION_CONTROL_ENABLE               STD_ON
#define PROG_CHECK_MEMORY_ENABLE                        STD_ON
#define PROG_GET_EXPECTED_CRC_ENABLED                   STD_OFF
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                 STD_ON
#define PROG_SET_CRC_COMPARE_RESULT_ENABLE              STD_ON
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
#define PROG_EXTENDED_SESSION_MANAGED                   STD_ON

#define PROG_ERASE_ALL                                  STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                  [!WS "18"!][!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BOOT_VERIFICATION                          [!WS "26"!][!IF "(as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated')"!]
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_ON
#define PROG_AUTHENTICATED_BOOT_START_ADDR              ([!"num:inttohex(as:modconf('BM')/Security/SecureBoot/BootCksStartAddress)"!]U)
#define PROG_AUTHENTICATED_BOOT_START_LENGTH            ([!"num:inttohex(as:modconf('BM')/Security/SecureBoot/BootCksRangeLength)"!]U)
[!ELSE!]
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
[!ENDIF!]

[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_ON
[!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF
[!ENDIF!]

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]


[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define PROG_ANTISCANNING_ENABLED                       STD_ON
[!ELSE!]
#define PROG_ANTISCANNING_ENABLED                       STD_OFF
[!ENDIF!]

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                         [!WS "5"!][!IF "NRC78_Transmission/Transmit_Nrc78_On_SecurityAccess = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define for the fingerprint writing */
#define PROG_WF_DID_1ST_BYTE                            0xF1U
#define PROG_WF_DID_2ND_BYTE_APP                        0x84U
#define PROG_WF_DID_2ND_BYTE_CALIB                      0x85U

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                    STD_OFF

/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE              STD_OFF

[!IF "node:exists(as:modconf('Csm'))"!]
/* !!!! To Be Generated once Csm/ Csm stub will be available !!!!*/
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
#define PROG_CAL_PRESENT                                STD_ON
[!ELSE!]
#define PROG_CAL_PRESENT                                STD_OFF
[!ENDIF!]
#define PROG_DIGEST_LENGTH                              32U

/*Enable the response after reset in function of reset cause*/
#define PROG_RESET_CAUSE_ENABLE                         STD_OFF
/* Programming pre-conditions check */
#define PROG_PRECOND_CHECK_ENABLE                       STD_ON
/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                     STD_ON
#define PROG_USE_ECUID_CALLBACK                         STD_OFF

/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                    STD_ON


/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                     STD_OFF


/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE             STD_OFF

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                     STD_ON
#define PROG_BLOCKID_INDEX_IN_FINGREPRINT               3U

#define PROG_DECOMP_FLASH_ROUTINES                      STD_OFF


[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
#define PROG_BLOCK_NB                                   [!"$BLOCK_MAX"!]U

[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
#define PROG_SECURE_CHECKSUM_SIZE_IN_BITS               [!"num:dectoint((as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH) * 8)"!]U
#define PROG_SECURE_CHECKSUM_SIZE_IN_BYTES              [!"num:dectoint(as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH)"!]U

/* Secure Boot Algorithm used */
  [!IF "(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
    [!IF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmHash/') =  'true')) or
    ((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmHash)) )"!]
#define PROG_CSM_SECURE_HASH_ID                          CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
#define PROG_CSM_HASH_USED                              STD_ON
#define PROG_CSM_MAC_USED                               STD_OFF
    [!ELSEIF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmMacGenerate/') =  'true')) or
    ((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
#define PROG_CSM_SECURE_MAC_ID                           CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
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

extern const tProg_Block stCfgBlock[PROG_BLOCK_NB];
[!IF "not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))"!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[PROG_BLOCK_NB];
[!ENDIF!]

/* Header */
#define PROG_IMPL31_HEADER_SIZE                         448U
#define PROG_HEADER_SIGNATURE_OFFSET                    8U
#define PROG_IMPL31_HEADER_SIGNATURE_SIZE               256U
#define PROG_SIGNING_INFO_OFFSET                        40U
#define PROG_IMPL31_SIGNING_INFO_SIZE                   96U
#define PROG_BLOCK_HEADER_SIZE                          176U
#define PROG_FILE_DIGEST_OFFSET                         8U
#define PROG_BLOCK_HEADER_SIGNINGINFO_SIZE              96U

#define PROG_BLOCK_HEADER_TARGETNAME_OFFSET             136U
#define PROG_BLOCK_HEADER_TARGETNAME_SIZE               16U
#define PROG_BLOCK_HEADER_ROLLBACKID_OFFSET             152U
#define PROG_BLOCK_HEADER_ROLLBACKID_SIZE               4U
#define PROG_BLOCK_HEADER_COMPATIBILITYID_OFFSET        156U
#define PROG_BLOCK_HEADER_COMPATIBILITYID_SIZE          4U
#define PROG_BLOCK_HEADER_UUID_OFFSET                   160U
#define PROG_BLOCK_HEADER_UUID_SIZE                     16U
#define PROG_SIGNATURE_LENGTH                           256U
#define PROG_KEY_LENGTH                                 256U
#define PROG_CRY_EXPONENT_ENABLED                       STD_ON



#define PROG_RESPONSE_PARAMETERS_OFFSET                 (u8) (1U)/* This define is used because the tables in C starts from 0 and not 1
                                                                    and the indexes in the specifications starts sometimes from 1 */

/* Routines */
#define PROG_RC_ROUTINE_STATUS_BASE_INDEX               PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_ROUTINE_STATUS_SIZE                     (u8) 1U

/* Routine 0xF000 */
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_BASE_INDEX  PROG_RC_ROUTINE_STATUS_BASE_INDEX
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIZE        (u8) 1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_OK          (u8) 0U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_GEN_FAILURE (u8) 1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_CRC_FAILED  (u8) 2U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIG_FAILED  (u8) 4U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_DELTA_FAILED (u8) 8U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_RW_FAILED   (u8) 64U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_NOK         (u8) 3U


[!ELSE!]
[!ERROR "The FCA variant configured in ProgFCA is unknown"!]
[!ENDIF!] [!/* as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High' */!]

[!ENDIF!]

/*Securiy access request seed delay timer*/
[!IF "as:modconf('SA')/General/Security_Access_Rs_Delay_Timer != '0'"!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_ON
[!ELSE!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_OFF
[!ENDIF!]

/*Introduced below the compiler switch to support Fingerprint for the Segments in RAM*/
#ifndef PROG_RAMSEG_FINGERPRINT_SUPPORT
#define PROG_RAMSEG_FINGERPRINT_SUPPORT                 STD_OFF
#endif
#endif /* PROG_CFG_IMPL_30_H */
