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
/*%%   _____________________________   %%  \file BM_Security.c                   */
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

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: Variable Types                                                */


/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */

#include "EB_Prj.h"
#include "BM_Priv.h"
#include <BM_Trace.h>

#if (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER)
#if (BM_CSM_PRESENT == STD_ON)
#include "Csm.h"
#endif

/*                                                                               */
/*===============================================================================*/




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

#if (BM_CSM_HASH_USED == STD_ON)
 u32 m_ulDigestLength;
#elif (BM_CSM_MAC_USED == STD_ON)
/* Key used for the MAC algorithm */
 Csm_SymKeyType m_stBMMacKey;
#endif
#if ((BM_CSM_HASH_USED == STD_ON) || (BM_CSM_MAC_USED == STD_ON))
 u8  m_ubCsmFinished;
 Csm_ReturnType m_ubCsmResult;
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
 const u8 * m_pubDataBuffer;
 u32 m_uwDataLength;
#if (BM_CSM_HASH_USED == STD_ON)
 u8 * m_pubChecksum;
#elif (BM_CSM_MAC_USED == STD_ON)
const u8 * m_pubChecksum;
#endif
#endif
#endif
#endif

#if (BM_CSM_MAC_USED == STD_ON)
#define BM_CSMRESULT_START_SEC_VAR
#include <MemMap.h>
 Csm_VerifyResultType m_eCsmResult = CSM_E_VER_NOT_OK;
#define BM_CSMRESULT_STOP_SEC_VAR
#include <MemMap.h>
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
#if ((BM_CSM_MAC_USED == STD_ON) && (BM_HSM_MAC_USED != STD_ON))
NCS_PRI_VAR void BM_GetMacKey(Csm_SymKeyType* pstMacKey);
#endif
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - PrivateFunctions                                                            */
/*------------------------------{BM_GetMacKey}------------------------------*/
#if ((BM_CSM_MAC_USED == STD_ON) && (BM_HSM_MAC_USED != STD_ON))
NCS_PRI_VAR void BM_GetMacKey(Csm_SymKeyType* pstMacKey)
{
#if ((BM_CRYSHE_PRESENT == STD_OFF) && (BM_CSM_ASR43_USED == STD_OFF))
    u8 ubIdx;
#endif
#if ((BM_CRYSHE_PRESENT == STD_ON) || (BM_CSM_ASR43_USED == STD_ON))
    u32 ulIndex;
#endif
    const u8 * paubKeyData;
#if ((BM_CRYSHE_PRESENT == STD_ON) || (BM_CSM_ASR43_USED == STD_ON))
    u8 * paubKeyDataPtr;
#endif
    u32 ulMacKeyLength;
    BM_CustomGetMacKey(&paubKeyData, &ulMacKeyLength);

    pstMacKey->length = ulMacKeyLength;
#if ((BM_CRYSHE_PRESENT == STD_ON) || (BM_CSM_ASR43_USED == STD_ON))
    paubKeyDataPtr = (u8*)&(pstMacKey->data[0]);
    for (ulIndex = 0U; ulIndex < (ulMacKeyLength); ulIndex++)
    {
        paubKeyDataPtr[ulIndex]  = paubKeyData[ulIndex];
    }
#else
    for (ubIdx = 0U; ubIdx < (ulMacKeyLength/sizeof(u32)); ubIdx++)
    {
        pstMacKey->data[ubIdx]  = (u32)paubKeyData[((u16)((u16)ulMacKeyLength - 1U) - ((u16)ubIdx*4U))];
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 2U) - ((u16)ubIdx*4U))] << 8U)  & 0x0000FF00U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif
}
/*----------------------{End BM_GetMacKey}---------------------------*/
#endif

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
#if (BM_CSM_HASH_USED == STD_ON)
tBMBoolean BM_ComputeHash(u8 const * pubDataToSign, u32 uwDataLength, u8 * pubHashValue)
{
    tBMBoolean eComputeSuccess = BM_FALSE;
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
    u32 uwSlicedDataLength;
#endif
#endif

    m_ubCsmFinished = BM_FALSE;
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
    m_pubDataBuffer = pubDataToSign;
    m_uwDataLength = uwDataLength;
    m_pubChecksum = pubHashValue;
#endif
#endif

    m_ulDigestLength  = BM_CHECKSUM_SIZE_IN_BYTES;

    /* Start the hash calculation */
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_CSM_CANCELJOB_ENABLED == STD_ON)
    (void)Csm_CancelJob(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_START);
