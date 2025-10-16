/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cry.c                      */
/*%%  |                             |  %%  \brief PROG cryptography feature      */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 */
/* NOCOV List
 *
 * NOCOV-EMPTYDEFAULT:
 *   defensive code.
 *
 * Reason:
 * Defensive case which shall never happen.
 *
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
#if (PROG_CRY_PRESENT == STD_ON)
#include "PROG_Cry.h"
#if (PROG_CSMASR43_USED == STD_OFF)
#include "Cry_LN.h"
#endif/*(PROG_CSMASR43_USED == STD_OFF)*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */
#if (PROG_CSMASR43_USED == STD_ON)
NCS_PRI_VAR u8 m_ubActiveProgCsmTableId;
NCS_PRI_VAR u32 m_ulCryptoProcessedDataLength;
NCS_PRI_VAR u32 m_ulCryptoPendingDataLength;
NCS_PRI_VAR u32 m_ulCryptoTotalBlockDataLength;
NCS_PRI_VAR const Csm_AsymPublicKeyType* m_pstAsymPublicKey;
#endif
NCS_PRI_VAR tProgStatus m_eCryptoStatus;
#if ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_MAC_USED == STD_ON) || (PROG_CSMASR43_USED == STD_ON)  || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
NCS_PRI_VAR u8 const * m_pubCryptoData;
NCS_PRI_VAR u32 m_ulCryptoDataSize;
#endif /* ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_HASH_CALCULATION == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))) */

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
NCS_PRI_VAR const u8* m_pubProgCryptoSignature;
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
NCS_PRI_VAR u8* m_pubHashValue;
#endif
#if (PROG_CSM_MAC_USED == STD_ON)
NCS_PRI_VAR u8* m_pubMacValue;
NCS_PRI_VAR Csm_SymKeyType m_stProgMacKey;
#endif


#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON) || (PROG_CSM_MAC_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
#if (PROG_CSMASR43_USED == STD_OFF)
NCS_PRI_VAR u16 m_uwCsmConfigId;
#endif
NCS_PRI_VAR u32 m_ulDigestLength;
#endif

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
NCS_PRI_VAR Csm_VerifyResultType m_ubProgVerifyResult;
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

NCS_PRI_VAR tProgCryState m_eCryptoState;

#if((PROG_CSM_CANCELJOB_ENABLED == STD_ON) || (PROG_SIGNFIN_SENDFRP == STD_ON) || (PROG_HASHFIN_SENDFRP == STD_ON))
NCS_PRI_VAR tProgCryState m_eCryptoStateOnHold;
#endif
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
/** \brief Treat the Csm signature check notification **/
#if (PROG_SIGNATURE_CALCULATION == STD_ON)
NCS_PRI_FCT void PROG_CsmSignatureCheckNotification(void);
#endif /* (PROG_SIGNATURE_CALCULATION == STD_ON)*/

/** \brief Treat the Csm Hash notification **/
#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
NCS_PRI_FCT void PROG_CsmHashNotification(void);
#endif

/** \brief Treat the Csm Mac notification **/
#if (PROG_CSM_MAC_USED == STD_ON)
NCS_PRI_FCT void PROG_CsmMacGenerateNotification(void);
#endif
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */


/*---------------------------{PROG_VerifySignature}------------------------------*/
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON)
tProgStatus PROG_VerifySignature(const Csm_AsymPublicKeyType* pstAsymPublicKey, u8* pubData, u32 ulDataSize, const u8* pubSignature)
{
    tProgStatus eStatus;

    DBG_PROG_VERIFYSIGNATURE_ENTRY(pstAsymPublicKey, pubData, ulDataSize, pubSignature);

    m_pubCryptoData = pubData;
    m_ulCryptoDataSize = ulDataSize;

    eStatus = PROG_VerifySignatureStart(pstAsymPublicKey, pubSignature)

    DBG_PROG_VERIFYSIGNATURE_EXIT(eStatus);
    return eStatus;
}
#endif /* PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON */
/*--------------------------{End PROG_VerifySignature}---------------------------*/

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*---------------------------{PROG_VerifySignatureStart}-------------------------*/
tProgStatus PROG_VerifySignatureStart(const Csm_AsymPublicKeyType* pstAsymPublicKey, const u8* pubSignature)
{
    Csm_ReturnType eCsmStatus;
    tProgStatus eStatus;

    DBG_PROG_VERIFYSIGNATURESTART_ENTRY(pstAsymPublicKey, pubSignature);

    m_eCryptoStatus = PROG_E_BUSY;
    m_pubProgCryptoSignature = pubSignature;
#if (PROG_CSMASR43_USED == STD_ON)
    /* Steps to Start a New CSM 4.3 job*/
    m_ubActiveProgCsmTableId = PROG_CSMSIGNATUREJOBINDEX;
    eCsmStatus = PROG_CsmSetPreConditions((const u8*)pstAsymPublicKey, m_ubActiveProgCsmTableId);
    if (eCsmStatus == CSM_E_OK)
    {
#if (PROG_STREAMSTART_ENABLE == STD_OFF)
        eCsmStatus = Csm_SignatureVerify(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                        CRYPTO_OPERATIONMODE_START,
                                        &m_pubCryptoData[0U],
                                        m_ulCryptoDataSize,
                                        &m_pubProgCryptoSignature[0U],
                                        PROG_SIGNATURE_LENGTH,
                                        &m_ubProgVerifyResult);
#else
        eCsmStatus = Csm_SignatureVerify(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                        CRYPTO_OPERATIONMODE_STREAMSTART,
                                        &m_pubCryptoData[0U],
                                        0U,
                                        &m_pubProgCryptoSignature[0U],
                                        PROG_SIGNATURE_LENGTH,
                                        &m_ubProgVerifyResult);
#endif
    }
    else
    {
        /*Do nothing, return status is already set*/
    }
#else
    eCsmStatus = Csm_SignatureVerifyStart(PROG_CSM_SIG_VERIFY_ID, pstAsymPublicKey);
#endif
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    if (eCsmStatus == CRYPTO_E_JOB_CANCELED)
    {
        /* Wait until the Crypto Cancellation operation is completed and a notification is received */
        m_eCryptoStateOnHold = PROG_SIGNATURE_CHECK_START;
        m_eCryptoState       = PROG_CSM_JOBCANCEL_INPROGRESS;

        /*Store the key ptr for the later use*/
        m_pstAsymPublicKey   = pstAsymPublicKey;
    }
    else
#endif
    if(eCsmStatus != CSM_E_OK)
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
#if ((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11))
        m_ubCheckMemoryStatus = PROG_INVALID_PUBLIC_KEY;
#endif
     /*trigger event only for VCC and VWAG OEMs*/
#if (((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11))||((PROG_CRY_PRESENT == STD_ON) && (PROG_VERIFICATION_ON_THE_FLY == STD_ON)&&(PROG_SIGNATURE_CALCULATION_OVER_HASH == STD_OFF)&&(PROG_IMPL_VARIANT == PROG_IMPL_40)))
        /* Emit event PROG_EVENT_FAILED */
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
    }
    else
    {
#if (PROG_STREAMSTART_ENABLE == STD_OFF)
        /* No error occurred indicates that the Start operation was triggered successfully
         * set the current triggered job state */
        m_eCryptoState = PROG_SIGNATURE_CHECK_START;
#else
        /* No error occurred indicates that the StreamStart operation was triggered successfully
         * set the current triggered job state */
        m_eCryptoState = PROG_SIGNATURE_CHECK_STREAMSTART;
#endif
    }

    /* Return the Crypto status */
    eStatus = m_eCryptoStatus;

    DBG_PROG_VERIFYSIGNATURESTART_EXIT(eStatus);
    return eStatus;
}
/*----------------------{End PROG_VerifySignatureStart}--------------------------*/
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*---------------------------{PROG_VerifySignatureUpdate}------------------------*/
void PROG_VerifySignatureUpdate(u8 const * pubData, u32 ulDataSize)
{
    Csm_ReturnType eCsmStatus;
    DBG_PROG_VERIFYSIGNATUREUPDATE_ENTRY(pubData, ulDataSize);

    if(m_eCryptoStatus != PROG_E_NOT_OK)
    {
        m_eCryptoState = PROG_SIGNATURE_CHECK_UPDATE;
#if (PROG_CSMASR43_USED == STD_ON)
        PROG_SetCryptoDataSizeDataAdr(pubData, ulDataSize);
        eCsmStatus = Csm_SignatureVerify(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                        CRYPTO_OPERATIONMODE_UPDATE,
                                        &m_pubCryptoData[0U],
                                        m_ulCryptoDataSize,
                                        &m_pubProgCryptoSignature[0U],
                                        PROG_SIGNATURE_LENGTH,
                                        &m_ubProgVerifyResult);
#else
        eCsmStatus = Csm_SignatureVerifyUpdate(PROG_CSM_SIG_VERIFY_ID, pubData, ulDataSize);
#endif /*(PROG_CSMASR43_USED == STD_ON)*/
        PROG_CsmCheckResult(eCsmStatus);
    }
    DBG_PROG_VERIFYSIGNATUREUPDATE_EXIT();
}
/*--------------------------{End PROG_VerifySignatureUpdate}---------------------*/

