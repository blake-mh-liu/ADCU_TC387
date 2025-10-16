/*==================================================================================================
 * Copyright 2024 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/
#ifndef __CDD_ADC_LOOKUP_TABLE_H__
#define __CDD_ADC_LOOKUP_TABLE_H__

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define MOTOR_TEMP_TABLE_SIZE    (251u)
#define OIL_TEMP_TABLE_SIZE      (20u)
#define PCB_TEMP_TABLE_SIZE      (201u)
#define SIC_TEMP_TABLE_SIZE      (221u)

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    float32 temp;
    float32 volt;
}EvAdc_stTempVoltPairType;

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
extern const EvAdc_stTempVoltPairType c_stMotorTempVoltageTable[MOTOR_TEMP_TABLE_SIZE];
extern const EvAdc_stTempVoltPairType c_stOilTempVoltageTable[OIL_TEMP_TABLE_SIZE];
extern const EvAdc_stTempVoltPairType c_stPCBTempVoltageTable[PCB_TEMP_TABLE_SIZE];
extern const EvAdc_stTempVoltPairType c_stSICTempVoltageTable[SIC_TEMP_TABLE_SIZE];

#endif