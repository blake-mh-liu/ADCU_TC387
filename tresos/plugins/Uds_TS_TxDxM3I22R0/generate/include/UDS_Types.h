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
/*%%   _____________________________   %%  \file UDS_Types.h                     */
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
[!AUTOSPACING!]

#ifndef UDS_TYPES_H
#define UDS_TYPES_H
#include<ComStack_Cfg.h>

/*-------------------------------------------------------------------------------*/
/* - Configuration Constants                                                     */

/** \brief Timer period in milliseconds for the UDS periodic task. Range : (1.. 100) */
#define UDS_MANAGE_PERIOD[!WS "12"!][!"General/UDS_MANAGE_PERIOD"!]U

 /** \brief Specifies the max response length of any DID configured. Range : (Must be greater than zero) */
 #define RDBI_MAX_RESPONSE_LENGTH[!WS "12"!][!"General/RDBI_MAX_RESPONSE_LENGTH"!]U
 
/** \brief Diagnostic services number of the configuration 1 managed by UDS */
#define UDS_SRV_CFG1_MAX[!WS "12"!][!"num:dectoint(count(Service/*))"!]U

/** \brief Diagnostic services number of the configuration 2 managed by UDS */
#define UDS_SRV_CFG2_MAX[!WS "12"!][!"num:dectoint(count(Service_DID/*))"!]U

/** \brief Diagnostic services number of the configuration 3 managed by UDS */
#define UDS_SRV_CFG3_MAX[!WS "12"!][!"num:dectoint(count(Routine_Control/*))"!]U

/** \brief Diagnostic services number of the configuration 5 managed by UDS */
#define UDS_SRV_CFG5_MAX[!WS "12"!][!"num:dectoint(count(Service_OBD/*))"!]U

/** \brief Number of DID allowed on RDBI request */
#define UDS_SRV_CFG_RDBI_MAX[!WS "12"!][!"General/UDS_MAX_DID_MULTI_RDBI"!]U

#define UDS_SECURITY_CHECK_OFF          0U
#define UDS_SECURITY_CHECK_ON           1U

[!IF "General/SecurityCheck = 'true'"!]
#define UDS_SECURITY_CHECK              UDS_SECURITY_CHECK_ON
[!ELSE!]
#define UDS_SECURITY_CHECK              UDS_SECURITY_CHECK_OFF
[!ENDIF!]

#define UDS_TIMEOUT_CHECK_OFF        0U
#define UDS_TIMEOUT_CHECK_ON         1U

[!IF "(node:exists(as:modconf('Uds')/General/UDS_TIMEOUT_CHECK) and as:modconf('Uds')/General/UDS_TIMEOUT_CHECK = 'true')"!]
#define UDS_TIMEOUT_CHECK               UDS_TIMEOUT_CHECK_ON
[!ELSE!]
#define UDS_TIMEOUT_CHECK               UDS_TIMEOUT_CHECK_OFF
[!ENDIF!]

/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */

/** \brief UDS layer TRUE define used for boolean actions in the layer  **/
#define UDS_FALSE       (tUdsBoolean) 0x00U
/** \brief UDS layer FALSE define used for boolean actions in the layer **/
#define UDS_TRUE        (tUdsBoolean) 0x01U
/** \brief Boolean for UDS layer    **/
typedef u8 tUdsBoolean;

