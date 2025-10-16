/* --------{ EB Automotive Header File }-------- */
/* This file generated from the configuration of J1939Nm module . */

[!INCLUDE "J1939Nm_Vars.m"!][!//
#ifndef J1939NM_TYPES_H
#define J1939NM_TYPES_H
[!//
/*==================[includes]===============================================*/

/* !LINKSTO J1939Nm.ASR42.SWS_J1939Nm_00008,1 */
#include <ComStack_Types.h>   /* Inclusion of ComStack types */
#include <NmStack_Types.h>   /* Inclusion of Nm Stack types */
#include <EcuC.h>			  /* Inclusion of Ecuc module */
#include <J1939Nm_Types_Int.h> /*Inclusion of internal typees*/
#include <TSPBConfig_Signature.h>
[!IF "node:contains(util:distinct(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef)), as:modconf('J1939Nm')) = 'true'"!]
#include <PbcfgM_Types.h>
[!ENDIF!]    
/*============================================================================*/
/*                       J1939Nm Type Definitions                             */
/*============================================================================*/

#if (defined J1939NM_NO_TRANSMISSION_PENDING)
#error J1939NM_NO_TRANSMISSION_PENDING already defined
#endif
/** \brief Switch, indicating the status of No pending transmission */
#define J1939NM_NO_TRANSMISSION_PENDING      0U

#if (defined J1939NM_TRANSMISSION_PENDING)
#error J1939NM_TRANSMISSION_PENDING already defined
#endif
/** \brief Switch, indicating the status of pending transmission */
#define J1939NM_TRANSMISSION_PENDING      1U

#if (defined J1939NM_TRANSMISSION_ABORT)
#error J1939NM_TRANSMISSION_ABORT already defined
#endif
/** \brief Switch, indicating the status of transmission abort */
#define J1939NM_TRANSMISSION_ABORT      2U

#if (defined J1939NM_NUMBER_OF_NODES)
#error J1939NM_NUMBER_OF_NODES already defined
#endif
/** \brief Switch, indicating Total Number of Nodes */
#define J1939NM_NUMBER_OF_NODES      (J1939Nm_ConfigPtr->J1939NmNodeNum)

#define J1939NM_NUMBER_OF_NODES_MAX      [!"num:i($TotalMaxNode)"!]U
/*==================[type definitions]=======================================*/

/** \brief Type for the configuration data (place holder because of pre-compile
 **        time configuration support).
 */
 
/* J1939Nm state-machine states */
typedef enum
{
    J1939NM_UNINIT = 0, /* J1939Nm Uninitialized state */
    J1939NM_INIT        /* J1939Nm Initialized state */
} J1939Nm_StateType;

/* J1939Nm Off-line sub-state-machine states */
typedef enum
{
    J1939NM_OFFLINE_CLAIMING = 0, /* OFF-LINE claiming state */
    J1939NM_OFFLINE_ACLOST        /* OFF-LINE Address claim lost state */
} J1939Nm_OfflineStateType;

/* J1939Nm NodeChannel types */
typedef struct
{
    Nm_ModeType                             NodeChannelMode;
    Nm_StateType                            NodeChannelNetworkModeState;
    J1939Nm_OfflineStateType                NodeChannelOfflineSubState;
    uint8                                   NodeID;  /* ID of the NodeChannel related Node */
} J1939Nm_NodeInfoType;

/* J1939Nm Channel description type */
typedef struct
{
    J1939Nm_NodeInfoType                    NodeChannel[J1939NM_NUMBER_OF_NODES_MAX];
} J1939Nm_ChannelNodeInfoType;


/* definition of pointer to J1939NmUserCallout function  */
typedef void (* J1939Nm_CalloutFunctionPointerType)( VAR(NetworkHandleType, AUTOMATIC) channel,
                                                                        VAR(uint8, AUTOMATIC) sourceAddress,
                                                                        P2CONST(uint8, AUTOMATIC, AUTOMATIC) name
);

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef J1939NM_TYPES_H */
/*==================[end of file]============================================*/
