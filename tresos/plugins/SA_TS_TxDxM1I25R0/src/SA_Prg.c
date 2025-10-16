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
/*%%   _____________________________   %%  \file SA_Prg.c                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.255 BL3 */
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
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type and a pointer to a
 * different object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 *
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * Variable is already has a unique declaration. no functional impact.
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "board.h"
#include "SA_Priv.h"
#include "SA_Cbk.h"
#include <SA_Trace.h>                        /* Dbg related macros for EB */
#include "SA_Pub.h"
/*                                                                               */
/*===============================================================================*/

/* CHECK: RULE 503 OFF */


/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/* Deviation MISRAC2012-2 */
tSaStatus m_eSaStatus;
#if (SA_USE_CRYPTO == STD_ON)
tSaCsmState m_eSaCsmState;
u8* m_pubDataRandomNumber;
u8 m_aubLastRandomNumber[SA_RANDOM_NUMBER_LENGTH];
u8 m_aubCurrentRandomNumber[SA_RANDOM_NUMBER_LENGTH];
tSaBoolean m_ubGenRandReqReceived;
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
Csm_AsymPublicKeyType m_stAsymPublicKey;
const u8* m_pubCryptoSignature;
u8 m_ubVerifSigUpdateReqReceived;
Csm_VerifyResultType m_ubVerifyResult;
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
u32 m_ulSA2waitTime;
u8 m_ubMacVerificationResult;
#endif /*#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)*/
#endif /*(SA_USE_CRYPTO == STD_ON)*/

#if (SA_CSMASR43_USED == STD_ON)
uint32 m_aubCurrentRandomNumberlen;
#endif /*SA_CSMASR43_USED*/
#if (SA_STATIC_SEED_ENABLED == STD_ON)
u8 m_ubLastSeedWasUsed;
u8 m_aubLastSeed[SA_SEED_LEN];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
tLimitReqSeedInfo m_stLimitReqSeed;
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/

#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))
u8 m_aubSeedForSASApi[SA_RANDOM_NUMBER_LENGTH];
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON)) */
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
/* - Private Variables */
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))
u8 m_aubCalculatedKey[SA_KEY_LEN];
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)*/

#if (SA_ANTISCANNING_ENABLED == STD_ON)
tAntiscanInfo m_stAntiscanInfo;
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{SA_Init}------------------------------------*/
void SA_Init (void)
{
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))
    u8 localIdx;
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON))) */
    DBG_SA_INIT_ENTRY();
    /*Init SA status*/
    m_eSaStatus = SA_E_NOT_OK;
    /*Init SA calculated key*/
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))
    for (localIdx = 0U; localIdx < SA_KEY_LEN; localIdx++)
    {
        m_aubCalculatedKey[localIdx] = 0U;
    }
#endif /*((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))*/
#if ((SA_COMPRESSION_STATE == SA_COMPRESSION_ENABLED) && (PROG_CAL_PRESENT == STD_OFF))
    SA_DecompressInit();
#endif
#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
    SA_InitCrypto();
#endif
#if (SA_ANTISCANNING_ENABLED == STD_ON)
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
    if (m_stAntiscanInfo.ulLockTimer < SA_RS_DELAY_TIMER)
    {
        /*Rearm request seed delay timer*/
        PROG_SetRsDelayTimer(SA_RS_DELAY_TIMER);
    }
    else
    {
        /*Do nothing*/
    }
#endif/*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
    /*Restore SA Anti-scanning retry counter*/
    m_stAntiscanInfo.ubRetryCnt = SA_CustomRestoreAsRetryCnt();
    if((SA_AS_MAX_NB_RETRY - 1U) < m_stAntiscanInfo.ubRetryCnt)
    {
        /*Rearm Antiscanning Lock Timer*/
        m_stAntiscanInfo.ulLockTimer = SA_AS_LOCK_TIMER;
        m_stAntiscanInfo.ubAsLocked = SA_TRUE;
        m_eSaStatus = SA_E_NOK_AS_LOCKED;
    }
    else
    {
        m_stAntiscanInfo.ulLockTimer = 0U;
        m_stAntiscanInfo.ubAsLocked = SA_FALSE;
    }

#elif (SA_ANTISCANNING_ENABLED == STD_OFF)
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
    /*Rearm request seed delay timer*/
    PROG_SetRsDelayTimer(SA_RS_DELAY_TIMER);
#endif/*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
    PROG_SetRequestSeedCounter(0U);
    PROG_SetRequestSeedTimer(0U);
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/

#if (SA_STATIC_SEED_ENABLED == STD_ON)
    m_ubLastSeedWasUsed = SA_TRUE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
#if (SA_CSMASR43_USED == STD_ON)
    m_aubCurrentRandomNumberlen = SA_RANDOM_NUMBER_LENGTH;
#endif /*SA_CSMASR43_USED*/
    DBG_SA_INIT_EXIT();
}
/*----------------------------------{end SA_Init}----------------------------*/

/*----------------------------------{SA_Manage}--------------------------------*/
void SA_Manage (void)
{
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
    u32 RequestSeedTimer;
    u8 RequestSeedCounter;
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
    tSA_AuthenticationState ulAuthentication0001State;
#endif
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
    u32 ulRsDelayTimer;
#endif /*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
    DBG_SA_MANAGE_ENTRY();
#if (SA_ANTISCANNING_ENABLED == STD_ON)

    /*Is the Anti-scanning locked*/
    if(0U < m_stAntiscanInfo.ulLockTimer)
    {
        /*Decrement Anti-scanning Lock Timer*/
        m_stAntiscanInfo.ulLockTimer--;
    }
    else
    {
        if(SA_TRUE == m_stAntiscanInfo.ubAsLocked)
        {
            /*Reset anti-scanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt = 0U;
            m_stAntiscanInfo.ubAsLocked = SA_FALSE;
            m_eSaStatus = SA_E_OK;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt( m_stAntiscanInfo.ubRetryCnt);
        }
        else
        {
            /*Do nothing*/
        }
    }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
    /*Get request seed delay timer value*/
    ulRsDelayTimer = PROG_GetRsDelayTimer();
    if (ulRsDelayTimer > 0U)
    {
        /*Decrement request seed delay timer*/
        ulRsDelayTimer --;
        /*Set request seed delay timer*/
        PROG_SetRsDelayTimer(ulRsDelayTimer);
    }
    else
    {
        /*Do nothing*/
    }
#endif/*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
    RequestSeedTimer = PROG_GetRequestSeedTimer();
    /*check if the timer is not eqal to zero */
    if (RequestSeedTimer > 0U)
    {
        /*Decrement limit request seed Timer*/
      RequestSeedTimer-- ;
      PROG_SetRequestSeedTimer(RequestSeedTimer);
    }
    else
    {
        /*Reset limit request seed counter*/
      RequestSeedCounter = 0U;
      PROG_SetRequestSeedCounter(RequestSeedCounter);
    }

#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001 )
    ulAuthentication0001State = SA_AM0001_GetState();
    if((ulAuthentication0001State == SA_AWAIT_SA2REQ) || (ulAuthentication0001State == SA_AWAIT_SA2REQ_BUSY))
    {
        if (m_ulSA2waitTime == 0U)
        {
            /* SA_WAIT, SA1 has been sent successfully, wait for the Key(SA2) Request for the configured time*/
            m_ulSA2waitTime = SA2_MAX_AWAIT_TIME;
            SA_AM0001_SetState(SA_AWAIT_SA2REQ_BUSY);
        }
        else
        {
            m_ulSA2waitTime--;
            if (m_ulSA2waitTime == 0U)
            {
                /*WaitingTime Expired SA2 cannot be received any more, resend SA1 to unlock*/
                SA_AM0001_SetStatus(SA_E_WAITING_SA2_NOT_OK);
            }
        }
    }
    else
    {
        /* SA2 wait timer not running */
        m_ulSA2waitTime = 0U;
    }
#endif
    DBG_SA_MANAGE_EXIT();
}
/*----------------------------------{end SA_Manage}----------------------------*/

