#ifndef CANTRCVCALLOUTSTUBS_H
#define CANTRCVCALLOUTSTUBS_H
/**
 * \file
 *
 * \brief Simulated shutdown by software
 *
 * This file contains the declarations of a simulated shutdown and wakeup
 * by Nm frame in software. Normally this is done by external hardware.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*#warning Simulated wakeup and shutdown stub is used.*/

/*==[Includes]================================================================*/

#include <Std_Types.h>                  /* AUTOSAR standard types        */

/*==[Declaration of functions with external linkage]==========================*/

extern FUNC(void, ECUM_APPL_CODE) CanTrcv_Callout_SimulatedShutDown(void);
extern FUNC(void, ECUM_APPL_CODE) CanTrcv_Callout_SimulatedWakeup(void);

#endif /* CANTRCVCALLOUTSTUBS_H */
