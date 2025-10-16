/**EB_Automotive_C_Source_File */



/* ==================[Includes]=============================================== */
#include <Rte_SWC_E2ESafety.h>

/* ==================[Definition of functions with external linkage]========== */
/* ------------------------[runnable entity skeletons]------------------------ */

uint8 E2E_Data_Safety = 0U;
 
FUNC(void, RTE_CODE) SWC_E2EProtSafe_Data_Received (void)
{
  E2EProt_Data arg_Receive_data;
  Std_ReturnType ret_Receive;
  E2EProt_Data arg_IWrite_data = 
  {
    E2E_Data_Safety,
    0U,
    0U
  };
  P2VAR(E2EProt_Data, AUTOMATIC, RTE_APPL_DATA) ret_IWriteRef;

  (void)ret_Receive;
  if( Rte_Receive_R_E2E_SafeData_E2EProt_Data(&arg_Receive_data) == E_OK )
  {
	E2E_Data_Safety = arg_Receive_data.SafetyE2E_Data;
  }
  Rte_IWrite_UpdateE2EProtSafeData_P_E2E_SafeData_E2EProt_Data(&arg_IWrite_data);
  (void)ret_IWriteRef;
  ret_IWriteRef = Rte_IWriteRef_UpdateE2EProtSafeData_P_E2E_SafeData_E2EProt_Data();
  
} /* FUNC(void, RTE_CODE) SWC_E2EProtSafe_Data_Received (void) */
 
 
FUNC(void, RTE_CODE) SWC_E2EProtSafe_Data_Cyclic (void)
{
  E2EProt_Data arg_Send_data = 
  {
    E2E_Data_Safety += 1U,
    0U,
    0U
  };
  Std_ReturnType ret_Send;
  (void)ret_Send;
  ret_Send = Rte_Send_P_E2E_SafeData_E2EProt_Data(&arg_Send_data);

} /* FUNC(void, RTE_CODE) SWC_E2EProtSafe_Data_Cyclic (void) */

/*
  ------------------------[runnable-independent API]-------------------------

  Copy and paste the following API to those runnable entity functions where
  you want to use them.

  ------------------------[port handle API]----------------------------------
  ------------------------[per instance memory API]--------------------------
 */

/** @} doxygen end group definition  */
/* ==================[end of file]============================================ */
