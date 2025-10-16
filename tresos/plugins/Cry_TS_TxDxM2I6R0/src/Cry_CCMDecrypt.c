/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Cry_Common.h>
#include <Cry_CCM_Common.h>
#include <Cry_CcmDecrypt.h>  /* !LINKSTO EB_CRY_0005,1 */

#if (CRY_CCM_DEC_ENABLED == STD_ON)

#include <Csm_SymBlockEncrypt.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Compute the MAC.
 **/
STATIC FUNC(void, CRY_CODE) Cry_CCMDecComputeMAC
(
 void
);

/** \brief Copy input data for processing.
 */
static FUNC(void, CRY_CODE) Cry_CBCDecCopyFromInput
(
  void
);

/** \brief Decrypt the payload.
 */
STATIC FUNC(void, CRY_CODE) Cry_CCMDecPayload
(
  void
);

/** \brief Build the header.
 */
STATIC FUNC(void, CRY_CODE) Cry_CCMDecBuildHeader
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_CCMCtxType, CRY_VAR) Cry_CCMDecCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_CCM_DecStart,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CcmDecryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr,
  P2CONST(uint8,          AUTOMATIC, CRY_APPL_DATA) initVectorPtr,
          uint32                                    initVectorLength
)
{
  Csm_ReturnType       locRetVal;

  Cry_CCMDecCtx.cfgPtr = (P2CONST(Cry_CcmCryptConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;
  Cry_CCMDecCtx.keyPtr = keyPtr;

  if ( Cry_CCMDecCtx.ctxState == CRY_CCM_ENC_S_UNINIT )
  {
    if (initVectorLength != (uint32)((uint32)15U - Cry_CCMDecCtx.cfgPtr->L))
    {
      /* The nonce length doesn't match the constraints specified in the configuration */
      locRetVal = CSM_E_NOT_OK;

      /* Nothing to do, exit. */
      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    else
    {
      locRetVal = CSM_E_OK;

      Cry_CommonCopy(Cry_CCMDecCtx.IV,
                     initVectorPtr,
                     initVectorLength
                    );

      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_WAIT_FOR_INIT;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_CCM_DecUpdate,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CcmDecryptUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) iputTextPtr,
          uint32                            iputTextLength,
    P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  Csm_ReturnType locRetVal;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( Cry_CCMDecCtx.ctxState == CRY_CCM_ENC_S_UNINIT )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CCMDecCtx.ctxState == CRY_CCM_ENC_S_INITIALIZED )
  {

    if (iputTextLength <= Cry_CCMDecCtx.cfgPtr->M)
    {
      locRetVal              = CSM_E_NOT_OK;
      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    else if (*oputTextLengthPtr < (iputTextLength - Cry_CCMDecCtx.cfgPtr->M))
    {
      locRetVal = CSM_E_SMALL_BUFFER;
      Csm_SymDecryptCallbackNotification(CSM_E_SMALL_BUFFER);
    }
    else
    {
      locRetVal = CSM_E_OK;

      Cry_CCMDecCtx.ctxState          = CRY_CCM_ENC_S_FORMAT_DATA;
      Cry_CCMDecCtx.iputTextPtr       = iputTextPtr;
      Cry_CCMDecCtx.initInDataPtr     = iputTextPtr;
      Cry_CCMDecCtx.iputTextLength    = iputTextLength;
      Cry_CCMDecCtx.inDataLen         = (uint32)(iputTextLength - Cry_CCMDecCtx.cfgPtr->M);
      Cry_CCMDecCtx.oputTextPtr       = oputTextPtr;
      Cry_CCMDecCtx.oputTextLengthPtr = oputTextLengthPtr;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_CCM_DecFinish,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CcmDecryptFinish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  if ( Cry_CCMDecCtx.ctxState == CRY_CCM_ENC_S_UNINIT )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CCMDecCtx.ctxState == CRY_CCM_ENC_S_INITIALIZED )
  {
    locRetVal = CSM_E_OK;

    /* context state administration */
    Cry_CCMDecCtx.oputTextPtr       = oputTextPtr;
    Cry_CCMDecCtx.oputTextLengthPtr = oputTextLengthPtr;
    Cry_CCMDecCtx.ctxState          = CRY_CCM_ENC_S_CP_PLAINTEXT;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_CCM_DecMainFunction,1 */
FUNC(void, CRY_CODE) Cry_CcmDecryptMainFunction
(
  void
)
{
  switch ( Cry_CCMDecCtx.ctxState )
  {
    case CRY_CCM_ENC_S_UNINIT:
    break;

    case CRY_CCM_ENC_S_WAIT_FOR_INIT:
    {
      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_INITIALIZED;

      /* Nothing to do, exit. */
      Csm_SymDecryptCallbackNotification(CSM_E_OK);
    }
    break;

    case CRY_CCM_ENC_S_FORMAT_DATA:
    {
      Cry_CCMDecBuildHeader();
    }
    break;

    case CRY_CCM_ENC_S_ENC_PAYLOAD:
    {
      Cry_CCMDecPayload();
    }
    break;

    case CRY_CCM_ENC_S_ENC_B0:
    {
      if(Cry_CCMDecCtx.encFinished == FALSE)
      {
        uint32         encB0MacLen = sizeof(Cry_CCMDecCtx.encMac);
        Csm_ReturnType retVal;

        retVal = Cry_CCMBlockEnc(&Cry_CCMDecCtx,
                                 Cry_CCMDecCtx.B0Mac,
                                 sizeof(Cry_CCMDecCtx.block),
                                 Cry_CCMDecCtx.lastCipherText,
                                 &encB0MacLen
                                );

        /* Prepare B0/header for authentication */
        if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
        {
          Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

          Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
          Csm_SymDecryptServiceFinishNotification();
        }
      }
      else
      {
        Cry_CCMDecCtx.encFinished = FALSE;
        Cry_CCMDecCtx.macState    = CRY_CBC_ENC_S_REQ_SB_ST;
        Cry_CCMDecCtx.ctxState    = CRY_CCM_ENC_S_GEN_MAC;

        /* Set the pointer to the data needed for MAC. */
        Cry_CCMDecCtx.processPtr     = Cry_CCMDecCtx.plainText;
        Cry_CCMDecCtx.iputTextLength = Cry_CCMDecCtx.inDataLen;
        Cry_CCMDecCtx.iputTextPtr    = Cry_CCMDecCtx.initInDataPtr;

        if(Cry_CCMDecCtx.cfgPtr->aDataLen != 0U)
        {
          Cry_CCMFormatAad(&Cry_CCMDecCtx);
        }

        Cry_CCMDecCtx.processedPT = (Cry_CCMDecCtx.inDataLen - Cry_CCMDecCtx.cfgPtr->aDataLen);

      }
    }
    break;

    case CRY_CCM_ENC_S_GEN_MAC:
    {
      Cry_CCMDecComputeMAC();
    }
    break;

    case CRY_CCM_ENC_S_ENC_MAC:
    {
      if(Cry_CCMDecCtx.encFinished == FALSE)
      {
        uint32         encB0MacLen = sizeof(Cry_CCMDecCtx.encMac);
        Csm_ReturnType retVal;

        retVal = Cry_CCMBlockEnc(&Cry_CCMDecCtx,
                                 Cry_CCMDecCtx.B0Enc,
                                 sizeof(Cry_CCMDecCtx.encMac),
                                 Cry_CCMDecCtx.encMac,
                                 &encB0MacLen
                                );

        /* B0Enc = encoded IV with CTR = 0 */
        if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
        {
          Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

          Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
          Csm_SymDecryptServiceFinishNotification();
        }
      }
      else
      {
        /* Finialize the MAC calculation */
        Cry_CommonXOR(Cry_CCMDecCtx.encMac,
                      Cry_CCMDecCtx.paddedMac,
                      sizeof(Cry_CCMDecCtx.encMac)
                     );

        Cry_CCMDecCtx.encFinished = FALSE;
        Cry_CCMDecCtx.ctxState    = CRY_CCM_ENC_S_INITIALIZED;

        Csm_SymDecryptCallbackNotification(CSM_E_OK);
      }
    }
    break;

    case CRY_CCM_ENC_S_CP_PLAINTEXT:
    {
      uint32  i;
      boolean macFailed = FALSE;

      for (i = 0U; i < Cry_CCMDecCtx.cfgPtr->M; i++)
      {
        if(Cry_CCMDecCtx.initInDataPtr[i + Cry_CCMDecCtx.inDataLen] != Cry_CCMDecCtx.encMac[i])
        {
          macFailed = TRUE;

          break;
        }
      }

      if(macFailed == TRUE)
      {
       /* If the MAC does not match erase the decrypted ciphertext. */
        for (i = 0U; i < (Cry_CCMDecCtx.inDataLen - Cry_CCMDecCtx.cfgPtr->aDataLen); i++)
        {
          Cry_CCMDecCtx.plainText[i] = 0x00U;
        }

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
      else
      {
        Cry_CommonCopy(Cry_CCMDecCtx.oputTextPtr,
                       Cry_CCMDecCtx.initInDataPtr,
                       Cry_CCMDecCtx.cfgPtr->aDataLen
                      );

        Cry_CommonCopy(&Cry_CCMDecCtx.oputTextPtr[Cry_CCMDecCtx.cfgPtr->aDataLen],
                       Cry_CCMDecCtx.plainText,
                       (Cry_CCMDecCtx.inDataLen - Cry_CCMDecCtx.cfgPtr->aDataLen)
                      );

        Csm_SymDecryptCallbackNotification(CSM_E_OK);
        Csm_SymDecryptServiceFinishNotification();
      }

      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;
    }
    break;

    /* *** Cry_CcmDecryptMainFunction > DEFAULT *************************************** */
    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
    /* CHECK: PARSE */
  }

}

FUNC(Std_ReturnType, CRY_CODE) Cry_CcmDecryptCallback
(
   Csm_ReturnType Result
)
{
  Std_ReturnType locRetVal;

  if (Result != CSM_E_OK)
  {
    locRetVal                   = E_NOT_OK;
    Cry_CCMDecCtx.ctxState      = CRY_CCM_ENC_S_UNINIT;
    Cry_CCMDecCtx.macState      = CRY_CBC_ENC_S_UNINIT;
    Cry_CCMDecCtx.blockEncState = CRY_AES_ENC_S_UNINIT;
    Cry_CCMDecCtx.payloadState  = CRY_PLD_ENC_S_UNINIT;

    Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
    Csm_SymDecryptServiceFinishNotification();
  }
  else
  {
    locRetVal = E_OK;

    switch(Cry_CCMDecCtx.macState)
    {
      case CRY_CBC_ENC_S_WAIT_SB_ST:
        {
          Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_ENC_AAD;
        }
        break;

      case CRY_CBC_ENC_S_WAIT_AAD_UPD:
        {
          Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_CP_FROM_INP;
        }
        break;

      case CRY_CBC_ENC_S_WAIT_SB_UPD:
        {
          Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_CP_FROM_INP;
        }
        break;

      case CRY_CBC_ENC_S_WAIT_SB_FIN:
        {
          Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_SAVE_MAC;
        }
        break;

      default:
        {
          break;
        }
    }

    switch(Cry_CCMDecCtx.blockEncState)
    {
      case CRY_AES_ENC_S_WAIT_SB_ST:
        {
          Cry_CCMDecCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_UPD;
        }
        break;

      case CRY_AES_ENC_S_WAIT_SB_UPD:
        {
          Cry_CCMDecCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_FIN;
        }
        break;

      case CRY_AES_ENC_S_WAIT_SB_FIN:
        {
          Cry_CCMDecCtx.blockEncState = CRY_AES_ENC_S_UNINIT;
          Cry_CCMDecCtx.encFinished   = TRUE;
        }
        break;

      default:
        {
          break;
        }
    }

    switch(Cry_CCMDecCtx.payloadState)
    {
      case CRY_PLD_ENC_S_WAIT_SB_ST:
        {
          Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_CP_FROM_INP;
        }
        break;

      case CRY_PLD_ENC_S_WAIT_SB_UPD:
        {
          Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_XOR_IN_DATA;
        }
        break;

      case CRY_PLD_ENC_S_WAIT_SB_FIN:
        {
          Cry_CCMDecCtx.payloadState  = CRY_PLD_ENC_S_UNINIT;
          Cry_CCMDecCtx.ctxState      = CRY_CCM_ENC_S_ENC_B0;
          Cry_CCMDecCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_ST;
        }
        break;

      default:
        {
        }
        break;
    }
  }

  return locRetVal;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(void, CRY_CODE) Cry_CCMDecComputeMAC
(
 void
)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  switch (Cry_CCMDecCtx.macState)
  {
    case CRY_CBC_ENC_S_REQ_SB_ST:
    {
      retVal = Cry_CBCReqStart(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_ENC_AAD:
    {
      retVal = Cry_CBCEncAad(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_CP_FROM_INP:
    {
      Cry_CBCDecCopyFromInput();
    }
    break;

    case CRY_CBC_ENC_S_REQ_SB_UPD:
    {
      retVal = Cry_CBCReqUpdate(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_REQ_SB_FIN:
    {
      retVal = Cry_CBCReqFinish(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_SAVE_MAC:
    {
      uint8 i;

      /* Pad MAC for CTR decryption. */
      Cry_CommonCopy(Cry_CCMDecCtx.paddedMac,
                     Cry_CCMDecCtx.lastCipherText,
                     Cry_CCMDecCtx.cfgPtr->M
                    );

      for(i = Cry_CCMDecCtx.cfgPtr->M; i < CRY_CCM_BLOCK_LEN; i++)
      {
        Cry_CCMDecCtx.paddedMac[i] = 0x00U;
      }

      Cry_CCMDecCtx.ctxState      = CRY_CCM_ENC_S_ENC_MAC;
      Cry_CCMDecCtx.macState      = CRY_CBC_ENC_S_UNINIT;
      Cry_CCMDecCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_ST;
    }
    break;

    case CRY_CBC_ENC_S_WAIT_SB_ST:
    case CRY_CBC_ENC_S_WAIT_SB_UPD:
    case CRY_CBC_ENC_S_WAIT_AAD_UPD:
    case CRY_CBC_ENC_S_WAIT_SB_FIN:
    {
    }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    case CRY_CBC_ENC_S_UNINIT:
    default:
    {
      Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_UNINIT;
      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
    /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_CBCDecCopyFromInput
(
  void
)
{
  uint32 i;

  /* If there is enough data for one block process it otherwise wait for another Update. */
  if (Cry_CCMDecCtx.iputTextLength >= sizeof(Cry_CCMDecCtx.block))
  {

    /* First MAC the aData */
    if ((Cry_CCMDecCtx.aDataProcessed == FALSE) && (Cry_CCMDecCtx.cfgPtr->aDataLen != 0U))
    {
      if (Cry_CCMDecCtx.leftAData >= CRY_CCM_BLOCK_LEN)
      {
        /* Copy entire block from aData */
        Cry_CommonCopy(Cry_CCMDecCtx.block,
                       Cry_CCMDecCtx.iputTextPtr,
                       sizeof(Cry_CCMDecCtx.block)
                      );

        Cry_CommonXOR(Cry_CCMDecCtx.block,
                      Cry_CCMDecCtx.lastCipherText,
                      sizeof(Cry_CCMDecCtx.block)
                     );

        Cry_CCMDecCtx.iputTextPtr     = &Cry_CCMDecCtx.iputTextPtr[sizeof(Cry_CCMDecCtx.block)];
        Cry_CCMDecCtx.iputTextLength -= sizeof(Cry_CCMDecCtx.block);
        Cry_CCMDecCtx.leftAData      -= sizeof(Cry_CCMDecCtx.block);
      }
      else
      {
        /* Copy what is left from aData */
        Cry_CommonCopy(Cry_CCMDecCtx.block,
                       Cry_CCMDecCtx.iputTextPtr,
                       Cry_CCMDecCtx.leftAData
                      );

        for(i = Cry_CCMDecCtx.leftAData; i < CRY_CCM_BLOCK_LEN; i++)
        {
          Cry_CCMDecCtx.block[i] = 0x00U;
        }

        Cry_CommonXOR(Cry_CCMDecCtx.block,
                      Cry_CCMDecCtx.lastCipherText,
                      sizeof(Cry_CCMDecCtx.block)
                     );

        Cry_CCMDecCtx.iputTextPtr     = &Cry_CCMDecCtx.iputTextPtr[Cry_CCMDecCtx.leftAData];
        Cry_CCMDecCtx.iputTextLength -= Cry_CCMDecCtx.leftAData;

        Cry_CCMDecCtx.leftAData       = 0U;
        Cry_CCMDecCtx.aDataProcessed  = TRUE;
      }

      Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_REQ_SB_UPD;
    }
    else
    {
      Cry_CommonCopy(Cry_CCMDecCtx.block,
                     Cry_CCMDecCtx.processPtr,
                     sizeof(Cry_CCMDecCtx.block)
                    );

       Cry_CommonXOR(Cry_CCMDecCtx.block,
                     Cry_CCMDecCtx.lastCipherText,
                     sizeof(Cry_CCMDecCtx.block)
                    );

       Cry_CCMDecCtx.processPtr      = &Cry_CCMDecCtx.processPtr[sizeof(Cry_CCMDecCtx.block)];
       Cry_CCMDecCtx.processedPT    -= sizeof(Cry_CCMDecCtx.block);
       Cry_CCMDecCtx.iputTextLength -= sizeof(Cry_CCMDecCtx.block);
       Cry_CCMDecCtx.macState        = CRY_CBC_ENC_S_REQ_SB_UPD;
    }
  }
  else
  {
    if (Cry_CCMDecCtx.iputTextLength == 0U)
    {
      Cry_CCMDecCtx.macState = CRY_CBC_ENC_S_REQ_SB_FIN;
    }
    else
    {
      /* copy and do padding */
      Cry_CommonCopy(Cry_CCMDecCtx.block,
                     Cry_CCMDecCtx.processPtr,
                     Cry_CCMDecCtx.processedPT
                    );

      for(i = Cry_CCMDecCtx.processedPT; i < CRY_CCM_BLOCK_LEN; i++)
      {
        Cry_CCMDecCtx.block[i] = 0x00U;
      }

      Cry_CommonXOR(Cry_CCMDecCtx.block,
                    Cry_CCMDecCtx.lastCipherText,
                    sizeof(Cry_CCMDecCtx.block)
                   );

      Cry_CCMDecCtx.iputTextLength = 0U;
      Cry_CCMDecCtx.processedPT    = 0U;
      Cry_CCMDecCtx.macState       = CRY_CBC_ENC_S_REQ_SB_UPD;
    }
  }
}

STATIC FUNC(void, CRY_CODE) Cry_CCMDecPayload
(
  void
)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  switch ( Cry_CCMDecCtx.payloadState )
  {
    case CRY_PLD_ENC_S_REQ_SB_ST:
    {
      retVal = Cry_CTRReqStart(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_PLD_ENC_S_CP_FROM_INP:
    {
      Cry_CTRCopyFromInput(&Cry_CCMDecCtx);
    }
    break;

    case CRY_PLD_ENC_S_REQ_SB_UPD:
    {
      retVal = Cry_CTRReqUpdate(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_PLD_ENC_S_XOR_IN_DATA:
    {
      Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_CP_TO_OUTP;

      Cry_CommonXOR(Cry_CCMDecCtx.block,
                    Cry_CCMDecCtx.encIV,
                    Cry_CCMDecCtx.blockFilled
                   );
    }
    break;

    case CRY_PLD_ENC_S_CP_TO_OUTP:
    {
      Cry_CommonCopy(Cry_CCMDecCtx.processPtr,
                     Cry_CCMDecCtx.block,
                     Cry_CCMDecCtx.blockFilled
                    );

      Cry_CCMDecCtx.processPtr   = &Cry_CCMDecCtx.processPtr[Cry_CCMDecCtx.blockFilled];
      Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_CP_FROM_INP;
    }
    break;

    case CRY_PLD_ENC_S_REQ_SB_FIN:
    {
      retVal = Cry_CTRReqFinish(&Cry_CCMDecCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_PLD_ENC_S_WAIT_SB_ST:
    case CRY_PLD_ENC_S_WAIT_SB_UPD:
    case CRY_PLD_ENC_S_WAIT_SB_FIN:
    {
    }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    case CRY_PLD_ENC_S_UNINIT:
    default:
    {
      Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_UNINIT;
      Cry_CCMDecCtx.ctxState     = CRY_CCM_ENC_S_UNINIT;
      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
    /* CHECK: PARSE */
  }
}

STATIC FUNC(void, CRY_CODE) Cry_CCMDecBuildHeader
(
  void
)
{
  uint32 payloadLen = (uint32)(Cry_CCMDecCtx.iputTextLength   -
                               Cry_CCMDecCtx.cfgPtr->aDataLen -
                               Cry_CCMDecCtx.cfgPtr->M
                              );

  Cry_CCMFormatHeader(&Cry_CCMDecCtx, payloadLen);

  /* Input data length without the tag. */
  Cry_CCMDecCtx.iputTextLength = payloadLen;

  /* Location where to store the plaintext after CTR decryption */
  Cry_CCMDecCtx.processPtr     = Cry_CCMDecCtx.plainText;
  Cry_CCMDecCtx.blockFilled    = sizeof(Cry_CCMDecCtx.block);

  Cry_CCMDecCtx.ctxState       = CRY_CCM_ENC_S_ENC_PAYLOAD;
  Cry_CCMDecCtx.payloadState   = CRY_PLD_ENC_S_REQ_SB_ST;

  /* If the payload length is bigger than what we can code on L bytes exit. */
  switch (Cry_CCMDecCtx.cfgPtr->L)
  {
    case 2U:
    {
      if (payloadLen > 0xFFFFU)
      {
        Cry_CCMDecCtx.ctxState     = CRY_CCM_ENC_S_UNINIT;
        Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case 3U:
    {
      if (payloadLen > 0xFFFFFFU)
      {
        Cry_CCMDecCtx.ctxState     = CRY_CCM_ENC_S_UNINIT;
        Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;
    /* CHECK: NOPARSE */
    case 4U:
    {
      if (payloadLen > 0xFFFFFFFFUL)
      {
        Cry_CCMDecCtx.ctxState     = CRY_CCM_ENC_S_UNINIT;
        Cry_CCMDecCtx.payloadState = CRY_PLD_ENC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;
    /* CHECK: PARSE */

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      Cry_CCMDecCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
    /* CHECK: PARSE */
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*----------------------------------------------------------------------------*/
#else /* #if (CRY_CCM_DEC_ENABLED == STD_ON) */

typedef uint8 Cry_CcmDecrypt_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CCM_DEC_ENABLED == STD_ON) #else */