/*----------------------------------{SA_GetSeed}--------------------------------*/
tSaStatus SA_GetSeed(u8* aubSeed)
{
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
    u32 ulRsDelayTimer;
#endif /*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
      u32 RequestSeedTimer;
      u8 RequestSeedCounter;
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/
    tSaStatus eSaStatus;
#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
#if (SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD)
    u32 ulTempSeedData;
    /* Index of first copied byte of the random seed */
    u8 ubIdxRandom = 3U;
#endif /*(SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD) */
#endif /* if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM) */

#if ((SA_SEED_TYPE != SA_SEED_CSM_RANDOM) || (SA_STATIC_SEED_ENABLED == STD_ON))
    /* Index of byte of the seed */
    u8 ubIdx;
#endif /*((SA_SEED_TYPE != SA_SEED_CSM_RANDOM) || (SA_STATIC_SEED_ENABLED == STD_ON))*/

    DBG_SA_GETSEED_ENTRY(aubSeed);

#if (SA_ANTISCANNING_ENABLED == STD_ON)
    if(0U == m_stAntiscanInfo.ulLockTimer)
    {
        /*Anti-scanning not locked*/
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
        /*Get request seed dalay timer value*/
        ulRsDelayTimer = PROG_GetRsDelayTimer();
        if (ulRsDelayTimer == 0U)
        {
#endif/*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)*/
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
          RequestSeedCounter = PROG_GetRequestSeedCounter();
            if (RequestSeedCounter < SA_RS_LIMIT_COUNTER)
            {
                /* Request seed limit not reached*/
                if (RequestSeedCounter == 0U)
                {
                    /*Resert Timer*/
                  RequestSeedTimer = SA_RS_LIMIT_TIMER;
                  PROG_SetRequestSeedTimer(RequestSeedTimer);
                }
                /*Increment limit request seed counter */
                RequestSeedCounter++;
                PROG_SetRequestSeedCounter(RequestSeedCounter);
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/
#if (SA_STATIC_SEED_ENABLED == STD_ON)
            if(SA_TRUE == m_ubLastSeedWasUsed)
            {
                /* Generate new seed */
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001 )
            /*Start Verification of the recevied MAC*/
            eSaStatus = SA_E_BUSY;

            /*Start AM0001 Authentication Procedure*/
            SA_AM0001_SetState(SA_VRFYMSG_AUTHCODE_SA1);
            /*Store the Input-Output data ptr for further processing*/
            m_pubSAReqResptr = &aubSeed[0U];
#else
#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
#if (SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD)
                ulTempSeedData = BoardGetRandom();

                /* For each byte of the seed */
                for (ubIdx = 0U; ubIdx < SA_SEED_LEN; ubIdx++)
                {
                    /* Copy each byte of the random seed */
                    aubSeed[ubIdx] = (u8)((u32)(ulTempSeedData >> (8U*ubIdxRandom)) & 0x000000FFU);
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                    /*store the generated seed*/
                    m_aubLastSeed[ubIdx] = aubSeed[ubIdx];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
                    /* If all of the four bytes of the random seed have been copied */
                    if (0U == ubIdxRandom)
                    {
                        /* Set the index to the first copied byte of the random seed */
                        ubIdxRandom = 3U;

                        /* Generate an other random seed */
                        ulTempSeedData = BoardGetRandom();
                    }
                    else
                    {
                        /* Decrease the index of the copied byte of the random seed */
                        ubIdxRandom--;
                    }
                }
#else
                SA_CustomGetRandomSeed(&aubSeed[0]);
                /* For each byte of the seed */
                for (ubIdx = 0U; ubIdx < SA_SEED_LEN; ubIdx++)
                {
                /* Copy seed data if Static seed feature enabled */
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                    /*store the generated seed*/
                    m_aubLastSeed[ubIdx] = aubSeed[ubIdx];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))
                /* Copy the seed incase of Key calculation was custom*/
                    m_aubSeedForSASApi[ubIdx] = aubSeed[ubIdx];
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON)) */
                }
#endif /* (SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD) */
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                /*reset the seed usage flag*/
                m_ubLastSeedWasUsed = SA_FALSE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if (SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD)
                PROG_CalculateKey(&aubSeed[0], &m_aubCalculatedKey[0]);
#else
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))
                /*Use custom algorithm to calculate key*/
                SA_CustomCalculateKey(&aubSeed[0], &m_aubCalculatedKey[0]);
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON))) */
#endif
                eSaStatus = SA_E_OK;
#endif /* if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM) */

#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
                eSaStatus = SA_GenerateRandomNumber (aubSeed);
#endif /* (SA_SEED_TYPE == SA_SEED_CSM_RANDOM) */
#endif /* (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001 )*/
#if (SA_STATIC_SEED_ENABLED == STD_ON)
            }
            else
            {
                /*The last generated seed was not used, send it again*/
                for (ubIdx = 0U; ubIdx < SA_SEED_LEN; ubIdx++)
                {
                    /* Copy each byte of the last seed */
                    aubSeed[ubIdx] = m_aubLastSeed[ubIdx];
                }
                eSaStatus = SA_E_OK;
            }
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
            }
            else
            {
                /* Request seed limit reached*/
                eSaStatus = SA_E_NOK_AS_LIMIT_RS;
            }
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/
#if (SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
        }
        else
        {
            eSaStatus = SA_E_NOK_RS_DELAY_LOCKED;
        }