/*---------------------------{PROG_VerifySignatureFinish}------------------------*/
void PROG_VerifySignatureFinish(const u8* pubSignature)
{
    Csm_ReturnType eCsmStatus = CSM_E_OK;
    DBG_PROG_VERIFYSIGNATUREFINISH_ENTRY(pubSignature);

    if(m_eCryptoStatus != PROG_E_NOT_OK)
    {
        if (pubSignature != NULL_PTR)
        {
            /* Update expected signature with the provided one */
            m_pubProgCryptoSignature = pubSignature;
        }
        m_eCryptoState = PROG_SIGNATURE_CHECK_FINISH;
#if (PROG_SIGNFIN_SENDFRP == STD_ON)
        /* Trigger to provide a response pending to prevent communication timeouts in
         * case the duration of crypto processing takes long time */
        if (m_eCryptoStateOnHold != PROG_SIGNATURE_CHECK_FINISH)
        {
            UDS_StopNRC78Timer();
            m_eCryptoStateOnHold = m_eCryptoState;

            /* Update the status to ok to continue to execute the finish operation */
            eCsmStatus = CSM_E_OK;
        }
        else
        {
            /* FRP sent, execute the job on hold */
            m_eCryptoStateOnHold = PROG_IDLE;
        }
#endif
#if (PROG_CSMASR43_USED == STD_ON)
#if (PROG_SIGNFIN_SENDFRP == STD_ON)
        if (m_eCryptoStateOnHold == PROG_IDLE)
#endif
        {
            eCsmStatus = Csm_SignatureVerify(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                            CRYPTO_OPERATIONMODE_FINISH,
                                            &m_pubCryptoData[0U],
                                            m_ulCryptoDataSize,
                                            &m_pubProgCryptoSignature[0U],
                                            PROG_SIGNATURE_LENGTH,
                                            &m_ubProgVerifyResult);
        }
#else
        eCsmStatus = Csm_SignatureVerifyFinish(PROG_CSM_SIG_VERIFY_ID,
                                                m_pubProgCryptoSignature,
                                                PROG_SIGNATURE_LENGTH,
                                                &m_ubProgVerifyResult);
#endif
        PROG_CsmCheckResult(eCsmStatus);
    }
    DBG_PROG_VERIFYSIGNATUREFINISH_EXIT();
}
/*--------------------------{End PROG_VerifySignatureFinish}---------------------*/
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

/*---------------------------{PROG_GetCryptoStatus}------------------------------*/
tProgStatus PROG_GetCryptoStatus(void)
{
    tProgStatus eStatus;

    DBG_PROG_GETCRYPTOSTATUS_ENTRY();
    eStatus = m_eCryptoStatus;
    DBG_PROG_GETCRYPTOSTATUS_EXIT(eStatus);
    return eStatus;
}
/*--------------------------{End PROG_GetCryptoStatus}---------------------------*/

/*---------------------------{PROG_GetCryptoState}-------------------------------*/
tProgCryState PROG_GetCryptoState(void)
{
    tProgCryState eState;

    DBG_PROG_GETCRYPTOSTATE_ENTRY();
    eState = m_eCryptoState;
    DBG_PROG_GETCRYPTOSTATE_EXIT(eState);
    return eState;
}
/*--------------------------{End PROG_GetCryptoState}----------------------------*/
#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
/*---------------------------{PROG_ComputeHashStart}-----------------------------*/
tProgStatus PROG_ComputeHashStart(u16 uwCsmConfigId, u8 const * pubData,u32 ulDataSize, u8 * pubHashResult)
{
    Csm_ReturnType eCsmStatus;
    tProgStatus    eProgStatus;

#if (PROG_CSM_HASH_USED == STD_OFF)
    OSC_PARAM_UNUSED(pubHashResult);
#endif

    DBG_PROG_COMPUTEHASHSTART_ENTRY(uwCsmConfigId,pubData,ulDataSize,pubHashResult);

    m_eCryptoStatus = PROG_E_BUSY;
    m_ulDigestLength = PROG_DIGEST_LENGTH;

    if (NULL_PTR != pubData)
    {
        m_pubCryptoData = pubData;
        m_ulCryptoDataSize = ulDataSize;
#if (PROG_CSM_HASH_USED == STD_ON)
        m_pubHashValue = pubHashResult;
#endif
    }
#if (PROG_CSMASR43_USED == STD_ON)
    /* Steps to Start a New CSM 4.3 job*/
    m_ubActiveProgCsmTableId = (u8)uwCsmConfigId;
    eCsmStatus = PROG_CsmSetPreConditions(NULL_PTR, m_ubActiveProgCsmTableId);
    if (eCsmStatus == CSM_E_OK)
    {
        eCsmStatus = Csm_Hash(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                            CRYPTO_OPERATIONMODE_START,
                            &m_pubCryptoData[0U],
                            m_ulCryptoDataSize,
                            m_pubHashValue,
                            &m_ulDigestLength);
    }
    else
    {
        /*Do nothing, return status is already set*/
    }
#else
    m_uwCsmConfigId = uwCsmConfigId;
    eCsmStatus = Csm_HashStart(m_uwCsmConfigId);
#endif
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    if (eCsmStatus == CRYPTO_E_JOB_CANCELED)
    {
        /* Wait until the Crypto Cancellation operation is completed and a notification is received */
        m_eCryptoStateOnHold = PROG_HASH_START;
        m_eCryptoState       = PROG_CSM_JOBCANCEL_INPROGRESS;

        /* Set status as ok to continue the Crypto operation */
        eProgStatus          = PROG_E_OK;
    }
    else
#endif
    if (CSM_E_OK != eCsmStatus)
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
        eProgStatus     = PROG_E_NOT_OK;
    }
    else
    {
        eProgStatus     = PROG_E_OK;
        m_eCryptoState  = PROG_HASH_START;
    }

    DBG_PROG_COMPUTEHASHSTART_EXIT(eProgStatus);

    return eProgStatus;
}
/*--------------------------{End Prog_ComputeHashStart}--------------------------*/

