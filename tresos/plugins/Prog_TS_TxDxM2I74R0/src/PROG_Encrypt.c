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
/*%%   _____________________________   %%  \file PROG_Encrypt.c                  */
/*%%  |                             |  %%  \brief PROG cryptography feature      */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3              */
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
#include "Csm.h"
#if (PROG_CSMASR43_USED==STD_OFF)
#include "Cry_LN.h"
#endif/*(PROG_CSMASR43_USED==STD_OFF)*/
#endif /* (PROG_CRY_PRESENT == STD_ON) */

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/* Encryption-Decryption state */
tProgCryState m_eEncryptDecryptState;
#endif /* PROG_CSM_DECRYPTION_ENABLE == STD_ON */
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

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/* Encryption-Decryption status */
NCS_PRI_VAR tProgStatus m_eEncryptDecryptStatus;
/* Decryption hey */
NCS_PRI_VAR Csm_SymKeyType m_stProgDecryptionKey;
/* Public Init Vector */
NCS_PRI_VAR const u8 * m_pubInitVector;
/* Lenght of Init Vector */
NCS_PRI_VAR u32 m_ulInitVectorLength;
#if (PROG_CSMASR43_USED ==STD_ON)
/* Variables to store the cipher ptr for the later use*/
NCS_PRI_VAR const u8 * m_pubCipherText;
NCS_PRI_VAR u32 m_ulCipherTextLength;
NCS_PRI_VAR u8 * m_pubPlainText;
NCS_PRI_VAR u32 m_ulPlainTextLength;
#endif /* (PROG_CSMASR43_USED ==STD_ON) */
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */


/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/** \brief Treat the Csm Decryption notification **/
#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
NCS_PRI_FCT void PROG_CsmDecryptionNotification(void);
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*---------------------------{PROG_GetDecryptionStatus}------------------------------*/
tProgStatus PROG_GetDecryptionStatus(void)
{
    tProgStatus eStatus;

    DBG_PROG_GETDECRYPTIONSTATUS_ENTRY( );

    eStatus = m_eEncryptDecryptStatus;

    DBG_PROG_GETDECRYPTIONSTATUS_EXIT(eStatus);

    return eStatus;
}
/*--------------------------{End PROG_GetDecryptionStatus}---------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*---------------------------{PROG_GetDecryptionState}------------------------------*/
tProgCryState PROG_GetDecryptionState(void)
{
    tProgCryState eState;

    DBG_PROG_GETDECRYPTIONSTATE_ENTRY( );

    eState = m_eEncryptDecryptState;

    DBG_PROG_GETDECRYPTIONSTATE_EXIT(eState);

    return eState;
}
/*--------------------------{End PROG_GetDecryptionState}---------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

/*---------------------------{PROG_CsmEncryptDecryptNotification}----------------------------*/
#if ((PROG_CSM_DECRYPTION_ENABLE == STD_ON) && (PROG_CSMASR43_USED == STD_OFF))
Std_ReturnType PROG_CsmEncryptDecryptNotification(Csm_ReturnType eResult)
{
    Std_ReturnType RetVal = 0U;

    DBG_PROG_CSMENCRYPTDECRYPTNOTIFICATION_ENTRY(eResult);

    if (CSM_E_OK == eResult)
    {
        switch (m_eEncryptDecryptState)
        {
            case PROG_DECRYPTION_START:
            case PROG_DECRYPTION_UPDATE:
            case PROG_DECRYPTION_FINISH:
                PROG_CsmDecryptionNotification();
                break;
            /* Shall not happened go back in stable state happened */
            default:
                m_eEncryptDecryptStatus = PROG_E_NOT_OK;
                m_eEncryptDecryptState  = PROG_IDLE;
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                break;
        }
    }
    else
    {

        m_eEncryptDecryptStatus = PROG_E_NOT_OK;
        m_eEncryptDecryptState = PROG_IDLE;
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }

    DBG_PROG_CSMENCRYPTDECRYPTNOTIFICATION_EXIT(RetVal);
    return RetVal;
}
#endif /* ((PROG_CSM_DECRYPTION_ENABLE == STD_ON) && (PROG_CSMASR43_USED == STD_OFF)) */
/*--------------------------{End PROG_CsmEncryptDecryptNotification}-------------------------*/

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*------------------------------{PROG_GetSymDecryptionKey}------------------------------*/
void PROG_GetSymDecryptionKey(Csm_SymKeyType* pstDecryptionKey)
{
    u32 ulIdx;
    const u8 * paubKeyData;
    u32 ulDecryptionKeyLength;

    DBG_PROG_GETSYMDECRYPTIONKEY_ENTRY(pstDecryptionKey);
    PROG_CustomGetSymDecryptionKey(&paubKeyData, &ulDecryptionKeyLength);

    pstDecryptionKey->length = ulDecryptionKeyLength;
#if (PROG_CSMASR43_USED ==STD_ON)
    for(ulIdx = 0U; /* key */
        ulIdx < ulDecryptionKeyLength;
        ulIdx++)
    {
        pstDecryptionKey->data[ulIdx] = paubKeyData[ulIdx];
    }
#else
    for (ulIdx = 0U; ulIdx < (ulDecryptionKeyLength/sizeof(u32)); ulIdx++)
    {
        pstDecryptionKey->data[ulIdx]  = (u32)paubKeyData[(u16)(ulIdx*4U)];
        pstDecryptionKey->data[ulIdx] |= (u32)((u32)((u32)paubKeyData[(1U + ((u16)ulIdx*4U))] << 8U)  & 0x0000FF00U);
        pstDecryptionKey->data[ulIdx] |= (u32)((u32)((u32)paubKeyData[(2U + ((u16)ulIdx*4U))] << 16U) & 0x00FF0000U);
        pstDecryptionKey->data[ulIdx] |= (u32)((u32)((u32)paubKeyData[(3U + ((u16)ulIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif
    DBG_PROG_GETSYMDECRYPTIONKEY_EXIT( );
}
/*----------------------{End PROG_GetSymDecryptionKey}---------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*-----------------------{PROG_DecryptionStart}--------------------*/
void PROG_DecryptionStart(void)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_DECRYPTIONSTART_ENTRY();
    m_eEncryptDecryptStatus = PROG_E_BUSY;

    /* Get initialization vector and decryption key */
    PROG_CustomDecryptGetInitVector(&m_pubInitVector, &m_ulInitVectorLength);
    PROG_GetSymDecryptionKey(&m_stProgDecryptionKey);

#if (PROG_CSMASR43_USED ==STD_ON)
#ifdef PROG_CRYPTO_DECRYPTION_IV_ELEID
    /* Allow to set the IV for the Decryption job*/
    (void)Csm_KeyElementSet
            (
                    m_astProgCsmJobConf[PROG_CSMDECRYPTIONJOBINDEX].ulCsmKeyID,
                    PROG_CRYPTO_DECRYPTION_IV_ELEID,
                    m_pubInitVector,
                    m_ulInitVectorLength
            );

#endif
    eCsmStatus = PROG_CsmSetPreConditions((u8*)&m_stProgDecryptionKey, PROG_CSMDECRYPTIONJOBINDEX);
    if (eCsmStatus == CSM_E_OK)
    {
        eCsmStatus = Csm_Decrypt(m_astProgCsmJobConf[PROG_CSMDECRYPTIONJOBINDEX].ulCsmJobId, CRYPTO_OPERATIONMODE_START, \
                m_pubCipherText, m_ulCipherTextLength, m_pubPlainText, (u32*)&m_ulPlainTextLength);
    }
#else
    eCsmStatus = Csm_SymDecryptStart(PROG_CSM_DECRYPTION_ID, &m_stProgDecryptionKey,
            m_pubInitVector, m_ulInitVectorLength);
#endif /* (PROG_CSMASR43_USED ==STD_ON)*/
    m_eEncryptDecryptState  = PROG_DECRYPTION_START;
    if(eCsmStatus == CSM_E_OK)
    {
#if (PROG_CSMASR43_USED ==STD_ON)
        /* For Crypto 4.3 no callback shall be provided for the Start operation,
         * therefore simulate the callback */
        PROG_CsmDecryptionNotification();
#endif /* (PROG_CSMASR43_USED == STD_ON) */
    }
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    else if(eCsmStatus == CRYPTO_E_JOB_CANCELED)
    {
        /* Wait for the Async Job cancellation process to finish */
    }
#endif /* (PROG_CSMASR43_USED == STD_ON) */
    else
    {
        m_eEncryptDecryptStatus = PROG_E_NOT_OK;
    }
    DBG_PROG_DECRYPTIONSTART_EXIT();
}
/*----------------------------{End PROG_DecryptionStart}----------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*-----------------------{PROG_DecryptionUpdate}--------------------*/
void PROG_DecryptionUpdate(const u8 * pubCipherText , u32 ulCipherTextLength, u8 * pubPlainText , u32 * pulPlainTextLength)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_DECRYPTIONUPDATE_ENTRY(pubCipherText, ulCipherTextLength, pubPlainText, pulPlainTextLength);
    if (m_eEncryptDecryptStatus != PROG_E_NOT_OK)
    {
        m_eEncryptDecryptState  = PROG_DECRYPTION_UPDATE;
#if (PROG_CSMASR43_USED ==STD_ON)
        m_pubCipherText = pubCipherText;
        m_ulCipherTextLength = ulCipherTextLength;
        m_pubPlainText = pubPlainText;
        m_ulPlainTextLength = (u32)*pulPlainTextLength;
        eCsmStatus = Csm_Decrypt(m_astProgCsmJobConf[PROG_CSMDECRYPTIONJOBINDEX].ulCsmJobId, CRYPTO_OPERATIONMODE_UPDATE, \
                m_pubCipherText, m_ulCipherTextLength, m_pubPlainText, pulPlainTextLength);
#else
        eCsmStatus = Csm_SymDecryptUpdate(PROG_CSM_DECRYPTION_ID, pubCipherText, ulCipherTextLength,
                                          pubPlainText, pulPlainTextLength);
#endif
        PROG_CsmDecryptionCheckResult(eCsmStatus);
    }

    DBG_PROG_DECRYPTIONUPDATE_EXIT( );
}
/*----------------------------{End PROG_DecryptionUpdate}----------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*-----------------------{PROG_DecryptionFinish}--------------------*/
void PROG_DecryptionFinish(u8 * pubplainText , u32 * pulPlainTextLength)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_DECRYPTIONFINISH_ENTRY(pubplainText, pulPlainTextLength);

    if(m_eEncryptDecryptStatus != PROG_E_NOT_OK)
    {
        m_eEncryptDecryptState = PROG_DECRYPTION_FINISH;
#if (PROG_CSMASR43_USED ==STD_ON)
        eCsmStatus = Csm_Decrypt(m_astProgCsmJobConf[PROG_CSMDECRYPTIONJOBINDEX].ulCsmJobId, CRYPTO_OPERATIONMODE_FINISH, \
                m_pubCipherText, m_ulCipherTextLength, pubplainText, pulPlainTextLength);
#else
        eCsmStatus = Csm_SymDecryptFinish(PROG_CSM_DECRYPTION_ID, pubplainText, pulPlainTextLength);
#endif
        PROG_CsmDecryptionCheckResult(eCsmStatus);
    }

    DBG_PROG_DECRYPTIONFINISH_EXIT( );
}
/*----------------------------{End PROG_DecryptionFinish}----------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*-----------------------{PROG_CsmDecryptionNotification}--------------------*/
NCS_PRI_FCT void PROG_CsmDecryptionNotification(void)
{
    DBG_PROG_CSMDECRYPTIONNOTIFICATION_ENTRY();

    switch (m_eEncryptDecryptState)
    {
        case PROG_DECRYPTION_START:
          m_eEncryptDecryptState  = PROG_DECRYPTION_START_END;
          m_eEncryptDecryptStatus = PROG_E_OK;
          break;

        case PROG_DECRYPTION_UPDATE:
          m_eEncryptDecryptState  = PROG_DECRYPTION_UPDATE_END;
          m_eEncryptDecryptStatus = PROG_E_OK;
          break;

        case PROG_DECRYPTION_FINISH:
          m_eEncryptDecryptState  = PROG_DECRYPTION_FINISH_END;
          m_eEncryptDecryptStatus = PROG_E_OK;
          break;
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            /* Do nothing */
          break;
/* CHECK: PARSE */
    }

    DBG_PROG_CSMDECRYPTIONNOTIFICATION_EXIT();
}
/*----------------------------{End PROG_CsmDecryptionNotification}----------------------------*/
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*------------------------{PROG_ComputeTotalEncryptedDataWithAesCbcPkcs7}--------------------------*/
void PROG_ComputeTotalEncryptedDataWithAesCbcPkcs7(u32 ulTotalPlainDataSize, u32 *pulTotalCipheredDataSize)
{
    DBG_PROG_COMPUTETOTALENCRYPTEDDATAWITHAESCBCPKCS7_ENTRY(ulTotalPlainDataSize, pulTotalCipheredDataSize);

    *pulTotalCipheredDataSize = (u32)PROG_CIPHERED_TEXT_SIZE(ulTotalPlainDataSize);

    DBG_PROG_COMPUTETOTALENCRYPTEDDATAWITHAESCBCPKCS7_EXIT();
}
/*-------------------------{end PROG_ComputeTotalEncryptedDataWithAesCbcPkcs7}---------------------------*/
#endif /*  (PROG_CSM_DECRYPTION_ENABLE == STD_ON)*/

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/*-----------------------------{PROG_CsmDecryptionCheckResult}-------------------------------------------*/
void PROG_CsmDecryptionCheckResult(Csm_ReturnType eCsmStatus)
{
    if (eCsmStatus == CSM_E_OK)
    {
        m_eEncryptDecryptStatus = PROG_E_BUSY;
#if (PROG_CSMASR43_USED ==STD_ON)
        /* Check if the callback for decryption received from the Crypto 4.3 stack*/
        if(PROG_E_NOT_BUSY == (m_eEncryptDecryptState & PROG_E_NOT_BUSY))
        {
            m_eEncryptDecryptState = (m_eEncryptDecryptState & (~PROG_E_NOT_BUSY));
            PROG_CsmDecryptionNotification();
        }
#endif /* (PROG_CSMASR43_USED ==STD_ON) */
    }
#if(PROG_CSM_CANCELJOB_ENABLED == STD_ON)
    else if (eCsmStatus == CRYPTO_E_JOB_CANCELED)
    {
        if(m_eEncryptDecryptState == PROG_DECRYPTION_START_DONE)
        {
            /* Callback received for the Async. Job cancellation after main func call, job can be restarted */
            PROG_DecryptionStart();
        }
    }
#endif
    else if (eCsmStatus == CSM_E_BUSY)
    {
        /* Nothing to do */
    }
    else
    {
        m_eEncryptDecryptStatus = PROG_E_NOT_OK;
        m_eEncryptDecryptState = PROG_IDLE;
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
}
/*-------------------------{end PROG_CsmDecryptionCheckResult}-------------------------------------------*/
#endif /*  (PROG_CSM_DECRYPTION_ENABLE == STD_ON)*/
