/*===============================================================================*/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_AuthMethod0001.c             */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.25.0 BL3 */
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
/* NOCOV List
 *
 * NOCOV-NCS_UNITARY_TEST:
 *   code is deactivated for test.
 *
 * Reason:
 * Test are performed under WINDOWS environment.
 *
 * MISRAC2012-1) Deviated Rule: 8.4 (required)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined.
 *
 * Reason:
 * Static keyword is automatically removed and these variables are not used in test environment
 *
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "SA_Priv.h"
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
/*                                                                               */
/*===============================================================================*/
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
tSA_MACAlgo m_stMACpar;
tSA_AESCTRAlgo m_stAESCTRpar;
u8 * m_pubSAReqResptr;
tSaStatus m_ubSaAllKeysStatus;
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
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#define SA_AM0001_START_SEC_VAR_INIT_16
#include <MemMap.h>
u8 m_ubAesBlockIndex;
u8 m_ubAESCTR_Blockcount;
u8 m_aubMacValue[SA_MACSIZE];
u8 m_aubAesCtrClientRndNum[SA_CLIENT_RNDNUM_SIZE];
u8 m_aubAesCtrServerRndNum[SA_SERVER_RNDNUM_SIZE];
tSA_AuthenticationState m_ulAuthentication0001State;
u8 m_aubIV_Aligned16[SA_AESCTR_IVLEN];
u8 m_aubSaAm0001BufAligned16[SA_AM0001_MAXBUF];
#define SA_AM0001_STOP_SEC_VAR_INIT_16
#include <MemMap.h>
tSaStatus m_ubSaStatus;
Csm_ReturnType m_ubCsmStatus;
tSA_ConcatenatePar m_aubConcatenatedataptr[2U];

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
NCS_PRI_FCT void SA_VrfyMsg_AuthCode(void);
NCS_PRI_FCT void SA_AESDecrypt_ReqData(void);
NCS_PRI_FCT void SA_SeedGen_ServerPoo(void);
NCS_PRI_FCT void SA_SeedGen_EncryptServerPoo(void);
NCS_PRI_FCT void SA_SeedGen_MsgAuthCode(void);
NCS_PRI_FCT void SA_KeyUnlock(void);
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{SA_AuthMethod0001}------------------------------------*/
void SA_AuthMethod0001(void)
{
    m_ubSaStatus = SA_E_OK;
    m_ubCsmStatus = CSM_E_OK;

    switch(m_ulAuthentication0001State)
    {
        case SA_VRFYMSG_AUTHCODE_SA1:
        case SA_VRFYMSG_AUTHCODE_SA2:
            if((m_ulAuthentication0001State == SA_VRFYMSG_AUTHCODE_SA1) &&
                    (m_pubSAReqResptr[2U] == (u8)(SA1_MSGID & 0xFF00U)) && ((SA1_MSGID & 0xFFU) == m_pubSAReqResptr[3U]) &&
                    (m_pubSAReqResptr[4U] == (u8)(SA_AUTHENTICATION_0001 & 0xFF00U)) && ((SA_AUTHENTICATION_0001 & 0xFFU) == m_pubSAReqResptr[5U]))
            {
                m_stMACpar.DataLen = SA1_MSGSIZE_WITHOUT_MACVALUE;
            }
            else if((m_ulAuthentication0001State == SA_VRFYMSG_AUTHCODE_SA2) &&
                    (m_pubSAReqResptr[2U] == (u8)(SA2_MSGID & 0xFF00U)) &&((SA2_MSGID & 0xFFU) == m_pubSAReqResptr[3U]))
            {
                m_stMACpar.DataLen = SA2_MSGSIZE_WITHOUT_MACVALUE;
            }
            else
            {
                /*Preliminary Checks Not OK*/
                m_ubSaStatus = SA_E_NOT_OK;
                break;
            }
            SA_VrfyMsg_AuthCode();
            break;
        case SA_DECRYPT_REQDATA_SA1 :
        case SA_DECRYPT_REQDATA_SA2 :
            SA_AESDecrypt_ReqData();
            break;
        case SA_SEND_SA1RES:

            m_aubConcatenatedataptr[0U].DataPtr = &m_stMACpar.MACPtr[0U];
            m_aubConcatenatedataptr[0U].DataLength = SA_MACSIZE;

            /*Seed Response (&ubResponsedata[0], &aubMsgAuthMAC[0], &ubResponsedata[0]) */
            SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0], 1U, &m_pubSAReqResptr[SA1_RESSIZE_WITHOUT_MACVALUE]);

            /*SA1 Processing complete send response*/
            m_eSaStatus = SA_E_OK;
#if (SA_CSMASR43_USED == STD_ON)
            SA_AM0001_SetState(SA_AM0001_STATE_BUSY|(m_ulAuthentication0001State << 1));