/* Diagnostic request reception callbacks status            **/
/** \brief UDS_ACK: Positive answer                         **/
#define UDS_ACK            (tUdsStatus) 0x40U
/** \brief NRC_11: serviceNotSupported                      **/
#define UDS_NRC_11         (tUdsStatus) 0x11U
/** \brief NRC_12: sub-functionNotSupported                 **/
#define UDS_NRC_12         (tUdsStatus) 0x12U
/** \brief NRC_13: incorrectMessageLengthOrInvalidFormat    **/
#define UDS_NRC_13         (tUdsStatus) 0x13U
/** \brief NRC_14: responseTooLong                          **/
#define UDS_NRC_14         (tUdsStatus) 0x14U
/** \brief NRC_21: busyRepeatRequest                        **/
#define UDS_NRC_21         (tUdsStatus) 0x21U
/** \brief NRC_22: conditionsNotCorrect                     **/
#define UDS_NRC_22         (tUdsStatus) 0x22U
/** \brief NRC_24: requestSequenceError                     **/
#define UDS_NRC_24         (tUdsStatus) 0x24U
/** \brief NRC_25: noResponseFromSubnetComponent            **/
#define UDS_NRC_25         (tUdsStatus) 0x25U
/** \brief NRC_26: FailurePreventsExecutionOfRequestedAction **/
#define UDS_NRC_26         (tUdsStatus) 0x26U
/** \brief NRC_31: requestOutOfRange                        **/
#define UDS_NRC_31         (tUdsStatus) 0x31U
/** \brief NRC_33: securityAccessDenied                     **/
#define UDS_NRC_33         (tUdsStatus) 0x33U
/** \brief NRC_35: invalidKey                               **/
#define UDS_NRC_35         (tUdsStatus) 0x35U
/** \brief NRC_36: exceedNumberOfAttempts                   **/
#define UDS_NRC_36         (tUdsStatus) 0x36U
/** \brief NRC_37: requiredTimeDelayNotExpired              **/
#define UDS_NRC_37         (tUdsStatus) 0x37U
/** \brief NRC_70: uploadDownloadNotAccepted                **/
#define UDS_NRC_70         (tUdsStatus) 0x70U
/** \brief NRC_71: transferDataSuspended                    **/
#define UDS_NRC_71         (tUdsStatus) 0x71U
/** \brief NRC_72: generalProgrammingFailure                **/
#define UDS_NRC_72         (tUdsStatus) 0x72U
/** \brief NRC_73: wrongBlockSequenceCounter                **/
#define UDS_NRC_73         (tUdsStatus) 0x73U
/** \brief NRC_78: requestCorrectlyReceived-ResponsePending **/
#define UDS_NRC_78         (tUdsStatus) 0x78U
/** \brief NRC_7E: subfunctionNotSupportedInActiveSession   **/
#define UDS_NRC_7E         (tUdsStatus) 0x7EU
/** \brief NRC_7F: serviceNotSupportedInActiveSession       **/
#define UDS_NRC_7F         (tUdsStatus) 0x7FU

/** NRC for specific conditions that are not correct    **/
/** \brief NRC_81: rpmTooHigh                           **/
#define UDS_NRC_81         (tUdsStatus) 0x81U
/** \brief NRC_82: rpmTooLow                            **/
#define UDS_NRC_82         (tUdsStatus) 0x82U
/** \brief NRC_83: engineIsRunning                      **/
#define UDS_NRC_83         (tUdsStatus) 0x83U
/** \brief NRC_84: engineIsNotRunning                   **/
#define UDS_NRC_84         (tUdsStatus) 0x84U
/** \brief NRC_85: engineRunTimeTooLow                  **/
#define UDS_NRC_85         (tUdsStatus) 0x85U
/** \brief NRC_86: temperatureTooHigh                   **/
#define UDS_NRC_86         (tUdsStatus) 0x86U
/** \brief NRC_87: temperatureTooLow                    **/
#define UDS_NRC_87         (tUdsStatus) 0x87U
/** \brief NRC_88: vehicleSpeedTooHigh                  **/
#define UDS_NRC_88         (tUdsStatus) 0x88U
/** \brief NRC_89: vehicleSpeedTooLow                   **/
#define UDS_NRC_89         (tUdsStatus) 0x89U
/** \brief NRC_8A: throttle/PedalTooHigh                **/
#define UDS_NRC_8A         (tUdsStatus) 0x8AU
/** \brief NRC_8B: throttle/PedalTooLow                 **/
#define UDS_NRC_8B         (tUdsStatus) 0x8BU
/** \brief NRC_8C: transmissionRangeNotInNeutral        **/
#define UDS_NRC_8C         (tUdsStatus) 0x8CU
/** \brief NRC_8D: transmissionRangeNotInGear           **/
#define UDS_NRC_8D         (tUdsStatus) 0x8DU
/** \brief NRC_8F: brakeSwitchNotClosed                 **/
#define UDS_NRC_8F         (tUdsStatus) 0x8FU
/** \brief NRC_90: shifterLeverNotInPark                **/
#define UDS_NRC_90         (tUdsStatus) 0x90U
/** \brief NRC_91: torqueConverterClutchLocked          **/
#define UDS_NRC_91         (tUdsStatus) 0x91U
/** \brief NRC_92: Voltage too high                     **/
#define UDS_NRC_92         (tUdsStatus) 0x92U
/** \brief NRC_93: Voltage too low                      **/
#define UDS_NRC_93         (tUdsStatus) 0x93U

