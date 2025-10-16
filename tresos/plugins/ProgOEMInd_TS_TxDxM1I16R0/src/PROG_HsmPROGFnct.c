/* --------{ EB Automotive C Source File }-------- */

/* Implementation of the state handler functions of the state machine
 * PROG.
 *
 * This file contains the implementation of the state functions.  It
 * is generated but must be edited to implement the real actions.  If the
 * state machine model is updated and the code generator regenerates the
 * files the user must manually merge the changes with any existing hand
 * written code.
 */

/* CHECK: RULE 301 OFF (this file is partly generated, some lines may be
 * longer then 100 characters) */

/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.40
 * Do not create incompatible declarations of the same function or object
 *
 * Reason:
 * Two functions are declared to  provide two different functionalities though.
 * they are almost similar in declarations they wont be functional impact.
 */

/*==================[inclusions]============================================*/
#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <PROG_Hsm.h>  /* state machine driver interface */
#include <PROG_HsmPROG.h> /* public statechart model definitions */
#include <PROG_HsmPROGInt.h> /* internal statechart model definitions */
#include <PROG_Guard.h>  /* state machine transitions guards */


/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define PROG_START_SEC_CODE
#include <MemMap.h>

/* ************************ state functions ******************************* */

/* ************************************************************************
 * State: TOP
 * Parent state: none
 * Init substate: PRE_INIT
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: ALIVE
 * Parent state: TOP
 * Init substate: INIT
 * Transitions originating from this state:
 * 1) ALIVE -> PROG_SESSION: PROG_EVENT_OPEN_PROG_SESSION[]/
 * 2) ALIVE -> DEFAULT_SESSION: PROG_EVENT_REQ_DSC01[]/
 * 3) ALIVE -> EXT_SESSION: PROG_EVENT_REQ_DSC03[]/
 * 4) ALIVE -> ECU_RESET: PROG_EVENT_REQ_ER[]/
 * 5) PROG_EVENT_REQ_PRECOND_CHECK[]/(void)PROG_CheckProgrammingPreCondition();
 * 6) ALIVE -> RESET: PROG_EVENT_RESET[]/
 * 7) ALIVE -> RESET: PROG_EVENT_S3_TIMEOUT[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfALIVEAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action '(void)PROG_CheckProgrammingPreCondition();'
   * for PROG_EVENT_REQ_PRECOND_CHECK[]/...
   * internal transition */
  (void)PROG_CheckProgrammingPreCondition();
}

/* ************************************************************************
 * State: CHECK_MEMORY_TOP
 * Parent state: ALIVE
 * Init substate: SIGNATURE_CHECK
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) CHECK_MEMORY_TOP -> ERASE_TOP: PROG_EVENT_REQ_ERASE[(PROG_Custom_Guard_Erase_Check_CheckMemory()==PROG_E_OK)]/
 * 3) PROG_EVENT_REQ_GET_SEED[]/PROG_GetSeed_Unlocked();
 * 4) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 5) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 6) CHECK_MEMORY_TOP -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_TOPAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_TOPGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_Erase_Check_CheckMemory()==PROG_E_OK)'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if((PROG_Custom_Guard_Erase_Check_CheckMemory()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_GetSeed_Unlocked();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_GetSeed_Unlocked();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_TOPAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: BLU_PRE_RESET
 * Parent state: CHECK_MEMORY_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) BLU_PRE_RESET -> RESET: PROG_EVENT_TX_CONF[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfBLU_PRE_RESETEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_SendNRC78();' */
  PROG_SendNRC78();
}

/* ************************************************************************
 * State: BLU_RESUME
 * Parent state: CHECK_MEMORY_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) BLU_RESUME -> CHECK_MEMORY_FINISH: PROG_EVENT_FINISHED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfBLU_RESUMEEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_BLU_Resume();' */
  PROG_Entry_BLU_Resume();
}

