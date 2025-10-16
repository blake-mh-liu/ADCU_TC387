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
/*%%   _____________________________   %%  \file PROG_Types.h                    */
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
#ifndef PROG_TYPES_H
#define PROG_TYPES_H
#include<ComStack_Cfg.h>

#include <Std_Types.h>          /* AUTOSAR standard types */
[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
#include "fblFrameworkPublicApi.h"
[!ENDIF!]
 [!IF "node:exists(as:modconf('ProgJLR'))"!]
 [!IF "node:exists(as:modconf('Cry'))"!]
#include "Cry_SHA_Common.h"
  [!ENDIF!]
   [!ENDIF!]
[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "NBR_PROT_CAL"="0"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
    [!VAR "NBR_PROT_CAL" = "num:dectoint($NBR_PROT_CAL) + 1"!]
[!ENDIF!]
[!ENDFOR!]


[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_RAM" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM" = "0"!]
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
    [!ELSEIF "$Memory_Type = 'RAM'"!]
        [!IF "not(node:exists(as:modconf('ReProgMemM')))"!]
         [!VAR "MEMORY_MODE_RAM" = "node:ref(Memory)/Memory_Mode"!]
		[!ENDIF!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_RAM"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_RAM > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_RAM"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'CUSTOM'"!]
    [!IF "(node:exists(as:modconf('Flash')))"!]
        [!VAR "MEMORY_MODE_CUSTOM_MEM" = "node:ref(Memory)/Memory_Mode"!]
    [!ENDIF!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
[!IF "node:exists(as:modconf('CryIf'))"!]
/* Below are the Csm ASR v4.3 depreciated typedefs that are needed for the PROG module */
typedef u8 Csm_ReturnType;
typedef u8 Csm_VerifyResultType;
[!ENDIF!]
#define PROG_MIN_VAL_TO_WRITE            [!"$MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]U
[!IF "(node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgPSA')) or ((node:exists(as:modconf('ProgFCA'))) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')))"!]
[!VAR "BLOCK_IDX"="1"!]
[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
[!VAR "MAX_IDX"="0"!]
[!VAR "BLOCK_ID_FOUND"="0"!]
[!VAR "BLOCK_IDENTIFIER_VALUE"="0"!]

[!FOR "BLOCK_IDENTIFIER_VALUE" = "0" TO "65534"!]
[!VAR "BLOCK_ID_FOUND"="0"!]
[!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
[!IF "$BLOCK_IDENTIFIER_VALUE = num:hextoint(Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
    [!VAR "BLOCK_ID_FOUND" = "1"!]
    [!BREAK!]
[!ENDIF!]

[!ENDFOR!]

[!IF "($BLOCK_ID_FOUND = 0)"!]
[!BREAK!]
[!ENDIF!]

[!ENDFOR!]
 
/* Block Identifier */
#define PROG_LOGICAL_BLOCK_VALUE_INIT    [!"$BLOCK_MAX"!]  
[!ENDIF!]
/* PROG boolean type */
#define PROG_FALSE                       0U
#define PROG_TRUE                        1U
typedef u8 tProgBoolean;

typedef u8 tProgStatus;
#define PROG_E_OK                        0x00U
#define PROG_E_NOT_OK                    0x01U
#define PROG_E_BUSY                      0x02U
#define PROG_E_CHECK_FAILED              0x03U
#define PROG_E_BYPASS                    0x04U
[!IF "node:exists(as:modconf('ProgVAG')) and (VAG/Downgrade_Protection = 'true')"!]
#define PROG_E_RFS_DRIVER_FAIL           0x05U
#define PROG_E_RFS_VERSION_FAIL          0x06U
[!ENDIF!]
#define PROG_E_NOT_BUSY                  0x80U
#define PROG_E_TXCONF_OK                 0x40U

typedef u8 tProgResCause;
#define PROG_RESET_CAUSE_ER              0x00U
#define PROG_RESET_CAUSE_DSC01           0x01U
#define PROG_RESET_CAUSE_DSC02           0x02U
#define PROG_RESET_CAUSE_S3_TIMEOUT      0x03U
#define PROG_RESET_CAUSE_SBLACTIVEFAIL   0x04U
#define PROG_RESET_CAUSE_BLU             0x05U
typedef u8  tProgMemType;
#define PROG_MEM_TYPE_INIT               0xFFU
#define PROG_MEM_TYPE_FLASH              0x00U
#define PROG_MEM_TYPE_EEPROM             0x01U
#define PROG_MEM_TYPE_RAM                0x02U
#define PROG_MEM_TYPE_SCRATCHPAD         0x03U
#define PROG_MEM_TYPE_FLASH_EXT          0x04U
#define PROG_MEM_TYPE_CUSTOM             0x05U
typedef u8  tProgMemIdx;
typedef u8  tProgMemMode;
#define PROG_MEMORY_SYNCHRONOUS          0x01U
#define PROG_MEMORY_ASYNCHRONOUS         0x02U
#define PROG_MEMORY_NOTUSED              0x03U

typedef u8 tProgAccessType;
#define PROG_MEM_ACCESS_TYPE_NONE        0x00U
#define PROG_MEM_ACCESS_TYPE_READ        0x01U
#define PROG_MEM_ACCESS_TYPE_WRITE       0x02U
#define PROG_MEM_ACCESS_TYPE_READ_WRITE  0x03U

typedef u32 tDataLength;
/* basic data is byte */

typedef u8 tDataBufferType;

typedef u32 tProgAddressType;

typedef u8 tOperationType;
#define PROG_MEM_OPERATION_TYPE_ERASE    0x01U
#define PROG_MEM_OPERATION_TYPE_WRITE    0x02U
#define PROG_MEM_OPERATION_TYPE_READ     0x03U

typedef u8 tProgCompTimeoutStatus;
#define PROG_COMPLETECOMPATIBLE_START    0x01U
#define PROG_COMPLETECOMPATIBLE_END      0x02U
#define PROG_COMPLETECOMPATIBLE_ERROR    0x03U

typedef u8 tProgPartitionType;
#define PROG_APPLICATION_PARTITION       0x01U
#define PROG_CALIBRATION_PARTITION       0x02U
#define PROG_PROT_CALIBRATION_PARTITION  0x03U
#define PROG_SBA_PARTITION               0x04U
#define PROG_BOOTLOADER_PARTITION        0x05U
#define PROG_FLASH_ROUTINES_PARTITION    0x06U
#define PROG_ESS_PARTITION               0x07U
#define PROG_HSM_PARTITION               0x08U
#define PROG_BLU_PARTITION               0x10U
#define PROG_BLU_APP_PARTITION           0x11U
#define PROG_BLU_CAL_PARTITION           0x12U
#define PROG_PSEUDO_FLASH_ROUTINES_PARTITION    0x13U
/* mask to combine all partitions which support BLU */
#define PROG_BLU_PARTITION_MASK          0x10U

typedef u8 tProgDownloadType;
#define PROG_DOWNLOAD_BY_ADDR            0x01U
#define PROG_DOWNLOAD_BY_LOGICAL_BLOCK   0x02U
#define PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT   0x03U

#define PROG_NO_REPROG_TYPE              0U
#define PROG_STANDARD_REPROG             1U
#define PROG_AUTHENTICATED_REPROG        2U

/* Size of the maximum length of the answer to Check Memory request */
/* between the Implementation 40,50 and 60 */
#define PROG_MAX_LENGTH_CHECKMEMORY_ANSWER  6U

#define PROG_RC_WITH_RI_LENGTH              4U


[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "GM/PEC_Enable = 'true'"!]
typedef u16 tProgPECError;
#define PROG_PEC_NO_ERROR                 0x0000U
#define PROG_ERR_PARTITION_ID             0x0001U
#define PROG_ERR_SW_NOT_PRESENT           0x0002U
#define PROG_ERR_REVOKE_SW                0x0003U
#define PROG_ERR_ERASE_SW                 0x0004U
#define PROG_ERR_GET_APP_INFO             0x0005U
#define PROG_ERR_REVOKE_CAL               0x0006U
#define PROG_ERR_ERASE_CAL                0x0007U
#define PROG_ERR_GET_CAL_INFO             0x0008U
#define PROG_ERR_UPDATE_PSI               0x0009U
#define PROG_ERR_DATA_TYPE                0x000AU
#define PROG_ERR_COMPRESSION              0x000BU
#define PROG_ERR_LENGTH_EXCEEDED          0x000CU
#define PROG_ERR_MORE_DATA_EXPECTED       0x000DU
#define PROG_ERR_FLASH_WRITE              0x000EU
#define PROG_ERR_MODULE_ID                0x000FU
#define PROG_ERR_BCID                     0x0010U
#define PROG_ERR_CCID                     0x0011U
#define PROG_ERR_ECU_NAME                 0x0012U
#define PROG_ERR_ECU_ID                   0x0013U
#define PROG_ERR_SW_REGION                0x0014U
#define PROG_ERR_SIGNATURE                0x0015U
#define PROG_ERR_APP_NBID                 0x0016U
#define PROG_ERR_SUBJECT_NAME             0x0017U
#define PROG_ERR_KEY_NBID                 0x0018U
#define PROG_ERR_CERT                     0x0019U
#define PROG_ERR_CAL_REGION               0x001AU
#define PROG_ERR_MD                       0x001BU
#define PROG_ERR_ROOT_SIGNATURE           0x001CU
#define PROG_ERR_MSG_OUT_OF_SEQUENCE      0x001DU
#define PROG_ERR_UNDEFINED                0x0020U
#define PROG_ERR_PROTECTEDCAL_NOT_DEFINED 0x0035U
#define PROG_ERR_PER_DATA_TX_NOT_ALLOW    0x0037U

[!ENDIF!]

typedef u8 tProgSigBypass;
#define PROG_ERR_SBA_ECU_NAME            0x01U
#define PROG_ERR_SBA_ECU_ID              0x02U
#define PROG_ERR_SBA_SIGNATURE           0x04U
#define PROG_ERR_SBA_CERT                0x08U
#define PROG_SBA_OK                      0x80U

typedef u8 tProgPsiValue;
#define PROG_PSI_PROGRAMMED              0x00U
#define PROG_PSI_REVOKED                 0x01U
#define PROG_PSI_INVALID                 0x02U

#define PROG_ECU_ID_SIZE                 16U
#define PROG_ECU_NAME_SIZE               8U
#define PROG_SUBJECT_NAME_SIZE           16U
#define PROG_BOOT_NB_MODULE_SIZE         1U
#define PROG_BOOT_MODULE_ID_SIZE         1U
#define PROG_BOOT_PART_NUMBER_SIZE       4U
#define PROG_BOOT_DLS_SIZE               2U
#define PROG_BOOT_PROT_CALIB_NUMBER_SIZE        1U
#define PROG_BOOT_PROT_CALIB_PARTITION_ID_SIZE  1U
#define PROG_BOOT_MAX_PROT_PARTITIONS           [!"num:dectoint($NBR_PROT_CAL)"!]U
#define PROG_BOOT_PRIMARY_MICRO_ID       0x47U
#define PROG_BOOT_NUMBER_OF_MODULES      0x01U
#define PROG_MAX_PARTITION               [!"num:dectoint(GM/MAX_PARTITION)"!]U
#define PROG_MAX_REGION_ALLOWED          [!"num:dectoint(GM/MAX_REGION_ALLOWED)"!]U
[!ENDIF!]

[!IF "(as:modconf('ProgVAG')) or (as:modconf('ProgOEMInd')) and (as:modconf('Prog')/Decryption/Enable_Csm_Decryption='true')"!]
#define PROG_CIPHERED_MIN_DATA_SIZE        256
#define PROG_DECRYPT_BUFFER_SIZE           4112U

typedef u8 tProgEncryptOperation;
#define PROG_NO_OPERATION_IN_PROGRESS      0x00U
#define PROG_DECRYPTION_IN_PROGRESS        0xAAU

typedef struct
{
  u8  aubCryptoBuffer[PROG_DECRYPT_BUFFER_SIZE];          /* Contains the decrpted data */
  u32 ulNextWritePosition;                                /* Position from where next writing shall be start */
  u32 ulCryptoBufferSize;                                 /* Size of decrypted data */
  u32 ulEncryptDataSize;                                  /* Size of data to be decrypted */
  u32 ulTotDecryptedWrittenSize;                          /* Stores the total length of decrypted and written data */
  u16 uwRemainNotWrittenLength;                           /* Stores the length of decrypted but not written data */
  tProgEncryptOperation  ubOperationInProgress;           /* Defines operation in progress: encryption, decryption or none of them */
}tCryptoData;
[!ENDIF!]
[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL' or as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'
    or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'"!]
typedef struct s_secondary_bootloader_interface
{
    u32 software_version;          /* meta data */
    u8  referenceString[16];       /* reference string of the SBL */
    void *ptr_function[25];        /* function pointer list */
    u32 ulSBLValidityFlagAddr;     /* SBL validity flag address */
}t_secondary_bootloader_interface;
[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL' or as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'"!]
#define PROG_DIGEST_LENGTH     32U    /* digest length for VCC and FORD */
 typedef struct
 {
    u32 ulStartAddress;          /* start address of the hashed data */
    u32 ulLength;       /* length of the hashed data */
    u8  aubDigest[PROG_DIGEST_LENGTH];        /* function pointer list */
 }tDataBlockType;
 [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
[!IF "(as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
 [!IF "node:exists(as:modconf('Csm'))"!]
 [!IF "node:exists(as:modconf('CryIf'))"!]
  [!VAR "DigestLength" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId)/CsmJobPrimitiveRef)/CsmHash/*/CsmHashResultLength)"!]
/* Digest Length shall be configured based on the value provided in the Csm job conf paramater- CsmHashResultLength */
#define PROG_DIGEST_LENGTH                                 [!WS "31"!][!"$DigestLength"!]U
 [!ELSE!]
   [!VAR "AlgoType" 	= "(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId)/CsmHashPrimitiveName)"!]
#ifndef CRY_[!"$AlgoType"!]_WORD_SIZE
#define CRY_[!"$AlgoType"!]_WORD_SIZE                      [!WS "9"!]32U
#endif
#define PROG_DIGEST_LENGTH                               CRY_[!"$AlgoType"!]_WORD_SIZE
 [!ENDIF!]
 [!ENDIF!]
  [!ENDIF!]
#ifndef PROG_DIGEST_LENGTH
#define PROG_DIGEST_LENGTH                                   32U
#endif
 typedef struct
 {
    u8  aubDigest[PROG_DIGEST_LENGTH];        /* function pointer list */
 }tDataBlockType;
 [!ENDIF!]

typedef u32 tProgCompleteStatus;
[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL_WITH_EB_FRAMEWORK'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
	or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL'"!]

	[!IF "node:exists(as:modconf('EB')) and (as:modconf('EB')/Communication/EnableMultipleTpConnection='true')"!]
typedef void (*ptSBL_StartUp_Code)(u32 ulInfoSBL, u8 ubRxPduId);
    [!ELSE!]
typedef void (*ptSBL_StartUp_Code)(u32 ulInfoSBL);
    [!ENDIF!]
typedef void (*ptAPPL_START_ADDR)(void);
[!ELSEIF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT=''or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'"!]
 typedef void (*ptAPPL_START_ADDR)(void);
[!ENDIF!]
typedef tProgCompleteStatus (*ptCompleteCompatibleCallOut)(void);

[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL_WITH_EB_FRAMEWORK' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
/* Function pointer type definition for ZF framework */
typedef u8 (*tpulVerifySectionCrc)(void);
typedef u8 (*tpulinvalidateSection)(u32);
typedef u8 (*tpulisValidApplication)(void);
typedef void* (*tpulGetAddress)(u8,u32);
[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
/* Function pointer for skipPage Api */
typedef u8 (*tpulskipPage)(u32*);
[!ENDIF!]
[!ENDIF!]

/* Type of algorithm used for programming verification */
typedef u8 tProgVerifAlgo;
#define PROG_VERIFY_CRC         0x00U
#define PROG_VERIFY_SIGNATURE   0x01U
#define PROG_VERIFY_HASH        0x02U

typedef struct
{
    u32 ulAdd; /*Address to read data*/
    u32 ulCnt; /*Number of data get to compute CRC */
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or OemInd/Checksum_Algo='CRC32 Ethernet' or OemInd/Checksum_Algo='CRC32 InternationalStandard'"!]
    u32 ulVal; /* CRC32 value */
[!ELSE!]
    u16 uwVal; /* CRC16 value */
[!ENDIF!]
    tProgVerifAlgo ubAlgo;
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))  or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'LogicalBlock') or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'All')"!]
    u8  ubLogicalBlockId;
[!ENDIF!]
}tProgVerificationInfo;

[!IF "node:exists(as:modconf('ProgGM'))"!]
typedef struct
{
    u32 ulAddress;
    u32 ulSize;
}tRegiontype;
[!ENDIF!]

typedef struct
{
    u32  ulStartAddress;   /*Start address of the segment*/
    u32  ulSize;           /*Size of the segment */
[!IF "node:exists(as:modconf('ProgGM'))"!]
    tRegiontype astRegion[PROG_MAX_REGION_ALLOWED];
    u8   *pubRegionPtr;    /*Pointer to the current region*/
    u16  uwModuleId;       /* Current downloaded module ID */
    u8   ubRegionNbr;
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
 or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC'))
    or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'All')
    or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'LogicalBlock')
    or (node:exists(as:modconf('ProgPSA')))"!]
    u8  ubLogicalSegmentId;    /*Identifier for the logical segment*/
    u8  ubLogicalBlockId;      /*Identifier for the logical block*/
[!ENDIF!]
    u8   ubSegmentId;      /*Identifier of the segment in segment configuration array */
    u8   ubSegmentNbr;     /*Remaining number of segment in the current block*/
}tSegmentType;

[!IF "(node:exists(as:modconf('ReProgMemM')))"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(as:modconf('ReProgMemM')/MemoryConfig/Memory/*))"!]
[!ELSEIF "node:exists(as:modconf('Flash')) or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (node:exists(as:modconf('ProgVCC')) and as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
[!ENDIF!]
#define PROG_MEMORY_NB [!"$MEMORY_MAX"!]U
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgOEMInd'))"!]
#define PROG_SEGMENT_NB [!"$SEGMENT_MAX"!]U
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgOEMInd'))
    or (node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') and (as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Standard'))"!]

#define PROG_MAX_RD_PER_BLOCK   [!"num:dectoint(DownloadVerification/MaxNumberOfRDPerBlock)"!]U
typedef struct
{
    u8 ubSegNbr;
    tSegmentType astSeg[PROG_MAX_RD_PER_BLOCK];
    u8 ubSegListCrcIndex;
}tSegmentListType;
[!ENDIF!]
 [!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
 [!IF "node:exists(as:modconf('ProgJLR')) or (node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid'))"!]
  [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
  [!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]
   [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
   [!VAR "SEGMENT_IDX"="$SEGMENT_MAX"!]
  [!ENDIF!]
  [!ENDFOR!]
  [!ENDIF!]
typedef struct
{
    tProgAddressType         ulStartAddress;
    tProgAddressType         ulEndAddress;
    tProgAddressType         ulEraseStartAddress;
    tProgAddressType         ulEraseEndAddress;
    tProgMemIdx              ubMemoryIdx;
    tProgAccessType          eSegAccessType;
[!IF "node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord'))"!]
    tProgPartitionType       ePartitionType;
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgOEMInd'))) or (node:exists(as:modconf('ProgJLR')) and ((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or
      (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')))"!]
    tProgBoolean            eValidityCheck;
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'Address') or node:exists(as:modconf('ProgPSA'))"!]
    u8                       ubBlockIndex;
[!ENDIF!]
 [!IF "((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')) or ((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid') and ($SIGNATUREVERIFCATIONENABLED = 'true')) "!]
    tProgBoolean             eVerifySignature;
 [!ENDIF!]
  [!IF "((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')) "!]
    u8             ubBlockIndentifier;
 [!ENDIF!]
   [!IF "((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')) "!]
    u8             ubStartSegment;
 [!ENDIF!]
}tCfgSegmentType;

typedef struct
{
    tProgMemType             eMemoryType;
[!IF "node:exists(as:modconf('Flash'))  or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (node:exists(as:modconf('ProgVCC')) and as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
    tProgMemMode             eMemoryMode;
[!ENDIF!]
    u32                      ulMinValueToWrite;
    tProgAddressType         ulAddressOffset;
    u8                       ubEraseValue;
}tCfgMemorytType;

typedef struct
{
    u16 uwBlockIdentifier;
    u8 ubFirstSegmentId;
    u8 ubSegmentNbr;
    u16 uwProgCntrMax;
[!IF "node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') and (as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Standard')"!]
    tProgAddressType ulCrcAddress;
[!ENDIF!]
[!IF "((node:exists(as:modconf('ProgVAG')))and (as:modconf('Prog')/VAG/Downgrade_Protection = 'true'))"!]
    u8 ubDwngrdProtected;
[!ENDIF!]
}tProg_Block;

[!IF "(not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) and
    (node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgJLR'))  or node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgOEMInd')))"!]
typedef struct
{
    u32 ulStartAddressForSecureBoot;
    u32 ulLengthForSecureBoot;
    u16 uwBlockIdentifier;
    u8  ubBlockVerifiedInSecure;
    u8  ubBlockBlockerExecution;
}tProg_BlockSecureBootInfo;
[!ENDIF!]

typedef struct
{
    u8 * pubData;    /* Pointer to Tp buffer use for reception*/
    u8 * pubTxData;  /* Pointer to Tp buffer use for transmission*/
    PduLengthType ulLength;    /* Length of request/response */
    u8 ubDiagStatus; /* Status of the request management */
}tDiagMessageInfo;

typedef struct
{
    u8 aubData[PROG_MAX_LENGTH_CHECKMEMORY_ANSWER];    /* Contains data of the answer */
    PduLengthType ulLength;    /* Length of request/response */
    u8 ubDiagStatus; /* Status of the request management */
}tFirstCheckMemoryAnswerInfo;

typedef struct
{
    u32 ulMemorySizeExpected;
    u32 ulReceivedSizeOfData; /* Number of data received and written */
[!IF "General/Enable_Compression = 'true'"!]
    u32 ulTotalDecompDataWrite;
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
    u16 uwExpectedModuleId[PROG_MAX_PARTITION];
[!ENDIF!]
    u8 ubBlockSequenceCounter;
    u8 ubRDReceived;
[!IF "General/Enable_Compression = 'true'"!]
    u8 ubCompRequired;
[!ENDIF!]
}tReprogInfo;

[!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]
typedef struct
{
    u32 ulBufferedSizeOfData;
    u8 eResponsePending;
    u8 eBufferProcessing;
}tMultipleBuffReprogInfo;
[!ENDIF!]

typedef struct
{
[!IF "General/Enable_Compression = 'true'"!]
    u8 * pubDecompData; /*Pointer to buffer in COMP containing data to write*/
[!ENDIF!]
    u32 ulAddressToWrite;
    u32 ulDataToBeWritten; /* Total number of data received */
    u32 ulWrittenData; /* Total number of data written */
    u32 ulWriteLength; /* Number of data written at last write */
[!IF "General/Enable_Compression = 'true'"!]
    u32 ulInDecompDataLength;
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgPSA'))"!]
    u32 ulNewAddressToWrite;
[!ENDIF!]
    u8 ubTDReceived;
}tWriteInfo;


typedef struct
{
    u32 ulStartAddress;
    u32 ulMemorySize;
    u16 uwBlockIdentifier;
    u8  ubSegmentId;
    u8  ubDataFormatId;
}tRDParam;

typedef P2FUNC (void*, EBSTUBS_APPL_CODE, t_PROG_fctptr)(void) ;

typedef struct
{
    u8 aubData[PROG_MIN_VAL_TO_WRITE];
    PduLengthType ulOldDataLength;
    PduLengthType ulNewDataLength;
}tPageBuffer;

[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "SEGMENT_IDX"="1"!]
[!VAR "PROT_CALIB_IDX"="1"!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
typedef struct
{
    u16 uwBCID;
[!IF "GM/EcuId_Source = 'Tresos_Configuration'"!]
    u8  aubEcuId[PROG_ECU_ID_SIZE];
[!ENDIF!]
    u8  aubEcuName[PROG_ECU_NAME_SIZE];
    u8  aubSubjectName[PROG_SUBJECT_NAME_SIZE];
    u8  aubBootPartNumber[PROG_BOOT_PART_NUMBER_SIZE];
    u8  aubBootDLS[PROG_BOOT_DLS_SIZE];
    u8  aubProtectedCalibNumber;
[!IF "$NBR_PROT_CAL > 0"!]
    u8  aubProtectedCalibPartitionID[PROG_BOOT_MAX_PROT_PARTITIONS];
[!ENDIF!]
}tBootInfoBlock;

typedef struct
{
    u8 ubBootIntegrity;
    tProgSigBypass ubSignatureBypass;
}tBootStatus;
[!ENDIF!]

typedef u8 tProgEraseCheckType;
#define PROG_DISABLED_ERASE_CHECK        0x00U
#define PROG_1ST_PROGRAMMING_ERASE_CHECK 0x01U
#define PROG_BLOCK_ERASE_CHECK           0x02U


typedef u8 tProgEraseStatus;
#define PROG_E_NOT_ERASED        0x00U
#define PROG_E_ERASED            0x01U



typedef struct
{
    u8 ubAppFingerprintWriten; /*Application Fingerprint writing success flag*/
    u8 ubCalFingerprintWriten; /*Calibration Fingerprint writing success flag*/
    u8 ubBluFingerprintWriten; /*Blupdater Fingerprint writing success flag*/
}tWfSuccess;

typedef u8 tProgCohChkResult;
#define PROG_E_COHCHK_CORRECT             0x00U
#define PROG_E_COHCHK_INCORRECT           0x01U
#define PROG_E_COHCHK_INCORRECT_SW_HW     0x02U
#define PROG_E_COHCHK_INCORRECT_SW_SW     0x03U
#define PROG_E_COHCHK_INCORRECT_OTHER     0x04U

[!IF "node:exists(as:modconf('Uds'))"!]
[!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
typedef u8 tProgCohPreChkResult;
#define PROG_E_COHPRECHK_CORRECT          0x00U
#define PROG_E_COHPRECHK_INTERNAL_ERROR   0x01U
#define PROG_E_COHPRECHK_INCORRECT_HW_SW  0x02U
#define PROG_E_COHPRECHK_INCORRECT_SW_SW  0x03U
    [!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]
typedef struct
{
    PduLengthType Length;    /* Length of request */
    u8 * Data;    /* Pointer to Tp buffer use for reception*/
    u8 Event;  /* Stored event */
}tEventInfo;
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgFCA')))"!]
typedef u8 tSignatureHandlingstatus;

#define PROG_CRCDONE                     0U
#define PROG_CRYPTOSTARTUPDATEINPROGRESS 1U
#define PROG_CRYPTOUPDATEDONE            2U
#define PROG_CRYPTOFINISHDONE            3U
#define PROG_ERASESTART                  4U
#define PROG_ERASEDONE                   5U
[!ENDIF!]

[!IF "as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_APP_PARTITION' 
   or as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_CAL_PARTITION'
   or as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_PARTITION'"!]
typedef struct
{
    u8 aubData[PROG_RC_WITH_RI_LENGTH];    /* Contains received data of the request */
    PduLengthType ulLength;    /* Length of request */
}tCheckMemoryRequestInfo;
/* Struct containing required informations to resume BLU download after ECU Reset */
typedef struct
{
    u8 ubProgSecurityLevel;                 /* Current security level */
    tCheckMemoryRequestInfo stBLUCheckMemoryRequestInfo;    /* Contains BLU Check Memory request information */
}tContextRestore;
[!ENDIF!]

 [!IF "node:exists(as:modconf('ProgJLR'))"!]
[!IF "(as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or
      (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')"!]
 [!IF "node:exists(as:modconf('Csm'))"!]
 [!IF "node:exists(as:modconf('CryIf'))"!]
  [!VAR "DigestLength" = "(as:ref(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId)/CsmJobPrimitiveRef)/CsmHash/*/CsmHashResultLength)"!]
/* Digest Length shall be configured based on the value provided in the Csm job conf paramater- CsmHashResultLength */
#define PROG_DIGEST_LENGTH                                 [!WS "31"!][!"$DigestLength"!]U
 [!ELSE!]
   [!VAR "AlgoType" 	= "(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId)/CsmHashPrimitiveName)"!]
#ifndef CRY_[!"$AlgoType"!]_WORD_SIZE
#define CRY_[!"$AlgoType"!]_WORD_SIZE                      [!WS "9"!]64U
#endif
#define PROG_DIGEST_LENGTH                               CRY_[!"$AlgoType"!]_WORD_SIZE
 [!ENDIF!]
 [!ENDIF!]
  [!ENDIF!]
#ifndef PROG_DIGEST_LENGTH
#define PROG_DIGEST_LENGTH                                   64U
#endif

#ifndef PROG_VDS_SIZE
#define PROG_VDS_SIZE                                        (PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN + PROG_DIGEST_LENGTH)
#endif
 typedef struct
 {
     u32 ulBlock_StartAddress;
 	 u32 ulBlock_Length;
     u8 aubBlockDigest[PROG_DIGEST_LENGTH];
 }tVDSlayout;
 [!ENDIF!]
[!IF "node:exists(as:modconf('ProgPSA'))"!]
typedef struct
{
    u8 ubSeedSent;[!WS "11"!]/* Indicates the right catenation of diagnostic requests needed for ECU unlocking */
    u8 ubEcuUnlock;[!WS "10"!]/* Deny or allow the handling of the programming requests (clearing and writing) */
    u8 ubTunBlank;[!WS "11"!]/* Identifies if calibration zone has been erased or not */
    u8 ubGlobalBlank;[!WS "8"!]/* Identifies if global (calibration + application) zone has been erased or not */
    u8 ubProgInit;[!WS "11"!]/* Identifies the start of the ECU reprogramming */
    u8 ubAuthorizeLog;[!WS "7"!]/* Forbid or allow the log zone writing */
    u8 ubWriteOk;[!WS "12"!]/* Identifies writing fault */
    u8 ubRDOk;[!WS "15"!]/* Indicates the right catenation of requests needed for APPLI+CALIB or CALIB writing */
    u8 ubRDLogOk;[!WS "12"!]/* Indicates the right catenation of the diagnostic requests needed for log zone writing */
    u8 ubRDKeyAppliOk;[!WS "7"!]/* Indicates the right catenation of diagnostic requests needed for APPLI_KEY writing */
    u8 ubLCBaudOk;[!WS "11"!]/* Indicates the right catenation of the diagnostic requests needed for speed modification */
    u8 ubLCProgOk;[!WS "11"!]/* Indicates the right catenation of the diagnostic requests needed for programming scheduler switching */
}tProgrammingFlags;

typedef struct
{
    u16 uwRoutineId;
    u8  ubRoutineIndexList;
}tProgRoutineResultInfo;

typedef struct
{
    u8  aubRoutineData[20U];     /* Buffer used to store received RC buffer */
    u16 uwRoutineLength;         /* Length of the RC */
}tProgRequestRoutineData;

typedef u8 tProgRequestRoutineResult;
#define PROG_REQUEST_ROUTINE_RESULT_INIT        0x00
#define PROG_REQUEST_ROUTINE_RESULT_PENDING     0x01
#define PROG_REQUEST_ROUTINE_RESULT_SUCCESS     0x02
#define PROG_REQUEST_ROUTINE_RESULT_FAIL        0x03

[!ENDIF!]
typedef void (*tProgCsmNotification)(u8 eCsmStatus);
[!IF "node:exists(as:modconf('CryIf'))"!]
typedef struct
 {
	  u32 ulBSsize; /* Size of the Data Block Slicing */
	  u32 ulCsmJobId; /* Corresponding Csm Job ID */
	  tProgCsmNotification pfuProgCsmNotification; /* Callback handling API for the configured Algo */
	  u32 ulCsmKeyID; /* KeyID assigned by Crypto Driver */
	  u32 ulCryptoElementId; /* KeyElementID assigned by the Crypto Driver */
	  u32 ulCryptoKeyLength; /* KeyLength stored in the Crypto Driver */
	  tProgBoolean eAllowJobCancellation; /* Cancel all ongoing Csm Jobs */
	  tProgBoolean eAllowKeySet; /* Enable to set the key and the keystatus in the Crypto driver */
	  tProgBoolean eAllowCustCsmPreProc; /* TRUE if the Custom Preprocessing before the CsmStart is expected (eg.: DER Key encoding )*/
 }tProgCsmJobConf;
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
 [!IF "(as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
/* Routine Data Index Macro's and Length of the routine Info */

/* Key Size */
#define PROG_DEVPUBLICKEY_SIZE                           [!"num:inttohex(SwitchingKeyRoutineData/SwitchingKey_DevPublic_Key_Size)"!]U
#define PROG_PRODPUBLICKEY_SIZE                          [!"num:inttohex(SwitchingKeyRoutineData/SwitchingKey_ProdPublic_Key_Size)"!]U
#define PROG_TOKENPUBLICKEY_SIZE                         [!"num:inttohex(SwitchingKeyRoutineData/SwitchingKey_TokenPublic_Key_Size)"!]U

/* Routine Min and Max Lenght Parameters */
#define PROG_SWITCHINGKEY_RC_MINLEN                      [!"num:inttohex(SwitchingKeyRoutineData/SwitchingKey_Routine_Min_Length)"!]U
#define PROG_SWITCHINGKEY_RC_MAXLEN                      [!"num:inttohex(SwitchingKeyRoutineData/SwitchingKey_Routine_Max_Length)"!]U

#define PROG_SWITCHINGKEY_HEADER_SIZE                    37U
#define PROG_SWITCHINGKEY_PAYLOAD_FESN                   3U
#define PROG_SWITCHINGKEY_PAYLOAD_NEWPARTNUM             24U

/* NameLen - 1, Token Name - 4, Expiration Date - 6, Session ID - 25, FESN Prefix - 3, New Part Number - 5 and keys - 3*512*/
#define PROG_SWITCHINGKEY_PAYLOAD_WITHOUTUPDATEKEYS      36U
#define PROG_SWITCHINGKEY_PAYLOAD_WITHUPDATEKEYS         (u16)((PROG_DEVPUBLICKEY_SIZE + PROG_PRODPUBLICKEY_SIZE + PROG_TOKENPUBLICKEY_SIZE) + PROG_SWITCHINGKEY_PAYLOAD_WITHOUTUPDATEKEYS + PROG_SWITCHINGKEY_PAYLOAD_FESN + PROG_SWITCHINGKEY_PAYLOAD_NEWPARTNUM)
 
/* Switching Key Modes */
#define PROG_SWITCH_TO_PRODUCTION_KEY                         0U
#define PROG_SWITCH_DEVELOPMENT_KEY_UNTILL_COMMANDED_EXIT     1U
#define PROG_SWITCH_DEVELOPMENT_KEY_TEMP                      2U
#define PROG_SWITCH_DEVELOPMENT_KEY_UNTILL_DATE               3U
#define PROG_SWITCH_DEVELOPMENT_KEY_UNTILL_N_IGN              4U
#define PROG_UPDATE_PUBLIC_KEYS                               5U

/* Key inedx for signature verification */
#define PROG_USE_SECRET_KEY_SIGN                              0U
#define PROG_USE_TOKEN_KEY_SIGN                               1U

/* Rotuine Status Codes */
#define PROG_SWITCHINGKEY_TOKEN_APPLIED                           0U
#define PROG_SWITCHINGKEY_WRONG_TOKEN_VER                         1U
#define PROG_SWITCHINGKEY_SYNCHP_DOESNOT_MATCH                    2U
#define PROG_SWITCHINGKEY_FESN_DOESNOT_MATCH                      3U
#define PROG_SWITCHINGKEY_MODULE_NOT_SUPPORT_TIMEBASED_TOKEN      4U
#define PROG_SWITCHINGKEY_KEYCHNGD_MANYTIMES_REFLASH              5U
#define PROG_SWITCHINGKEY_WRONG_SIGNATURE                         6U
#define PROG_SWITCHINGKEY_TOKN_OK_PASSED_APPL                     7U
#define PROG_SWITCHINGKEY_WRONG_PAYLOAD_SIGNATURE_ROTATION_ONLY   8U
#define PROG_SWITCHINGKEY_TOKN_OK_MODULE_ERROR                    9U
#define PROG_UPDATESWITCHINGKEY_STAT_UNKNOWN                      0xFFU


typedef struct
{
    u8 ubMsgStat;/* Stores the Message status from request */
    u8 ubDevPublicKey[PROG_DEVPUBLICKEY_SIZE];/* stores the Dev key from request */
    u8 ubProdPublicKey[PROG_PRODPUBLICKEY_SIZE];/* stores the Prod key from request */
    u8 ubTokenPublicKey[PROG_TOKENPUBLICKEY_SIZE];/* stores the token jey from request */
    u8 RoutineResult;/* stores the routine result */
    u8 ubKeyIndex;/* stores the key index from the request */
}tstUpdateSwitchKeyDataType;

 [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
 [!IF "(as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
 
 /* Size of RDID whic stores the complete valid request */
#define PROG_SWITCHING_SIZEOF_D071_RDID                            2134U
 
 extern u8 aubSwitchRoutineCmpltReq[PROG_SWITCHING_SIZEOF_D071_RDID];
 
/* Macro's to access key types */
#define PROG_USE_DEVPUB_KEY                                        0U
#define PROG_USE_PRODPUB_KEY                                       1U

 [!ENDIF!]
[!ENDIF!] 

#endif /* PROG_TYPES_H */