/*---------------------------{PROG_ComputeHashUpdate}----------------------------*/
void PROG_ComputeHashUpdate(u8 const * pubData, u32 ulDataSize)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_COMPUTEHASHUPDATE_ENTRY(pubData, ulDataSize);

    if(m_eCryptoStatus != PROG_E_NOT_OK)
    {
        m_eCryptoState = PROG_HASH_UPDATE;
#if (PROG_CSMASR43_USED == STD_ON)
        PROG_SetCryptoDataSizeDataAdr(pubData, ulDataSize);
        eCsmStatus = Csm_Hash(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                            CRYPTO_OPERATIONMODE_UPDATE,
                            &m_pubCryptoData[0U],
                            m_ulCryptoDataSize,
                            m_pubHashValue,
                            &m_ulDigestLength);
#else
        eCsmStatus = Csm_HashUpdate(m_uwCsmConfigId, pubData, ulDataSize);
#endif
        PROG_CsmCheckResult(eCsmStatus);
    }
    DBG_PROG_COMPUTEHASHUPDATE_EXIT();
}
/*--------------------------{End PROG_ComputeHashUpdate}-------------------------*/

/*---------------------------{PROG_ComputeHashFinish}----------------------------*/
void PROG_ComputeHashFinish(u8* pubHashValue)
{
    Csm_ReturnType eCsmStatus = CSM_E_OK;

    DBG_PROG_COMPUTEHASHFINISH_ENTRY(pubHashValue);

    if((m_eCryptoStatus != PROG_E_NOT_OK) && (m_eCryptoState == PROG_HASH_END))
    {
        m_eCryptoState = PROG_HASH_FINISH;
#if (PROG_HASHFIN_SENDFRP == STD_ON)
        /* Trigger to provide a response pending to prevent communication timeouts in
         * case the duration of crypto processing takes long time */
        if (m_eCryptoStateOnHold != PROG_HASH_FINISH)
        {
            UDS_StopNRC78Timer();
            m_eCryptoStateOnHold = m_eCryptoState;
            m_pubHashValue = pubHashValue;

            /* Update the status to ok to continue to execute the finish operation */
            eCsmStatus = CSM_E_OK;
        }
        else
        {
            /* FRP sent, execute the job on hold */
            m_eCryptoStateOnHold = PROG_IDLE;
        }
#endif
#if (PROG_CSMASR43_USED == STD_ON)
#if (PROG_HASHFIN_SENDFRP == STD_ON)
        if (m_eCryptoStateOnHold == PROG_IDLE)
#endif
        {
            eCsmStatus = Csm_Hash(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                CRYPTO_OPERATIONMODE_FINISH,
                                &m_pubCryptoData[0U],
                                m_ulCryptoDataSize,
                                pubHashValue,
                                &m_ulDigestLength);
        }
#else
        eCsmStatus = Csm_HashFinish(m_uwCsmConfigId, pubHashValue, &m_ulDigestLength, FALSE);
#endif
        PROG_CsmCheckResult(eCsmStatus);
    }
    DBG_PROG_COMPUTEHASHFINISH_EXIT();
}
/*--------------------------{End PROG_ComputeHashFinish}-------------------------*/
#endif /* ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))) */

#if (PROG_CSM_MAC_USED == STD_ON)
/*-----------------------{PROG_CsmMacGenerateNotification}-----------------------*/
NCS_PRI_FCT void PROG_CsmMacGenerateNotification(void)
{
#if (PROG_CSM_MAC_USED == STD_ON)
    tProgBoolean eProgBoolean;
    Csm_ReturnType eCsmStatus;
#endif
    switch (m_eCryptoState)
    {
        case PROG_MAC_GENERATE_START:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_MAC_GENERATE_START_END;

#if (PROG_CSM_MAC_USED == STD_ON)
            /* Check if Mac computation is for Authentication. In positive case all crypto calculation triggering is performed */
            eProgBoolean = PROG_SecurityPendingOperation();

            if (PROG_TRUE == eProgBoolean)
            {
                m_eCryptoState = PROG_MAC_GENERATE_UPDATE;
#if (PROG_CSMASR43_USED == STD_ON)
                PROG_SetCryptoDataSizeDataAdr(&m_pubCryptoData[0U], m_ulCryptoDataSize);
                eCsmStatus = Csm_MacGenerate(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                            CRYPTO_OPERATIONMODE_UPDATE,
                                            &m_pubCryptoData[0U],
                                            m_ulCryptoDataSize,
                                            m_pubMacValue,
                                            &m_ulDigestLength);
#else
                eCsmStatus = Csm_MacGenerateUpdate(m_uwCsmConfigId, m_pubCryptoData, m_ulCryptoDataSize);
#endif
                PROG_CsmCheckResult(eCsmStatus);
            }
            else
            {
                /* Nothing to do */
            }
#endif
            break;


        case PROG_MAC_GENERATE_UPDATE:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_MAC_GENERATE_UPDATE_END;

#if (PROG_CSM_MAC_USED == STD_ON)
            /* Check if Mac computation is for Authentication. In positive case all crypto calculation triggering is performed */
            eProgBoolean = PROG_SecurityPendingOperation();

            if (PROG_TRUE == eProgBoolean)
            {
                m_ulDigestLength = PROG_SECURE_CHECKSUM_SIZE_IN_BITS;
                m_eCryptoState = PROG_MAC_GENERATE_FINISH;
#if (PROG_CSMASR43_USED == STD_ON)
                eCsmStatus = Csm_MacGenerate(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId,
                                            CRYPTO_OPERATIONMODE_FINISH,
                                            &m_pubCryptoData[0U],
                                            m_ulCryptoDataSize,
                                            m_pubMacValue,
                                            &m_ulDigestLength);
#else
                eCsmStatus = Csm_MacGenerateFinish(m_uwCsmConfigId, m_pubMacValue, &m_ulDigestLength, FALSE);
#endif
                PROG_CsmCheckResult(eCsmStatus);
            }
            else
#endif
            {
                /* Nothing to do */
            }
            break;



        case PROG_MAC_GENERATE_FINISH:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_IDLE;

#if (PROG_CSM_MAC_USED == STD_ON)
            /* Check if hash computation is for Authentication. In positive case all crypto calculation triggering is performed */
            /* directly in not */
            eProgBoolean = PROG_SecurityPendingOperation();

            if (PROG_TRUE == eProgBoolean)
            {
                /* Notify security feature with hash value */
                PROG_SecurityChecksumNotification();
            }
            else
#endif
            {
                /* Emit event PROG_EVENT_CRYPTO_FINISH */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
            }
            break;
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            m_eCryptoStatus = PROG_E_NOT_OK;
            m_eCryptoState = PROG_IDLE;
            /*push failed event*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
/* CHECK: PARSE */
    }
}
/*----------------------{End PROG_CsmMacGenerateNotification}--------------------*/

