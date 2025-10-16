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
/*%%   _____________________________   %%  \file PROG_Cfg_Impl60.h              */
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
#ifndef PROG_CFG_IMPL60_H
#define PROG_CFG_IMPL60_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgOEMInd')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
[!/********************* Feature configuration for OEM Independent bootloader ************************/!]
[!IF "(as:modconf('Prog')/DownloadFlashRoutines/Decompress_Flash_Routines = 'true')"!]
/* __FLASH_DRIVER_ROM_START_ADDRESS shall be set to the start address of ROM section/group for Flash driver in the linker file */
/* __FLASH_DRIVER_ROM_END_ADDRESS shall be set to the end address of ROM section/group for Flash driver in the linker file */
/* __FLASH_DRIVER_RAM_START_ADDRESS shall be set to the start address of RAM section/group for Flash driver in the linker file */
/* __FLASH_DRIVER_RAM_END_ADDRESS shall be set to the end address of RAM section/group for Flash driver in the linker file */
extern u8 __FLASH_DRIVER_ROM_START_ADDRESS;
extern u8 __FLASH_DRIVER_ROM_END_ADDRESS;
extern u8 __FLASH_DRIVER_RAM_START_ADDRESS;
extern u8 __FLASH_DRIVER_RAM_END_ADDRESS;
[!ENDIF!]



#define PROG_ECU_RESET_RESPONSE_SIZE                       2U
#define PROG_DSC_RESPONSE_SIZE                             2U
#define PROG_TD_RESPONSE_SIZE                              2U
#define PROG_RTE_RESPONSE_SIZE                             1U
#define PROG_COMPARE_KEY_RESPONSE_SIZE                     2U
#define PROG_ERASE_POS_RESPONSE_SIZE                       4U
#define PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE                4U
#define PROG_ERASE_REQUEST_DATA                            4U
#define PROG_TD_MIN_SIZE                                   2U
#define PROG_TD_MIN_SIZE_RD                                3U
#define PROG_WF_RESPONSE_SIZE                              3U
#define PROG_NRC_SIZE                                      3U
#define PROG_AUTOCONTROL_POS_RESPONSE_SIZE                 4U
#define PROG_CHK_PROG_PRECOND_SIZE                         4U
#define PROG_CRC_COMP_RESPONSE_SIZE                        4U
#define PROG_COH_CHK_RESP_SIZE                             5U
#define PROG_RTE_SIZE                                      1U

#define PROG_BOOT_REPROG                                   1U
#define PROG_BOOT_NOREPROG                                 0U

#define PROG_ERASE_ADDR_LEN                                4U
#define PROG_ERASE_SIZE_LEN                                4U

#define PROG_GET_PROG_CNTR_ENABLE                          1U
#define PROG_GET_PROG_CNTR_DISABLE                         0U
#define PROG_CNTR_GET_TYPE                                 PROG_GET_PROG_CNTR_DISABLE

#define PROG_REPROG_TYPE                                   PROG_NO_REPROG_TYPE

[!IF "OemInd/Erase_Mode = 'All'"!]
#define PROG_ERASE_ALL                                     STD_ON
#define PROG_ERASE_TYPE                                    PROG_ERASE_BY_BLOCK_ID
#define PROG_BLOCK_NB                                      1U
extern const tProg_Block     stCfgBlock[PROG_BLOCK_NB];
[!ENDIF!]


[!ENDIF!]

[!IF "OemInd/Erase_Mode = 'Address'"!]
#define PROG_ERASE_ALL                                     STD_OFF
#define PROG_ERASE_TYPE                                    PROG_ERASE_BY_ADDR
#undef PROG_ERASE_ALFI
#define PROG_ERASE_ALFI                                    [!WS "24"!][!IF "OemInd/EraseALFI_Enable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
[!ENDIF!]

