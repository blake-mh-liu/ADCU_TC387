/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BM configuration                              */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cfg.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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

#ifndef BM_CFG_H
#define BM_CFG_H

#define BM_IMPL_10                          10U
#define BM_IMPL_NOT_DEFINED                 255U

[!IF "node:exists(as:modconf('ProgVCC')) and (as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
#define BM_IMPL_VARIANT                     BM_IMPL_10
[!ELSE!]
#define BM_IMPL_VARIANT                     BM_IMPL_NOT_DEFINED
[!ENDIF!]

[!IF "General/Test_Application = 'true'"!]
#define BM_EXECUTE_TESTAPPL                 STD_ON
[!ELSE!]
#define BM_EXECUTE_TESTAPPL                 STD_OFF
[!ENDIF!]

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager""!]
#define BM_BOOT_MANAGER_VARIANT             BM_INITIAL_BOOT_MANAGER
  [!IF "as:modconf('BM')/General/Initial_Boot_Check_Application = 'true'"!]
#define BM_INITIAL_BOOT_APPLICATION_VALIDITY_CHECK        STD_ON
  [!ELSE!]
#define BM_INITIAL_BOOT_APPLICATION_VALIDITY_CHECK        STD_OFF
  [!ENDIF!]
[!ELSE!]
#define BM_BOOT_MANAGER_VARIANT             BM_BOOT_MANAGER
[!ENDIF!]

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager""!]
  [!IF "as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT ='Secure'"!]
#define BM_BLU_BLOCK_ID                     0U
  [!ENDIF!]
[!ELSE!]
  /* BM Csm Presence */
  [!IF "node:exists(as:modconf('Csm'))"!]
#define BM_CSM_PRESENT                      STD_ON
    [!IF "node:exists(as:modconf('CryIf'))"!]
/* Crypto stack ASR 4.3 is used */
#define BM_CSM_ASR43_USED                   STD_ON
#define BM_Csm_Mainfunction                 Crypto_MainFunction
      [!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF') and (Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
        [!IF "Security/BMCsmReferences/BS_size = '0'"!]
#define BM_BLOC_SLICING_ENABLED             STD_OFF
        [!ELSE!]
#define BM_BLOC_SLICING_ENABLED             STD_ON
#define BM_BLOC_SLICING_SIZE                [!WS "16"!][!"num:dectoint(Security/BMCsmReferences/BS_size)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
/* Crypto stack ASR version used is below ASR 4.3 */
#define BM_CSM_ASR43_USED                   STD_OFF
#define BM_Csm_Mainfunction                 Csm_MainFunction
    [!ENDIF!]
  [!ELSE!]
/* CSM module not configured/added!*/
#define BM_CSM_PRESENT                      STD_OFF
#define BM_Csm_Mainfunction();
#define BM_CSM_ASR43_USED                   STD_OFF
  [!ENDIF!]

  [!IF "node:exists(as:modconf('CryShe'))"!]
#define BM_CRYSHE_PRESENT                                STD_ON
  [!ELSE!]
#define BM_CRYSHE_PRESENT                                STD_OFF
  [!ENDIF!]

  [!IF "node:exists(as:modconf('EB'))"!]
 /*Network Selection before BL 3 via the EB module*/
#define BM_CAN_USED              0U
#define BM_FLEXRAY_USED          1U
#define BM_ETHERNET_USED         2U
#define BM_NETWORK_USED              [!WS "21"!][!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]BM_CAN_USED[!ELSEIF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]BM_FLEXRAY_USED[!ELSE!]BM_ETHERNET_USED[!ENDIF!]
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]

#define BM_FR_CYCLE_LENGTH              [!"General/BM_FR_CYCLE_LENGTH"!]U
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_ON
    [!ELSE!]
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_OFF
    [!ENDIF!]
  [!ENDIF!]

