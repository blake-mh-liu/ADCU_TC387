/*==================================================================================================
 * Copyright 2025 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/
#ifndef __PMIC_TLF35584_H__
#define __PMIC_TLF35584_H__

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef enum Pmic_SystemModeTypeTag
{
  PMIC_SYS_MODE_INVALID = 0, /* For internal usage only */
  /* NORMAL mode of the system. */
  PMIC_SYS_MODE_NORMAL,
  /* STANDBY mode of the system. */
  PMIC_SYS_MODE_STANDBY,
  /* SLEEP mode of the system. */
  PMIC_SYS_MODE_SLEEP
} Pmic_SystemModeType;

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
void pmic_tlf35584_init(void);

#endif