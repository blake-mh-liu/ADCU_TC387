/**
 * \file
 *
 * \brief AUTOSAR EcuC
 *
 * This file contains the implementation of the AUTOSAR
 * module EcuC.
 *
 * \version 5.0.25
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <EcuC_Cfg.h>

[!AUTOSPACING!]

[!SELECT "as:modconf('EcuC')[1]"!]
[!INCLUDE "../include/EcuC_Vars.m"!]
[!INCLUDE "../include/CommonMacros.m"!]

/*==================[macros]================================================*/

[!IF "as:modconf('EcuC')[1]/EcucGeneral/EcucMetaDataHandlingEnabled = 'true'"!]

[!//Gets Meta Data Id from an item and prints it with comment
[!MACRO "Insert_Meta_Data_Item_Id", "ItemType"!]
  [!VAR "value"="'null'"!]
  [!IF "$ItemType = 'ETHERNET_MAC_64'"!]
    [!VAR "value" = "num:i(0)"!]
  [!ELSEIF "$ItemType = 'CAN_ID_32'"!]
    [!VAR "value" = "num:i(1)"!]
  [!ELSEIF "$ItemType = 'SOCKET_CONNECTION_ID_16'"!]
    [!VAR "value" = "num:i(2)"!]
  [!ELSEIF "$ItemType = 'SOURCE_ADDRESS_16'"!]
    [!VAR "value" = "num:i(3)"!]
  [!ELSEIF "$ItemType = 'TARGET_ADDRESS_16'"!]
    [!VAR "value" = "num:i(4)"!]
  [!ELSEIF "$ItemType = 'ADDRESS_EXTENSION_8'"!]
    [!VAR "value" = "num:i(5)"!]
  [!ELSEIF "$ItemType = 'LIN_NAD_8'"!]
    [!VAR "value" = "num:i(6)"!]
  [!ELSEIF "$ItemType = 'PRIORITY_8'"!]
    [!VAR "value" = "num:i(7)"!]
  [!ELSEIF "$ItemType = 'PAYLOAD_TYPE_16'"!]
    [!VAR "value" = "num:i(8)"!]
  [!ENDIF!]
            [!"$value"!]U, /* metaDataItemId */
[!ENDMACRO!]

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define ECUC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <EcuC_MemMap.h>

/* Space reserved for configured meta data items
 * Memory is aligned to the most stringent alignment requirement
 * of any simple data type available on the respective platform,
 * e.g. uint32.*/

#if (ECUC_META_DATA_CONFIG_SIZE_MAX_64 > 0) /* To prevent empty arrays */
static TS_DefMaxAlignedByteArray(EcuC_MetaDataMemory, ECUC, VAR_CLEARED, (ECUC_META_DATA_CONFIG_SIZE_MAX_64 * 8U));
#endif /* (ECUC_META_DATA_CONFIG_SIZE_MAX_64 > 0) */

#define ECUC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <EcuC_MemMap.h>

/*==================[external constants]====================================*/
#define ECUC_START_SEC_CONST_UNSPECIFIED
#include <EcuC_MemMap.h>

/* Global configuration data */
CONST(EcuC_ConfigType, ECUC_CONST) EcuC_ConfigData =
{
  /* pduConfig */[!// generates the array pduConfig[PduId] for every valid PduId
  {
    [!VAR "Meta_Data_Item_List_Offset" = "num:i(0)"!]
    [!LOOP "util:distinct(node:order(node:filter(as:modconf("EcuC")[1]/EcucPduCollection/Pdu/*,'node:exists(PduId)'), 'PduId' ))"!][!//
     [!VAR "PduIdent"="PduId"!]
     { /* [!"concat('pduConfig[',$PduIdent,']',' -- EcuCConf_PduId_',as:name(.))"!] - [!"node:name(node:path(node:ref(./MetaDataTypeRef)))"!] */
          [!VAR "Meta_Data_Items" = "num:i(count(node:ref(./MetaDataTypeRef)/MetaDataItem/*))"!]
          [!"num:i($Meta_Data_Item_List_Offset)"!]U, /* metaDataItemListOffset */
          [!VAR "Meta_Data_Item_List_Offset" = "num:i($Meta_Data_Item_List_Offset) + num:i($Meta_Data_Items)"!]
          [!"$Meta_Data_Items"!]U, /* NumberMetaDataItems */
          [!"asc_ecuc:getMetaDataTypeLength(node:ref(./MetaDataTypeRef))"!]U /* metaDataTypeLength */
      },
    [!ENDLOOP!]
  },
  /* metaDataItemConfig */
  {
    [!VAR "Meta_Data_Item_Byte_Array_Offset" = "num:i(0)"!]
    [!VAR "Comment_Meta_Data_Item_List_Offset" = "num:i(0)"!]
    [!LOOP "util:distinct(node:order(node:filter(as:modconf("EcuC")[1]/EcucPduCollection/Pdu/*,'node:exists(PduId)'), 'PduId' ))"!][!//
      [!VAR "Comment_Pdu_Name" = "concat('EcuCConf_PduId_',as:name(.))"!]
      [!VAR "Comment_MetaDataType_Name" = "node:name(node:path(node:ref(./MetaDataTypeRef)))"!]
        [!LOOP "node:ref(./MetaDataTypeRef)/MetaDataItem/*"!][!// generate entry for every meta data item with proper comment for PduId, MetaDataType and MetaDataItemType reference
          {  /* metaDataItemConfig[[!"num:i($Comment_Meta_Data_Item_List_Offset)"!]] -- [!"$Comment_Pdu_Name"!] -- [!"$Comment_MetaDataType_Name"!] -- [!"./MetaDataItemType"!] */
            [!VAR "Comment_Meta_Data_Item_List_Offset" = "num:i($Comment_Meta_Data_Item_List_Offset) + num:i(1)"!]
            [!CALL "Insert_Meta_Data_Item_Id", "ItemType"="./MetaDataItemType"!][!// Adding line for MetaDataItemId with comment
            {
              (&((P2VAR(uint8, AUTOMATIC, ECUC_APPL_DATA))EcuC_MetaDataMemory)[[!"num:i($Meta_Data_Item_Byte_Array_Offset)"!]U]), /* metaDataItemOffsetPtr */
              [!"./MetaDataItemLength"!]U /* metaDataItemLength */
            }
          },
            [!VAR "Meta_Data_Item_Byte_Array_Offset" = "num:i($Meta_Data_Item_Byte_Array_Offset) + num:i(./MetaDataItemLength)"!]
        [!ENDLOOP!]
         [!// all items listed - add padding bytes after the final one if needed
          [!VAR "remainder" = "num:i($Meta_Data_Item_Byte_Array_Offset mod 8)"!]
        [!IF "$remainder > num:i(0)"!]
          [!VAR "Meta_Data_Item_Byte_Array_Offset" = "$Meta_Data_Item_Byte_Array_Offset + num:i(8) - $remainder"!]
        [!ENDIF!]
    [!ENDLOOP!]
  },
  [!"num:i($EcuC_Number_Of_PduIds)"!]U /* numConfigPdus */
};

#define ECUC_STOP_SEC_CONST_UNSPECIFIED
#include <EcuC_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/

[!ENDIF!]
[!ENDSELECT!]