/* ************************************************************************
 * State: CHECK_MEMORY
 * Parent state: CHECK_MEMORY_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) CHECK_MEMORY -> BLU_PRE_RESET: PROG_EVENT_BLU_PROGRESS[]/
 * 2) CHECK_MEMORY -> SECUREBOOT_COMPUTE_CHECKSUM: PROG_EVENT_CHECKSUM_UPDATE[]/
 * 3) PROG_EVENT_CRC_FINISH[]/PROG_CheckSegmentListCrc();
 * 4) PROG_EVENT_CRYPTO_FINISH[]/(void)PROG_CRC_Compare();
 * 5) CHECK_MEMORY -> CHECK_MEMORY_FINISH: PROG_EVENT_FAILED[]/
 * 6) CHECK_MEMORY -> CHECK_MEMORY_FINISH: PROG_EVENT_FINISHED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORYEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_CheckMemoryCompute();' */
  PROG_Entry_CheckMemoryCompute();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORYDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action '(void)PROG_CRC();' */
  (void)PROG_CRC();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORYAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_CheckSegmentListCrc();'
   * for PROG_EVENT_CRC_FINISH[]/...
   * internal transition */
  PROG_CheckSegmentListCrc();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORYAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action '(void)PROG_CRC_Compare();'
   * for PROG_EVENT_CRYPTO_FINISH[]/...
   * internal transition */
  (void)PROG_CRC_Compare();
}