#endif
            break;
        case SA_SEEDGEN_RNDIV:

            /*Initialize the state for SA_Random Generation */
            m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
            m_ubSaStatus = SA_GenerateRandomNumber (&m_pubSAReqResptr[SA1_AESCTR_IVOFFSET_RES]);
            break;
        case SA_SEEDGEN_RNDSERVER:

            /*Initialize the state for SA_Random Generation */
            m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
            m_ubSaStatus = SA_GenerateRandomNumber (&m_aubAesCtrServerRndNum[0U]);
            break;
        case SA_SEEDGEN_SERVERPOO:
            SA_SeedGen_ServerPoo();
            break;
        case SA_SEEDGEN_SERVERPOO_ENCRYPT:
#if (SA_CSMASR43_USED == STD_ON)
        case SA_SEEDGEN_SERVERPOO_ENCRYBLK2:
#endif
            SA_SeedGen_EncryptServerPoo();
            break;
        case SA_SEEDGEN_MSGAUTHCODE:
            SA_SeedGen_MsgAuthCode();
            break;
        case SA_KEYUNLOCK:
            SA_KeyUnlock();
            break;
        case SA_KEYUNLOCK_SUCCESS:
            /*Positive response shall be sent for Send Key Request*/
            m_eSaStatus = SA_E_OK;
            break;
        default:
            if ((m_ulAuthentication0001State & SA_AM0001_STATE_BUSY) == SA_AM0001_STATE_BUSY)
            {
                /*Wait*/
                m_ubSaStatus = SA_E_BUSY;
            }
            else
            {
                /*SA Authentication failed- due to Undefined state access*/
                m_ubSaStatus = SA_E_NOT_OK;
            }
            break;
    }
    if((CSM_E_OK == m_ubCsmStatus) && (m_ubSaStatus != SA_E_NOT_OK) && \
        ((m_ulAuthentication0001State & SA_AM0001_STATE_BUSY) != SA_AM0001_STATE_BUSY) && \
        ((m_ulAuthentication0001State & SA_AM0001_STATE_FAILED) != SA_AM0001_STATE_FAILED)
    )
    {
#if (SA_CSMASR43_USED == STD_ON)
        /* Crypto ASR 4.3 uses Synchronous Single call operation that shall complete in
         * the first call without the need to wait for the callback, hence go to the
         * next state for execution without setting the busy flag */
        SA_AM0001_SetState(m_ulAuthentication0001State << 1);
#else
        SA_AM0001_SetState(SA_AM0001_STATE_BUSY|(m_ulAuthentication0001State << 1));
#endif
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
        /*Set the Key Programming status if not set*/
        SA_SetSecuredKeyStatus(m_ubCsmStatus);
#endif
    }
    else if((((CSM_E_BUSY != m_ubCsmStatus) && (CSM_E_OK != m_ubCsmStatus)) || (SA_E_NOT_OK == m_ubSaStatus)) && \
            ((m_ulAuthentication0001State & SA_AM0001_STATE_FAILED) != SA_AM0001_STATE_FAILED))
    {
        /*Update State before Indicating failure*/
        SA_AM0001_SetState(m_ulAuthentication0001State << 1);
        SA_AM0001_SetStatus(SA_E_NOT_OK);
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
        SA_SetSecuredKeyStatus(m_ubCsmStatus);
#endif
    }
    else
    {
        /*Busy, do nothing*/
    }
}
/*----------------------------------{end SA_AuthMethod0001}------------------------------------*/

/*----------------------------------{SA_AM0001_SetStatus}--------------------------------------*/
void SA_AM0001_SetStatus(tSaStatus eSaStatus)
{
    /*Clear Busy status of the current operation*/
    SA_AM0001_SetState((~((u32)SA_AM0001_STATE_BUSY)) & (m_ulAuthentication0001State));

    if (eSaStatus == SA_E_OK)
    {
        /*Do nothing, next state is already set and busy status is reset*/
    }
    else
    {
        /*Set Failure status of the current operation*/
        SA_AM0001_SetState(SA_AM0001_STATE_FAILED | m_ulAuthentication0001State);

        /* Prevent execution of further SA Crypto states during a failure */
        m_eSaCsmState = SA_IDLE;

        switch(m_ulAuthentication0001State)
        {
            case SA_AWAITSA2_TIMEEXPIRED:
                /*To Send NRC22*/
                /* In case the  Send key was not send, and it's from request seed, do not call this */
                if(m_ulSA2waitTime != 0)
                {
                m_eSaStatus = SA_Antiscanning(SA_FALSE);
                m_eSaCsmState = SA_IDLE;
                }
                else
                {
                    m_eSaStatus=SA_SA2AWATINGTIME_EXPIRED;
                }
                /*set status to NOT ok */
                break;
            case SA_KEYUNLOCK_FAILED:
            case SA_VRFYMSG_AUTHCODE_SA2_FAILED:
            case SA_DECRYPT_REQDATA_SA2_FAILED:
                /*To Send NRC35 or NRC36*/
#if (SA_ANTISCANNING_ENABLED == STD_ON)
                m_eSaStatus = SA_Antiscanning(SA_FALSE);
#else
                m_eSaStatus = SA_E_NOK_INVALID_KEY;
#endif
                break;
            default:
                /*For any undefined failure action during SA processing- To Send NRC31 */
                m_eSaStatus = SA_AM0001_PROCESSING_FAILED;
                break;
        }
    }
#if (SA_ANTISCANNING_ENABLED == STD_ON)
    if (m_ulAuthentication0001State == SA_KEYUNLOCK_SUCCESS)
    {
        m_eSaStatus = SA_Antiscanning( SA_TRUE );
    }
    else
    {
        /*Do nothing let the m_eSaStatus retain the updated status*/
    }
#endif
}
/*----------------------------------{end SA_AM0001_SetStatus}----------------------------------*/