#if (PROG_HSM_MAC_USED == STD_OFF)
/*------------------------------{PROG_GetMacKey}---------------------------------*/
void PROG_GetMacKey(Csm_SymKeyType* pstMacKey)
{
#if ((PROG_CRYSHE_PRESENT == STD_ON)|| (PROG_CSMASR43_USED == STD_ON))
    u32 ulIndex;
    u8 * paubKeyDataPtr;
#else
    u8 ubIdx;
#endif
    const u8 * paubKeyData;
    u32 ulMacKeyLength;

    DBG_PROG_GETMACKEY_ENTRY(pstMacKey);

    (void)PROG_CustomGetMacKey(&paubKeyData, &ulMacKeyLength);

    pstMacKey->length = ulMacKeyLength;

#if ((PROG_CRYSHE_PRESENT == STD_ON) || (PROG_CSMASR43_USED == STD_ON))
    paubKeyDataPtr = (u8*)&(pstMacKey->data[0]);
    for (ulIndex = 0U; ulIndex < (ulMacKeyLength); ulIndex++)
    {
        paubKeyDataPtr[ulIndex]  = paubKeyData[ulIndex];
    }
#else
    for (ubIdx = 0U; ubIdx < (ulMacKeyLength/sizeof(u32)); ubIdx++)
    {
        pstMacKey->data[ubIdx]  = (u32)            paubKeyData[((u16)((u16)ulMacKeyLength - 1U) - ((u16)ubIdx*4U))];
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 2U) - ((u16)ubIdx*4U))] << 8U)  & 0x0000FF00U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif
    DBG_PROG_GETMACKEY_EXIT();
}
/*----------------------{End PROG_GetMacKey}-------------------------------------*/
#endif
/*---------------------------{PROG_MacGenerateStart}-----------------------------*/
tProgStatus PROG_MacGenerateStart(u16 uwCsmConfigId, u8 const * pubData, u32 ulDataSize, u8 * pubMacResult)
{
    Csm_ReturnType eCsmStatus;
    tProgStatus    eProgStatus;

    DBG_PROG_MACGENERATESTART_ENTRY(uwCsmConfigId,pubData,ulDataSize,pubMacResult);

    m_eCryptoStatus = PROG_E_BUSY;

    if (NULL_PTR != pubData)
    {
        m_pubCryptoData = pubData;
        m_ulCryptoDataSize = ulDataSize;
#if (PROG_CSM_MAC_USED == STD_ON)
        m_pubMacValue = pubMacResult;
#endif
    }
#if (PROG_HSM_MAC_USED == STD_OFF)
    PROG_GetMacKey(&m_stProgMacKey);
#endif
#if (PROG_CSMASR43_USED == STD_ON)
    /* Steps to Start a New CSM 4.3 job*/
    m_ubActiveProgCsmTableId = (u8)uwCsmConfigId;
    eCsmStatus = PROG_CsmSetPreConditions((u8*)&m_stProgMacKey, m_ubActiveProgCsmTableId);

    if (eCsmStatus == CSM_E_OK)
    {
        eCsmStatus = Csm_MacGenerate(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulCsmJobId, CRYPTO_OPERATIONMODE_START,\
                &m_pubCryptoData[0U], m_ulCryptoDataSize, m_pubMacValue, &m_ulDigestLength);
    }
    else
    {
        /*Do nothing, return status is already set*/
    }
#else
    m_uwCsmConfigId = uwCsmConfigId;
    eCsmStatus = Csm_MacGenerateStart(m_uwCsmConfigId, &m_stProgMacKey);
#endif
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    if (eCsmStatus == CRYPTO_E_JOB_CANCELED)
    {
        /* Wait until the Crypto Cancellation operation is completed and a notification is received */
        m_eCryptoStateOnHold = PROG_MAC_GENERATE_START;
        m_eCryptoState       = PROG_CSM_JOBCANCEL_INPROGRESS;

        /* Set status as ok to continue the Crypto operation */
        eProgStatus          = PROG_E_OK;
    }
    else
#endif
    if (CSM_E_OK != eCsmStatus)
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
        eProgStatus     = PROG_E_NOT_OK;
    }
    else
    {
        eProgStatus     = PROG_E_OK;
        m_eCryptoState  = PROG_MAC_GENERATE_START;
    }

    DBG_PROG_MACGENERATESTART_EXIT(eProgStatus);

    return eProgStatus;
}
/*--------------------------{End PROG_MacGenerateStart}--------------------------*/
#endif

