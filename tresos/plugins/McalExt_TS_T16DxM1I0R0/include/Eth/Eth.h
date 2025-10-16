/* --------{ EB Automotive C Source File }-------- */

#ifndef ETH_H
#define ETH_H

#include <Eth_17_GEthMacV2.h>


/* needed since the module test do not consider VendorId & VendorApiInfix in all published interfaces */

#define Eth_ControllerInit(tmp1,tmp2)    E_OK 

#define ETH_AR_RELEASE_MAJOR_VERSION     ETH_17_GETHMACV2_AR_RELEASE_MAJOR_VERSION
#define ETH_AR_RELEASE_MINOR_VERSION     ETH_17_GETHMACV2_AR_RELEASE_MINOR_VERSION

/* Global Type Definitions */
typedef Eth_17_GEthMacV2_ConfigType        Eth_ConfigType;

/* Global Function Declarations */

#define Eth_Init                         Eth_17_GEthMacV2_Init
#define Eth_SetControllerMode            Eth_17_GEthMacV2_SetControllerMode
#define Eth_GetControllerMode            Eth_17_GEthMacV2_GetControllerMode
#define Eth_GetPhysAddr                  Eth_17_GEthMacV2_GetPhysAddr
#define Eth_SetPhysAddr                  Eth_17_GEthMacV2_SetPhysAddr
#define Eth_UpdatePhysAddrFilter         Eth_17_GEthMacV2_UpdatePhysAddrFilter
#define Eth_WriteMii                     Eth_17_GEthMacV2_WriteMii
#define Eth_ReadMii                      Eth_17_GEthMacV2_ReadMii
#define Eth_GetDropCount                 Eth_17_GEthMacV2_GetDropCount 
#define Eth_GetEtherStats                Eth_17_GEthMacV2_GetEtherStats
#define Eth_GetCurrentTime       	     Eth_17_GEthMacV2_GetCurrentTime
#define Eth_EnableEgressTimeStamp        Eth_17_GEthMacV2_EnableEgressTimeStamp
#define Eth_GetEgressTimeStamp           Eth_17_GEthMacV2_GetEgressTimeStamp
#define Eth_GetIngressTimeStamp          Eth_17_GEthMacV2_GetIngressTimeStamp
#define Eth_SetCorrectionTime            Eth_17_GEthMacV2_SetCorrectionTime
#define Eth_SetGlobalTime                Eth_17_GEthMacV2_SetGlobalTime
#define Eth_ProvideTxBuffer              Eth_17_GEthMacV2_ProvideTxBuffer
#define Eth_Transmit                     Eth_17_GEthMacV2_Transmit
#define Eth_Receive                      Eth_17_GEthMacV2_Receive
#define Eth_TxConfirmation               Eth_17_GEthMacV2_TxConfirmation
#define Eth_GetVersionInfo               Eth_17_GEthMacV2_GetVersionInfo
#define Eth_MainFunction                 Eth_17_GEthMacV2_MainFunction

#endif /* ETH_H */
