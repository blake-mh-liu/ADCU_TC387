
#ifndef PROG_HSMPROGINT_H
#define PROG_HSMPROGINT_H

/* --------{ EB Automotive C Source File }-------- */

/* Internal interface for the PROG state
 * machine.
 *
 * This header must only be included by
 * PROG_HsmPROGData.c and PROG_HsmPROGFnct.c.
 */

/* CHECK: RULE 301 OFF (this file is generated, some lines may be longer then
 * 100 characters) */

/* NOCOV List
 *
 * NOCOV-TEMPLATE:
 *
 * Reason:
 * The file is a generated from a generic template that does not
 * respect all the OsekCore rules.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <PROG_Hsm.h>

/*==================[macros]================================================*/
/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */

/*==================[type definitions]======================================*/

/* *** State indices and IDs for states *** */
typedef enum
{
  PROG_HSM_PROG_SIDX_TOP,
  PROG_HSM_PROG_SIDX_ALIVE,
  PROG_HSM_PROG_SIDX_CHECK_MEMORY_TOP,
  PROG_HSM_PROG_SIDX_BLU_PRE_RESET,
  PROG_HSM_PROG_SIDX_BLU_RESUME,
  PROG_HSM_PROG_SIDX_CHECK_MEMORY,
  PROG_HSM_PROG_SIDX_CHECK_MEMORY_FINISH,
  PROG_HSM_PROG_SIDX_SECUREBOOT_COMPUTE_CHECKSUM,
  PROG_HSM_PROG_SIDX_SIGNATURE_CHECK,
  PROG_HSM_PROG_SIDX_CHECK_PROG_DEPENDENCIES_TOP,
  PROG_HSM_PROG_SIDX_CHECK_PROG_DEP,
  PROG_HSM_PROG_SIDX_CHECK_PROG_DEP_FINISH,
  PROG_HSM_PROG_SIDX_COMPARE_KEY,
  PROG_HSM_PROG_SIDX_DEFAULT_SESSION,
  PROG_HSM_PROG_SIDX_ECU_RESET,
  PROG_HSM_PROG_SIDX_ERASE_TOP,
  PROG_HSM_PROG_SIDX_ERASE,
  PROG_HSM_PROG_SIDX_ERASE_CHECK,
  PROG_HSM_PROG_SIDX_ERASE_FINISH,
  PROG_HSM_PROG_SIDX_ERASE_NRC78,
  PROG_HSM_PROG_SIDX_ERASE_TRANSMITNRC78,
  PROG_HSM_PROG_SIDX_EXT_SESSION,
  PROG_HSM_PROG_SIDX_GET_SEED,
  PROG_HSM_PROG_SIDX_INIT,
  PROG_HSM_PROG_SIDX_LOCKED,
  PROG_HSM_PROG_SIDX_PROG_SESSION,
  PROG_HSM_PROG_SIDX_REPROG,
  PROG_HSM_PROG_SIDX_RD,
  PROG_HSM_PROG_SIDX_RTE_TOP,
  PROG_HSM_PROG_SIDX_RTE,
  PROG_HSM_PROG_SIDX_RTE_DECRYPT,
  PROG_HSM_PROG_SIDX_RTE_DECRYPT_FINISH,
  PROG_HSM_PROG_SIDX_RTE_WRITE,
  PROG_HSM_PROG_SIDX_RTE_WRITE_CHECK,
  PROG_HSM_PROG_SIDX_RTE_FAILED,
  PROG_HSM_PROG_SIDX_RTE_FINISH,
  PROG_HSM_PROG_SIDX_TD_TOP,
  PROG_HSM_PROG_SIDX_TD,
  PROG_HSM_PROG_SIDX_TD_CRC,
  PROG_HSM_PROG_SIDX_TD_FAILED,
  PROG_HSM_PROG_SIDX_TD_STREAMING,
  PROG_HSM_PROG_SIDX_TD_WRITE,
  PROG_HSM_PROG_SIDX_DECRYPT_FINISH,
  PROG_HSM_PROG_SIDX_DECRYPT_UPDATE,
  PROG_HSM_PROG_SIDX_WRITE,
  PROG_HSM_PROG_SIDX_WRITE_CHECK,
  PROG_HSM_PROG_SIDX_RESET,
  PROG_HSM_PROG_SIDX_WRITE_FINGERPRINT,
  PROG_HSM_PROG_SIDX_WFP_FINISHED,
  PROG_HSM_PROG_SIDX_WFP_INPROGRESS,
  PROG_HSM_PROG_SIDX_PRE_INIT,
  PROG_HSM_PROG_SIDX_SLEEP,
  PROG_HSM_PROG_NO_OF_STATES
} PROG_HsmPROGStateIdType;
/* typedefed type only used for debugging */