/*----------------------------------{SA_AM0001_SetState}---------------------------------------*/
void SA_AM0001_SetState(tSA_AuthenticationState ulAuthentication0001State)
{
    m_ulAuthentication0001State = ulAuthentication0001State;
}
/*----------------------------------{end SA_AM0001_SetState}-----------------------------------*/

/*----------------------------------{SA_AM0001_GetState}---------------------------------------*/
tSA_AuthenticationState SA_AM0001_GetState(void)
{
    return m_ulAuthentication0001State;
}
/*----------------------------------{end SA_AM0001_GetState}-----------------------------------*/

/*----------------------------------{SA_ConcatenateAndStoreData}-------------------------------*/
/*Generic API to Concatenate and store data from multiple Input buffers*/
void SA_ConcatenateAndStoreData(tSA_ConcatenatePar *aubInputData, u32 ulInputbufCount, u8 * aubStore)
{
    u32 ulIpBufIndex;
    u8 ubIpdataPtrIndex;
    u8 ubOpBufIndex;

    ubOpBufIndex = 0U;

    for (ulIpBufIndex = 0U; (ulIpBufIndex < ulInputbufCount) && (aubInputData != NULL_PTR); ulIpBufIndex++ )
    {
        if((aubStore != NULL_PTR) && (aubInputData[ulIpBufIndex].DataPtr != NULL_PTR))
        {
            for ( ubIpdataPtrIndex = 0U;(ubIpdataPtrIndex< aubInputData[ulIpBufIndex].DataLength); ubIpdataPtrIndex++)
            {
                aubStore[ubOpBufIndex] = aubInputData[ulIpBufIndex].DataPtr[ubIpdataPtrIndex];
                ubOpBufIndex++;
            }
        }
    }
}
/*----------------------------------{end SA_ConcatenateAndStoreData}---------------------------*/
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
/*----------------------------------{SA_GetSecuredKeysStatus}----------------------------------*/
tSaStatus SA_GetSecuredKeysStatus(void)
{
    return m_ubSaAllKeysStatus;
}
/*----------------------------------{end SA_GetSecuredKeysStatus}-------------------------------*/

/*----------------------------------{SA_SetSecuredKeyStatus}------------------------------------*/
void SA_SetSecuredKeyStatus(Csm_ReturnType eCsmResult)
{
    tSA_AuthenticationState ulAuthentication0001State;

    if (m_ubSaAllKeysStatus == SA_E_STATUS_UNKNOWN)
    {
        ulAuthentication0001State = SA_AM0001_GetState();

        if (((eCsmResult == CSM_E_OK) || (CRYPTO_E_KEY_NOT_VALID == eCsmResult)) \
                && (ulAuthentication0001State == SA_SEEDGEN_MSGAUTHCODE_SUCCESS))
        {
            /*Keys are programmed*/
            m_ubSaAllKeysStatus = SA_E_OK;
        }
        else if (CRYPTO_E_KEY_NOT_VALID == eCsmResult)
        {
            /*Invalid Key observed during test execution, therfore key exist, move to next key test*/
            SA_AM0001_SetState(ulAuthentication0001State & ~(SA_AM0001_STATE_FAILED));
        }
        else if (eCsmResult != CSM_E_OK)
        {
            /*Error during the Test execution- probable reason could be Key not found or test execution error*/
            m_ubSaAllKeysStatus = SA_E_NOT_OK;
        }
        else
        {
            /*Test Execution in progress*/
        }
    }
}
#endif /*SA_SECUREDKEYS_STATUSREAD == STD_ON*/
/*----------------------------------{end SA_SetSecuredKeyStatus}---------------------------------*/
/*----------------------------------{SA_VrfyMsg_AuthCode}----------------------------------------*/
NCS_PRI_FCT void SA_VrfyMsg_AuthCode(void)
{
#if ((SA_CSMASR43_USED == STD_ON)&&(SA_CSM_SETKEY_ENABLED == STD_ON))
    Csm_ReturnType eCsmStatus;
#endif
    /* Copy the received data without MAC to 16 byte aligned input data buffer */
    m_aubConcatenatedataptr[0U].DataPtr = m_pubSAReqResptr;
    m_aubConcatenatedataptr[0U].DataLength = m_stMACpar.DataLen;
    SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 1U, &m_aubSaAm0001BufAligned16[0U]);

    /* Copy the received MAC to 16 byte aligned MAC data buffer */
    m_aubConcatenatedataptr[0U].DataPtr = &m_pubSAReqResptr[m_stMACpar.DataLen];
    m_aubConcatenatedataptr[0U].DataLength = SA_MACSIZE;
    SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 1U, &m_aubMacValue[0U]);

    /*Set Crypto Input and Output Parameters*/
    m_stMACpar.CsmCfdID = SA_CSM_MAC_MSGCODEVERIFY_ID;
    m_stMACpar.DataPtr = &m_aubSaAm0001BufAligned16[0U];
    m_stMACpar.MACLen = SA_MACSIZE;
    m_stMACpar.MACLenPtr = (u32*)&m_stMACpar.MACLen;
    m_stMACpar.MACPtr = &m_aubMacValue[0U];

