/*********************************************************************************/
/*                                                                               */
/*                                  BOOT Layers                                  */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 PROG configuration                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cfg.c                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
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
#include "EB_Prj.h"
[!AUTOSPACING!]

[!NOCODE!]
[!IF "(node:exists(as:modconf('ReProgMemM')))"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(as:modconf('ReProgMemM')/MemoryConfig/Memory/*))"!]
[!ELSEIF "node:exists(as:modconf('Flash')) or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (node:exists(as:modconf('ProgVCC')) and as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
[!ENDIF!]
[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "SEGMENT_IDX"="1"!]
[!VAR "SEGMENT_IDX_2"="1"!]
[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
[!VAR "BLOCK_IDX"="1"!]

[!VAR "SEGMENT_FOR_BOOTLOADER_PARTITION_IS_DEFINED" = "0"!]
[!/* Collect the information if a Bootloader Partition has been defined */!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
    [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_BOOTLOADER_PARTITION'"!]
        [!VAR "SEGMENT_FOR_BOOTLOADER_PARTITION_IS_DEFINED" = "1"!]
        [!VAR "NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION" = "text:toupper(name(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]))"!]
    [!ENDIF!]
[!ENDFOR!]

[!/* In case that a segment has been defined for Bootloader partition, a block with index 0 shall refer to this segment */!]
[!IF "$SEGMENT_FOR_BOOTLOADER_PARTITION_IS_DEFINED = 1"!]
    [!VAR "GOOD_ASSOCIATION" = "0"!]
    [!VAR "BLOCK_INDEX_0_IS_DEFINED" = "0"!]
    [!VAR "BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS" = "0"!]
    [!VAR "NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT" = "0"!]
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!IF "(text:toupper(name(node:ref(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/First_Segment))) = $NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION)"!]
            [!VAR "BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS" = "1"!]
            [!VAR "NAME_OF_BLOCK_REFERENCING_BOOTLOADER_SEGMENT" = "name(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)])"!]
            [!VAR "NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT" = "$NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT + 1"!]
            [!IF "num:hextoint(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/Block_Identifier) = number('0')"!]
                [!VAR "BLOCK_INDEX_0_IS_DEFINED" = "1"!]
                [!VAR "NAME_OF_BLOCK_INDEX_0" = "name(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)])"!]
                [!VAR "GOOD_ASSOCIATION" = "1"!]
            [!ENDIF!]
        [!ELSE!]
            [!IF "num:hextoint(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/Block_Identifier) = number('0')"!]
                [!VAR "BLOCK_INDEX_0_IS_DEFINED" = "1"!]
                [!VAR "NAME_OF_BLOCK_INDEX_0" = "name(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)])"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDFOR!]
    [!IF "$GOOD_ASSOCIATION = 0"!]
        [!IF "$BLOCK_INDEX_0_IS_DEFINED = 0"!]
            [!IF "$BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS = 0"!]
                [!ERROR!]
                    No block with index 0 exists and no block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]"
                [!ENDERROR!]
            [!ELSE!]
                [!IF "$NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT = 1"!]
                    [!ERROR!]
                        Block "[!"$NAME_OF_BLOCK_REFERENCING_BOOTLOADER_SEGMENT"!]" which refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" must have index 0
                    [!ENDERROR!]
                [!ELSE!]
                    [!ERROR!]
                        More than one block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" but none of them has index 0
                    [!ENDERROR!]
                [!ENDIF!]
            [!ENDIF!]
        [!ELSE!]
            [!IF "$BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS = 0"!]
                [!ERROR!]
                    No block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]". Block with index 0 "[!"$NAME_OF_BLOCK_INDEX_0"!]" must refer to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]"
                [!ENDERROR!]
            [!ELSE!]
                [!IF "$NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT = 1"!]
                    [!ERROR!]
                        Either Block with index 0 "[!"$NAME_OF_BLOCK_INDEX_0"!]" must refer to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" or block "[!"$NAME_OF_BLOCK_REFERENCING_BOOTLOADER_SEGMENT"!]" which refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" must have index 0
                    [!ENDERROR!]
                [!ELSE!]
                    [!ERROR!]
                        More than one block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" but none of them has index 0. Block with index 0 "[!"$NAME_OF_BLOCK_INDEX_0"!]" doesn't refer to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]"
                    [!ENDERROR!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]