/* *** IDs for entry/do/exit and transition actions *** */
typedef enum
{
  PROG_HSM_PROG_AIDX_ALIVE_ACTION_5,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_TOP_ACTION_1,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_TOP_ACTION_3,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_TOP_ACTION_4,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_TOP_ACTION_5,
  PROG_HSM_PROG_AIDX_BLU_PRE_RESET_ENTRY,
  PROG_HSM_PROG_AIDX_BLU_RESUME_ENTRY,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_ENTRY,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_DO,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_ACTION_3,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_ACTION_4,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_FINISH_ENTRY,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_FINISH_EXIT,
  PROG_HSM_PROG_AIDX_CHECK_MEMORY_FINISH_ACTION_1,
  PROG_HSM_PROG_AIDX_SECUREBOOT_COMPUTE_CHECKSUM_DO,
  PROG_HSM_PROG_AIDX_SECUREBOOT_COMPUTE_CHECKSUM_ACTION_2,
  PROG_HSM_PROG_AIDX_SIGNATURE_CHECK_ENTRY,
  PROG_HSM_PROG_AIDX_SIGNATURE_CHECK_EXIT,
  PROG_HSM_PROG_AIDX_CHECK_PROG_DEPENDENCIES_TOP_ACTION_3,
  PROG_HSM_PROG_AIDX_CHECK_PROG_DEPENDENCIES_TOP_ACTION_4,
  PROG_HSM_PROG_AIDX_CHECK_PROG_DEPENDENCIES_TOP_ACTION_5,
  PROG_HSM_PROG_AIDX_CHECK_PROG_DEP_DO,
  PROG_HSM_PROG_AIDX_CHECK_PROG_DEP_FINISH_ACTION_1,
  PROG_HSM_PROG_AIDX_COMPARE_KEY_ENTRY,
  PROG_HSM_PROG_AIDX_COMPARE_KEY_ACTION_1,
  PROG_HSM_PROG_AIDX_COMPARE_KEY_ACTION_3,
  PROG_HSM_PROG_AIDX_COMPARE_KEY_ACTION_5,
  PROG_HSM_PROG_AIDX_COMPARE_KEY_ACTION_7,
  PROG_HSM_PROG_AIDX_COMPARE_KEY_ACTION_8,
  PROG_HSM_PROG_AIDX_DEFAULT_SESSION_ENTRY,
  PROG_HSM_PROG_AIDX_ECU_RESET_ENTRY,
  PROG_HSM_PROG_AIDX_ERASE_TOP_ACTION_2,
  PROG_HSM_PROG_AIDX_ERASE_TOP_ACTION_3,
  PROG_HSM_PROG_AIDX_ERASE_TOP_ACTION_4,
  PROG_HSM_PROG_AIDX_ERASE_TOP_ACTION_5,
  PROG_HSM_PROG_AIDX_ERASE_ENTRY,
  PROG_HSM_PROG_AIDX_ERASE_DO,
  PROG_HSM_PROG_AIDX_ERASE_CHECK_ENTRY,
  PROG_HSM_PROG_AIDX_ERASE_FINISH_ENTRY,
  PROG_HSM_PROG_AIDX_ERASE_NRC78_ENTRY,
  PROG_HSM_PROG_AIDX_ERASE_TRANSMITNRC78_ENTRY,
  PROG_HSM_PROG_AIDX_EXT_SESSION_ENTRY,
  PROG_HSM_PROG_AIDX_EXT_SESSION_ACTION_1,
  PROG_HSM_PROG_AIDX_GET_SEED_ENTRY,
  PROG_HSM_PROG_AIDX_GET_SEED_ACTION_1,
  PROG_HSM_PROG_AIDX_GET_SEED_ACTION_2,
  PROG_HSM_PROG_AIDX_GET_SEED_ACTION_4,
  PROG_HSM_PROG_AIDX_GET_SEED_ACTION_5,
  PROG_HSM_PROG_AIDX_GET_SEED_ACTION_6,
  PROG_HSM_PROG_AIDX_GET_SEED_ACTION_7,
  PROG_HSM_PROG_AIDX_INIT_ENTRY,
  PROG_HSM_PROG_AIDX_INIT_EXIT,
  PROG_HSM_PROG_AIDX_LOCKED_ACTION_1,
  PROG_HSM_PROG_AIDX_LOCKED_ACTION_2,
  PROG_HSM_PROG_AIDX_LOCKED_ACTION_3,
  PROG_HSM_PROG_AIDX_LOCKED_ACTION_5,
  PROG_HSM_PROG_AIDX_LOCKED_ACTION_6,
  PROG_HSM_PROG_AIDX_LOCKED_ACTION_7,
  PROG_HSM_PROG_AIDX_PROG_SESSION_ENTRY,
  PROG_HSM_PROG_AIDX_PROG_SESSION_ACTION_2,
  PROG_HSM_PROG_AIDX_PROG_SESSION_ACTION_3,
  PROG_HSM_PROG_AIDX_PROG_SESSION_ACTION_4,
  PROG_HSM_PROG_AIDX_PROG_SESSION_ACTION_7,
  PROG_HSM_PROG_AIDX_PROG_SESSION_ACTION_8,
  PROG_HSM_PROG_AIDX_REPROG_ACTION_1,
  PROG_HSM_PROG_AIDX_REPROG_ACTION_2,
  PROG_HSM_PROG_AIDX_RD_ENTRY,
  PROG_HSM_PROG_AIDX_RD_ACTION_1,
  PROG_HSM_PROG_AIDX_RD_ACTION_5,
  PROG_HSM_PROG_AIDX_RTE_TOP_ACTION_3,
  PROG_HSM_PROG_AIDX_RTE_TOP_ACTION_4,
  PROG_HSM_PROG_AIDX_RTE_ENTRY,
  PROG_HSM_PROG_AIDX_RTE_DO,
  PROG_HSM_PROG_AIDX_RTE_DECRYPT_EXIT,
  PROG_HSM_PROG_AIDX_RTE_DECRYPT_FINISH_ENTRY,
  PROG_HSM_PROG_AIDX_RTE_DECRYPT_FINISH_DO,
  PROG_HSM_PROG_AIDX_RTE_WRITE_ENTRY,
  PROG_HSM_PROG_AIDX_RTE_WRITE_DO,
  PROG_HSM_PROG_AIDX_RTE_WRITE_CHECK_DO,
  PROG_HSM_PROG_AIDX_RTE_FAILED_ENTRY,
  PROG_HSM_PROG_AIDX_RTE_FAILED_DO,
  PROG_HSM_PROG_AIDX_RTE_FINISH_ENTRY,
  PROG_HSM_PROG_AIDX_TD_TOP_ACTION_2,
  PROG_HSM_PROG_AIDX_TD_ENTRY,
  PROG_HSM_PROG_AIDX_TD_CRC_DO,
  PROG_HSM_PROG_AIDX_TD_FAILED_ENTRY,
  PROG_HSM_PROG_AIDX_TD_STREAMING_ENTRY,
  PROG_HSM_PROG_AIDX_TD_WRITE_EXIT,
  PROG_HSM_PROG_AIDX_TD_WRITE_ACTION_1,
  PROG_HSM_PROG_AIDX_TD_WRITE_ACTION_2,
  PROG_HSM_PROG_AIDX_DECRYPT_FINISH_ENTRY,
  PROG_HSM_PROG_AIDX_DECRYPT_FINISH_DO,
  PROG_HSM_PROG_AIDX_DECRYPT_UPDATE_ENTRY,
  PROG_HSM_PROG_AIDX_DECRYPT_UPDATE_DO,
  PROG_HSM_PROG_AIDX_WRITE_ENTRY,
  PROG_HSM_PROG_AIDX_WRITE_DO,
  PROG_HSM_PROG_AIDX_WRITE_CHECK_DO,
  PROG_HSM_PROG_AIDX_RESET_ENTRY,
  PROG_HSM_PROG_AIDX_WRITE_FINGERPRINT_ACTION_1,
  PROG_HSM_PROG_AIDX_WRITE_FINGERPRINT_ACTION_3,
  PROG_HSM_PROG_AIDX_WRITE_FINGERPRINT_ACTION_4,
  PROG_HSM_PROG_AIDX_WRITE_FINGERPRINT_ACTION_6,
  PROG_HSM_PROG_AIDX_WRITE_FINGERPRINT_ACTION_7,
  PROG_HSM_PROG_AIDX_WFP_INPROGRESS_ENTRY,
  PROG_HSM_PROG_AIDX_WFP_INPROGRESS_DO,
  PROG_HSM_PROG_AIDX_PRE_INIT_ENTRY,
  PROG_HSM_PROG_AIDX_PRE_INIT_DO,
  PROG_HSM_PROG_AIDX_SLEEP_ENTRY,
  PROG_HSM_PROG_NO_OF_ACTIONS
} PROG_HsmPROGActionIdType;
/* typedefed type only used for debugging */