#endif /*(SA_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON) */
#if (SA_ANTISCANNING_ENABLED == STD_ON)
    }
    else
    {
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
      RequestSeedCounter = PROG_GetRequestSeedCounter();
      if (RequestSeedCounter == 0U)
        {
          /*Resert Timer*/
          RequestSeedTimer = SA_RS_LIMIT_TIMER;
          PROG_SetRequestSeedTimer(RequestSeedTimer);
        }
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/
        /*Anti-scanning locked*/
        eSaStatus = SA_E_NOK_AS_LOCKED;
    }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/

    DBG_SA_GETSEED_EXIT(eSaStatus);
    return eSaStatus;
}
/*----------------------------------{end SA_GetSeed}----------------------------*/

/*----------------------------------{SA_CompareKey}-----------------------------*/
tSaStatus SA_CompareKey (u8* aubReceivedKey)
{
    tSaStatus eSaStatus = SA_E_NOT_OK;

#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))
    Dcm_NegativeResponseType ErrorCode = SA_E_NOT_OK;
    Std_ReturnType SAS_CompareKeyStat = SA_TRUE;
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))*/
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))
#if (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_OFF)
    u8 ubIdx;
    tSaBoolean ubKeyMatch;
#endif
#endif /* if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON))) */
    DBG_SA_COMPAREKEY_ENTRY(aubReceivedKey);
#if (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)

    eSaStatus = SA_GetStatus();
    if(SA_E_OK == eSaStatus)
    {
        /* SA2 received before wait time expired correctly */
        SA_AM0001_SetStatus(SA_E_OK);
        /*Store the Input-Output data ptr for further processing*/
        m_pubSAReqResptr = &aubReceivedKey[0U];
        /*Return status BUSY here for time being and further processing will be done in the do action*/
        eSaStatus = SA_E_BUSY;
    }
    else
    {
        /* SA2 request received but Conditions not correct,
         * however the global status is already updated hence
         * appropriate response shall be sent from Prog do action*/
    }
#else
#if (SA_STATIC_SEED_ENABLED == STD_ON)
    /*The generated seed was used*/
    m_ubLastSeedWasUsed = SA_TRUE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if ( (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)) )
    ubKeyMatch = SA_TRUE;
    /*Check received key*/
    for (ubIdx = 0U; ubIdx < SA_KEY_LEN; ubIdx++)
    {
        if(m_aubCalculatedKey[ubIdx] != aubReceivedKey[ubIdx])
        {
            ubKeyMatch = SA_FALSE;
        }
    }
    eSaStatus = SA_Antiscanning(ubKeyMatch);
#elif ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))
    /* FORD wants to use their own compare key function which will return the error code directly with help of DCM Library */
    SAS_CompareKeyStat = SAS_CompareKeyLevel01(aubReceivedKey, m_aubSeedForSASApi, &ErrorCode);
    /* Copy the status from DCM */
    if(SAS_CompareKeyStat == SA_E_BUSY)
    {
        /*Update status global*/
        m_eSaStatus = SA_E_BUSY;
        /*Return status BUSY*/
        eSaStatus = SA_E_BUSY;
    }
    else if (SAS_CompareKeyStat == E_OK)
    {
        /*Key Matches*/
        eSaStatus = SA_Antiscanning(SA_TRUE);
    }
    else if (ErrorCode == UDS_NRC_35)
    {
        /* Key is invalid */
        eSaStatus = SA_Antiscanning(SA_FALSE);
    }
    else
    {
        /* Other NRC */
        eSaStatus = ErrorCode;
    }
#else
    /* Do nothing */
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON)) */

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_OFF)
    /* The received key is a signature, verify it */
    SA_VerifySignatureUpdate(aubReceivedKey);
    /*Update status global*/
    m_eSaStatus = SA_E_BUSY;
    /*Return status BUSY*/
    eSaStatus = SA_E_BUSY;
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_OFF) */
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_ON)
    /* Update the pointer to the received signature */
    m_pubCryptoSignature = aubReceivedKey;

    /* Start the signature verification algorithm */
    SA_VerifySignature(&m_stAsymPublicKey);

    /* Return status BUSY, response shall be sent from the Do-action of the CompareKey State */
    eSaStatus = SA_E_BUSY;
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_ON) */
#if (SA_COMPARE_KEY_TYPE != SA_COMPARE_KEY_VERIFY_SIGNATURE)&&(SA_COMPARE_KEY_TYPE != SA_COMPARE_KEY_STANDARD)
    OSC_PARAM_UNUSED(aubReceivedKey);
#endif
#endif /* (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)*/

    DBG_SA_COMPAREKEY_EXIT(eSaStatus);
    return eSaStatus;
}
/*----------------------------------{end SA_CompareKey}-------------------------*/

#if (SA_USE_CRYPTO == STD_ON)
/*---------------------------{SA_InitCrypto}-----------------------------*/
void SA_InitCrypto(void)
{
#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
    Csm_ReturnType eCsmStatus;
#endif /*(SA_SEED_TYPE == SA_SEED_CSM_RANDOM)*/
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
    static u8 aubSAReqRes[SA1_MSGREQ_SIZE];
#endif
#endif
    DBG_SA_INITCRYPTO_ENTRY();

#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
    m_ubSaAllKeysStatus = SA_E_STATUS_UNKNOWN;
    m_pubSAReqResptr = (u8*)&aubSAReqRes[0U];
    SA_AM0001_SetState(SA_SEEDGEN_SERVERPOO);
    m_eSaStatus = SA_E_OK;
    while(m_ubSaAllKeysStatus == SA_E_STATUS_UNKNOWN)
    {
        /* Perform tests to check if the Secured Keys are programmed */
        SA_AuthMethod0001();
        SA_Csm_MainFunction();
    }
#else
    SA_AM0001_SetState(SA_AM0001_IDLE);
#endif /*(SA_SECUREDKEYS_STATUSREAD == STD_ON)*/
#endif
#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
    /* Start random number generation*/
#if (SA_CSMASR43_USED == STD_ON)
    /* Get the last seed of a random value for seed generation */
    SA_CustomGetLastRandomNumber(m_aubLastRandomNumber);
#if(SA_CSM_CANCELJOB_ENABLED == STD_ON)
    if(m_astSACsmJobConf[SA_CSMRANDOMSEEDJOBINDEX].ubAllowJobCancellation == PROG_TRUE)
    {
       (void)SA_CsmCancelActiveJobs();
    }
#endif
    eCsmStatus = Csm_RandomSeed(SA_CSM_RANDOM_SEED_KEYID,(const u8*) m_aubLastRandomNumber,(u32)SA_RANDOM_NUMBER_LENGTH);
#else
    eCsmStatus = Csm_RandomSeedStart(SA_CSM_RANDOM_SEED_ID);
#endif
    if(eCsmStatus == CSM_E_OK)
    {
#if (SA_CSMASR43_USED == STD_ON)
        m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
#else
        m_eSaCsmState = SA_SEED_GEN_STATE_START;
#endif
    }
    else
    {
#if (SA_CSMASR43_USED == STD_ON)
        m_eSaCsmState = SA_CSM_STATE_INIT;
        m_eSaStatus = SA_E_NOT_OK;
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
        SA_AM0001_SetStatus(SA_E_NOT_OK);
#endif
#else
        m_eSaCsmState = SA_SEED_GEN_STATE_INIT;
#endif
    }
#endif /*(SA_SEED_TYPE == SA_SEED_CSM_RANDOM)*/
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
    SA_GetPublicKey(&m_stAsymPublicKey);
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */

    DBG_SA_INITCRYPTO_EXIT();
}
/*------------------------{end SA_InitCrypto}--------------------------*/

