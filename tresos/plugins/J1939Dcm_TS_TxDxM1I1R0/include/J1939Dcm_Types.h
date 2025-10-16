/* *--------{ EB Automotive C Source File }-------- */
#ifndef  J1939DCM_TYPES_H
#define  J1939DCM_TYPES_H

/*==================[includes]===============================================*/


/* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00086,1 */
#include <ComStack_Types.h>
#include <TSPBConfig_Signature.h>
/* types from configuration */
#include <J1939Dcm_CfgTypes.h>
/*==================[macros]=================================================*/
#define J1939DCM_INSTANCE_ID                         (uint8)0x00u         /**< The Instance ID for the J1939DCM used for det error reporting */
/* possible return values of DM processing function */
/* DM processing OK */
#define J1939DCM_DM_FUNCTION_OK        ((J1939Dcm_DmResponseType)0x00)
/* DM processing NOT OK */
#define J1939DCM_DM_FUNCTION_NOT_OK    ((J1939Dcm_DmResponseType)0x01)
/* DM processing PENDING */
#define J1939DCM_DM_FUNCTION_PENDING   ((J1939Dcm_DmResponseType)0x02)
/* DM processing NOT READY */
#define J1939DCM_DM_FUNCTION_NOT_READY ((J1939Dcm_DmResponseType)0x03)

/* possible types of responses needed for a DM */
#define J1939DCM_NO_RESPONSE         ((J1939Dcm_ResponseType)0x00 )
#define J1939DCM_NORMAL_RESPONSE    ((J1939Dcm_ResponseType)0x01 )
#define J1939DCM_ACK_RESPONSE    ((J1939Dcm_ResponseType)0x02 )

/*==================[type definitions]=======================================*/
/* response type for the DM processing function */
typedef uint8 J1939Dcm_DmResponseType;

typedef uint8 J1939Dcm_ResponseType;

typedef uint8 J1939Dcm_OpStatusType;

/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00123,1  */
/* * This type represents the communication state of the J1939 Diagnostic
Communication Manager */
typedef uint8 J1939Dcm_StateType;

#define J1939DCM_STATE_ONLINE       ((J1939Dcm_StateType)0x00U)  /* * Normal communication (0) */
#define J1939DCM_STATE_OFFLINE      ((J1939Dcm_StateType)0x01U)  /* * No diagnostic communication (1) */

/* This type represents the available kinds of internal acknowledgments in J1939Dcm .*/
/* J1939Dcm ack codes created to remove dependency between J1939Dcm and J1939Rm Types */
typedef enum {
    J1939DCM_ACK_POSITIVE,         /* * Positive Acknowledgment (0) */
    J1939DCM_ACK_NEGATIVE,         /* * Negative Acknowledgment (1) */
    J1939DCM_ACK_DEFAULT          /* * Default Acknowledgment (2) */
} J1939Dcm_AckCodeType;

/* Contains information necessary to process a diagnostic message from request to response and
 *   response confirmation. */
typedef  struct {
    P2VAR(uint8, J1939DCM_VAR, J1939DCM_VAR) resData; /* The response of each DM will be stored here. */
    VAR(J1939Dcm_AckCodeType, J1939DCM_VAR) Acknowledge;  /* DM Acknowledge type */
    VAR(J1939Dcm_MsgLenType, J1939DCM_VAR) resDataLen;  /* Response data length, to be updated by DM processing function */
    /* Maximum Response data length, handled by J1939Dcm core */
    /* DM processing function shall not write more in the response data bytes than */
    VAR(J1939Dcm_MsgLenType, J1939DCM_VAR) resMaxDataLen;  /* maximum available resMaxDataLen */
    VAR(J1939Dcm_ResponseType, J1939DCM_VAR) Response; /* DM response type */
    VAR(uint8, J1939DCM_VAR) DMIdx;   /* stores the index of the requested DM in the J1939Dcm_ConfiguredDMs table */
}J1939Dcm_MsgContextType;



#endif /* J1939DCM_TYPES_H */