#if (PROG_CSMASR43_USED == STD_OFF)
/*---------------------------{PROG_CsmNotification}------------------------------*/
Std_ReturnType PROG_CsmNotification(Csm_ReturnType eResult)
{
    Std_ReturnType RetVal = 0U;

    DBG_PROG_CSMNOTIFICATION_ENTRY(eResult);

#if ((PROG_SIGNATURE_CALCULATION == STD_ON) || (PROG_HASH_CALCULATION == STD_ON)|| (PROG_CSM_HASH_USED == STD_ON) || (PROG_CSM_MAC_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
    if (CSM_E_OK == eResult)
    {
        switch (m_eCryptoState)
        {
#if (PROG_SIGNATURE_CALCULATION == STD_ON)
            /* Management of the signature check */
            case PROG_SIGNATURE_CHECK_START:
            case PROG_SIGNATURE_CHECK_UPDATE:
            case PROG_SIGNATURE_CHECK_FINISH:
                PROG_CsmSignatureCheckNotification();
                break;
#endif /*#if (PROG_SIGNATURE_CALCULATION == STD_ON)*/
#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON)|| ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
            /* Management of the Hash */
            case PROG_HASH_START:
            case PROG_HASH_UPDATE:
            case PROG_HASH_FINISH :
                PROG_CsmHashNotification();
                break;
#endif /* ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON)|| ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))) */
#if (PROG_CSM_MAC_USED == STD_ON)
            /* Management of the Hash */
            case PROG_MAC_GENERATE_START:
            case PROG_MAC_GENERATE_UPDATE:
            case PROG_MAC_GENERATE_FINISH :
                PROG_CsmMacGenerateNotification();
                break;
#endif /* PROG_CSM_MAC_USED == STD_ON  */
            /* Shall not happened go back in stable state happened */
            default:
                m_eCryptoStatus = PROG_E_NOT_OK;
                m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
                break;
        }
    }
    else
#else
    OSC_PARAM_UNUSED(eResult);
#endif /*((PROG_SIGNATURE_CALCULATION == STD_ON) || (PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON)||
(PROG_CSM_MAC_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))*/
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
        m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
    }

    DBG_PROG_CSMNOTIFICATION_EXIT(RetVal);

    return RetVal;
}
/*--------------------------{End PROG_CsmNotification}---------------------------*/
#endif /*#if (PROG_CSMASR43_USED == STD_OFF)*/
#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*-----------------------{PROG_CsmSignatureCheckNotification}--------------------*/
NCS_PRI_FCT void PROG_CsmSignatureCheckNotification(void)
{
    switch(m_eCryptoState)
    {
    case PROG_SIGNATURE_CHECK_START:
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_OFF)
        m_eCryptoStatus = PROG_E_OK;
        m_eCryptoState = PROG_SIGNATURE_CHECK_START_END;
#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
        /* Emit event PROG_EVENT_CRYPTO_FINISH */
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_NOTIFY);
#endif
#else
        PROG_VerifySignatureUpdate(m_pubCryptoData, m_ulCryptoDataSize);
#endif
        break;

    case PROG_SIGNATURE_CHECK_UPDATE:
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_OFF)
        m_eCryptoStatus = PROG_E_OK;
        m_eCryptoState = PROG_SIGNATURE_CHECK_UPDATE_END;

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
        /* Emit event PROG_EVENT_CRYPTO_NOTIFY */
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_NOTIFY);
#endif
#else
        PROG_VerifySignatureFinish(m_pubProgCryptoSignature);
#endif
        break;

    case PROG_SIGNATURE_CHECK_FINISH:
        m_eCryptoStatus = PROG_E_OK;
        m_eCryptoState = PROG_IDLE;

        if (m_ubProgVerifyResult == CSM_E_VER_OK)
        {
            /* Emit event PROG_EVENT_CRYPTO_FINISH */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
        }
        else
        {
            m_eCryptoStatus = PROG_E_NOT_OK;
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
           /* Update the error code */
           PROG_SetErrorCodeSwitchingKeyFailure();
#endif
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
        }
        break;

        /* CHECK: NOPARSE */
        /* NOCOV-EMPTYDEFAULT */
    default:
        m_eCryptoStatus = PROG_E_NOT_OK;
        m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
        break;
        /* CHECK: PARSE */
    }
}
/*----------------------{End PROG_CsmSignatureCheckNotification}-----------------*/

/*------------------------------{PROG_GetPublicKey}------------------------------*/
void PROG_GetPublicKey(Csm_AsymPublicKeyType* pstPublicKey)
{
    u16 uwIdx;
#if ((PROG_CRY_EXPONENT_ENABLED == STD_ON) || (PROG_CSMASR43_USED == STD_ON))
    u16 uwLocIdx;
#endif
    const u8 * paubPublicModulus;
    u32 ulPublicExponent;

    PROG_CustomGetAsymPublicKey(&paubPublicModulus, &ulPublicExponent);
    pstPublicKey->length = 0U;
#if (PROG_CSMASR43_USED == STD_ON)
#if (PROG_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0U] = (u8)(ulPublicExponent >> 24U); /* Exponent */
    pstPublicKey->data[1U] = (u8)(ulPublicExponent >> 16U); /* Exponent */
    pstPublicKey->data[2U] = (u8)(ulPublicExponent >> 8U); /* Exponent */
    pstPublicKey->data[3U] = (u8)ulPublicExponent; /* Exponent */
    uwLocIdx = 4U;
#else
    uwLocIdx = 0U;
#endif
    for(uwIdx = 0U; /* Modulus */
        uwIdx < PROG_KEY_LENGTH;
        uwIdx++)
    {
        pstPublicKey->data[uwLocIdx] = paubPublicModulus[uwIdx];
        uwLocIdx++;
    }
#else
#if (PROG_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0] = 1U; /* Exponent size */
    pstPublicKey->data[1] = ulPublicExponent; /* Exponent */

    pstPublicKey->data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(uwIdx = 0U; /* Modulus */
        uwIdx < pstPublicKey->data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U];
        uwIdx++)
    {
        uwLocIdx = uwIdx + ((u16)(PROG_KEY_LENGTH/sizeof(u32))) + 2U;
        pstPublicKey->data[uwLocIdx] = (u32) paubPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((uwIdx*4U)))];
        pstPublicKey->data[uwLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)uwIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[uwLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)uwIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[uwLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)uwIdx*4U))] << 24U) & 0xFF000000U);
    }
#else
    pstPublicKey->data[0] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(uwIdx = 0U; /* Modulus */
        uwIdx < pstPublicKey->data[0];
        uwIdx++)
    {
        pstPublicKey->data[uwIdx + 1U] = (u32) paubPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((u16)uwIdx*4U))];
        pstPublicKey->data[uwIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)uwIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[uwIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)uwIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[uwIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)uwIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif
#endif /* (PROG_CSMASR43_USED == STD_ON)*/
}
/*----------------------------{End PROG_GetPublicKey}----------------------------*/