/*---------------------------{SA_GenerateRandomNumber}-----------------------------*/
tSaStatus SA_GenerateRandomNumber(u8* aubRandomNumber)
{
    Csm_ReturnType eCsmStatus;

    DBG_SA_GENERATERANDOMNUMBER_ENTRY(aubRandomNumber);
    /* Memorize Random Number buffer address for usage in next step */
    m_pubDataRandomNumber = aubRandomNumber;
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_OFF)
    if((m_eSaCsmState == SA_RANDOM_GEN_STATE_STANDBY)
        || (m_eSaCsmState == SA_SIGNATURE_CHECK_START)
        || (m_eSaCsmState == SA_SIGNATURE_CHECK_UPDATE)
        || (m_eSaCsmState == SA_SIGNATURE_CHECK_STANDBY))
#else
    if(m_eSaCsmState == SA_RANDOM_GEN_STATE_STANDBY)
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */
    {
#if (SA_CSMASR43_USED == STD_ON)
        eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, (u8 *)m_aubCurrentRandomNumber, (u32 *)&m_aubCurrentRandomNumberlen);
#else
        eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, (u8 *)m_aubCurrentRandomNumber, SA_RANDOM_NUMBER_LENGTH);
#endif /*SA_CSMASR43_USED*/
        if(eCsmStatus == CSM_E_OK)
        {
            m_eSaCsmState = SA_RANDOM_GEN_STATE_GENERATE;
            m_eSaStatus = SA_E_BUSY;
#if (SA_CSMASR43_USED == STD_ON)
            SA_GenerateRandomCallback(eCsmStatus);
#endif /*SA_CSMASR43_USED*/
        }
        else
        {
            m_eSaCsmState = SA_CSM_STATE_INIT;
            m_eSaStatus = SA_E_NOT_OK;
        }
    }
    else
    {
        if(m_eSaCsmState == SA_CSM_STATE_INIT)
        {
            m_eSaCsmState = SA_SEED_GEN_STATE_INIT;
            m_eSaStatus = SA_E_NOT_OK;
        }
        else
        {
            m_ubGenRandReqReceived = SA_TRUE;
            m_eSaStatus = SA_E_BUSY;
        }
    }

    DBG_SA_GENERATERANDOMNUMBER_EXIT(m_eSaStatus);
    return m_eSaStatus;
}
/*------------------------{end SA_GenerateRandomNumber}--------------------------*/

/*---------------------------{SA_GenerateRandomCallback}-----------------------------*/
void SA_GenerateRandomCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    u32 ulLocalIdx;

    DBG_SA_GENERATERANDOMCALLBACK_ENTRY(eCsmResult);
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
#if (SA_CSMASR43_USED == STD_OFF)
            case SA_SEED_GEN_STATE_START:
                /* Get the last seed of a random value for seed generation */
                SA_CustomGetLastRandomNumber(m_aubLastRandomNumber);
                eCsmStatus = Csm_RandomSeedUpdate(SA_CSM_RANDOM_SEED_ID, (const u8*) m_aubLastRandomNumber, (u32)SA_RANDOM_NUMBER_LENGTH);
                if(eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_SEED_GEN_STATE_UPDATE;
                }
                else
                {
                    m_eSaCsmState = SA_CSM_STATE_INIT;
                    m_eSaStatus = SA_E_NOT_OK;
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
                    SA_AM0001_SetStatus(SA_E_NOT_OK);
#endif
                }
                break;
            case SA_SEED_GEN_STATE_UPDATE:
                eCsmStatus = Csm_RandomSeedFinish(SA_CSM_RANDOM_SEED_ID);
                if(eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
                }
                else
                {
                    m_eSaCsmState = SA_CSM_STATE_INIT;
                    m_eSaStatus = SA_E_NOT_OK;
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
                    SA_AM0001_SetStatus(SA_E_NOT_OK);
#endif
                }
                break;
#endif
            case SA_RANDOM_GEN_STATE_STANDBY:
                if(SA_TRUE == m_ubGenRandReqReceived)
                {
#if (SA_CSMASR43_USED == STD_ON)
                    eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID,(u8 *)m_aubCurrentRandomNumber,(u32 *) &m_aubCurrentRandomNumberlen);
#else
                    eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, (u8 *)m_aubCurrentRandomNumber, SA_RANDOM_NUMBER_LENGTH);
#endif /*SA_CSMASR43_USED*/
                    if(eCsmStatus == CSM_E_OK)
                    {
                        m_eSaCsmState = SA_RANDOM_GEN_STATE_GENERATE;
                    }
                    else
                    {
                        m_eSaCsmState = SA_CSM_STATE_INIT;
                        m_eSaStatus = SA_E_NOT_OK;
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
                        SA_AM0001_SetStatus(SA_E_NOT_OK);
#endif
                    }
                }
                break;
            case SA_RANDOM_GEN_STATE_GENERATE:
                /* The random number has been generated and can now be used */
                m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
                /* Store the random value for further use */
                for(ulLocalIdx=0; ulLocalIdx<SA_RANDOM_NUMBER_LENGTH; ulLocalIdx++)
                {
                    m_pubDataRandomNumber[ulLocalIdx] = m_aubCurrentRandomNumber[ulLocalIdx];
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                    /* Store the last generated Seed */
                    m_aubLastSeed[ulLocalIdx] = m_aubCurrentRandomNumber[ulLocalIdx];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))
                    m_aubSeedForSASApi[ulLocalIdx] =m_aubCurrentRandomNumber[ulLocalIdx] ;
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON)) */
                }
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                    /* Reset the Seed usage flag */
                    m_ubLastSeedWasUsed = SA_FALSE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
                SA_CustomStoreRandomNumber(m_aubCurrentRandomNumber);

