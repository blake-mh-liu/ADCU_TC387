#ifndef BM_PRIV_H
#define BM_PRIV_H

/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Priv.h                       */
/*%%  |                             |  %%  \brief BM layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

#include "BM_Cfg.h"

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */
#if (BM_CSM_HASH_USED == STD_ON)
extern u32 m_ulDigestLength;
#elif (BM_CSM_MAC_USED == STD_ON)
/* Key used for the MAC algorithm */
extern Csm_SymKeyType m_stBMMacKey;
#endif
#if ((BM_CSM_HASH_USED == STD_ON) || (BM_CSM_MAC_USED == STD_ON))
extern u8  m_ubCsmFinished;
extern Csm_ReturnType m_ubCsmResult;
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
extern const u8 * m_pubDataBuffer;
extern u32 m_uwDataLength;
#if (BM_CSM_HASH_USED == STD_ON)
extern u8 * m_pubChecksum;
#elif (BM_CSM_MAC_USED == STD_ON)
extern const u8 * m_pubChecksum;
#endif
#endif
#endif
#endif

#if (BM_CSM_MAC_USED == STD_ON)
#define BM_CSMRESULT_START_SEC_VAR
#include <MemMap.h>
extern Csm_VerifyResultType m_eCsmResult;
#define BM_CSMRESULT_STOP_SEC_VAR
#include <MemMap.h>
#endif

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if ((BM_NETWORK_FLEXRAY_SUPPORTED == STD_ON) && (BM_NETWORK_MANAGEMENT_ENABLE == STD_ON))
extern tBMFRStatus m_ubBMFRStatus;
extern tBMNetworkStatus m_ubBMNetworkStatus;
extern tBMCycleCount m_ubBMFRCycleOrigin;
#endif
#endif

#if (((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON)) && (BM_BOOT_CHECKSUM_VERIFICATION == STD_ON))

/* Bootloader checksum, shall be stored at specific address in order to be set at build time */
extern const uint8 m_aubExpectedBootloaderChecksum[BM_CHECKSUM_SIZE_IN_BYTES];

#endif
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */


/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))

/** \brief This function loops on all blocks and verify their checksum
 **
 ** \param[in] void
 **
 ** \return Result of treatment
 ** \retval BM_TRUE  Software integrity test succeeded
 ** \retval BM_FALSE Software integrity test failed
 **/
extern tBMBoolean BM_VerifySoftwareIntegrity(void);
#endif /*((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))*/

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if (BM_CSM_HASH_USED == STD_ON)
/** \brief Calculate the hash value on the given data
 **
 ** This function allow to set the address and size for the Hash calculation
 **
 ** \param[in] pubDataToSign Data on which hash will be calculated
 ** \param[in] uwDataLength length of data to calculate hash on
 ** \param[out] pubHashValue calculated hash value
 **
 ** \return Result of treatment
 ** \retval BM_TRUE  Operation succeeded
 ** \retval BM_FALSE Operation failed
 **/
extern tBMBoolean BM_ComputeHash(u8 const * pubDataToSign, u32 uwDataLength, u8 * pubHashValue);
#endif

#if (BM_CSM_MAC_USED == STD_ON)
/** \brief Calculate the MAC value on the given data and compare it to the expected MAC value
 ** Get from the memory
 **
 ** This function allow to set the address and size for the MAC calculation
 **
 ** \param[in] pubExpectedChecksum Expected MAC value get from the memory
 ** \param[in] pubDataToSign Data on which MAC will be calculated
 ** \param[in] uwDataLength length of data to calculate MAC on
 **
 ** \return Result of treatment
 ** \retval BM_TRUE  Operation succeeded
 ** \retval BM_FALSE Operation failed
 **/
extern tBMBoolean BM_VerifyMac(u8 const * pubExpectedChecksum, u8 const * pubDataToSign, u32 uwDataLength);
#endif
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/

#if (BM_HSM_MAC_USED == STD_ON)
tBMBoolean BM_HsmVerifyMac(u16 uwBlockId);
#endif

#endif      /* BM_PRIV_H */