/* *** IDs for guards *** */
typedef enum
{
  PROG_HSM_PROG_GIDX_CHECK_MEMORY_TOP_GUARD_2,
  PROG_HSM_PROG_GIDX_CHECK_MEMORY_FINISH_GUARD_2,
  PROG_HSM_PROG_GIDX_CHECK_MEMORY_FINISH_GUARD_3,
  PROG_HSM_PROG_GIDX_CHECK_PROG_DEPENDENCIES_TOP_GUARD_1,
  PROG_HSM_PROG_GIDX_CHECK_PROG_DEPENDENCIES_TOP_GUARD_2,
  PROG_HSM_PROG_GIDX_CHECK_PROG_DEPENDENCIES_TOP_GUARD_6,
  PROG_HSM_PROG_GIDX_CHECK_PROG_DEP_FINISH_GUARD_2,
  PROG_HSM_PROG_GIDX_CHECK_PROG_DEP_FINISH_GUARD_3,
  PROG_HSM_PROG_GIDX_COMPARE_KEY_GUARD_2,
  PROG_HSM_PROG_GIDX_COMPARE_KEY_GUARD_4,
  PROG_HSM_PROG_GIDX_COMPARE_KEY_GUARD_6,
  PROG_HSM_PROG_GIDX_COMPARE_KEY_GUARD_9,
  PROG_HSM_PROG_GIDX_ERASE_TOP_GUARD_1,
  PROG_HSM_PROG_GIDX_ERASE_FINISH_GUARD_1,
  PROG_HSM_PROG_GIDX_ERASE_FINISH_GUARD_2,
  PROG_HSM_PROG_GIDX_ERASE_FINISH_GUARD_3,
  PROG_HSM_PROG_GIDX_PROG_SESSION_GUARD_5,
  PROG_HSM_PROG_GIDX_PROG_SESSION_GUARD_9,
  PROG_HSM_PROG_GIDX_RD_GUARD_2,
  PROG_HSM_PROG_GIDX_RD_GUARD_3,
  PROG_HSM_PROG_GIDX_RD_GUARD_4,
  PROG_HSM_PROG_GIDX_RD_GUARD_7,
  PROG_HSM_PROG_GIDX_RTE_TOP_GUARD_1,
  PROG_HSM_PROG_GIDX_RTE_TOP_GUARD_2,
  PROG_HSM_PROG_GIDX_RTE_TOP_GUARD_5,
  PROG_HSM_PROG_GIDX_RTE_FINISH_GUARD_1,
  PROG_HSM_PROG_GIDX_RTE_FINISH_GUARD_2,
  PROG_HSM_PROG_GIDX_TD_TOP_GUARD_3,
  PROG_HSM_PROG_GIDX_TD_TOP_GUARD_4,
  PROG_HSM_PROG_GIDX_TD_TOP_GUARD_5,
  PROG_HSM_PROG_GIDX_TD_TOP_GUARD_7,
  PROG_HSM_PROG_GIDX_WRITE_FINGERPRINT_GUARD_2,
  PROG_HSM_PROG_GIDX_WRITE_FINGERPRINT_GUARD_5,
  PROG_HSM_PROG_GIDX_WFP_FINISHED_GUARD_1,
  PROG_HSM_PROG_GIDX_WFP_FINISHED_GUARD_2,
  PROG_HSM_PROG_NO_OF_GUARDS
} PROG_HsmPROGGuardIdType;
/* typedefed type only used for debugging */

