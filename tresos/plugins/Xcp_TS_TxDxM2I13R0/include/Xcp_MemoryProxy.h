#ifndef XCP_MEMORY_PROXY_H
#define XCP_MEMORY_PROXY_H

/*==[Includes]================================================================*/

#include <Xcp_Cfg.h>
#include <Std_Types.h>

#if (XCP_BSW_DISTRIBUTION_MEMORY_ACCESS_AREAS == STD_ON)

#include <Xcp_Int_Cfg.h>
#include <Xcp_Int.h>
#include <Rte_Type.h>
#include <Atomics.h>

/*==[Macros definitions]======================================================*/

#if (defined XCP_MEMORY_PROXY_AVAILABLE)
#error XCP_MEMORY_PROXY_AVAILABLE already defined
#endif
#define XCP_MEMORY_PROXY_AVAILABLE 0U

#if (defined XCP_MEMORY_PROXY_READY)
#error XCP_MEMORY_PROXY_READY already defined
#endif
#define XCP_MEMORY_PROXY_READY 1U

#if (defined XCP_MEMORY_PROXY_LOCKED)
#error XCP_MEMORY_PROXY_LOCKED already defined
#endif
#define XCP_MEMORY_PROXY_LOCKED 2U

#if (defined XCP_MEMORY_PROXY_STATES_COUNT)
#error XCP_MEMORY_PROXY_STATES_COUNT already defined
#endif
#define XCP_MEMORY_PROXY_STATES_COUNT 3U

#if (defined XCP_MEMORYPROXYDATA_UPLOAD)
#error XCP_MEMORYPROXYDATA_UPLOAD already defined
#endif
#define XCP_MEMORYPROXYDATA_UPLOAD          0U

#if (defined XCP_MEMORYPROXYDATA_DOWNLOAD)
#error XCP_MEMORYPROXYDATA_DOWNLOAD already defined
#endif
#define XCP_MEMORYPROXYDATA_DOWNLOAD        1U

#if (defined XCP_MEMORYPROXYDATA_EVENT_PROCESSOR)
#error XCP_MEMORYPROXYDATA_EVENT_PROCESSOR already defined
#endif
#define XCP_MEMORYPROXYDATA_EVENT_PROCESSOR 2U

#if (defined XCP_MEMORYPROXYDATA_STIMULATION)
#error XCP_MEMORYPROXYDATA_STIMULATION already defined
#endif
#define XCP_MEMORYPROXYDATA_STIMULATION     3U

#if (defined XCP_MEMORYPROXYDATA_SAMPLE)
#error XCP_MEMORYPROXYDATA_SAMPLE already defined
#endif
#define XCP_MEMORYPROXYDATA_SAMPLE          4U

#if (defined XCP_MEMORYPROXYDATA_STIMULATION_0)
#error XCP_MEMORYPROXYDATA_STIMULATION_0 already defined
#endif
#define XCP_MEMORYPROXYDATA_STIMULATION_0   5U

#if (defined XCP_MEMORYPROXYDATA_STIMULATION_1)
#error XCP_MEMORYPROXYDATA_STIMULATION_1 already defined
#endif
#define XCP_MEMORYPROXYDATA_STIMULATION_1   6U

#if (defined XCP_MEMORYPROXYDATA_SAMPLE_0)
#error XCP_MEMORYPROXYDATA_SAMPLE_0 already defined
#endif
#define XCP_MEMORYPROXYDATA_SAMPLE_0        7U

#if (defined XCP_MEMORYPROXYDATA_SAMPLE_1)
#error XCP_MEMORYPROXYDATA_SAMPLE_1 already defined
#endif
#define XCP_MEMORYPROXYDATA_SAMPLE_1        8U

#if (defined XCP_XCP_MEMORYPROXYDATA_CRC)
#error XCP_XCP_MEMORYPROXYDATA_CRC already defined
#endif
#define XCP_XCP_MEMORYPROXYDATA_CRC 9U

#define XCP_GET_MEMORY_PROXY_STATE() (Atomics_Load(&Xcp_MemoryProxyState) % XCP_MEMORY_PROXY_STATES_COUNT)

/*==[Types declarations]======================================================*/

/*==[Declaration of constants with external linkage]==========================*/

/*==[Declaration of variables with external linkage]==========================*/

#define XCP_START_SEC_VAR_CLEARED_MEMORY_PROXY_8
#include <Xcp_MemMap.h>

extern VAR(uint8, XCP_VAR_CLEARED) Xcp_MemoryProxyBuffer[XCP_MAX_MEMORY_WRITE_BYTES];

#define XCP_STOP_SEC_VAR_CLEARED_MEMORY_PROXY_8
#include <Xcp_MemMap.h>

#define XCP_START_SEC_VAR_CLEARED_MEMORY_PROXY_16
#include <Xcp_MemMap.h>

extern VAR(uint16, XCP_VAR_CLEARED) Xcp_MemoryProxyResponseLength;

#define XCP_STOP_SEC_VAR_CLEARED_MEMORY_PROXY_16
#include <Xcp_MemMap.h>


#define XCP_START_SEC_VAR_INIT_MEMORY_PROXY_UNSPECIFIED
#include <Xcp_MemMap.h>

/** \brief This variables holds both the state and the session identifier for the memory proxy.
 ** As the state has 3 possible values (XCP_MEMORY_PROXY_AVAILABLE, XCP_MEMORY_PROXY_LOCKED and
 ** XCP_MEMORY_PROXY_READY) we can encode a session identifier value (which can be 0,1,2..) by
 ** multiplying the session identifier value with the number of states and adding the numberical
 ** value of the state.
 */
extern VAR(Atomic_t, XCP_VAR) Xcp_MemoryProxyState;

#define XCP_STOP_SEC_VAR_INIT_MEMORY_PROXY_UNSPECIFIED
#include <Xcp_MemMap.h>

/*==[Declaration of functions with external linkage]==========================*/

#define XCP_START_SEC_CODE
#include <Xcp_MemMap.h>

extern FUNC(void, XCP_CODE) Xcp_MemoryProxyHandler(Xcp_MemoryProxyDataType* data);
extern FUNC(void, XCP_CODE) Xcp_MemoryProxySetReadyIfSameSession(uint16 original);
extern FUNC(void, XCP_CODE) Xcp_MemoryProxySetAvailableNewSession(void);
extern FUNC(void, XCP_CODE) Xcp_MemoryProxySetNewState(uint8 newState);

#define XCP_STOP_SEC_CODE
#include <Xcp_MemMap.h>

#endif /* XCP_BSW_DISTRIBUTION_MEMORY_ACCESS_AREAS == STD_ON */

#endif /* XCP_MEMORY_PROXY_H */

