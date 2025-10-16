/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Cry_Common.h>
#include <Cry_CCM_Common.h>
#include <Cry_CcmEncrypt.h>  /* !LINKSTO EB_CRY_0005,1 */

#if (CRY_CCM_ENC_ENABLED == STD_ON)

#include <Csm_SymBlockEncrypt.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Compute the MAC.
 **/
STATIC FUNC(void, CRY_CODE) Cry_CCMEncComputeMAC
(
 void
);

/** \brief Copy input data for processing.
 */
STATIC FUNC(void, CRY_CODE) Cry_CBCEncCopyFromInput
(
  void
);

/** \brief Encrypt the payload.
 */
STATIC FUNC(void, CRY_CODE) Cry_CCMEncPayload
(
  void
);

/** \brief Build the header.
 */
STATIC FUNC(void, CRY_CODE) Cry_CCMEncBuildHeader
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
STATIC VAR(Cry_CCMCtxType, CRY_VAR) Cry_CCMEncCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_CCM_EncStart,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CcmEncryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr,
  P2CONST(uint8,          AUTOMATIC, CRY_APPL_DATA) initVectorPtr,
          uint32                                    initVectorLength
)
{
  Csm_ReturnType locRetVal;

  if ( Cry_CCMEncCtx.ctxState == CRY_CCM_ENC_S_UNINIT )
  {
    Cry_CCMEncCtx.cfgPtr = (P2CONST(Cry_CcmCryptConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;
    Cry_CCMEncCtx.keyPtr = keyPtr;
    Cry_CCMEncCtx.oputTextLength = 0U;

    if (initVectorLength != (uint32)((uint32)15U - Cry_CCMEncCtx.cfgPtr->L))
    {
      locRetVal = CSM_E_NOT_OK;

      /* Nothing to do, exit. */
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    else
    {
      locRetVal = CSM_E_OK;

      Cry_CommonCopy(Cry_CCMEncCtx.IV,
                     initVectorPtr,
                     initVectorLength
                    );

      Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_WAIT_FOR_INIT;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_CCM_EncUpdate,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CcmEncryptUpdate
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

  if ( Cry_CCMEncCtx.ctxState == CRY_CCM_ENC_S_UNINIT )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CCMEncCtx.ctxState == CRY_CCM_ENC_S_INITIALIZED )
  {

    if (*oputTextLengthPtr < (iputTextLength + Cry_CCMEncCtx.cfgPtr->M))
    {
      locRetVal = CSM_E_SMALL_BUFFER;
      Csm_SymEncryptCallbackNotification(CSM_E_SMALL_BUFFER);
    }
    else
    {
      locRetVal = CSM_E_OK;

      Cry_CCMEncCtx.ctxState          = CRY_CCM_ENC_S_FORMAT_DATA;
      Cry_CCMEncCtx.iputTextPtr       = iputTextPtr;
      Cry_CCMEncCtx.initInDataPtr     = iputTextPtr;
      Cry_CCMEncCtx.iputTextLength    = iputTextLength;
      Cry_CCMEncCtx.inDataLen         = (uint32)(iputTextLength - Cry_CCMEncCtx.cfgPtr->aDataLen);
      Cry_CCMEncCtx.oputTextPtr       = oputTextPtr;
      Cry_CCMEncCtx.oputTextLengthPtr = oputTextLengthPtr;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_CCM_EncFinish,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CcmEncryptFinish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  Csm_ReturnType locRetVal;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( Cry_CCMEncCtx.ctxState == CRY_CCM_ENC_S_UNINIT )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CCMEncCtx.ctxState == CRY_CCM_ENC_S_INITIALIZED )
  {
    locRetVal = CSM_E_OK;

    /* context state administration */
    Cry_CCMEncCtx.oputTextPtr       = oputTextPtr;
    Cry_CCMEncCtx.oputTextLengthPtr = oputTextLengthPtr;
    Cry_CCMEncCtx.ctxState          = CRY_CCM_ENC_S_CP_COPY_TAG;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_CCM_EncMainFunction,1 */
FUNC(void, CRY_CODE) Cry_CcmEncryptMainFunction
(
  void
)
{
  switch ( Cry_CCMEncCtx.ctxState )
  {
    case CRY_CCM_ENC_S_UNINIT:
    break;

    case CRY_CCM_ENC_S_WAIT_FOR_INIT:
    {
      Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_INITIALIZED;

      /* Nothing to do, exit. */
      Csm_SymEncryptCallbackNotification(CSM_E_OK);
    }
    break;

    case CRY_CCM_ENC_S_FORMAT_DATA:
    {
      Cry_CCMEncBuildHeader();
    }
    break;

    case CRY_CCM_ENC_S_ENC_B0:
    {
      if(Cry_CCMEncCtx.encFinished == FALSE)
      {
        Csm_ReturnType retVal;

        retVal = Cry_CCMBlockEnc(&Cry_CCMEncCtx,
                                 Cry_CCMEncCtx.B0Mac,
                                 sizeof(Cry_CCMEncCtx.block),
                                 Cry_CCMEncCtx.lastCipherText,
                                 &Cry_CCMEncCtx.blockFilled
                                );

        /* Prepare the first IV for authentication(= Enc(B0)) */
        if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
        {
          Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

          Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
          Csm_SymEncryptServiceFinishNotification();
        }
      }
      else
      {
        Cry_CCMEncCtx.encFinished = FALSE;
        Cry_CCMEncCtx.macState    = CRY_CBC_ENC_S_REQ_SB_ST;
        Cry_CCMEncCtx.ctxState    = CRY_CCM_ENC_S_GEN_MAC;
      }
    }
    break;

    case CRY_CCM_ENC_S_GEN_MAC:
    {
      Cry_CCMEncComputeMAC();
    }
    break;

    case CRY_CCM_ENC_S_MOV_ADATA:
    {
      if (Cry_CCMEncCtx.cfgPtr->aDataLen != 0U)
      {
        Cry_CommonCopy(Cry_CCMEncCtx.oputTextPtr,
                       Cry_CCMEncCtx.initInDataPtr,
                       Cry_CCMEncCtx.cfgPtr->aDataLen
                      );

        Cry_CCMEncCtx.oputTextLength += Cry_CCMEncCtx.cfgPtr->aDataLen;
        Cry_CCMEncCtx.oputTextPtr     = &Cry_CCMEncCtx.oputTextPtr[Cry_CCMEncCtx.cfgPtr->aDataLen];
      }

      Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_ENC_MAC;
      Cry_CCMEncCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_ST;
    }
    break;

    case CRY_CCM_ENC_S_ENC_MAC:
    {
      if(Cry_CCMEncCtx.encFinished == FALSE)
      {
        uint32         encB0MacLen = sizeof(Cry_CCMEncCtx.encMac);
        Csm_ReturnType retVal;

        retVal = Cry_CCMBlockEnc(&Cry_CCMEncCtx,
                                 Cry_CCMEncCtx.B0Enc,
                                 sizeof(Cry_CCMEncCtx.paddedMac),
                                 Cry_CCMEncCtx.encMac,
                                 &encB0MacLen
                                );

        /* Prepare the first IV for CTR encryption Enc(Nonce|CTR = 0) */
        if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
        {
          Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

          Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
          Csm_SymEncryptServiceFinishNotification();
        }
      }
      else
      {
        /* Compute the final MAC = PaddedMac ^ Enc(Nonce|CTR = 0) */
        Cry_CommonXOR(Cry_CCMEncCtx.encMac,
                      Cry_CCMEncCtx.paddedMac,
                      Cry_CCMEncCtx.cfgPtr->M
                     );

        /* Prepare the length for the encryption */
        Cry_CCMEncCtx.iputTextLength = Cry_CCMEncCtx.inDataLen;
        Cry_CCMEncCtx.encFinished    = FALSE;

        Cry_CCMEncCtx.ctxState       = CRY_CCM_ENC_S_ENC_PAYLOAD;
        Cry_CCMEncCtx.payloadState   = CRY_PLD_ENC_S_REQ_SB_ST;
      }
    }
    break;

    case CRY_CCM_ENC_S_ENC_PAYLOAD:
    {
       /* If there is payload encrypt it. */
       if (Cry_CCMEncCtx.inDataLen != 0U)
       {
          Cry_CCMEncPayload();
       }
       else
       {
         Cry_CCMEncCtx.payloadState = CRY_PLD_ENC_S_UNINIT;
         Cry_CCMEncCtx.ctxState     = CRY_CCM_ENC_S_INITIALIZED;

         Csm_SymEncryptCallbackNotification(CSM_E_OK);
       }
    }
    break;

    case CRY_CCM_ENC_S_CP_COPY_TAG:
    {
      /* Move the pointer at the end of aData + enc(payload) */
      Cry_CCMEncCtx.oputTextPtr = &Cry_CCMEncCtx.oputTextPtr[Cry_CCMEncCtx.cfgPtr->aDataLen +
                                                             Cry_CCMEncCtx.inDataLen
                                                            ];

      Cry_CommonCopy(Cry_CCMEncCtx.oputTextPtr,
                     Cry_CCMEncCtx.encMac,
                     Cry_CCMEncCtx.cfgPtr->M
                    );

      Cry_CCMEncCtx.oputTextLength     += Cry_CCMEncCtx.cfgPtr->M;
      *Cry_CCMEncCtx.oputTextLengthPtr  = Cry_CCMEncCtx.oputTextLength;
      Cry_CCMEncCtx.oputTextPtr         = &Cry_CCMEncCtx.oputTextPtr[Cry_CCMEncCtx.cfgPtr->M];
      Cry_CCMEncCtx.ctxState            = CRY_CCM_ENC_S_UNINIT;

      Csm_SymEncryptCallbackNotification(CSM_E_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;

    case CRY_CCM_ENC_S_INITIALIZED:
    break;

    /* *** Cry_CcmEncryptMainFunction > DEFAULT *************************************** */
    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
    }
    break;
    /* CHECK: PARSE */
  }

}

FUNC(Std_ReturnType, CRY_CODE) Cry_CcmEncryptCallback
(
   Csm_ReturnType Result
)
{
  Std_ReturnType locRetVal;

  if(Result != CSM_E_OK)
  {
    locRetVal                   = E_NOT_OK;
    Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_UNINIT;
    Cry_CCMEncCtx.macState      = CRY_CBC_ENC_S_UNINIT;
    Cry_CCMEncCtx.blockEncState = CRY_AES_ENC_S_UNINIT;
    Cry_CCMEncCtx.payloadState  = CRY_PLD_ENC_S_UNINIT;

    Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
    Csm_SymEncryptServiceFinishNotification();
  }
  else
  {
    locRetVal = E_OK;

    switch(Cry_CCMEncCtx.macState)
    {
      case CRY_CBC_ENC_S_WAIT_SB_ST:
        {
          Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_ENC_AAD;
        }
        break;

      case CRY_CBC_ENC_S_WAIT_AAD_UPD:
        {
          Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_CP_FROM_INP;
        }
        break;

      case CRY_CBC_ENC_S_WAIT_SB_UPD:
        {
          Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_CP_FROM_INP;
        }
        break;

      case CRY_CBC_ENC_S_WAIT_SB_FIN:
        {
          Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_SAVE_MAC;
        }
        break;

      default:
        {
          break;
        }
    }

    switch(Cry_CCMEncCtx.blockEncState)
    {
      case CRY_AES_ENC_S_WAIT_SB_ST:
        {
          Cry_CCMEncCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_UPD;
        }
        break;

      case CRY_AES_ENC_S_WAIT_SB_UPD:
        {
          Cry_CCMEncCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_FIN;
        }
        break;

      case CRY_AES_ENC_S_WAIT_SB_FIN:
        {
          Cry_CCMEncCtx.blockEncState = CRY_AES_ENC_S_UNINIT;
          Cry_CCMEncCtx.encFinished   = TRUE;
        }
        break;

      default:
        {
          break;
        }
    }

    switch(Cry_CCMEncCtx.payloadState)
    {
      case CRY_PLD_ENC_S_WAIT_SB_ST:
        {
          Cry_CCMEncCtx.payloadState = CRY_PLD_ENC_S_CP_FROM_INP;
        }
        break;

      case CRY_PLD_ENC_S_WAIT_SB_UPD:
        {
          Cry_CCMEncCtx.payloadState = CRY_PLD_ENC_S_XOR_IN_DATA;
        }
        break;

      case CRY_PLD_ENC_S_WAIT_SB_FIN:
        {
          Cry_CCMEncCtx.payloadState = CRY_PLD_ENC_S_UNINIT;
          Cry_CCMEncCtx.ctxState     = CRY_CCM_ENC_S_INITIALIZED;

          Csm_SymEncryptCallbackNotification(Result);
        }
        break;

      default:
        {
          break;
        }
    }
  }

  return locRetVal;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(void, CRY_CODE) Cry_CCMEncComputeMAC
(
 void
)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  switch (Cry_CCMEncCtx.macState)
  {
    case CRY_CBC_ENC_S_REQ_SB_ST:
    {
      retVal = Cry_CBCReqStart(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_ENC_AAD:
    {
      retVal = Cry_CBCEncAad(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_CP_FROM_INP:
    {
      Cry_CBCEncCopyFromInput();
    }
    break;

    case CRY_CBC_ENC_S_REQ_SB_UPD:
    {
      retVal = Cry_CBCReqUpdate(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_REQ_SB_FIN:
    {
      retVal = Cry_CBCReqFinish(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_ENC_S_SAVE_MAC:
    {
      uint8 i;

      /* Pad MAC for CTR encryption. */
      Cry_CommonCopy(Cry_CCMEncCtx.paddedMac,
                     Cry_CCMEncCtx.lastCipherText,
                     Cry_CCMEncCtx.cfgPtr->M
                    );

      for(i = Cry_CCMEncCtx.cfgPtr->M; i < CRY_CCM_BLOCK_LEN; i++)
      {
        Cry_CCMEncCtx.paddedMac[i] = 0x00U;
      }

      Cry_CCMEncCtx.ctxState     = CRY_CCM_ENC_S_MOV_ADATA;
      Cry_CCMEncCtx.payloadState = CRY_CBC_ENC_S_UNINIT;
      Cry_CCMEncCtx.macState     = CRY_CBC_ENC_S_UNINIT;
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
      Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_UNINIT;
      Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
    }
    break;
    /* CHECK: PARSE */
  }
}

STATIC FUNC(void, CRY_CODE) Cry_CBCEncCopyFromInput
(
  void
)
{
  uint32 i;

  /* If there is enough data for one block process it otherwise pad the block. */
  if (Cry_CCMEncCtx.iputTextLength >= sizeof(Cry_CCMEncCtx.block))
  {
    /* First MAC the aData */
    if ((Cry_CCMEncCtx.aDataProcessed == FALSE) && (Cry_CCMEncCtx.cfgPtr->aDataLen != 0U))
    {
      if (Cry_CCMEncCtx.leftAData >= CRY_CCM_BLOCK_LEN)
      {
        /* Copy entire block from aData */
        Cry_CommonCopy(Cry_CCMEncCtx.block,
                       Cry_CCMEncCtx.iputTextPtr,
                       sizeof(Cry_CCMEncCtx.block)
                      );

        Cry_CCMEncCtx.iputTextPtr     = &Cry_CCMEncCtx.iputTextPtr[sizeof(Cry_CCMEncCtx.block)];
        Cry_CCMEncCtx.iputTextLength -= sizeof(Cry_CCMEncCtx.block);
        Cry_CCMEncCtx.leftAData      -= sizeof(Cry_CCMEncCtx.block);
      }
      else
      {
        /* Copy what is left from aData */
        Cry_CommonCopy(Cry_CCMEncCtx.block,
                       Cry_CCMEncCtx.iputTextPtr,
                       Cry_CCMEncCtx.leftAData
                      );


        for(i = Cry_CCMEncCtx.leftAData; i < CRY_CCM_BLOCK_LEN; i++)
        {
          Cry_CCMEncCtx.block[i] = 0x00U;
        }

        Cry_CCMEncCtx.iputTextPtr     = &Cry_CCMEncCtx.iputTextPtr[Cry_CCMEncCtx.leftAData];
        Cry_CCMEncCtx.iputTextLength -= Cry_CCMEncCtx.leftAData;

        Cry_CCMEncCtx.leftAData       = 0U;
        Cry_CCMEncCtx.aDataProcessed  = TRUE;
      }

      Cry_CommonXOR(Cry_CCMEncCtx.block,
                    Cry_CCMEncCtx.lastCipherText,
                    sizeof(Cry_CCMEncCtx.block)
                   );

      Cry_CCMEncCtx.macState          = CRY_CBC_ENC_S_REQ_SB_UPD;
    }
    else
    {
      Cry_CommonCopy(Cry_CCMEncCtx.block,
                     Cry_CCMEncCtx.iputTextPtr,
                     sizeof(Cry_CCMEncCtx.block)
                    );

      Cry_CommonXOR(Cry_CCMEncCtx.block,
                    Cry_CCMEncCtx.lastCipherText,
                    sizeof(Cry_CCMEncCtx.block)
                   );

      Cry_CCMEncCtx.iputTextPtr     = &Cry_CCMEncCtx.iputTextPtr[sizeof(Cry_CCMEncCtx.block)];
      Cry_CCMEncCtx.iputTextLength -= sizeof(Cry_CCMEncCtx.block);

      /* context state administration */
      Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_REQ_SB_UPD;
    }
  }
  else
  {
    if (Cry_CCMEncCtx.iputTextLength == 0U)
    {
      Cry_CCMEncCtx.macState = CRY_CBC_ENC_S_REQ_SB_FIN;
    }
    else
    {
      /* copy and do padding */
      Cry_CommonCopy(Cry_CCMEncCtx.block,
                     Cry_CCMEncCtx.iputTextPtr,
                     Cry_CCMEncCtx.iputTextLength
                    );

      for(i = Cry_CCMEncCtx.iputTextLength; i < CRY_CCM_BLOCK_LEN; i++)
      {
        Cry_CCMEncCtx.block[i] = 0x00U;
      }

      Cry_CommonXOR(Cry_CCMEncCtx.block,
                    Cry_CCMEncCtx.lastCipherText,
                    sizeof(Cry_CCMEncCtx.block)
                   );

      Cry_CCMEncCtx.iputTextLength = 0U;
      Cry_CCMEncCtx.macState       = CRY_CBC_ENC_S_REQ_SB_UPD;
    }

  }
}

STATIC FUNC(void, CRY_CODE) Cry_CCMEncPayload
(
  void
)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  switch ( Cry_CCMEncCtx.payloadState )
  {
    case CRY_PLD_ENC_S_REQ_SB_ST:
    {
      retVal = Cry_CTRReqStart(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_PLD_ENC_S_CP_FROM_INP:
    {
      Cry_CTRCopyFromInput(&Cry_CCMEncCtx);
    }
    break;

    case CRY_PLD_ENC_S_REQ_SB_UPD:
    {
      retVal = Cry_CTRReqUpdate(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_PLD_ENC_S_XOR_IN_DATA:
    {
      Cry_CCMEncCtx.payloadState = CRY_PLD_ENC_S_CP_TO_OUTP;

      Cry_CommonXOR(Cry_CCMEncCtx.block,
                    Cry_CCMEncCtx.encIV,
                    Cry_CCMEncCtx.blockFilled
                   );
    }
    break;

    case CRY_PLD_ENC_S_CP_TO_OUTP:
    {
      Cry_CommonCopy(Cry_CCMEncCtx.oputTextPtr,
                     Cry_CCMEncCtx.block,
                     Cry_CCMEncCtx.blockFilled
                    );

      Cry_CCMEncCtx.oputTextLength += Cry_CCMEncCtx.blockFilled;
      Cry_CCMEncCtx.oputTextPtr     = &Cry_CCMEncCtx.oputTextPtr[Cry_CCMEncCtx.blockFilled];
      Cry_CCMEncCtx.payloadState    = CRY_PLD_ENC_S_CP_FROM_INP;
    }
    break;

    case CRY_PLD_ENC_S_REQ_SB_FIN:
    {
      retVal = Cry_CTRReqFinish(&Cry_CCMEncCtx);

      if ((retVal != CSM_E_OK) && (retVal != CSM_E_BUSY))
      {
        Cry_CCMEncCtx.ctxState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
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
      Cry_CCMEncCtx.payloadState = CRY_PLD_ENC_S_UNINIT;
      Cry_CCMEncCtx.ctxState     = CRY_CCM_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
    }
    break;
    /* CHECK: PARSE */
  }
}

STATIC FUNC(void, CRY_CODE) Cry_CCMEncBuildHeader
(
  void
)
{
  uint32 payloadLen = (uint32)(Cry_CCMEncCtx.iputTextLength   -
                               Cry_CCMEncCtx.cfgPtr->aDataLen
                              );

  Cry_CCMFormatHeader(&Cry_CCMEncCtx, payloadLen);

  if(Cry_CCMEncCtx.cfgPtr->aDataLen != 0U)
  {
    Cry_CCMFormatAad(&Cry_CCMEncCtx);
  }

  Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_ENC_B0;
  Cry_CCMEncCtx.blockEncState = CRY_AES_ENC_S_REQ_SB_ST;

  /* If the payload length is bigger than what we can code on L bytes exit. */
  switch (Cry_CCMEncCtx.cfgPtr->L)
  {
    case 2U:
    {
      if (payloadLen > 0xFFFFU)
      {
        Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_UNINIT;
        Cry_CCMEncCtx.blockEncState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case 3U:
    {
      if (payloadLen > 0xFFFFFFU)
      {
        Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_UNINIT;
        Cry_CCMEncCtx.blockEncState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;
    /* CHECK: NOPARSE */
    case 4U:
    {
      if (payloadLen > 0xFFFFFFFFUL)
      {
        Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_UNINIT;
        Cry_CCMEncCtx.blockEncState = CRY_CCM_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;
    /* CHECK: PARSE */
    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      Cry_CCMEncCtx.ctxState      = CRY_CCM_ENC_S_UNINIT;
      Cry_CCMEncCtx.blockEncState = CRY_CCM_ENC_S_UNINIT;

      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;
    /* CHECK: PARSE */
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*----------------------------------------------------------------------------*/
#else /* #if (CRY_CCM_ENC_ENABLED == STD_ON) */

typedef uint8 Cry_CcmEncrypt_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CCM_ENC_ENABLED == STD_ON) #else */
