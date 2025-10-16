/* *--------{ EB Automotive C Source File }-------- */
#ifndef J1939DCM_REPORTDTC_H
#define J1939DCM_REPORTDTC_H

/*==================[includes]===============================================*/
#include <J1939Dcm.h>

/*==================[external data]==========================================*/
#if( J1939DCM_REPORTDTCS_AVAILABLE == STD_ON)

#define  J1939DCM_START_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

/* Variable used to store the number of filter DTC's\Records depending on the received sub-function */
extern VAR(uint16, J1939DCM_VAR) J1939Dcm_NumberOfFilteredItems; /* ANALYSIS_REPORT_JUSTIFICATION (2014/10/03 : uidl7595) !-->  TOOL_NUMBER(QAC:777) MISRA(M5.1) It is checked and is ok <--! */

#define  J1939DCM_STOP_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

/*==================[external function declarations]========================*/
extern FUNC(J1939Dcm_DmResponseType, J1939DCM_CODE) J1939Dcm_ReportDTC_RequestProcessing( VAR(J1939Dcm_OpStatusType, AUTOMATIC)OpStatus,
    P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
    VAR(uint8, AUTOMATIC) NodeId ); /* ANALYSIS_REPORT_JUSTIFICATION (2014/10/03 : uidl7595) !-->  TOOL_NUMBER(QAC:777) MISRA(M5.1) It is checked and is ok <--! */

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_REPORTDTCS_AVAILABLE */

#endif  /* Notice: the file ends with a blank new line to avoid compiler warnings */
