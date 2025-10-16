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
/*%%   _____________________________   %%  \file PROG_Cfg_Impl80.h              */
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
/* Copyright 2019 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]
#ifndef PROG_CFG_IMPL80_H
#define PROG_CFG_IMPL80_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgPSA')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!IF "node:exists(as:modconf('ProgPSA'))"!]
[!/********************* Feature configuration for PSA-DCTI ************************/!]

/****************************************************/
/*                    General                       */
/****************************************************/
#define PROG_ECU_RESET_RESPONSE_SIZE                       2U
#define PROG_DSC_RESPONSE_SIZE                             2U
#define PROG_TD_RESPONSE_SIZE                              3U
#define PROG_RTE_RESPONSE_SIZE                             1U
#define PROG_COMPARE_KEY_RESPONSE_SIZE                     2U
#define PROG_ERASE_POS_RESPONSE_SIZE                       5U
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
#define PROG_MAX_RD_ADDRESS_LENGTH                         0U

/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                   1U

#define PROG_CVN_CHECK                                     STD_OFF
#define PROG_SEG_LIST_CKS                                  STD_OFF
/* Download type */
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_LOGICAL_BLOCK

#define PROG_APPL_VALID                                    0x00000002U
#define PROG_APPL_INVALID                                  0x00000001U