[!/*Check if two segment are not overlapping each other */!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
    [!FOR "SEGMENT_IDX_2" = "1" TO "$SEGMENT_MAX"!]
        [!IF "$SEGMENT_IDX_2 != $SEGMENT_IDX"!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address) != 0)"!]
                [!WARNING "The reprogramming start address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address) != 0)"!]
                [!WARNING "The reprogramming end address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address) != 0)"!]
                [!WARNING "The erasing start address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address) != 0)"!]
                [!WARNING "The erasing end address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDFOR!]
[!ENDFOR!]

[!IF "node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') and (as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Standard')"!]
[!/*Check if the CRC isn't outside of the block */!]
  [!VAR "START_ADD"="0"!]
  [!VAR "END_ADD"="0"!]
  [!VAR "BLOCK_FIRST_SEGMENT_INDEX"="0"!]
  [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
    [!VAR "CRC_IS_IN_BLOCK"="0"!]
    [!VAR "BLOCK_FIRST_SEGMENT_NAME"="name(node:ref(Blocks/*[number($BLOCK_IDX)]/First_Segment))"!]
    [!VAR "CRC_ADDR"="num:dectoint(Blocks/*[number($BLOCK_IDX)]/Crc_Address)"!]
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
      [!VAR "CURRENT_SEGMENT_NAME" = "name(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)])"!]
      [!IF "$BLOCK_FIRST_SEGMENT_NAME = $CURRENT_SEGMENT_NAME"!]
        [!VAR "START_ADD"="num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
        [!VAR "END_ADD"="num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address)"!]
        [!VAR "PARTITION_TYPE" = "Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
        [!VAR "BLOCK_FIRST_SEGMENT_INDEX" = "$SEGMENT_IDX"!]
        [!IF "(num:i($CRC_ADDR) >= num:i($START_ADD)) and (num:i($CRC_ADDR) <= (num:i($END_ADD)-1))"!]
          [!VAR "CRC_IS_IN_BLOCK"="1"!]
        [!ENDIF!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDFOR!]
    [!IF "$SEGMENT_MAX > 1"!]
      [!VAR "BLOCK_SEGMENT_NBR"="num:dectoint(Blocks/*[number($BLOCK_IDX)]/Segment_Number)"!]
      [!FOR "SEGMENT_IDX" = "1" TO "$BLOCK_SEGMENT_NBR - 1"!]
        [!FOR "SEGMENT_IDX_2" = "1" TO "$SEGMENT_MAX"!]
          [!IF "$SEGMENT_IDX_2 != $BLOCK_FIRST_SEGMENT_INDEX"!]
            [!IF "($PARTITION_TYPE = Segments/*[number($SEGMENT_IDX_2)]/Partition_Type)"!]
              [!VAR "START_ADD"="num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_Start_Address)"!]
              [!VAR "END_ADD"="num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address)"!]
              [!IF "(num:i($CRC_ADDR) >= num:i($START_ADD)) and (num:i($CRC_ADDR) <= (num:i($END_ADD)-1))"!]
                [!VAR "CRC_IS_IN_BLOCK"="1"!]
              [!ENDIF!]
            [!ELSE!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDFOR!]
      [!ENDFOR!]
    [!ENDIF!]
    [!IF "$CRC_IS_IN_BLOCK = 0"!]
      [!ERROR!]
        Block [!"string($BLOCK_IDX - 1)"!] : The CRC is outside of the block
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]
/*----------------------------------------------------------------------------------*/
[!ENDNOCODE!]

const tCfgMemorytType m_astCfgMemory[PROG_MEMORY_NB] =
{
    [!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
[!IF "(node:exists(as:modconf('ReProgMemM')))"!]
    [!VAR "MEMORY_TYPE"="text:toupper(as:modconf('ReProgMemM')/MemoryConfig/Memory/*[number($MEMORY_IDX)]/Memory_Type)"!]
    [!VAR "MEMORY_MIN_VALUE_TO_WRITE"="num:inttohex(as:modconf('ReProgMemM')/MemoryConfig/Memory/*[number($MEMORY_IDX)]/Min_Value_To_Write)"!]
    [!VAR "MEMORY_ADDRESS_OFFSET"="num:inttohex(as:modconf('ReProgMemM')/MemoryConfig/Memory/*[number($MEMORY_IDX)]/Addr_Offset)"!]
    [!VAR "MEMORY_ERASE_VALUE"="num:inttohex(as:modconf('ReProgMemM')/MemoryConfig/Memory/*[number($MEMORY_IDX)]/Erase_Value)"!]
[!ELSEIF "node:exists(as:modconf('Flash')) or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (node:exists(as:modconf('ProgVCC')) and as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
    [!VAR "MEMORY_TYPE"="text:toupper(Memory/*[number($MEMORY_IDX)]/Memory_Type)"!]
    [!VAR "MEMORY_MODE"="(Memory/*[number($MEMORY_IDX)]/Memory_Mode)"!]
    [!VAR "MEMORY_MIN_VALUE_TO_WRITE"="num:inttohex(Memory/*[number($MEMORY_IDX)]/Min_Value_To_Write)"!]
    [!VAR "MEMORY_ADDRESS_OFFSET"="num:inttohex(Memory/*[number($MEMORY_IDX)]/Addr_Offset)"!]
    [!VAR "MEMORY_ERASE_VALUE"="num:inttohex(Memory/*[number($MEMORY_IDX)]/Erase_Value)"!]
[!ENDIF!]

    {
        PROG_MEM_TYPE_[!"$MEMORY_TYPE"!],
[!IF "node:exists(as:modconf('Flash'))  or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (node:exists(as:modconf('ProgVCC')) and as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
        [!WS "8"!][!IF "$MEMORY_MODE = 'asynchronous'"!]PROG_MEMORY_ASYNCHRONOUS[!ELSE!]PROG_MEMORY_SYNCHRONOUS[!ENDIF!],
[!ENDIF!]
        [!"$MEMORY_MIN_VALUE_TO_WRITE"!]U,
        [!"$MEMORY_ADDRESS_OFFSET"!]U,
        [!"$MEMORY_ERASE_VALUE"!]U,
    },
    [!ENDFOR!]
};

[!IF "General/Tunable_Parameters = 'false'"!]
 [!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
 [!VAR "CRCVERIFCATIONENABLED"="'false'"!]
 [!IF "node:exists(as:modconf('ProgJLR')) or (node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid'))"!]
 
  [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
  [!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]
   [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
   [!VAR "SEGMENT_IDX"="$SEGMENT_MAX"!]
  [!ELSE!]
   [!VAR "CRCVERIFCATIONENABLED"="'true'"!]
  [!ENDIF!]
  [!ENDFOR!]
  [!ENDIF!]
const tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB] =
{
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
        [!VAR "END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address)"!]
        [!VAR "ERASE_START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address)"!]
        [!VAR "ERASE_END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address)"!]
        [!VAR "MEM_NAME" = "text:toupper(name(node:ref(Segments/*[number($SEGMENT_IDX)]/Memory)))"!]
        [!VAR "ACCESS_TYPE"="num:Segments/*[number($SEGMENT_IDX)]/Access_Type"!]

        [!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
[!IF "(node:exists(as:modconf('ReProgMemM')))"!]
		 [!IF "$MEM_NAME = text:toupper(name(as:modconf('ReProgMemM')/MemoryConfig/Memory/*[number($MEMORY_IDX)]))"!][!//
		    [!VAR "SELECTED_MEM_IDX" = "num:dectoint($MEMORY_IDX - 1)"!][!//
         [!ENDIF!]
[!ELSEIF "node:exists(as:modconf('Flash')) or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL') or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (node:exists(as:modconf('ProgVCC')) and as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL')"!]
                 [!IF "$MEM_NAME = text:toupper(name(Memory/*[number($MEMORY_IDX)]))"!]
            [!VAR "SELECTED_MEM_IDX" = "num:dectoint($MEMORY_IDX - 1)"!][!//
            [!ENDIF!]
[!ENDIF!]
        [!ENDFOR!]
        [!VAR "LAST_LOWER_START_ADDRESS" = "0"!]
        [!IF "(((node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode = 'All') or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord'))) and $BLOCK_MAX=0)"!]
            [!VAR "BLOCK_INDEX" = "num:i(0)"!]
        [!ENDIF!]
        [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
            [!VAR "SEGMENT_REFERENCE" = "text:toupper(name(node:ref(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/First_Segment)))"!]
            [!FOR "SEGMENT_IDX1" = "1" TO "$SEGMENT_MAX"!]
                [!IF "(text:toupper(name(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX1)])) = $SEGMENT_REFERENCE)"!]
                    [!VAR "CURRENT_START_ADDRESS" = "num:dectoint(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX1)]/Reprog_Start_Address)"!]
                    [!IF "$CURRENT_START_ADDRESS <= num:dectoint(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
                        [!IF "$LAST_LOWER_START_ADDRESS <= $CURRENT_START_ADDRESS"!]
                            [!VAR "BLOCK_INDEX" = "num:i(($BLOCK_IDX)-1)"!]
                            [!VAR "LAST_LOWER_START_ADDRESS" = "$CURRENT_START_ADDRESS"!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDFOR!]
        [!ENDFOR!]
    {
        [!"$START_ADD"!]U,[!WS "24"!]/* Start Address */
        [!"$END_ADD"!]U,[!WS "24"!]/* End Address */
        [!"$ERASE_START_ADD"!]U,[!WS "24"!]/* Erase Start Address */
        [!"$ERASE_END_ADD"!]U,[!WS "24"!]/* Erase End Address */
        [!"$SELECTED_MEM_IDX"!]U,[!WS "15"!]/* Selected Memory Index */
        PROG_MEM_ACCESS_TYPE_[!"$ACCESS_TYPE"!],[!WS "3"!]/* Memory Access Type */
[!IF "node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgOEMInd'))"!]
        [!"Segments/*[number($SEGMENT_IDX)]/Partition_Type"!][!IF "node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or (node:exists(as:modconf('ProgFCA')))"!],[!ENDIF!][!WS "8"!]/* Partition Type */
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgOEMInd'))) or (node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or ( as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/ValidityCheck = 'false'"!]PROG_FALSE[!ELSE!]PROG_TRUE[!ENDIF!],/* Validity Check */
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'Address') or node:exists(as:modconf('ProgPSA'))"!]
        [!"$BLOCK_INDEX"!]U,[!WS "33"!]/* Corresponding Block Index */
[!ENDIF!]
 [!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid') and ($SIGNATUREVERIFCATIONENABLED = 'true')"!]
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]PROG_TRUE, [!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!] /*Signature Verification to be done or not for this segment */
 [!ELSEIF "((node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')) and (($CRCVERIFCATIONENABLED = 'true') or ($SIGNATUREVERIFCATIONENABLED = 'true')))"!]
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]PROG_TRUE, [!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!] /*Signature Verification to be done or not for this segment */
 [!ELSEIF "(node:exists(as:modconf('ProgJLR')) and ((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL')))"!]
        PROG_TRUE, /*Signature Verification to be done or not for this segment */
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR')) and ((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')))"!]
        [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_APPLICATION_PARTITION'"!]
        0,
        [!ENDIF!]
        [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_CALIBRATION_PARTITION'"!]
        1,
        [!ENDIF!]
        [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_APP1_PARTITION'"!]
        2,
        [!ENDIF!]
        [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_CAL1_PARTITION'"!]
        3,
        [!ENDIF!]
        [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_RAM_PARTITION'"!]
        4,
        [!ENDIF!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR')) and ((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')))"!]
        [!"Segments/*[number($SEGMENT_IDX)]/StartSegment"!]

[!ENDIF!]
    },
    [!ENDFOR!]
};

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgPSA'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'LogicalBlock')"!]
const tProg_Block    stCfgBlock[PROG_BLOCK_NB] =
{
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!VAR "BLOCK_IDENT"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
        [!VAR "SEGMENT_NAME"="text:toupper(name(node:ref(Blocks/*[number($BLOCK_IDX)]/First_Segment)))"!]
        [!VAR "SEGMENT_NBR"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Segment_Number)"!]
        [!VAR "SEGMENT_PRG_CNT_MAX"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Block_Programming_Counter_Max)"!]
        [!VAR "SEGMENT_ID"="(Blocks/*[number($BLOCK_IDX)]/First_Segment)"!]
[!IF "node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') and (as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Standard')"!]
        [!VAR "CRC_ADDR"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Crc_Address)"!]
[!ENDIF!]
    {
        [!"$BLOCK_IDENT"!]U,[!WS "23"!]/* Block Identifier */
        PROG_SEG_[!"$SEGMENT_NAME"!],[!WS "2"!]/* Name of the first segment*/
        [!"$SEGMENT_NBR"!]U,[!WS "23"!]/* Number of segments contained in the block */
        [!"$SEGMENT_PRG_CNT_MAX"!]U,[!WS "23"!]/* Maximum number of programming allowed */
[!IF "node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') and (as:modconf('Prog')/DownloadVerification/FCA_Reprogramming = 'Standard')"!]
        [!"$CRC_ADDR"!]U,[!WS "16"!]/* Address of the CRC in data*/
[!ENDIF!]
[!IF "((node:exists(as:modconf('ProgVAG')))and (as:modconf('Prog')/VAG/Downgrade_Protection = 'true'))"!]
        [!WS "8"!][!IF "Blocks/*[number($BLOCK_IDX)]/Downgrade_Protected = 'false'"!]PROG_FALSE[!ELSE!]PROG_TRUE[!ENDIF!],[!WS "18"!]/* Downgrade Protected */
[!ENDIF!]
    },
    [!ENDFOR!]
    [!IF "General/PreliminaryErasing = 'true'"!]
    /* A virtual block containing all the segments in order to support preliminary erasing */
    [!ENDIF!]
     [!IF "node:exists(as:modconf('ProgPSA'))"!]
     /* A virtual block containing all the segments in order to search a segment ID */
     [!ENDIF!]
     [!IF "General/PreliminaryErasing = 'true' or node:exists(as:modconf('ProgPSA'))"!]
        [!VAR "SEGMENT_NAME"="text:toupper(name(Segments/*[number(1)]))"!]
        [!VAR "SEGMENT_NBR"="num:dectoint(count(Segments/*))"!]
    {
        PROG_MAX_BLOCK_ID,[!WS "10"!]/* Block Identifier */
        PROG_SEG_[!"$SEGMENT_NAME"!],[!WS "11"!]/* Name of the first segment*/
        [!"$SEGMENT_NBR"!]U,[!WS "25"!]/* Number of segments contained in the block */
        0U,[!WS "25"!]/* Maximum number of programming allowed */
[!IF "((node:exists(as:modconf('ProgVAG')))and (as:modconf('Prog')/VAG/Downgrade_Protection = 'true'))"!]
        [!WS "8"!]PROG_TRUE,[!WS "18"!]/* Downgrade Protected */
[!ENDIF!]
    }
    [!ENDIF!]
};
[!ENDIF!]

[!/*All segments shall be erased on reception of EraseMemory so we generate a single block containing all segments */!]
[!IF "((node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'All') or (node:exists(as:modconf('ProgVCC'))) or (node:exists(as:modconf('ProgFord'))))"!]
const tProg_Block    stCfgBlock[PROG_BLOCK_NB] =
{
    [!VAR "SEGMENT_NAME"="text:toupper(name(Segments/*[number(1)]))"!]
    [!VAR "SEGMENT_NBR"="num:dectoint(count(Segments/*))"!]
    {
        0,/* Block Identifier */
        PROG_SEG_[!"$SEGMENT_NAME"!],/* Name of the first segment*/
        [!"$SEGMENT_NBR"!]U,/* Number of segments contained in the block */
        0,/* Maximum number of programming allowed */
    },
};
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF') or (as:modconf('Prog')/Security/Secure_Checksum_computation = 'true'))
       and (node:exists(as:modconf('ProgDAG'))
       or  (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
       or  (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode = 'LogicalBlock'))"!]
const tProg_BlockSecureBootInfo    stCfgBlockSecureBootInfo[PROG_BLOCK_NB] =
{
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!VAR "BLOCK_IDENT"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
        [!VAR "START_ADDRESS"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/SecureBoot/Start_Address_Secure_Boot_Verification)"!]
        [!VAR "LENGTH"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/SecureBoot/Length_Secure_Boot_Verification)"!]
    {
        [!WS "8"!][!"$START_ADDRESS"!]U,[!WS "17"!]/* Start Address for the Secure Boot Verification */
        [!WS "8"!][!"$LENGTH"!]U,[!WS "17"!]/* Length of the block for the Secure Boot Verification */
        [!"$BLOCK_IDENT"!]U,[!WS "23"!]/* Block Identifier */
        [!WS "8"!][!IF "Blocks/*[number($BLOCK_IDX)]/SecureBoot/Verified_For_Secure_Boot='Block will be verified'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* Block will be verified by the Secure Boot */
        [!WS "8"!][!IF "Blocks/*[number($BLOCK_IDX)]/SecureBoot/Blocker_for_Software_execution='Will block software execution'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* Block will prevent the execution of software if Secure Boot verification is failed */
    },
    [!ENDFOR!]
};
[!ENDIF!]
[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF') or (as:modconf('Prog')/Security/Secure_Checksum_computation = 'true'))
       and ((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid') 
       or node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgJLR'))
       or   (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'LogicalBlock'))"!]
const tProg_BlockSecureBootInfo    stCfgBlockSecureBootInfo[PROG_SEGMENT_NB] =
{
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "START_ADDRESS"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/SecureBoot/Start_Address_Secure_Boot_Verification)"!]
        [!VAR "LENGTH"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/SecureBoot/Length_Secure_Boot_Verification)"!]
    {
        [!WS "8"!][!"$START_ADDRESS"!]U,[!WS "17"!]/* Start Address for the Secure Boot Verification */
        [!WS "8"!][!"$LENGTH"!]U,[!WS "17"!]/* Memory size for the Secure Boot Verification */
        [!"$SEGMENT_IDX"!]U,[!WS "23"!]/* Segment Identifier */
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/SecureBoot/Verified_For_Secure_Boot='Block will be verified'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* if TRUE Segment will be verified by the Secure Boot else this will be excluded from the secure boot verification */
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/SecureBoot/Blocker_for_Software_execution='Will block software execution'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* if set to TRUE then on the failure of Secure Boot verification for this segment, execution of the software is halted*/
    },
    [!ENDFOR!]
};
[!ENDIF!]
[!ELSE!]
const tCfgSegmentType stConstConfigSegment[PROG_SEGMENT_NB] =
{
    [!VAR "NBR_PROT_CAL"="0"!]
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
        [!VAR "END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address)"!]
        [!VAR "ERASE_START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address)"!]
        [!VAR "ERASE_END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address)"!]
        [!VAR "MEM_NAME" = "text:toupper(name(node:ref(Segments/*[number($SEGMENT_IDX)]/Memory)))"!]
        [!VAR "ACCESS_TYPE"="num:Segments/*[number($SEGMENT_IDX)]/Access_Type"!]
        [!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
            [!IF "$MEM_NAME = text:toupper(name(Memory/*[number($MEMORY_IDX)]))"!]
                [!VAR "SELECTED_MEM_IDX" = "num:dectoint($MEMORY_IDX - 1)"!]
            [!ENDIF!]
        [!ENDFOR!]
    {
        [!"$START_ADD"!]U,
        [!"$END_ADD"!]U,
        [!"$ERASE_START_ADD"!]U,
        [!"$ERASE_END_ADD"!]U,
        [!"$SELECTED_MEM_IDX"!]U,
        PROG_MEM_ACCESS_TYPE_[!"$ACCESS_TYPE"!],
[!IF "node:exists(as:modconf('ProgGM'))"!]
        [!"Segments/*[number($SEGMENT_IDX)]/Partition_Type"!],
[!ENDIF!]
 [!IF "((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid') or (node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')))"!]
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!] /*Signature Verification to be done or not for this segment */
 [!ELSEIF "(node:exists(as:modconf('ProgJLR')) and ((as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL')))"!]
        PROG_TRUE,
 [!ELSEIF "((node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')) and ($CRCVERIFCATIONENABLED = 'true'))"!]
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]PROG_TRUE [!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!] /*Signature Verification to be done or not for this segment */
[!ENDIF!]
    },
    [!ENDFOR!]
};


tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB];
[!ENDIF!]

[!IF "as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_APP_PARTITION' 
   or as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_CAL_PARTITION'
   or as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_PARTITION'"!]
[!/* Get information about the Routine controle*/!]
    [!VAR "RC_TABLE_INDEX"="0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "(node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgOEMInd'))) and Callback = 'PROG_CheckMemory'"!]
            [!VAR "RC_TABLE_INDEX"="@index + 1"!]
tContextRestore stBLUContextRestore =
{
    [!"as:modconf('Uds')/Routine_Control/*[number($RC_TABLE_INDEX)]/SecurityLevel"!],
    {
        {
            0x31,
            [!"num:inttohex(as:modconf('Uds')/Routine_Control/*[number($RC_TABLE_INDEX)]/SubService)"!],
            [!"num:inttohex(bit:shr(bit:and(as:modconf('Uds')/Routine_Control/*[number($RC_TABLE_INDEX)]/Routine_Identifier, 65280), 8))"!],
            [!"num:inttohex(bit:and(as:modconf('Uds')/Routine_Control/*[number($RC_TABLE_INDEX)]/Routine_Identifier, 255))"!],
        },
        [!"num:inttohex(as:modconf('Uds')/Routine_Control/*[number($RC_TABLE_INDEX)]/Length)"!]
    }
};
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
/* Programmed magic number value */
const u8 m_aCfgMagicNumProgrammedValue[PROG_MAGIC_NUM_SIZE] =
{
    /* PROGRAMM in ASCII */
    0x50U,
    0x52U,
    0x4FU,
    0x47U,
    0x52U,
    0x41U,
    0x4dU,
    0x4dU,
};
/* Revoked PSI value */
const u8 m_aCfgMagicNumRevokedValue[PROG_MAGIC_NUM_SIZE] =
{
    /* REVOKED in ASCII */
    0x56U,
    0x52U,
    0x45U,
    0x56U,
    0x4FU,
    0x4BU,
    0x45U,
    0x44U
};
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/* Pointer to App Sw Info */
u8* m_pubAppSwInfo = (u8*)PROG_APP_SW_INFO_ADDR;
/* Programmed PSI value */
const u8 m_aCfgPSIProgrammedValue[PROG_PSI_VAL_SIZE] =
{
    0x[!"substring(GM//PSI_Programmed,1,2)"!],
    0x[!"substring(GM//PSI_Programmed,3,2)"!],
    0x[!"substring(GM//PSI_Programmed,5,2)"!],
    0x[!"substring(GM//PSI_Programmed,7,2)"!],
    0x[!"substring(GM//PSI_Programmed,9,2)"!],
    0x[!"substring(GM//PSI_Programmed,11,2)"!],
    0x[!"substring(GM//PSI_Programmed,13,2)"!],
    0x[!"substring(GM//PSI_Programmed,15,2)"!],
};
/* Revoked PSI value */
const u8 m_aCfgPSIRevokedValue[PROG_PSI_VAL_SIZE] =
{
    0x[!"substring(GM//PSI_Revoked,1,2)"!],
    0x[!"substring(GM//PSI_Revoked,3,2)"!],
    0x[!"substring(GM//PSI_Revoked,5,2)"!],
    0x[!"substring(GM//PSI_Revoked,7,2)"!],
    0x[!"substring(GM//PSI_Revoked,9,2)"!],
    0x[!"substring(GM//PSI_Revoked,11,2)"!],
    0x[!"substring(GM//PSI_Revoked,13,2)"!],
    0x[!"substring(GM//PSI_Revoked,15,2)"!],
};

/* Bootloader information */
#define PROG_BOOT_INFO_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
const tBootInfoBlock m_stBootInfoBlock =
{
    [!"num:inttohex(GM//BCID)"!]U, /*  BICD value */
[!IF "GM/EcuId_Source = 'Tresos_Configuration'"!]
    /* ECU ID */
    {
        0x[!"substring(GM//ECU_ID,1,2)"!],
        0x[!"substring(GM//ECU_ID,3,2)"!],
        0x[!"substring(GM//ECU_ID,5,2)"!],
        0x[!"substring(GM//ECU_ID,7,2)"!],
        0x[!"substring(GM//ECU_ID,9,2)"!],
        0x[!"substring(GM//ECU_ID,11,2)"!],
        0x[!"substring(GM//ECU_ID,13,2)"!],
        0x[!"substring(GM//ECU_ID,15,2)"!],
        0x[!"substring(GM//ECU_ID,17,2)"!],
        0x[!"substring(GM//ECU_ID,19,2)"!],
        0x[!"substring(GM//ECU_ID,21,2)"!],
        0x[!"substring(GM//ECU_ID,23,2)"!],
        0x[!"substring(GM//ECU_ID,25,2)"!],
        0x[!"substring(GM//ECU_ID,27,2)"!],
        0x[!"substring(GM//ECU_ID,29,2)"!],
        0x[!"substring(GM//ECU_ID,31,2)"!],
    },
[!ENDIF!]
    /* ECU name */
    {
        [!VAR "SEGMENT_MAX"="num:dectoint(string-length(GM/ECU_Name))"!]
        [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!WS "8"!]'[!"substring(GM//ECU_Name,$SEGMENT_IDX,1)"!]',
        [!ENDFOR!]
        [!FOR "SEGMENT_IDX" = "$SEGMENT_MAX" TO "7"!]
        [!WS "8"!]0x00,
        [!ENDFOR!]
    },
    /* ECU subject name */
    {
        0x[!"substring(GM//Subject_Name,1,2)"!],
        0x[!"substring(GM//Subject_Name,3,2)"!],
        0x[!"substring(GM//Subject_Name,5,2)"!],
        0x[!"substring(GM//Subject_Name,7,2)"!],
        0x[!"substring(GM//Subject_Name,9,2)"!],
        0x[!"substring(GM//Subject_Name,11,2)"!],
        0x[!"substring(GM//Subject_Name,13,2)"!],
        0x[!"substring(GM//Subject_Name,15,2)"!],
        0x[!"substring(GM//Subject_Name,17,2)"!],
        0x[!"substring(GM//Subject_Name,19,2)"!],
        0x[!"substring(GM//Subject_Name,21,2)"!],
        0x[!"substring(GM//Subject_Name,23,2)"!],
        0x[!"substring(GM//Subject_Name,25,2)"!],
        0x[!"substring(GM//Subject_Name,27,2)"!],
        0x[!"substring(GM//Subject_Name,29,2)"!],
        0x[!"substring(GM//Subject_Name,31,2)"!],
    },
    /* Boot Part Number */
    {
        0x[!"substring(GM//BOOT_Part_Number,1,2)"!],
        0x[!"substring(GM//BOOT_Part_Number,3,2)"!],
        0x[!"substring(GM//BOOT_Part_Number,5,2)"!],
        0x[!"substring(GM//BOOT_Part_Number,7,2)"!],
    },
    /* Boot DLS */
    {
        '[!"substring(GM//BOOT_DLS,1,1)"!]',
        '[!"substring(GM//BOOT_DLS,2,1)"!]',
    },
    /* Number of Protected Calibrations*/
        [!VAR "NBR_PROT_CAL"="num:dectoint(0)"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
        [!VAR "NBR_PROT_CAL" = "num:dectoint($NBR_PROT_CAL + 1)"!]
[!ENDIF!]
[!ENDFOR!]
        [!"$NBR_PROT_CAL"!]U,
[!IF "$NBR_PROT_CAL > num:dectoint(0)"!]
    /*Protected Partition IDs*/
    {
[!VAR "PROT_CAL_PARTITION_ID"="num:dectoint(0)"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
[!VAR "PROT_CAL_PARTITION_ID"="num:dectoint(Segments/*[number($SEGMENT_IDX)]/Protected_Partition_ID)"!]
        [!"$PROT_CAL_PARTITION_ID"!]U,
[!ENDIF!]
[!ENDFOR!]
    },
[!ENDIF!]
};
#define PROG_BOOT_INFO_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgPSA'))"!]
/* Match table that contains for each routine associated index in request routine result list */
[!VAR "LIST_INDEX" = "num:i(0)"!]
const tProgRoutineResultInfo    stCfgRoutineResultTable[PROG_ROUTINE_RESULT_NB] = 
{
    [!FOR "ROUTINE_INDEX" = "1" TO "num:dectoint(count(as:modconf('Uds')/Routine_Control/*))"!]
        [!IF "as:modconf('Uds')/Routine_Control/*[number($ROUTINE_INDEX)]/SubService = '3'"!]
        {
            PROG_ROUTINE_ID_[!"translate(substring(num:inttohex(as:modconf('Uds')/Routine_Control/*[number($ROUTINE_INDEX)]/Routine_Identifier),3,6),'abcdef','ABCDEF')"!],[!WS "10"!]/* Routine identifier */
            [!"num:inttohex($LIST_INDEX)"!]U,[!WS "25"!]/* Index of routine identifier in the list */
            [!VAR "LIST_INDEX" = "($LIST_INDEX + 1)"!]
        },
        [!ENDIF!]
    [!ENDFOR!]
};
[!ENDIF!]
 [!IF "node:exists(as:modconf('CryIf'))"!]
/* Prog-Csm Job configurations */
  [!VAR "ProgCsmJobIndex" = "0"!]
  [!VAR "ProgCsmSignatureJobIndex" = "255"!]
  [!VAR "ProgCsmHashJobIndex" = "255"!]
  [!VAR "ProgCsmSecureJobIndex" = "255"!]
  [!VAR "ProgCsmDecryptionJobIndex" = "255"!]

[!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))"!]
   [!VAR "ProgCsmSignatureJobIndex" = "num:dectoint(number($ProgCsmJobIndex))"!]
   [!VAR "ProgCsmJobIndex"= "$ProgCsmJobIndex + 1"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId))"!]
    [!VAR "ProgCsmHashJobIndex" = "num:dectoint(number($ProgCsmJobIndex))"!]
    [!VAR "ProgCsmJobIndex" = "$ProgCsmJobIndex + 1"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
    [!VAR "ProgCsmSecureJobIndex" = "num:dectoint(number($ProgCsmJobIndex))"!]
    [!VAR "ProgCsmJobIndex" = "$ProgCsmJobIndex + 1"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('Prog')/Decryption/ProgCsmDecryptionConfigId))"!]
	[!VAR "ProgCsmDecryptionJobIndex" = "num:dectoint(number($ProgCsmJobIndex))"!]
[!VAR "ProgCsmJobIndex" = "$ProgCsmJobIndex + 1"!]
[!ENDIF!]
[!IF "num:dectoint($ProgCsmJobIndex) > 0"!]
const tProgCsmJobConf m_astProgCsmJobConf[PROG_CSM_NUMCONF_JOBS] =
{
[!IF "number($ProgCsmSignatureJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!][!"(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/BS_size)"!]U, /*Size of the Data Block Slicing*/
[!WS "8"!][!"(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId)/CsmJobId)"!]U, /*Corresponding Csm Job ID*/
[!WS "8"!]&PROG_CsmCheckResult, /*Callback handling API for the configured Algo*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/Allow2SetCryptoKey) = 'true'"!]PROG_CSM_SIGN_KEYID[!ELSE!]0U[!ENDIF!], /*KeyID assigned by Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/Allow2SetCryptoKey) = 'true'"!]PROG_CRYPTO_SIGN_KEYELEID[!ELSE!]0U[!ENDIF!], /*KeyElementID assigned by the Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/Allow2SetCryptoKey) = 'true'"!]PROG_CRYPTO_SIGN_KEYSIZE[!ELSE!]0U[!ENDIF!], /*KeyLength stored in the Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /* Allow cancellation of ongoing Csm Job? */
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*Enable to set the key and the keystatus in the Crypto driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/Allow2CustomCsmStartPreprocess) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*TRUE if the Custom Preprocessing before the CsmStart is expected (eg.: DER Key encoding )*/
[!WS "4"!]},
[!ENDIF!]
[!IF "number($ProgCsmHashJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!][!"(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/BS_size)"!]U, /*Size of the Data Block Slicing*/
[!WS "8"!][!"(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId)/CsmJobId)"!]U, /*Corresponding Csm Job ID*/
[!WS "8"!]&PROG_CsmCheckResult, /*Callback handling API for the configured Algo*/
[!WS "8"!]0U, /*KeyID is not applicable for Hash jobs*/
[!WS "8"!]0U, /*KeyElementID is not applicable for Hash jobs*/
[!WS "8"!]0U, /*KeyLength is not applicable for Hash jobs*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*Allow cancellation of ongoing Csm Job? */
[!WS "8"!]PROG_FALSE, /*Allow keyset is not applicable for Hash job*/
[!WS "8"!]PROG_FALSE, /*Custom Preprocessing is not needed for Hash jobs*/
[!WS "4"!]},
[!ENDIF!]
[!IF "number($ProgCsmSecureJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!][!"(as:modconf('Prog')/Security/BS_size)"!]U, /*Size of the Data Block Slicing*/
[!WS "8"!][!"(as:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobId)"!]U, /*Corresponding Csm Job ID*/
[!WS "8"!]&PROG_CsmCheckResult, /*Callback handling API for the configured Algo*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/Allow2SetCryptoKey) = 'true'"!]PROG_CSM_SECURE_KEYID[!ELSE!]0U[!ENDIF!], /*KeyID assigned by Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/Allow2SetCryptoKey) = 'true'"!]PROG_CRYPTO_SECURE_KEYELEID[!ELSE!]0U[!ENDIF!], /*KeyElementID assigned by the Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/Allow2SetCryptoKey) = 'true'"!]PROG_CRYPTO_SECURE_KEYSIZE[!ELSE!]0U[!ENDIF!], /*KeyLength stored in the Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*Allow cancellation of ongoing Csm Job? */
[!WS "8"!][!IF "(as:modconf('Prog')/Security/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*Enable to set the key and the keystatus in the Crypto driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Security/Allow2CustomCsmStartPreprocess) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*TRUE if the Custom Preprocessing before the CsmStart is expected (eg.: DER Key encoding )*/
[!WS "4"!]},
[!ENDIF!]
[!IF "number($ProgCsmDecryptionJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]0U, /* Block Slicing is not very effective for Streaming type jobs, hence not supported for Decryption */
[!WS "8"!][!"(as:ref(as:modconf('Prog')/Decryption/ProgCsmDecryptionConfigId)/CsmJobId)"!]U, /*Corresponding Csm Job ID*/
[!WS "8"!]&PROG_CsmDecryptionCheckResult, /*Callback handling API for the configured Algo*/
[!WS "8"!][!IF "(as:modconf('Prog')/Decryption/Allow2SetCryptoKey) = 'true'"!]PROG_CSM_DECRYPTION_KEYID[!ELSE!]0U[!ENDIF!], /*KeyID assigned by Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Decryption/Allow2SetCryptoKey) = 'true'"!]PROG_CRYPTO_DECRYPTION_KEYELEID[!ELSE!]0U[!ENDIF!], /*KeyElementID assigned by the Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Decryption/Allow2SetCryptoKey) = 'true'"!]PROG_CRYPTO_DECRYPTION_KEYSIZE[!ELSE!]0U[!ENDIF!], /*KeyLength stored in the Crypto Driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Decryption/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*Allow cancellation of ongoing Csm Job? */
[!WS "8"!][!IF "(as:modconf('Prog')/Decryption/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*Enable to set the key and the keystatus in the Crypto driver*/
[!WS "8"!][!IF "(as:modconf('Prog')/Decryption/Allow2CustomCsmStartPreprocess) = 'true'"!]PROG_TRUE[!ELSE!]PROG_FALSE[!ENDIF!], /*TRUE if the Custom Preprocessing before the CsmStart is expected (eg.: DER Key encoding )*/
[!WS "4"!]}
[!ENDIF!]
};
[!ENDIF!]
[!ENDIF!]

