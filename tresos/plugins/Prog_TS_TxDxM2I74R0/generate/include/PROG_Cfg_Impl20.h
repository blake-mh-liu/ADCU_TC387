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
/*%%   _____________________________   %%  \file PROG_Cfg_Impl20.h                      */
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
#ifndef PROG_CFG_IMPL20_H
#define PROG_CFG_IMPL20_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgGM')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]


[!IF "node:exists(as:modconf('ProgGM'))"!]

[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
    [!VAR "APP_PARTITION_NUM" = "0"!]
    [!VAR "APP_PARTITION_FOUND" = "0"!]
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "PARTITION"="Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
        [!IF "$PARTITION = 'PROG_APPLICATION_PARTITION'"!]
            [!IF "$APP_PARTITION_NUM = 0"!]
                [!VAR "APP_PARTITION_NUM"= "$SEGMENT_IDX"!]
                [!VAR "APP_PARTITION_FOUND"= "1"!]
            [!ELSE!]
                [!ERROR "Only one application segment shall be configured"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDFOR!]
    [!IF "$APP_PARTITION_FOUND = 0"!]
        [!ERROR "One application segment shall be configured"!]
    [!ENDIF!]
[!ENDIF!]

#define PROG_ECU_RESET_RESPONSE_SIZE                       2U
#define PROG_DSC_RESPONSE_SIZE                             2U
#define PROG_TD_RESPONSE_SIZE                              2U
#define PROG_RTE_RESPONSE_SIZE                             1U
#define PROG_TD_MIN_SIZE                                   2U
#define PROG_TD_MIN_SIZE_RD                                3U
#define PROG_ERASE_REQUEST_DATA                            4U
#define PROG_ERASE_POS_RESPONSE_SIZE                       4U
#define PROG_NRC_SIZE                                      3U
#define PROG_RTE_SIZE                                      1U

#define PROG_REGION_INFO_SIZE                              8U
#define PROG_MODULE_INFO_CCID_SIZE                         2U
#define PROG_MODULE_CCID_ADDR_OFFSET                       6U

#define PROG_SW_APP_ID                                     0x01U
#define PROG_SBA_MODULE_ID                                 0x5BU

#define PROG_DIGEST_LENGTH                                 32U
#define PROG_SIGNATURE_LENGTH                              256U

/* !!!! To Be Generated once Csm stub will be available !!!!*/
#define PROG_CRY_PRESENT                                   STD_ON
#define PROG_CAL_PRESENT                                   STD_ON
#define PROG_CRYSHE_PRESENT                                STD_OFF

#define PROG_KEY_LENGTH                                    256U /* In bytes */
#define PROG_CRY_EXPONENT_ENABLED                          STD_ON

#define PROG_GET_PROG_CNTR_ENABLE                          1U
#define PROG_GET_PROG_CNTR_DISABLE                         0U
#define PROG_CNTR_GET_TYPE                                 PROG_GET_PROG_CNTR_DISABLE

#define PROG_ENABLE_DOWNGRADE_PROTECTION                   STD_OFF


#define PROG_ERASE_TYPE                                    PROG_ERASE_BY_DYNAMIC_PARTITION_ID

/* Data verification */
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_HASH
#define PROG_CRC_CALCULATION                               PROG_NO_CRC
#define PROG_SIGNATURE_CALCULATION                         STD_ON
#define PROG_HASH_CALCULATION                              STD_ON
#define PROG_RANGE_CKS                                     STD_OFF
#define PROG_SEG_LIST_CKS                                  STD_OFF
#undef PROG_VERIFICATION_ON_THE_FLY
#define PROG_VERIFICATION_ON_THE_FLY                       STD_ON
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                   STD_ON
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_ADDR
#define PROG_CVN_CHECK                                     STD_OFF

#define PROG_MAX_RD_ADDRESS_LENGTH                         4U
/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                   1U

#define PROG_SIGNATURE_CALCULATION_OVER_HASH               STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                    STD_OFF
#define PROG_RESUM_REPROG                                  STD_OFF

#define PROG_REPROG_TYPE                                   PROG_NO_REPROG_TYPE

/* Tester address check (tester filtering) */
[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
#define PROG_SOURCE_ADDRESS_CHECK_ENABLE                   STD_ON
[!ELSE!]
#define PROG_SOURCE_ADDRESS_CHECK_ENABLE                   STD_OFF
[!ENDIF!]

#define PROG_APP_SEGMENT_ID                                [!"num:dectoint($APP_PARTITION_NUM - 1)"!]U


#if ((!defined(EB_INTEGRATION_TEST)) && (!defined(NCS_UNITARY_TEST)))
#define PROG_APP_SW_INFO_ADDR                              [!"num:inttohex(Segments/*[number($APP_PARTITION_NUM)]/Reprog_Start_Address)"!]U
#else
extern u8 TS_aubAppSwInfo[];
#define PROG_APP_SW_INFO_ADDR                              TS_aubAppSwInfo
#endif

#define PROG_SBA_TICKET_SIZE                               822U

#define PROG_APP_PSI_ADDR                                  [!WS "15"!]([!"num:inttohex(Segments/*[number($APP_PARTITION_NUM)]/Erase_End_Address)"!]U - PROG_PSI_SIZE) + 1U

#define PROG_ECU_ADDR                                      [!WS "19"!][!"num:inttohex(GM/ECU_ADDR)"!]U

/* Value to return in PSI read DID */
#define PROG_PSI_DID_PROGRAMMED                            0U
#define PROG_PSI_DID_REVOKED                               1U
#define PROG_PSI_DID_INVALID                               2U

/* Datatype define */
#define PROG_DATATYPE_PLAIN                                0x0101U
#define PROG_DATATYPE_PROTECTED                            0x0200U
#define PROG_DATATYPE_SIGNED                               0x0301U
[!IF "(node:exists(as:modconf('Cal')) and as:modconf('Prog')/General/Enable_Compression='true')"!]
[!IF "as:modconf('Cal')/CalDecompress/CalDecompressConfig/*/CalDecompressPrimitiveName='ARLEDecompress'"!]
#define PROG_DATATYPE_COMPRESSED                           0x0401U
[!ELSEIF "as:modconf('Cal')/CalDecompress/CalDecompressConfig/*/CalDecompressPrimitiveName='LZMADecompress'"!]
#define PROG_DATATYPE_COMPRESSED                           0x0402U
[!ENDIF!]
[!ENDIF!]
#define PROG_DATATYPE_ENCRYPTED                            0x0500U
#define PROG_DATATYPE_DIFERENCE                            0x0600U

#define PROG_PSI_SIZE                                      (2U*PROG_MIN_VAL_TO_WRITE)
#define PROG_PSI_VAL_SIZE                                  8U
#define PROG_REGION_INFO_SIZE                              8U

#define PROG_SWINFO_FROM_FLASH                             0U

/* Minimum size of AppSignedHeader/CalSignedHeader */
#define PROG_MIN_HEADER_SIZE                               856U
/* Minimum size of application header (AppSignedHeader 866 + AppSwInfo 52) */
#define PROG_MIN_APP_HEADER_SIZE                            918U
/* Minimum size of AppSignedHeader */
#define PROG_MIN_APP_SIGNED_HEADER_SIZE                     866U


#define PROG_GET_U32_VAL(Address)                           ((u32)((u32)(((u32)((Address)[0])) << 24U) & 0xFF000000U) + (u32)((u32)(((u32)((Address)[1])) << 16U) & 0x00FF0000U) + (u32)((u32)(((u32)((Address)[2])) << 8U) & 0x0000FF00U) + (u32)(((u32)((Address)[3])) & 0x000000FFU))
#define PROG_GET_U16_VAL(Address)                           ((u16)((u16)(((u16)((Address)[0])) << 8U) & 0xFF00U) + (u16)(((u16)((Address)[1])) & 0x00FFU))

#define PROG_EXT_FLASH_OFFSET   [!"num:inttohex(GM/External_Flash_Offset)"!]U
#define PROG_20_APP_SW_INFO_SIZE   [!"num:inttohex(GM/Application_InfoHeader_Size)"!]U

/* Macro definition to access all data in headers */
extern u8* m_pubAppSwInfo;
extern u8 m_aubAppSwInfo_RAM_mirror[PROG_20_APP_SW_INFO_SIZE];
#define PROG_GET_APP_SW_CONF_OPT_ADDR                       ((u8*)(&m_aubAppSwInfo_RAM_mirror[2U]))
#define PROG_GET_APP_SW_CONF_OPT_ADDR_FROM_REQ(HeaderAddr,RegionNbr)((u8*)(&HeaderAddr[860U + (8U * RegionNbr) + 2U] ))

#define PROG_GET_APP_SW_CONF_OPT PROG_GET_U16_VAL(PROG_GET_APP_SW_CONF_OPT_ADDR)
#define PROG_GET_APP_SW_CONF_OPT_FROM_REQ(HeaderAddr,RegionNbr) PROG_GET_U16_VAL(PROG_GET_APP_SW_CONF_OPT_ADDR_FROM_REQ(HeaderAddr,RegionNbr))

#define PROG_GET_APP_SW_NBID_ADDR                           ((u8*)(&m_aubAppSwInfo_RAM_mirror[8U]))
#define PROG_GET_APP_SW_NBID_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (((u8*)(&HeaderAddr[860U + (8U * RegionNbr)+ 8U] ))

#define PROG_GET_APP_SW_NBID PROG_GET_U16_VAL(PROG_GET_APP_SW_NBID_ADDR)
#define PROG_GET_APP_SW_NBID_FROM_REQ(HeaderAddr,RegionNbr) PROG_GET_U16_VAL(PROG_GET_APP_SW_NBID_ADDR_FROM_REQ(HeaderAddr,RegionNbr))

#define PROG_GET_APP_SW_DLS_ADDR            (u8 *)(&(PROG_GET_APP_SW_NBID_ADDR)[2U])
#define PROG_GET_APP_SW_DLS_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (u8 *)(&(PROG_GET_APP_SW_NBID_ADDR_FROM_REQ(HeaderAddr,RegionNbr))[2U])

#define PROG_GET_APP_SW_DLS PROG_GET_U16_VAL(PROG_GET_APP_SW_DLS_ADDR)
#define PROG_GET_APP_SW_DLS_FROM_REQ(HeaderAddr,RegionNbr) PROG_GET_U16_VAL(PROG_GET_APP_SW_DLS_ADDR_FROM_REQ(HeaderAddr,RegionNbr))

#define PROG_GET_APP_SW_REGION_NB_ADDR      ((u8*)(&m_aubAppSwInfo_RAM_mirror[16U + ((PROG_GET_APP_SW_CONF_OPT)*16U)]))
#define PROG_GET_APP_SW_REGION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr) ((u8*)(&HeaderAddr[860U + (8U * RegionNbr) + 16U + ((PROG_GET_APP_SW_CONF_OPT_FROM_REQ(HeaderAddr,RegionNbr))*16U)]))

#define PROG_GET_APP_SW_REGION_NB PROG_GET_U16_VAL(PROG_GET_APP_SW_REGION_NB_ADDR)
#define PROG_GET_APP_SW_REGION_NB_FROM_REQ(HeaderAddr,RegionNbr) PROG_GET_U16_VAL(PROG_GET_APP_SW_REGION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr))

#define PROG_GET_APP_SW_FIRST_REGION_ADDR_START_ADDR (u8*)(&(PROG_GET_APP_SW_REGION_NB_ADDR)[2U])
#define PROG_GET_APP_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (u8*)(&(PROG_GET_APP_SW_REGION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr))[2U])

#define PROG_GET_APP_SW_FIRST_REGION_SIZE_START_ADDR (u8*)(&(PROG_GET_APP_SW_FIRST_REGION_ADDR_START_ADDR)[4U])
#define PROG_GET_APP_SW_FIRST_REGION_SIZE_START_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (u8*)(&(PROG_GET_APP_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,RegionNbr))[4U])

#define PROG_GET_CALIB_PARTITION_NB_ADDR (u8*)(&(PROG_GET_APP_SW_REGION_NB_ADDR)[(2U + (8U*(PROG_GET_APP_SW_REGION_NB)))])
#define PROG_GET_CALIB_PARTITION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (u8*)(&(PROG_GET_APP_SW_REGION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr))[(2U + (8U*(PROG_GET_APP_SW_REGION_NB_FROM_REQ(HeaderAddr,RegionNbr))))])

#define PROG_GET_CALIB_PARTITION_NB PROG_GET_U16_VAL(PROG_GET_CALIB_PARTITION_NB_ADDR)
#define PROG_GET_CALIB_PARTITION_NB_FROM_REQ(HeaderAddr,RegionNbr) PROG_GET_U16_VAL(PROG_GET_CALIB_PARTITION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr))

#define PROG_GET_CALIB_SW_FIRST_PARTITION_ADDR (u8*)(&(PROG_GET_CALIB_PARTITION_NB_ADDR)[2U])
#define PROG_GET_CALIB_SW_FIRST_PARTITION_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (u8*)(&(PROG_GET_CALIB_PARTITION_NB_ADDR_FROM_REQ(HeaderAddr,RegionNbr))[2U])

#define PROG_GET_CALIB_SW_FIRST_PARTITION_REGION_NBR_ADDR (u8*)PROG_GET_CALIB_SW_FIRST_PARTITION_ADDR
#define PROG_GET_CALIB_SW_FIRST_PARTITION_REGION_NBR_ADDR_FROM_REQ(HeaderAddr,RegionNbr) (u8*)PROG_GET_CALIB_SW_FIRST_PARTITION_ADDR_FROM_REQ(HeaderAddr,RegionNbr)

#define PROG_GET_CALIB_SW_REGION_NBR_ADDR(PartitionId) (u8*)PROG_GetPartitionAddrInAppSWInfo(NULL_PTR, PartitionId,PROG_SWINFO_FROM_FLASH)
#define PROG_GET_CALIB_SW_REGION_NBR_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) (u8*)PROG_GetPartitionAddrInAppSWInfo(HeaderAddr,PartitionId,RegionNbr)

#define PROG_GET_CALIB_SW_REGION_NBR(PartitionId) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_REGION_NBR_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_REGION_NBR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_REGION_NBR_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))

#define PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR(PartitionId) (u8*)(&(PROG_GET_CALIB_SW_REGION_NBR_ADDR(PartitionId))[2])
#define PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) (u8*)(&(PROG_GET_CALIB_SW_REGION_NBR_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))[2])

#define PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START(PartitionId)  PROG_GET_U32_VAL(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_FROM_REQ(HeaderAddr,PartitionId,RegionNbr)  PROG_GET_U32_VAL(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))


#define PROG_GET_CALIB_SW_FIRST_REGION_SIZE_START_ADDR(PartitionId) (u8*)(&(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR(PartitionId))[4U])
#define PROG_GET_CALIB_SW_FIRST_REGION_SIZE_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) (u8*)(&(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))[4U])

#define PROG_GET_CALIB_SW_FIRST_REGION_SIZE_START(PartitionId) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_FIRST_REGION_SIZE_START_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_FIRST_REGION_SIZE_START_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_FIRST_REGION_SIZE_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))

#define PROG_GET_CALIB_SW_LAST_REGION_ADDR_START_ADDR(PartitionId) (u8*)(&(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR(PartitionId))[((PROG_GET_CALIB_SW_REGION_NBR(PartitionId)) - 1U) * 8U])
#define PROG_GET_CALIB_SW_LAST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,artitionId,RegionNbr) (u8*)(&(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))[((PROG_GET_CALIB_SW_REGION_NBR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr)) - 1U) * 8U])

#define PROG_GET_CALIB_SW_LAST_REGION_ADDR_START(PartitionId) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_LAST_REGION_ADDR_START_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_LAST_REGION_ADDR_START_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_LAST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))

#define PROG_GET_CALIB_SW_LAST_REGION_SIZE_ADDR(PartitionId) (u8*)( &(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR(PartitionId))[4U + (((PROG_GET_CALIB_SW_REGION_NBR(PartitionId)) - 1U) * 8U)])
#define PROG_GET_CALIB_SW_LAST_REGION_SIZE_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) (u8*)( &(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))[4U + (((PROG_GET_CALIB_SW_REGION_NBR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr)) - 1U) * 8U)])

#define PROG_GET_CALIB_SW_LAST_REGION_SIZE(PartitionId) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_LAST_REGION_SIZE_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_LAST_REGION_SIZE_FROM_REQ(HeaderAddr,PartitionId,RegionNbr)   PROG_GET_U32_VAL(PROG_GET_CALIB_SW_LAST_REGION_SIZE_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))


#define PROG_GET_CALIB_SW_MODULE_NBR_ADDR(PartitionId) (u8 *)(&(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR(PartitionId))[((PROG_GET_CALIB_SW_REGION_NBR(PartitionId))*8U)])
#define PROG_GET_CALIB_SW_MODULE_NBR_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) (u8 *)(&(PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))[((PROG_GET_CALIB_SW_REGION_NBR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))*8U)])

#define PROG_GET_CALIB_SW_MODULE_NBR(PartitionId) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_MODULE_NBR_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_MODULE_NBR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_MODULE_NBR_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))

#define PROG_GET_CALIB_SW_FIRST_MODULE_ID_ADDR(PartitionId) (u8*)(&(PROG_GET_CALIB_SW_MODULE_NBR_ADDR(PartitionId))[2U])
#define PROG_GET_CALIB_SW_FIRST_MODULE_ID_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) (u8*)(&(PROG_GET_CALIB_SW_MODULE_NBR_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))[2U])

#define PROG_GET_CALIB_SW_FIRST_MODULE_ID(PartitionId) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_FIRST_MODULE_ID_ADDR(PartitionId))
#define PROG_GET_CALIB_SW_FIRST_MODULE_ID_FROM_REQ(HeaderAddr,PartitionId,RegionNbr) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_FIRST_MODULE_ID_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr))

#define PROG_GET_CALIB_SW_MODULE_ID_ADDR(PartitionId,ModuleIndex) (u8*)(&((PROG_GET_CALIB_SW_FIRST_MODULE_ID_ADDR(PartitionId)))[(12U * ModuleIndex)])
#define PROG_GET_CALIB_SW_MODULE_ID_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) (u8*)(&((PROG_GET_CALIB_SW_FIRST_MODULE_ID_ADDR_FROM_REQ(HeaderAddr,PartitionId,RegionNbr)))[(12U * ModuleIndex)])

#define PROG_GET_CALIB_SW_MODULE_ID(PartitionId,ModuleIndex) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_MODULE_ID_ADDR(PartitionId,ModuleIndex))
#define PROG_GET_CALIB_SW_MODULE_ID_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_MODULE_ID_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr))

#define PROG_GET_CALIB_SW_MODULE_CCID_ADDR(PartitionId,ModuleIndex) (u8*)(&((PROG_GET_CALIB_SW_MODULE_ID_ADDR(PartitionId,ModuleIndex)))[2U])
#define PROG_GET_CALIB_SW_MODULE_CCID_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) (u8*)(&((PROG_GET_CALIB_SW_MODULE_ID_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr)))[2U])

#define PROG_GET_CALIB_SW_MODULE_CCID(PartitionId,ModuleIndex) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_MODULE_CCID_ADDR(PartitionId,ModuleIndex))
#define PROG_GET_CALIB_SW_MODULE_CCID_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) PROG_GET_U16_VAL(PROG_GET_CALIB_SW_MODULE_CCID_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr))

#define PROG_GET_CALIB_SW_MODULE_ADDR_ADDR(PartitionId,ModuleIndex) (u8*)(&((PROG_GET_CALIB_SW_MODULE_CCID_ADDR(PartitionId,ModuleIndex)))[2U])
#define PROG_GET_CALIB_SW_MODULE_ADDR_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) (u8*)(&((PROG_GET_CALIB_SW_MODULE_CCID_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr)))[2U])

#define PROG_GET_CALIB_SW_MODULE_ADDR(PartitionId,ModuleIndex) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_MODULE_ADDR_ADDR(PartitionId,ModuleIndex))
#define PROG_GET_CALIB_SW_MODULE_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_MODULE_ADDR_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr))

#define PROG_GET_CALIB_SW_MODULE_SIZE_ADDR(PartitionId,ModuleIndex) (u8*)(&((PROG_GET_CALIB_SW_MODULE_ADDR_ADDR(PartitionId,ModuleIndex)))[4U])
#define PROG_GET_CALIB_SW_MODULE_SIZE_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) (u8*)(&((PROG_GET_CALIB_SW_MODULE_ADDR_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr)))[4U])

#define PROG_GET_CALIB_SW_MODULE_SIZE(PartitionId,ModuleIndex) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_MODULE_SIZE_ADDR(PartitionId,ModuleIndex))
#define PROG_GET_CALIB_SW_MODULE_SIZE_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr) PROG_GET_U32_VAL(PROG_GET_CALIB_SW_MODULE_SIZE_ADDR_FROM_REQ(HeaderAddr,PartitionId,ModuleIndex,RegionNbr))

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

[!IF "General/Network_Management = 'true'"!]
#define PROG_FR_NS_INIT                                 0x0000U
#define PROG_FR_NS_NORMAL                               0x0001U
#define PROG_FR_NS_BOOT                                 0x1000U
#define PROG_FR_NS_UNDEFINED                            0x2000U
[!ENDIF!]

#define PROG_P2_PROG_SESSION_VAL                        [!WS "27"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2"!]U
#define PROG_P2STAR_PROG_SESSION_VAL                    [!WS "23"!](u16)[!"as:modconf('Uds')/Session/PROGRAMMING/UDS_P2STAR"!]U
#define PROG_P2_DEFAULT_SESSION_VAL                     [!WS "24"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2"!]U
#define PROG_P2STAR_DEFAULT_SESSION_VAL                 [!WS "20"!](u16)[!"as:modconf('Uds')/Session/DEFAULT/UDS_P2STAR"!]U

#define PROG_IMPL_VARIANT                               PROG_IMPL_20

/*Protected Calibration*/
[!VAR "NBR_PROT_CAL"="0"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
    [!VAR "NBR_PROT_CAL" = "num:dectoint($NBR_PROT_CAL) + 1"!]
[!ENDIF!]
[!ENDFOR!]
[!IF "$NBR_PROT_CAL > 0"!]
#define PROG_BOOT_PROT_PARTITIONS                       STD_ON
[!ELSE!]
#define PROG_BOOT_PROT_PARTITIONS                       STD_OFF
[!ENDIF!]
#define PROG_WATCHDOG_ENABLE                            STD_OFF
#define PROG_REQUEST_DOWNLOAD_ENABLE                    STD_ON
#define PROG_SECURITY_ENABLE                            STD_OFF
#define PROG_SA_SEED_ENABLE                             STD_ON
#define PROG_SA_KEY_ENABLE                              STD_OFF
#define PROG_ERASE_MEMORY_ENABLE                        STD_ON
#define PROG_TRANSFER_DATA_ENABLE                       STD_ON
#define PROG_REQUEST_TRANSFER_EXIT_ENABLE               STD_ON
#define PROG_ECU_RESET_ENABLE                           STD_OFF
#define PROG_ACTIVE_SBL_ENABLE                          STD_OFF
#define PROG_UPDATE_PSI_ENABLE                          STD_ON
#define PROG_CONTROL_DTC_SETTING_ENABLE                 STD_ON
#define PROG_COMMUNICATION_CONTROL_ENABLE               STD_ON
#define PROG_CHECK_MEMORY_ENABLE                        STD_OFF
#define PROG_GET_EXPECTED_CRC_ENABLED                   STD_OFF
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                 STD_OFF
#define PROG_SET_CRC_COMPARE_RESULT_ENABLE              STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE    STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE     STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE      STD_OFF
#define PROG_NETWORK_MANAGEMENT_ENABLE                  STD_OFF
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE            STD_OFF
#define PROG_APPLI_CHECK_ENABLE                         STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                    [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_PEC_ENABLE                                 [!WS "33"!][!IF "GM/PEC_Enable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_USE_ECUID_CALLBACK                         [!WS "25"!][!IF "GM/EcuId_Source = 'User_Callback'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_MULTIPLE_BUFFERS_ENABLE                    [!WS "20"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BYPASS_SA_COMPARE_KEY                      [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_SBL_HEADER_DEFINE                          STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE             STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE           STD_ON
#define PROG_CAL_CRC_ENABLE                             STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                 STD_OFF
#define PROG_PRE_INIT_ENABLE                            STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                   STD_OFF

/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                     STD_OFF

#define PROG_AUTHENTICATED_BOOT_ENABLE                  STD_OFF
#define PROG_BOOT_VERIFICATION                          STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION           STD_OFF
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION          STD_OFF

#define PROG_SLEEP_MANAGEMENT_TYPE                      [!WS "22"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
#define PROG_ERASE_ALL                                  STD_OFF
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                              ([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]

#define PROG_BOOT_REPROG                                1U
#define PROG_BOOT_NOREPROG                              0U

extern const u8 m_aCfgPSIProgrammedValue[PROG_PSI_VAL_SIZE];
extern const u8 m_aCfgPSIRevokedValue[PROG_PSI_VAL_SIZE];
extern const tBootInfoBlock m_stBootInfoBlock;

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                    STD_OFF

/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE              STD_OFF
/*Security access antiscanning*/
#define PROG_ANTISCANNING_ENABLED                       STD_OFF

/*Enable the response after reset in function of reset cause*/
#define PROG_RESET_CAUSE_ENABLE                         [!WS "28"!][!IF "General/Transmit_Response_Before_Reset = 'false'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Programming pre-conditions check */
#define PROG_PRECOND_CHECK_ENABLE                       STD_OFF
/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                     STD_OFF

/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                    STD_OFF

/* Use partial checksum verification */
#define PROG_PARTIAL_VERIFY_CRC                         STD_OFF

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                         STD_OFF

/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE             STD_OFF

/* Downloading Pseudo Flash driver feature activation */
#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_ENABLE      STD_OFF

#define PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_OFF

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                     STD_OFF

#define PROG_DECOMP_FLASH_ROUTINES                      STD_OFF

/* Security access limit request seed */
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_OFF

/*Securiy access request seed delay timer*/
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED           STD_OFF

[!ENDIF!]
/*Introduced below the compiler switch to support Fingerprint for the Segments in RAM*/
#ifndef PROG_RAMSEG_FINGERPRINT_SUPPORT
#define PROG_RAMSEG_FINGERPRINT_SUPPORT                 STD_OFF
#endif

#define PROG_CSM_HASH_USED                              STD_OFF
#define PROG_CSM_MAC_USED                               STD_OFF

#endif /* PROG_CFG_IMPL20_H */