#if (SA_CSMASR43_USED == STD_ON)
#if(SA_CSM_CANCELJOB_ENABLED == STD_ON)
    if(m_astSACsmJobConf[SA_CSMMACVERIFMSGAUTHJOBINDEX].ubAllowJobCancellation == PROG_TRUE)
    {
        (void)SA_CsmCancelActiveJobs();
    }
#endif
#if(SA_CSM_SETKEY_ENABLED == STD_ON)

#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif
    eCsmStatus = SA_CsmSetKeys (m_stMACpar.CsmKeyPtr, SA_CSMMACVERIFMSGAUTHJOBINDEX);
    if (eCsmStatus != CSM_E_OK)
    {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }

    if (eCsmStatus == CSM_E_OK)
#endif
    {
        m_ubCsmStatus = Csm_MacVerify(SA_CSM_MAC_MSGCODEVERIFY_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stMACpar.DataPtr, m_stMACpar.DataLen, m_stMACpar.MACPtr, m_stMACpar.MACLen*8U, &m_ubMacVerificationResult);

        m_eSaCsmState = SA_IDLE;
       if (m_ubMacVerificationResult == CSM_E_VER_OK)
       {
       /*Initialize the status to Busy until the SA processing completion*/
           m_eSaStatus = SA_E_BUSY;
           SA_AM0001_SetStatus(SA_E_OK);
       }
       else
       {
           m_eSaStatus = SA_E_NOT_OK;
           SA_AM0001_SetStatus(SA_E_NOT_OK);
       }
    }
#else

#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif

    /*Initialize the state for SA_MAC verification*/
    m_eSaCsmState = SA_MAC_VERIFY_START;

    m_ubCsmStatus = Csm_MacVerifyStart
                    (
                    m_stMACpar.CsmCfdID,
                    m_stMACpar.CsmKeyPtr
                    );
    /*Initialize the status to Busy until the SA processing completion*/
    m_eSaStatus = SA_E_BUSY;
#endif
}
/*----------------------------------{end SA_VrfyMsg_AuthCode}------------------------------------*/
/*----------------------------------{SA_AESDecrypt_ReqData}--------------------------------------*/
NCS_PRI_FCT void SA_AESDecrypt_ReqData(void)
{
#if (SA_ECB2CTR_ENABLED == STD_ON)
      u32  ulIpDataIdx;
#endif
#if ((SA_CSMASR43_USED == STD_ON) && (SA_CSM_SETKEY_ENABLED == STD_ON))
    Csm_ReturnType eCsmStatus;
#endif
    /*Fill the Csm_SymDecryptStart parameters */
    if (m_ulAuthentication0001State == SA_DECRYPT_REQDATA_SA1)
    {
        m_stAESCTRpar.CTLen = SA_CLIENT_RNDNUM_SIZE;
        m_stAESCTRpar.PTLen = SA_CLIENT_RNDNUM_SIZE;

        /*Copy the IV to 16 byte aligned buffer*/
        m_aubConcatenatedataptr[0U].DataPtr = &m_pubSAReqResptr[SA1_AESCTR_IVOFFSET];
        m_aubConcatenatedataptr[0U].DataLength = SA_AESCTR_IVLEN;
        SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 1U, &m_aubIV_Aligned16[0U]);

        m_stAESCTRpar.IVptr = &m_aubIV_Aligned16[0U];
        m_stAESCTRpar.PTptr = &m_aubAesCtrClientRndNum[0U];
        m_stAESCTRpar.CTptr = &m_pubSAReqResptr[SA1_AESCTR_CTOFFSET_REQ];
    }
    else
    {
        m_stAESCTRpar.CTLen = SA_CLIENT_POO_SIZE;
        m_stAESCTRpar.PTLen = SA2_AESCTR_PTLEN;

        /*Copy the IV to 16 byte aligned buffer*/
        m_aubConcatenatedataptr[0U].DataPtr = &m_pubSAReqResptr[SA2_AESCTR_IVOFFSET];
        m_aubConcatenatedataptr[0U].DataLength = SA_AESCTR_IVLEN;
        SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 1U, &m_aubIV_Aligned16[0U]);

        m_stAESCTRpar.IVptr = &m_aubIV_Aligned16[0U];
        m_stAESCTRpar.PTptr = &m_aubMacValue[0U];
        m_stAESCTRpar.CTptr = &m_pubSAReqResptr[SA2_AESCTR_CTOFFSET];
    }
    m_stAESCTRpar.IVLen = SA_AESCTR_IVLEN;
    m_stAESCTRpar.CTLenptr =  (u32*)&m_stAESCTRpar.CTLen;
    m_stAESCTRpar.PTLenptr = (u32*)&m_stAESCTRpar.PTLen;
    m_stAESCTRpar.CsmCfdID = SA_CSM_AESCTR_DECRYPT_ID;

