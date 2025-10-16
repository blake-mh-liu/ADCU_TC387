/*==================================================================================================
 * Copyright 2024 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/
#ifndef __ATAN_LOOKUP_TABLE_H__
#define __ATAN_LOOKUP_TABLE_H__

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include <Platform_Types.h>

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define ANGLE2TAN_MAP_SIZE (9001U)

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct LinerKandB_tag
{
    float32 f32KVal;
	float32 f32BVal;
}LinerKandB_ST;

typedef struct AngleMapTanType_tag
{
    float32 f32Angle;
	float32 f32TanVal;
}AngleMapTanType_ST;

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
extern const LinerKandB_ST LinearRelationTable0[70];
extern const LinerKandB_ST LinearRelationTable[45];
extern const AngleMapTanType_ST Angle2TanValMap[ANGLE2TAN_MAP_SIZE];


#endif