#if ( (SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD) )
            PROG_CalculateKey(m_aubCurrentRandomNumber, &m_aubCalculatedKey[0]);
#endif

#if ((SA_SEED_TYPE == SA_SEED_CSM_RANDOM) && (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_OFF))
                m_eSaStatus = SA_E_OK;
#endif /* if ((SA_SEED_TYPE == SA_SEED_CSM_RANDOM) && (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_OFF)) */
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_OFF)
                /* Start the signature verification algorithm */
                SA_VerifySignature(&m_stAsymPublicKey);
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
                /* Rnd num Generated Successfully */
                SA_AM0001_SetStatus(SA_E_OK);
#endif
                break;
            default:
                /* Nothing to do */
                break;
        }
    }
    else
    {
        m_eSaCsmState = SA_SEED_GEN_STATE_INIT;
        m_eSaStatus = SA_E_NOT_OK;
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
        SA_AM0001_SetStatus(SA_E_NOT_OK);
#endif
    }

    DBG_SA_GENERATERANDOMCALLBACK_EXIT();
}
/*------------------------{end SA_GenerateRandomCallback}--------------------------*/

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
#if (SA_CSMASR43_USED == STD_OFF)
/*---------------------------{SA_SignatureVerifAndHashCallback}-----------------------------*/
void SA_SignatureVerifAndHashCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    tSaBoolean ubKeyMatch;

    DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_ENTRY(eCsmResult);
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_SIGNATURE_CHECK_START:
                eCsmStatus = Csm_SignatureVerifyUpdate(SA_CSM_SIG_VERIFY_ID, (const u8*) m_aubCurrentRandomNumber,SA_SEED_LEN);
                m_eSaCsmState = SA_SIGNATURE_CHECK_UPDATE;
                if(eCsmStatus != CSM_E_OK)
                {
                    /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
                    The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
                    m_eSaStatus = SA_Antiscanning(SA_FALSE);
                    m_eSaCsmState = SA_CSM_STATE_INIT;
                }
                break;
            case SA_SIGNATURE_CHECK_UPDATE:
                if(SA_TRUE == m_ubVerifSigUpdateReqReceived)
                {
                    eCsmStatus = Csm_SignatureVerifyFinish(SA_CSM_SIG_VERIFY_ID, m_pubCryptoSignature, SA_SIGNATURE_LENGTH, &m_ubVerifyResult);
                    /* continue with the signature verification */
                    m_eSaCsmState = SA_SIGNATURE_CHECK_FINISH;
                    m_ubVerifSigUpdateReqReceived = FALSE;
                    if(eCsmStatus != CSM_E_OK)
                    {
                        /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
                        The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
                        m_eSaStatus = SA_Antiscanning(SA_FALSE);
                        m_eSaCsmState = SA_CSM_STATE_INIT;
                    }
                }
                else
                {
                    m_eSaCsmState = SA_SIGNATURE_CHECK_STANDBY;
                }
                break;
            case SA_SIGNATURE_CHECK_FINISH:
                m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
                if(m_ubVerifyResult == CSM_E_VER_OK)
                {
                    ubKeyMatch = SA_TRUE;
                }
                else
                {
                    ubKeyMatch = SA_FALSE;
                }
                /* Check for SA_ANTISCANNING_ENABLED is done inside SA_Antiscanning()*/
                m_eSaStatus = SA_Antiscanning(ubKeyMatch);
                break;
            case SA_SIGNATURE_CHECK_STANDBY:
                break;
            default:
                /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
                The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
                m_eSaStatus = SA_Antiscanning(SA_FALSE);
                m_eSaCsmState = SA_CSM_STATE_INIT;
                break;
        }
    }
    else
    {
        /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
        The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
        m_eSaStatus = SA_Antiscanning(SA_FALSE);
        m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
    }

    DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_EXIT();
}
/*------------------------{end SA_SignatureVerifAndHashCallback}--------------------------*/
#endif
/*---------------------------{SA_VerifySignature}-----------------------------*/
void SA_VerifySignature(const Csm_AsymPublicKeyType* pstAsymPublicKey)
{
    Csm_ReturnType eCsmStatus = CSM_E_OK;
#if (SA_CSMASR43_USED == STD_ON)
    tSaBoolean ubKeyMatch;
#endif
    DBG_SA_VERIFYSIGNATURE_ENTRY(pstAsymPublicKey);
#if (SA_CSMASR43_USED == STD_ON)
#if(SA_CUSTOM_CSMSTARTPREPROCESS_ENABLED == STD_ON)
    /* Deviation MISRAC2012-1 */
    eCsmStatus = SA_CustomCsmStrtPreproc((const u8**)&pstAsymPublicKey, m_astSACsmJobConf[SA_CSMSIGNATUREJOBINDEX].ubCsmJobId);
#endif /* (SA_CUSTOM_CSMSTARTPREPROCESS_ENABLED == STD_ON) */
    if (eCsmStatus == CSM_E_OK)
    {
        eCsmStatus = Csm_KeyElementSet
                     (
                       SA_CSM_SIG_VERIFY_KEYID,
                       SA_CRYPTO_SIGN_KEYELEID,
                       (u8 const *)pstAsymPublicKey,
                       SA_PUBLIC_KEY_LENGTH
                     );
        if (eCsmStatus == E_OK)
        {
            /*Before the use of the key, set the key state to valid*/
            eCsmStatus = Csm_KeySetValid(SA_CSM_SIG_VERIFY_KEYID);
        }
        if (eCsmStatus == E_OK)
        {
            eCsmStatus = Csm_SignatureVerify(SA_CSM_SIG_VERIFY_ID, CRYPTO_OPERATIONMODE_SINGLECALL,\
                 (const u8*) m_aubCurrentRandomNumber, SA_SEED_LEN, m_pubCryptoSignature, SA_SIGNATURE_LENGTH, &m_ubVerifyResult);
        }
    }
#else
    eCsmStatus = Csm_SignatureVerifyStart(SA_CSM_SIG_VERIFY_ID, pstAsymPublicKey);
#endif
    if(eCsmStatus == CSM_E_OK)
    {
#if (SA_CSMASR43_USED == STD_ON)
        if(m_ubVerifyResult == CSM_E_VER_OK)
        {
            ubKeyMatch = SA_TRUE;
        }
        else
        {
            ubKeyMatch = SA_FALSE;
        }
        /* Check for SA_ANTISCANNING_ENABLED is done inside SA_Antiscanning()*/
        m_eSaStatus = SA_Antiscanning(ubKeyMatch);
#else
        m_eSaCsmState = SA_SIGNATURE_CHECK_START;
#endif
    }
    else
    {
        /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
        The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
        m_eSaStatus = SA_Antiscanning(SA_FALSE);
        m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
    }

    DBG_SA_VERIFYSIGNATURE_EXIT();
    }