/*==================[external function declarations]========================*/

#define PROG_START_SEC_CODE
#include <MemMap.h>

/* function declarations of state entry, exit, guard, action functions
 * defined in PROG_fnct.c */


/* implements action '(void)PROG_CheckProgrammingPreCondition();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfALIVEAction5(
  PROG_PDL_SF(const uint8 instIdx));

/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_TOPAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_Erase_Check_CheckMemory()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_TOPGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_GetSeed_Unlocked();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_TOPAction5(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfBLU_PRE_RESETEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfBLU_RESUMEEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORYEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORYDo(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_CheckSegmentListCrc();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORYAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action '(void)PROG_CRC_Compare();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORYAction4(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_FINISHExit(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_AnswerSuccesiveCheckMemoryRequests();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_FINISHAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_CheckMemory_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_CheckMemory()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_MEMORY_FINISHGuard3(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfSECUREBOOT_COMPUTE_CHECKSUMDo(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Entry_SecureChecksumFailed();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfSECUREBOOT_COMPUTE_CHECKSUMAction2(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfSIGNATURE_CHECKEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfSIGNATURE_CHECKExit(
  PROG_PDL_SF(const uint8 instIdx));

/* implements guard 'PROG_Custom_Guard_CheckProgDep_CompareKey()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPGuard1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_Erase_Check_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_GetSeed_Unlocked();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPAction5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_CheckProgDep_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPENDENCIES_TOPGuard6(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEPDo(
  PROG_PDL_SF(const uint8 instIdx));

/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEP_FINISHAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_CheckProgDep_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEP_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_CheckProgDep()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCHECK_PROG_DEP_FINISHGuard3(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_CompareKey_CheckProgDep()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_Erase_Check_CompareKey()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYGuard4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_GetSeed_Unlocked();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYAction5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_CompareKey()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYGuard6(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYAction7(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYAction8(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_CompareKey_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfCOMPARE_KEYGuard9(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfDEFAULT_SESSIONEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfECU_RESETEntry(
  PROG_PDL_SF(const uint8 instIdx));

/* implements guard 'PROG_Custom_Guard_EraseMemory_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfERASE_TOPGuard1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_TOPAction2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_GetSeed_Unlocked();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_TOPAction5(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASEEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASEDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_CHECKEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_Erase_Check_EraseMemory()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfERASE_FINISHGuard1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_EraseMemory()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfERASE_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_EraseMemory_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfERASE_FINISHGuard3(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_NRC78Entry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfERASE_TRANSMITNRC78Entry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfEXT_SESSIONEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfEXT_SESSIONAction1(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDAction2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Entry_GetSeed();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDAction5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDAction6(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfGET_SEEDAction7(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfINITEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfINITExit(
  PROG_PDL_SF(const uint8 instIdx));

/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfLOCKEDAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfLOCKEDAction2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfLOCKEDAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfLOCKEDAction5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfLOCKEDAction6(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfLOCKEDAction7(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONAction2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_Erase_Check_ProgSession()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONGuard5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONAction7(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONAction8(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_ProgSession_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfPROG_SESSIONGuard9(
  PROG_PDL_SF(const uint8 instIdx));

/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfREPROGAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_GetSeed_Unlocked();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfREPROGAction2(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRDEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRDAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_RD_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRDGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_Erase_Check_RD()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRDGuard3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_RD()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRDGuard4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRDAction5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_RD_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRDGuard7(
  PROG_PDL_SF(const uint8 instIdx));

/* implements guard '(PROG_Custom_Guard_Erase_Check_RTE()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRTE_TOPGuard1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_E_OK==PROG_RD_Check())' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRTE_TOPGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_TOPAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_TOPAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_RTE_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRTE_TOPGuard5(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTEEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTEDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_DECRYPTExit(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_DECRYPT_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_DECRYPT_FINISHDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_WRITEEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_WRITEDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_WRITE_CHECKDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_FAILEDEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_FAILEDDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRTE_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_RTE_CheckMemory()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRTE_FINISHGuard1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_RTE_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfRTE_FINISHGuard2(
  PROG_PDL_SF(const uint8 instIdx));

/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_TOPAction2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_TD_CheckProgDep()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfTD_TOPGuard3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_Erase_Check_TD()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfTD_TOPGuard4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_TD()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfTD_TOPGuard5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_TD_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfTD_TOPGuard7(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTDEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_CRCDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_FAILEDEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_STREAMINGEntry(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_WRITEExit(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action '(void)PROG_TD();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_WRITEAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Streaming();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfTD_WRITEAction2(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfDECRYPT_FINISHEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfDECRYPT_FINISHDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfDECRYPT_UPDATEEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfDECRYPT_UPDATEDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITEEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITEDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITE_CHECKDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfRESETEntry(
  PROG_PDL_SF(const uint8 instIdx));

/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTAction1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_FingerPrint_CheckProgDep()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTGuard2(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTAction3(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_GetSeed_Unlocked();' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTAction4(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard '(PROG_Custom_Guard_RD_Check_FingerPrint()==PROG_E_OK)' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTGuard5(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTAction6(
  PROG_PDL_SF(const uint8 instIdx));
/* implements action 'PROG_Send_NRC(UDS_NRC_24);' */
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWRITE_FINGERPRINTAction7(
  PROG_PDL_SF(const uint8 instIdx));

/* implements guard 'PROG_Custom_Guard_Erase_Check_Fingerprint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfWFP_FINISHEDGuard1(
  PROG_PDL_SF(const uint8 instIdx));
/* implements guard 'PROG_Custom_Guard_FingerPrint_FingerPrint()==PROG_E_OK' */
extern FUNC(boolean, PROG_CODE)
 PROG_HsmPROGSfWFP_FINISHEDGuard2(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWFP_INPROGRESSEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfWFP_INPROGRESSDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPRE_INITEntry(
  PROG_PDL_SF(const uint8 instIdx));
extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfPRE_INITDo(
  PROG_PDL_SF(const uint8 instIdx));

extern FUNC(void, PROG_CODE)
 PROG_HsmPROGSfSLEEPEntry(
  PROG_PDL_SF(const uint8 instIdx));


#define PROG_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/
/* CHECK: PARSE */
#endif /* defined PROG_HSMPROGINT_H */
/*==================[end of file]===========================================*/