#endif /*(BM_CSM_CANCELJOB_ENABLED == STD_ON)*/
    /* Before the use of the key, set the key state to valid*/
    (void)Csm_KeySetValid(BM_CSM_KEY_ID);

    m_ubCsmResult = Csm_Hash(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_START,
                             pubDataToSign, uwDataLength,
                             pubHashValue, &m_ulDigestLength);
#else
    m_ubCsmResult = Csm_HashStart(BM_CSM_CHECKSUM_ID);
#endif

    if (CSM_E_OK == m_ubCsmResult)
    {
        while (BM_FALSE == m_ubCsmFinished)
        {
            /* call to Crypto/CSM/Demo main function*/
            BM_Csm_Mainfunction();
            BM_CustomBckOperation();
#if (BM_CSM_ASR43_USED == STD_ON)
            /* CSM job never provides callback for the start operation completion in Crypto Stack ASR4.3 */
            break;
#endif
        }

        m_ubCsmFinished = BM_FALSE;

        if (CSM_E_OK == m_ubCsmResult)
        {
            /* Update the Hash calculation */
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
            if (uwDataLength > (u32)BM_BLOC_SLICING_SIZE)
            {
                uwSlicedDataLength = BM_BLOC_SLICING_SIZE;
                m_uwDataLength -= (u32)BM_BLOC_SLICING_SIZE;
            }
            else
            {
                uwSlicedDataLength = uwDataLength;
                m_uwDataLength = 0U;
            }

            m_ubCsmResult = Csm_Hash(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_UPDATE,
                                     pubDataToSign, uwSlicedDataLength,
                                     pubHashValue, &m_ulDigestLength);
#else
            m_ubCsmResult = Csm_Hash(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_UPDATE,
                                     pubDataToSign, uwDataLength,
                                     pubHashValue, &m_ulDigestLength);
#endif /*(BM_BLOC_SLICING_ENABLED == STD_ON)*/
#else
            m_ubCsmResult = Csm_HashUpdate(BM_CSM_CHECKSUM_ID, pubDataToSign, uwDataLength);
#endif /*(BM_CSM_ASR43_USED == STD_ON)*/
            if (CSM_E_OK == m_ubCsmResult)
            {
                while (BM_FALSE == m_ubCsmFinished)
                {
                    /* call to Crypto/CSM/Demo main function*/
                    BM_Csm_Mainfunction();

                    BM_CustomBckOperation();
                }

                m_ubCsmFinished = BM_FALSE;

                if (CSM_E_OK == m_ubCsmResult)
                {
                    /* Finish the hash calculation */
#if (BM_CSM_ASR43_USED == STD_ON)
                    m_ubCsmResult = Csm_Hash(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_FINISH,
                                             pubDataToSign, uwDataLength,
                                             pubHashValue, &m_ulDigestLength);
#else
                    m_ubCsmResult = Csm_HashFinish(BM_CSM_CHECKSUM_ID, pubHashValue, &m_ulDigestLength, FALSE);
#endif
                    if (CSM_E_OK == m_ubCsmResult)
                    {
                        while (BM_FALSE == m_ubCsmFinished)
                        {
                            /* call to Crypto/CSM/Demo main function*/
                            BM_Csm_Mainfunction();

                            BM_CustomBckOperation();
                        }

                        eComputeSuccess = BM_TRUE;
                    }
                }
            }
        }
    }

    return eComputeSuccess;
}
#endif

#if (BM_CSM_MAC_USED == STD_ON)
tBMBoolean BM_VerifyMac(const u8 * pubExpectedChecksum, const u8 * pubDataToSign, u32 uwDataLength)
{
    tBMBoolean eComputeSuccess = BM_FALSE;
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
    u32 uwSlicedDataLength;
#endif
#endif

    m_ubCsmFinished = BM_FALSE;
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
    m_pubDataBuffer = pubDataToSign;
    m_uwDataLength = uwDataLength;
    m_pubChecksum = pubExpectedChecksum;
#endif
#endif

    BM_DisableECCCheck();
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_CSM_SET_KEY_ENABLED == STD_ON)
    /* Get the key used for MAC algorithm */
    BM_GetMacKey(&m_stBMMacKey);
#endif
#else /*(BM_CSM_ASR43_USED == STD_OFF)*/
    /* Get the key used for MAC algorithm */
    BM_GetMacKey(&m_stBMMacKey);