/** \brief SDF UDS error        **/
#define UDS_ERR_COHE       (tUdsStatus) 0xFFU

/** \brief Type of return status for UDS API*/
typedef u8 tUdsStatus;

/* Diagnostic session type */
#define UDS_SESSION_PROT_DEFAULT                SDF_U16_VALUE1
#define UDS_SESSION_PROT_PROGRAMMING            SDF_U16_VALUE2
#define UDS_SESSION_PROT_EXTENDED_DIAG          SDF_U16_VALUE3
#define UDS_SESSION_PROT_SUPPLIER               SDF_U16_VALUE4
#define UDS_SESSION_PROT_OTHER_01               SDF_U16_VALUE5
#define UDS_SESSION_PROT_OTHER_02               SDF_U16_VALUE6
#define UDS_SESSION_PROT_OTHER_03               SDF_U16_VALUE7
#define UDS_SESSION_PROT_OTHER_04               SDF_U16_VALUE8
typedef u16 tUdsSessionProtType;
typedef u8 tUdsSessionType;
typedef u8 tUdsSessionIndex;
/* Changing cause type */
#define UDS_SESSION_CHANGE_REQUESTED            0x00U
#define UDS_SESSION_TIMEOUT                     0x01U
typedef u8 tUdsChangeReason;

/* Diagnostic session index */
#define UDS_DEFAULT_SESSION_INDEX                       0x00U
#define UDS_PROGRAMMING_SESSION_INDEX                       0x01U
#define UDS_EXTENDED_SESSION_INDEX                       0x02U
#define UDS_SUPPLIER_SESSION_INDEX                       0x03U
#define UDS_OTHER_01_SESSION_INDEX                       0x04U
#define UDS_OTHER_02_SESSION_INDEX                       0x05U
#define UDS_OTHER_03_SESSION_INDEX                       0x06U
#define UDS_OTHER_04_SESSION_INDEX                       0x07U

/* Diagnostic session masks, with SDF protection */
#define UDS_SESSION_PROT_DEFAULT_MASK                SDF_U16_VALUE1
#define UDS_SESSION_PROT_PROGRAMMING_MASK            SDF_U16_VALUE2
#define UDS_SESSION_PROT_EXTENDED_DIAG_MASK          SDF_U16_VALUE3
#define UDS_SESSION_PROT_SUPPLIER_MASK               SDF_U16_VALUE4
#define UDS_SESSION_PROT_OTHER_01_MASK               SDF_U16_VALUE5
#define UDS_SESSION_PROT_OTHER_02_MASK               SDF_U16_VALUE6
#define UDS_SESSION_PROT_OTHER_03_MASK               SDF_U16_VALUE7
#define UDS_SESSION_PROT_OTHER_04_MASK               SDF_U16_VALUE8
typedef u16 tUdsSessionProtMask;