/* ************************************************************************
 * State: CHECK_MEMORY_FINISH
 * Parent state: CHECK_MEMORY_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_AnswerSuccesiveCheckMemoryRequests();
 * 2) CHECK_MEMORY_FINISH -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[PROG_Custom_Guard_CheckMemory_CheckProgDep()==PROG_E_OK]/
 * 3) CHECK_MEMORY_FINISH -> REPROG: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_CheckMemory()==PROG_E_OK)]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_CheckMemoryFinish();' */
  PROG_Entry_CheckMemoryFinish();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_FINISHExit(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* exit action 'PROG_Exit_CheckMemoryFinish();' */
  PROG_Exit_CheckMemoryFinish();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_FINISHAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_AnswerSuccesiveCheckMemoryRequests();'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_AnswerSuccesiveCheckMemoryRequests();
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_CheckMemory_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if(PROG_Custom_Guard_CheckMemory_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_MEMORY_FINISHGuard3(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_CheckMemory()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state REPROG */
  if((PROG_Custom_Guard_RD_Check_CheckMemory()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: SECUREBOOT_COMPUTE_CHECKSUM
 * Parent state: CHECK_MEMORY_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) SECUREBOOT_COMPUTE_CHECKSUM -> BLU_PRE_RESET: PROG_EVENT_BLU_PROGRESS[]/
 * 2) PROG_EVENT_FAILED[]/PROG_Entry_SecureChecksumFailed();
 * 3) SECUREBOOT_COMPUTE_CHECKSUM -> CHECK_MEMORY_FINISH: PROG_EVENT_FINISHED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfSECUREBOOT_COMPUTE_CHECKSUMDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_HsmManage();' */
  PROG_HsmManage();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfSECUREBOOT_COMPUTE_CHECKSUMAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Entry_SecureChecksumFailed();'
   * for PROG_EVENT_FAILED[]/...
   * internal transition */
  PROG_Entry_SecureChecksumFailed();
}

/* ************************************************************************
 * State: SIGNATURE_CHECK
 * Parent state: CHECK_MEMORY_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) SIGNATURE_CHECK -> CHECK_MEMORY: PROG_EVENT_CRYPTO_FINISH[]/
 * 2) SIGNATURE_CHECK -> CHECK_MEMORY_FINISH: PROG_EVENT_FAILED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfSIGNATURE_CHECKEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_CheckMemory();' */
  PROG_Entry_CheckMemory();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfSIGNATURE_CHECKExit(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* exit action 'PROG_Exit_CheckMemory();' */
  PROG_Exit_CheckMemory();
}

/* ************************************************************************
 * State: CHECK_PROG_DEPENDENCIES_TOP
 * Parent state: ALIVE
 * Init substate: CHECK_PROG_DEP
 * Transitions originating from this state:
 * 1) CHECK_PROG_DEPENDENCIES_TOP -> COMPARE_KEY: PROG_EVENT_REQ_COMPARE_KEY[PROG_Custom_Guard_CheckProgDep_CompareKey()==PROG_E_OK]/
 * 2) CHECK_PROG_DEPENDENCIES_TOP -> ERASE_TOP: PROG_EVENT_REQ_ERASE[PROG_Custom_Guard_Erase_Check_CheckProgDep()==PROG_E_OK]/
 * 3) PROG_EVENT_REQ_GET_SEED[]/PROG_GetSeed_Unlocked();
 * 4) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 5) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 6) CHECK_PROG_DEPENDENCIES_TOP -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_CheckProgDep_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPGuard1(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_CheckProgDep_CompareKey()==PROG_E_OK'
   * for PROG_EVENT_REQ_COMPARE_KEY[...]/
   * external transition to state COMPARE_KEY */
  if(PROG_Custom_Guard_CheckProgDep_CompareKey()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_Erase_Check_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if(PROG_Custom_Guard_Erase_Check_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_GetSeed_Unlocked();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_GetSeed_Unlocked();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPGuard6(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_CheckProgDep_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_CheckProgDep_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: CHECK_PROG_DEP
 * Parent state: CHECK_PROG_DEPENDENCIES_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) CHECK_PROG_DEP -> CHECK_PROG_DEP_FINISH: PROG_EVENT_FINISHED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEPDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Do_CoherencyCheck();' */
  PROG_Do_CoherencyCheck();
}

/* ************************************************************************
 * State: CHECK_PROG_DEP_FINISH
 * Parent state: CHECK_PROG_DEPENDENCIES_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) CHECK_PROG_DEP_FINISH -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[PROG_Custom_Guard_CheckProgDep_CheckProgDep()==PROG_E_OK]/
 * 3) CHECK_PROG_DEP_FINISH -> REPROG: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_CheckProgDep()==PROG_E_OK)]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEP_FINISHAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEP_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_CheckProgDep_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if(PROG_Custom_Guard_CheckProgDep_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCHECK_PROG_DEP_FINISHGuard3(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_CheckProgDep()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state REPROG */
  if((PROG_Custom_Guard_RD_Check_CheckProgDep()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: COMPARE_KEY
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) COMPARE_KEY -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[(PROG_Custom_Guard_CompareKey_CheckProgDep()==PROG_E_OK)]/
 * 3) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 4) COMPARE_KEY -> ERASE_TOP: PROG_EVENT_REQ_ERASE[(PROG_Custom_Guard_Erase_Check_CompareKey()==PROG_E_OK)]/
 * 5) PROG_EVENT_REQ_GET_SEED[]/PROG_GetSeed_Unlocked();
 * 6) COMPARE_KEY -> RD: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_CompareKey()==PROG_E_OK)]/
 * 7) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 8) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 9) COMPARE_KEY -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_CompareKey_FingerPrint()==PROG_E_OK]/
 * 10) COMPARE_KEY -> LOCKED: PROG_EVENT_UNLOCK_FAILED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_CompareKey();' */
  PROG_Entry_CompareKey();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_CompareKey_CheckProgDep()==PROG_E_OK)'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if((PROG_Custom_Guard_CompareKey_CheckProgDep()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYGuard4(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_Erase_Check_CompareKey()==PROG_E_OK)'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if((PROG_Custom_Guard_Erase_Check_CompareKey()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_GetSeed_Unlocked();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_GetSeed_Unlocked();
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYGuard6(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_CompareKey()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state RD */
  if((PROG_Custom_Guard_RD_Check_CompareKey()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYAction7(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYAction8(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfCOMPARE_KEYGuard9(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_CompareKey_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_CompareKey_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: DEFAULT_SESSION
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) DEFAULT_SESSION -> RESET: PROG_EVENT_TX_CONF[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfDEFAULT_SESSIONEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_DefaultSession();' */
  PROG_Entry_DefaultSession();
}

/* ************************************************************************
 * State: ECU_RESET
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ECU_RESET -> RESET: PROG_EVENT_TX_CONF[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfECU_RESETEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_EcuReset();' */
  PROG_Entry_EcuReset();
}

/* ************************************************************************
 * State: ERASE_TOP
 * Parent state: ALIVE
 * Init substate: ERASE_TRANSMITNRC78
 * Transitions originating from this state:
 * 1) ERASE_TOP -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[PROG_Custom_Guard_EraseMemory_CheckProgDep()==PROG_E_OK]/
 * 2) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 3) PROG_EVENT_REQ_GET_SEED[]/PROG_GetSeed_Unlocked();
 * 4) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 5) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 */

/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfERASE_TOPGuard1(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_EraseMemory_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if(PROG_Custom_Guard_EraseMemory_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_TOPAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_GetSeed_Unlocked();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_GetSeed_Unlocked();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_TOPAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: ERASE
 * Parent state: ERASE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ERASE -> ERASE_FINISH: PROG_EVENT_FINISHED[]/
 * 2) ERASE -> ERASE_NRC78: PROG_EVENT_WAIT_NRC78[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASEEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_Erase();' */
  PROG_Entry_Erase();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASEDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Erase();' */
  PROG_Erase();
}

/* ************************************************************************
 * State: ERASE_CHECK
 * Parent state: ERASE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ERASE_CHECK -> ERASE_FINISH: PROG_EVENT_FINISHED[]/
 * 2) ERASE_CHECK -> ERASE: PROG_EVENT_TX_CONF[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_CHECKEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_EraseCheck();' */
  PROG_Entry_EraseCheck();
}

/* ************************************************************************
 * State: ERASE_FINISH
 * Parent state: ERASE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ERASE_FINISH -> ERASE_TOP: PROG_EVENT_REQ_ERASE[PROG_Custom_Guard_Erase_Check_EraseMemory()==PROG_E_OK]/
 * 2) ERASE_FINISH -> REPROG: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_EraseMemory()==PROG_E_OK)]/
 * 3) ERASE_FINISH -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_EraseMemory_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_EraseFinish();' */
  PROG_Entry_EraseFinish();
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfERASE_FINISHGuard1(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_Erase_Check_EraseMemory()==PROG_E_OK'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if(PROG_Custom_Guard_Erase_Check_EraseMemory()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfERASE_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_EraseMemory()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state REPROG */
  if((PROG_Custom_Guard_RD_Check_EraseMemory()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfERASE_FINISHGuard3(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_EraseMemory_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_EraseMemory_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: ERASE_NRC78
 * Parent state: ERASE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ERASE_NRC78 -> ERASE: PROG_EVENT_TX_CONF[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_NRC78Entry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_EraseNRC78();' */
  PROG_Entry_EraseNRC78();
}

/* ************************************************************************
 * State: ERASE_TRANSMITNRC78
 * Parent state: ERASE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ERASE_TRANSMITNRC78 -> ERASE_CHECK: PROG_EVENT_TX_CONF[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfERASE_TRANSMITNRC78Entry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_EraseTransmitNRC78();' */
  PROG_Entry_EraseTransmitNRC78();
}

/* ************************************************************************
 * State: EXT_SESSION
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) EXT_SESSION -> GET_SEED: PROG_EVENT_REQ_GET_SEED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfEXT_SESSIONEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_ExtendedSession();' */
  PROG_Entry_ExtendedSession();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfEXT_SESSIONAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: GET_SEED
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) PROG_EVENT_REQ_COHERENCY_CHECK[]/PROG_Send_NRC(UDS_NRC_24);
 * 3) GET_SEED -> COMPARE_KEY: PROG_EVENT_REQ_COMPARE_KEY[]/
 * 4) PROG_EVENT_REQ_GET_SEED[]/PROG_Entry_GetSeed();
 * 5) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 6) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 7) PROG_EVENT_REQ_WRITE_FP[]/PROG_Send_NRC(UDS_NRC_24);
 * 8) GET_SEED -> LOCKED: PROG_EVENT_UNLOCK_FAILED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_GetSeed();' */
  PROG_Entry_GetSeed();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Entry_GetSeed();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_Entry_GetSeed();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDAction6(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfGET_SEEDAction7(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_WRITE_FP[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: INIT
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) INIT -> SLEEP: PROG_EVENT_SLEEP[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfINITEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_INIT();' */
  PROG_Entry_INIT();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfINITExit(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* exit action 'PROG_Exit_INIT();' */
  PROG_Exit_INIT();
}

/* ************************************************************************
 * State: LOCKED
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) PROG_EVENT_REQ_COHERENCY_CHECK[]/PROG_Send_NRC(UDS_NRC_24);
 * 3) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 4) LOCKED -> GET_SEED: PROG_EVENT_REQ_GET_SEED[]/
 * 5) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 6) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 7) PROG_EVENT_REQ_WRITE_FP[]/PROG_Send_NRC(UDS_NRC_24);
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfLOCKEDAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfLOCKEDAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfLOCKEDAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfLOCKEDAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfLOCKEDAction6(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfLOCKEDAction7(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_WRITE_FP[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: PROG_SESSION
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_SESSION -> BLU_RESUME: PROG_EVENT_BLU_PROGRESS[]/
 * 2) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 3) PROG_EVENT_REQ_COHERENCY_CHECK[]/PROG_Send_NRC(UDS_NRC_24);
 * 4) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 5) PROG_SESSION -> ERASE_TOP: PROG_EVENT_REQ_ERASE[PROG_Custom_Guard_Erase_Check_ProgSession()==PROG_E_OK]/
 * 6) PROG_SESSION -> GET_SEED: PROG_EVENT_REQ_GET_SEED[]/
 * 7) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 8) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 9) PROG_SESSION -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_ProgSession_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_ProgrammingSession();' */
  PROG_Entry_ProgrammingSession();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONGuard5(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_Erase_Check_ProgSession()==PROG_E_OK'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if(PROG_Custom_Guard_Erase_Check_ProgSession()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONAction7(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONAction8(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfPROG_SESSIONGuard9(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_ProgSession_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_ProgSession_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: REPROG
 * Parent state: ALIVE
 * Init substate: RD
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) PROG_EVENT_REQ_GET_SEED[]/PROG_GetSeed_Unlocked();
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfREPROGAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfREPROGAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_GetSeed_Unlocked();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_GetSeed_Unlocked();
}

/* ************************************************************************
 * State: RD
 * Parent state: REPROG
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) RD -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[PROG_Custom_Guard_RD_CheckProgDep()==PROG_E_OK]/
 * 3) RD -> ERASE_TOP: PROG_EVENT_REQ_ERASE[PROG_Custom_Guard_Erase_Check_RD()==PROG_E_OK]/
 * 4) RD -> REPROG: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_RD()==PROG_E_OK)]/
 * 5) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 6) RD -> TD_TOP: PROG_EVENT_REQ_TD[]/
 * 7) RD -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_RD_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRDEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_RD();' */
  PROG_Entry_RD();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRDAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRDGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_RD_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if(PROG_Custom_Guard_RD_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRDGuard3(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_Erase_Check_RD()==PROG_E_OK'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if(PROG_Custom_Guard_Erase_Check_RD()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRDGuard4(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_RD()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state REPROG */
  if((PROG_Custom_Guard_RD_Check_RD()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRDAction5(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRDGuard7(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_RD_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_RD_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: RTE_TOP
 * Parent state: REPROG
 * Init substate: RTE
 * Transitions originating from this state:
 * 1) RTE_TOP -> ERASE_TOP: PROG_EVENT_REQ_ERASE[(PROG_Custom_Guard_Erase_Check_RTE()==PROG_E_OK)]/
 * 2) RTE_TOP -> REPROG: PROG_EVENT_REQ_RD[(PROG_E_OK==PROG_RD_Check())]/
 * 3) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 4) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 * 5) RTE_TOP -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_RTE_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRTE_TOPGuard1(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_Erase_Check_RTE()==PROG_E_OK)'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if((PROG_Custom_Guard_Erase_Check_RTE()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRTE_TOPGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_E_OK==PROG_RD_Check())'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state REPROG */
  if((PROG_E_OK==PROG_RD_Check()))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRTE_TOPGuard5(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_RTE_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_RTE_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: RTE
 * Parent state: RTE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) RTE -> RTE_DECRYPT: PROG_EVENT_CRYPTO_FINISH[]/
 * 2) RTE -> RTE_FAILED: PROG_EVENT_FAILED[]/
 * 3) RTE -> RTE_FINISH: PROG_EVENT_FINISHED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTEEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_RTE();' */
  PROG_Entry_RTE();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTEDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action '(void)PROG_VerificationOnTheFly(PROG_RTE_CALL);' */
  (void)PROG_VerificationOnTheFly(PROG_RTE_CALL);
}

/* ************************************************************************
 * State: RTE_DECRYPT
 * Parent state: RTE_TOP
 * Init substate: RTE_DECRYPT_FINISH
 * Transitions originating from this state:
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_DECRYPTExit(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* exit action 'PROG_Exit_RTE_Decrypt();' */
  PROG_Exit_RTE_Decrypt();
}

/* ************************************************************************
 * State: RTE_DECRYPT_FINISH
 * Parent state: RTE_DECRYPT
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) RTE_DECRYPT_FINISH -> RTE_WRITE: PROG_EVENT_WRITE[]/
 * 2) RTE_DECRYPT_FINISH -> RTE_WRITE_CHECK: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_DECRYPT_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_DecryptionFinish();' */
  PROG_Entry_DecryptionFinish();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_DECRYPT_FINISHDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Do_DecryptionFinish();' */
  PROG_Do_DecryptionFinish();
}