/*------------------------------{PROG_GetPublicKeyToValidateKeyRoutine}------------------------------*/

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
void PROG_GetPublicKeyToValidateKeyRoutine(Csm_AsymPublicKeyType* pstPublicKey, u8 ubSignKeyType)
{
    u16 uwIdx;
#if ((PROG_CRY_EXPONENT_ENABLED == STD_ON) || (PROG_CSMASR43_USED == STD_ON))
    u16 uwLocIdx;
#endif

    const u8 * paubPublicModulus;
    u32 ulPublicExponent;

    PROG_CustomGetRequiredTokenAsymPublicKey(&paubPublicModulus, &ulPublicExponent, ubSignKeyType);

    pstPublicKey->length = 0U;
#if (PROG_CSMASR43_USED == STD_ON)
#if (PROG_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0U] = (u8)(ulPublicExponent >> 24U); /* Exponent */
    pstPublicKey->data[1U] = (u8)(ulPublicExponent >> 16U); /* Exponent */
    pstPublicKey->data[2U] = (u8)(ulPublicExponent >> 8U); /* Exponent */
    pstPublicKey->data[3U] = (u8)ulPublicExponent; /* Exponent */
    uwLocIdx = 4U;
#endif
    for(uwIdx = 0U; /* Modulus */
        uwIdx < PROG_KEY_LENGTH;
        uwIdx++)
    {
        pstPublicKey->data[uwLocIdx] = paubPublicModulus[uwIdx];
        uwLocIdx++;
    }
#else
#if (PROG_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0] = 1U; /* Exponent size */
    pstPublicKey->data[1] = ulPublicExponent; /* Exponent */

    pstPublicKey->data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(uwIdx = 0U; /* Modulus */
        uwIdx < pstPublicKey->data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U];
        uwIdx++)
    {
        uwLocIdx = uwIdx + ((u16)(PROG_KEY_LENGTH/sizeof(u32))) + 2U;
        pstPublicKey->data[uwLocIdx] = (u32) paubPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((uwIdx*4U)))];
        pstPublicKey->data[uwLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)uwIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[uwLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)uwIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[uwLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)uwIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif
#endif /* (PROG_CSMASR43_USED == STD_ON)*/
}
/*----------------------------{End PROG_GetPublicKeyToValidateKeyRoutine}----------------------------*/
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_91) */

#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))
/*-----------------------{PROG_CsmHashNotification}------------------------------*/
NCS_PRI_FCT void PROG_CsmHashNotification(void)
{
    switch (m_eCryptoState)
    {
        case PROG_HASH_START:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_HASH_START_END;

#if (PROG_CSM_HASH_USED == STD_ON)
            /* Check if hash computation is for Authentication. In positive case all crypto calculation triggering is performed */
            /* directly in not */
            if (PROG_TRUE == PROG_SecurityPendingOperation())
            {
                PROG_ComputeHashUpdate(m_pubCryptoData, m_ulCryptoDataSize);
            }
            else
            {
                /* Nothing to do */
            }
#endif
            break;


        case PROG_HASH_UPDATE:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_HASH_END;

#if (PROG_CSM_HASH_USED == STD_ON)
            /* Check if hash computation is for SecureChecksumComputation */
            if (PROG_TRUE == PROG_SecurityPendingOperation())
            {
                PROG_ComputeHashFinish(m_pubHashValue);
            }
            else
#endif
            {
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
                /* Emit event PROG_EVENT_CRYPTO_NOTIFY */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_NOTIFY);
#endif
            }
            break;

        case PROG_HASH_FINISH:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_IDLE;

#if (PROG_CSM_HASH_USED == STD_ON)
            /* Check if hash computation is for Authentication. In positive case all */
            /* crypto calculation triggering is performed directly in not */
            if (PROG_TRUE == PROG_SecurityPendingOperation())
            {
                /* Notify security feature with hash value */
                PROG_SecurityChecksumNotification();
            }
            else
#endif
            {
                /* Emit event PROG_EVENT_CRYPTO_FINISH */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
            }
            break;
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            m_eCryptoStatus = PROG_E_NOT_OK;
            m_eCryptoState = PROG_IDLE;
            /*push failed event*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
/* CHECK: PARSE */
    }
}
/*----------------------{End PROG_CsmHashNotification}---------------------------*/
#endif /* ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_HASH_USED == STD_ON)|| ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))*/

/*------------------------------{PROG_CsmCheckResult}----------------------------*/
void PROG_CsmCheckResult(Csm_ReturnType eCsmStatus)
{
#if ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_CSM_MAC_USED == STD_ON))
    tProgBoolean eRejectBusy = PROG_FALSE;
#endif
    if (CSM_E_OK == eCsmStatus)
    {
        m_eCryptoStatus = PROG_E_BUSY;
    }
    else if (eCsmStatus == CSM_E_BUSY)
    {
        /* Wait for the treatment to finish only for the execution of the Streaming type of jobs
         * otherwise the busy status is not accepted*/
#if (PROG_CSM_MAC_USED == STD_ON)
        eRejectBusy = PROG_SecurityPendingOperation();
#endif
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON)
        if((PROG_SIGNATURE_CHECK_UPDATE == m_eCryptoState) || (PROG_SIGNATURE_CHECK_FINISH == m_eCryptoState))
        {
            eRejectBusy = PROG_TRUE;
        }
#endif
#if ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_CSM_MAC_USED == STD_ON))
        if(PROG_TRUE == eRejectBusy)
        {
            /* Busy return is not accepted when a single step continuous verification is triggered
             * or during the Secure Checksum computation */
            m_eCryptoStatus = PROG_E_NOT_OK;

#if (PROG_IMPL_VARIANT != PROG_IMPL_20 )
            /* Emit failed event to indicate that the Crypto Finish operation failed
             * except for Signature verification of Impl20 */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
            m_eCryptoState = PROG_IDLE;
        }
#endif /* ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_CSM_MAC_USED == STD_ON)) */
    }
    else
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
#if (PROG_IMPL_VARIANT == PROG_IMPL_20 )
        if(!((PROG_SIGNATURE_CHECK_UPDATE == m_eCryptoState) || (PROG_SIGNATURE_CHECK_FINISH == m_eCryptoState)))
#endif
        {
            /* Emit failed event to indicate that the Crypto Finish operation failed
               except for Signature verification of Impl20 */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
        m_eCryptoState = PROG_IDLE;
    }
}
/*------------------------------{End PROG_CsmCheckResult}------------------------*/

/*-----------------------{Start Crypto ASR 4.3 Support Impl.}--------------------*/
#if (PROG_CSMASR43_USED == STD_ON)

