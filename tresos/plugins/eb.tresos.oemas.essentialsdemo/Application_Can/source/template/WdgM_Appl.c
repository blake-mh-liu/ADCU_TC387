/**EB_Automotive_C_Source_File */

/*
#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program must not be used in connection with series production"
#endif
*/

#include <WdgM_Appl.h>
#include <Std_Types.h>            /* AUTOSAR Standard Types                   */
#include <WdgM.h>                 /* AUTOSAR WdgM                             */

#define WDGM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                                                                            **
** FUNC-NAME     : WdgM_Appl_TriggerTaskCom                                   **
**                                                                            **
** DESCRIPTION   : Triggers the Watchdog in the Task_Com                      **
**                                                                            **
** PRECONDITIONS : ---                                                        **
**                                                                            **
** GLOBAL DATA   : ---                                                        **
**                                                                            **
** PARAMETER     : ---                                                        **
**                                                                            **
** RETURN        : ---                                                        **
**                                                                            **
** REMARKS       : ---                                                        **
**                                                                            **
*******************************************************************************/
FUNC(void, WDGM_APPL_CODE) WdgM_Appl_WdgM_TriggerTaskCom(void)
{
  WdgM_CheckpointReached
  (
      WdgMConf_WdgMSupervisedEntity_WDGM_SE_TASK_Com,
      WdgMConf_WdgMCheckpoint_WdgMCheckpoint_TASK_Com
  );
}

#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*** End of file **************************************************************/