/* BM Network Management */
#define BM_NETWORK_MANAGEMENT_ENABLE              [!WS "8"!][!IF "(as:modconf('Prog')/General/Network_Management = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

  [!IF "node:exists(as:modconf('BlPduR'))"!]
 /*Network Selection for BL-3.x(when BLPDUR module used)*/
    [!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_ON
#define BM_FR_CYCLE_LENGTH                  [!"General/BM_FR_CYCLE_LENGTH"!]U
    [!ELSE!]
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_OFF
    [!ENDIF!]
  [!ELSE!]
#ifndef BM_NETWORK_FLEXRAY_SUPPORTED
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_OFF
#endif
  [!ENDIF!]
  [!IF "node:exists(as:modconf('BlPduR'))"!]
    [!IF "as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true'"!]
#define BM_NETWORK_CAN_SUPPORTED              STD_ON
    [!ELSE!]
#define BM_NETWORK_CAN_SUPPORTED              STD_OFF
    [!ENDIF!]
  [!ELSE!]
#define BM_NETWORK_CAN_SUPPORTED              STD_OFF
  [!ENDIF!]

  [!IF "node:exists(as:modconf('BlPduR'))"!]
    [!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]
#define BM_NETWORK_ETH_SUPPORTED              STD_ON
    [!ELSE!]
#define BM_NETWORK_ETH_SUPPORTED              STD_OFF
    [!ENDIF!]
  [!ELSE!]
#define BM_NETWORK_ETH_SUPPORTED              STD_OFF
  [!ENDIF!]

  [!IF "node:exists(as:modconf('BlPduR'))"!]
    [!IF "as:modconf('BlPduR')/General/Lin_Protocol_Supported = 'true'"!]
#define BM_NETWORK_LIN_SUPPORTED              STD_ON
    [!ELSE!]
#define BM_NETWORK_LIN_SUPPORTED              STD_OFF
    [!ENDIF!]
  [!ELSE!]
#define BM_NETWORK_LIN_SUPPORTED              STD_OFF
  [!ENDIF!]
/* BM Timeout Check */
#define BM_TIMEOUT_CHECK_OFF                0U
#define BM_TIMEOUT_CHECK_ON                 1U
#define BM_TIMEOUT_CHECK                    [!WS "20"!][!IF "General/BM_TIMEOUT_CHECK = 'true'"!]BM_TIMEOUT_CHECK_ON[!ELSE!]BM_TIMEOUT_CHECK_OFF[!ENDIF!]

  [!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
/* Specific to timeout management */
#define BM_CALL_CYCLE                       [!"General/BM_CALL_CYCLE"!]U
#define BM_TIMEOUT_VALUE                    [!"General/BM_TIMEOUT_VALUE"!]U
  [!ENDIF!]

  [!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/* Accept All Tester Address Value */
#define EB_ALL_TESTER_ADDRESS               0xFFU
  [!ENDIF!]

/* Source Address Check status */
#define BM_SOURCE_ADDRESS_CHECK             [!WS "13"!][!IF "(as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

  [!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF')
       and (node:exists(as:modconf('ProgDAG'))
       or  (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
       or  (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode = 'LogicalBlock'))"!]
/* Table of information for each Block needed for Authenticated/Secure Boot */
extern const tProg_BlockSecureBootInfo stCfgBMBlockSecureBootInfo[PROG_BLOCK_NB];
  [!ENDIF!]

  [!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF')
       and ((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')
       or    node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgJLR'))
       or   (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'LogicalBlock'))"!]
  [!VAR "SEGMENT_MAX"="num:dectoint(count(as:modconf('Prog')/Segments/*))"!]
 /* Table of information for each Segment needed for Authenticated/Secure Boot */
extern const tProg_BlockSecureBootInfo stCfgBMBlockSecureBootInfo[[!"$SEGMENT_MAX"!]];
  [!ENDIF!]

  [!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure') and node:exists(as:modconf('ProgOEMInd')))
    or (as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager")"!]
  [!ENDIF!]

  [!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
extern tBMTimeout m_ubBMTimeoutCount;
  [!ENDIF!]
[!ENDIF!]

/* BM Authenticated Boot/Secure Boot information */
#define BM_AUTHENTICATED_BOOT_ENABLE        [!WS "8"!][!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_SECURE_BOOT_ENABLE               [!WS "15"!][!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_BOOT_CHECKSUM_VERIFICATION       [!WS "7"!][!IF "(as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "(((Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or (Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')) and (Security/SecureBoot/BMSecureBootWithHsm = 'false'))"!]
/* Specific to Authenticated and Secure Boot */
  [!IF "node:exists(as:modconf('CryIf'))"!]
#define BM_CSM_KEY_ID                       [!"as:ref(as:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobKeyRef)/CsmKeyId"!]U
    [!IF "as:modconf('BM')/Security/BMCsmReferences/SetCryptoKey = 'true'"!]
      [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
      [!VAR "KEYELEPOSNUM"="1"!]
#define BM_CSM_SET_KEY_ENABLED             STD_ON
#define BM_CSM_KEY_ELEMENT_ID              [!"as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId"!]U
    [!ELSE!]
#define BM_CSM_SET_KEY_ENABLED             STD_OFF
    [!ENDIF!]
    [!IF "as:modconf('BM')/Security/BMCsmReferences/Cancel_OngoingJobs = 'true'"!]
#define BM_CSM_CANCELJOB_ENABLED           STD_ON
    [!ELSE!]
#define BM_CSM_CANCELJOB_ENABLED          STD_OFF
    [!ENDIF!]
/* Type of algorithm used to check integrity of Bootloader/Application */
/* For version of Csm from 4.3.0 */
/* Csm Configuration used */
#define BM_CSM_CHECKSUM_ID                  [!WS "18"!][!"(as:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobId)"!]U
#define BM_CSM_HASH_USED                    [!WS "20"!][!IF "node:exists(node:ref(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)/CsmHash)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_CSM_MAC_USED                     [!WS "21"!][!IF "node:exists(node:ref(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)/CsmMacVerify)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
  [!ELSE!]
/* For version of Csm to 4.0.3 */
/* Csm Configuration used */
#define BM_CSM_CHECKSUM_ID                  [!WS "18"!][!"as:name(as:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId))"!]
#define BM_CSM_MAC_USED                     [!WS "21"!][!IF "contains(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId, '/Csm/Csm/CsmMacVerify/') =  'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_CSM_HASH_USED                    [!WS "20"!][!IF "contains(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId, '/Csm/Csm/CsmHash/') =  'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
  [!ENDIF!]
  [!IF "Security/SecureBoot/BOOT_VERIFICATION = 'ON'"!]
/* Specific to Authenticated and Secure Boot with Bootloader verification */
#define BM_BOOT_START_ADDR                  ([!"num:inttohex(Security/SecureBoot/BootCksStartAddress)"!]U)
#define BM_BOOT_LENGTH                      ([!"num:inttohex(Security/SecureBoot/BootCksRangeLength)"!]U)
  [!ENDIF!]
[!ELSE!]
#define BM_CSM_MAC_USED                     STD_OFF
#define BM_CSM_HASH_USED                    STD_OFF
[!ENDIF!]

[!IF "as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true'"!]
#define BM_HSM_MAC_USED                     STD_ON
[!ELSE!]
#define BM_HSM_MAC_USED                     STD_OFF
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF') and (Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
/* Size of the checksum */
#define BM_CHECKSUM_SIZE_IN_BITS            [!"num:dectoint((Security/SecureBoot/CHECKSUM_LENGTH)*8)"!]U
#define BM_CHECKSUM_SIZE_IN_BYTES           [!"num:dectoint(Security/SecureBoot/CHECKSUM_LENGTH)"!]U
[!ENDIF!]

[!IF "as:modconf('BM')/General/Dual_Memory_Bank_Used = 'true'"!]
#define BM_OTA_DUALBANK_USED                          STD_ON
[!ELSE!]
#define BM_OTA_DUALBANK_USED                          STD_OFF
[!ENDIF!]

[!IF "as:modconf('BM')/General/Trial_period = 'true'"!]
#define BM_TRIAL_PERIOD                          STD_ON
[!ELSE!]
#define BM_TRIAL_PERIOD                          STD_OFF
[!ENDIF!]

#endif /* BM_CFG_H */
