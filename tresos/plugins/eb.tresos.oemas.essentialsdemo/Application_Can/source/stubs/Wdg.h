/**EB_Automotive_C_Source_File */

#if (!defined WDG_H)
#define WDG_1_EB_H

/*==[Includes]================================================================*/

#include <WdgIf_Types.h>


/*==[Macros]==================================================================*/


/* Wdg_VersionMacros_Dummy */
#define WDG_AR_RELEASE_MAJOR_VERSION 4U
#define WDG_AR_RELEASE_MINOR_VERSION 0U

/*==[Types]===================================================================*/

typedef struct
{
   uint8 PBcfg_dummy;
} Wdg_ConfigType;

/*==[Declaration of functions with external linkage]==========================*/

#define WDG_START_SEC_CODE
#include <MemMap.h>

extern FUNC(void, EBSTUBS_CODE) Wdg_Init
(
  P2CONST(Wdg_ConfigType, AUTOMATIC, EBSTUBS_APPL_CONST) ConfigPtr
);

extern FUNC(Std_ReturnType, WDG_CODE) Wdg_SetMode
(
  WdgIf_ModeType Mode
);

extern FUNC(void, WDG_CODE) Wdg_SetTriggerCondition
(
  uint16 timeout
);


#define WDG_STOP_SEC_CODE
#include <MemMap.h>


#endif /* !defined WDG_1_EB_H */