#endif
    /* Start the Mac calculation */
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_CSM_CANCELJOB_ENABLED == STD_ON)
    (void)Csm_CancelJob(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_START);
#endif /*(BM_CSM_CANCELJOB_ENABLED == STD_ON)*/
#if (BM_CSM_SET_KEY_ENABLED == STD_ON)
    (void)Csm_KeyElementSet(BM_CSM_KEY_ID,
                      BM_CSM_KEY_ELEMENT_ID,
                      (uint8 const*)m_stBMMacKey.data,
                      m_stBMMacKey.length);
#endif /*(BM_CSM_SET_KEY_ENABLED == STD_ON)*/
    /* Before the use of the key, set the key state to valid*/
    (void)Csm_KeySetValid(BM_CSM_KEY_ID);

    m_ubCsmResult = Csm_MacVerify(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_START,
                                  pubDataToSign, uwDataLength, pubExpectedChecksum, BM_CHECKSUM_SIZE_IN_BITS, &m_eCsmResult);
#else
    m_ubCsmResult = Csm_MacVerifyStart(BM_CSM_CHECKSUM_ID, &m_stBMMacKey);
#endif/*(BM_CSM_ASR43_USED == STD_ON)*/
    if (CSM_E_OK == m_ubCsmResult)
    {
        while (BM_FALSE == m_ubCsmFinished)
        {
            /* call to Crypto/CSM Integration main function */
            BM_Csm_Mainfunction();

            /* Perform Background operation while the crypto operation is in progress */
            BM_CustomBckOperation();
#if (BM_CSM_ASR43_USED == STD_ON)
            /* CSM job never provides callback for the start operation completion in Crypto Stack ASR4.3 */
            break;
#endif
        }

        m_ubCsmFinished = BM_FALSE;

        if (CSM_E_OK == m_ubCsmResult)
        {
            /* Update the Mac calculation */
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
            if (uwDataLength > (u32)BM_BLOC_SLICING_SIZE)
            {
                uwSlicedDataLength = BM_BLOC_SLICING_SIZE;
                m_uwDataLength -= (u32)BM_BLOC_SLICING_SIZE;
            }
            else
            {
                uwSlicedDataLength = uwDataLength;
                m_uwDataLength = 0U;
            }

            m_ubCsmResult = Csm_MacVerify(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_UPDATE,
                                          pubDataToSign, uwSlicedDataLength,
                                          pubExpectedChecksum, BM_CHECKSUM_SIZE_IN_BITS, &m_eCsmResult);
#else
            m_ubCsmResult = Csm_MacVerify(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_UPDATE,
                                          pubDataToSign, uwDataLength,
                                          pubExpectedChecksum, BM_CHECKSUM_SIZE_IN_BITS, &m_eCsmResult);
#endif /*(BM_BLOC_SLICING_ENABLED == STD_ON)*/
#else
            m_ubCsmResult = Csm_MacVerifyUpdate(BM_CSM_CHECKSUM_ID, pubDataToSign, uwDataLength);
#endif /*(BM_CSM_ASR43_USED == STD_ON)*/

            if (CSM_E_OK == m_ubCsmResult)
            {
                while (BM_FALSE == m_ubCsmFinished)
                {
                    /* call to Crypto/CSM/DemoWrapper Integration main function*/
                    BM_Csm_Mainfunction();

                    /* Perform Background operation while the crypto operation is in progress*/
                    BM_CustomBckOperation();
                }

                m_ubCsmFinished = BM_FALSE;

                if (CSM_E_OK == m_ubCsmResult)
                {
                  /* Finish the Mac calculation */
#if (BM_CSM_ASR43_USED == STD_ON)
                    m_ubCsmResult = Csm_MacVerify(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_FINISH,
                                                  pubDataToSign, uwDataLength,
                                                  pubExpectedChecksum, BM_CHECKSUM_SIZE_IN_BITS, &m_eCsmResult);
#else
                    m_ubCsmResult = Csm_MacVerifyFinish(BM_CSM_CHECKSUM_ID, pubExpectedChecksum, BM_CHECKSUM_SIZE_IN_BITS, &m_eCsmResult);
#endif

                    if (CSM_E_OK == m_ubCsmResult)
                    {
                        while (BM_FALSE == m_ubCsmFinished)
                        {
                            /* call to Crypto/CSM/Demo main function*/
                            BM_Csm_Mainfunction();

                            /* Perform Background operation while the crypto operation is in progress*/
                            BM_CustomBckOperation();
                        }

                        if (CSM_E_VER_OK == m_eCsmResult)
                        {
                            /* The comparison of MAC returned success status */
                            eComputeSuccess = BM_TRUE;
                        }
                    }
                }
            }
        }
    }

    BM_EnableECCCheck();
    return eComputeSuccess;
}
#endif

