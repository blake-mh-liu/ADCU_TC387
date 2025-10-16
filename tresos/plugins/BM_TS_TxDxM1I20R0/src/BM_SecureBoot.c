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
/*%%   _____________________________   %%  \file BM_SecureBoot.c                 */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 *
 * MISRAC2012-2) Deviated Rule: 8.4 (required)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined
 *
 *   Reason:
 * This variable need to be used in test environment
 */
/* NOCOV List
 *
 * NOCOV-NOCOV-BMTIMEOUTCHECKONNOTSUPPORTED:
 *
 * Reason:
 * BM_TIMEOUT_CHECK_ON not yet supported
 */
/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: INT.36
 * Converting a pointer to integer or integer to pointer
 *
 * Reason:
 * this variable contains a flash memory address that will not be subject to pointer arithmetics no risk of alignment issues.
 */



/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: Variable Types                                                */


/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */


/*                                                                               */
/*===============================================================================*/
#include "EB_Prj.h"
#include "BM_Priv.h"
#include <BM_Trace.h>

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#if ((BM_CSM_MAC_USED == STD_ON) || (BM_CSM_HASH_USED == STD_ON))
#define BM_APP_CKS_START_SEC_VAR
#include <MemMap.h>
/* Deviation MISRAC2012-2 */
NCS_PRI_VAR u8 m_aubExpectedApplicationChecksum[BM_CHECKSUM_SIZE_IN_BYTES];
#define BM_APP_CKS_STOP_SEC_VAR
#include <MemMap.h>
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if (BM_IMPL_VARIANT == BM_IMPL_10)
#define BM_ESS_INDEX     0
#endif
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

NCS_PRI_VAR tBMBoolean BM_VerifyESSIntegrity(void);

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if (BM_IMPL_VARIANT == BM_IMPL_10)
NCS_PRI_VAR tBMBoolean BM_VerifyESSIntegrity(void)
{
  tBMBoolean ubCheckOk;
#if (BM_HSM_MAC_USED == STD_OFF)
  u32 ulStartAddress;
  u32 ulLength;
#endif
#if (BM_HSM_MAC_USED == STD_ON)
  ubCheckOk = BM_HsmVerifyMac(BM_ESS_INDEX);
#else
  /* Block index 0 is reserved for ESS */
  BM_CustomGetExpectedApplicationChecksum(&m_aubExpectedApplicationChecksum[0U], BM_ESS_INDEX);

  Prog_GetEssStartAddr(&ulStartAddress);
  Prog_GetEssLength(&ulLength);

  /* Verification of the MAC for ESS*/
  /* Deviation MISRAC2012-1 */
  /* Deviation CERTC-1 */
  ubCheckOk = BM_VerifyMac(
          &m_aubExpectedApplicationChecksum[0U],
          (u8 const *)ulStartAddress,
          ulLength);
#endif
  return ubCheckOk;
}
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_IMPL_10)*/
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
tBMBoolean BM_VerifySoftwareIntegrity(void)
{
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_CSM_HASH_USED == STD_ON))
    u16 uwLoopIndex;
    u8 aubComputedApplicationChecksum[BM_CHECKSUM_SIZE_IN_BYTES];
#endif
#if (BM_IMPL_VARIANT == BM_IMPL_10)
    u8 ubBlockIndex;
    u8 ubBlockCount;
#if (BM_HSM_MAC_USED == STD_OFF)
    u32 ulStartAddress;
    u32 ulLength;
#endif
#else
#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
    u16 uwVerificationunitIndex;
    u16 uwMaxverificationscount = 0U;
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/
    tBMBoolean ubCheckOk = BM_TRUE;
#endif /*(BM_IMPL_VARIANT == BM_IMPL_10)*/

    tBMBoolean ubSoftBootable = BM_TRUE;
#if (BM_SECURE_BOOT_ENABLE == STD_ON)
    tBMBoolean eOperationSuccess = BM_TRUE;
#endif

#if (BM_IMPL_VARIANT == BM_IMPL_10)

    /* Verify ESS first */
    ubSoftBootable = BM_VerifyESSIntegrity();

    /* ESS is valid */
    if(BM_TRUE == ubSoftBootable)
    {
      (void)Prog_GetEssLogicalBlockNbr(&ubBlockCount);

      /* Block index 0 is reserved for ESS */
      for (ubBlockIndex = 0U; ((ubBlockIndex < ubBlockCount) && (BM_TRUE == eOperationSuccess)); ubBlockIndex++)
      {
#if (BM_HSM_MAC_USED == STD_ON)
        eOperationSuccess = BM_HsmVerifyMac((u16)ubBlockIndex + 1U);
#else
        (void)Prog_GetEssLogicalBlockStartAddr(ubBlockIndex, &ulStartAddress);
        (void)Prog_GetEssLogicalBlockLength(ubBlockIndex, &ulLength);

        /* Get Expected Application checksum of the corresponding Block identifier */
        /* add 1 because first index is reserved for the ESS */
        BM_CustomGetExpectedApplicationChecksum(&m_aubExpectedApplicationChecksum[0U], (u16)ubBlockIndex + 1U);

          /* Computation of the MAC for the current block */
          /* Comparison to the MAC saved for the same block */
          /* Deviation MISRAC2012-1 */
         /* Deviation CERTC-1 */
          eOperationSuccess = BM_VerifyMac(
                  &m_aubExpectedApplicationChecksum[0U],
                  (u8 const *)ulStartAddress,
                  ulLength);
#endif
      }


      if (BM_TRUE == eOperationSuccess)
      {
        ubSoftBootable = BM_TRUE;
      }
      else
      {
        ubSoftBootable = BM_FALSE;
        /* Block index 0 is reserved for ESS */
        BM_CustomSetInvalidAppli(ubBlockIndex);
      }
    }
    /* ESS integrity failed */
    else
    {
      /* Block index 0 is reserved for ESS */
      BM_CustomSetInvalidAppli(BM_ESS_INDEX);
    }