/* ************************************************************************
 * State: RTE_WRITE
 * Parent state: RTE_DECRYPT
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) RTE_WRITE -> RTE_WRITE_CHECK: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_WRITEEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_Write();' */
  PROG_Entry_Write();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_WRITEDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Write();' */
  PROG_Write();
}

/* ************************************************************************
 * State: RTE_WRITE_CHECK
 * Parent state: RTE_DECRYPT
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) RTE_WRITE_CHECK -> RTE: PROG_EVENT_TD_END[]/
 * 2) RTE_WRITE_CHECK -> RTE_WRITE: PROG_EVENT_WRITE[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_WRITE_CHECKDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_WriteCheck();' */
  PROG_WriteCheck();
}

/* ************************************************************************
 * State: RTE_FAILED
 * Parent state: RTE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_FAILEDEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_RTEFailed();' */
  PROG_Entry_RTEFailed();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_FAILEDDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Send_NRC(UDS_NRC_24);' */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: RTE_FINISH
 * Parent state: RTE_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) RTE_FINISH -> CHECK_MEMORY_TOP: PROG_EVENT_REQ_CHECKMEMORY[PROG_Custom_Guard_RTE_CheckMemory()==PROG_E_OK]/
 * 2) RTE_FINISH -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[PROG_Custom_Guard_RTE_CheckProgDep()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRTE_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_RTEFinish();' */
  PROG_Entry_RTEFinish();
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRTE_FINISHGuard1(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_RTE_CheckMemory()==PROG_E_OK'
   * for PROG_EVENT_REQ_CHECKMEMORY[...]/
   * external transition to state CHECK_MEMORY_TOP */
  if(PROG_Custom_Guard_RTE_CheckMemory()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfRTE_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_RTE_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if(PROG_Custom_Guard_RTE_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: TD_TOP
 * Parent state: REPROG
 * Init substate: TD
 * Transitions originating from this state:
 * 1) TD_TOP -> TD_FAILED: PROG_EVENT_FAILED[]/
 * 2) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 3) TD_TOP -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[PROG_Custom_Guard_TD_CheckProgDep()==PROG_E_OK]/
 * 4) TD_TOP -> ERASE_TOP: PROG_EVENT_REQ_ERASE[PROG_Custom_Guard_Erase_Check_TD()==PROG_E_OK]/
 * 5) TD_TOP -> RD: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_TD()==PROG_E_OK)]/
 * 6) TD_TOP -> RTE_TOP: PROG_EVENT_REQ_RTE[]/
 * 7) TD_TOP -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_TD_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_TOPAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfTD_TOPGuard3(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_TD_CheckProgDep()==PROG_E_OK'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if(PROG_Custom_Guard_TD_CheckProgDep()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfTD_TOPGuard4(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_Erase_Check_TD()==PROG_E_OK'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if(PROG_Custom_Guard_Erase_Check_TD()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfTD_TOPGuard5(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_TD()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state RD */
  if((PROG_Custom_Guard_RD_Check_TD()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfTD_TOPGuard7(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_TD_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_TD_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: TD
 * Parent state: TD_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) TD -> TD_WRITE: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTDEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_TD();' */
  PROG_Entry_TD();
}

/* ************************************************************************
 * State: TD_CRC
 * Parent state: TD_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) TD_CRC -> TD: PROG_EVENT_REQ_TD[]/
 * 2) TD_CRC -> TD_STREAMING: PROG_EVENT_STREAMING[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_CRCDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action '(void)PROG_VerificationOnTheFly(PROG_TD_CALL);' */
  (void)PROG_VerificationOnTheFly(PROG_TD_CALL);
}

/* ************************************************************************
 * State: TD_FAILED
 * Parent state: TD_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) TD_FAILED -> TD: PROG_EVENT_REQ_TD[]/
 * 2) TD_FAILED -> TD_STREAMING: PROG_EVENT_STREAMING[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_FAILEDEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_TD_Failed();' */
  PROG_Entry_TD_Failed();
}

/* ************************************************************************
 * State: TD_STREAMING
 * Parent state: TD_TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) TD_STREAMING -> TD_WRITE: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_STREAMINGEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_Streaming();' */
  PROG_Entry_Streaming();
}

/* ************************************************************************
 * State: TD_WRITE
 * Parent state: TD_TOP
 * Init substate: DECRYPT_UPDATE
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_TD[]/(void)PROG_TD();
 * 2) PROG_EVENT_STREAMING[]/PROG_Streaming();
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_WRITEExit(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* exit action 'PROG_Exit_TD_Write();' */
  PROG_Exit_TD_Write();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_WRITEAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action '(void)PROG_TD();'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  (void)PROG_TD();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfTD_WRITEAction2(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Streaming();'
   * for PROG_EVENT_STREAMING[]/...
   * internal transition */
  PROG_Streaming();
}

/* ************************************************************************
 * State: DECRYPT_FINISH
 * Parent state: TD_WRITE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) DECRYPT_FINISH -> WRITE: PROG_EVENT_WRITE[]/
 * 2) DECRYPT_FINISH -> WRITE_CHECK: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfDECRYPT_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_DecryptionFinish();' */
  PROG_Entry_DecryptionFinish();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfDECRYPT_FINISHDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Do_DecryptionFinish();' */
  PROG_Do_DecryptionFinish();
}