#if (SA_CSMASR43_USED == STD_ON)

#if(SA_CSM_SETKEY_ENABLED == STD_ON)

#if(SA_CUSTOMGETAESCTRKEY == STD_ON)
    SA_CustomGetAESCTRKey(&m_stAESCTRpar.CsmKeyPtr, m_stAESCTRpar.CsmCfdID);
#endif
    eCsmStatus = SA_CsmSetKeys (m_stAESCTRpar.CsmKeyPtr, SA_CSMAESDECRYPTJOBINDEX);
    if (eCsmStatus != CSM_E_OK)
    {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
    else
#endif
    {
#if (SA_ECB2CTR_ENABLED == STD_ON)
        m_ubCsmStatus = Csm_Encrypt(SA_CSM_AESCTR_DECRYPT_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stAESCTRpar.IVptr, m_stAESCTRpar.IVLen, m_stAESCTRpar.PTptr, m_stAESCTRpar.PTLenptr);
        for (ulIpDataIdx = 0U; ulIpDataIdx < m_stAESCTRpar.PTLen; ulIpDataIdx++)
        {
            m_stAESCTRpar.PTptr[ulIpDataIdx] = m_stAESCTRpar.PTptr[ulIpDataIdx] ^ m_stAESCTRpar.CTptr[ulIpDataIdx];
        }
#else
        m_ubCsmStatus = Csm_Decrypt(SA_CSM_AESCTR_DECRYPT_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stAESCTRpar.CTptr, m_stAESCTRpar.CTLen, m_stAESCTRpar.PTptr, m_stAESCTRpar.PTLenptr);
#endif
       if (m_ubCsmStatus == CSM_E_OK)
       {
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_OK);
       }
       else
       {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
       }
    }
#else
#if(SA_CUSTOMGETAESCTRKEY == STD_ON)
    SA_CustomGetAESCTRKey(&m_stAESCTRpar.CsmKeyPtr, m_stAESCTRpar.CsmCfdID);
#endif

    /*Initialize the state for SA_AES Decryption */
    m_eSaCsmState = SA_AES_DECRYPT_START;

    m_ubCsmStatus = Csm_SymDecryptStart
            (
                    m_stAESCTRpar.CsmCfdID,
                    m_stAESCTRpar.CsmKeyPtr,
                    m_stAESCTRpar.IVptr,
                    m_stAESCTRpar.IVLen);
#endif
}
/*----------------------------------{end SA_AESDecrypt_ReqData}-----------------------------------*/
/*----------------------------------{SA_SeedGen_ServerPoo}----------------------------------------*/
NCS_PRI_FCT void SA_SeedGen_ServerPoo(void)
{
#if ((SA_CSMASR43_USED == STD_ON) && (SA_CSM_SETKEY_ENABLED == STD_ON))
    Csm_ReturnType eCsmStatus;
#endif
    /* Concatenate RND num of Server and Client */
    m_aubConcatenatedataptr[0U].DataPtr = &m_aubAesCtrServerRndNum[0];
    m_aubConcatenatedataptr[0U].DataLength = SA_SERVER_RNDNUM_SIZE;

    m_aubConcatenatedataptr[1U].DataPtr = &m_aubAesCtrClientRndNum[0U];
    m_aubConcatenatedataptr[1U].DataLength = SA_CLIENT_RNDNUM_SIZE;

    SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 2U, &m_aubSaAm0001BufAligned16[0U]);

    /*Set Crypto Input and Output Parameters*/
    m_stMACpar.DataLen = SA_CLIENT_RNDNUM_SIZE + SA_SERVER_RNDNUM_SIZE;
    m_stMACpar.CsmCfdID = SA_CSM_MAC_POOGEN_ID;

    m_stMACpar.DataPtr = &m_aubSaAm0001BufAligned16[0U];
    m_stMACpar.MACLen = SA_MACSIZE;
    m_stMACpar.MACLenPtr = (u32*)&m_stMACpar.MACLen;
    m_stMACpar.MACPtr = &m_aubMacValue[0U];

#if (SA_CSMASR43_USED == STD_ON)

#if(SA_CSM_SETKEY_ENABLED == STD_ON)