/*------------------------------{PROG_CsmMange}----------------------------------*/
void PROG_CsmManage(void)
{
    switch (m_eCryptoState)
    {
    /* Management of the Signature verification */
#if (PROG_SIGNATURE_CALCULATION == STD_ON)

#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    case PROG_SIGNATURE_CHECK_START_DONE:
        /* Received the ongoing job cancellation notification.
         * Resume the SignatureStart operation */
        (void)PROG_VerifySignatureStart(m_pstAsymPublicKey,  m_pubProgCryptoSignature);
        break;
#endif/*(PROG_CSM_CANCELJOB_ENABLED == STD_ON)*/

#if (PROG_STREAMSTART_ENABLE == STD_ON)
    case PROG_SIGNATURE_CHECK_STREAMSTART_DONE:
        /* Received the Signature StreamStart Notification
         * Indicate that the start operation is complete */
        m_eCryptoState = PROG_SIGNATURE_CHECK_START;
        PROG_CsmSignatureCheckNotification();
        break;
#endif /*(PROG_CSMASR43_STREAMSTART_ENABLED == STD_ON)*/

    case PROG_SIGNATURE_CHECK_START:
        /* Simulate the Signature Start Notification */
        PROG_CsmSignatureCheckNotification();
        break;

    case PROG_SIGNATURE_CHECK_UPDATE_DONE:
        /* Callback received for the Crypto Job Update operation */
        if ((m_ulCryptoTotalBlockDataLength > m_ulCryptoProcessedDataLength) &&
                (m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize != 0U))
        {
            /* Trigger to start to process the pending data */
            PROG_VerifySignatureUpdate(m_pubCryptoData, m_ulCryptoPendingDataLength);
        }
        else
        {
            /*All the data has been processed successfully */
            m_eCryptoState = PROG_SIGNATURE_CHECK_UPDATE;
            PROG_CsmSignatureCheckNotification();
        }
        break;

    case PROG_SIGNATURE_CHECK_FINISH_TXCONF:
        /* Received TxConf, resume the Crypto Finish operation */
        PROG_VerifySignatureFinish(NULL_PTR);
        break;

    case PROG_SIGNATURE_CHECK_FINISH_DONE:
        /* Signature Verification is complete */
        m_eCryptoState = PROG_SIGNATURE_CHECK_FINISH;
        PROG_CsmSignatureCheckNotification();
        break;
#endif /*#if (PROG_SIGNATURE_CALCULATION == STD_ON)*/

        /* Management of the Hash computation*/
#if ((PROG_HASH_CALCULATION == STD_ON)|| (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG)))

#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    case PROG_HASH_START_DONE:
        (void)PROG_ComputeHashStart((u16)m_ubActiveProgCsmTableId, m_pubCryptoData ,m_ulCryptoDataSize, m_pubHashValue);
        break;
#endif/*(PROG_CSM_CANCELJOB_ENABLED == STD_ON)*/

    case PROG_HASH_START:
        /* Simulate the Hash Start Notification */
        PROG_CsmHashNotification();
        break;

    case PROG_HASH_UPDATE_DONE:
        /* Callback received for the Crypto Job Update operation */
        if ((m_ulCryptoTotalBlockDataLength != m_ulCryptoProcessedDataLength) &&
                (m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize != 0U))
        {
            /* Trigger to start to process the pending data */
            PROG_ComputeHashUpdate(m_pubCryptoData, m_ulCryptoPendingDataLength);
        }
        else
        {
            m_eCryptoState = PROG_HASH_UPDATE;
            PROG_CsmHashNotification();
        }
        break;

    case PROG_HASH_FINISH_TXCONF:
        /* Received TxConf, resume the Crypto Finish operation */
        m_eCryptoState = PROG_HASH_END;
        PROG_ComputeHashFinish(m_pubHashValue);
        break;

    case PROG_HASH_FINISH_DONE :
        m_eCryptoState = PROG_HASH_FINISH;
        PROG_CsmHashNotification();
        break;
#endif /* ((PROG_HASH_CALCULATION == STD_ON)|| (PROG_CSM_HASH_USED == STD_ON) || ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))) */

        /* Management of the MAC computation */
#if (PROG_CSM_MAC_USED == STD_ON)

#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    case PROG_MAC_GENERATE_START_DONE:
        (void)PROG_MacGenerateStart((u16)m_ubActiveProgCsmTableId, m_pubCryptoData, m_ulCryptoDataSize, m_pubMacValue);
        break;
#endif/*(PROG_CSM_CANCELJOB_ENABLED == STD_ON)*/

    case PROG_MAC_GENERATE_START:
        /* Simulate the Mac Generate Notification */
        PROG_CsmMacGenerateNotification();
        break;

    case PROG_MAC_GENERATE_UPDATE_DONE:
        /* Callback received for the Crypto Job Update operation */
        if ((m_ulCryptoTotalBlockDataLength != m_ulCryptoProcessedDataLength) &&
                (m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize != 0U))
        {
            /* Trigger to start to process the pending data */
            m_eCryptoState = PROG_MAC_GENERATE_START;
        }
        else
        {
            /*All the data is processed, provide a callback for the update*/
            m_eCryptoState = PROG_MAC_GENERATE_UPDATE;
        }
        PROG_CsmMacGenerateNotification();
        break;

    case PROG_MAC_GENERATE_FINISH_DONE:
        m_eCryptoState = PROG_MAC_GENERATE_FINISH;
        PROG_CsmMacGenerateNotification();
        break;
#endif /* PROG_CSM_MAC_USED == STD_ON  */

        /* Management of the Job cancellation*/
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    case PROG_CSM_JOBCANCEL_DONE:
        /* Callback received after the job cancellation, execute the job on hold */
        m_eCryptoState = m_eCryptoStateOnHold | PROG_E_NOT_BUSY;
        break;

    case PROG_CSM_JOBCANCEL_INPROGRESS:
        /*Awaiting callback after triggering cancellation of the Csm Job, do nothing*/
        break;
#endif /* (PROG_CSM_CANCELJOB_ENABLED == STD_ON) */

    case PROG_IDLE:
    default:
        /* Do nothing*/
        break;
    }
}
/*------------------------------{End PROG_CsmMange}------------------------------*/

/*--------------------------{PROG_CsmSetPreConditions}---------------------------*/
Csm_ReturnType PROG_CsmSetPreConditions(const u8 * ubKeyPtr, u8 ubProgCsmJobTabId)
{
    Csm_ReturnType eCsmStatus;
    const u8 * ubPtr2Key;

    /* Initialize the Crypto Data size, keyptr for the current crypto update operation */
    m_ulCryptoTotalBlockDataLength = 0U;
    ubPtr2Key = ubKeyPtr;
    eCsmStatus = E_OK;

#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    if(m_astProgCsmJobConf[ubProgCsmJobTabId].eAllowJobCancellation == PROG_TRUE)
    {
        eCsmStatus = PROG_CsmCancelActiveJobs();
    }
#endif /* (PROG_CSM_CANCELJOB_ENABLED == STD_ON) */
#if(PROG_CUSTOM_CSMSTARTPREPROCESS_ENABLED == STD_ON)
    if((m_astProgCsmJobConf[ubProgCsmJobTabId].eAllowCustCsmPreProc == PROG_TRUE) && (eCsmStatus == E_OK))
    {
        eCsmStatus = PROG_CustomCsmStrtPreproc(&ubPtr2Key, m_astProgCsmJobConf[ubProgCsmJobTabId].ulCsmJobId);
    }
#endif /* (PROG_CUSTOM_CSMSTARTPREPROCESS_ENABLED == STD_ON) */
#if(PROG_CSM_SETKEY_ENABLED == STD_ON)
    if((m_astProgCsmJobConf[ubProgCsmJobTabId].eAllowKeySet == PROG_TRUE) && \
            (ubPtr2Key != NULL_PTR))
    {
#if ((PROG_CUSTOM_CSMSTARTPREPROCESS_ENABLED == STD_ON) || (PROG_CSM_CANCELJOB_ENABLED == STD_ON))
    if(eCsmStatus == E_OK)
#endif
        {
            eCsmStatus = Csm_KeyElementSet
                         (
                           m_astProgCsmJobConf[ubProgCsmJobTabId].ulCsmKeyID,
                           m_astProgCsmJobConf[ubProgCsmJobTabId].ulCryptoElementId,
                           ubPtr2Key,
                           m_astProgCsmJobConf[ubProgCsmJobTabId].ulCryptoKeyLength
                         );
            if (eCsmStatus == E_OK)
            {
                /*Before the use of the key, set the key state to valid*/
                eCsmStatus = Csm_KeySetValid(m_astProgCsmJobConf[ubProgCsmJobTabId].ulCsmKeyID);
            }
        }
    }
#endif /* (PROG_CSM_SETKEY_ENABLED == STD_ON) */
    return eCsmStatus;
}
/*--------------------------{End PROG_CsmSetPreConditions}-----------------------*/