/* Diagnostic session masks, without protection, for configuration parameter */
[!/* These values are hardcoded in UDS_Cfg.c to generate Session field code. Any modification shall be apply in both file */!][!AUTOSPACING!]
#define UDS_SESSION_DEFAULT_MASK        (tUdsSessionMask) 0x01U
#define UDS_SESSION_PROGRAMMING_MASK    (tUdsSessionMask) 0x02U
#define UDS_SESSION_EXTENDED_DIAG_MASK  (tUdsSessionMask) 0x04U
#define UDS_SESSION_SUPPLIER_MASK       (tUdsSessionMask) 0x08U
#define UDS_SESSION_OTHER_01_MASK       (tUdsSessionMask) 0x10U
#define UDS_SESSION_OTHER_02_MASK       (tUdsSessionMask) 0x20U
#define UDS_SESSION_OTHER_03_MASK       (tUdsSessionMask) 0x40U
#define UDS_SESSION_OTHER_04_MASK       (tUdsSessionMask) 0x80U
typedef u8 tUdsSessionMask;

#define UDS_CONFIGURABLE_SESSION_MAX             [!"num:i(count(as:modconf('Uds')[1]/Session/*))"!]U

/* Diagnostic session information about P2 and P2Star configured for each session */
typedef struct
{
    u8 ubSessionValue;
    u16 uwP2Val;
    u16 uwP2StarVal;
    tUdsSessionProtType ubSessionProtValue;
    tUdsSessionProtMask ubSessionProtMaskValue;
}tUdsSessionInfo;

/* Long request sequence step */
typedef u8 tUdsLongRequestState;

/* Addressing mode (functionnal or physical) */
#define UDS_ADDR_PHYSICAL       0x01U
#define UDS_ADDR_FUNCTIONAL     0x02U
#define UDS_ADDR_PHYSICAL_FUNCTIONAL     0x03U
typedef u8 tUdsAddrMode;

/* Addressing Type DIAG / OBD */
#define UDS_TYPE_DIAG           0x00U
#define UDS_TYPE_OBD            0x01U
#define UDS_TYPE_DIAG_OBD       0x02U
typedef u8 tUdsAddrType;

/* Diagnostic service index definition
   The type size depends on the number of managed frames */
#if (((UDS_SRV_CFG1_MAX <= U8_MAX) && (UDS_SRV_CFG2_MAX <= U8_MAX)) && ((UDS_SRV_CFG3_MAX <= U8_MAX) && (UDS_SRV_CFG5_MAX <= U8_MAX)))
    typedef u8 tUdsSrvIdx;
#elif (((UDS_SRV_CFG1_MAX <= U16_MAX) && (UDS_SRV_CFG2_MAX <= U16_MAX)) && ((UDS_SRV_CFG3_MAX <= U16_MAX) && (UDS_SRV_CFG5_MAX <= U16_MAX)))
    typedef u16 tUdsSrvIdx;
#elif (((UDS_SRV_CFG1_MAX <= U32_MAX) && (UDS_SRV_CFG2_MAX <= U32_MAX)) && ((UDS_SRV_CFG3_MAX <= U32_MAX) && (UDS_SRV_CFG5_MAX <= U32_MAX)))
    typedef u32 tUdsSrvIdx;
#endif

/* Diagnostic session timeout
   Range : (0 .. 2^32) */
#define UDS_SESS_TIMEOUT         ( 5000U / UDS_MANAGE_PERIOD )

/* Diagnostic session timeout counter definition
   The type size depends on the number of managed frames */
#if (UDS_SESS_TIMEOUT <= U8_MAX)
    typedef u8 tUdsSessionTimeout;
#elif (UDS_SESS_TIMEOUT <= U16_MAX)
    typedef u16 tUdsSessionTimeout;
#elif (UDS_SESS_TIMEOUT <= U32_MAX)
    typedef u32 tUdsSessionTimeout;
#endif 

typedef u16 tRi;

typedef tUdsStatus (* tUdsRxMsgInd) (PduLengthType *pulLen, u8 *aubUdsData);

/* Diagnostic services configuration 1, stored in Read-Only memory */
typedef struct
{
    u8   ubSrvId;                       /* Service value */
    u8   ubSubSrvId;                    /* Sub-service value */
    tUdsSessionMask   eSessionMasks;    /* Session masks for which this service is authorized */
    PduLengthType  ulReqLen;                      /* Sub-service request length */
    u8  ubSecLev;                      /* Security Level */
    tUdsAddrMode ubAddrMode;            /* Mode value (physical / functional / both) */
    tUdsRxMsgInd  pfuRxMsgInd; /* Request reception notification callback */
} tUdsSrvCfg1;