#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif

    eCsmStatus = SA_CsmSetKeys (m_stMACpar.CsmKeyPtr, SA_CSMMACGENPOOJOBINDEX);
    if (eCsmStatus != CSM_E_OK)
    {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
    else
#endif
    {
        m_ubCsmStatus = Csm_MacGenerate(SA_CSM_MAC_POOGEN_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stMACpar.DataPtr, m_stMACpar.DataLen, m_stMACpar.MACPtr, m_stMACpar.MACLenPtr);
    }
#else
#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif
    /*Initialize the state for SA_MAC Generation*/
    m_eSaCsmState = SA_MAC_GENERATE_START;

    m_ubCsmStatus = Csm_MacGenerateStart
            (
                    m_stMACpar.CsmCfdID,
                    m_stMACpar.CsmKeyPtr
            );
#endif
}
/*----------------------------------{end SA_SeedGen_ServerPoo}------------------------------------*/
/*----------------------------------{SA_SeedGen_EncryptServerPoo}---------------------------------*/
NCS_PRI_FCT void SA_SeedGen_EncryptServerPoo(void)
{
#if (SA_ECB2CTR_ENABLED == STD_ON)
      u32  ulIpDataIdx;
#endif
#if ((SA_CSMASR43_USED == STD_ON) && (SA_CSM_SETKEY_ENABLED == STD_ON))
    Csm_ReturnType eCsmStatus;
#endif

    /*Fill the Csm_SymEncryptStart parameters */
    m_stAESCTRpar.CTptr = &m_aubSaAm0001BufAligned16[0U];
    m_stAESCTRpar.IVLen = SA_AESCTR_IVLEN;
    m_stAESCTRpar.CTLen = SA_AESCTR_BLOCKSIZE;
    m_stAESCTRpar.PTLen = SA_AESCTR_BLOCKSIZE;
    m_stAESCTRpar.IVptr = &m_aubIV_Aligned16[0U];
    m_stAESCTRpar.CTLenptr =  (u32*)&m_stAESCTRpar.CTLen;
    m_stAESCTRpar.PTLenptr = (u32*)&m_stAESCTRpar.PTLen;
    m_stAESCTRpar.CsmCfdID = SA_CSM_AESCTR_ENCRYPT_ID;

    if (m_ubAesBlockIndex < ((SA1_ENCRYPTION_DATALEN/SA_AESCTR_BLOCKSIZE) -1U))
    {
        m_stAESCTRpar.PTptr = &m_aubAesCtrServerRndNum[0U];

        /*Copy the IV to 16 byte aligned buffer*/
        m_aubConcatenatedataptr[0U].DataPtr = &m_pubSAReqResptr[SA2_AESCTR_IVOFFSET];
        m_aubConcatenatedataptr[0U].DataLength = SA_AESCTR_IVLEN;
        SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 1U, &m_aubIV_Aligned16[0U]);
    }
    else
    {
        /*Copy the Previous Encrypted Block from 16 byte aligned buffer to Comm. I/O request-response buffer*/
        m_aubConcatenatedataptr[0U].DataPtr = &m_stAESCTRpar.CTptr[0U];
        m_aubConcatenatedataptr[0U].DataLength = SA_AESCTR_BLOCKSIZE;
        SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U], 1U, \
                &m_pubSAReqResptr[SA1_AESCTR_CTOFFSET_RES + ((m_ubAesBlockIndex -1U) * SA_AESCTR_BLOCKSIZE)]);

        /*Copy the updated IV to request-response buffer*/
        m_aubConcatenatedataptr[0U].DataPtr = &m_aubIV_Aligned16[0U];
        m_aubConcatenatedataptr[0U].DataLength = SA_AESCTR_IVLEN;
        SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 1U, &m_pubSAReqResptr[SA2_AESCTR_IVOFFSET]);

        /*Plaint text for 2nd block encryption*/
        m_stAESCTRpar.PTptr = &m_aubMacValue[0U];
    }
#if SA_ECB2CTR_ENABLED == STD_ON
    if(m_ubAESCTR_Blockcount > 1U)
    {
       /* Current SA AM0001feat has max Block count =2 (32 bytes) for encryption
        * Hence reset the counter after 32 bytes encryption and restore IV val*/
        m_ubAESCTR_Blockcount = 0U;
    }

    m_stAESCTRpar.IVptr[15U] = (m_stAESCTRpar.IVptr[15U] & 0xFCU) + m_ubAESCTR_Blockcount;
    m_ubAESCTR_Blockcount = m_ubAESCTR_Blockcount + 1U;
#endif

#if (SA_CSMASR43_USED == STD_ON)

#if(SA_CSM_SETKEY_ENABLED == STD_ON)

#if(SA_CUSTOMGETAESCTRKEY == STD_ON)
    SA_CustomGetAESCTRKey(&m_stAESCTRpar.CsmKeyPtr, m_stAESCTRpar.CsmCfdID);