/*------------------------------{PROG_CsmCancelActiveJobs}-----------------------*/
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
Csm_ReturnType PROG_CsmCancelActiveJobs(void)
{
    u32 ulCsmjobIndex;
    Csm_ReturnType eCsmCancelStatus;
    eCsmCancelStatus = CSM_E_OK;

    /* Generic way to cancel all the configured jobs in Boot */
    for (ulCsmjobIndex = 0U; (ulCsmjobIndex < PROG_CSM_ALLJOBS_COUNT) && (CRYPTO_E_JOB_CANCELED != eCsmCancelStatus); ulCsmjobIndex++)
    {
        eCsmCancelStatus = Csm_CancelJob(ulCsmjobIndex, CRYPTO_OPERATIONMODE_SINGLECALL);
    }

    /* Job cancellation return value E_NOT_OK is not considered as a failure as E_NOT_OK
     * could also mean that there was no job in the queue before to perform cancellation
     * allowed values are CRYPTO_E_JOB_CANCELED and CSM_E_OK */
    eCsmCancelStatus = (eCsmCancelStatus == CRYPTO_E_JOB_CANCELED)? CRYPTO_E_JOB_CANCELED : CSM_E_OK;

    return eCsmCancelStatus;
}
#endif /*(PROG_CSM_CANCELJOB_ENABLED == STD_ON)*/
/*------------------------------{End PROG_CsmCancelActiveJobs}-------------------*/

/*----------------------------{PROG_CsmNotification}-----------------------------*/
FUNC(void, CSM_APPL_CODE)PROG_CsmNotification(P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job, Std_ReturnType result)
{
    DBG_PROG_CSMNOTIFICATION_ENTRY(result);
#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
    /* This is a special scenario in Bootloader where two jobs could be active at the same time,
    so to determine the right callback handling check the Job Id */
    if(m_astProgCsmJobConf[PROG_CSMDECRYPTIONJOBINDEX].ulCsmJobId == job->jobId)
    {
        /*This is a callback for decryption job*/
        m_eEncryptDecryptState = (m_eEncryptDecryptState|PROG_E_NOT_BUSY);
        m_astProgCsmJobConf[PROG_CSMDECRYPTIONJOBINDEX].pfuProgCsmNotification(result);
    }
    else
#else
    OSC_PARAM_UNUSED(job);
#endif
    {
        /* Indicate the current mode execution is complete by setting the not busy bit of the corresponding state */
        m_eCryptoState |= PROG_E_NOT_BUSY;
        if (CRYPTO_E_JOB_CANCELED!= result)
        {
            /* It is assumed that only a single Crypto job operation is active at any given point of time
             * in the Bootloader when decryption is disabled, hence referencing the current active job */
            m_astProgCsmJobConf[m_ubActiveProgCsmTableId].pfuProgCsmNotification(result);

            if ((m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize != 0U) && (result == E_OK) && \
                    (m_ulCryptoProcessedDataLength < m_ulCryptoTotalBlockDataLength))
            {
                /* Update the data length and dataptr that is processed by the Crypto stack*/
                m_ulCryptoProcessedDataLength += m_ulCryptoDataSize;
                m_pubCryptoData = &m_pubCryptoData[m_ulCryptoDataSize];
            }
        }
        else
        {
            /* This is a Callback to indicate the Job cancellation is done */
        }
    }
    DBG_PROG_CSMNOTIFICATION_EXIT(result);
}
/*------------------------------{End PROG_CsmNotification}-----------------------*/

/*----------------------------{PROG_SetCryptoDataSizeDataAdr}--------------------*/
void PROG_SetCryptoDataSizeDataAdr(u8 const * pubData, u32 ulDataSize)
{
    if(m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize != 0U)
    {
        if (m_ulCryptoTotalBlockDataLength <= m_ulCryptoProcessedDataLength)
        {
            /*Store the total size of the new data or the next block of data to be processed */
            m_ulCryptoTotalBlockDataLength = ulDataSize;
            m_pubCryptoData = pubData;
            m_ulCryptoProcessedDataLength = 0U;
        }
        m_ulCryptoPendingDataLength = m_ulCryptoTotalBlockDataLength - m_ulCryptoProcessedDataLength;
        m_ulCryptoDataSize = (m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize < m_ulCryptoPendingDataLength) ? \
                m_astProgCsmJobConf[m_ubActiveProgCsmTableId].ulBSsize: m_ulCryptoPendingDataLength;
    }
    else
    {
        /* Block slicing is disabled, process all the available data */
        m_pubCryptoData = pubData;
        m_ulCryptoDataSize = ulDataSize;
    }
}
/*----------------------------{End PROG_SetCryptoDataSizeDataAdr}----------------*/
#if ((PROG_HASHFIN_SENDFRP == STD_ON) || (PROG_SIGNFIN_SENDFRP == STD_ON))
/*---------------------------{PROG_TxConfNotification}---------------------------*/
void PROG_TxConfNotification(void)
{
    if ((m_eCryptoStateOnHold == PROG_HASH_FINISH) || (m_eCryptoStateOnHold == PROG_SIGNATURE_CHECK_FINISH))
    {
         /* Receieved the notification for awaited TxConf for the NRC78 transmission */
         m_eCryptoState = m_eCryptoStateOnHold|PROG_E_TXCONF_OK;
    }
}
/*--------------------------{End PROG_TxConfNotification}------------------------*/
#endif /* (PROG_HASHFIN_SENDFRP == STD_ON) && (PROG_SIGNFIN_SENDFRP == STD_ON) */
#endif /*(PROG_CSMASR43_USED == STD_ON)*/
/*-----------------------------{End Crypto ASR 4.3 Support}----------------------*/

#endif /* (PROG_CRY_PRESENT == STD_ON) */