[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "num:dectoint("0")"!]
[!LOOP "Segments/*"!]
    [!VAR "Memory_Type" = "node:ref(Memory)/Memory_Type"!]
    [!IF "$Memory_Type = 'FLASH'"!]
        [!VAR "MEMORY_MODE_FLASH" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_FLASH > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_FLASH"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'FLASH_EXT'"!]
        [!VAR "MEMORY_MODE_FLASH_EXT" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_FLASH_EXT > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_FLASH_EXT"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'CUSTOM'"!]
        [!VAR "MEMORY_MODE_CUSTOM" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_CUSTOM > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_CUSTOM"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

#define PROG_P2_PROG_SESSION_VAL                           [!WS "27"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2"!]U
#define PROG_P2STAR_PROG_SESSION_VAL                       [!WS "23"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2STAR"!]U
#define PROG_P2_DEFAULT_SESSION_VAL                        [!WS "24"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2"!]U
#define PROG_P2STAR_DEFAULT_SESSION_VAL                    [!WS "20"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2STAR"!]U
#define PROG_IMPL_VARIANT                                  PROG_IMPL_80
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
#define PROG_MULTIPLE_BUFFERS_ENABLE                       [!WS "23"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_REPROG_TYPE                                   PROG_NO_REPROG_TYPE
#define PROG_RESUM_REPROG                                  STD_OFF
#define PROG_GET_PROG_CNTR_ENABLE                          1U
#define PROG_GET_PROG_CNTR_DISABLE                         0U
#define PROG_CNTR_GET_TYPE                                 PROG_GET_PROG_CNTR_DISABLE

#define PROG_AUTHENTICATED_BOOT_ENABLE                     STD_OFF
#define PROG_SECURE_BOOT_ENABLE                            STD_OFF
#define PROG_BOOT_VERIFICATION                             STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION              STD_OFF
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION             STD_OFF

#define PROG_SBL_HEADER_DEFINE                             STD_OFF
#define PROG_ENABLE_DOWNGRADE_PROTECTION                   STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE                STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE              STD_ON
#define PROG_CAL_CRC_ENABLE                                STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                    STD_OFF
#define PROG_PRE_INIT_ENABLE                               STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                      STD_ON
#define PROG_SLEEP_MANAGEMENT_TYPE [!WS "25"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]

[!IF "node:exists(as:modconf('Csm'))"!]
#define PROG_CRY_PRESENT                                   STD_ON

#define PROG_DIGEST_LENGTH                                 64U
#define PROG_SIGNATURE_LENGTH                              384U
#define PROG_KEY_LENGTH                                    384U /* In bytes */

#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
[!ELSE!]
#define PROG_CRY_PRESENT                                   STD_OFF
[!ENDIF!]

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
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED               STD_ON
[!ELSE!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED               STD_OFF
[!ENDIF!]

/*Securiy access request seed delay timer*/
[!IF "as:modconf('SA')/General/Security_Access_Rs_Delay_Timer != '0'"!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED             STD_ON
[!ELSE!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED             STD_OFF
[!ENDIF!]

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                            [!WS "28"!][!IF "Security/NRC78_Transmission/Transmit_Nrc78_On_SecurityAccess = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

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

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                       STD_OFF
/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE                 STD_OFF
#define PROG_USE_ECUID_CALLBACK                            STD_OFF
/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                        STD_OFF
/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                            STD_OFF
/* Download verification configuration */
#define PROG_CRC_ALGO                                      PROG_CRC16
#define PROG_CRC_CALCULATION                               PROG_TD_CRC16
/* CRC byte length (CRC16) */
#define PROG_CRC_BYTE_LENGTH                               2U
#define PROG_HASH_CALCULATION                              STD_OFF
#define PROG_RANGE_CKS                                     STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                    STD_OFF
#define PROG_VERIFICATION_ON_THE_FLY                       STD_OFF
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_OFF
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_OFF
#define PROG_SIGNATURE_CALCULATION                         STD_OFF
#define PROG_SIGNATURE_CALCULATION_OVER_HASH               STD_OFF
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_CRC
#define PROG_CSM_MAC_USED                                  STD_OFF
#define PROG_CSM_HASH_USED                                 STD_OFF
#define PROG_RC_OPTION_RECORD_CRC_VAL_BASE_INDEX           PROG_MSG_BYTE_INDEX(5U)
/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                       STD_OFF

/*Enable the response after reset in function of reset cause*/
#define PROG_RESET_CAUSE_ENABLE                            [!WS "28"!][!IF "General/Transmit_Response_Before_Reset = 'false'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Programming pre-conditions check */
#define PROG_PRECOND_CHECK_ENABLE                          [!WS "26"!][!IF "General/Check_Programming_PreConditions = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                        STD_OFF

/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE                [!WS "16"!][!IF "DownloadFlashRoutines/Download_Flash_Routines = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_OFF

/* Downloading Pseudo Flash driver feature activation */
#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_ENABLE      STD_OFF

#define PROG_DOWNLOAD_FLASH_ROUTINES_REJECT_AFTER_FAILURE  [!WS "2"!][!IF "DownloadFlashRoutines/Reject_RD_After_Corrupt_Flash_Routines = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define PROG_BYPASS_SA_COMPARE_KEY                         [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Most Significant Byte of addresses */
#define PROG_IMPL80_BASE_ADDR                              [!WS "30"!]0x[!"translate(substring(num:inttohex(PSA/Memory_Base_Address,2),3,6),'abcdef','ABCDEF')"!]000000U

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                     STD_OFF

/* Block configuration */
[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
#define PROG_BLOCK_NB                                      [!"num:dectoint($BLOCK_MAX + 1)"!]U
extern const tProg_Block stCfgBlock[PROG_BLOCK_NB];

/* Erase type */
#define PROG_ERASE_TYPE                                    PROG_ERASE_BY_BLOCK_ID
#define PROG_ERASE_ALL                                     STD_OFF

/* Max value of the block identifier */
#define PROG_MAX_BLOCK_ID                                  0xFFU

#define PROG_BOOT_REPROG                                   1U
#define PROG_BOOT_NOREPROG                                 0U

/* Request routine result definitions */
[!VAR "LIST_INDEX" = "num:i(0)"!]
[!FOR "ROUTINE_INDEX" = "1" TO "num:dectoint(count(as:modconf('Uds')/Routine_Control/*))"!]
  [!IF "as:modconf('Uds')/Routine_Control/*[number($ROUTINE_INDEX)]/SubService = '3'"!]
#define PROG_ROUTINE_ID_[!"translate(substring(num:inttohex(as:modconf('Uds')/Routine_Control/*[number($ROUTINE_INDEX)]/Routine_Identifier),3,6),'abcdef','ABCDEF')"!][!WS "31"!]0x[!"translate(substring(num:inttohex(as:modconf('Uds')/Routine_Control/*[number($ROUTINE_INDEX)]/Routine_Identifier),3,6),'abcdef','ABCDEF')"!]U
      [!VAR "LIST_INDEX" = "($LIST_INDEX + 1)"!]
  [!ENDIF!]
[!ENDFOR!]

#define PROG_ROUTINE_RESULT_NB         [!WS "29"!][!"num:dectoint($LIST_INDEX)"!]U

extern const tProgRoutineResultInfo    [!WS "24"!]stCfgRoutineResultTable[PROG_ROUTINE_RESULT_NB];

/****************************************************/
/*                  UDS                             */
/****************************************************/
#define PROG_RESPONSE_PARAMETERS_OFFSET                    (1U)/* This define is used because the tables in C starts from 0 and not 1
                                                                    and the indexes in the specifications starts sometimes from 1 */
/* Services */

/* Routines */
#define PROG_RC_ROUTINE_STATUS_BASE_INDEX          PROG_MSG_BYTE_INDEX(5U)
/* Erase routine */
#define PROG_IMPL80_ERASE_ROUTINE_ID               0xFF00U
/* Self-Check routine */
#define PROG_IMPL80_SELF_CHECK_ROUTINE_ID          0xFF04U

/****************************************************/
/*                  SPECIFIC                        */
/****************************************************/
/* Logical markers definition */
#define PROG_IMPL80_LOGICAL_MARKER_KEY_APPLI       0x88U
#define PROG_IMPL80_LOGICAL_MARKER_CALIB           0x81U
#define PROG_IMPL80_LOGICAL_MARKER_APP_CALIB       0x82U
#define PROG_IMPL80_LOGICAL_MARKER_ZI              0x83U

#define PROG_IMPL80_FIRST_BLOCK_INDEX              0x0U
#define PROG_IMPL80_SECOND_BLOCK_INDEX             0x1U

/* Default APPLI_KEY value and length */
#define PROG_IMPL80_DEFAULT_APPLI_KEY              0xFFFFU
#define PROG_IMPL80_APPLI_KEY_LENGTH               0x02U
/* ZI length */
#define PROG_IMPL80_LOG_ZONE_LENGTH                0x30U

/* LFID value in RD response */
#define PROG_IMPL80_LENGTH_FORMAT_ID               0x10U
/* Max number of block length */
#define PROG_IMPL80_MAX_NUM_BLOCK_LENGTH           0x00U
/* Block sequence value counter for APPLI KEY */
#define PROG_IMPL80_BLOCK_SEQ_COUNT_APPLI_KEY      0x01U
/* Block sequence value counter for ZI */
#define PROG_IMPL80_BLOCK_SEQ_COUNT_ZI             0x01U

/* Polynomial CRC 16 calculation */
#define PROG_IMPL80_CRC_POLYNOMIAL                 0x8408U
/* CRC initialization value */
#define PROG_IMPL80_CRC_INIT_VALUE                 0xFFFFU
/* CRC check value */
#define PROG_IMPL80_CRC_REVERSED_CCITT             0xF0B8U
/* Fault CRC error code */
#define PROG_IMPL80_FAULT_CRC                      0x0AU
/* No more space available error code */
#define PROG_IMPL80_NO_MORE_SPACE_AVAILABLE        0x08U
/* Writing OK code */
#define PROG_IMPL80_WRITING_OK                     0x02U
/* Routines error codes: */
/* Writing error code */
#define PROG_IMPL80_ERROR_WRITING                  0x10U
/* Software checking error code */
#define PROG_IMPL80_SOFTWARE_NOT_OK                0x08U
/* Calibration checking error code */
#define PROG_IMPL80_CALIBRATION_NOT_OK             0x04U
/* ACT checking error code */
#define PROG_IMPL80_ACT_NOT_OK                     0x40U

/* Log save marking byte reset value */
#define PROG_IMPL80_LOG_SAVE_MARKING_RESET         0x00U

/* Tool-Signature value */
#define PROG_IMPL80_TOOL_SIGNATURE                 0xF05A

/* Flash routine decompression */
#define PROG_DECOMP_FLASH_ROUTINES                 STD_OFF

/* Index of the first byte in TD request */
#define PROG_IMPL80_INFO_DATA_FIRST_BYTE_IN_TD     0x06
#define PROG_IMPL80_KEY_APPLI_FIRST_BYTE_IN_TD     0x02
#define PROG_IMPL80_ZI_FIRST_BYTE_IN_TD            0x02

/* ECU Status */
#define PROG_IMPL80_ECU_STATUS_APP_INHIBITED               0x00
#define PROG_IMPL80_ECU_STATUS_CLEARING_APP_INHIBITED      0xFF
#define PROG_IMPL80_ECU_STATUS_END_ALIGNEMENT              0xF0

/* Max size of data to be written after several TD */
#define PROG_IMPL80_MAX_WRITTEN_DATA_NBR           1024U

/* Min expected size of data in a transfer data request */
#define PROG_IMPL80_MIN_TD_SIZE                    8U

[!ENDIF!]
#endif /* PROG_CFG_IMPL80_H */