/* Diagnostic services configuration 2, stored in Read-Only memory */
typedef struct
{
    u8   ubSrvId;                       /* Service value */
    u16  uwDid;                        /* Data identifier */
    tUdsSessionMask   eSessionMasks;    /* Session masks for which this service is authorized */
    PduLengthType  ulReqLen;                      /* Sub-service request length */
    u8  ubSecLev;                      /* Security Level */
    tUdsAddrMode ubAddrMode;            /* Mode value (physical / functional / both) */
    tUdsRxMsgInd  pfuRxMsgInd; /* Request reception notification callback */
} tUdsSrvCfg2;

/* Diagnostic services configuration 3, stored in Read-Only memory */
typedef struct
{
    u8   ubSrvId;                       /* Service value */
    u8   ubSubSrvId;                    /* Sub-service value */
    tRi  uwRi;                            /* Routine identifier */
    tUdsSessionMask   eSessionMasks;    /* Session masks for which this service is authorized */
    PduLengthType  ulReqLen;                      /* Sub-service request length */
    u8  ubSecLev;                      /* Security Level */
    tUdsAddrMode ubAddrMode;            /* Mode value (physical / functional / both) */
    tUdsRxMsgInd  pfuRxMsgInd; /* Request reception notification callback */
} tUdsSrvCfg3;

/* Diagnostic services configuration 5, stored in Read-Only memory */
typedef struct
{
    u8   ubSrvId;                       /* Service value */
    PduLengthType  ulReqLen;                      /* Sub-service request length */
    tUdsAddrMode ubAddrMode;            /* Mode value (physical / functional / both) */
    tUdsRxMsgInd  pfuRxMsgInd; /* Request reception notification callback */
} tUdsSrvCfg5;

/* Authorized Diagnostic services identifier */
#define UDS_SRV_DSC              0x10U
#define UDS_SRV_ER               0x11U
#define UDS_SRV_SA               0x27U
#define UDS_SRV_CC               0x28U
#define UDS_SRV_TP               0x3EU
#define UDS_SRV_RC               0x31U
#define UDS_SRV_CDTCS            0x85U
#define UDS_SRV_LC               0x87U
#define UDS_SRV_IOCBI            0x2FU
#define UDS_SRV_ARS              0x29U

#define UDS_SRV_RMBA             0x23U
#define UDS_SRV_RSDBI            0x24U
#define UDS_SRV_WMBA             0x3DU
#define UDS_SRV_CDTCI            0x14U
#define UDS_SRV_RDTCI            0x19U
#define UDS_SRV_RD               0x34U
#define UDS_SRV_RU               0x35U
#define UDS_SRV_TD               0x36U
#define UDS_SRV_RTE              0x37U
#define UDS_SRV_RDBI             0x22U
#define UDS_SRV_WDBI             0x2EU
#define UDS_TEST                 0xABU

/* Supplier services */
#define UDS_SRV_BA               0xBAU
#define UDS_SRV_BB               0xBBU
#define UDS_SRV_BC               0xBCU
#define UDS_SRV_BD               0xBDU
#define UDS_SRV_BE               0xBEU

/* OBD services */
#define UDS_SRV_OBD_SID_00       0x00U
#define UDS_SRV_OBD_SID_01       0x01U
#define UDS_SRV_OBD_SID_02       0x02U
#define UDS_SRV_OBD_SID_03       0x03U
#define UDS_SRV_OBD_SID_04       0x04U
#define UDS_SRV_OBD_SID_05       0x05U
#define UDS_SRV_OBD_SID_06       0x06U
#define UDS_SRV_OBD_SID_07       0x07U
#define UDS_SRV_OBD_SID_08       0x08U
#define UDS_SRV_OBD_SID_09       0x09U
#define UDS_SRV_OBD_SID_10       0x0AU
#define UDS_SRV_OBD_SID_11       0x0BU
#define UDS_SRV_OBD_SID_12       0x0CU
#define UDS_SRV_OBD_SID_13       0x0DU
#define UDS_SRV_OBD_SID_14       0x0EU
#define UDS_SRV_OBD_SID_15       0x0FU