#endif

    eCsmStatus = SA_CsmSetKeys (m_stAESCTRpar.CsmKeyPtr, SA_CSMAESENCRYPTJOBINDEX);
    if (eCsmStatus != CSM_E_OK)
    {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
    else
#endif
    {
#if SA_ECB2CTR_ENABLED == STD_ON
        m_ubCsmStatus = Csm_Encrypt(SA_CSM_AESCTR_ENCRYPT_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stAESCTRpar.IVptr, m_stAESCTRpar.IVLen, m_stAESCTRpar.CTptr, m_stAESCTRpar.CTLenptr);
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
        for (ulIpDataIdx = 0U; ulIpDataIdx < m_stAESCTRpar.CTLen; ulIpDataIdx++)
        {
            m_stAESCTRpar.CTptr[ulIpDataIdx] = m_stAESCTRpar.CTptr[ulIpDataIdx] ^ m_stAESCTRpar.PTptr[ulIpDataIdx];
        }
/* CHECK: PARSE */
#else
        m_ubCsmStatus = Csm_Encrypt(SA_CSM_AESCTR_ENCRYPT_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stAESCTRpar.PTptr, m_stAESCTRpar.PTLen, m_stAESCTRpar.CTptr, m_stAESCTRpar.CTLenptr);
#endif
        if (m_ubCsmStatus == CSM_E_OK)
        {
            m_eSaCsmState = SA_IDLE;
            if (m_ubAesBlockIndex < ((SA1_ENCRYPTION_DATALEN/SA_AESCTR_BLOCKSIZE) -1U))
            {
                /* Stay in same state until all the blocks are Encrypted */
                SA_AM0001_SetState(SA_AM0001_STATE_BUSY | m_ulAuthentication0001State);
            }
            else
            {
                SA_AM0001_SetStatus(SA_E_OK);
            }
        }
        else
        {
            /* Do nothing the status shall be checked later */
        }
    }
#else
#if(SA_CUSTOMGETAESCTRKEY == STD_ON)
    SA_CustomGetAESCTRKey(&m_stAESCTRpar.CsmKeyPtr, m_stAESCTRpar.CsmCfdID);
#endif
    /*Initialize the state for SA_AES Encryption*/
    m_eSaCsmState = SA_AES_ENCRYPT_START;

    m_ubCsmStatus = Csm_SymEncryptStart
            (
                    m_stAESCTRpar.CsmCfdID,
                    m_stAESCTRpar.CsmKeyPtr,
                    m_stAESCTRpar.IVptr,
                    m_stAESCTRpar.IVLen);
#endif
    m_ubAesBlockIndex++;
}
/*----------------------------------{end SA_SeedGen_EncryptServerPoo}-----------------------------*/
/*----------------------------------{SA_SeedGen_MsgAuthCode}--------------------------------------*/
NCS_PRI_FCT void SA_SeedGen_MsgAuthCode(void)
{
#if ((SA_CSMASR43_USED == STD_ON)  && (SA_CSM_SETKEY_ENABLED == STD_ON))
   Csm_ReturnType eCsmStatus;
#endif
    /* Copy the last Encrypted Block from 16 byte aligned buffer to Comm. I/O buffer */
    m_aubConcatenatedataptr[0U].DataPtr = &m_stAESCTRpar.CTptr[0U];
    m_aubConcatenatedataptr[0U].DataLength = SA_AESCTR_BLOCKSIZE;

    SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U], 1U, \
            &m_pubSAReqResptr[SA1_AESCTR_CTOFFSET_RES + ((m_ubAesBlockIndex -1U) * SA_AESCTR_BLOCKSIZE)]);

    /*Reset the block counter post encryption*/
    m_ubAesBlockIndex = 0U;

    /* Set the Response Message ID*/
    m_pubSAReqResptr[2U] = (u8)((u32)((SA1_RESPONSE_MSGID) & 0xFF00U) >> 8U);
    m_pubSAReqResptr[3U] = ((SA1_RESPONSE_MSGID) & 0xFFU);

    /*Copy the entire data from Comm. Req-Res buffer to 16 byte aligned buffer*/
    m_aubConcatenatedataptr[0U].DataPtr = &m_pubSAReqResptr[0U];
    m_aubConcatenatedataptr[0U].DataLength = SA1_RESSIZE_WITHOUT_MACVALUE;
    SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U], 1U, &m_aubSaAm0001BufAligned16[0U]);

    m_stMACpar.DataLen = SA1_RESSIZE_WITHOUT_MACVALUE;
    m_stMACpar.CsmCfdID = SA_CSM_MAC_MSGCODEGEN_ID;

    /*Update the Response byte for positive response*/
    m_aubSaAm0001BufAligned16[0U] = m_aubSaAm0001BufAligned16[0U]  + SA_UDS_ACK;

    m_stMACpar.DataPtr = &m_aubSaAm0001BufAligned16[0U];
    m_stMACpar.MACLen = SA_MACSIZE;
    m_stMACpar.MACLenPtr = (u32*)&m_stMACpar.MACLen;
    /* MAC pointer shall be 16 byte aligned*/
    m_stMACpar.MACPtr = &m_aubMacValue[0U];

#if (SA_CSMASR43_USED == STD_ON)

#if(SA_CSM_SETKEY_ENABLED == STD_ON)