#if ((BM_CSM_HASH_USED == STD_ON) || (BM_CSM_MAC_USED == STD_ON))
/*-------------------------------{BM_CsmNotification}--------------------------*/
#if (BM_CSM_ASR43_USED == STD_ON)
FUNC(void, CSM_APPL_CODE) BM_CsmNotification(P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job, Std_ReturnType result)
#else
Std_ReturnType BM_CsmNotification(Csm_ReturnType result)
#endif
{
#if (BM_CSM_ASR43_USED == STD_ON)
#if (BM_BLOC_SLICING_ENABLED == STD_ON)
    u32 uwDataLength;
    if ((CSM_E_OK == m_ubCsmResult) && (m_uwDataLength > 0U))
    {
        m_pubDataBuffer += BM_BLOC_SLICING_SIZE;

        if (m_uwDataLength > (u32)BM_BLOC_SLICING_SIZE)
        {
            uwDataLength = BM_BLOC_SLICING_SIZE;
            m_uwDataLength -= (u32)BM_BLOC_SLICING_SIZE;
        }
        else
        {
            uwDataLength = m_uwDataLength;
            m_uwDataLength = 0U;
        }
#if (BM_CSM_MAC_USED == STD_ON)
        m_ubCsmResult = Csm_MacVerify(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_UPDATE,
                                      m_pubDataBuffer, uwDataLength,
                                      m_pubChecksum, BM_CHECKSUM_SIZE_IN_BITS, &m_eCsmResult);
#elif (BM_CSM_HASH_USED == STD_ON)
        m_ubCsmResult = Csm_Hash(BM_CSM_CHECKSUM_ID, CRYPTO_OPERATIONMODE_UPDATE,
                                 m_pubDataBuffer, uwDataLength,
                                 m_pubChecksum, &m_ulDigestLength);
#endif /*(BM_CSM_MAC_USED == STD_ON)*/
    }
    else
    {
        /* Finish the Csm operation */
        m_ubCsmFinished = BM_TRUE;
        /* Update Csm status variables */
        m_ubCsmResult = result;
    }
#else
    /* Finish the Csm operation */
    m_ubCsmFinished = BM_TRUE;
    /* Update Csm status variables */
    m_ubCsmResult = result;
#endif /*(BM_BLOC_SLICING_ENABLED == STD_ON)*/
    OSC_PARAM_UNUSED(job);
#else /*(BM_CSM_ASR43_USED == STD_OFF)*/
    /* Finish the Csm operation */
    m_ubCsmFinished = BM_TRUE;
    /* Update Csm status variables */
    m_ubCsmResult = result;

    return E_OK;
#endif /*(BM_CSM_ASR43_USED == STD_ON)*/
}
/*------------------------------{end BM_CsmNotification}------------------------*/
#endif /* ((BM_CSM_HASH_USED == STD_ON) || (BM_CSM_MAC_USED == STD_ON)) */
#endif /* (BM_BOOT_MANAGER_VARIANT == BM_BOOT_MANAGER) */

#if (BM_HSM_MAC_USED == STD_ON)
/*-------------------------------{BM_HsmVerifyMac}--------------------------*/
tBMBoolean BM_HsmVerifyMac(u16 uwBlockId)
{
    tBMBoolean      ubLocReturn;
    tBMHsmJobResult ubJobResult;

    ubLocReturn = BM_TRUE;

    BM_DisableECCCheck();

    do
    {
        ubJobResult = BM_CustomHsmVerifyMac(uwBlockId);

        BM_CustomBckOperation();
    }
    while (ubJobResult == BM_HSM_JOB_PENDING);

    BM_EnableECCCheck();

    if (ubJobResult == BM_HSM_JOB_FAILED)
    {
        ubLocReturn = BM_FALSE;
    }

    return ubLocReturn;
}
/*------------------------------{end BM_HsmVerifyMac}------------------------*/
#endif /* (BM_HSM_MAC_USED == STD_ON)*/
