/* *--------{ EB Automotive C Source File }-------- */
#ifndef J1939DCM_SERV26_H
#define J1939DCM_SERV26_H

/*==================[includes]===============================================*/
#include <J1939Dcm.h>

/*==================[external function declarations]========================*/
#if( J1939DCM_DM26_AVAILABLE == STD_ON )

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

extern FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_DM26_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
                                                    P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                                    VAR(uint8, AUTOMATIC) NodeId );

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM26_AVAILABLE */

#endif  /* Notice: the file ends with a blank new line to avoid compiler warnings */
