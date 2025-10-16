/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Types.h                      */
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




#ifndef BM_TYPES_H
#define BM_TYPES_H

[!IF "node:exists(as:modconf('BlPduR'))"!]
  [!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]
typedef u16 tBMNetworkStatus;
#define BM_FR_NS_INIT               0x0000U
#define BM_FR_NS_NORMAL             0x0001U
#define BM_FR_NS_BOOT               0x1000U
#define BM_FR_NS_UNDEFINED          0x2000U

typedef u8 tBMFRStatus;
#define BM_FR_NOTHING_REQUESTED     0U
#define BM_FR_BOOT_REQUESTED        1U
#define BM_FR_APPLI_REQUESTED       2U

typedef u8 tBMCycleCount;
[!ENDIF!]
[!ELSE!]
  [!IF "node:exists(as:modconf('EB'))"!]
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]
 typedef u16 tBMNetworkStatus;
 #define BM_FR_NS_INIT               0x0000U
 #define BM_FR_NS_NORMAL             0x0001U
 #define BM_FR_NS_BOOT               0x1000U
 #define BM_FR_NS_UNDEFINED          0x2000U

 typedef u8 tBMFRStatus;
 #define BM_FR_NOTHING_REQUESTED     0U
 #define BM_FR_BOOT_REQUESTED        1U
 #define BM_FR_APPLI_REQUESTED       2U

 typedef u8 tBMCycleCount;
    [!ENDIF!]
  [!ENDIF!]
[!ENDIF!]
typedef u8 tBMTimeout;

typedef u8 tBMBoolean;
#define BM_FALSE                    0U
#define BM_TRUE                     1U

#define BM_BOOT_MANAGER             0U
#define BM_INITIAL_BOOT_MANAGER     1U

typedef u8 tBMHsmJobResult;
#define BM_HSM_JOB_OK               0U
#define BM_HSM_JOB_FAILED           1U
#define BM_HSM_JOB_PENDING          2U

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Boot Manager""!]
  [!IF "node:exists(as:modconf('CryIf'))"!]
#define Csm_ReturnType              Std_ReturnType
#define CSM_E_OK                    E_OK
#define CSM_E_NOT_OK                E_NOT_OK
#define Csm_VerifyResultType        Crypto_VerifyResultType
#define CSM_E_VER_OK                CRYPTO_E_VER_OK
#define CSM_E_VER_NOT_OK            CRYPTO_E_VER_NOT_OK
  [!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager""!]
  [!IF "as:modconf('BM')/General/Initial_Boot_Check_Application = 'true'"!]
typedef void (*ptAPPL_START_ADDR)(void);
  [!ENDIF!]
typedef void (*ptBLU_START_ADDR)(void);
typedef void (*ptBL_START_ADDR)(void);
[!ENDIF!]

#endif      /* BM_TYPES_H */