#else

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
    /* For each Block to be verified for secure boot */
    uwMaxverificationscount = PROG_BLOCK_NB;
#else
    /* For each Segment to be verified for secure boot */
    uwMaxverificationscount = PROG_SEGMENT_NB;
#endif
    for (uwVerificationunitIndex = 0U; ((uwVerificationunitIndex < uwMaxverificationscount) && (BM_TRUE == ubSoftBootable)); uwVerificationunitIndex++)
    {
        /* If the block shall be verified by Secure Boot */
        if (BM_TRUE == stCfgBMBlockSecureBootInfo[uwVerificationunitIndex].ubBlockVerifiedInSecure)
        {
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/
#if ((BM_CSM_MAC_USED == STD_ON) || (BM_CSM_HASH_USED == STD_ON))
            /* Get Expected Application checksum of the corresponding Block identifier */
            BM_CustomGetExpectedApplicationChecksum(&m_aubExpectedApplicationChecksum[0U], uwVerificationunitIndex);
#endif

#if (BM_AUTHENTICATED_BOOT_ENABLE == STD_ON)
            /* Verify application checksum before starting it */
            BM_CustomGetComputedApplicationChecksum(&aubComputedApplicationChecksum[0U], uwVerificationunitIndex);
#elif (BM_SECURE_BOOT_ENABLE == STD_ON)
#if (BM_CSM_MAC_USED == STD_ON)
            /* Computation of the MAC for the current block */
            /* Comparison to the MAC saved for the same block */
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            eOperationSuccess = BM_VerifyMac(
                    &m_aubExpectedApplicationChecksum[0U],
                    (u8 const *)stCfgBMBlockSecureBootInfo[uwVerificationunitIndex].ulStartAddressForSecureBoot,
                    stCfgBMBlockSecureBootInfo[uwVerificationunitIndex].ulLengthForSecureBoot);
#endif

#if (BM_CSM_HASH_USED == STD_ON)
            /* Deviation MISRAC2012-1 */
            /* Computation of the Hash */
           /* Deviation CERTC-1 */
            eOperationSuccess = BM_ComputeHash((u8 const *)stCfgBMBlockSecureBootInfo[uwVerificationunitIndex].ulStartAddressForSecureBoot,
                stCfgBMBlockSecureBootInfo[uwVerificationunitIndex].ulLengthForSecureBoot,
                &aubComputedApplicationChecksum[0]);
#endif

#if ((BM_SECURE_BOOT_ENABLE == STD_ON) && (BM_HSM_MAC_USED == STD_ON))
#if (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER)
            eOperationSuccess = BM_HsmVerifyMac(BM_BLU_BLOCK_ID);
#else
            eOperationSuccess = BM_HsmVerifyMac(uwVerificationunitIndex);
#endif
#endif

            if (BM_TRUE == eOperationSuccess)
#endif /* (BM_SECURE_BOOT_ENABLE == STD_ON) */

            {
                ubCheckOk = BM_TRUE;
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_CSM_HASH_USED == STD_ON))

                for (uwLoopIndex = 0U; ((uwLoopIndex < BM_CHECKSUM_SIZE_IN_BYTES) && (BM_TRUE == ubCheckOk)); uwLoopIndex++)
                {
                    if (aubComputedApplicationChecksum[uwLoopIndex] != m_aubExpectedApplicationChecksum[uwLoopIndex])
                    {
                        ubCheckOk = BM_FALSE;
                    }
                }
#endif
            }
#if (BM_SECURE_BOOT_ENABLE == STD_ON)
            else
            {
                ubCheckOk = BM_FALSE;
            }
#endif

            if (BM_FALSE == ubCheckOk)
            {
#if (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER)
                /* Notify that the BLUpdater block is not valid */
                BM_CustomSetInvalidBlu();
#else
                /* Notify that corresponding block identifier is not valid */
                BM_CustomSetInvalidAppli(uwVerificationunitIndex);
                /* Test if the invalid Block shall block the execution of the software  */
                if (BM_TRUE == stCfgBMBlockSecureBootInfo[uwVerificationunitIndex].ubBlockBlockerExecution)
#endif
                {
                    /* Set the flag to block the soft execution */
                  ubSoftBootable = BM_FALSE;
                }
            }
#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
        }
        else
        {
            /* Do nothing */
        }
    }
#endif /*(BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)*/
#endif /*(BM_IMPL_VARIANT == BM_IMPL_10)*/

  return ubSoftBootable;

}
#endif /* ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON)) */
