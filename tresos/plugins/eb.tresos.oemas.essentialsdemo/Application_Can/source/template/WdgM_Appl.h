/**EB_Automotive_C_Source_File */

/*
#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program must not be used in connection with series production"
#endif
*/

#ifndef WDGM_APPL_H
#define WDGM_APPL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include <Std_Types.h>     /* AUTOSAR standard types */

/*******************************************************************************
**                      external function declarations                        **
*******************************************************************************/

#define WDGM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, WDGM_APPL_CODE) WdgM_Appl_WdgM_TriggerTaskCom(void);

#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* WDGM_APPL_H                                                         */

/*** End of file **************************************************************/

