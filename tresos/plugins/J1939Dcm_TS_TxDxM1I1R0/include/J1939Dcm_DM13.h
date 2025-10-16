/* *--------{ EB Automotive C Source File }-------- */
#ifndef J1939DCM_SERV13_H
#define J1939DCM_SERV13_H

/*==================[includes]===============================================*/
#include <J1939Dcm.h>

/*==================[external function declarations]========================*/
#if( J1939DCM_DM13_AVAILABLE == STD_ON )

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>
extern FUNC(void, J1939DCM_CODE) J1939Dcm_DM13_ProcessRequest(uint8 ComMChannelIdx, P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr);

extern FUNC(void, J1939DCM_CODE)J1939Dcm_DM13TimeoutSupervision( void );

extern FUNC(Std_ReturnType, J1939DCM_CODE)J1939Dcm_ValidateMetadata(uint8 tRxDMsIndex);
#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM13_AVAILABLE */

#endif  /* Notice: the file ends with a blank new line to avoid compiler warnings */