/*------------------------{end SA_VerifySignature}--------------------------*/
#if (SA_CSMASR43_USED == STD_OFF)
/*---------------------------{SA_VerifySignatureUpdate}-----------------------------*/
void SA_VerifySignatureUpdate(const u8* pubSignature)
{
    DBG_SA_VERIFYSIGNATUREUPDATE_ENTRY(pubSignature);

    /* Update the pointer to the received signature */
    m_pubCryptoSignature = pubSignature;

    if(m_eSaCsmState == SA_SIGNATURE_CHECK_STANDBY)
    {
        (void) Csm_SignatureVerifyFinish(SA_CSM_SIG_VERIFY_ID, m_pubCryptoSignature, SA_SIGNATURE_LENGTH, &m_ubVerifyResult);
        /* Continue with the signature verification */
        m_eSaCsmState = SA_SIGNATURE_CHECK_FINISH;
    }
    else
    {
        m_ubVerifSigUpdateReqReceived = SA_TRUE;
    }

    DBG_SA_VERIFYSIGNATUREUPDATE_EXIT();
}
#endif
/*------------------------{end SA_VerifySignatureUpdate}--------------------------*/
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
#if (SA_CSMASR43_USED == STD_OFF)
/*---------------------------{SA_CsmNotification}-----------------------------*/
Std_ReturnType SA_CsmNotification(Csm_ReturnType eCsmResult)
{
    DBG_SA_CSMNOTIFICATION_ENTRY(eCsmResult);
    switch(m_eSaCsmState)
    {
#if (SA_CSMASR43_USED == STD_OFF)
    case SA_SEED_GEN_STATE_INIT:
    case SA_SEED_GEN_STATE_START:
    case SA_SEED_GEN_STATE_UPDATE:
    case SA_RANDOM_GEN_STATE_STANDBY:
    case SA_RANDOM_GEN_STATE_GENERATE:
        SA_GenerateRandomCallback(eCsmResult);
        break;
#endif
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) && (SA_CSMASR43_USED == STD_OFF)
    case SA_SIGNATURE_CHECK_START:
    case SA_SIGNATURE_CHECK_UPDATE:
    case SA_SIGNATURE_CHECK_STANDBY:
    case SA_SIGNATURE_CHECK_FINISH:
        SA_SignatureVerifAndHashCallback(eCsmResult);
        break;
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
#if (SA_CSM_AESCTR_ENCRYPTION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
    case SA_AES_ENCRYPT_START:
    case SA_AES_ENCRYPT_UPDATE:
    case SA_AES_ENCRYPT_FINISH:
        SA_CsmAESEncryptCallback(eCsmResult);
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
        SA_SetSecuredKeyStatus(eCsmResult);
#endif
#endif
        break;
#endif /*(SA_CSM_AESCTR_ENCRYPTION_USED == STD_ON)*/
#if (SA_CSM_AESCTR_DECRYPTION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
    case SA_AES_DECRYPT_START:
    case SA_AES_DECRYPT_UPDATE:
    case SA_AES_DECRYPT_FINISH:
        SA_CsmAESDecryptCallback(eCsmResult);
        break;
#endif /*(SA_CSM_AESCTR_DECRYPTION_USED == STD_ON)*/
#if (SA_CSM_MAC_GENERATION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
    case SA_MAC_GENERATE_START:
    case SA_MAC_GENERATE_UPDATE:
    case SA_MAC_GENERATE_FINISH:
        SA_CsmMacGenerateCallback(eCsmResult);
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
        /*Set the Key Programming status if not set*/
        SA_SetSecuredKeyStatus(eCsmResult);
#endif
#endif
        break;
#endif /* (SA_CSM_MAC_GENERATION_USED == STD_ON)*/
#if (SA_CSM_MAC_VERIFICATION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
    case SA_MAC_VERIFY_START:
    case SA_MAC_VERIFY_UPDATE:
    case SA_MAC_VERIFY_FINISH:
        SA_CsmMacVerifyCallback(eCsmResult);
        break;
#endif /*(SA_CSM_MAC_VERIFICATION_USED == STD_ON)*/
    default:
        /* Nothing to do */
        break;
    }

    DBG_SA_CSMNOTIFICATION_EXIT(E_OK);
    return E_OK;
}
#endif
/*------------------------{end SA_CsmNotification}--------------------------*/
#if (SA_CSMASR43_USED == STD_ON)
/*----------------------------{SA_CsmNotification}-----------------------------*/
FUNC(void, CSM_APPL_CODE)SA_CsmNotification(P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job, Std_ReturnType result)
{
  DBG_SA_CSMNOTIFICATION_ENTRY(result);
  OSC_PARAM_UNUSED(job);
  OSC_PARAM_UNUSED(result);
 /*The CSM Notification is not supported*/
  DBG_SA_CSMNOTIFICATION_EXIT(E_OK);
}
#endif
#endif /*(SA_USE_CRYPTO == STD_ON)*/

/*---------------------------{SA_GetStatus}-----------------------------*/
tSaStatus SA_GetStatus(void)
{
    DBG_SA_GETSTATUS_ENTRY();
    DBG_SA_GETSTATUS_EXIT(m_eSaStatus);
    return m_eSaStatus;
}
/*------------------------{end SA_GetStatus}--------------------------*/

