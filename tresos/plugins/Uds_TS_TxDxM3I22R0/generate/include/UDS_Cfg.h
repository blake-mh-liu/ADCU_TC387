/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               UDS configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Cfg.h                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.22.0 BL3 */
/*%%  |   &       &    &            |  %%  Variant: ISO                  */
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



#ifndef UDS_CFG_H
#define UDS_CFG_H

[!IF "General/UDS_MANAGE_PERIOD > 250"!][!AUTOSPACING!]
[!WARNING!]To ensure the T_Sess_Diag timout (1s), the period of the task should not exceed 250ms.[!ENDWARNING!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]




/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Configuration Constants                                                     */

/* Define if NRC 7E is implemented for RC request */
#define RC_NRC_IMPLEMENTATION [!WS "12"!][!"num:inttohex(General/RC_NRC_IMPLEMENTATION , 2)"!]U

/* DID implemented in other session and session supported by the service */
#define UDS_NRC_INVALID_DID [!WS "12"!][!"num:inttohex(General/DID_NRC_IMPLEMENTATION , 2)"!]U

/* Define NRC78 first timing */
[!IF "node:exists(General/UDS_P2_ADJUST)"!]#define UDS_P2_ADJUST [!WS "12"!][!"num:i(General/UDS_P2_ADJUST div General/UDS_MANAGE_PERIOD)"!]U
[!ELSE!]#define UDS_P2_ADJUST [!WS "12"!]0U
[!ENDIF!]

/* Define NRC78 period */
[!IF "node:exists(General/P2STAR_ADJUST)"!]#define UDS_P2STAR_ADJUST [!WS "12"!][!"num:i(General/P2STAR_ADJUST div General/UDS_MANAGE_PERIOD)"!]U
[!ELSE!]#define UDS_P2STAR_ADJUST [!WS "12"!]0U
[!ENDIF!]

/* for compatibility for older modules version, keep all these defines */
#define UDS_SESSION_DEFAULT[!WS "12"!]m_stSessionInfo[UDS_DEFAULT_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_PROGRAMMING[!WS "12"!]m_stSessionInfo[UDS_PROGRAMMING_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_EXTENDED_DIAG[!WS "12"!]m_stSessionInfo[UDS_EXTENDED_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_SUPPLIER[!WS "12"!]m_stSessionInfo[UDS_SUPPLIER_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_01[!WS "12"!]m_stSessionInfo[UDS_OTHER_01_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_02[!WS "12"!]m_stSessionInfo[UDS_OTHER_02_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_03[!WS "12"!]m_stSessionInfo[UDS_OTHER_03_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_04[!WS "12"!]m_stSessionInfo[UDS_OTHER_04_SESSION_INDEX].ubSessionValue

#define UDS_SUPPLIERSERVICE_BA[!WS "12"!][!IF "Supplier_Services/BA = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define UDS_SUPPLIERSERVICE_BB[!WS "12"!][!IF "Supplier_Services/BB = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define UDS_SUPPLIERSERVICE_BC[!WS "12"!][!IF "Supplier_Services/BC = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define UDS_SUPPLIERSERVICE_BD[!WS "12"!][!IF "Supplier_Services/BD = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define UDS_SUPPLIERSERVICE_BE[!WS "12"!][!IF "Supplier_Services/BE = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/*-------------------------------------------------------------------------------*/
/* - Configuration Variable or Register Aliases                                  */



/*-------------------------------------------------------------------------------*/
/* - Public Constants                                                            */

extern const tUdsSessionInfo m_stSessionInfo[UDS_CONFIGURABLE_SESSION_MAX];

/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */


/*-------------------------------------------------------------------------------*/
/* - Public Macros                                                               */
[!IF "General/SecurityCheck = 'true'"!]
#define UDS_SECURITY_LEVEL_CHECK_CBK            [!"General/SecurityFunction"!]
[!ENDIF!]

[!IF "node:exists(as:modconf('BlPduR'))"!]
#define UDS_FULL_RESPONSEPENDING                    STD_ON
[!ELSE!]
#define UDS_FULL_RESPONSEPENDING                    STD_OFF
[!ENDIF!]

[!IF "General/Ext_ResponsePending_Manage_Call = 'true'"!]
#define UDS_EXT_RESPONSEPENDING_MANAGE_CALL         STD_ON
[!ELSE!]
#define UDS_EXT_RESPONSEPENDING_MANAGE_CALL         STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('BlPduR'))"!]
/* Physical buffer size (same for all physical if multiple buffer enable) */
#define UDS_RX_PHYS_BUFFERSIZE         [!WS "12"!][!"num:dectoint(as:modconf('BlPduR')/General/RxPhysicalBufferSize)"!]U
[!ELSE!]
#define UDS_RX_PHYS_BUFFERSIZE         [!WS "12"!]0U
[!ENDIF!]
/*                                                                               */
/*********************************************************************************/

#endif      /* UDS_CFG_H */
