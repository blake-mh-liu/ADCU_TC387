/* *--------{ EB Automotive C Source File }-------- */
#ifndef  J1939DCM_H
#define  J1939DCM_H

/*==================[includes]===============================================*/
#include <J1939Dcm_Types.h>
#include <J1939Dcm_PBcfg.h>
#include <J1939Dcm_Cfg.h>
#include <J1939Dcm_Cbk.h>
#include <J1939Dcm_Version.h>

#if (J1939DCM_PBCFGM_SUPPORT_ENABLED == STD_ON)
#include <PbcfgM_PBcfg.h>
#include <PbcfgM_Api.h>
#endif

#include <EcuC.h>

/*==================[macros]=================================================*/
/* Development Error Detection*/
#define J1939DCM_E_INVALID_PDU_SDU_ID           0x01u
#define J1939DCM_E_UNINIT                       0x20u
#define J1939DCM_E_REINIT                       0x21u
#define J1939DCM_E_INVALID_STATE                0x06u
#define J1939DCM_E_INVALID_NODE                 0x08u
#define J1939DCM_E_INVALID_CHANNEL              0x0Bu
#define J1939DCM_E_INVALID_PGN                  0x0Du
#define J1939DCM_E_BUFFER_TOO_SMALL             0x0Eu
#define J1939DCM_E_IF_TX_CONFIRMATION_TIMEOUT   0x30u
#define J1939DCM_E_PARAM_POINTER                0x11u
#define J1939DCM_E_INALID_SDU_LENGTH            0x31u
#define J1939DCM_E_INIT_FAILED                  0x22u
#define J1939DCM_E_WRONG_NODE_CHANNEL_STATE     0x45u

#define J1939DCM_INIT                           0x01u
#define J1939DCM_REQUESTINDICATION              0x43u
#define J1939DCM_RXINDICATION                   0x42u
#define J1939DCM_STARTOFRECEPTION               0x07u
#define J1939DCM_TXCONFIRMATION                 0x40u
#define J1939DCM_MAINFUNCTION                   0x04u
#define J1939DCM_COPYRXDATA                     0x05u
#define J1939DCM_TPRXINDICATION                 0x08u
#define J1939DCM_COPYTXDATA                     0x43u
#define J1939DCM_TPTXCONFIRMATION               0x09u
#define J1939DCM_SETSTATE                       0x0Bu
#define J1939DCM_TRIGGER_ON_DTCSTATUS           0x0Au
#define J1939DCM_GETVERSIONINFO                 0x03u

/*==================[external function declarations]========================*/
#define  J1939DCM_START_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

extern FUNC( Std_ReturnType, J1939DCM_CODE) J1939Dcm_IsValidConfig(P2CONST(void,AUTOMATIC,J1939DCM_APPL_CONST) voidConfigPtr);

extern FUNC(void, J1939DCM_CODE) J1939Dcm_Init( P2CONST(J1939Dcm_ConfigType, AUTOMATIC, J1939DCM_APPL_CONST) configPtr );

extern FUNC(void, J1939DCM_CODE) J1939Dcm_DeInit(void);

extern FUNC(void, J1939DCM_CODE) J1939Dcm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939DCM_VAR) versionInfo);

extern FUNC(void, J1939DCM_CODE) J1939Dcm_MainFunction( void );

#define  J1939DCM_STOP_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

#endif