/*---------------------------{SA_Antiscanning}-----------------------------*/
tSaStatus SA_Antiscanning(u8 ubKeyMatch)
{
    tSaStatus eSaStatus;

    DBG_SA_ANTISCANNING_ENTRY(ubKeyMatch);
    if(ubKeyMatch == SA_TRUE)
    {
#if (SA_ANTISCANNING_ENABLED == STD_ON)
        if(m_stAntiscanInfo.ubRetryCnt != 0U)
        {
            /*Reset anti-scanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt = 0;
            m_stAntiscanInfo.ubAsLocked = SA_FALSE;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt(m_stAntiscanInfo.ubRetryCnt);
        }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
        /*Return status OK*/
        eSaStatus = SA_E_OK;
    }
    else
    {
#if (SA_ANTISCANNING_ENABLED == STD_ON)
        if((SA_AS_MAX_NB_RETRY-1U) > m_stAntiscanInfo.ubRetryCnt)
        {
            /*Increment antiscanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt++;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt(m_stAntiscanInfo.ubRetryCnt);
            /*Return INVALID KEY status*/
            eSaStatus = SA_E_NOK_INVALID_KEY;
        }
        else
        {
            /*Increment antiscanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt++;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt(m_stAntiscanInfo.ubRetryCnt);

            /*Load Anti-scanning Lock Timer */
            m_stAntiscanInfo.ulLockTimer = SA_AS_LOCK_TIMER;
            m_stAntiscanInfo.ubAsLocked = SA_TRUE;
            /*Return antiscanning Locked status*/
            eSaStatus = SA_E_NOK_AS_LOCKED;
        }
#else /* (SA_ANTISCANNING_ENABLED == STD_OFF) */
        /*Return INVALID KEY status*/
        eSaStatus = SA_E_NOK_INVALID_KEY;
#endif /* (SA_ANTISCANNING_ENABLED == STD_ON) */
    }
    m_eSaStatus = eSaStatus;
    DBG_SA_ANTISCANNING_EXIT(eSaStatus);
    return eSaStatus;
}
/*------------------------{end SA_Antiscanning}--------------------------*/

#if(SA_CSM_CANCELJOB_ENABLED == STD_ON)
Csm_ReturnType SA_CsmCancelActiveJobs(void)
{
    u32 ulCsmjobIndex;
    Csm_ReturnType eCsmCancelStatus;
    eCsmCancelStatus = CSM_E_OK;
    for (ulCsmjobIndex = 0U; (ulCsmjobIndex < SA_CSM_ALLJOBS_COUNT) && (CRYPTO_E_JOB_CANCELED != eCsmCancelStatus); ulCsmjobIndex++)
    {
        eCsmCancelStatus = Csm_CancelJob(ulCsmjobIndex,  CRYPTO_OPERATIONMODE_SINGLECALL);
    }
    /* Job cancellation return value E_NOT_OK is not considered as a failure as E_NOT_OK
     * could also mean that there was no job in the queue before to perform cancellation */
    eCsmCancelStatus = (eCsmCancelStatus == CRYPTO_E_JOB_CANCELED)? CRYPTO_E_JOB_CANCELED : CSM_E_OK;

    return eCsmCancelStatus;
}
#endif /*(SA_CSM_CANCELJOB_ENABLED == STD_ON)*/
#if(SA_CSM_SETKEY_ENABLED == STD_ON)
Csm_ReturnType SA_CsmSetKeys(Csm_SymKeyType const * ubKeyPtr, u8 ubSACsmJobTabId)
{
    Csm_ReturnType eCsmStatus;
    eCsmStatus = E_OK;

    if((m_astSACsmJobConf[ubSACsmJobTabId].ubAllowKeySet == PROG_TRUE) && \
            (ubKeyPtr != NULL_PTR))
    {
        eCsmStatus = Csm_KeyElementSet
                     (
                       m_astSACsmJobConf[ubSACsmJobTabId].ubCsmKeyID,
                       m_astSACsmJobConf[ubSACsmJobTabId].ubCryptoElementId,
                       (u8 const *)ubKeyPtr,
                       m_astSACsmJobConf[ubSACsmJobTabId].ubCryptoKeyLength
                     );
        if (eCsmStatus == E_OK)
        {
            /*Before the use of the key, set the key state to valid*/
            eCsmStatus = Csm_KeySetValid(m_astSACsmJobConf[ubSACsmJobTabId].ubCsmKeyID);
        }
    }

    return eCsmStatus;
}
#endif
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
/*------------------------------{SA_GetPublicKey}------------------------------*/
void SA_GetPublicKey(Csm_AsymPublicKeyType* pstPublicKey)
{
#if (SA_CSMASR43_USED == STD_OFF)
    u8 ubIdx;
#endif
#if (SA_CSMASR43_USED == STD_ON)
    u16 uwLocIdx;
#endif
#if (SA_CSMASR43_USED == STD_ON)
    u16 uwIdx;
#endif
    const u8 * paubPublicModulus;
    u32 ulPublicExponent;
#if (SA_CSMASR43_USED == STD_ON)
    uwLocIdx = 0U;
#endif
    SA_CustomGetAsymPublicKey(&paubPublicModulus, &ulPublicExponent);

    pstPublicKey->length = 0U;
#if (SA_CSMASR43_USED == STD_ON)
#if(SA_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[uwLocIdx] = (u8)(ulPublicExponent >> 24); /* Exponent */
    uwLocIdx = uwLocIdx + 1U;
    pstPublicKey->data[uwLocIdx] = (u8)(ulPublicExponent >> 16); /* Exponent */
    uwLocIdx = uwLocIdx + 1U;
    pstPublicKey->data[uwLocIdx] = (u8)(ulPublicExponent >> 8); /* Exponent */
    uwLocIdx = uwLocIdx + 1U;
    pstPublicKey->data[uwLocIdx] = (u8)ulPublicExponent; /* Exponent */
    uwLocIdx = uwLocIdx + 1U;
#endif
    for(uwIdx = 0U; /* Modulus */
        uwIdx < SA_PUBLIC_KEY_LENGTH;
        uwIdx++)
    {
        pstPublicKey->data[uwLocIdx] = paubPublicModulus[uwIdx];
        uwLocIdx = uwLocIdx + 1U;
    }
#else
#if(SA_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0] = 1U; /* Exponent size */
    pstPublicKey->data[1] = ulPublicExponent; /* Exponent */

    pstPublicKey->data[(SA_PUBLIC_KEY_LENGTH/sizeof(u32)) + 1U] = (SA_PUBLIC_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(ubIdx = 0U; /* Modulus */
        ubIdx < pstPublicKey->data[(SA_PUBLIC_KEY_LENGTH/sizeof(u32)) + 1U];
        ubIdx++)
    {
        u8 ubLocIdx = ubIdx + ((u8)(SA_PUBLIC_KEY_LENGTH/sizeof(u32))) + 2U;
        pstPublicKey->data[ubLocIdx] = (u32) paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 1U) - ((u16)ubIdx*4U))];
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 2U) - ((u16)ubIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#else /*(SA_CRY_EXPONENT_ENABLED == STD_OFF)*/

    pstPublicKey->data[0] = (SA_PUBLIC_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(ubIdx = 0U; /* Modulus */
        ubIdx < pstPublicKey->data[0];
        ubIdx++)
    {
        pstPublicKey->data[ubIdx + 1U] = (u32) paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 1U) - (ubIdx*4U))];
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 2U) - (ubIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 3U) - (ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 4U) - (ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif /*(SA_CRY_EXPONENT_ENABLED == STD_ON)*/
#endif /*(SA_CSMASR43_USED ==STD_ON)*/

}
/*----------------------------{End SA_GetPublicKey}----------------------------*/
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */
#if (SA_USE_CRYPTO == STD_ON)
#if (SA_CSM_AESCTR_ENCRYPTION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
void SA_CsmAESEncryptCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_AES_ENCRYPT_START:
                eCsmStatus = Csm_SymEncryptUpdate(
                m_stAESCTRpar.CsmCfdID,
                m_stAESCTRpar.PTptr,
                m_stAESCTRpar.PTLen,
                m_stAESCTRpar.CTptr,
                m_stAESCTRpar.CTLenptr);
                if (eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_AES_ENCRYPT_UPDATE;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;
                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
                break;
            case SA_AES_ENCRYPT_UPDATE:
                eCsmStatus = Csm_SymEncryptFinish
                (
                m_stAESCTRpar.CsmCfdID,
                m_stAESCTRpar.CTptr,
                m_stAESCTRpar.CTLenptr);
                if (eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_AES_ENCRYPT_FINISH;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;
                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
                break;
            case SA_AES_ENCRYPT_FINISH:
                m_eSaCsmState = SA_IDLE;
                SA_AM0001_SetStatus(SA_E_OK);
                break;
            default:
                m_eSaStatus = SA_E_NOT_OK;
                m_eSaCsmState = SA_IDLE;
                SA_AM0001_SetStatus(SA_E_NOT_OK);
                break;
        }
    }
    else
    {
        m_eSaStatus = SA_E_NOT_OK;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
}
#endif /*(SA_CSM_AESCTR_ENCRYPTION_USED == STD_ON)*/
#if (SA_CSM_AESCTR_DECRYPTION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
void SA_CsmAESDecryptCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_AES_DECRYPT_START:
                eCsmStatus = Csm_SymDecryptUpdate(
                m_stAESCTRpar.CsmCfdID,
                m_stAESCTRpar.CTptr,
                m_stAESCTRpar.CTLen,
                m_stAESCTRpar.PTptr,
                m_stAESCTRpar.PTLenptr);
                if (eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_AES_DECRYPT_UPDATE;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;
                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
                break;
            case SA_AES_DECRYPT_UPDATE:
            {
                eCsmStatus = Csm_SymDecryptFinish(
                m_stAESCTRpar.CsmCfdID,
                m_stAESCTRpar.PTptr,
                m_stAESCTRpar.PTLenptr
                );
                if (eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_AES_DECRYPT_FINISH;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;
                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
            }
                break;
            case SA_AES_DECRYPT_FINISH:
                m_eSaCsmState = SA_IDLE;
                SA_AM0001_SetStatus(SA_E_OK);
                break;
            default:
                m_eSaStatus = SA_E_NOT_OK;
                m_eSaCsmState = SA_IDLE;
                SA_AM0001_SetStatus(SA_E_NOT_OK);
                break;
        }
    }
    else
    {
        m_eSaStatus = SA_E_NOT_OK;
        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
}
#endif /*(SA_CSM_AESCTR_DECRYPTION_USED == STD_ON)*/
#if (SA_CSM_MAC_GENERATION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
void SA_CsmMacGenerateCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_MAC_GENERATE_START:
                eCsmStatus = Csm_MacGenerateUpdate(
                        m_stMACpar.CsmCfdID,
                        m_stMACpar.DataPtr,
                        m_stMACpar. DataLen);

                if (eCsmStatus == CSM_E_OK)
                {

                    m_eSaCsmState = SA_MAC_GENERATE_UPDATE;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;

                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
                break;
            case SA_MAC_GENERATE_UPDATE:
            {
                eCsmStatus = Csm_MacGenerateFinish (
                        m_stMACpar.CsmCfdID,
                        m_stMACpar.MACPtr,
                        m_stMACpar.MACLenPtr,FALSE);
                if (eCsmStatus == CSM_E_OK)
                {

                    m_eSaCsmState = SA_MAC_GENERATE_FINISH;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;

                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
            }
            break;
            case SA_MAC_GENERATE_FINISH:

                m_eSaCsmState = SA_IDLE;

                SA_AM0001_SetStatus(SA_E_OK);
                break;
            default:
                m_eSaStatus = SA_E_NOT_OK;
                m_eSaCsmState = SA_IDLE;

                SA_AM0001_SetStatus(SA_E_NOT_OK);
                break;
        }
    }
    else
    {
        m_eSaStatus = SA_E_NOT_OK;

        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
}
#endif /*(SA_CSM_MAC_GENERATION_USED == STD_ON)*/
#if (SA_CSM_MAC_VERIFICATION_USED == STD_ON) && (SA_CSMASR43_USED == STD_OFF)
void SA_CsmMacVerifyCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_MAC_VERIFY_START:
                eCsmStatus = Csm_MacVerifyUpdate(
                        m_stMACpar.CsmCfdID,
                        m_stMACpar.DataPtr,
                        m_stMACpar. DataLen);

                if (eCsmStatus == CSM_E_OK)
                {

                    m_eSaCsmState = SA_MAC_VERIFY_UPDATE;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;

                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
                break;
            case SA_MAC_VERIFY_UPDATE:
            {
                eCsmStatus = Csm_MacVerifyFinish (
                        m_stMACpar.CsmCfdID,
                        m_stMACpar.MACPtr,
                        m_stMACpar.MACLen,
                        &m_ubMacVerificationResult);

                if (eCsmStatus == CSM_E_OK)
                {

                    m_eSaCsmState = SA_MAC_VERIFY_FINISH;
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;
                    m_eSaCsmState = SA_IDLE;

                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
            }
            break;
            case SA_MAC_VERIFY_FINISH:
                m_eSaCsmState = SA_IDLE;
                if (m_ubMacVerificationResult == CSM_E_OK)
                {
                    SA_AM0001_SetStatus(SA_E_OK);
                }
                else
                {
                    m_eSaStatus = SA_E_NOT_OK;

                    SA_AM0001_SetStatus(SA_E_NOT_OK);
                }
                break;
            default:
                m_eSaStatus = SA_E_NOT_OK;
                m_eSaCsmState = SA_IDLE;

                SA_AM0001_SetStatus(SA_E_NOT_OK);
                break;
        }
    }
    else
    {
        m_eSaStatus = SA_E_NOT_OK;

        SA_AM0001_SetStatus(SA_E_NOT_OK);
    }
}
#endif /*(SA_CSM_MAC_VERIFICATION_USED == STD_ON)*/
#endif /*(SA_CRYPTO_USED == STD_ON)*/
