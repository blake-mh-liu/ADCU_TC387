#ifndef FVT_INTGR_BSWM_OSAPP_1_USERCALLOUTS_H
#define FVT_INTGR_BSWM_OSAPP_1_USERCALLOUTS_H


/*==================[includes]==============================================*/

#include <TSAutosar.h>     /* EB specific standard types */

/*==================[macros]================================================*/

/* BswM states:
 * The values assigned to the macros must be less than or equal to the value
 * you have configured in parameter "BswMRequestedModeMax" of the corresponding
 * BswM mode request port (the value of parameter "BswMModeRequestSource" of
 * this mode request port has to be "BswMGenericRequest"). */
#define BSWM_OS_APP_1_BSWM_SM        1u  /* the BswMModeRequesterId of the BswM state
                                          * machine. */
#if 0
#define EB_INTGR_BSWM_STARTUP_TWO_A  RTE_MODE_BSWM_BswMModeGroup_EB_INTGR_BSWM_STARTUP_TWO_A  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_STARTUP_TWO_B  RTE_MODE_BSWM_BswMModeGroup_EB_INTGR_BSWM_STARTUP_TWO_B  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_RUN_TWO        RTE_MODE_BSWM_BswMModeGroup_EB_INTGR_BSWM_RUN_TWO  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_GO_OFF_ONE_A   RTE_MODE_BSWM_BswMModeGroup_EB_INTGR_BSWM_GO_OFF_ONE_A  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_GO_OFF_ONE_B   RTE_MODE_BSWM_BswMModeGroup_EB_INTGR_BSWM_GO_OFF_ONE_B  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_WAKEUP_TWO     RTE_MODE_BSWM_BswMModeGroup_EB_INTGR_BSWM_WAKEUP_TWO  /*!< ECU state handled by BswM module. */
#else
#define EB_INTGR_BSWM_CORE1_GO_OFF_ONE_A   0u  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_CORE1_GO_OFF_ONE_B   1u  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_CORE1_RUN_TWO        3u  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_CORE1_STARTUP_TWO_A  4u  /*!< ECU state handled by BswM module. */
#define EB_INTGR_BSWM_CORE1_STARTUP_TWO_B  5u  /*!< ECU state handled by BswM module. */
#endif	




/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

extern FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnRunTwo(void);
extern FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnPrpShutdown(void);
extern FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnStartupTwoA(void);
extern FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnStartupTwoB(void);
extern FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnGoOffOneA(void);
extern FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnGoOffOneB(void);


#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>


/*==================[internal function definitions]=========================*/


#endif /* ifndef FVT_INTGR_BSWM_OSAPP_1_USERCALLOUTS_H */

/*==================[end of file]===========================================*/