/* Authorized Diagnostic services length */
#define UDS_LEN_NRC              3U

/* Negative code */
#define UDS_NRC                  (u8)0x7FU

/* Long treatment enumeration steps */
#define UDS_LONG_REQ_OFF         0U /* No NACK_78 running */
#define UDS_LONG_REQ_ON          1U /* NACK_78 is sent every UDS_NRC78_PERIOD ms */
#define UDS_LONG_REQ_END         2U /* The real response of the service has been received from the application */

/* SPREC available states */
#define UDS_SPREC_OFF            0U
#define UDS_SPREC_ON             1U

/* SPREC (Session Parameter RECord) functionality */
    [!IF "General/SPREC_IN_RESPONSE = 'true'"!][!AUTOSPACING!]
#define UDS_SPREC   UDS_SPREC_ON
    [!ELSE!][!AUTOSPACING!]
#define UDS_SPREC   UDS_SPREC_OFF
    [!ENDIF!][!AUTOSPACING!]

/* RESPONSE_PENDING available states */
#define UDS_RESPONSE_PENDING_OFF 0U
#define UDS_RESPONSE_PENDING_ON  1U

/* RESPONSE_PENDING (NRC_78) functionality */
    [!IF "General/RESPONSE_PENDING = 'true'"!][!AUTOSPACING!]
#define UDS_RESPONSE_PENDING   UDS_RESPONSE_PENDING_ON
    [!ELSE!][!AUTOSPACING!]
#define UDS_RESPONSE_PENDING   UDS_RESPONSE_PENDING_OFF
    [!ENDIF!][!AUTOSPACING!]

#define TIMER_RESPONSE_PENDING_CHECK_OFF 0U
#define TIMER_RESPONSE_PENDING_CHECK_ON  1U
    [!IF "General/TIMER_RESPONSE_PENDING_CHECK = 'true'"!][!AUTOSPACING!]
#define TIMER_RESPONSE_PENDING_CHECK   TIMER_RESPONSE_PENDING_CHECK_ON
    [!ELSE!][!AUTOSPACING!]
#define TIMER_RESPONSE_PENDING_CHECK   TIMER_RESPONSE_PENDING_CHECK_OFF
    [!ENDIF!][!AUTOSPACING!]
/* RELOAD_TSTOPDIAG available states */
#define UDS_RELOAD_TSTOPDIAG_OFF 0U
#define UDS_RELOAD_TSTOPDIAG_ON  1U

/* RELOAD_TSTOPDIAG functionality */
    [!IF "General/RELOAD_TSTOPDIAG = 'true'"!][!AUTOSPACING!]
#define UDS_RELOAD_TSTOPDIAG   UDS_RELOAD_TSTOPDIAG_ON
    [!ELSE!][!AUTOSPACING!]
#define UDS_RELOAD_TSTOPDIAG   UDS_RELOAD_TSTOPDIAG_OFF
    [!ENDIF!][!AUTOSPACING!]
    
#if (UDS_RESPONSE_PENDING == UDS_RESPONSE_PENDING_ON)
/* Long request behavior enabling */
typedef struct
{
    tUdsLongRequestState m_eState;        /* Sequence step */
    u16 m_ubCnt;                        /* Counter for periodic transmissions */
    u8 m_aubDiagNack78Data[UDS_LEN_NRC]; /* Data buffer for NRC78 only */
    u8 *m_paubData;                    /* Pointer to the TP data buffer */
    PduLengthType m_ulLen;                        /* Final response length */
    tUdsBoolean m_ubtRespPending;         /* A response is pending. Must wait for TxConf before any other response transmission. */
} tUdsLongRequestStr;
#endif
    
#define UDS_CFG_1           0U
#define UDS_CFG_2           1U
#define UDS_CFG_3           2U

#endif      /* UDS_TYPES_H */