[!IF "OemInd/Erase_Mode = 'LogicalBlock'"!]
#define PROG_ERASE_ALL                                     STD_OFF
#define PROG_ERASE_TYPE                                    PROG_ERASE_BY_BLOCK_ID
[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
#define PROG_BLOCK_NB                                      [!"$BLOCK_MAX"!]U
extern const tProg_Block     stCfgBlock[PROG_BLOCK_NB];
[!ENDIF!]

[!IF "OemInd/Checksum_Algo = 'Signature'"!]
#define PROG_SIGNATURE_CALCULATION                         STD_ON
#define PROG_VERIFICATION_ON_THE_FLY                       STD_ON
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_ON
#define PROG_HASH_CALCULATION                              STD_OFF
#define PROG_CRC_CALCULATION                               PROG_NO_CRC
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_SIGNATURE
[!ELSEIF "OemInd/Checksum_Algo = 'Hash256' or OemInd/Checksum_Algo = 'Hash512'"!]
#define PROG_SIGNATURE_CALCULATION                         STD_OFF
#define PROG_VERIFICATION_ON_THE_FLY                       STD_ON
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_OFF
#define PROG_HASH_CALCULATION                              STD_ON
#define PROG_CRC_CALCULATION                               PROG_NO_CRC
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_HASH
[!IF "OemInd/Checksum_Algo = 'Hash256'"!]
#define PROG_DIGEST_LENGTH                                 32U
[!ELSEIF "OemInd/Checksum_Algo = 'Hash512'"!]
#define PROG_DIGEST_LENGTH                                 64U
[!ENDIF!]
[!ELSE!]
#define PROG_VERIFICATION_ON_THE_FLY                       STD_OFF
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_ON
#define PROG_SIGNATURE_CALCULATION                         STD_OFF
#define PROG_HASH_CALCULATION                              STD_OFF
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_CRC
[!ENDIF!]

[!IF "OemInd/Checksum_Algo = 'CRC16' or OemInd/Checksum_Algo = 'NO CRC'"!]
#define PROG_CRC_ALGO                                      PROG_CRC16
#define PROG_CRC_CALCULATION                               PROG_TD_CRC16
[!ENDIF!]
[!IF "OemInd/Checksum_Algo = 'CRC32 Ethernet'"!]
#define PROG_CRC_ALGO                                      PROG_CRC32_ETHERNET
#define PROG_CRC_CALCULATION                               PROG_TD_CRC32
[!ENDIF!]
[!IF "OemInd/Checksum_Algo = 'CRC32 InternationalStandard'"!]
#define PROG_CRC_ALGO                                      PROG_CRC32_INT_STD
#define PROG_CRC_CALCULATION                               PROG_TD_CRC32
[!ENDIF!]

#define PROG_RANGE_CKS                                     STD_OFF
#define PROG_SEG_LIST_CKS                                  STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                   STD_OFF
#define PROG_MAX_RD_ADDRESS_LENGTH                         4U
/*Download type*/
[!IF "OemInd/Request_Download_Address_Mode = 'Download by Segment Address'"!]
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_ADDR
[!ELSEIF "OemInd/Request_Download_Address_Mode = 'Download by logical block'"!]
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_LOGICAL_BLOCK
[!ELSEIF "OemInd/Request_Download_Address_Mode = 'Download by logical block and segment'"!]
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT
[!ENDIF!]

/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                   1U

#define PROG_CVN_CHECK                                     STD_OFF

/* Routine type defines */
#define PROG_ROUTINE_TYPE_1                                0x10U
#define PROG_ROUTINE_TYPE_2                                0x20U
#define PROG_ROUTINE_TYPE_3                                0x30U

/* Routine status defines */
#define PROG_ROUTINE_FINISHED_OK                           0x00U
#define PROG_ROUTINE_FINISHED_NOK                          0x01U
#define PROG_ROUTINE_IN_PROGRESS                           0x02U

/* specific routine result value */
#define PROG_ROUTINE_ACTIVE                                0x01U
#define PROG_ROUTINE_RESAVAILABLE                          0x02U
#define PROG_ROUTINE_PREDIF                                0x08U
#define PROG_ROUTINE_STOP_SUBFUNC                          0x10U
#define PROG_ROUTINE_RES_SUBFUNC                           0x20U
#define PROG_ROUTINE_SELFTERM                              0x40U
#define PROG_ROUTINE_AUTONOMOUS                            0x80U

#define PROG_APPL_VALID                                    0x00000002U
#define PROG_APPL_INVALID                                  0x00000001U

#define PROG_MAGIC_NUM_SIZE                                8U

[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "num:dectoint("0")"!]
[!LOOP "Segments/*"!]
    [!VAR "Memory_Type" = "node:ref(Memory)/Memory_Type"!]
    [!IF "$Memory_Type = 'FLASH'"!]
        [!IF "(node:exists(as:modconf('Flash')))"!]
           [!VAR "MEMORY_MODE_FLASH" = "node:ref(Memory)/Memory_Mode"!]
        [!ENDIF!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_FLASH > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_FLASH"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'FLASH_EXT'"!]
        [!IF "(node:exists(as:modconf('Flash')))"!]
           [!VAR "MEMORY_MODE_FLASH_EXT" = "node:ref(Memory)/Memory_Mode"!]
        [!ENDIF!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_FLASH_EXT > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_FLASH_EXT"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'CUSTOM'"!]
        [!IF "(node:exists(as:modconf('Flash')))"!]
           [!VAR "MEMORY_MODE_CUSTOM" = "node:ref(Memory)/Memory_Mode"!]
        [!ENDIF!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_CUSTOM > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_CUSTOM"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
[!IF "node:exists(as:modconf('ProgOEMInd')) and as:modconf('Uds')/Service_DID/*/Callback = 'PROG_WriteFingerprint'"!]
[!VAR "PROG_FINGERPRINT_SIZE" = "num:dectoint(as:modconf('Prog')/OemInd/Size_Of_FingerPrint)"!]
/* Size in Bytes of the FingerPrint */
#define PROG_FINGERPRINT_SIZE                              [!"num:i($PROG_FINGERPRINT_SIZE)"!]U
    [!IF "OemInd/Application_Validity_Algo = 'EB'"!]
/* Size in Bytes reserved to the FingerPrint which is a multiple of size of page */
#define PROG_FINGERPRINT_FLASH_PAGE_SIZE                   [!"num:i((ceiling($PROG_FINGERPRINT_SIZE div $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES))*$MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES)"!]U
#define PROG_FINGERPRINT_FLASH_EXT_PAGE_SIZE               [!"num:i((ceiling($PROG_FINGERPRINT_SIZE div $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES))*$MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES)"!]U
#define PROG_FINGERPRINT_CUSTOM_MEM_PAGE_SIZE              [!"num:i((ceiling($PROG_FINGERPRINT_SIZE div $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES))*$MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES)"!]U
    [!ENDIF!]
[!ENDIF!]

#define PROG_P2_PROG_SESSION_VAL                           [!WS "27"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2"!]U
#define PROG_P2STAR_PROG_SESSION_VAL                       [!WS "23"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2STAR"!]U
#define PROG_P2_DEFAULT_SESSION_VAL                        [!WS "24"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2"!]U
#define PROG_P2STAR_DEFAULT_SESSION_VAL                    [!WS "20"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2STAR"!]U

#define PROG_IMPL_VARIANT                                  PROG_IMPL_60

#define PROG_WATCHDOG_ENABLE                               STD_OFF
#define PROG_REQUEST_DOWNLOAD_ENABLE                       STD_ON
#define PROG_SECURITY_ENABLE                               STD_ON
#define PROG_SA_SEED_ENABLE                                STD_ON
#define PROG_SA_KEY_ENABLE                                 STD_ON
#define PROG_ERASE_MEMORY_ENABLE                           STD_ON
#define PROG_TRANSFER_DATA_ENABLE                          STD_ON
#define PROG_REQUEST_TRANSFER_EXIT_ENABLE                  STD_ON
#define PROG_ECU_RESET_ENABLE                              STD_ON
#define PROG_ACTIVE_SBL_ENABLE                             STD_OFF
#define PROG_UPDATE_PSI_ENABLE                             STD_OFF
#define PROG_CONTROL_DTC_SETTING_ENABLE                    STD_ON
#define PROG_COMMUNICATION_CONTROL_ENABLE                  STD_ON
#define PROG_CHECK_MEMORY_ENABLE                           STD_ON
#define PROG_GET_EXPECTED_CRC_ENABLED                      STD_OFF
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                    STD_OFF
#define PROG_SET_CRC_COMPARE_RESULT_ENABLE                 STD_ON
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE       STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE        STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE         STD_OFF
#define PROG_NETWORK_MANAGEMENT_ENABLE                     STD_OFF
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE               STD_OFF
#define PROG_APPLI_CHECK_ENABLE                            STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                       [!WS "23"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_PEC_ENABLE                                    STD_OFF
#define PROG_MULTIPLE_BUFFERS_ENABLE                       [!WS "37"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_AUTHENTICATED_BOOT_ENABLE                     STD_OFF
#define PROG_BOOT_VERIFICATION                             STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION              STD_OFF
[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION             STD_ON
[!ELSE!]
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION             STD_OFF
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF') or (as:modconf('Prog')/Security/Secure_Checksum_computation = 'true'))"!]
    [!IF "as:modconf('Prog')/OemInd/Erase_Mode = 'LogicalBlock'"!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[PROG_BLOCK_NB];
    [!ELSE!]
extern const tProg_BlockSecureBootInfo stCfgBlockSecureBootInfo[PROG_SEGMENT_NB];
    [!ENDIF!]
[!ENDIF!]

#define PROG_SBL_HEADER_DEFINE                             STD_OFF
#define PROG_ENABLE_DOWNGRADE_PROTECTION                   STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE                STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE              STD_ON
#define PROG_CAL_CRC_ENABLE                                STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                    STD_OFF
#define PROG_PRE_INIT_ENABLE                               STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                      STD_ON

#define PROG_SLEEP_MANAGEMENT_TYPE [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT   [!WS "30"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]
[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define PROG_ANTISCANNING_ENABLED                          STD_ON
[!ELSE!]
#define PROG_ANTISCANNING_ENABLED                          STD_OFF
[!ENDIF!]

/* Security access limit request seed */
[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_ON
[!ELSE!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_OFF
[!ENDIF!]

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                            [!WS "32"!][!IF "NRC78_Transmission/Transmit_Nrc78_On_SecurityAccess = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                       STD_OFF

/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE                 STD_OFF

#define PROG_USE_ECUID_CALLBACK                            STD_OFF

/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                        [!WS "24"!][!IF "OemInd/CoherencyCheck_Enable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "OemInd/Request_Download_Address_Mode = 'Download by logical block' or OemInd/Request_Download_Address_Mode = 'Download by logical block and segment'"!]
/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                       STD_ON
[!ELSE!]
/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                       STD_OFF
[!ENDIF!]

/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                            STD_OFF


/*Enable the response after reset in function of reset cause*/
#define PROG_RESET_CAUSE_ENABLE                            [!WS "28"!][!IF "General/Transmit_Response_Before_Reset = 'false'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Disable bypass of SA */
#define PROG_BYPASS_SA_COMPARE_KEY                         [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Programming pre-conditions check */
#define PROG_PRECOND_CHECK_ENABLE                          [!WS "26"!][!IF "General/Check_Programming_PreConditions = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                        STD_OFF

extern const u8 m_aCfgMagicNumProgrammedValue[PROG_MAGIC_NUM_SIZE];
extern const u8 m_aCfgMagicNumRevokedValue[PROG_MAGIC_NUM_SIZE];
[!IF "node:exists(as:modconf('Csm'))"!]
#define PROG_CRY_PRESENT                                   STD_ON

#define PROG_SIGNATURE_LENGTH                              256U
#define PROG_KEY_LENGTH                                    256U /* In bytes */

#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
[!ELSE!]
#define PROG_CRY_PRESENT                                   STD_OFF
[!ENDIF!]
[!IF "node:exists(as:modconf('Cal'))"!]
#define PROG_CAL_PRESENT                                   STD_ON
[!ELSE!]
#define PROG_CAL_PRESENT                                   STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('CryShe'))"!]
#define PROG_CRYSHE_PRESENT                                STD_ON
[!ELSE!]
#define PROG_CRYSHE_PRESENT                                STD_OFF
[!ENDIF!]

/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE                [!WS "16"!][!IF "DownloadFlashRoutines/Download_Flash_Routines = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define PROG_DOWNLOAD_FLASH_ROUTINES_REJECT_AFTER_FAILURE  [!WS "2"!][!IF "DownloadFlashRoutines/Reject_RD_After_Corrupt_Flash_Routines = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* Downloading Pseudo Flash driver feature activation */
#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_ENABLE         [!WS "16"!][!IF "DownloadFlashRoutines/Download_Pseudo_Flash_Routines = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_ON

/****************************************************/
/*                  UDS                             */
/****************************************************/
#define PROG_RESPONSE_PARAMETERS_OFFSET                    (u8) (1U)/* This define is used because the tables in C starts from 0 and not 1
                                                                    and the indexes in the specifications starts sometimes from 1 */
/* Services */

/* Routines */
#define PROG_RC_ROUTINE_STATUS_BASE_INDEX                  PROG_MSG_BYTE_INDEX(5U)

/* Routine 0x0202 */

[!IF "node:exists(General/Prog_RC_CrcOffset)"!]
/* CRC Offset*/
#define PROG_RC_CRC_OFFSET         [!"num:i(General/Prog_RC_CrcOffset)"!]U
[!ENDIF!]
[!IF "OemInd/Checksum_Algo = 'Signature'"!]
#define PROG_RC_OPTION_RECORD_SIGVAL_BASE_INDEX            PROG_MSG_BYTE_INDEX(5U) + PROG_RC_CRC_OFFSET
#define PROG_RC_OPTION_RECORD_SIGVAL_SIZE                  (u8) 64U
#define PROG_RC_OPTION_RECORD_CRC_NBBYTES_BASE_INDEX       (u8)(PROG_RC_OPTION_RECORD_SIGVAL_BASE_INDEX + PROG_RC_OPTION_RECORD_SIGVAL_SIZE)
#define PROG_RC_OPTION_RECORD_CRC_NBBYTES_SIZE             (u8) 2U
#define PROG_RC_OPTION_RECORD_CRC_VAL_BASE_INDEX           (u8)(PROG_RC_OPTION_RECORD_CRC_NBBYTES_BASE_INDEX + PROG_RC_OPTION_RECORD_CRC_NBBYTES_SIZE)

#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_BASE_INDEX     PROG_RC_ROUTINE_STATUS_BASE_INDEX
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIZE           (u8) 1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_OK             (u8) 0U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_GEN_FAILURE    (u8) 1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_CRC_FAILED     (u8) 2U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIG_FAILED     (u8) 4U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_DELTA_FAILED   (u8) 8U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_RW_FAILED      (u8) 64U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_NOK            (u8) 3U
[!ELSE!]
#define PROG_RC_OPTION_RECORD_CRC_VAL_BASE_INDEX           PROG_MSG_BYTE_INDEX(5U) + PROG_RC_CRC_OFFSET
[!ENDIF!]

/* Routine 0xFF00 */
#define PROG_RC_STATUS_RECORD_ERASEVERIF_BASE_INDEX        PROG_RC_ROUTINE_STATUS_BASE_INDEX
#define PROG_RC_STATUS_RECORD_ERASEVERIF_OK                (u8) 0U
#define PROG_RC_STATUS_RECORD_ERASEVERIF_NOT_OK            (u8) 1U

/* Routine 0xFF01 */

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                        STD_OFF

[!IF "(as:modconf('Prog')/DownloadFlashRoutines/Decompress_Flash_Routines = 'true')"!]
#define PROG_DECOMP_FLASH_ROUTINES                         STD_ON
#define PROG_DOWNLOAD_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_OFF
#define PROG_FLASH_ROUTINES_RAM_ADDR_START                 &__FLASH_DRIVER_RAM_START_ADDRESS
#define PROG_FLASH_ROUTINES_RAM_ADDR_END                   &__FLASH_DRIVER_RAM_END_ADDRESS
#define PROG_FLASH_ROUTINES_ROM_ADDR_START                 &__FLASH_DRIVER_ROM_START_ADDRESS
#define PROG_FLASH_ROUTINES_ROM_ADDR_END                   &__FLASH_DRIVER_ROM_END_ADDRESS
[!ELSE!]
#define PROG_DECOMP_FLASH_ROUTINES                         STD_OFF
[!ENDIF!]

/*Introduced below the compiler switch to support Fingerprint for the Segments in RAM*/
#ifndef PROG_RAMSEG_FINGERPRINT_SUPPORT
#define PROG_RAMSEG_FINGERPRINT_SUPPORT                    STD_ON
#endif

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure') and (as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
#define PROG_SECURE_CHECKSUM_SIZE_IN_BITS               [!"num:dectoint((as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH) * 8)"!]U
#define PROG_SECURE_CHECKSUM_SIZE_IN_BYTES              [!"num:dectoint(as:modconf('BM')/Security/SecureBoot/CHECKSUM_LENGTH)"!]U
[!IF "(node:exists(as:modconf('CryIf')) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmHash)))"!]
/* Secure Boot Algorithm used */
#define PROG_CSM_SECURE_HASH_ID                            [!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
#define PROG_CSM_HASH_USED                                 STD_ON
#define PROG_CSM_MAC_USED                                  STD_OFF
[!ELSEIF "(node:exists(as:modconf('CryIf')) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
/* Secure Boot Algorithm used */
#define PROG_CSM_SECURE_MAC_ID                             CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!])
#define PROG_CSM_HASH_USED                                 STD_OFF
#define PROG_CSM_MAC_USED                                  STD_ON
[!ELSE!]
#define PROG_CSM_HASH_USED                                 STD_OFF
#define PROG_CSM_MAC_USED                                  STD_OFF
[!ENDIF!]
[!ELSE!]
#define PROG_CSM_HASH_USED                                 STD_OFF
#define PROG_CSM_MAC_USED                                  STD_OFF
[!ENDIF!]

#define PROG_SIGNATURE_CALCULATION_OVER_HASH               STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                    STD_OFF
#define PROG_RESUM_REPROG                                  STD_OFF

/*Securiy access request seed delay timer*/
[!IF "as:modconf('SA')/General/Security_Access_Rs_Delay_Timer != '0'"!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_ON
[!ELSE!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_OFF
[!ENDIF!]

#endif /* PROG_CFG_IMPL_60_H */