#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif
    eCsmStatus = SA_CsmSetKeys (m_stMACpar.CsmKeyPtr, SA_CSMMACGENMSGAUTHJOBINDEX);
    if (eCsmStatus != CSM_E_OK)
    {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
    else
#endif
    {
        m_ubCsmStatus = Csm_MacGenerate(SA_CSM_MAC_MSGCODEGEN_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stMACpar.DataPtr, m_stMACpar.DataLen, m_stMACpar.MACPtr, m_stMACpar.MACLenPtr);

    }
#else
#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif
    /*Initialize the state for SA_MAC Generation*/
    m_eSaCsmState = SA_MAC_GENERATE_START;

    m_ubCsmStatus = Csm_MacGenerateStart
            (
                    m_stMACpar.CsmCfdID,
                    m_stMACpar.CsmKeyPtr
            );
#endif
}
/*----------------------------------{end SA_SeedGen_MsgAuthCode}----------------------------------*/
/*----------------------------------{SA_KeyUnlock}------------------------------------------------*/
NCS_PRI_FCT void SA_KeyUnlock(void)
{
#if ((SA_CSMASR43_USED == STD_ON) && (SA_CSM_SETKEY_ENABLED == STD_ON))
    Csm_ReturnType eCsmStatus;
#endif
    /* Concatenate RND num of Client and Server */
    m_aubConcatenatedataptr[1U].DataPtr = &m_aubAesCtrServerRndNum[0];
    m_aubConcatenatedataptr[1U].DataLength = SA_SERVER_RNDNUM_SIZE;

    m_aubConcatenatedataptr[0U].DataPtr = &m_aubAesCtrClientRndNum[0U];
    m_aubConcatenatedataptr[0U].DataLength = SA_CLIENT_RNDNUM_SIZE;

    SA_ConcatenateAndStoreData(&m_aubConcatenatedataptr[0U] , 2U, &m_aubSaAm0001BufAligned16[0U]);

    m_stMACpar.DataLen = SA_SERVER_RNDNUM_SIZE + SA_CLIENT_RNDNUM_SIZE;
    m_stMACpar.CsmCfdID = SA_CSM_MAC_POOVRFY_ID;

    m_stMACpar.DataPtr = &m_aubSaAm0001BufAligned16[0U];
    m_stMACpar.MACLen = SA_MACSIZE;
    m_stMACpar.MACLenPtr = (u32*)&m_stMACpar.MACLen;
    /* MAC pointer shall be 16 byte aligned*/
    m_stMACpar.MACPtr = &m_aubMacValue[0U];

#if (SA_CSMASR43_USED == STD_ON)
#if(SA_CSM_CANCELJOB_ENABLED == STD_ON)
    if(m_astSACsmJobConf[SA_CSMMACVERIFPOOJOBINDEX].ubAllowJobCancellation == PROG_TRUE)
    {
       (void)SA_CsmCancelActiveJobs();
    }
#endif
#if(SA_CSM_SETKEY_ENABLED == STD_ON)

#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif

    eCsmStatus = SA_CsmSetKeys (m_stMACpar.CsmKeyPtr, SA_CSMMACVERIFPOOJOBINDEX);
    if (eCsmStatus != CSM_E_OK)
    {
        m_eSaStatus = SA_E_NOT_OK;
        m_eSaCsmState = SA_IDLE;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
    else
#endif
    {
        m_ubCsmStatus = Csm_MacVerify(SA_CSM_MAC_POOVRFY_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
            m_stMACpar.DataPtr, m_stMACpar.DataLen, m_stMACpar.MACPtr, m_stMACpar.MACLen*8U, &m_ubMacVerificationResult);

        m_eSaCsmState = SA_IDLE;
#if (SA_CSMASR43_USED == STD_ON)
        SA_AM0001_SetState(SA_AM0001_STATE_BUSY|(m_ulAuthentication0001State << 1));
#endif
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
        if ((m_ubCsmStatus == CSM_E_OK) && (m_ubMacVerificationResult == CSM_E_VER_OK))
        {
           SA_AM0001_SetStatus(SA_E_OK);
        }
        else
        {
           m_eSaStatus = SA_E_NOT_OK;
           SA_AM0001_SetStatus(SA_E_NOT_OK);
        }
/* CHECK: PARSE */
    }
#else
#if(SA_CUSTOMGETMACKEY == STD_ON)
    SA_CustomGetMACKey(&m_stMACpar.CsmKeyPtr, m_stMACpar.CsmCfdID);
#endif
    /*Initialize the state for SA_MAC verification*/
    m_eSaCsmState = SA_MAC_VERIFY_START;

    m_ubCsmStatus = Csm_MacVerifyStart
            (
                    m_stMACpar.CsmCfdID,
                    m_stMACpar.CsmKeyPtr
            );
#endif
}
/*----------------------------------{end SA_KeyUnlock}--------------------------------------------*/
#endif /*SA_AUTHENTICATION_METHOD SA_AUTHENTICATION_0001*/