/* ************************************************************************
 * State: DECRYPT_UPDATE
 * Parent state: TD_WRITE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) DECRYPT_UPDATE -> WRITE_CHECK: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfDECRYPT_UPDATEEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_DecryptionUpdate();' */
  PROG_Entry_DecryptionUpdate();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfDECRYPT_UPDATEDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Do_DecryptionUpdate();' */
  PROG_Do_DecryptionUpdate();
}

/* ************************************************************************
 * State: WRITE
 * Parent state: TD_WRITE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WRITE -> WRITE_CHECK: PROG_EVENT_WRITE_CHECK[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITEEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_Write();' */
  PROG_Entry_Write();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITEDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_Write();' */
  PROG_Write();
}

/* ************************************************************************
 * State: WRITE_CHECK
 * Parent state: TD_WRITE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WRITE_CHECK -> DECRYPT_FINISH: PROG_EVENT_CRYPTO_FINISH[]/
 * 2) WRITE_CHECK -> TD_CRC: PROG_EVENT_TD_END[]/
 * 3) WRITE_CHECK -> WRITE: PROG_EVENT_WRITE[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITE_CHECKDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_WriteCheck();' */
  PROG_WriteCheck();
}

/* ************************************************************************
 * State: RESET
 * Parent state: ALIVE
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfRESETEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_Reset();' */
  PROG_Entry_Reset();
}

