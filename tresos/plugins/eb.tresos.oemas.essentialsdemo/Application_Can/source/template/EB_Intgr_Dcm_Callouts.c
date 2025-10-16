/**
 * \file
 *
 * \brief AUTOSAR GenericDemo
 *
 * This file contains the implementation of the AUTOSAR
 * module GenericDemo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#include <TSAutosar.h>     /* EB specific standard types, TS_PARAM_UNUSED() */
#include <Dcm.h>


#define NVM_START_SEC_CONFIG_DATA_APPL_CONST
#include <MemMap.h>
CONST(uint8, NVM_APPL_CONST) DidF190_DefaultData[17]= {0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB,0xEB};
#define NVM_STOP_SEC_CONFIG_DATA_APPL_CONST
#include <MemMap.h>


/* Variable which will be shared with Bootloader.
 * Booloader will check this Variable to verify if the Reset is
 * due to Diagnose Request in Application */
#define PROG_SIG  0x55AA55AAU

#define PROG_REPROG_FLAG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
static uint32 m_ulProgSig;
#define PROG_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>
/*======================== */

FUNC(uint8, DCM_APPL_CODE) Rte_DcmSecGetNumAtt
(
  Dcm_SecLevelType SecurityLevel
)
{
  TS_PARAM_UNUSED(SecurityLevel);

  return 0u;
}

FUNC(void, DCM_APPL_CODE) Rte_DcmSecSetNumAtt
(
  Dcm_SecLevelType SecurityLevel, uint8 NumAtt
)
{
  TS_PARAM_UNUSED(SecurityLevel);
  TS_PARAM_UNUSED(NumAtt);

}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_SetProgConditions
(
  P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions
)
{
  TS_PARAM_UNUSED(ProgConditions);
  /*write diag bootword (PROG_SIG  0x55AA55AAU) on shared init ram*/
  m_ulProgSig = PROG_SIG;
  return E_OK;
}

FUNC(Dcm_EcuStartModeType, DCM_APPL_CODE) Dcm_GetProgConditions
(
  P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions
)
{
  TS_PARAM_UNUSED(ProgConditions);

  return DCM_COLD_START;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DcmDsdSidTabFnc
(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
  TS_PARAM_UNUSED(OpStatus);
  TS_PARAM_UNUSED(pMsgContext);
  return E_NOT_OK;
}
/*Function for successfully flashing the Bootloader while Application is running */
FUNC(Std_ReturnType, DCM_APPL_CODE) PROG_ReqCheckProgPreCondition
(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
  TS_PARAM_UNUSED(OpStatus);
  TS_PARAM_UNUSED(pMsgContext);
  return E_OK;
}
/*Function for successfully flashing the Bootloader while Application is running as this is part of the Nominal Download Test Sequence */
FUNC(Std_ReturnType, DCM_APPL_CODE) PROG_ApplicationPresent
(
    P2VAR(uint8, AUTOMATIC, DCM_VAR) Data
)
{
    *Data = 0xEB;
    return E_OK;
}
