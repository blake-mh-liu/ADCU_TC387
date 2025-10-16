[!/**
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
 */!][!//

[!NOCODE!]

[!SELECT "as:modconf('EcuC')[1]"!][!//
[!//

[!IF "as:modconf('EcuC')[1]/EcucGeneral/EcucMetaDataHandlingEnabled = 'true'"!][!//Only do it if Meta Data Handling is enabled
[!//Number of the PDUs
[!VAR "EcuC_Number_Of_PduIds" = "num:i(count(as:modconf('EcuC')[1]/EcucPduCollection/Pdu/*/PduId))"!]

[!//Maximum size of used RAM
[!VAR "Meta_Data_RAM_Size" = "num:i(0)"!]
[!LOOP "as:modconf('EcuC')[1]/EcucPduCollection/Pdu/*[node:exists(PduId)]"!][!//
    [!VAR "Meta_Data_RAM_Size" = "num:i($Meta_Data_RAM_Size) + asc_ecuc:getMetaDataTypeLength(node:ref(./MetaDataTypeRef))"!]
    [!VAR "remainder" = "num:i($Meta_Data_RAM_Size mod 8)"!]
    [!IF "$remainder > num:i(0)"!][!//
      [!VAR "Meta_Data_RAM_Size" = "$Meta_Data_RAM_Size + num:i(8) - $remainder"!]
    [!ENDIF!]
[!ENDLOOP!]
[!VAR "Meta_Data_RAM_Size" = "num:i(num:div($Meta_Data_RAM_Size, num:i(8)))"!]

[!//Number of the Meta Data Items
[!VAR "EcuC_Meta_Data_Item_List_Size" = "num:i(0)"!]
[!LOOP "as:modconf('EcuC')[1]/EcucPduCollection/Pdu/*[node:exists(PduId)]"!][!//
    [!VAR "EcuC_Meta_Data_Item_List_Size" = "num:i($EcuC_Meta_Data_Item_List_Size) + num:i(count(node:ref(./MetaDataTypeRef)/MetaDataItem/*))"!]
[!ENDLOOP!]


[!ENDIF!][!//Meta Data Handling is enabled

[!ENDSELECT!]

[!ENDNOCODE!]