/* ************************************************************************
 * State: WRITE_FINGERPRINT
 * Parent state: ALIVE
 * Init substate: WFP_INPROGRESS
 * Transitions originating from this state:
 * 1) PROG_EVENT_REQ_CHECKMEMORY[]/PROG_Send_NRC(UDS_NRC_24);
 * 2) WRITE_FINGERPRINT -> CHECK_PROG_DEPENDENCIES_TOP: PROG_EVENT_REQ_COHERENCY_CHECK[(PROG_Custom_Guard_FingerPrint_CheckProgDep()==PROG_E_OK)]/
 * 3) PROG_EVENT_REQ_COMPARE_KEY[]/PROG_Send_NRC(UDS_NRC_24);
 * 4) PROG_EVENT_REQ_GET_SEED[]/PROG_GetSeed_Unlocked();
 * 5) WRITE_FINGERPRINT -> RD: PROG_EVENT_REQ_RD[(PROG_Custom_Guard_RD_Check_FingerPrint()==PROG_E_OK)]/
 * 6) PROG_EVENT_REQ_RTE[]/PROG_Send_NRC(UDS_NRC_24);
 * 7) PROG_EVENT_REQ_TD[]/PROG_Send_NRC(UDS_NRC_24);
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTAction1(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_CHECKMEMORY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_FingerPrint_CheckProgDep()==PROG_E_OK)'
   * for PROG_EVENT_REQ_COHERENCY_CHECK[...]/
   * external transition to state CHECK_PROG_DEPENDENCIES_TOP */
  if((PROG_Custom_Guard_FingerPrint_CheckProgDep()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTAction3(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_COMPARE_KEY[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTAction4(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_GetSeed_Unlocked();'
   * for PROG_EVENT_REQ_GET_SEED[]/...
   * internal transition */
  PROG_GetSeed_Unlocked();
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTGuard5(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition '(PROG_Custom_Guard_RD_Check_FingerPrint()==PROG_E_OK)'
   * for PROG_EVENT_REQ_RD[...]/
   * external transition to state RD */
  if((PROG_Custom_Guard_RD_Check_FingerPrint()==PROG_E_OK))
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTAction6(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_RTE[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWRITE_FINGERPRINTAction7(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* action 'PROG_Send_NRC(UDS_NRC_24);'
   * for PROG_EVENT_REQ_TD[]/...
   * internal transition */
  PROG_Send_NRC(UDS_NRC_24);
}

/* ************************************************************************
 * State: WFP_FINISHED
 * Parent state: WRITE_FINGERPRINT
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WFP_FINISHED -> ERASE_TOP: PROG_EVENT_REQ_ERASE[PROG_Custom_Guard_Erase_Check_Fingerprint()==PROG_E_OK]/
 * 2) WFP_FINISHED -> WRITE_FINGERPRINT: PROG_EVENT_REQ_WRITE_FP[PROG_Custom_Guard_FingerPrint_FingerPrint()==PROG_E_OK]/
 */

/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfWFP_FINISHEDGuard1(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_Erase_Check_Fingerprint()==PROG_E_OK'
   * for PROG_EVENT_REQ_ERASE[...]/
   * external transition to state ERASE_TOP */
  if(PROG_Custom_Guard_Erase_Check_Fingerprint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}
/* Deviation CERTC-1 */
FUNC(boolean, PROG_CODE) PROG_HsmPROGSfWFP_FINISHEDGuard2(
  PROG_PDL_SF(const uint8 instIdx))
{
  boolean RetVal;
  /* guard condition 'PROG_Custom_Guard_FingerPrint_FingerPrint()==PROG_E_OK'
   * for PROG_EVENT_REQ_WRITE_FP[...]/
   * external transition to state WRITE_FINGERPRINT */
  if(PROG_Custom_Guard_FingerPrint_FingerPrint()==PROG_E_OK)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/* ************************************************************************
 * State: WFP_INPROGRESS
 * Parent state: WRITE_FINGERPRINT
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WFP_INPROGRESS -> WFP_FINISHED: PROG_EVENT_FINISHED[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWFP_INPROGRESSEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_WriteFingerprint();' */
  PROG_Entry_WriteFingerprint();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfWFP_INPROGRESSDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_WriteFingerprintCheck();' */
  PROG_WriteFingerprintCheck();
}

/* ************************************************************************
 * State: PRE_INIT
 * Parent state: TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PRE_INIT -> ALIVE: PROG_EVENT_INIT[]/
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPRE_INITEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_PreInit();' */
  PROG_Entry_PreInit();
}
/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfPRE_INITDo(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* do action 'PROG_PreInit();' */
  PROG_PreInit();
}

/* ************************************************************************
 * State: SLEEP
 * Parent state: TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

/* Deviation CERTC-1 */
FUNC(void, PROG_CODE) PROG_HsmPROGSfSLEEPEntry(
  PROG_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PROG_Entry_Sleep();' */
  PROG_Entry_Sleep();
}


/*==================[internal function definitions]=========================*/


#define PROG_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
